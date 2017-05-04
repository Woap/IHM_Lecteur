/**
 * \file clickablelabel.cpp
 * \author CHIBOUT Yanis et IBIS Ibrahim
 *
 * Aud.io lecteur audio pour mpv
 * Label personnalisé permettant le clic
 */

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
    emit clicked(value);
}

void ClickableLabel::mouseReleaseEvent ( QMouseEvent * event)
{
    emit clicked(1);
    emit clicked();
}


// Fonction de debug
void ClickableLabel::slotClicked()
{
    printf("Clicked");
    QTextStream out(stdout);
}

