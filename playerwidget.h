#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QPair>
#include <QBoxLayout>
#include <QPaintEvent>
#include "player.h"
#include "orientationOfMapEnum.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
    QPixmap image;
    orientationOfMapEnum orientation;
    Player* player;
protected:
    void paintEvent(QPaintEvent* event) override;
public:
    explicit PlayerWidget(QWidget *parent = nullptr, orientationOfMapEnum orientation = left_side_map);
    bool foo();
signals:

};

#endif // PLAYERWIDGET_H
