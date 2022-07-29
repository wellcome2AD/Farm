#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent, orientationOfMapEnum orientation, Player* player)
    : QWidget(parent),
      image(QPixmap()),
      orientation(orientation),
      player(player)
{
    setFixedSize(380, 388);
    connect(player, SIGNAL(playerUpdated()), this, SLOT(onPlayerUpdate()));
    QString map_path;
    if(orientation == left_side_map)
    {
        map_path = ":/resources/left_farm_map";
    }
    else
    {
        map_path = ":/resources/right_farm_map";
    }
    bool isLoaded = image.load(map_path);
    if(isLoaded == false)
    {
        qDebug() << "image is not loaded";
    }
    resize(400,200);
}
void PlayerWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter1(this);
    QPixmap copy_image = image.scaled(size(), Qt::AspectRatioMode::KeepAspectRatio);
    QPainter painter2(&copy_image);

    size_t text_size = copy_image.width()/32;
    painter2.setFont(QFont("Times", text_size, QFont::Bold));

    if(orientation == left_side_map)
    {
        painter2.drawText(copy_image.width()/16, copy_image.height()/16,     QString::number(player->GetHorses()));
        painter2.drawText(copy_image.width()/16, copy_image.height()*7/16,   QString::number(player->GetCows()));
        painter2.drawText(copy_image.width()/16, copy_image.height()*13/16,  QString::number(player->GetPigs()));
        painter2.drawText(copy_image.width()*3/4, copy_image.height()/8,     QString::number(player->GetDucks()));
        painter2.drawText(copy_image.width()*3/4, copy_image.height()*11/16, QString::number(player->GetGoats()));
    }
    else
    {
        painter2.drawText(copy_image.width()*15/16, copy_image.height()/16,     QString::number(player->GetHorses()));
        painter2.drawText(copy_image.width()*15/16, copy_image.height()*7/16,   QString::number(player->GetCows()));
        painter2.drawText(copy_image.width()*15/16, copy_image.height()*13/16,  QString::number(player->GetPigs()));
        painter2.drawText(copy_image.width()/4, copy_image.height()/8,     QString::number(player->GetDucks()));
        painter2.drawText(copy_image.width()/4, copy_image.height()*11/16, QString::number(player->GetGoats()));
    }

    if(player->GetAntyfoxDog())
    {
        QPixmap antyfox_dog(":/resources/antyfox_dog");
        antyfox_dog = antyfox_dog.scaled(size()/10, Qt::AspectRatioMode::KeepAspectRatio);
        if(orientation == left_side_map)
        {
            painter2.drawPixmap(copy_image.width()*33/64, copy_image.height()*11/32, antyfox_dog);
        }
        else
        {
            painter2.drawPixmap(copy_image.width()*28/64, copy_image.height()*11/32, antyfox_dog);
        }
    }
    if(player->GetAntybearDog())
    {
        QPixmap antybear_dog(":/resources/antybear_dog");
        antybear_dog = antybear_dog.scaled(size()/10, Qt::AspectRatioMode::KeepAspectRatio);
        if(orientation == left_side_map)
        {
            painter2.drawPixmap(copy_image.width()*66/128, copy_image.height()*21/32, antybear_dog);
        }
        else
        {
            painter2.drawPixmap(copy_image.width()*49/128, copy_image.height()*21/32, antybear_dog);
        }
    }
    painter1.drawPixmap(0, 0, copy_image);
}
void PlayerWidget::onPlayerUpdate()
{
    repaint();
}
