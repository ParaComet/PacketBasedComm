//
// Created by QingG on 2025/9/14.
//

#include "configElem/Config.h"
#include "configElem/PacketType.h"

namespace PBCS {

    void Config::deleteSet(std::unordered_set<TreeNode*> *setD) {
        for (auto& node : *setD) {
            deleteSet(node->children);
            IDs->erase(node->type->id);
            node->childrenByName->clear();
            delete node->type;
            delete node->childrenByName;
            delete node;
        }
        setD->clear();
        delete setD;
    }

    void Config::deleteTreeNode(TreeNode* node) {
        if (node->type->parent != node->type) {
            TreeNode* parent = IDs->at(node->type->parent->id);
            parent->children->erase(node);
            parent->childrenByName->erase(node->type->name);
        }else {
            belongings->erase(node);
            types->erase(node->type->name);
        }
        deleteSet(node->children);
        delete node->type;
        delete node;
    }

    Config::Config(bool nonTMod) {
        this->nonTMod = nonTMod;
        this->types = new std::unordered_map<std::string, TreeNode*>();
        this->belongings = new std::unordered_set<TreeNode*>();
        this->IDs = new std::unordered_map<PBCS_PTID, TreeNode *>;
    }

    Config::~Config() {
        types->clear();
        IDs->clear();
        delete types;
        delete IDs;
        deleteSet(belongings);
    }

    PacketType* Config::getPacketType(PacketType* parent,const std::string& name) {
        if (parent == nullptr) return types->at(name)->type;
        return IDs->at(parent->id)->childrenByName->at(name)->type;
    }

    PacketType* Config::getPacketType(PBCS_PTID id) {
        return IDs->at(id)->type;
    }

    bool Config::contains(PacketType* parent,const std::string& name) {
        if (parent == nullptr) return types->find(name) != types->end();
        std::unordered_map<std::string,TreeNode*>* parentChildrenByName = IDs->at(parent->id)->childrenByName;
        return parentChildrenByName->find(name) != parentChildrenByName->end();
    }

    bool Config::contains(PBCS_PTID id) {
        return IDs->find(id) != IDs->end();
    }

    size_t Config::getTypesNum() {
        return IDs->size();
    }

    void Config::addPacketType(PacketType* type) {
        if (contains(type->id)) return;
        if (type == type->parent && types->find(type->name) != types->end()) return;
        if (type != type->parent && contains(type->parent,type->name)) return;
        TreeNode* node = new TreeNode;
        node->children = new std::unordered_set<TreeNode*>();
        node->childrenByName = new std::unordered_map<std::string, TreeNode*>();
        node->type = type;
        if (type->parent == type) {
            types->insert(std::pair<std::string,TreeNode*>(type->name,node));
            belongings->insert(node);
        }else {
            TreeNode* parentNode = IDs->find(type->parent->id)->second;
            parentNode->children->insert(node);
            parentNode->childrenByName->insert(std::pair<std::string,TreeNode*>(type->name,node));
        }
        IDs->insert(std::pair<PBCS_PTID, TreeNode *>(type->id,node));
    }

    //同时调用对应的析构函数
    void Config::removePacketType(PacketType* type,const std::string& name) {
        if(!contains(type,name)) return;
        TreeNode* node;
        if (type->parent == type) {
            node = types->at(name);
            types->erase(name);
        }else {
            node = IDs->at(type->getID())->childrenByName->at(name);
        }
        IDs->erase(node->type->id);
        deleteTreeNode(node);
    }

    //同时调用对应的析构函数
    void Config::removePacketType(PBCS_PTID id) {
        if(!contains(id)) return;
        TreeNode* node = IDs->find(id)->second;
        if (node->type->parent == node->type) types->erase(node->type->name);
        IDs->erase(id);
        deleteTreeNode(node);
    }

    bool Config::isNonTMod() const {
        return nonTMod;
    }

    void Config::setNonTMod(bool nonTMod) {
        this->nonTMod = nonTMod;
    }

    void Config::changeName(PacketType* parent,const std::string& needToChange,std::string newName) {
        if (contains(parent,newName)) return;
        if (parent == nullptr) {
            TreeNode* node = types->find(needToChange)->second;
            types->erase(needToChange);
            node->type->name = std::move(newName);
            types->insert(std::pair<std::string,TreeNode*>(node->type->name,node));
        }else {
            std::unordered_map<std::string, TreeNode *>* childrenMap = IDs->at(parent->id)->childrenByName;
            TreeNode* node = childrenMap->at(needToChange);
            childrenMap->erase(needToChange);
            node->type->name = std::move(newName);
            childrenMap->insert(std::pair<std::string,TreeNode*>(node->type->name,node));
        }
    }

    void Config::changeID(PBCS_PTID needToChange,PBCS_PTID newID) {
        TreeNode* node = IDs->find(needToChange)->second;
        IDs->erase(needToChange);
        node->type->id = newID;
        IDs->insert(std::pair<PBCS_PTID,TreeNode *>(newID,node));
    }

    void Config::changeParent(PacketType* needToChange,PacketType* newParent,std::string newName) {
        TreeNode* node = IDs->at(needToChange->id);
        if (node->type->parent != node->type) {
            TreeNode* oldParent = IDs->at(node->type->parent->id);
            oldParent->children->erase(node);
            oldParent->childrenByName->erase(needToChange->name);
        }
        needToChange->name = std::move(newName);
        if (newParent != nullptr) {
            TreeNode* newParentNode = IDs->at(newParent->id);
            newParentNode->children->insert(node);
            newParentNode->childrenByName->insert(std::pair<std::string,TreeNode*>(needToChange->name,node));
            node->type->parent = newParentNode->type;
        }else {
            types->insert(std::pair<std::string,TreeNode*>(needToChange->name,node));
            belongings->insert(node);
            needToChange->parent = needToChange;
        }
    }

    Config::Iterator::Iterator(Config* configBelongsTo){
        this->configBelongsTo = configBelongsTo;
        parentIts = new std::stack<std::unordered_set<TreeNode*>::iterator>();
        parentSets = new std::stack<std::unordered_set<TreeNode*>*>();
        nowSet = configBelongsTo->belongings;
        nowIt = nowSet->begin();
    }

    Config::Iterator::Iterator(Iterator&& it) noexcept {
        configBelongsTo = it.configBelongsTo;
        parentIts = it.parentIts;
        parentSets = it.parentSets;
        nowIt = it.nowIt;
        nowSet = it.nowSet;
        it.parentIts = nullptr;
        it.parentSets = nullptr;
    }

    Config::Iterator::~Iterator() {
        delete parentIts;
        delete parentSets;
    }

    PacketType* Config::Iterator::now() {
        if (nowIt != nowSet->end()) return (*nowIt)->type;
        return nullptr;
    }

    void Config::Iterator::step() {
        if (nowIt != nowSet->end()) ++nowIt;
    }

    void Config::Iterator::nextLayer() {
        if (nowIt == nowSet->end()) return;
        TreeNode* node = *nowIt;
        parentIts->push(nowIt);
        parentSets->push(nowSet);
        nowSet = node->children;
        nowIt = nowSet->begin();
    }

    void Config::Iterator::prevLayer() {
        if (!parentIts->empty()) {
            nowIt = parentIts->top();
            nowSet = parentSets->top();
            parentIts->pop();
            parentSets->pop();
        }
    }

    Config::Iterator& Config::Iterator::operator=(Iterator&& other) noexcept {
        if (this != &other) {
            delete parentIts;
            delete parentSets;
            // 拷贝资源
            configBelongsTo = other.configBelongsTo;
            parentIts = other.parentIts;
            parentSets = other.parentSets;
            nowSet = other.nowSet;
            nowIt = other.nowIt;
            other.parentIts = nullptr;
            other.parentSets = nullptr;
        }
        return *this;
    }

}
