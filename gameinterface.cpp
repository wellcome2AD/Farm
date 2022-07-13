#include <QPainter>
#include <QDebug>
#include "gameinterface.h"

GameInterface::GameInterface(QWidget *parent)
    : QWidget       (parent),
      game          (2),
      common_layout (new QVBoxLayout(this)),
      maps_layout   (new QGridLayout),
      buttons_layout(new QHBoxLayout)
{
    QPixmap image = QPixmap("D:\\QtProjects\\Farm\\exchange1");
    QVector<QIcon> icon_for_button({image.scaled(QSize(300, 200), Qt::AspectRatioMode::KeepAspectRatio),
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
    for(int i=0; i<text_for_button.size(); ++i)
    {
        auto button = new ExchangeButton(icon_for_button.at(i), text_for_button.at(i), this);
        buttons_layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, method_ptr.at(i));
    }

    PlayerWidget* plwidget1 = new PlayerWidget(this, left_side_map);
    PlayerWidget* plwidget2 = new PlayerWidget(this, right_side_map);
    maps_layout->addWidget(plwidget1,0,0);
    maps_layout->addWidget(plwidget2,0,1);

    common_layout->addLayout(maps_layout);
    common_layout->addLayout(buttons_layout);
    setLayout(common_layout);
    resize(600,400);
}
GameInterface::~GameInterface()
{
}
/*bool GameInterface::eventFilter(QObject* object, QEvent* event)
{
    if (exch_button == object && event->type() == QEvent::Resize) {
    qDebug() << "button was resized!";
    pushButton->setIconSize( QSize( pushButton->size().width(),
    pushButton->size().height() ));
}*/
void GameInterface::onExchange1ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    int order = game.GetOrder() - 1;
    bool result = currentPlayer->Exchange(changeDucksToGoat);
    QLayoutItem* item = maps_layout->takeAt(order);
    PlayerWidget* widget = (PlayerWidget*)item;
    if(result)
    {
        repaint(0, 0, widget->width(), widget->height());
    }
}
void GameInterface::onExchange2ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    int order = game.GetOrder() - 1;
    bool result = currentPlayer->Exchange(changeGoatsToPig);
    QLayoutItem* item = maps_layout->takeAt(order);
    PlayerWidget* widget = (PlayerWidget*)item;
    if(result)
    {
        repaint(0, 0, widget->width(), widget->height());
    }
}
void GameInterface::onExchange3ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    int order = game.GetOrder() - 1;
    bool result = currentPlayer->Exchange(changePigsToHorse);
    QLayoutItem* item = maps_layout->takeAt(order);
    PlayerWidget* widget = (PlayerWidget*)item;
    if(result)
    {
        repaint(0, 0, widget->width(), widget->height());
    }
}
void GameInterface::onExchange4ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    int order = game.GetOrder() - 1;
    bool result = currentPlayer->Exchange(changeHorsesToCow);
    QLayoutItem* item = maps_layout->takeAt(order);
    PlayerWidget* widget = (PlayerWidget*)item;
    if(result)
    {
        repaint(0, 0, widget->width(), widget->height());
    }
}
void GameInterface::onExchange5ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    int order = game.GetOrder() - 1;
    bool result = currentPlayer->Exchange(changeGoatToDog);
    QLayoutItem* item = maps_layout->takeAt(order);
    PlayerWidget* widget = (PlayerWidget*)item;
    if(result)
    {
        repaint(0, 0, widget->width(), widget->height());
    }
}
void GameInterface::onExchange6ButtonClicked()
{
    Player* currentPlayer = game.GetCurrentPlayer();
    int order = game.GetOrder() - 1;
    bool result = currentPlayer->Exchange(changeHorseToDog);
    QLayoutItem* item = maps_layout->takeAt(order);
    PlayerWidget* widget = (PlayerWidget*)item;
    if(result)
    {
        repaint(0, 0, widget->width(), widget->height());
    }

}
