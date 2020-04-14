#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "GParser/GParser.h"

const qreal SCALE_CHANGE = 1;
const int DRAW_PRE_SCALE = 10000 / static_cast<int>(FLOAT_TO_INT_PERSITION);

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

#endif
