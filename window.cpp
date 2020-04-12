#include "GDrawler/displaywidget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>


Window::Window()
{
    setWindowTitle(tr("CNC Control"));
    resize(600, 600);

    DisplayWidget *wg = new DisplayWidget(&helper, this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(wg, 0, 0, 1, 3);
    setLayout(layout);

//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, native, &Widget::animate);
//    connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
//    timer->start(10);
}
