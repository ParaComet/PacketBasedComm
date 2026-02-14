//
// Created by QingG on 2025/9/13.
//

#ifndef PBCSCONFIGGENERATOR_PBCSCONFIG_H
#define PBCSCONFIGGENERATOR_PBCSCONFIG_H

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>

#include "Typedef.h"
#include "configElem/Classes.h"

namespace PBCS {

    const std::string NONT_MOD_TYPENAME("DEFAULT");

    class Config {

        struct TreeNode;

        std::unordered_map<std::string,TreeNode*> *types;
        std::unordered_set<TreeNode*> *belongings;
        std::unordered_map<PBCS_PTID,TreeNode*>* IDs;
        bool nonTMod;
        void deleteSet(std::unordered_set<TreeNode*> *setD);
        void deleteTreeNode(TreeNode* node);

        struct TreeNode {
            std::unordered_set<TreeNode*> *children;
            std::unordered_map<std::string,TreeNode*> *childrenByName;
            PacketType* type;
        };

    public:

        class Iterator {
            Config* configBelongsTo;
            std::stack<std::unordered_set<TreeNode*>::iterator>* parentIts;
            std::stack<std::unordered_set<TreeNode*>*>* parentSets;
            std::unordered_set<TreeNode*>* nowSet;
            std::unordered_set<TreeNode*>::iterator nowIt;
        public:
            explicit Iterator(Config* configBelongsTo);
            Iterator(Iterator&& it) noexcept ;
            ~Iterator();
            PacketType* now();
            void step();
            void nextLayer();
            void prevLayer();
            Iterator& operator=(Iterator&& other) noexcept ;
        };

        //nonTMod为false时自动创建名为 NONT_MOD_TYPENAME 的类型,ID为0
        explicit Config(bool nonTMod);
        ~Config();
        PacketType* getPacketType(PacketType* parent,const std::string& name);
        PacketType* getPacketType(PBCS_PTID id);
        bool contains(PacketType* parent,const std::string& name);
        bool contains(PBCS_PTID id);
        size_t getTypesNum();
        void addPacketType(PacketType* type);
        //同时调用对应的析构函数
        void removePacketType(PacketType* parent,const std::string& name);
        void removePacketType(PBCS_PTID id);
        bool isNonTMod() const;
        void setNonTMod(bool nonTMod);
        void changeName(PacketType* parent,const std::string& needToChange,std::string newName);
        void changeID(PBCS_PTID needToChange,PBCS_PTID newID);
        void changeParent(PacketType* needToChange,PacketType* newParent,std::string newName);
    };

}

#endif //PBCSCONFIGGENERATOR_PBCSCONFIG_H