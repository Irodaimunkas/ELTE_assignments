#include "blackholeview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    blackHoleView w;
    w.show();

    return a.exec();
}
