#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

//! [0]
class Helper;

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(Helper *helper, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private:
    Helper *helper;
    int elapsed;
    bool drag;
};
//! [0]

#endif
