//
// Created by QingG on 2025/9/19.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>

#include "windows/mainwindow.h"
#include "windows/packeteditpage.h"
#include "windows/PacketTreeItem.h"
#include "windows/generatewindow.h"
#include "windows/SimpleDragTreeWidget.h"

#include <utility>

#include "FileOperation.h"
#include "ui_mainwindow.h"
#include "ui_packeteditpage.h"
#include "configElem/PacketType.h"
#include "configElem/Packet.h"

namespace PBCS {

    extern QRegExpValidator* NAME_VALI;

    MainWindow::MainWindow(QWidget *parent,std::string fileName) : QMainWindow(parent), ui(new Ui::MainWindow), configNow(nullptr) {

        ui->setupUi(this);
        ui->treeWidget->mainWindow = this;

        pkttypeIcon = new QIcon("./res/pkttype.ico");
        packetIcon = new QIcon("./res/packet.ico");
        pages = new std::map<QTreeWidgetItem*,PacketEditPage*>();
        itemsByType = new std::map<PacketType*,QTreeWidgetItem*>();
        QIcon* titleIcon = new QIcon("./res/title.ico");
        setWindowIcon(*titleIcon);

        connect(ui->tabWidget, &QTabWidget::tabCloseRequested, [this](int index) {
            deletePage(dynamic_cast<PacketEditPage*>(ui->tabWidget->widget(index)),index);
        });
        connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
        connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
        connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
        connect(ui->actionGen, &QAction::triggered, [this,titleIcon] {
            if (configNow == nullptr) return;
            GenerateWindow *generateWindow = new GenerateWindow(nullptr,this->filePath,titleIcon);
            generateWindow->setAttribute(Qt::WA_DeleteOnClose);
            generateWindow->show();
        });
        connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, [this](QTreeWidgetItem *item,int) {
            openPacket(item);
        });
        connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &MainWindow::treeMenu);

        QShortcut *saveShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
        connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveFile);
        QShortcut *delShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
        connect(delShortcut, &QShortcut::activated, this, &MainWindow::deletePressed);

        packetMenu = new QMenu(ui->treeWidget);
        pkttypeMenu = new QMenu(ui->treeWidget);
        nullMenu = new QMenu(ui->treeWidget);
        nullMenuNonTMod = new QMenu(ui->treeWidget);
        connect(
            packetMenu->addAction("Open"),
            &QAction::triggered,
            this,
            &MainWindow::packetMenuOpen
            );
        connect(
            packetMenu->addAction("Delete"),
            &QAction::triggered,
            this,
            &MainWindow::packetMenuDelete
            );
        connect(
            packetMenu->addAction("Change Type..."),
            &QAction::triggered,
            this,
            &MainWindow::packetMenuChangeType
            );
        connect(
            pkttypeMenu->addAction("Change Name..."),
            &QAction::triggered,
            this,
            &MainWindow::pkttypeMenuChangeName
            );
        connect(
            pkttypeMenu->addAction("Change ID..."),
            &QAction::triggered,
            this,
            &MainWindow::pkttypeMenuChangeID
            );
        connect(
            pkttypeMenu->addAction("Change Parent..."),
            &QAction::triggered,
            this,
            &MainWindow::pkttypeMenuChangeParent
            );
        connect(
            pkttypeMenu->addAction("New Packet..."),
            &QAction::triggered,
            this,
            &MainWindow::pkttypeMenuNewPacket
            );
        connect(
            pkttypeMenu->addAction("New Packet Type..."),
            &QAction::triggered,
            this,
            &MainWindow::pkttypeMenuNewPacketType
            );
        connect(
            pkttypeMenu->addAction("Delete"),
            &QAction::triggered,
            this,
            &MainWindow::pkttypeMenuDelete
            );
        connect(
            nullMenu->addAction("New Packet Type..."),
            &QAction::triggered,
            this,
            &MainWindow::nullMenuNewPacketType
            );
        connect(
            nullMenu->addAction("Enable nonTMod"),
            &QAction::triggered,
            this,
            &MainWindow::nullMenuNonTModOn
            );
        connect(
            nullMenuNonTMod->addAction("Disable nonTMod"),
            &QAction::triggered,
            this,
            &MainWindow::nullMenuNonTModOff
            );

        if (!fileName.empty()) openFileWithName(QString::fromStdString(fileName));

    }

    MainWindow::~MainWindow() {
        delete ui;
    }

    void MainWindow::openFile() {
        saveConfirm();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"));
        openFileWithName(fileName);
    }

    void MainWindow::openPacket(QTreeWidgetItem *item) {
        std::map<QTreeWidgetItem*,PacketEditPage*>::iterator it = pages->find(item);
        if (it != pages->end()) {
            ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(it->second));
        }else {
            if (item->data(0,Qt::UserRole).toBool()) return;
            QString packetName = item->text(0);
            PacketEditPage* page = new PacketEditPage(ui->tabWidget,configNow,item,ui->tabWidget,[this]() {
                nonSaveState();
            });
            ui->tabWidget->addTab(page, *packetIcon ,packetName);
            ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(page));
            pages->insert(std::pair<QTreeWidgetItem*,PacketEditPage*>(item,page));
        }
    }

    void MainWindow::freshTreeMap() {
        ui->treeWidget->clear();
        Config::Iterator iterator = Config::Iterator(configNow);
        PacketType* type = nullptr;
        while ((type = iterator.now()) != nullptr) {
            PacketTreeItem *typeItem = new PacketTreeItem(ui->treeWidget,type,*pkttypeIcon);
            itemsByType->insert(std::pair<PacketType*,QTreeWidgetItem*>(type,typeItem));
            ui->treeWidget->addTopLevelItem(typeItem);
            iterator.nextLayer();
            freshTreeMap(iterator,typeItem);
            iterator.prevLayer();
            type->iterate([this,typeItem](Packet* packet) {
                PacketTreeItem *treeItem = new PacketTreeItem(typeItem,packet,*packetIcon);
                typeItem->addChild(treeItem);
            });
            iterator.step();
        }
        ui->treeWidget->sortItems(0,Qt::AscendingOrder);
    }

    void MainWindow::freshTreeMap(Config::Iterator& iterator,PacketTreeItem* parent) {
        PacketType* type = nullptr;
        while ((type = iterator.now()) != nullptr) {
            PacketTreeItem *typeItem = new PacketTreeItem(parent,type,*pkttypeIcon);
            itemsByType->insert(std::pair<PacketType*,QTreeWidgetItem*>(type,typeItem));
            parent->addChild(typeItem);
            iterator.nextLayer();
            freshTreeMap(iterator,typeItem);
            iterator.prevLayer();
            type->iterate([this,typeItem](Packet* packet) {
                PacketTreeItem *treeItem = new PacketTreeItem(typeItem,packet,*packetIcon);
                typeItem->addChild(treeItem);
            });
            iterator.step();
        }
        parent->sortChildren(0, Qt::AscendingOrder);
    }

    void MainWindow::deletePage(PacketEditPage* page,int index) {
        ui->tabWidget->removeTab(index);
        pages->erase(page->item);
        delete page;
    }

    void MainWindow::nonSaveState() {
        if (needToSave) return;
        needToSave = true;
        setWindowTitle("PBCSConfigGenerator - not save*");
    }

    void MainWindow::saveConfirm() {
        if (!needToSave) return;
        QMessageBox::StandardButton reply = QMessageBox::question(
                    this,
                    "Save",
                    "This config hasn't been saved yet, do you want to save it?",
                    QMessageBox::Yes | QMessageBox::No
                );
        if (reply == QMessageBox::Yes) saveFile();
        needToSave = false;
        setWindowTitle("PBCSConfigGenerator");
    }

    void MainWindow::newPacketType(PacketType* parent) {

        if (nonTModAssert()) return;

        std::string newTypeName = genNewPacketTypeName(parent,"");
        if (newTypeName.empty()) return;
        PBCS_PTID newID = 0;
        while (configNow->contains(newID)) newID++;

        PacketType* newType = new PacketType(newID,newTypeName,configNow,parent);
        configNow->addPacketType(newType);
        PacketTreeItem* item;
        if (parent == nullptr) {
            item = new PacketTreeItem(ui->treeWidget,newType,*pkttypeIcon);
            ui->treeWidget->addTopLevelItem(item);
        }else {
            item = new PacketTreeItem(nowItem,newType,*pkttypeIcon);
            nowItem->addChild(item);
        }
        itemsByType->insert(std::pair<PacketType*,QTreeWidgetItem*>(newType,item));
        nonSaveState();

    }

    void MainWindow::saveFile() {
        if (needToSave && configNow != nullptr) {
            needToSave = false;
            setWindowTitle("PBCSConfigGenerator");
            if (saveConfigFile(configNow,filePath.toStdString(),"UTF-8")) {
                QMessageBox::warning(
                this,
                "Save Failed",
                QString("Save failed, please check the config file: ").append(filePath)
                );
                nonSaveState();
            }
        }
    }

    void MainWindow::newFile() {

        saveConfirm();

        QString dirName = QFileDialog::getExistingDirectory(this, "Choose dir", QDir::homePath());
        if (dirName.isEmpty()) return;

        bool ok;
        QString fileName = QInputDialog::getText(
            nullptr,
            "Input File Name",
            "File name(It is recommended to use \".pbcs\" as the file extension):",
            QLineEdit::Normal,"config.pbcs",
            &ok
            );
        if (!ok) return;

        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Last Step",
            "Is this config need to be nonTMod?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

        bool nonTMod;
        if (reply == QMessageBox::Yes)
            nonTMod = true;
        else if (reply == QMessageBox::No)
            nonTMod = false;
        else return;

        saveFile();
        while (ui->tabWidget->count() > 0) {
            deletePage(dynamic_cast<PacketEditPage*>(ui->tabWidget->widget(0)),0);
        }
        pages->clear();
        delete configNow;
        configNow = new Config(nonTMod);

        if (nonTMod) {
            configNow->addPacketType(new PacketType(0,NONT_MOD_TYPENAME,configNow,nullptr));
        }

        freshTreeMap();

        filePath = QDir(dirName).absoluteFilePath(fileName);
        needToSave = true;
        saveFile();

    }

    void MainWindow::deletePressed() {
        QTreeWidgetItem* item = ui->treeWidget->currentItem();
        if (!ui->treeWidget->hasFocus() || item == nullptr) return;
        nowItem = item;
        if (item->data(0,Qt::UserRole).toBool()) pkttypeMenuDelete();
        else packetMenuDelete();
    }

    void MainWindow::treeMenu(const QPoint& pos) {
        if (configNow == nullptr) return;
        QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);
        if (item == nullptr) {
            if (configNow->isNonTMod()) nullMenuNonTMod->exec(QCursor::pos());
            else nullMenu->exec(QCursor::pos());
            return;
        }
        nowItem = item;
        if (nowItem->data(0,Qt::UserRole).toBool()) pkttypeMenu->exec(QCursor::pos());
        else packetMenu->exec(QCursor::pos());
    }

    void MainWindow::packetMenuOpen() {
        openPacket(nowItem);
    }

    void MainWindow::packetMenuDelete() {
        if (!deleteConfirm()) return;
        std::string packetName = nowItem->text(0).toStdString();
        PBCS_PTID pkttypeID = nowItem->parent()->text(1).toULongLong();
        configNow->getPacketType(pkttypeID)->removePacket(packetName);
        delete nowItem;
        nonSaveState();
    }

    void MainWindow::packetMenuChangeType() {
        bool ok;
        PBCS_PTID pkttypeID = inputPTID(ok,"Input Packet Type ID");
        if (!ok) return;
        packetChangeType(pkttypeID,true,true);
    }

    void MainWindow::pkttypeMenuChangeName() {
        if (nonTModAssert()) return;
        PacketType* parent;
        if (nowItem->parent() == nullptr) parent = nullptr;
        else parent = configNow->getPacketType(nowItem->parent()->text(1).toULongLong());
        std::string newTypeName = genNewPacketTypeName(parent,"");
        if (newTypeName.empty()) return;
        PacketType* type = configNow->getPacketType(nowItem->text(1).toULongLong());
        configNow->changeName(parent,type->getName(),newTypeName);
        nowItem->setText(0,QString::fromStdString(newTypeName));
        nonSaveState();
    }

    void MainWindow::pkttypeMenuChangeID() {
        if (nonTModAssert()) return;
        bool ok;
        PBCS_PTID newID = QInputDialog::getInt(
                nullptr,
                "Input A New Packet Type ID",
                "New packet type ID:",
                0,0,2147483647,1,
                &ok
            );
        if (!ok) return;
        while (configNow->contains(newID)) {
            newID = QInputDialog::getInt(
                nullptr,
                "Input A New Packet Type ID",
                QString("Packet Type ID \"")
                    .append(QString::number(newID))
                    .append("\" already occupied, please type a new packet name:"),
                0,0,2147483647,1,
                &ok
            );
            if (!ok) return;
        }
        configNow->changeID(nowItem->text(1).toULongLong(),newID);
        nowItem->setText(1,QString::number(newID));
        nonSaveState();
    }

    void MainWindow::pkttypeMenuChangeParent() {
        if (nonTModAssert()) return;
        bool ok;
        PBCS_PTID parentID = inputPTID(ok,"Input Packet Type ID(same means move to top)");
        if (!ok) return;
        PacketType* newParent = configNow->getPacketType(parentID);
        pkttypeChangeType(newParent,true);
    }

    void MainWindow::pkttypeMenuNewPacket() {

        PacketType* pkttype = configNow->getPacketType(nowItem->text(1).toULongLong());

        std::string newPacketName = genNewPacketName(pkttype,"");
        if (newPacketName.empty()) return;
        PBCS_PID newID = 0;
        while (pkttype->contains(newID)) newID++;

        Packet* packet = new Packet(newID,newPacketName,pkttype);
        pkttype->addPacket(packet);
        PacketTreeItem* item = new PacketTreeItem(nowItem,packet,*packetIcon);
        nowItem->addChild(item);
        openPacket(item);
        nonSaveState();

    }

    void MainWindow::pkttypeMenuNewPacketType() {
        PacketType* pkttype = configNow->getPacketType(nowItem->text(1).toULongLong());
        newPacketType(pkttype);
    }

    void MainWindow::pkttypeMenuDelete() {
        if (nonTModAssert()) return;
        if (!deleteConfirm()) return;
        PacketType* pkttype = configNow->getPacketType(nowItem->text(1).toULongLong());
        for (int i = 0;i < ui->tabWidget->count();i++) {
            PacketEditPage* page = dynamic_cast<PacketEditPage*>(ui->tabWidget->widget(i));
            bool isParent = false;
            for (PacketType *tmp = page->typeBelongsTo;tmp != tmp->getParent();tmp = tmp->getParent()) {
                if (tmp == pkttype) {
                    isParent = true;
                    break;
                }
            }
            if (isParent) {
                deletePage(page,i);
                i--;
            }
        }
        clearItemsByType(nowItem);
        delete nowItem;
        configNow->removePacketType(pkttype->getID());
        nonSaveState();
    }

    void MainWindow::nullMenuNewPacketType() {
        newPacketType(nullptr);
    }

    void MainWindow::nullMenuNonTModOn() {
        if (configNow->getTypesNum() != 1) {
            QMessageBox::warning(
                this,
                "Illegal action!",
                "The nonTMod only allow one packet type!"
                );
            return;
        }
        if (!configNow->contains(nullptr,NONT_MOD_TYPENAME) || !configNow->contains(0)) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                "Change packet type to default",
                QString("The packet type remains is not named \"")
                .append(QString::fromStdString(NONT_MOD_TYPENAME))
                .append("\" or it's ID isn't 0, do you want to automatically change it?"),
                QMessageBox::Yes | QMessageBox::No
            );
            if (reply != QMessageBox::Yes) return;
            PacketType* pkttype = Config::Iterator(configNow).now();
            itemsByType->at(pkttype)->setText(0,QString::fromStdString(NONT_MOD_TYPENAME));
            configNow->changeName(nullptr,pkttype->getName(),NONT_MOD_TYPENAME);
            configNow->changeID(pkttype->getID(),0);
        }
        configNow->setNonTMod(true);
        nonSaveState();
    }

    void MainWindow::nullMenuNonTModOff() {
        configNow->setNonTMod(false);
        nonSaveState();
    }

    void MainWindow::clearItemsByType(QTreeWidgetItem *item) {
        if (item->data(0,Qt::UserRole).toBool()) {
            itemsByType->erase(configNow->getPacketType(item->text(1).toULongLong()));
        }
        for (int i = 0;i < item->childCount();i++) {
            clearItemsByType(item->child(i));
        }
    }

    bool MainWindow::packetChangeType(PBCS_PTID pkttypeID,bool openNewPage,bool itemNeedMove) {

        bool ok;
        std::string packetName = nowItem->text(0).toStdString();
        PacketType* newPacketType = configNow->getPacketType(pkttypeID);
        PacketType* nowPacketType = configNow->getPacketType(nowItem->parent()->text(1).toULongLong());
        Packet* packet = nowPacketType->getPacket(packetName);
        if (newPacketType->contains(packetName)) packetName = genNewPacketName(newPacketType,packetName);
        if (packetName.empty()) return false;
        PBCS_PID newID = packet->getID();
        while (newPacketType->contains(newID)) {
            newID = QInputDialog::getInt(
                nullptr,
                "Input A New Packet ID",
                QString("Packet ID \"")
                    .append(QString::number(newID))
                    .append("\" already occupied in packet type \"")
                    .append(QString::fromStdString(newPacketType->getName()))
                    .append("\", please type a new packet ID:"),
                0,0,2147483647,1,
                &ok
            );
            if (!ok) return false;
        }

        if (pages->find(nowItem) != pages->end() && openNewPage) {
            PacketEditPage* page = pages->at(nowItem);
            deletePage(page,ui->tabWidget->indexOf(page));
        }else {
            openNewPage = false;
        }

        nowPacketType->moveToAnotherType(packet->getName(),newPacketType,packetName,newID);
        if (itemNeedMove) {
            nowItem->parent()->removeChild(nowItem);
            itemsByType->at(newPacketType)->addChild(nowItem);
        }

        if (openNewPage) openPacket(nowItem);
        nonSaveState();
        return true;

    }

    bool MainWindow::pkttypeChangeType(PacketType* newParent,bool itemNeedMove) {
        if (nonTModAssert()) return false;
        PacketType* nowType = configNow->getPacketType(nowItem->text(1).toULongLong());
        QTreeWidgetItem* nowParentItem = nowItem->parent();
        if (nowType == newParent) {
            if (nowType->getParent() == nowType) {
                QMessageBox::warning(
                this,
                "Invalid Operation",
                "This packet type is already at the top level!"
                );
                return false;
            }
            std::string newName = genNewPacketTypeName(nullptr,nowType->getName());
            if (newName.empty()) return false;
            configNow->changeParent(nowType,nullptr,newName);
            nowItem->setText(0,QString::fromStdString(newName));
            if (itemNeedMove) {
                nowParentItem->removeChild(nowItem);
                ui->treeWidget->addTopLevelItem(nowItem);
            }
        }else {
            for (PacketType* tmp = newParent; tmp != tmp->getParent(); tmp = tmp->getParent()) {
                if (tmp == nowType) {
                    QMessageBox::warning(
                    this,
                    "Invalid Operation",
                    "New parent is a child type of this packet type!"
                    );
                    return false;
                }
            }
            std::string newName = genNewPacketTypeName(newParent,nowType->getName());
            if (newName.empty()) return false;
            configNow->changeParent(nowType,newParent,newName);
            nowItem->setText(0,QString::fromStdString(newName));
            if (itemNeedMove) {
                if (nowParentItem != nullptr) {
                    nowParentItem->removeChild(nowItem);
                }else {
                    ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(nowItem));
                }
                itemsByType->at(newParent)->addChild(nowItem);
            }
        }
        nonSaveState();
        return true;
    }

    void MainWindow::openFileWithName(const QString& fileName) {
        if (!fileName.isEmpty()) {
            Config* newConfig = loadConfigFile(fileName.toStdString());
            //编译器又发狂了
            if (newConfig == nullptr) {
                QMessageBox::warning(
                    nullptr,
                    "Warning",
                    "Config file is damaged."
                    );
            }else {
                delete configNow;
                configNow = newConfig;
                freshTreeMap();
                ui->tabWidget->clear();
                this->filePath = fileName;
                pages->clear();
            }
        }
    }

    bool MainWindow::deleteConfirm() {
        QMessageBox::StandardButton reply = QMessageBox::question(
                    this,
                    "Confirm",
                    "Do you really want to delete?",
                    QMessageBox::Yes | QMessageBox::No
                );
        if (reply == QMessageBox::Yes)
            return true;
        return false;
    }

    bool MainWindow::nonTModAssert() {
        if (configNow->isNonTMod()) {
            QMessageBox::warning(
                this,
                "Illegal action!",
                "This config is a nonTMod config, you cannot take any action on packet type!"
                );
            return true;
        }
        return false;
    }

    PBCS_PTID MainWindow::inputPTID(bool& ok,const QString& title) {
        PBCS_PTID pkttypeID = QInputDialog::getInt(
                nullptr,
                title,
                "Packet type ID:",
                0,0,2147483647,1,
                &ok
            );
        if (!ok) return 0;
        while (!configNow->contains(pkttypeID)) {
            pkttypeID = QInputDialog::getInt(
                nullptr,
                title,
                QString("No such packet type's ID is \"")
                        .append(QString::number(pkttypeID))
                        .append("\" ,please entering a new packet type ID:"),
                0,0,2147483647,1,
                &ok
            );
            if (!ok) return 0;
        }
        return pkttypeID;
    }

    std::string MainWindow::genNewPacketTypeName(PacketType* parent,std::string start) {
        bool ok;
        int ignored;
        std::string newTypeName = std::move(start);
        if (newTypeName.empty()) {
            newTypeName = QInputDialog::getText(
                nullptr,
                "Input New Type Name",
                "New type name:",
                QLineEdit::Normal,"",
                &ok
            ).toStdString();
            if (!ok) return "";
        }
        QString typeNameQT = QString::fromStdString(newTypeName);
        bool validate = NAME_VALI->validate(typeNameQT,ignored) == QValidator::State::Acceptable;
        bool contains = configNow->contains(parent,newTypeName);
        while (!validate || contains) {
            if (contains) {
                QString label = QString("Packet type name \"").append(QString::fromStdString(newTypeName));
                if (parent == nullptr) {
                    label.append("already occupied in top level packet types, please type a new packet name:");
                }else {
                    label.append("\" already occupied in parent packet type \"")
                        .append(QString::fromStdString(parent->getName()))
                        .append("\", please type a new packet name:");
                }
                typeNameQT = QInputDialog::getText(
                    nullptr,
                    "Input A New Packet Type Name",
                    label,
                    QLineEdit::Normal,"",
                    &ok
                );
                if (!ok) return "";
            }else {
                typeNameQT = QInputDialog::getText(
                    nullptr,
                    "Input A New Packet Type Name",
                    "Only accept variable-like name, please entering a new name:",
                    QLineEdit::Normal,"",
                    &ok
                );
                if (!ok) return "";
            }
            newTypeName = typeNameQT.toStdString();
            validate = NAME_VALI->validate(typeNameQT,ignored) == QValidator::State::Acceptable;
            contains = configNow->contains(parent,newTypeName);
        }
        return newTypeName;
    }

    std::string MainWindow::genNewPacketName(PacketType* under,std::string start) {
        bool ok;
        std::string newPacketName = std::move(start);
        if (newPacketName.empty()) {
            newPacketName = QInputDialog::getText(
                nullptr,
                "Input New Packet Name",
                "New packet name:",
                QLineEdit::Normal,"",
                &ok
            ).toStdString();
            if (!ok) return "";
        }
        QString packetNameQT = QString::fromStdString(newPacketName);
        int ignored;
        bool validate = NAME_VALI->validate(packetNameQT,ignored) == QValidator::State::Acceptable;
        bool contains = under->contains(newPacketName);
        while (!validate || contains) {
            if (contains) {
                packetNameQT = QInputDialog::getText(
                    nullptr,
                    "Input A New Packet Name",
                    QString("Packet name \"")
                        .append(QString::fromStdString(newPacketName))
                        .append("\" already occupied in packet type \"")
                        .append(QString::fromStdString(under->getName()))
                        .append("\", please type a new packet name:"),
                    QLineEdit::Normal,"",
                    &ok
                );
                if (!ok) return "";
            }else {
                packetNameQT = QInputDialog::getText(
                    nullptr,
                    "Input A New Packet Name",
                    "Only accept variable-like name, please entering a new name:",
                    QLineEdit::Normal,"",
                    &ok
                );
                if (!ok) return "";
            }
            newPacketName = packetNameQT.toStdString();
            validate = NAME_VALI->validate(packetNameQT,ignored) == QValidator::State::Acceptable;
            contains = under->contains(newPacketName);
        }
        return newPacketName;
    }

    void MainWindow::closeEvent(QCloseEvent *event) {
        saveConfirm();
        event->accept();
    }

} // PBCS