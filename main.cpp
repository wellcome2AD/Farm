#include "gameinterface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameInterface w;
    w.Turn();
    w.show();
    return a.exec();
}
