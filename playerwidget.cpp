#include <QPixmap>
#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(this);
    QPixmap image("D:\\QtProjects\\Farm\\farm_map.jpg");
    label->setPixmap(image.scaled(QSize(600, 400), Qt::AspectRatioMode::KeepAspectRatio));
    //label->resize(image.size());
    label->setScaledContents(true);

    map_layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    map_layout->addWidget(label);
    setLayout(map_layout);
}
