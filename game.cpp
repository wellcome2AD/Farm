#include "game.h"

Game::Game(int number_of_players)
    : number_of_players(number_of_players),
      players(number_of_players, new Player()){}
void Game::NextTurn()
{
    order = (order + 1) % number_of_players;
}
size_t Game::GetOrder()
{
    return order;
}
Player* Game::GetCurrentPlayer()
{
    return players.at(order);
}
QVector<Player*> Game::GetListOfPlayers()
{
    return players;
}

