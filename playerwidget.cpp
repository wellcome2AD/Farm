#include <QPixmap>
#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(this);
    QPixmap image("D:\\QtProjects\\Farm\\farm_map.png");
    label->setFixedSize(image.size());
    label->setPixmap(image);

    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->addWidget(label);
    setLayout(layout);
}
