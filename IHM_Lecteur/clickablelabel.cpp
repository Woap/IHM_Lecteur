#include "clickablelabel.h"
#include <QTextStream>

ClickableLabel::ClickableLabel(const QString& text, QWidget* parent) : QLabel(parent)
{
   setText(text);
   connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

ClickableLabel::~ClickableLabel() { }

void ClickableLabel::mousePressEvent(QMouseEvent* event) {


    //emit clicked();
}

void ClickableLabel::mouseReleaseEvent ( QMouseEvent * event)
{

    emit clicked();

}

void ClickableLabel::slotClicked()
{
    printf("Clicked");

    QTextStream out(stdout);
    //out << QString("");
}

