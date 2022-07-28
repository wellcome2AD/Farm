#include "gameinterface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameInterface w;
    w.show();
    w.StartGame();
    return a.exec();
}
