#ifndef GAMEPHASEWIDGET_H
#define GAMEPHASEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QString>

class GamePhaseWidget : public QWidget
{
    Q_OBJECT
    QLabel* label;
    QLabel* dice1,* dice2;
    const QVector<QString> phase_text{"DICE THROW", "EXCHANGE"};
    size_t current_phase;
private:
    void labelFadeAnimation(QLabel* label, const QVariant& start_value, const QVariant& end_value, int duration);
public:
    explicit GamePhaseWidget(QWidget *parent = nullptr);
    void NextPhase();
};

#endif // GAMEPHASEWIDGET_H
