#include "GDrawler/helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <iostream>

#include "GStreamer/GSerialStream/Serial.h"
#include "GPacker/PacketCreator.h"

//! [0]
Helper::Helper()
{
    background = QBrush(QColor(255, 255, 255));
    scale = 20000000.0 / DRAW_PRE_SCALE / static_cast<int>(FLOAT_TO_INT_PERSITION);
    zeroPos = QPoint(300, 300);

    GParser parser("D:\\Projects\\HW\\Project_207b\\CNC_V1\\input.txt");
    parser.parse();
    parser.normalize();
    codes = parser.getCodes();

    PacketCreator pac;
    Serial ser;
    ser.open("COM3", 9600);
    ser.close();
    ser.open("COM3", 9600);

    std::cout<< "here1" << std::endl;
    Sleep(1000);


    int i = 0, c;
    foreach (auto code, codes) {
        GPacket p = pac.create(code);

//        cout << p.xDist << " " << p.yDist << " " <<p.zDist << " " << p.xVel << " " << p.yVel << " " <<p.zVel <<  endl;
//        if (i == 30) break;

        ser << p;
        string sss;
        while(!(ser.try_read(sss))){
            Sleep(100);
            //cout << '.' << endl;
        }

        std::cout<< "out: " << i << " - " << sss << std::endl;
        ++i;

        Sleep(100);

    }
    cout << i << endl;

}
//! [0]

//! [1]
void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    painter->translate(zeroPos);
//! [1]

//! [2]
    painter->save();

    QPen drill = QPen(QColor(96, 96, 255));
    QPen black = QPen(QColor(96, 96, 96));
    QPen move  = QPen(QColor(255, 255, 0, 160));
    drill.setWidth(2);
    black.setWidth(2);
    move.setWidth(2);

    QPoint lastCoords = QPoint(0, 0);
    foreach (GCode code, codes) {
        code *= DRAW_PRE_SCALE;
        QPoint newCoords(code.x / scale, - code.y / scale);

        if(code.opcode == 1 && code.mx == 1){
            painter->setPen(drill);
            painter->drawLine(lastCoords, newCoords);
            lastCoords = newCoords;
        }

        if(code.opcode == 0 && code.mx == 1){
            painter->setPen(move);
            painter->drawLine(lastCoords, newCoords);
            lastCoords = newCoords;
        }

    }

    painter->restore();
//! [2]

//! [3]
      painter->setPen(black);
      painter->drawLine(QPoint(0, 0), QPoint(0, -1000000 / scale));
      painter->drawLine(QPoint(0, 0), QPoint(1000000 / scale, 0));
}

qreal Helper::getScale()
{
    return this->scale;
}

void Helper::changeScale(int change, QPoint relative)
{
    qreal oldScale = scale;
    qreal newScale = scale - SCALE_CHANGE * change;

    if(newScale > 100) scale = newScale;

    zeroPos = (zeroPos - relative) * (oldScale / scale) + relative;
}

QPoint Helper::getZeroPos() const
{
    return zeroPos;
}

void Helper::changeZeroPos(QPoint change)
{
    zeroPos = zeroPos + change;
}
//! [3]
