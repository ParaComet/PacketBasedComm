/********************************************************************************
** Form generated from reading UI file 'generatewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEWINDOW_H
#define UI_GENERATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PBCS {

class Ui_GenerateWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QGridLayout *gridLayout;
    QLineEdit *cFileText;
    QLineEdit *vdlLenText;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_5;
    QLineEdit *hFileText;
    QLineEdit *configVarText;
    QLineEdit *onceDefineText;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_7;
    QFormLayout *formLayout;
    QLineEdit *namespaceText;
    QCheckBox *prefixCB;
    QLineEdit *prefixText;
    QCheckBox *ptidLenCB;
    QLineEdit *ptidLenText;
    QCheckBox *pidLenCB;
    QLineEdit *pidLenText;
    QCheckBox *dtidLenCB;
    QLineEdit *dtidLenText;
    QCheckBox *cfgIndexLenCB;
    QLineEdit *cfgIndexLenText;
    QCheckBox *upperCaseCB;
    QCheckBox *namespaceCB;
    QSplitter *splitter;
    QPushButton *genButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *PBCS__GenerateWindow)
    {
        if (PBCS__GenerateWindow->objectName().isEmpty())
            PBCS__GenerateWindow->setObjectName(QStringLiteral("PBCS__GenerateWindow"));
        PBCS__GenerateWindow->resize(441, 415);
        verticalLayout = new QVBoxLayout(PBCS__GenerateWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_6 = new QLabel(PBCS__GenerateWindow);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cFileText = new QLineEdit(PBCS__GenerateWindow);
        cFileText->setObjectName(QStringLiteral("cFileText"));

        gridLayout->addWidget(cFileText, 1, 1, 1, 1);

        vdlLenText = new QLineEdit(PBCS__GenerateWindow);
        vdlLenText->setObjectName(QStringLiteral("vdlLenText"));

        gridLayout->addWidget(vdlLenText, 4, 1, 1, 1);

        label_4 = new QLabel(PBCS__GenerateWindow);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(PBCS__GenerateWindow);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_5 = new QLabel(PBCS__GenerateWindow);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        hFileText = new QLineEdit(PBCS__GenerateWindow);
        hFileText->setObjectName(QStringLiteral("hFileText"));

        gridLayout->addWidget(hFileText, 0, 1, 1, 1);

        configVarText = new QLineEdit(PBCS__GenerateWindow);
        configVarText->setObjectName(QStringLiteral("configVarText"));

        gridLayout->addWidget(configVarText, 2, 1, 1, 1);

        onceDefineText = new QLineEdit(PBCS__GenerateWindow);
        onceDefineText->setObjectName(QStringLiteral("onceDefineText"));
        onceDefineText->setReadOnly(false);

        gridLayout->addWidget(onceDefineText, 3, 1, 1, 1);

        label_2 = new QLabel(PBCS__GenerateWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(PBCS__GenerateWindow);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        label_7 = new QLabel(PBCS__GenerateWindow);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        namespaceText = new QLineEdit(PBCS__GenerateWindow);
        namespaceText->setObjectName(QStringLiteral("namespaceText"));
        namespaceText->setEnabled(false);
        namespaceText->setReadOnly(false);
        namespaceText->setClearButtonEnabled(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, namespaceText);

        prefixCB = new QCheckBox(PBCS__GenerateWindow);
        prefixCB->setObjectName(QStringLiteral("prefixCB"));

        formLayout->setWidget(1, QFormLayout::LabelRole, prefixCB);

        prefixText = new QLineEdit(PBCS__GenerateWindow);
        prefixText->setObjectName(QStringLiteral("prefixText"));
        prefixText->setEnabled(false);
        prefixText->setReadOnly(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, prefixText);

        ptidLenCB = new QCheckBox(PBCS__GenerateWindow);
        ptidLenCB->setObjectName(QStringLiteral("ptidLenCB"));

        formLayout->setWidget(2, QFormLayout::LabelRole, ptidLenCB);

        ptidLenText = new QLineEdit(PBCS__GenerateWindow);
        ptidLenText->setObjectName(QStringLiteral("ptidLenText"));
        ptidLenText->setEnabled(false);
        ptidLenText->setReadOnly(false);

        formLayout->setWidget(2, QFormLayout::FieldRole, ptidLenText);

        pidLenCB = new QCheckBox(PBCS__GenerateWindow);
        pidLenCB->setObjectName(QStringLiteral("pidLenCB"));

        formLayout->setWidget(3, QFormLayout::LabelRole, pidLenCB);

        pidLenText = new QLineEdit(PBCS__GenerateWindow);
        pidLenText->setObjectName(QStringLiteral("pidLenText"));
        pidLenText->setEnabled(false);
        pidLenText->setReadOnly(false);

        formLayout->setWidget(3, QFormLayout::FieldRole, pidLenText);

        dtidLenCB = new QCheckBox(PBCS__GenerateWindow);
        dtidLenCB->setObjectName(QStringLiteral("dtidLenCB"));

        formLayout->setWidget(4, QFormLayout::LabelRole, dtidLenCB);

        dtidLenText = new QLineEdit(PBCS__GenerateWindow);
        dtidLenText->setObjectName(QStringLiteral("dtidLenText"));
        dtidLenText->setEnabled(false);
        dtidLenText->setReadOnly(false);

        formLayout->setWidget(4, QFormLayout::FieldRole, dtidLenText);

        cfgIndexLenCB = new QCheckBox(PBCS__GenerateWindow);
        cfgIndexLenCB->setObjectName(QStringLiteral("cfgIndexLenCB"));

        formLayout->setWidget(5, QFormLayout::LabelRole, cfgIndexLenCB);

        cfgIndexLenText = new QLineEdit(PBCS__GenerateWindow);
        cfgIndexLenText->setObjectName(QStringLiteral("cfgIndexLenText"));
        cfgIndexLenText->setEnabled(false);
        cfgIndexLenText->setReadOnly(false);

        formLayout->setWidget(5, QFormLayout::FieldRole, cfgIndexLenText);

        upperCaseCB = new QCheckBox(PBCS__GenerateWindow);
        upperCaseCB->setObjectName(QStringLiteral("upperCaseCB"));

        formLayout->setWidget(6, QFormLayout::LabelRole, upperCaseCB);

        namespaceCB = new QCheckBox(PBCS__GenerateWindow);
        namespaceCB->setObjectName(QStringLiteral("namespaceCB"));

        formLayout->setWidget(0, QFormLayout::LabelRole, namespaceCB);


        gridLayout_2->addLayout(formLayout, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        splitter = new QSplitter(PBCS__GenerateWindow);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        genButton = new QPushButton(splitter);
        genButton->setObjectName(QStringLiteral("genButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(genButton->sizePolicy().hasHeightForWidth());
        genButton->setSizePolicy(sizePolicy);
        splitter->addWidget(genButton);
        cancelButton = new QPushButton(splitter);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy);
        splitter->addWidget(cancelButton);

        verticalLayout->addWidget(splitter);

        QWidget::setTabOrder(hFileText, cFileText);
        QWidget::setTabOrder(cFileText, configVarText);
        QWidget::setTabOrder(configVarText, onceDefineText);
        QWidget::setTabOrder(onceDefineText, vdlLenText);
        QWidget::setTabOrder(vdlLenText, namespaceCB);
        QWidget::setTabOrder(namespaceCB, namespaceText);
        QWidget::setTabOrder(namespaceText, prefixCB);
        QWidget::setTabOrder(prefixCB, prefixText);
        QWidget::setTabOrder(prefixText, ptidLenCB);
        QWidget::setTabOrder(ptidLenCB, ptidLenText);
        QWidget::setTabOrder(ptidLenText, pidLenCB);
        QWidget::setTabOrder(pidLenCB, pidLenText);
        QWidget::setTabOrder(pidLenText, dtidLenCB);
        QWidget::setTabOrder(dtidLenCB, dtidLenText);
        QWidget::setTabOrder(dtidLenText, cfgIndexLenCB);
        QWidget::setTabOrder(cfgIndexLenCB, cfgIndexLenText);
        QWidget::setTabOrder(cfgIndexLenText, upperCaseCB);
        QWidget::setTabOrder(upperCaseCB, genButton);
        QWidget::setTabOrder(genButton, cancelButton);

        retranslateUi(PBCS__GenerateWindow);

        QMetaObject::connectSlotsByName(PBCS__GenerateWindow);
    } // setupUi

    void retranslateUi(QWidget *PBCS__GenerateWindow)
    {
        PBCS__GenerateWindow->setWindowTitle(QApplication::translate("PBCS::GenerateWindow", "GenerateWindow", Q_NULLPTR));
        label_6->setText(QApplication::translate("PBCS::GenerateWindow", "Parameters:", Q_NULLPTR));
        label_4->setText(QApplication::translate("PBCS::GenerateWindow", "Once define:", Q_NULLPTR));
        label->setText(QApplication::translate("PBCS::GenerateWindow", "Output .c filename:", Q_NULLPTR));
        label_5->setText(QApplication::translate("PBCS::GenerateWindow", "vdlLen:", Q_NULLPTR));
        label_2->setText(QApplication::translate("PBCS::GenerateWindow", "Output .h filename:", Q_NULLPTR));
        label_3->setText(QApplication::translate("PBCS::GenerateWindow", "Config var name:", Q_NULLPTR));
        label_7->setText(QApplication::translate("PBCS::GenerateWindow", "Additions:", Q_NULLPTR));
        prefixCB->setText(QApplication::translate("PBCS::GenerateWindow", "prefix:", Q_NULLPTR));
        ptidLenCB->setText(QApplication::translate("PBCS::GenerateWindow", "ptidLen:", Q_NULLPTR));
        pidLenCB->setText(QApplication::translate("PBCS::GenerateWindow", "pidLen:", Q_NULLPTR));
        dtidLenCB->setText(QApplication::translate("PBCS::GenerateWindow", "dtidLen:", Q_NULLPTR));
        cfgIndexLenCB->setText(QApplication::translate("PBCS::GenerateWindow", "cfgIndexLen:", Q_NULLPTR));
        upperCaseCB->setText(QApplication::translate("PBCS::GenerateWindow", "upperCase", Q_NULLPTR));
        namespaceCB->setText(QApplication::translate("PBCS::GenerateWindow", "namespace:", Q_NULLPTR));
        genButton->setText(QApplication::translate("PBCS::GenerateWindow", "Generate", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("PBCS::GenerateWindow", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

} // namespace PBCS

namespace PBCS {
namespace Ui {
    class GenerateWindow: public Ui_GenerateWindow {};
} // namespace Ui
} // namespace PBCS

#endif // UI_GENERATEWINDOW_H
