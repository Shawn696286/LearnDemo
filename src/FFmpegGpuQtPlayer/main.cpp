#include "cmainwin.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    CMainWin w;
    w.show();
    return a.exec();
}
