#include "displaywidget.h"
#include "helper.h"

#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMouseEvent>

//! [0]
DisplayWidget::DisplayWidget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    elapsed = 0;
//    resize(600, 600);
    setAutoFillBackground(false);
    setMouseTracking(true);
}
//! [0]

//! [1]
void DisplayWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}
//! [1]

//! [2]
void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}

void DisplayWidget::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta() ;

    if (!delta.isNull()) {
        helper->changeScale(delta.y(), event->pos());
    }
    event->accept();
    update();
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint lastPos;

    if (event->buttons() & Qt::LeftButton)
        helper->changeZeroPos(event->pos() - lastPos);
    update();

    lastPos = event->pos();
    event->accept();
}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    drag = true;
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    drag = false;
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

//! [2]
