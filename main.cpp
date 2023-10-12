#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setGeometry(500,30,500,500);
    //w.showFullScreen();
    w.show();

    return a.exec();
}
