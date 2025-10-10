//
// Created by QingG on 2025/9/27.
//

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

using namespace PBCS;

std::string TAB = "    ";

void outputStart(const std::string& onceDefine,QTextStream& stream) {
    if (onceDefine == "*once") {
        stream << "#pragma once" << endl;
    }else {
        stream << "#ifndef " << onceDefine.c_str() << endl;
        stream << "#define " << onceDefine.c_str() << endl;
    }
    stream << endl;
    stream << "#include \"PBCSConfig.h\"" << endl << endl;
}

void outputEnd(const std::string& onceDefine,QTextStream& stream) {
    if (onceDefine != "*once") {
        stream << "#endif" << endl;
    }
}

void outputDefine(Config::Iterator& iterator,bool upperCase,const QString& prefix,QTextStream& stream,const QString& parentsName) {
    for (PacketType* nowType = iterator.now();nowType != nullptr;nowType = iterator.now()) {
        QString pkttypeName = parentsName;
        pkttypeName.append("_");
        if (!upperCase) pkttypeName.append(nowType->getName().c_str());
        else pkttypeName.append(QString::fromStdString(nowType->getName()).toUpper());
        stream << "#define " << prefix << "PTID" << pkttypeName << " " << nowType->getID() << endl;
        nowType->iterate([&stream,pkttypeName,upperCase,prefix](Packet* packet) {
            QString pktNameCStr;
            if (!upperCase) pktNameCStr = packet->getName().c_str();
            else pktNameCStr = QString::fromStdString(packet->getName()).toUpper();
            stream << "#define " << prefix << "PID" << pkttypeName << "_" << pktNameCStr << " " << packet->getID() << endl;
            packet->iterate([&stream,&pktNameCStr,pkttypeName,upperCase,prefix](PBCS_DTID dtid,Data* data) {
                const char* dtNameCStr;
                if (!upperCase) dtNameCStr = data->getName().c_str();
                else dtNameCStr = QString::fromStdString(data->getName()).toUpper().toStdString().c_str();
                stream << "#define " << prefix << "DTID"
                << pkttypeName
                << "_"
                << pktNameCStr
                << "_"
                << dtNameCStr
                << " "
                << dtid
                << endl;
            });
            stream << endl;
        });
        stream << endl;
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
        stream << "#define " << prefix << "PTID_DEFAULT 0" << endl << endl;
        config->iterator().now()->iterate([&stream,upperCase,prefix](Packet* packet) {
            QString pktNameCStr;
            if (!upperCase) pktNameCStr = packet->getName().c_str();
            else pktNameCStr = QString::fromStdString(packet->getName()).toUpper();
            stream << "#define " << prefix << "PID_" << pktNameCStr << " " << packet->getID() << endl;
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
                << endl;
            });
            stream << endl;
        });
    }else {
        Config::Iterator iterator = config->iterator();
        outputDefine(iterator,upperCase,prefix,stream,QString(""));
    }

    if (namespaceName.empty()) {
        stream << "extern const struct PBCS_config " << varName.c_str() << ";" << endl;
    }else {
        stream << "namespace " << namespaceName.c_str() << " {" << endl;
        stream << TAB.c_str();
        stream << "extern const struct PBCS_config " << varName.c_str() << ";" << endl;
        stream << "}" << endl;
    }
    stream << endl;

}

bool compPacket(const Packet* packet1,const Packet* packet2) {
    //return packet1 < packet2
    PBCS_PTID ptid1 = packet1->getBelongsToConst()->getID(),ptid2 = packet2->getBelongsToConst()->getID();
    if (ptid1 == ptid2) {
        return packet1->getID() < packet2->getID();
    }
    return ptid1 < ptid2;
}

bool satisfy(unsigned long long val,int bytes) {
    return val < ((1 << (bytes * 8)) - 1);
}

void infoIterate(
    Config::Iterator& iterator,
    int& ptidLen,
    int& pidLen,
    int& dtidLen,
    PBCS_PID& totalPkt,
    std::map<PBCS_PTID,PBCS_PTID>& parents,
    std::map<PBCS_PTID,PBCS_PID>& packetNums
    ) {
    for (PacketType* nowType = iterator.now();nowType != nullptr;nowType = iterator.now()) {
        totalPkt += nowType->getPacketNum();
        parents.insert(std::pair<PBCS_PTID,PBCS_PTID>(nowType->getID(),nowType->getParent()->getID()));
        if (nowType->getPacketNum() > 0) {
            packetNums.insert(std::pair<PBCS_PTID,PBCS_PID>(nowType->getID(),nowType->getPacketNum()));
        }
        while (!satisfy(nowType->getID(),ptidLen)) ptidLen++;
        nowType->iterate([&](Packet* packet) {
            while (!satisfy(packet->getID(),pidLen)) pidLen++;
            while (!satisfy(packet->getDataNum(),dtidLen)) dtidLen++;
        });
        iterator.nextLayer();
        infoIterate(iterator,ptidLen,pidLen,dtidLen,totalPkt,parents,packetNums);
        iterator.prevLayer();
        iterator.step();
    }
}

void bytesWriteToStream(unsigned long long val,int bytes,QTextStream& stream) {
    char buffer[5];
    for (int i = 0;i < bytes;i++) {
        if (i != 0) stream << ", ";
        unsigned char byte = val & 0xFF;
        snprintf(buffer, sizeof(buffer), "0x%02X", byte);
        stream << buffer;
        val >>= 8;
    }
}

unsigned char getTypeMarkByte(DataType type) {
    switch (type) {
        default:
        case DataType::UINT8: return 0;
        case DataType::UINT16: return 1;
        case DataType::UINT32: return 2;
        case DataType::INT8: return 3;
        case DataType::INT16: return 4;
        case DataType::INT32: return 5;
        case DataType::FLOAT32: return 6;
        case DataType::VARIABLE: return 7;
        case DataType::UINT64: return 8;
        case DataType::INT64: return 9;
        case DataType::FLOAT64: return 10;
    }
}

void writePackets(
    Config::Iterator& iterator,
    QTextStream& stream,
    int ptidLen,
    int pidLen,
    int dtidLen,
    int& cfgIndexLen,
    bool& first,
    size_t& cfgIndex,
    std::map<Packet*,size_t,decltype(&compPacket)>& packetIndexes
    ) {
    for (PacketType* nowType = iterator.now();nowType != nullptr;nowType = iterator.now()) {
        nowType->iterate([&](Packet* packet) {
            while (!satisfy(cfgIndex,cfgIndexLen)) cfgIndexLen++;
            packetIndexes.insert(std::pair<Packet*,size_t>(packet,cfgIndex));
            if (first) first = false;
            else stream << "," << endl;
            stream << TAB.c_str();
            if (ptidLen != 0) {
                bytesWriteToStream(packet->getBelongsTo()->getID(),ptidLen,stream);
                stream << ", ";
            }
            bytesWriteToStream(packet->getID(),pidLen,stream);
            stream << ", ";
            bytesWriteToStream(packet->getDataNum(),dtidLen,stream);
            if (packet->getDataNum() != 0) stream << ", ";
            cfgIndex += ptidLen + pidLen + dtidLen;
            bool lowFilled = false,highFilled = false;
            unsigned char typeByte = 0;
            packet->iterate([&](PBCS_DTID,Data* data) {
                if (lowFilled && highFilled) {
                    lowFilled = highFilled = false;
                    bytesWriteToStream(typeByte,1,stream);
                    stream << ", ";
                    typeByte = 0;
                    cfgIndex++;
                }
                if (!lowFilled) {
                    typeByte = getTypeMarkByte(data->getDataType());
                    lowFilled = true;
                }else {
                    typeByte += getTypeMarkByte(data->getDataType()) << 4;
                    highFilled = true;
                }
            });
            if (lowFilled) {
                bytesWriteToStream(typeByte,1,stream);
                cfgIndex++;
            }
        });
        iterator.nextLayer();
        writePackets(iterator,stream,ptidLen,pidLen,dtidLen,cfgIndexLen,first,cfgIndex,packetIndexes);
        iterator.prevLayer();
        iterator.step();
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
    Config::Iterator iterator1 = config->iterator();
    infoIterate(iterator1,ptidLen2,pidLen2,dtidLen2,totalPkt,parents,packetNums);
    if (ptidLen < 0 || ptidLen2 > ptidLen) ptidLen = ptidLen2;
    if (pidLen < 0 || pidLen2 > pidLen) pidLen = pidLen2;
    if (dtidLen < 0 || dtidLen2 > dtidLen) dtidLen = dtidLen2;
    if (cfgIndexLen < 0) cfgIndexLen = 0;

    stream << "#include \"PBCSConfig.h\"" << endl << endl;
    if (!config->isNonTMod()) {
        stream << "static const PBCS_U1 data_belonging[] = {" << endl;
        bool first = true;
        for (const auto& pair : parents) {
            if (first) first = false;
            else stream << "," << endl;
            stream << TAB.c_str();
            bytesWriteToStream(pair.first,ptidLen,stream);
            stream << ", ";
            bytesWriteToStream(pair.second,ptidLen,stream);
        }
        stream << endl << "};" << endl << endl;
        stream << "static const PBCS_U1 data_packetNums[] = {" << endl;
        first = true;
        for (const auto& pair : packetNums) {
            if (first) first = false;
            else stream << "," << endl;
            stream << TAB.c_str();
            bytesWriteToStream(pair.first,ptidLen,stream);
            stream << ", ";
            bytesWriteToStream(pair.second,pidLen,stream);
        }
        stream << endl << "};" << endl << endl;
    }
    stream << "static const PBCS_U1 data_packets[] = {" << endl;
    Config::Iterator iterator2 = config->iterator();
    bool first = true;
    size_t cfgIndex = 0;
    if (config->isNonTMod())
        writePackets(iterator2,stream,0,pidLen,dtidLen,cfgIndexLen,first,cfgIndex,packetIndexes);
    else
        writePackets(iterator2,stream,ptidLen,pidLen,dtidLen,cfgIndexLen,first,cfgIndex,packetIndexes);
    stream << endl << "};" << endl << endl;
    stream << "static const PBCS_U1 data_packetsIndexes[] = {" << endl;
    first = true;
    for (const auto& pair : packetIndexes) {
        if (first) first = false;
        else stream << "," << endl;
        stream << TAB.c_str();
        if (!config->isNonTMod()) {
            bytesWriteToStream(pair.first->getBelongsTo()->getID(),ptidLen,stream);
            stream << ", ";
        }
        bytesWriteToStream(pair.first->getID(),pidLen,stream);
        stream << ", ";
        bytesWriteToStream(pair.second,cfgIndexLen,stream);
    }
    stream << endl << "};" << endl << endl;

    QString tab = "";
    if (!namespaceName.empty()) {
        tab.append(TAB.c_str());
        stream << "namespace " << namespaceName.c_str() << " {" << endl;
    }
    stream << tab << "const struct PBCS_config " << varName.c_str() << " = {" << endl;
    if (config->isNonTMod()) {
        stream << tab << TAB.c_str() << "0," << endl;
        stream << tab << TAB.c_str() << "0," << endl;
    }else {
        stream << tab << TAB.c_str() << "data_belonging," << endl;
        stream << tab << TAB.c_str() << "data_packetNums," << endl;
    }
    stream << tab << TAB.c_str() << "data_packets," << endl;
    stream << tab << TAB.c_str() << "data_packetsIndexes," << endl;
    stream << tab << TAB.c_str() << QString::number(config->getTypesNum()) << "," << endl;
    stream << tab << TAB.c_str() << QString::number(packetNums.size()) << "," << endl;
    stream << tab << TAB.c_str() << QString::number(packetIndexes.size()) << "," << endl;
    stream << tab << TAB.c_str() << QString::number(ptidLen) << "," << endl;
    stream << tab << TAB.c_str() << QString::number(pidLen) << "," << endl;
    stream << tab << TAB.c_str() << QString::number(vdlLen) << "," << endl;
    stream << tab << TAB.c_str() << QString::number(dtidLen) << "," << endl;
    stream << tab << TAB.c_str() << QString::number(cfgIndexLen) << "," << endl;
    stream << tab << "};" << endl;
    if (!namespaceName.empty()) {
        stream << "}" << endl;
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