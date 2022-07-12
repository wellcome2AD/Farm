#include "gameinterface.h"

GameInterface::GameInterface(QWidget *parent)
    : QWidget(parent), game(2), plwidget(new PlayerWidget(this))
{
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->addWidget(plwidget);
    setLayout(layout);
}

GameInterface::~GameInterface()
{
}
