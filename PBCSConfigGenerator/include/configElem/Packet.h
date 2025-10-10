//
// Created by QingG on 2025/9/13.
//

#ifndef PBCSCONFIGGENERATOR_PBCSPACKET_H
#define PBCSCONFIGGENERATOR_PBCSPACKET_H

#include <list>
#include <string>
#include <functional>
#include <unordered_set>

#include "configElem/Classes.h"
#include "Typedef.h"

namespace PBCS{
    typedef void (*DataIterator)(PBCS_PTID,Data*);
    class Packet {
        PBCS_PID id;
        std::string name;
        PacketType* belongsTo;
        std::list<Data*> *datas;
        std::unordered_set<std::string>* names;
        friend class PacketType;
    public:
        explicit Packet(PBCS_PID id, std::string name, PacketType* belongsTo);
        ~Packet();
        Data* getData(PBCS_DTID dataID);
        std::list<Data*>::size_type getDataNum();
        void addData(Data* data);
        //同时调用析构函数
        void removeData(PBCS_DTID dataID);
        void swapData(PBCS_DTID id1, PBCS_DTID id2);
        void iterate(const std::function<void(PBCS_DTID,Data*)>& f);
        bool contains(const std::string& dataName);
        PBCS_PID getID() const;
        std::string getName();
        PacketType* getBelongsTo();
        const PacketType* getBelongsToConst() const;
        void changeName(PBCS_DTID dataID, std::string newName);
    };
}

#endif //PBCSCONFIGGENERATOR_PBCSPACKET_H