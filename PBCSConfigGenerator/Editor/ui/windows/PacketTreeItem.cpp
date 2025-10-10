//
// Created by QingG on 2025/9/21.
//

#include "windows/PacketTreeItem.h"

namespace PBCS {

    PacketTreeItem::PacketTreeItem(QTreeWidget* view,PacketType* type,QIcon& icon)
        :QTreeWidgetItem(view,{QString::fromStdString(type->getName()),QString::number(type->getID())}){
        QTreeWidgetItem::setData(0,Qt::UserRole,QVariant::fromValue(true));
        setIcon(0,icon);
    }

    PacketTreeItem::PacketTreeItem(QTreeWidgetItem* parent,PacketType* type,QIcon& icon)
        :QTreeWidgetItem(parent,{QString::fromStdString(type->getName()),QString::number(type->getID())}){
        QTreeWidgetItem::setData(0,Qt::UserRole,QVariant::fromValue(true));
        setIcon(0,icon);
    }

    PacketTreeItem::PacketTreeItem(QTreeWidgetItem* parent,Packet* packet,QIcon& icon)
        :QTreeWidgetItem(parent,{QString::fromStdString(packet->getName()),QString::number(packet->getID())}){
        QTreeWidgetItem::setData(0,Qt::UserRole,QVariant::fromValue(false));
        setIcon(0,icon);
    }

    bool PacketTreeItem::operator<(const QTreeWidgetItem &other) const {
        bool meType = data(0,Qt::UserRole).toBool();
        bool otherType = other.data(0,Qt::UserRole).toBool();
        if (meType != otherType) return meType > otherType;
        return text(0) < other.text(0);
    }

}
