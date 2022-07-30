#ifndef GAME_H
#define GAME_H

#include <QVector>
#include "player.h"

class Game
{
    size_t order;
    QVector<Player*> players;
public:
    Game(int number_of_players);
    ~Game();
    void NextTurn();
    size_t GetOrder() const;
    Player* GetCurrentPlayer();
    const Player* GetCurrentPlayer() const;
    const QVector<Player*>& GetListOfPlayers() const;
};

#endif // GAME_H
