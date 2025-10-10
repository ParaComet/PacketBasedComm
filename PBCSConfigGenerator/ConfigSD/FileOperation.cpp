//
// Created by QingG on 2025/9/15.
//

#include "configElem/Config.h"
#include "configElem/PacketType.h"
#include "configElem/Packet.h"
#include "configElem/Data.h"
#include <string>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtXml/QDomDocument>

namespace PBCS {

    int addByNode(Config* config,const QDomElement& element,PacketType* parent) {

        QDomNodeList pkttypeNodes = element.childNodes();

        for (int i=0;i<pkttypeNodes.length();i++) {

            QDomNode node = pkttypeNodes.at(i);
            if (!node.isElement() || node.nodeName() != "pkttype") continue;

            QDomElement childElement = node.toElement();
            if (!childElement.hasAttribute("name") ||
                !childElement.hasAttribute("id")) return -1;
            QString name = childElement.attribute("name");
            PBCS_PTID id = childElement.attribute("id").toULongLong();
            PacketType* type = new PacketType(id,name.toStdString(),config,parent);
            config->addPacketType(type);

            QDomNodeList packetNodes = childElement.childNodes();
            bool ok = false;
            for (int j = 0;j < packetNodes.size();j++) {

                QDomNode packetNode = packetNodes.at(j);
                if (!packetNode.isElement() || packetNode.nodeName() != "packet") continue;

                QDomElement packetElem = packetNode.toElement();
                if (!packetElem.hasAttribute("name") ||
                    !packetElem.hasAttribute("id")) return -1;
                PBCS_PID packetID = packetElem.attribute("id").toULongLong(&ok);
                if (!ok) return -1;
                QString packetName = packetElem.attribute("name");
                Packet* packet = new Packet(packetID,packetName.toStdString(),type);
                type->addPacket(packet);

                QDomNodeList dataNodes = packetElem.childNodes();
                for (int k = 0;k < dataNodes.size();k++) {

                    QDomNode dataNode = dataNodes.at(k);
                    if (!dataNode.isElement() || dataNode.nodeName() != "data") continue;

                    QDomElement dataElem = dataNode.toElement();
                    if (!dataElem.hasAttribute("name") ||
                        !dataElem.hasAttribute("type")) return -1;
                    uint8_t typeByte = dataElem.attribute("type").toUShort(&ok);
                    if (!ok) return -1;
                    QString dataName = dataElem.attribute("name");
                    Data* data = nullptr;
                    switch (typeByte) {
                        case 0x00:
                            data = new Data(DataType::UINT8,dataName.toStdString());
                            break;
                        case 0x01:
                            data = new Data(DataType::UINT16,dataName.toStdString());
                            break;
                        case 0x02:
                            data = new Data(DataType::UINT32,dataName.toStdString());
                            break;
                        case 0x03:
                            data = new Data(DataType::INT8,dataName.toStdString());
                            break;
                        case 0x04:
                            data = new Data(DataType::INT16,dataName.toStdString());
                            break;
                        case 0x05:
                            data = new Data(DataType::INT32,dataName.toStdString());
                            break;
                        case 0x06:
                            data = new Data(DataType::FLOAT32,dataName.toStdString());
                            break;
                        case 0x07:
                            data = new Data(DataType::VARIABLE,dataName.toStdString());
                            break;
                        case 0x08:
                            data = new Data(DataType::UINT64,dataName.toStdString());
                            break;
                        case 0x09:
                            data = new Data(DataType::INT64,dataName.toStdString());
                            break;
                        case 0x0A:
                            data = new Data(DataType::FLOAT64,dataName.toStdString());
                            break;
                        default:
                            return -1;
                    }
                    packet->addData(data);

                }

            }

            if (addByNode(config,childElement,type) != 0) {
                return -1;
            }

        }

        return 0;

    }

    void addToXML(Config* config,QDomDocument& doc,QDomElement& parentEle,Config::Iterator& iterator) {

        PacketType* type;
        while ((type = iterator.now()) != nullptr) {

            QDomElement childEle = doc.createElement("pkttype");
            childEle.setAttribute("name",type->getName().c_str());
            childEle.setAttribute("id",type->getID());

            type->iterate(
                [&doc,&childEle](Packet* packet) -> void{

                    QDomElement packetEle = doc.createElement("packet");
                    packetEle.setAttribute("name",packet->getName().c_str());
                    packetEle.setAttribute("id",packet->getID());

                    packet->iterate(
                        [&doc,&packetEle](PBCS_DTID,Data* data) -> void {
                            QDomElement dataEle = doc.createElement("data");
                            dataEle.setAttribute("name",data->getName().c_str());
                            switch (data->getDataType()) {
                                default:
                                case DataType::UINT8:
                                    dataEle.setAttribute("type",0x00);
                                    break;
                                case DataType::UINT16:
                                    dataEle.setAttribute("type",0x01);
                                    break;
                                case DataType::UINT32:
                                    dataEle.setAttribute("type",0x02);
                                    break;
                                case DataType::INT8:
                                    dataEle.setAttribute("type",0x03);
                                    break;
                                case DataType::INT16:
                                    dataEle.setAttribute("type",0x04);
                                    break;
                                case DataType::INT32:
                                    dataEle.setAttribute("type",0x05);
                                    break;
                                case DataType::FLOAT32:
                                    dataEle.setAttribute("type",0x06);
                                    break;
                                case DataType::VARIABLE:
                                    dataEle.setAttribute("type",0x07);
                                    break;
                                case DataType::UINT64:
                                    dataEle.setAttribute("type",0x08);
                                    break;
                                case DataType::INT64:
                                    dataEle.setAttribute("type",0x09);
                                    break;
                                case DataType::FLOAT64:
                                    dataEle.setAttribute("type",0x0A);
                                    break;
                            }
                            packetEle.appendChild(dataEle);
                        }
                    );

                    childEle.appendChild(packetEle);

                }
            );

            iterator.nextLayer();
            addToXML(config,doc,childEle,iterator);
            iterator.prevLayer();
            iterator.step();

            parentEle.appendChild(childEle);

        }

    }

    Config* loadConfigFile(const std::string& filePath) {
        QDomDocument doc;
        QFile file(filePath.data());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text) || !doc.setContent(&file)) {
            return nullptr;
        }
        QDomNodeList qnl = doc.childNodes();
        for (int i = 0;i < qnl.size();i++) {
            QDomNode configNode = qnl.at(i);
            if (configNode.isElement() && configNode.nodeName() == "config") {
                QDomElement configElem = configNode.toElement();
                Config* config;
                if (configElem.elementsByTagName("nonTMod").size() > 0) config = new Config(true);
                else config = new Config(false);
                if (addByNode(config,configElem,nullptr) != 0) {
                    delete config;
                    return nullptr;
                }
                return config;
            }
        }
        return nullptr;
    }

    int saveConfigFile(Config* config,const std::string& filePath,const std::string& encoding) {

        QDomDocument doc;

        QString instStr(R"(version="1.0" encoding=")");
        instStr.append(encoding.c_str());
        instStr.append("\"");
        QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", instStr);
        doc.appendChild(instruction);

        Config::Iterator iterator = config->iterator();
        QDomElement configEle = doc.createElement("config");
        if (config->isNonTMod()) {
            QDomElement nonTEle = doc.createElement("nonTMod");
            configEle.appendChild(nonTEle);
        }
        addToXML(config,doc,configEle,iterator);
        doc.appendChild(configEle);

        QFile file(filePath.data());
        if (!file.open(QFileDevice::WriteOnly | QFileDevice::Truncate)) {
            return -1;
        }
        QTextStream stream(&file);
        doc.save(stream,4);
        file.close();

        return 0;

    }

}
