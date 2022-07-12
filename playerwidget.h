#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include "player.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
    //Player* player;
    QLabel* label;
    QBoxLayout* map_layout;
public:
    explicit PlayerWidget(QWidget *parent = nullptr);

signals:

};

#endif // PLAYERWIDGET_H
