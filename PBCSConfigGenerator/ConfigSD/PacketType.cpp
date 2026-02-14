//
// Created by QingG on 2025/9/14.
//

#include <utility>
#include "configElem/PacketType.h"
#include "configElem/Packet.h"

namespace PBCS{

    PacketType::PacketType(PBCS_PTID id, std::string name, Config* belongsTo, PacketType* parent) {
        this->id = id;
        this->name = std::move(name);
        this->belongsTo = belongsTo;
        packets = new std::unordered_map<std::string,Packet*>();
        IDs = new std::unordered_map<PBCS_PID,Packet*>();
        if (parent == nullptr) this->parent = this;
        else this->parent = parent;
    }

    PacketType::~PacketType() {
        for (auto& pair : *packets) {
            delete pair.second;
        }
        packets->clear();
        IDs->clear();
        delete packets;
        delete IDs;
    }

    Packet* PacketType::getPacket(const std::string& pktName) {
        return packets->at(pktName);
    }

    Packet* PacketType::getPacket(PBCS_PID pktID) {
        return IDs->at(pktID);
    }

    bool PacketType::contains(const std::string& pktName) {
        return packets->find(pktName) != packets->end();
    }

    bool PacketType::contains(PBCS_PID id) {
        return IDs->find(id) != IDs->end();
    }

    size_t PacketType::getPacketNum() {
        return packets->size();
    }

    void PacketType::addPacket(Packet* packet) {
        if (contains(packet->name) || contains(packet->id)) return;
        packets->insert(std::pair<std::string,Packet*>(packet->name,packet));
        IDs->insert(std::pair<PBCS_PID,Packet*>(packet->id,packet));
    }

    //同时调用对应的析构函数
    void PacketType::removePacket(const std::string& pktName) {
        if (!contains(pktName)) return;
        Packet* packet = getPacket(pktName);
        packets->erase(pktName);
        IDs->erase(packet->id);
        delete packet;
    }

    void PacketType::removePacket(PBCS_PID pktID) {
        if (!contains(pktID)) return;
        Packet* packet = getPacket(pktID);
        packets->erase(packet->name);
        IDs->erase(pktID);
        delete packet;
    }

    void PacketType::iterate(const std::function<void(Packet*)>& f) {
        for (auto & packet : *packets) {
            f(packet.second);
        }
    }

    PBCS_PTID PacketType::getID() const {
        return id;
    }

    std::string PacketType::getName() {
        return name;
    }

    Config* PacketType::getBelongsTo() {
        return belongsTo;
    }

    PacketType* PacketType::getParent() {
        return parent;
    }

    void PacketType::changePacketName(const std::string& before,const std::string& after) {
        Packet* tmp = getPacket(before);
        tmp->name = after;
        packets->erase(before);
        packets->insert(std::pair<std::string,Packet*>(after,tmp));
    }

    void PacketType::changePacketID(PBCS_PID before, PBCS_PID after) {
        Packet* tmp = getPacket(before);
        tmp->id = after;
        IDs->erase(before);
        //IDs->insert(std::pair<PBCS_PID,Packet*>(after,tmp));
        IDs->insert(std::make_pair(after, tmp));
    }

    void PacketType::moveToAnotherType(
            const std::string& pktNeedMove,
            PacketType* moveTo,
            std::string newName,
            PBCS_PID newID
        ) {
        Packet* tmp = getPacket(pktNeedMove);
        tmp->belongsTo = moveTo;
        packets->erase(pktNeedMove);
        IDs->erase(tmp->id);
        tmp->name = std::move(newName);
        tmp->id = newID;
        moveTo->addPacket(tmp);
    }

}
