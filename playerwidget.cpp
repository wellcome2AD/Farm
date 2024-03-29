#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include "playerwidget.h"
#include "gameinterface.h"
#include "dicegenerator.h"

PlayerWidget::PlayerWidget(QWidget *parent, orientationOfMapEnum orientation, Player* player)
    : QWidget(parent),
      image(QPixmap()),
      orientation(orientation),
      player(player)
{
    coefficents.insert("left_side_map horse", QPointF(1.0/16, 1.0/16));
    coefficents.insert("left_side_map cow",   QPointF(1.0/16, 7.0/16));
    coefficents.insert("left_side_map pig",   QPointF(1.0/16, 13.0/16));
    coefficents.insert("left_side_map duck",  QPointF(3.0/4, 1.0/8));
    coefficents.insert("left_side_map goat",  QPointF(3.0/4, 11.0/16));
    coefficents.insert("left_side_map antyfox_dog", QPointF(33.0/64, 11.0/32));
    coefficents.insert("left_side_map antybear_dog", QPointF(66.0/128, 21.0/32));

    coefficents.insert("right_side_map horse", QPointF(15.0/16, 1.0/16));
    coefficents.insert("right_side_map cow",   QPointF(15.0/16, 7.0/16));
    coefficents.insert("right_side_map pig",   QPointF(15.0/16, 13.0/16));
    coefficents.insert("right_side_map duck",  QPointF(1.0/4, 1.0/8));
    coefficents.insert("right_side_map goat",  QPointF(1.0/4, 11.0/16));
    coefficents.insert("right_side_map antyfox_dog", QPointF(28.0/64, 11.0/32));
    coefficents.insert("right_side_map antybear_dog", QPointF(49.0/128, 21.0/32));

    setFixedSize(380, 388);
    connect(player, SIGNAL(playerUpdated()), this, SLOT(onPlayerUpdate()));
    QString map_path(":/resources/" + orientationOfMapEnumToQString(orientation));
    bool isLoaded = image.load(map_path);
    if(isLoaded == false)
    {
        qDebug() << "PlayerWidget: map is not loaded";
    }
    resize(400,200);
}
void PlayerWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPixmap copy_image = image.scaled(size(), Qt::AspectRatioMode::KeepAspectRatio);
    resize(copy_image.size());
    QPainter painter1(this);
    QPainter painter2(&copy_image);

    auto gameInterface = qobject_cast<GameInterface*>(parent());
    auto cur_player = gameInterface->GetCurrentPlayer();
    if (gameInterface == nullptr)
    {
        qDebug() << "PlayerWidget: can't convert parent to GameInterface*";
        return;
    }

    QString orientaion_string = orientationOfMapEnumToQString(orientation);
    QMap<animalEnum, int> animals= player->GetAnimals();
    animalEnum array[] = {duck, goat, pig, horse, cow};
    auto changed_animals = DiceGenerator::GetDice().GetResult();
    for(int i = 0; i < animals.size(); ++i)
    {
        animalEnum animal = array[i];
        if((animal == changed_animals.first || animal == changed_animals.second) && cur_player == player && gameInterface->GetCurrentPhase() == 0)
        {
            size_t text_size = copy_image.width()/20;
            painter2.setFont(QFont("Times", text_size, QFont::Bold));
            painter2.setPen(Qt::red);
        }
        else
        {
            size_t text_size = copy_image.width()/32;
            painter2.setFont(QFont("Times", text_size, QFont::Bold));
            painter2.setPen(Qt::black);
        }
        QString animal_string = animalEnumToQString(animal);
        QPointF coeff = coefficents[orientaion_string + ' ' + animal_string];
        int x = copy_image.width() * coeff.x();
        int y = copy_image.height() * coeff.y();
        painter2.drawText(x, y, QString::number(animals[animal]));
    }

    if(player->GetAntyfoxDog())
    {
        QPixmap antyfox_dog(":/resources/antyfox_dog");
        antyfox_dog = antyfox_dog.scaled(size()/10, Qt::AspectRatioMode::KeepAspectRatio);
        QPointF coeff = coefficents[orientaion_string + " antyfox_dog"];
        int x = copy_image.width() * coeff.x();
        int y = copy_image.height() * coeff.y();
        painter2.drawPixmap(x, y, antyfox_dog);
    }
    if(player->GetAntybearDog())
    {
        QPixmap antybear_dog(":/resources/antybear_dog");
        antybear_dog = antybear_dog.scaled(size()/10, Qt::AspectRatioMode::KeepAspectRatio);
        QPointF coeff = coefficents[orientaion_string + " antybear_dog"];
        int x = copy_image.width() * coeff.x();
        int y = copy_image.height() * coeff.y();
        painter2.drawPixmap(x, y, antybear_dog);
    }

    painter1.drawPixmap(0, 0, copy_image);

    if(cur_player == player)
    {
       constexpr int thickness = 4;
       painter1.setPen(QPen(Qt::red, thickness));
       painter1.drawRect(0 + thickness / 2, 0 + thickness / 2, width() - thickness, height() - thickness);
    }
}
void PlayerWidget::onPlayerUpdate()
{
    repaint();
}
