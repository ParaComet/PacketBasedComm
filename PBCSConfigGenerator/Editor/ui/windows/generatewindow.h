//
// Created by QingG on 2025/10/9.
//

#ifndef PBCSCONFIGGENERATOR_GENERATEWINDOW_H
#define PBCSCONFIGGENERATOR_GENERATEWINDOW_H

#include <QWidget>
#include <QFile>
#include <QIcon>

namespace PBCS {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class GenerateWindow;
    }

    QT_END_NAMESPACE

    class GenerateWindow : public QWidget {
        Q_OBJECT
        QString cfgFileName;
    public:
        explicit GenerateWindow(QWidget *parent = nullptr, const QString &cfgFileName = "", QIcon *icon = nullptr);

        ~GenerateWindow() override;

    private:
        Ui::GenerateWindow *ui;
    };
} // PBCS

#endif //PBCSCONFIGGENERATOR_GENERATEWINDOW_H