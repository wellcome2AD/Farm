#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include "gameinterface.h"

GameInterface::GameInterface(QWidget *parent)
    : QWidget       (parent),
      game          (4),
      common_layout (new QVBoxLayout(this)),
      maps_layout   (new QGridLayout),
      buttons_layout(new QHBoxLayout)
{
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

    QPushButton* skip_button = new QPushButton(this);
    size_t skip_text_size = skip_button->width()/10 + 3;
    skip_button->setFont(QFont("Times", skip_text_size, QFont::Bold));
    skip_button->setText("Skip exchange");
    connect(skip_button, &QPushButton::clicked, this, &GameInterface::onSkipButtonClicked);

    QPushButton* next_button = new QPushButton(this);
    size_t next_text_size = next_button->width()/10 + 3;
    next_button->setFont(QFont("Times", next_text_size, QFont::Bold));
    next_button->setText("Next turn");
    connect(next_button, &QPushButton::clicked, this, &GameInterface::onNextButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(skip_button);
    layout->addWidget(next_button);
    buttons_layout->addLayout(layout);
    buttons_layout->setAlignment(layout, Qt::AlignJustify);

    auto list_of_players = game.GetListOfPlayers();
    for(int i=0; i < list_of_players.size()/2; ++i)
    {
        PlayerWidget* left_plwidget = new PlayerWidget(this, left_side_map, list_of_players.at(i));
        PlayerWidget* right_plwidget = new PlayerWidget(this, right_side_map, list_of_players.at(i+2));
        qDebug() << "Players " << i << " and " << i+2 << " were created";
        maps_layout->addWidget(left_plwidget, i, 0);
        maps_layout->addWidget(right_plwidget, i, 1);
    }

    buttons_layout->setContentsMargins(2, 0, 2, 0);
    common_layout->setContentsMargins(0, 1, 0, 1);
    common_layout->addLayout(maps_layout);
    common_layout->addLayout(buttons_layout);
    common_layout->setAlignment(buttons_layout, Qt::AlignCenter);
    setLayout(common_layout);
    setFixedSize(770, 856);
}
GameInterface::~GameInterface()
{
}
void GameInterface::StartGame()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    if(!currentPlayer->IsWin())
    {
        currentPlayer->FirstStage();
        qDebug() << "turn " << game.GetOrder() << " was done";
    }
}
void GameInterface::onExchange1ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeDucksToGoat);
}
void GameInterface::onExchange2ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeGoatsToPig);
}
void GameInterface::onExchange3ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changePigsToHorse);
}
void GameInterface::onExchange4ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeHorsesToCow);
}
void GameInterface::onExchange5ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeGoatToDog);
}
void GameInterface::onExchange6ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    currentPlayer->Exchange(changeHorseToDog);
}
void GameInterface::onSkipButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    if(currentPlayer == nullptr)
    {
        qDebug() << "Can't get player " + QString::number(game.GetOrder());
        return;
    }
    if(currentPlayer->IsWin())
    {
        QMessageBox m(this);
        m.setWindowTitle("Congratulations!");
        m.setText("You win!!!");
        m.exec();
    }
    else
    {
        onNextButtonClicked();
    }
}
void GameInterface::onNextButtonClicked()
{
    game.NextTurn();
    /*QMessageBox m(this);
    m.setWindowTitle("Next turn");
    QString string = "Player's " + QString::number(game.GetOrder()) + " turn";
    m.setText(string);
    m.exec();*/
    StartGame();
}

const Game& GameInterface::GetGame() const
{
  return game;
}
