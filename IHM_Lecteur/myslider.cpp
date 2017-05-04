#include "myslider.h"

#include <QStyleOptionSlider>
#include <QToolTip>
#include <QMouseEvent>

MySlider::MySlider(QWidget * parent)
    : QSlider(parent)
{
    this->setMinimum(1);
    this->setMaximum(100);
}

MySlider::MySlider(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void MySlider::mousePressEvent ( QMouseEvent * event )
  {
    QStyleOptionSlider opt;
      initStyleOption(&opt);
      QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);


      if (event->button() == Qt::LeftButton && sr.contains(event->pos()) == false)
      {
        int newVal;
        if (orientation() == Qt::Vertical)
           newVal = minimum() + ((maximum()-minimum()) * (height()-event->y())) / height();
        else
           newVal = minimum() + ((maximum()-minimum()) * event->x()) / width();

        if (invertedAppearance() == true)
            setValue( maximum() - newVal );
        else
            setValue(newVal);

        event->accept();
        emit sliderMoved(newVal);
      }

      QSlider::mousePressEvent(event);

  }


