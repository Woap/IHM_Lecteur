#include "clickablelabel.h"
#include <QTextStream>
#include <QDebug>
#include <QMouseEvent>


ClickableLabel::ClickableLabel(const QString& text, QWidget* parent) : QLabel(parent)
{
   setText(text);
   connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

ClickableLabel::~ClickableLabel() { }

void ClickableLabel::mousePressEvent(QMouseEvent* event) {

    //ClickableLabel *widget =(ClickableLabel*) qApp->widgetAt(QCursor::pos());
    qDebug() << "Value";
    qDebug() << value;
    emit clicked(value);
}

void ClickableLabel::mouseReleaseEvent ( QMouseEvent * event)
{
    emit clicked(1);
    emit clicked();
}



void ClickableLabel::slotClicked()
{
    printf("Clicked");

    QTextStream out(stdout);
    //out << QString("");
}

