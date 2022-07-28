#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <QWidget>
#include "exchangebutton.h"
#include "game.h"
#include "playerwidget.h"

class GameInterface : public QWidget
{
    Q_OBJECT
    Game game;
    QVBoxLayout* common_layout;
    QGridLayout* maps_layout;
    QHBoxLayout* buttons_layout;
    // ducks to goat, goats to pig, pigs to horse, horses to cows, goat to a dog, horse to a dog
private:
    void Exchange();
    void repaintCurrentPlayer();
    void onExchange1ButtonClicked();
    void onExchange2ButtonClicked();
    void onExchange3ButtonClicked();
    void onExchange4ButtonClicked();
    void onExchange5ButtonClicked();
    void onExchange6ButtonClicked();
public:
    GameInterface(QWidget *parent = nullptr);
    ~GameInterface();
    void Turn();
};
#endif // GAMEINTERFACE_H
