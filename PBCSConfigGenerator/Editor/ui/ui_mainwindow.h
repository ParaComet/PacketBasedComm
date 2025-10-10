/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "windows/simpledragtreewidget.h"

namespace PBCS {

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionGen;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    SimpleDragTreeWidget *treeWidget;
    QTabWidget *tabWidget;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *PBCS__MainWindow)
    {
        if (PBCS__MainWindow->objectName().isEmpty())
            PBCS__MainWindow->setObjectName(QStringLiteral("PBCS__MainWindow"));
        PBCS__MainWindow->resize(887, 479);
        PBCS__MainWindow->setLayoutDirection(Qt::LeftToRight);
        actionNew = new QAction(PBCS__MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(PBCS__MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(PBCS__MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionGen = new QAction(PBCS__MainWindow);
        actionGen->setObjectName(QStringLiteral("actionGen"));
        centralwidget = new QWidget(PBCS__MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeWidget = new SimpleDragTreeWidget(splitter);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget->setDragEnabled(true);
        treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
        treeWidget->setDefaultDropAction(Qt::IgnoreAction);
        treeWidget->setSortingEnabled(true);
        treeWidget->setAnimated(true);
        splitter->addWidget(treeWidget);
        treeWidget->header()->setVisible(true);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        splitter->addWidget(tabWidget);

        horizontalLayout->addWidget(splitter);

        PBCS__MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PBCS__MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 887, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        PBCS__MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionGen);

        retranslateUi(PBCS__MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(PBCS__MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PBCS__MainWindow)
    {
        PBCS__MainWindow->setWindowTitle(QApplication::translate("PBCS::MainWindow", "PBCSConfigGenerator", Q_NULLPTR));
        actionNew->setText(QApplication::translate("PBCS::MainWindow", "New...", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("PBCS::MainWindow", "Open...", Q_NULLPTR));
        actionSave->setText(QApplication::translate("PBCS::MainWindow", "Save", Q_NULLPTR));
        actionGen->setText(QApplication::translate("PBCS::MainWindow", "Generate Code...", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("PBCS::MainWindow", "ID", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("PBCS::MainWindow", "Name", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("PBCS::MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

} // namespace PBCS

namespace PBCS {
namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui
} // namespace PBCS

#endif // UI_MAINWINDOW_H
