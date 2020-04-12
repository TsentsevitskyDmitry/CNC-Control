#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "GParser/gparser.h"

const qreal SCALE_CHANGE = 1;

//! [0]
class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    qreal getScale();
    void changeScale(int change, QPoint senter);
    QPoint getZeroPos() const;
    void changeZeroPos(QPoint change);

private:
    QBrush background;
    QPoint zeroPos;
    qreal scale;
    QVector<GCode> codes;
};
//! [0]

#endif
