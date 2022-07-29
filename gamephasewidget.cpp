#include <QLabel>
#include <QDebug>
#include <QTimer>
#include "gamephasewidget.h"

GamePhaseWidget::GamePhaseWidget(QWidget *parent)
    : QWidget(parent)//,
      //layout(new QVBoxLayout(this))
{    
    QPoint parent_center(parent->x() + parent->width() / 2 - 80, parent->y() + parent->height() / 2 + 100);
    qDebug() << parent_center;

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    QLabel* label = new QLabel(this);
    label->move(parent_center);
    size_t text_size = parent->width() / 20;
    label->setFont(QFont("Times", text_size, QFont::Bold));
    label->setText(phase_text.at(current_phase));
    label->setAutoFillBackground(true);
    //label->resize(300, 80);
    //layout->addWidget(label, Qt::AlignHCenter);
    //setLayout(layout);

    QTimer::singleShot(6000, label, &QLabel::hide);
}
void GamePhaseWidget::NextPhase()
{
    //QTimer::singleShot(2000, game_phase->hide());
    QLayoutItem* item = layout->takeAt(0);
    if(item == nullptr)
    {
        qDebug() << "GamePhaseWidget: Can't get an item from layout";
        return;
    }
    auto label = qobject_cast<QLabel*>(item->widget());
    if(label == nullptr)
    {
        qDebug() << "GamePhaseWidget: Can't get a label from item";
        return;
    }
    current_phase = (current_phase + 1) % phase_text.size();
    label->setText(phase_text.at(current_phase));
}
