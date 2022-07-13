#ifndef GAME_H
#define GAME_H

#include <QVector>
#include "player.h"

class Game
{
    int number_of_players;
    size_t order = 0;
    QVector<Player*> players;
public:
    Game(int number_of_players);
    size_t GetOrder();
    Player* GetCurrentPlayer() const;
};

#endif // GAME_H
