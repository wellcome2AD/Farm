#include "game.h"

Game::Game(int number_of_players)
    : players(number_of_players, new Player())
{
    /*for(int i = 0; i < number_of_players; ++i)
        players.append(new Player());*/
}
Game::~Game()
{

}
void Game::NextTurn()
{
    order = (order + 1) % players.size();
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

