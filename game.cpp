#include "game.h"

Game::Game(int number_of_players)
    : number_of_players(number_of_players),
      players(new Player[number_of_players]){}
