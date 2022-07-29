#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "gamephasewidget.h"

void labelFadeAnimation(QLabel* label, const QVariant& start_value, const QVariant& end_value, int duration);

GamePhaseWidget::GamePhaseWidget(QWidget *parent)
    : QWidget(parent),
      layout(new QVBoxLayout(this))
{    
    QPoint parent_center(parent->x() + parent->width() / 2 - 80, parent->y() + parent->height() / 2 + 120);
    qDebug() << parent_center;
    move(parent_center);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    QLabel* label = new QLabel(this);
    size_t text_size = parent->width() / 20;
    label->setFont(QFont("Times", text_size, QFont::Bold));
    label->setText(phase_text.at(current_phase));
    label->setAutoFillBackground(true);
    layout->addWidget(label, Qt::AlignHCenter);
    setLayout(layout);

    labelFadeAnimation(label, 0.0, 1.0, 500);
    QTimer::singleShot(4000, this, [label]{labelFadeAnimation(label, 1.0, 0.0, 500);});
}
void labelFadeAnimation(QLabel* label, const QVariant& start_value, const QVariant& end_value, int duration)
{
    QPropertyAnimation* anim = new QPropertyAnimation(label);
    QGraphicsOpacityEffect* grEffect = new QGraphicsOpacityEffect(label);
    label->setGraphicsEffect(grEffect);

    anim->setTargetObject(grEffect);
    anim->setPropertyName("opacity");
    anim->setStartValue(start_value);
    anim->setEndValue(end_value);
    anim->setDuration(duration);
    anim->start();
}
void GamePhaseWidget::NextPhase()
{
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
    layout->addWidget(label);
    labelFadeAnimation(label, 0.0, 1.0, 500);
    QTimer::singleShot(2000, this, [label]{labelFadeAnimation(label, 1.0, 0.0, 500);});
}
