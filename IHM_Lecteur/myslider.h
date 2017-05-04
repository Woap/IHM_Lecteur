#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QObject>
#include <QWidget>
#include <QSlider>

class MySlider : public QSlider
{
    Q_OBJECT
public:
    explicit MySlider(QWidget *parent = 0);
    explicit MySlider(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent* event);
    //void mouseReleaseEvent(QMouseEvent* event);
};

#endif // MYSLIDER_H
