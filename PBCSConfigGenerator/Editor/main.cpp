#include <QApplication>
#include "ui/windows/mainwindow.h"
#include <string>

using namespace PBCS;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow* w;
    if (argc == 1) w = new MainWindow(nullptr,"");
    else w = new MainWindow(nullptr,std::string(argv[1]));
    w->show();
    return QApplication::exec();
}