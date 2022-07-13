#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QPaintEvent>
#include "player.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
    Player* player;
protected:
    void paintEvent(QPaintEvent* event) override;
public:
    explicit PlayerWidget(QWidget *parent = nullptr);
signals:

};

#endif // PLAYERWIDGET_H
