#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class ClickableLabel : public QLabel { Q_OBJECT
public:

    explicit ClickableLabel( const QString& text="", QWidget* parent=0 );
   ~ClickableLabel();
    int value=0;

signals:

   void clicked();
   void clicked(int value);
protected:

   void mousePressEvent(QMouseEvent* event);
   void mouseReleaseEvent(QMouseEvent* event);


public slots:
   void slotClicked();
};

#endif // CLICKABLELABEL_H
