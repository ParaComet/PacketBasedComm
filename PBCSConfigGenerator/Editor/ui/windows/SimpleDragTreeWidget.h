//
// Created by QingG on 2025/9/25.
//

#ifndef PBCSCONFIGGENERATOR_SIMPLEDRAGTREEWIDGET_H
#define PBCSCONFIGGENERATOR_SIMPLEDRAGTREEWIDGET_H

#include <QTreeWidget>

namespace PBCS {

    class MainWindow;

    class SimpleDragTreeWidget : public QTreeWidget{
        MainWindow *mainWindow;
        friend class MainWindow;
    public:
        explicit SimpleDragTreeWidget(QWidget *parent = nullptr) : QTreeWidget(parent){}
    protected:
        void dropEvent(QDropEvent *event) override;
    };

}

#endif //PBCSCONFIGGENERATOR_SIMPLEDRAGTREEWIDGET_H