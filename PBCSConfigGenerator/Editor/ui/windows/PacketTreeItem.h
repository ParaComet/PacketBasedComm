//
// Created by QingG on 2025/9/21.
//

#ifndef PBCSCONFIGGENERATOR_PACKETTREEITEM_H
#define PBCSCONFIGGENERATOR_PACKETTREEITEM_H
#include <QTreeWidgetItem>

#include "configElem/PacketType.h"
#include "configElem/Packet.h"

namespace PBCS {

    class PacketTreeItem : public QObject,public QTreeWidgetItem {
        Q_OBJECT
    public:
        explicit PacketTreeItem(QTreeWidget* view,PacketType* type,QIcon& icon);
        explicit PacketTreeItem(QTreeWidgetItem* parent,PacketType* type,QIcon& icon);
        explicit PacketTreeItem(QTreeWidgetItem* parent,Packet* packet,QIcon& icon);
        bool operator<(const QTreeWidgetItem &other) const override;
    };

}

#endif //PBCSCONFIGGENERATOR_PACKETTREEITEM_H