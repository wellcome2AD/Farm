#include "gameinterface.h"

GameInterface::GameInterface(QWidget *parent)
    : QWidget(parent), game(2), plwidget(new PlayerWidget(this))
{
    common_layout = new QVBoxLayout(this);
    maps_layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    buttons_layout = new QHBoxLayout(this);

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
    for(int i=0; i<text_for_button.size(); ++i)
    {
        auto button = new ExchangeButton(text_for_button.at(i), this);
        buttons_layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, method_ptr.at(i));
    }

    maps_layout->addWidget(plwidget);
    common_layout->addLayout(maps_layout);
    common_layout->addLayout(buttons_layout);

    //setLayout(common_layout);
}
GameInterface::~GameInterface()
{
}
void GameInterface::onExchange1ButtonClicked()
{

}
void GameInterface::onExchange2ButtonClicked()
{

}
void GameInterface::onExchange3ButtonClicked()
{

}
void GameInterface::onExchange4ButtonClicked()
{

}
void GameInterface::onExchange5ButtonClicked()
{

}
void GameInterface::onExchange6ButtonClicked()
{

}
