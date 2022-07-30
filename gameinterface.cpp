#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include "gameinterface.h"
#include "gamephasewidget.h"

GameInterface::GameInterface(QWidget *parent)
    : QWidget       (parent),
      game          (4),
      common_layout (new QVBoxLayout(this)),
      maps_layout   (new QGridLayout),
      buttons_layout(new QHBoxLayout),
      game_phase(new GamePhaseWidget(this))
{
    move(0,0);
    QVector<QIcon> icon_for_button({QPixmap(":/resources/exchange1"),
                                    QPixmap(":/resources/exchange2"),
                                    QPixmap(":/resources/exchange3"),
                                    QPixmap(":/resources/exchange4"),
                                    QPixmap(":/resources/exchange5"),
                                    QPixmap(":/resources/exchange6")});
    QVector<QString> text_for_button(std::initializer_list<QString>{QString("6 Ducks to 1 Goat"),
                                                                    QString("2 Goat to 1 Pig"),
                                                                    QString("3 Pig to 1 Horse"),
                                                                    QString("2 Horse to 1 Cow"),
                                                                    QString("Goat to Antyfox Dog"),
                                                                    QString("Horse to Antybear Dog")});

    QVector<void(GameInterface::*)()> method_ptr = {&GameInterface::onExchange1ButtonClicked,
                                                    &GameInterface::onExchange2ButtonClicked,
                                                    &GameInterface::onExchange3ButtonClicked,
                                                    &GameInterface::onExchange4ButtonClicked,
                                                    &GameInterface::onExchange5ButtonClicked,
                                                    &GameInterface::onExchange6ButtonClicked};
    for(int i=0; i < text_for_button.size(); ++i)
    {
        auto button = new ExchangeButton(icon_for_button.at(i), text_for_button.at(i), this);
        buttons_layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, method_ptr.at(i));
    }

    QPushButton* next_button = new QPushButton(this);
    size_t next_text_size = next_button->width()/10 + 3;
    next_button->setFont(QFont("Times", next_text_size, QFont::Bold));
    next_button->setText("Next turn");
    next_button->setDisabled(true);
    connect(next_button, &QPushButton::clicked, this, &GameInterface::onNextButtonClicked);
    buttons_layout->addWidget(next_button);

    auto list_of_players = game.GetListOfPlayers();

    for(int n = 0; n < list_of_players.size() / 2; ++n)
    {
        for(int m = 0; m < 2; ++m)
        {
            orientationOfMapEnum o = m % 2 == 0? left_side_map : right_side_map;
            PlayerWidget* plwidget = new PlayerWidget(this, o, list_of_players.at(n * 2 + m));
            qDebug() << "Players " << n * 2 + m << " were created";
            maps_layout->addWidget(plwidget, n, m);
        }
    }

    buttons_layout->setContentsMargins(2, 0, 2, 0);
    common_layout->setContentsMargins(0, 1, 0, 1);
    common_layout->addLayout(maps_layout);
    common_layout->addLayout(buttons_layout);
    common_layout->setAlignment(buttons_layout, Qt::AlignCenter);
    setLayout(common_layout);

    game_phase->show();
}
GameInterface::~GameInterface()
{
}
void GameInterface::StartGame()
{
    game_phase->NextPhase();

    setDisabledNextButton(true);
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "GameInterface: Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->FirstStage();
    QTimer::singleShot(4000, [this](){ game_phase->NextPhase(), setDisabledNextButton(false); });
}
void GameInterface::setDisabledNextButton(bool is_disabled)
{
    QLayoutItem* item = buttons_layout->itemAt(6);
    if(item == nullptr)
    {
        qDebug() << "GameInterface: Can't get an item from buttons_layout";
        return;
    }
    auto next_button = qobject_cast<QPushButton*>(item->widget());
    if(next_button == nullptr)
    {
        qDebug() << "GameInterface: Can't get a next_button from item";
        return;
    }
    next_button->setDisabled(is_disabled);
}
void GameInterface::onExchange1ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "GameInterface: Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeDucksToGoat);
}
void GameInterface::onExchange2ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "GameInterface: Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeGoatsToPig);
}
void GameInterface::onExchange3ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "GameInterface: Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changePigsToHorse);
}
void GameInterface::onExchange4ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "GameInterface: Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeHorsesToCow);
}
void GameInterface::onExchange5ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "GameInterface: Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeGoatToDog);
}
void GameInterface::onExchange6ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "GameInterface: Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeHorseToDog);
}
void GameInterface::onNextButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer->IsWin())
    {
        QMessageBox m(this);
        m.setWindowTitle("Congratulations!");
        m.setText("You win!!!");
        m.addButton("yep", QMessageBox::AcceptRole);
        m.exec();
    }
    else
    {
        qDebug() << "turn " << game.GetOrder() << " was done";
        game.NextTurn();
        StartGame();
    }
}
void GameInterface::moveEvent(QMoveEvent* event)
{
    game_phase->move(event->pos());
}
const Game& GameInterface::GetGame() const
{
  return game;
}
