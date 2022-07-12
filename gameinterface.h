#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <QWidget>
#include "game.h"
#include "playerwidget.h"

class GameInterface : public QWidget
{
    Q_OBJECT
    Game game;
    PlayerWidget* plwidget;
    QBoxLayout* layout;

public:
    GameInterface(QWidget *parent = nullptr);
    ~GameInterface();
};
#endif // GAMEINTERFACE_H
