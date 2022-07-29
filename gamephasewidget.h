#ifndef GAMEPHASEWIDGET_H
#define GAMEPHASEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QString>

class GamePhaseWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout* layout;
    const QVector<QString> phase_text{"DICE THROW", "EXCHANGE", "ARE YOU WINNING SON?", "NEXT PLAYER"};
    size_t current_phase = 0;
public:
    explicit GamePhaseWidget(QWidget *parent = nullptr);
    void NextPhase();
};

#endif // GAMEPHASEWIDGET_H
