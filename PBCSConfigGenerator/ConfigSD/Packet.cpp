//
// Created by QingG on 2025/9/14.
//

#include <algorithm>
#include "configElem/Packet.h"
#include "configElem/Data.h"

namespace PBCS{

    Packet::Packet(PBCS_PID id, std::string name, PacketType* belongsTo) {
        this->id = id;
        this->name = std::move(name);
        this->belongsTo = belongsTo;
        datas = new std::list<Data*>;
        names = new std::unordered_set<std::string>;
    }

    Packet::~Packet() {
        for (auto& data : *datas) {
            delete data;
        }
        datas->clear();
        names->clear();
        delete datas;
        delete names;
    }

    Data* Packet::getData(PBCS_DTID dataID) {
        auto it = datas->begin();
        std::advance(it, dataID);
        return *it;
    }

    std::list<Data*>::size_type Packet::getDataNum() {
        return datas->size();
    }

    void Packet::addData(Data* data) {
        if (names->find(data->getName()) == names->end()) {
            datas->push_back(data);
            names->insert(data->getName());
        }
    }

    //同时调用析构函数
    void Packet::removeData(PBCS_DTID dataID) {
        if (dataID >= getDataNum()) return;
        auto it = datas->begin();
        std::advance(it, dataID);
        Data* data = *it;
        datas->erase(it);
        names->erase(data->getName());
        delete data;
    }

    void Packet::swapData(PBCS_DTID id1, PBCS_DTID id2) {
        if (id1 >= getDataNum() || id2 >= getDataNum() || id1 == id2) return;
        auto itID1 = datas->begin(),itID2 = datas->begin();
        std::advance(itID1, id1);
        std::advance(itID2, id2);
        std::iter_swap(itID1, itID2);
    }

    void Packet::iterate(const std::function<void(PBCS_DTID,Data*)>& f){
        auto i = 0;
        for (auto data = datas->begin() ; data != datas->end(); ++data,i++) {
            f(i,*data);
        }
    }

    bool Packet::contains(const std::string& dataName) {
        return std::find(names->begin(), names->end(), dataName) != names->end();
    }

    PBCS_PID Packet::getID() const {
        return id;
    }

    std::string Packet::getName() {
        return name;
    }

    PacketType* Packet::getBelongsTo() {
        return belongsTo;
    }

    const PacketType* Packet::getBelongsToConst() const {
        return belongsTo;
    }

    void Packet::changeName(PBCS_DTID dataID, std::string newName) {
        Data* data = getData(dataID);
        names->erase(data->getName());
        names->insert(newName);
        data->name = std::move(newName);
    }

}
