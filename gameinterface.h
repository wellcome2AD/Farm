#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <QWidget>
#include "game.h"

class GameInterface : public QWidget
{
    Q_OBJECT
    Game game;

public:
    GameInterface(QWidget *parent = nullptr);
    ~GameInterface();
};
#endif // GAMEINTERFACE_H
