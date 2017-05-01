#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clickablelabel.h>
#include "serveur.h"
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSlider *test8;
    ClickableLabel *test4;
    QSlider *progressbar;


private slots:
    void changer_mode();
    void play_pause(QWidget *wid);


    void on_test8_sliderMoved(int position);
    void on_test8_event_volume(int position);
    void on_progressbar_event_progress(int position);
    void on_test4_etatchanged(bool value);

private:
    Ui::MainWindow *ui;
    Serveur *serveur;
};



#endif // MAINWINDOW_H
