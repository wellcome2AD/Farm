#include "game.h"

Game::Game(int number_of_players)
    : number_of_players(number_of_players),
      players(number_of_players, new Player()){}
size_t Game::GetOrder()
{
    return order;
}
Player* Game::GetCurrentPlayer() const
{
    return players.at(order);
}

