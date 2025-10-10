//
// Created by QingG on 2025/9/13.
//

#ifndef PBCSCONFIGGENERATOR_PBCSPACKETTYPE_H
#define PBCSCONFIGGENERATOR_PBCSPACKETTYPE_H

#include <unordered_map>
#include <string>
#include <functional>
#include "configElem/Classes.h"
#include "Typedef.h"

namespace PBCS{

    //除在其所属 PBCS::Config 的成员函数中,不允许对其进行delete操作
    class PacketType {
        PBCS_PTID id;
        std::string name;
        Config* belongsTo;
        PacketType* parent;
        std::unordered_map<std::string,Packet*> *packets;
        std::unordered_map<PBCS_PID,Packet*> *IDs;
        friend class Config;
    public:
        //parent填入nullptr表示父类型为自身,即无父类型
        explicit PacketType(PBCS_PTID id, std::string name, Config* belongsTo, PacketType* parent);
        ~PacketType();
        Packet* getPacket(const std::string &pktName);
        Packet* getPacket(PBCS_PID pktID);
        bool contains(const std::string &pktName);
        bool contains(PBCS_PID id);
        size_t getPacketNum();
        void addPacket(Packet* packet);
        //同时调用对应的析构函数
        void removePacket(const std::string &pktName);
        void removePacket(PBCS_PID pktID);
        void iterate(const std::function<void(Packet *)> &f);
        PBCS_PTID getID() const;
        std::string getName();
        Config* getBelongsTo();
        PacketType* getParent();
        void changePacketName(const std::string &before, const std::string &after);
        void changePacketID(PBCS_PID before, PBCS_PID after);
        void moveToAnotherType(
            const std::string &pktNeedMove,
            PacketType *moveTo,
            std::string newName,
            PBCS_PID newID
            );
    };
}

#endif //PBCSCONFIGGENERATOR_PBCSPACKETTYPE_H