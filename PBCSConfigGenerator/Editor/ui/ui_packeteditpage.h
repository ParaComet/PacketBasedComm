/********************************************************************************
** Form generated from reading UI file 'packeteditpage.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKETEDITPAGE_H
#define UI_PACKETEDITPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PBCS {

class Ui_PacketEditPage
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *nameEdit;
    QLabel *label_3;
    QLineEdit *IDEdit;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QTableWidget *datasTable;

    void setupUi(QWidget *PBCS__PacketEditPage)
    {
        if (PBCS__PacketEditPage->objectName().isEmpty())
            PBCS__PacketEditPage->setObjectName(QStringLiteral("PBCS__PacketEditPage"));
        PBCS__PacketEditPage->resize(781, 317);
        PBCS__PacketEditPage->setAutoFillBackground(false);
        gridLayout = new QGridLayout(PBCS__PacketEditPage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(PBCS__PacketEditPage);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        nameEdit = new QLineEdit(PBCS__PacketEditPage);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        gridLayout->addWidget(nameEdit, 0, 1, 1, 2);

        label_3 = new QLabel(PBCS__PacketEditPage);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        IDEdit = new QLineEdit(PBCS__PacketEditPage);
        IDEdit->setObjectName(QStringLiteral("IDEdit"));

        gridLayout->addWidget(IDEdit, 1, 1, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(PBCS__PacketEditPage);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        upButton = new QPushButton(PBCS__PacketEditPage);
        upButton->setObjectName(QStringLiteral("upButton"));

        verticalLayout->addWidget(upButton);

        downButton = new QPushButton(PBCS__PacketEditPage);
        downButton->setObjectName(QStringLiteral("downButton"));

        verticalLayout->addWidget(downButton);

        addButton = new QPushButton(PBCS__PacketEditPage);
        addButton->setObjectName(QStringLiteral("addButton"));

        verticalLayout->addWidget(addButton);

        deleteButton = new QPushButton(PBCS__PacketEditPage);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        verticalLayout->addWidget(deleteButton);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 2);

        datasTable = new QTableWidget(PBCS__PacketEditPage);
        if (datasTable->columnCount() < 2)
            datasTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        datasTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        datasTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        datasTable->setObjectName(QStringLiteral("datasTable"));

        gridLayout->addWidget(datasTable, 2, 2, 1, 1);


        retranslateUi(PBCS__PacketEditPage);

        QMetaObject::connectSlotsByName(PBCS__PacketEditPage);
    } // setupUi

    void retranslateUi(QWidget *PBCS__PacketEditPage)
    {
        PBCS__PacketEditPage->setWindowTitle(QApplication::translate("PBCS::PacketEditPage", "PacketEditPage", Q_NULLPTR));
        label_2->setText(QApplication::translate("PBCS::PacketEditPage", "Name", Q_NULLPTR));
        label_3->setText(QApplication::translate("PBCS::PacketEditPage", "ID", Q_NULLPTR));
        label->setText(QApplication::translate("PBCS::PacketEditPage", "Datas:", Q_NULLPTR));
        upButton->setText(QApplication::translate("PBCS::PacketEditPage", "\342\206\221", Q_NULLPTR));
        downButton->setText(QApplication::translate("PBCS::PacketEditPage", "\342\206\223", Q_NULLPTR));
        addButton->setText(QApplication::translate("PBCS::PacketEditPage", "Add", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("PBCS::PacketEditPage", "Delete", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = datasTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PBCS::PacketEditPage", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = datasTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PBCS::PacketEditPage", "Type", Q_NULLPTR));
    } // retranslateUi

};

} // namespace PBCS

namespace PBCS {
namespace Ui {
    class PacketEditPage: public Ui_PacketEditPage {};
} // namespace Ui
} // namespace PBCS

#endif // UI_PACKETEDITPAGE_H
