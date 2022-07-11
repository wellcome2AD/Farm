#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game
{
    int number_of_players;
    int order = 1;
    Player* players;
public:
    Game(int number_of_players);
};

#endif // GAME_H
