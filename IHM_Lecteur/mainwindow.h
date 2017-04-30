#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clickablelabel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changer_mode();
    void play_pause(QWidget *wid);


private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
