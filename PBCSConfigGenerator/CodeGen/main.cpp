//
// Created by QingG on 2025/9/27.
//

#include "Typedef.h"
#include <iostream>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <configElem/Config.h>
#include <configElem/PacketType.h>
#include <configElem/Packet.h>
#include <configElem/Data.h>
#include <FileOperation.h>
#include <map>
#include <qchar.h>
#include <qdebug.h>
#include <qlocale.h>

using namespace PBCS;

std::string TAB = "    ";

void outputStart(const std::string& onceDefine,QTextStream& stream) {
    if (onceDefine == "*once") {
        stream << "#pragma once" << Qt::endl;
    }else {
        stream << "#ifndef " << onceDefine.c_str() << Qt::endl;
        stream << "#define " << onceDefine.c_str() << Qt::endl;
    }
    stream << Qt::endl;
    stream << "#include \"PBCSConfig.h\"" << Qt::endl << Qt::endl;
}

void outputEnd(const std::string& onceDefine,QTextStream& stream) {
    if (onceDefine != "*once") {
        stream << "#endif" << Qt::endl;
    }
}

void outputPacketData(
    PBCS_DTID dtid,
    Data * data,
    const QString& pkttypeName,
    const QString& pktNameCstr,
    bool upperCase,
    const QString& prefix,
    QTextStream& stream) {
    QString dtNameCstr;
    if (!upperCase)
        dtNameCstr = data->getName().c_str();
    else
        dtNameCstr = QString::fromStdString(data->getName()).toUpper();
    stream << "#define " << prefix << "DTID"
           << pkttypeName << "_" << pktNameCstr << "_" << dtNameCstr
           << " " << dtid << Qt::endl;
}

void outputPacketDefine(
    Packet* packet,
    const QString& pkttypeName,
    bool upperCase,
    const QString& prefix,
    QTextStream& stream) {
    QString pktNameCstr;
    if (!upperCase) 
        pktNameCstr = packet->getName().c_str();
    else
        pktNameCstr = QString::fromStdString(packet->getName()).toUpper();
    stream << "#define " << prefix << "PID" << pkttypeName << "_" << pktNameCstr
           << " " << packet->getID() << Qt::endl;

    packet->iterate([&](PBCS_DTID dtid, Data* data) {
        outputPacketData(dtid, data, pkttypeName, pkttypeName, upperCase, prefix, stream);
    });

    stream << Qt::endl;
}

void outputDefine(
    Config::Iterator& iterator, 
    bool upperCase,
    const QString& prefix, 
    QTextStream& stream,
    const QString& parentsName) {
        
    for (PacketType* nowType = iterator.now();nowType != nullptr;nowType = iterator.now()) {
        QString pkttypeName = parentsName;
        pkttypeName.append("_");
        if (!upperCase) 
            pkttypeName.append(nowType->getName().c_str());
        else 
            pkttypeName.append(QString::fromStdString(nowType->getName()).toUpper());
        
        stream << "#define " << prefix << "PTID" << pkttypeName << " " << nowType->getID() << Qt::endl;
        nowType->iterate([&](Packet* packet) {
            outputPacketDefine(packet, pkttypeName, upperCase, prefix, stream);
        });

        stream << Qt::endl;
        iterator.nextLayer();
        outputDefine(iterator,upperCase,prefix,stream,pkttypeName);
        iterator.prevLayer();
        iterator.step();
    }
}

void outputDefine(
    Config* config,
    bool upperCase,
    const std::string& varName,
    const std::string& namespaceName,
    const QString& prefix,
    QTextStream& stream
    ) {

    if (config->isNonTMod()) {
        stream << "#define " << prefix << "PTID_DEFAULT 0" << Qt::endl << Qt::endl;
        Config::Iterator(config).now()->iterate([&stream,upperCase,prefix](Packet* packet) {
            QString pktNameCStr;
            if (!upperCase) pktNameCStr = packet->getName().c_str();
            else pktNameCStr = QString::fromStdString(packet->getName()).toUpper();
            stream << "#define " << prefix << "PID_" << pktNameCStr << " " << packet->getID() << Qt::endl;
            packet->iterate([&stream,&pktNameCStr,upperCase,prefix](PBCS_DTID dtid,Data* data) {
                const char* dtNameCStr;
                if (!upperCase) dtNameCStr = data->getName().c_str();
                else dtNameCStr = QString::fromStdString(data->getName()).toUpper().toStdString().c_str();
                stream << "#define " << prefix << "DTID_"
                << pktNameCStr
                << "_"
                << dtNameCStr
                << " "
                << dtid
                << Qt::endl;
            });
            stream << Qt::endl;
        });
    }else {
        Config::Iterator iterator = Config::Iterator(config);
        outputDefine(iterator,upperCase,prefix,stream,QString(""));
    }

    if (namespaceName.empty()) {
        stream << "extern const struct PBCS_config " << varName.c_str() << ";" << Qt::endl;
    }else {
        stream << "namespace " << namespaceName.c_str() << " {" << Qt::endl;
        stream << TAB.c_str();
        stream << "extern const struct PBCS_config " << varName.c_str() << ";" << Qt::endl;
        stream << "}" << Qt::endl;
    }
    stream << Qt::endl;

}

// 包排序比较器：先按PacketType ID排序，再按Packet ID排序
// 用于确保生成的配置数据顺序一致
bool compPacket(const Packet* packet1,const Packet* packet2) {
    //return packet1 < packet2
    PBCS_PTID ptid1 = packet1->getBelongsToConst()->getID(),ptid2 = packet2->getBelongsToConst()->getID();
    if (ptid1 == ptid2) {
        return packet1->getID() < packet2->getID();
    }
    return ptid1 < ptid2;
}

// 检查一个值是否能用指定字节数存储
// 例如：satisfy(300, 1) = false (300超出了1字节能存储的范围0-255)
//       satisfy(255, 1) = false (边界值也不满足，需要 < 255)
bool satisfy(unsigned long long val,int bytes) {
    return val < ((1 << (bytes * 8)) - 1);
}

/** 
* 递归遍历配置树，计算动态的字节长度
* @param ptidLen: 
* @param pidLen: Packet ID需要的字节数
* @param dtidLen: Data ID需要的字节数
* @param parents: 记录每个包类型的父类
* @param packetNums: 记录每个包类型包含的包数量 
*/
void infoIterate(
    Config::Iterator& iterator,
    int& ptidLen,      // 动态计算所需字节数
    int& pidLen,
    int& dtidLen,
    PBCS_PID& totalPkt,
    std::map<PBCS_PTID,PBCS_PTID>& parents,
    std::map<PBCS_PTID,PBCS_PID>& packetNums
    ) {
    for (PacketType* nowType = iterator.now();nowType != nullptr;nowType = iterator.now()) {
        totalPkt += nowType->getPacketNum();  // 累计包数量
        
        // 记录父子关系
        parents.insert(std::pair<PBCS_PTID,PBCS_PTID>(nowType->getID(),nowType->getParent()->getID()));
        
        if (nowType->getPacketNum() > 0) {
            // 记录各包类型的包数量
            packetNums.insert(std::pair<PBCS_PTID,PBCS_PID>(nowType->getID(),nowType->getPacketNum()));
        }
        
        // 动态调整ptidLen：确保能存储该包类型的ID
        while (!satisfy(nowType->getID(),ptidLen)) ptidLen++;
        
        // 遍历该包类型下的所有包
        nowType->iterate([&](Packet* packet) {
            while (!satisfy(packet->getID(),pidLen)) pidLen++;                    // 调整pidLen
            while (!satisfy(packet->getDataNum(),dtidLen)) dtidLen++;            // 调整dtidLen
        });
        
        // 递归遍历子层级
        iterator.nextLayer();
        infoIterate(iterator,ptidLen,pidLen,dtidLen,totalPkt,parents,packetNums);
        iterator.prevLayer();
        iterator.step();  // 移到下一个同级类型
    }
}

// 将整数以小端序写入字节流（多字节）
// 例如：val=0x12345678, bytes=4 -> 输出 "0x78, 0x56, 0x34, 0x12"
void bytesWriteToStream(unsigned long long val,int bytes,QTextStream& stream) {
    char buffer[5];
    for (int i = 0;i < bytes;i++) {
        if (i != 0) stream << ", ";
        unsigned char byte = val & 0xFF;              // 取最低8位
        snprintf(buffer, sizeof(buffer), "0x%02X", byte);
        stream << buffer;
        val >>= 8;                                    // 右移8位，取下一字节
    }
}

// 将数据类型编码为4位值（用于位打包）
// 两个类型可以打包到一个字节：低4位一个，高4位一个
unsigned char getTypeMarkByte(DataType type) {
    switch (type) {
        default:
        case DataType::UINT8:     return 0;   // 00: 无符号8位
        case DataType::UINT16:    return 1;   // 01: 无符号16位
        case DataType::UINT32:    return 2;   // 02: 无符号32位
        case DataType::INT8:      return 3;   // 03: 有符号8位
        case DataType::INT16:     return 4;   // 04: 有符号16位
        case DataType::INT32:     return 5;   // 05: 有符号32位
        case DataType::FLOAT32:   return 6;   // 06: 浮点32位
        case DataType::VARIABLE:  return 7;   // 07: 可变长
        case DataType::UINT64:    return 8;   // 08: 无符号64位
        case DataType::INT64:     return 9;   // 09: 有符号64位
        case DataType::FLOAT64:   return 10;  // 0A: 浮点64位
    }
}

// 递归写入包配置数据到字节数组
// 格式: [PacketTypeID], PacketID, DataNum, [DataType编码...]
// [...]表示仅在非NonTMod模式下输出
void writePackets(
    Config::Iterator& iterator,
    QTextStream& stream,
    int ptidLen,                                           // PacketType ID占用字节数
    int pidLen,                                            // Packet ID占用字节数
    int dtidLen,                                           // Data数量占用字节数
    int& cfgIndexLen,                                      // 配置数据索引占用字节数（会动态调整）
    bool& first,                                           // 是否第一个元素
    size_t& cfgIndex,                                      // 当前配置数据偏移
    std::map<Packet*,size_t,decltype(&compPacket)>& packetIndexes  // 记录每个包的配置起始位置
    ) {
    for (PacketType* nowType = iterator.now();nowType != nullptr;nowType = iterator.now()) {
        // 遍历该类型下的所有包
        nowType->iterate([&](Packet* packet) {
            // 确保cfgIndexLen能存储当前configIndex
            while (!satisfy(cfgIndex,cfgIndexLen)) cfgIndexLen++;
            
            // 记录该包在配置数据中的起始位置
            packetIndexes.insert(std::pair<Packet*,size_t>(packet,cfgIndex));
            
            // 输出格式控制（不是第一个则先输出逗号换行）
            if (first) first = false;
            else stream << "," << Qt::endl;
            stream << TAB.c_str();
            
            // 写入PacketType ID（仅在有多个类型时）
            if (ptidLen != 0) {
                bytesWriteToStream(packet->getBelongsTo()->getID(),ptidLen,stream);
                stream << ", ";
            }
            
            // 写入Packet ID
            bytesWriteToStream(packet->getID(),pidLen,stream);
            stream << ", ";
            
            // 写入数据字段数量
            bytesWriteToStream(packet->getDataNum(),dtidLen,stream);
            if (packet->getDataNum() != 0) stream << ", ";
            
            // 更新当前配置数据位置
            cfgIndex += ptidLen + pidLen + dtidLen;
            
            // 数据类型打包：两个类型打到一个字节（低4位+高4位）
            bool lowFilled = false,highFilled = false;      // 低4位和高4位是否已填充
            unsigned char typeByte = 0;
            
            packet->iterate([&](PBCS_DTID,Data* data) {
                // 如果两位都满了，输出该字节并重置
                if (lowFilled && highFilled) {
                    lowFilled = highFilled = false;
                    bytesWriteToStream(typeByte,1,stream);
                    stream << ", ";
                    typeByte = 0;
                    cfgIndex++;  // 占用一个字节
                }
                
                if (!lowFilled) {
                    // 填充低4位
                    typeByte = getTypeMarkByte(data->getDataType());
                    lowFilled = true;
                }else {
                    // 填充高4位
                    typeByte += getTypeMarkByte(data->getDataType()) << 4;
                    highFilled = true;
                }
            });
            
            // 如果还有未输出的低4位，输出最后一个字节
            if (lowFilled) {
                bytesWriteToStream(typeByte,1,stream);
                cfgIndex++;
            }
        });
        
        // 递归处理子层级
        iterator.nextLayer();
        writePackets(iterator,stream,ptidLen,pidLen,dtidLen,cfgIndexLen,first,cfgIndex,packetIndexes);
        iterator.prevLayer();
        iterator.step();  // 移到下一个同级类型
    }
}

void outputC(
    Config* config,
    const std::string& varName,
    const std::string& namespaceName,
    QTextStream& stream,
    int ptidLen,
    int pidLen,
    int dtidLen,
    int cfgIndexLen,
    int vdlLen
    ) {

    std::map<PBCS_PTID,PBCS_PTID> parents;
    std::map<PBCS_PTID,PBCS_PID> packetNums;
    std::map<Packet*,size_t,decltype(&compPacket)> packetIndexes(compPacket);

    int ptidLen2 = 0,pidLen2 = 0,dtidLen2 = 0;
    PBCS_PID totalPkt = 0;
    Config::Iterator iterator1 = Config::Iterator(config);
    infoIterate(iterator1,ptidLen2,pidLen2,dtidLen2,totalPkt,parents,packetNums);
    if (ptidLen < 0 || ptidLen2 > ptidLen) ptidLen = ptidLen2;
    if (pidLen < 0 || pidLen2 > pidLen) pidLen = pidLen2;
    if (dtidLen < 0 || dtidLen2 > dtidLen) dtidLen = dtidLen2;
    if (cfgIndexLen < 0) cfgIndexLen = 0;

    stream << "#include \"PBCSConfig.h\"" << Qt::endl << Qt::endl;
    if (!config->isNonTMod()) {
        stream << "static const PBCS_U1 data_belonging[] = {" << Qt::endl;
        bool first = true;
        for (const auto& pair : parents) {
            if (first) first = false;
            else stream << "," << Qt::endl;
            stream << TAB.c_str();
            bytesWriteToStream(pair.first,ptidLen,stream);
            stream << ", ";
            bytesWriteToStream(pair.second,ptidLen,stream);
        }
        stream << Qt::endl << "};" << Qt::endl << Qt::endl;
        stream << "static const PBCS_U1 data_packetNums[] = {" << Qt::endl;
        first = true;
        for (const auto& pair : packetNums) {
            if (first) first = false;
            else stream << "," << Qt::endl;
            stream << TAB.c_str();
            bytesWriteToStream(pair.first,ptidLen,stream);
            stream << ", ";
            bytesWriteToStream(pair.second,pidLen,stream);
        }
        stream << Qt::endl << "};" << Qt::endl << Qt::endl;
    }
    stream << "static const PBCS_U1 data_packets[] = {" << Qt::endl;
    Config::Iterator iterator2 = Config::Iterator(config);
    bool first = true;
    size_t cfgIndex = 0;
    if (config->isNonTMod())
        writePackets(iterator2,stream,0,pidLen,dtidLen,cfgIndexLen,first,cfgIndex,packetIndexes);
    else
        writePackets(iterator2,stream,ptidLen,pidLen,dtidLen,cfgIndexLen,first,cfgIndex,packetIndexes);
    stream << Qt::endl << "};" << Qt::endl << Qt::endl;
    stream << "static const PBCS_U1 data_packetsIndexes[] = {" << Qt::endl;
    first = true;
    for (const auto& pair : packetIndexes) {
        if (first) first = false;
        else stream << "," << Qt::endl;
        stream << TAB.c_str();
        if (!config->isNonTMod()) {
            bytesWriteToStream(pair.first->getBelongsTo()->getID(),ptidLen,stream);
            stream << ", ";
        }
        bytesWriteToStream(pair.first->getID(),pidLen,stream);
        stream << ", ";
        bytesWriteToStream(pair.second,cfgIndexLen,stream);
    }
    stream << Qt::endl << "};" << Qt::endl << Qt::endl;

    QString tab = "";
    if (!namespaceName.empty()) {
        tab.append(TAB.c_str());
        stream << "namespace " << namespaceName.c_str() << " {" << Qt::endl;
    }
    stream << tab << "const struct PBCS_config " << varName.c_str() << " = {" << Qt::endl;
    if (config->isNonTMod()) {
        stream << tab << TAB.c_str() << "0," << Qt::endl;
        stream << tab << TAB.c_str() << "0," << Qt::endl;
    }else {
        stream << tab << TAB.c_str() << "data_belonging," << Qt::endl;
        stream << tab << TAB.c_str() << "data_packetNums," << Qt::endl;
    }
    stream << tab << TAB.c_str() << "data_packets," << Qt::endl;
    stream << tab << TAB.c_str() << "data_packetsIndexes," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(config->getTypesNum()) << "," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(packetNums.size()) << "," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(packetIndexes.size()) << "," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(ptidLen) << "," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(pidLen) << "," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(vdlLen) << "," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(dtidLen) << "," << Qt::endl;
    stream << tab << TAB.c_str() << QString::number(cfgIndexLen) << "," << Qt::endl;
    stream << tab << "};" << Qt::endl;
    if (!namespaceName.empty()) {
        stream << "}" << Qt::endl;
    }

}

int main(int argc, char *argv[]) {
// int main(){
//
//     int argc = 7;
//     const char* argv[] = {
//         "gen","config.pbcs","output.h","output.c","config","__OUTPUT_H","1"
//     };

    QRegExp varNameExp("[a-zA-Z_][a-zA-Z0-9_]*");
    QRegExp numberExp("[0-9]*");
    std::string onceDefine;
    QString prefix;
    int vdlLen = 0;
    if (argc > 5) onceDefine = argv[5];
    if (argc < 7) {
        std::cout << "Usage: " << GEN_EXECNAME << " <filename> <Houtput> <Coutput> <configVarName> <onceDefine> <vdlLen> [-options]" << std::endl;
        std::cout << R"(    "*once" for <onceDefine> means using "#pragma once".)" << std::endl;
        std::cout << "    -namespace <namespace>   assign a namespace for config var" << std::endl;
        std::cout << "    -prefix <prefix>         add prefix to all define" << std::endl;
        std::cout << "    -ptidLen <len>" << std::endl;
        std::cout << "    -pidLen <len>" << std::endl;
        std::cout << "    -dtidLen <len>" << std::endl;
        std::cout << "    -cfgIndexLen <len>" << std::endl;
        std::cout << "    -upperCase               convert all names to all capital letters" << std::endl;
        return 0;
    }
    if (!varNameExp.exactMatch(argv[4])) {
        std::cerr << "\"" << argv[4] << "\" is not a vaild name for var name." << std::endl;
        return -1;
    }
    if (!varNameExp.exactMatch(argv[5]) && onceDefine != "*once") {
        std::cerr << "\"" << argv[5] << "\" is not a vaild name for macro define." << std::endl;
        return -1;
    }
    if (!numberExp.exactMatch(argv[6]) || ((vdlLen = QString(argv[6]).toInt()) < 1)) {
        std::cerr << "\"" << argv[6] << "\" is not a vaild number." << std::endl;
        return -1;
    }

    std::string namespaceName;
    bool upperCase = false;
    int ptidLen = -1, pidLen = -1, dtidLen = -1, cfgIndexLen = -1;

    for (int i = 7; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-namespace") {
            if (i == argc - 1) {
                std::cerr << "Wrong usage for -namespace!" << std::endl;
                return -1;
            }
            if (!varNameExp.exactMatch(argv[i + 1])) {
                std::cerr << "\"" << argv[i + 1] << "\" is not a vaild name for namespace." << std::endl;
                return -1;
            }
            namespaceName = argv[i + 1];
            i++;
        }else if (arg == "-ptidLen" || arg == "-pidLen" || arg == "-dtidLen" || arg == "-cfgIndexLen") {
            if (i == argc - 1) {
                std::cerr << "Wrong usage for " << arg << "!"  << std::endl;
                return -1;
            }
            if (!numberExp.exactMatch(argv[i + 1])) {
                std::cerr << "\"" << argv[i + 1] << "\" is not a number." << std::endl;
                return -1;
            }
            if (arg == "-ptidLen") ptidLen = QString(argv[i + 1]).toInt();
            else if (arg == "-pidLen") pidLen = QString(argv[i + 1]).toInt();
            else if (arg == "-dtidLen") dtidLen = QString(argv[i + 1]).toInt();
            else cfgIndexLen = QString(argv[i + 1]).toInt();
            i++;
        }else if (arg == "-prefix") {
            if (i == argc - 1) {
                std::cerr << "Wrong usage for -prefix!" << std::endl;
                return -1;
            }
            if (!varNameExp.exactMatch(argv[i + 1])) {
                std::cerr << "\"" << argv[i + 1] << "\" is not a vaild name for namespace." << std::endl;
                return -1;
            }
            prefix.append(argv[i + 1]).append("_");
            i++;
        }else if (arg == "-upperCase") {
            upperCase = true;
        }else {
            std::cerr << "Unknown option " << argv[i + 1] << "!" << std::endl;
            return -1;
        }
    }

    Config* config = loadConfigFile(argv[1]);
    if (config == nullptr) {
        std::cerr << "Error loading config file: " << argv[1] << std::endl;
        return 1;
    }

    QFile Hfile(argv[2]);
    if (!Hfile.open(QFileDevice::WriteOnly | QFileDevice::Truncate)) {
        std::cerr << "Error opening output file: " << argv[2] << std::endl;
        return -1;
    }
    QTextStream Hstream(&Hfile);

    QFile Cfile(argv[3]);
    if (!Cfile.open(QFileDevice::WriteOnly | QFileDevice::Truncate)) {
        std::cerr << "Error opening output file: " << argv[3] << std::endl;
        return -1;
    }
    QTextStream Cstream(&Cfile);

    outputStart(argv[5],Hstream);
    outputDefine(config,upperCase,argv[4],namespaceName,prefix,Hstream);
    outputEnd(argv[5],Hstream);

    outputC(config,argv[4],namespaceName,Cstream,ptidLen,pidLen,dtidLen,cfgIndexLen,vdlLen);

    Hfile.close();
    Cfile.close();

    return 0;

}