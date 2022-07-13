#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    resize(1000, 300);
    qDebug() << width() << ' ' << height();
    update();
    show();
}
void PlayerWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPixmap image;
    bool isLoaded = image.load("D:\\QtProjects\\Farm\\left_farm_map.png");
    if(isLoaded == false)
        qDebug() << "image is not loaded";
    QPainter painter(this);
    qDebug() << width() << ' ' << height();
    painter.drawPixmap(0,0, image.scaled(size(), Qt::AspectRatioMode::KeepAspectRatio));
    painter.setFont(QFont("Times", 25, QFont::Normal));
    painter.drawText(0,0, QString("TEST"));
}
