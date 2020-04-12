/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <iostream>

//! [0]
Helper::Helper()
{
    background = QBrush(QColor(255, 255, 255));
    scale = 20000000.0 / FLOAT_TO_INT_PERSITION;
    zeroPos = QPoint(300, 300);

    GParser parser("D:\\Projects\\HW\\Project_207b\\CNC_V1\\input.txt");
    parser.parse();
    parser.normalize();
    codes = parser.getCodes();
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
