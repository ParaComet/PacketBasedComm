//
// Created by QingG on 2025/10/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GenerateWindow.h" resolved

#include "generatewindow.h"

#include <iostream>
#include <qdir.h>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

#include "ui_GenerateWindow.h"

namespace PBCS {

    extern QRegExpValidator* NAME_VALI;

    GenerateWindow::GenerateWindow(QWidget *parent, const QString &cfgFileName, QIcon *icon) : QWidget(parent), ui(new Ui::GenerateWindow) {

        ui->setupUi(this);
        this->cfgFileName = cfgFileName;
        setWindowIcon(*icon);

        ui->configVarText->setValidator(NAME_VALI);
        ui->vdlLenText->setValidator(new QIntValidator(ui->vdlLenText));
        ui->namespaceText->setValidator(NAME_VALI);
        ui->prefixText->setValidator(NAME_VALI);
        ui->ptidLenText->setValidator(new QIntValidator(ui->ptidLenText));
        ui->pidLenText->setValidator(new QIntValidator(ui->pidLenText));
        ui->dtidLenText->setValidator(new QIntValidator(ui->dtidLenText));
        ui->cfgIndexLenText->setValidator(new QIntValidator(ui->cfgIndexLenText));

        connect(ui->namespaceCB, &QCheckBox::clicked, [this](bool checked) {
            ui->namespaceText->setEnabled(checked);
        });
        connect(ui->prefixCB, &QCheckBox::clicked, [this](bool checked) {
            ui->prefixText->setEnabled(checked);
        });
        connect(ui->ptidLenCB, &QCheckBox::clicked, [this](bool checked) {
            ui->ptidLenText->setEnabled(checked);
        });
        connect(ui->pidLenCB, &QCheckBox::clicked, [this](bool checked) {
            ui->pidLenText->setEnabled(checked);
        });
        connect(ui->dtidLenCB, &QCheckBox::clicked, [this](bool checked) {
            ui->dtidLenText->setEnabled(checked);
        });
        connect(ui->cfgIndexLenCB, &QCheckBox::clicked, [this](bool checked) {
            ui->cfgIndexLenText->setEnabled(checked);
        });
        connect(ui->cancelButton, &QPushButton::clicked, this, &QWidget::close);

        connect(ui->genButton, &QPushButton::clicked,[this] {

            if (
                ui->hFileText->text().isEmpty() ||
                ui->cFileText->text().isEmpty() ||
                ui->configVarText->text().isEmpty() ||
                ui->onceDefineText->text().isEmpty() ||
                ui->vdlLenText->text().isEmpty() ||
                ui->namespaceCB->isChecked() && ui->namespaceText->text().isEmpty() ||
                ui->prefixCB->isChecked() && ui->prefixText->text().isEmpty() ||
                ui->ptidLenCB->isChecked() && ui->ptidLenText->text().isEmpty() ||
                ui->pidLenCB->isChecked() && ui->pidLenText->text().isEmpty() ||
                ui->dtidLenCB->isChecked() && ui->dtidLenText->text().isEmpty() ||
                ui->cfgIndexLenCB->isChecked() && ui->cfgIndexLenText->text().isEmpty()
            ) {
                QMessageBox::warning(
                this,
                "Something empty!",
                QString("Something you should fill is empty!")
                );
                return;
            }

            int ignored;
            QString onceDefine = ui->onceDefineText->text();
            if (
                ui->onceDefineText->text() != "*once" &&
                NAME_VALI->validate(onceDefine, ignored) != QValidator::State::Acceptable
                ) {
                QMessageBox::warning(
                this,
                "Illegal input!",
                QString("Illigal once define!")
                );
                return;
            }

            QFileInfo fi(this->cfgFileName);
            QDir dir(fi.absoluteFilePath());
            dir.cdUp();

            QStringList command;
            command << this->cfgFileName;
            command << dir.absoluteFilePath(ui->hFileText->text());
            command << dir.absoluteFilePath(ui->cFileText->text());
            command << ui->configVarText->text();
            command << onceDefine;
            command << ui->vdlLenText->text();

            if (ui->namespaceCB->isChecked()) command << "-namespace" << ui->namespaceText->text();
            if (ui->prefixCB->isChecked()) command << "-prefix" << ui->prefixText->text();
            if (ui->ptidLenCB->isChecked()) command << "-ptidLen" << ui->ptidLenText->text();
            if (ui->pidLenCB->isChecked()) command << "-pidLen" << ui->pidLenText->text();
            if (ui->dtidLenCB->isChecked()) command << "-dtidLen" << ui->dtidLenText->text();
            if (ui->cfgIndexLenCB->isChecked()) command << "-cfgIndexLen" << ui->cfgIndexLenText->text();
            if (ui->upperCaseCB->isChecked()) command << "-upperCase";

            QString appDir = QCoreApplication::applicationDirPath();
            QString targetPath = GEN_EXECNAME;
            QString fullPath = QDir(appDir).filePath(targetPath);
            QProcess process;
            process.start(fullPath,command);
            process.waitForFinished();

            this->close();

        });

    }

    GenerateWindow::~GenerateWindow() {
        delete ui;
    }

} // PBCS