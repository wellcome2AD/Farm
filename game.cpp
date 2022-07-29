#include "game.h"

Game::Game(int number_of_players)
{
    for(int i = 0; i < number_of_players; ++i)
        players.append(new Player());
}
Game::~Game()
{

}
void Game::NextTurn()
{
    auto prevPlayer = GetCurrentPlayer();
    order = (order + 1) % players.size();
    prevPlayer->update();
}
size_t Game::GetOrder() const
{
    return order;
}
Player* Game::GetCurrentPlayer()
{
    return const_cast<Player*>(const_cast<const Game&>(*this).GetCurrentPlayer());
}
const Player* Game::GetCurrentPlayer() const
{
    return players.at(order);
}
const QVector<Player*>& Game::GetListOfPlayers() const
{
    return players;
}

