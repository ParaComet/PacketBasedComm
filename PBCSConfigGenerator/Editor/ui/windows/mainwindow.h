//
// Created by QingG on 2025/9/19.
//

#ifndef PBCSCONFIGGENERATOR_MAINWINDOW_H
#define PBCSCONFIGGENERATOR_MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include "generatewindow.h"
#include "packeteditpage.h"
#include "PacketTreeItem.h"
#include "configElem/Config.h"

namespace PBCS {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class MainWindow;
    }

    QT_END_NAMESPACE

    class MainWindow : public QMainWindow {
        Q_OBJECT
    private slots:
        void openFile();
        void saveFile();
        void newFile();
        void deletePressed();
        void treeMenu(const QPoint& pos);
        void packetMenuOpen();
        void packetMenuDelete();
        void packetMenuChangeType();
        void pkttypeMenuChangeName();
        void pkttypeMenuChangeID();
        void pkttypeMenuChangeParent();
        void pkttypeMenuNewPacket();
        void pkttypeMenuNewPacketType();
        void pkttypeMenuDelete();
        void nullMenuNewPacketType();
        void nullMenuNonTModOn();
        void nullMenuNonTModOff();
    public:
        explicit MainWindow(QWidget *parent = nullptr,std::string fileName = "");
        ~MainWindow() override;
    private:
        Ui::MainWindow *ui;
        QString filePath;
        Config* configNow;
        QIcon *pkttypeIcon,*packetIcon;
        std::map<QTreeWidgetItem*,PacketEditPage*>* pages;
        std::map<PacketType*,QTreeWidgetItem*>* itemsByType;
        QMenu *packetMenu;
        QMenu *pkttypeMenu;
        QMenu *nullMenu;
        QMenu *nullMenuNonTMod;
        bool needToSave = false;
        QTreeWidgetItem *nowItem = nullptr;
        friend class SimpleDragTreeWidget;
        void freshTreeMap();
        void freshTreeMap(Config::Iterator& iterator,PacketTreeItem* parent);
        void openPacket(QTreeWidgetItem *item);
        void deletePage(PacketEditPage* page,int index);
        void nonSaveState();
        void saveConfirm();
        void newPacketType(PacketType* parent);
        void clearItemsByType(QTreeWidgetItem *item);
        void openFileWithName(const QString& fileName);
        bool deleteConfirm();
        bool nonTModAssert();
        PBCS_PTID inputPTID(bool& ok,const QString& title);
        bool packetChangeType(PBCS_PTID pkttypeID,bool openNewPage,bool itemNeedMove);
        bool pkttypeChangeType(PacketType* newParent,bool itemNeedMove);
        std::string genNewPacketTypeName(PacketType* parent,std::string start);
        static std::string genNewPacketName(PacketType* under,std::string start);
    protected:
        void closeEvent(QCloseEvent *event) override;
    };
} // PBCS

#endif //PBCSCONFIGGENERATOR_MAINWINDOW_H