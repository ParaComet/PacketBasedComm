//
// Created by QingG on 2025/9/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PacketEditPage.h" resolved

#include "windows/packeteditpage.h"

#include <QMessageBox>
#include <utility>

#include "ui_packeteditpage.h"
#include "configElem/PacketType.h"
#include "configElem/Data.h"

namespace PBCS {

    QRegExpValidator* NAME_VALI = new QRegExpValidator(QRegExp("[a-zA-Z_][a-zA-Z0-9_]*"));

    PacketEditPage::PacketEditPage(
        QWidget *parent,
        Config* config,
        QTreeWidgetItem* item,
        QTabWidget* tab,
        std::function<void()> nonSaveState
        ) : QWidget(parent), ui(new Ui::PacketEditPage) {

        ui->setupUi(this);
        typeBelongsTo = config->getPacketType(item->parent()->text(1).toULongLong());
        packet = typeBelongsTo->getPacket(item->text(0).toStdString());
        this->item = item;
        this->tab = tab;
        this->nonSaveState = std::move(nonSaveState);

        ui->nameEdit->setValidator(NAME_VALI);
        ui->IDEdit->setValidator(new QIntValidator(ui->IDEdit));

        ui->nameEdit->setText(tr(packet->getName().c_str()));
        ui->IDEdit->setText(QString::number(packet->getID()));
        packet->iterate([this](PBCS_DTID,Data* data) {
            //...
            QTableWidgetItem* name = new QTableWidgetItem(tr(data->getName().c_str()));
            QComboBox* dataTypeCB = createDataTypeCB();
            setCurrentDataType(data->getDataType(), dataTypeCB);
            int row = ui->datasTable->rowCount();
            ui->datasTable->insertRow(row);
            ui->datasTable->setItem(row, 0, name);
            ui->datasTable->setCellWidget(row,1,dataTypeCB);
        });

        connect(ui->nameEdit,&QLineEdit::textEdited,this,&PacketEditPage::nameEdited);
        connect(ui->nameEdit,&QLineEdit::editingFinished,this,&PacketEditPage::nameEditFinish);
        connect(ui->IDEdit,&QLineEdit::textEdited,this,&PacketEditPage::IDEdited);
        connect(ui->IDEdit,&QLineEdit::editingFinished,this,&PacketEditPage::IDEditFinish);
        connect(ui->upButton,&QPushButton::clicked,this,&PacketEditPage::upClicked);
        connect(ui->downButton,&QPushButton::clicked,this,&PacketEditPage::downClicked);
        connect(ui->datasTable,&QTableWidget::itemChanged,this,&PacketEditPage::dataNameChanged);
        connect(ui->addButton,&QPushButton::clicked,this,&PacketEditPage::addClicked);
        connect(ui->deleteButton,&QPushButton::clicked,this,&PacketEditPage::deleteClicked);

    }

    PacketEditPage::~PacketEditPage() {
        delete ui;
    }

    void PacketEditPage::nameEdited(const QString& newName) {
        if (
            newName.isEmpty() ||
            typeBelongsTo->contains(newName.toStdString())
            ) return;
        typeBelongsTo->changePacketName(packet->getName(),newName.toStdString());
        item->setText(0,newName);
        tab->setTabText(tab->indexOf(this),newName);
        nonSaveState();
    }

    void PacketEditPage::nameEditFinish() {
        std::string newName = ui->nameEdit->text().toStdString();
        if (
            typeBelongsTo->contains(newName) &&
            packet->getName() != newName
            ) {
            QMessageBox::warning(
                this,
                "Invalid Name",
                "There is a packet has the same name of this packet, please entering a new name!"
                );
            ui->nameEdit->setFocus();
        }
    }

    void PacketEditPage::IDEdited(const QString& newIDStr) {
        PBCS_PID newID = newIDStr.toULongLong();
        if (
            newIDStr.isEmpty() ||
            typeBelongsTo->contains(newID)
            ) return;
        typeBelongsTo->changePacketID(packet->getID(),newID);
        item->setText(1,QString::number(newID));
        nonSaveState();
    }

    void PacketEditPage::IDEditFinish() {
        PBCS_PID newID = ui->IDEdit->text().toULongLong();
        if (
            typeBelongsTo->contains(newID) &&
            packet->getID() != newID
            ) {
            QMessageBox::warning(
                this,
                "Invalid ID",
                "There is a packet has the same ID of this packet, please entering a new ID!"
                );
            ui->IDEdit->setFocus();
        }
    }

    void PacketEditPage::upClicked() {
        int row = ui->datasTable->currentRow();
        if (row == -1 || row == 0) return;
        int rowAbove = row - 1;
        packet->swapData(row,rowAbove);
        swapRows(row,rowAbove);
        ui->datasTable->setCurrentCell(rowAbove,ui->datasTable->currentColumn());
        nonSaveState();
    }

    void PacketEditPage::downClicked() {
        int row = ui->datasTable->currentRow();
        if (row == -1 || row == (ui->datasTable->rowCount() - 1)) return;
        int rowBelow = row + 1;
        packet->swapData(row,rowBelow);
        swapRows(row,rowBelow);
        ui->datasTable->setCurrentCell(rowBelow,ui->datasTable->currentColumn());
        nonSaveState();
    }

    void PacketEditPage::dataNameChanged(QTableWidgetItem *item) {
        if (cellStop) return;
        for (int row = 0; row < ui->datasTable->rowCount(); row++) {
            if (ui->datasTable->item(row,0) != item) continue;
            int ignored = 0;
            QString newName = item->text();
            std::string newNameStd = newName.toStdString();
            Data* data = packet->getData(row);
            if (newNameStd == data->getName()) break;
            if (NAME_VALI->validate(newName,ignored) != QValidator::State::Acceptable) {
                QMessageBox::warning(
                    this,
                    "Invalid Name",
                    "Only accept variable-like name, please entering a new name!"
                    );
                item->setText(tr(data->getName().c_str()));
                ui->datasTable->setCurrentCell(row,0);
            }else if (packet->contains(newNameStd)) {
                QMessageBox::warning(
                    this,
                    "Invalid Name",
                    "There is a data has the same name of this data, please entering a new name!"
                    );
                item->setText(tr(data->getName().c_str()));
                ui->datasTable->setCurrentCell(row,0);
            }else {
                packet->changeName(row,newNameStd);
                nonSaveState();
            }
            break;
        }
    }

    void PacketEditPage::addClicked() {
        QString newNameTmp = "var%1";
        std::string newName = newNameTmp.toStdString();
        PBCS_DTID i = 0;
        do {
            newName = newNameTmp.arg(i).toStdString();
            i++;
        }while (packet->contains(newName));
        Data* data = new Data(DataType::UINT8,newName);
        packet->addData(data);
        cellStop = true;
        QTableWidgetItem* name = new QTableWidgetItem(tr(newName.c_str()));
        QComboBox* dataTypeCB = createDataTypeCB();
        setCurrentDataType(data->getDataType(), dataTypeCB);
        int row = ui->datasTable->rowCount();
        ui->datasTable->insertRow(row);
        ui->datasTable->setItem(row, 0, name);
        ui->datasTable->setCellWidget(row,1,dataTypeCB);
        cellStop = false;
        nonSaveState();
    }

    void PacketEditPage::deleteClicked() {
        int row = ui->datasTable->currentRow();
        if (row == -1) return;
        cellStop = true;
        ui->datasTable->removeRow(row);
        cellStop = false;
        packet->removeData(row);
        nonSaveState();
    }

    QComboBox* PacketEditPage::createDataTypeCB() {
        QComboBox* dataTypeCB = new QComboBox(ui->datasTable);
        dataTypeCB->addItem("UINT8");
        dataTypeCB->addItem("UINT16");
        dataTypeCB->addItem("UINT32");
        dataTypeCB->addItem("INT8");
        dataTypeCB->addItem("INT16");
        dataTypeCB->addItem("INT32");
        dataTypeCB->addItem("FLOAT32");
        dataTypeCB->addItem("VARIABLE");
        dataTypeCB->addItem("UINT64");
        dataTypeCB->addItem("INT64");
        dataTypeCB->addItem("FLOAT64");
        dataTypeCB->setEditable(false);
        connect(
            dataTypeCB,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            [dataTypeCB,this](int index) {
                if (cellStop) return;
                for (int row = 0; row < ui->datasTable->rowCount(); row++) {
                    if (ui->datasTable->cellWidget(row,1) != dataTypeCB) continue;
                    DataType newDataType = DataType::UINT8;
                    switch (index) {
                        default:
                        case 0: break;
                        case 1: newDataType = DataType::UINT16; break;
                        case 2: newDataType = DataType::UINT32; break;
                        case 3: newDataType = DataType::INT8; break;
                        case 4: newDataType = DataType::INT16; break;
                        case 5: newDataType = DataType::INT32; break;
                        case 6: newDataType = DataType::FLOAT32; break;
                        case 7: newDataType = DataType::VARIABLE; break;
                        case 8: newDataType = DataType::UINT64; break;
                        case 9: newDataType = DataType::INT64; break;
                        case 10: newDataType = DataType::FLOAT64; break;
                    }
                    packet->getData(row)->setDataType(newDataType);
                    nonSaveState();
                    break;
                }
            }
        );
        return dataTypeCB;
    }

    void PacketEditPage::setCurrentDataType(DataType dataType,QComboBox* comboBox) {
        switch (dataType) {
            default:
            case DataType::UINT8: comboBox->setCurrentIndex(0); break;
            case DataType::UINT16: comboBox->setCurrentIndex(1); break;
            case DataType::UINT32: comboBox->setCurrentIndex(2); break;
            case DataType::INT8: comboBox->setCurrentIndex(3); break;
            case DataType::INT16: comboBox->setCurrentIndex(4); break;
            case DataType::INT32: comboBox->setCurrentIndex(5); break;
            case DataType::FLOAT32: comboBox->setCurrentIndex(6); break;
            case DataType::VARIABLE: comboBox->setCurrentIndex(7); break;
            case DataType::UINT64: comboBox->setCurrentIndex(8); break;
            case DataType::INT64: comboBox->setCurrentIndex(9); break;
            case DataType::FLOAT64: comboBox->setCurrentIndex(10); break;
        }
    }

    void PacketEditPage::swapRows(int row1, int row2) {
        cellStop = true;
        QTableWidgetItem* itemRow1 = ui->datasTable->item(row1,0);
        QTableWidgetItem* itemRow2 = ui->datasTable->item(row2,0);
        QString dtNameTmp = std::move(itemRow2->text());
        itemRow2->setText(itemRow1->text());
        itemRow1->setText(dtNameTmp);
        setCurrentDataType(
            packet->getData(row1)->getDataType(),
            dynamic_cast<QComboBox *>(ui->datasTable->cellWidget(row1,1))
            );
        setCurrentDataType(
            packet->getData(row2)->getDataType(),
            dynamic_cast<QComboBox *>(ui->datasTable->cellWidget(row2,1))
            );
        cellStop = false;
    }

} // PBCS