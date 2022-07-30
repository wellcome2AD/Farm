#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "gamephasewidget.h"
#include "dicegenerator.h"

void labelFadeAnimation(QLabel* label, const QVariant& start_value, const QVariant& end_value, int duration);

GamePhaseWidget::GamePhaseWidget(QWidget *parent)
    : QWidget(parent),
      label(new QLabel(this)),
      dice1(new QLabel(this)),
      dice2(new QLabel(this)),
      current_phase(-1)
{    
    QPoint parent_center(parent->x() + parent->width() / 2 - 80, parent->y() + parent->height() / 2 + 120);
    qDebug() << parent_center;
    //move(parent_center);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* dice_layout = new QHBoxLayout;

    size_t text_size = parent->width() / 20;
    label->setMaximumHeight(50);
    label->setFont(QFont("Times", text_size, QFont::Bold));
    label->setText("GAME STARTS");
    label->setAutoFillBackground(true);
    label->show();

    dice_layout->addWidget(dice1);
    dice_layout->addWidget(dice2);
    layout->addWidget(label, Qt::AlignHCenter);
    layout->addLayout(dice_layout, Qt::AlignHCenter);

    setLayout(layout);
}
void GamePhaseWidget::labelFadeAnimation(QLabel* label, const QVariant& start_value, const QVariant& end_value, int duration)
{
    QPropertyAnimation* anim = new QPropertyAnimation(label);
    QGraphicsOpacityEffect* grEffect = new QGraphicsOpacityEffect(label);
    (label)->setGraphicsEffect(grEffect);

    anim->setTargetObject(grEffect);
    anim->setPropertyName("opacity");
    anim->setStartValue(start_value);
    anim->setEndValue(end_value);
    anim->setDuration(duration);
    anim->start();
}
void GamePhaseWidget::NextPhase()
{
    current_phase = (current_phase + 1) % phase_text.size();
    label->setText(phase_text.at(current_phase));
    qDebug() << current_phase << " " << phase_text.at(current_phase);

    labelFadeAnimation(label, 0.0, 1.0, 500);
    QTimer::singleShot(2000, [this]{ labelFadeAnimation(label, 1.0, 0.0, 500); });
    if(current_phase == 0)
    {
        DiceGenerator::GetDice().ThrowDice();
        auto pair_of_animals = DiceGenerator::GetDice().GetResult();

        QString file_path1(":/resources/dice_" + animalEnumToQString(pair_of_animals.first));
        QString file_path2(":/resources/dice_" + animalEnumToQString(pair_of_animals.second));
        QPixmap dice1_pic(file_path1);
        QPixmap dice2_pic(file_path2);
        dice1->setPixmap(dice1_pic.scaled(150, 150, Qt::AspectRatioMode::KeepAspectRatio));
        dice2->setPixmap(dice2_pic.scaled(150, 150, Qt::AspectRatioMode::KeepAspectRatio));

        labelFadeAnimation(dice1, 0.0, 1.0, 500);
        labelFadeAnimation(dice2, 0.0, 1.0, 500);
        QTimer::singleShot(2000, [this]{ labelFadeAnimation(dice1, 1.0, 0.0, 500), labelFadeAnimation(dice2, 1.0, 0.0, 500); });
    }
}
size_t GamePhaseWidget::GetCurrentPhase()
{
    return current_phase;
}
