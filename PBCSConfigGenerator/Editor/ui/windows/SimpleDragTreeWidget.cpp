//
// Created by QingG on 2025/9/25.
//

#include "SimpleDragTreeWidget.h"
#include "ui_MainWindow.h"
#include "mainwindow.h"

namespace PBCS {

    void SimpleDragTreeWidget::dropEvent(QDropEvent *event) {
        QTreeWidgetItem *item = mainWindow->ui->treeWidget->currentItem();
        QTreeWidgetItem *moveTo = mainWindow->ui->treeWidget->itemAt(event->pos());
        mainWindow->nowItem = item;
        if (item->data(0, Qt::UserRole).toBool()) {
            if (moveTo == nullptr) {
                if (!mainWindow->pkttypeChangeType(nullptr,false)) return;
            }else if (!moveTo->data(0, Qt::UserRole).toBool()) return;
            else {
                PacketType* newParent = mainWindow->configNow->getPacketType(
                    moveTo->text(1).toULongLong()
                    );
                if (!mainWindow->pkttypeChangeType(newParent,false)) return;
            }
        }else {
            if (moveTo == nullptr || !moveTo->data(0, Qt::UserRole).toBool()) return;
            if (!mainWindow->packetChangeType(moveTo->text(1).toULongLong(),false,false)) return;
        }
        QTreeWidget::dropEvent(event);
    }

}
