//
// Created by QingG on 2025/9/20.
//

#ifndef PBCSCONFIGGENERATOR_PACKETEDITPAGE_H
#define PBCSCONFIGGENERATOR_PACKETEDITPAGE_H

#include <QTableWidget>
#include <QComboBox>
#include <QTreeWidgetItem>
#include <QWidget>

#include "configElem/Config.h"
#include "configElem/Data.h"
#include "configElem/Packet.h"

namespace PBCS {

    QT_BEGIN_NAMESPACE

    namespace Ui {
        class PacketEditPage;
    }

    QT_END_NAMESPACE

    class PacketEditPage : public QWidget {
        Q_OBJECT
        Ui::PacketEditPage *ui;
        friend class MainWindow;
    public:
        explicit PacketEditPage(
            QWidget *parent = nullptr,
            Config* config = nullptr,
            QTreeWidgetItem* item = nullptr,
            QTabWidget* tab = nullptr,
            std::function<void()> nonSaveState = nullptr
            );

        ~PacketEditPage() override;
    private slots:
        void nameEdited(const QString& newName);
        void nameEditFinish();
        void IDEdited(const QString& newIDStr);
        void IDEditFinish();
        void upClicked();
        void downClicked();
        void dataNameChanged(QTableWidgetItem *item);
        void addClicked();
        void deleteClicked();
    private:
        QTreeWidgetItem* item;
        QTabWidget* tab;
        PacketType* typeBelongsTo;
        Packet* packet;
        std::function<void()> nonSaveState;
        bool cellStop = false;
        static void setCurrentDataType(DataType dataType,QComboBox* comboBox);
        void swapRows(int row1, int row2);
        QComboBox* createDataTypeCB();
    };
} // PBCS

#endif //PBCSCONFIGGENERATOR_PACKETEDITPAGE_H