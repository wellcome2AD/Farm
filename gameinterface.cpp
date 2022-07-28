#include <QPainter>
#include <QDebug>
#include "gameinterface.h"

GameInterface::GameInterface(QWidget *parent)
    : QWidget       (parent),
      game          (4),
      common_layout (new QVBoxLayout(this)),
      maps_layout   (new QGridLayout),
      buttons_layout(new QHBoxLayout)
{
    //setFixedSize(800,457);
    QVector<QIcon> icon_for_button({QPixmap("D:\\QtProjects\\Farm\\exchange1.png"),
                                    QPixmap("D:\\QtProjects\\Farm\\exchange2"),
                                    QPixmap("D:\\QtProjects\\Farm\\exchange3"),
                                    QPixmap("D:\\QtProjects\\Farm\\exchange4"),
                                    QPixmap("D:\\QtProjects\\Farm\\exchange5"),
                                    QPixmap("D:\\QtProjects\\Farm\\exchange6")});
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
    QPushButton* next_button = new QPushButton(this);
    //skip_button->resize(100,40);
    size_t text_size = skip_button->width()/10 + 3;
    skip_button->setFont(QFont("Times", text_size, QFont::Bold));
    skip_button->setText("Skip exchange");
    next_button->setFont(QFont("Times", text_size, QFont::Bold));
    next_button->setText("Next turn");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(skip_button);
    layout->addWidget(next_button);
    buttons_layout->addLayout(layout);
    buttons_layout->setAlignment(layout, Qt::AlignJustify);

    auto list_of_players = game.GetListOfPlayers();
    for(int i=0; i<list_of_players.size()/2; ++i)
    {
        PlayerWidget* left_plwidget = new PlayerWidget(this, left_side_map, list_of_players.at(i));
        PlayerWidget* right_plwidget = new PlayerWidget(this, right_side_map, list_of_players.at(i+1));
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
void GameInterface::Turn()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    bool result = currentPlayer->FirstStage();
    if(result)
    {
        qDebug() << game.GetOrder() << " turn";
    }
}
void GameInterface::repaintCurrentPlayer()
{
    int order = game.GetOrder();
    QLayoutItem* item = maps_layout->takeAt(order);
    PlayerWidget* widget = qobject_cast<PlayerWidget*>(item->widget());
    if(widget == nullptr)
    {
        qDebug() << "Item from map_layout isn't PlayerWidget";
    }
    else
    {
        widget->repaint();
    }
}
void GameInterface::onExchange1ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    bool result = currentPlayer->Exchange(changeDucksToGoat);
    if(result)
    {
        repaintCurrentPlayer();
    }
}
void GameInterface::onExchange2ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    bool result = currentPlayer->Exchange(changeGoatsToPig);
    if(result)
    {
        repaintCurrentPlayer();
    }
}
void GameInterface::onExchange3ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    bool result = currentPlayer->Exchange(changePigsToHorse);
    if(result)
    {
        repaintCurrentPlayer();
    }
}
void GameInterface::onExchange4ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    bool result = currentPlayer->Exchange(changeHorsesToCow);
    if(result)
    {
        repaintCurrentPlayer();
    }
}
void GameInterface::onExchange5ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    bool result = currentPlayer->Exchange(changeGoatToDog);
    if(result)
    {
        repaintCurrentPlayer();
    }
}
void GameInterface::onExchange6ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    bool result = currentPlayer->Exchange(changeHorseToDog);
    if(result)
    {
        repaintCurrentPlayer();
    }
}
