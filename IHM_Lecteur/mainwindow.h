#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clickablelabel.h>
#include "serveur.h"
#include <QSlider>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int minimal;

    QSlider *test8;
    ClickableLabel *test4;
    QSlider *progressbar;
    QLabel *tempsactuel;
    QLabel *duration;
    ClickableLabel *test7;


private slots:
    void changer_mode();
    void play_pause(QWidget *wid);

    void event_previous();
    void event_next();
    void event_seek(int value);
    void event_shuffle();
    void on_test8_sliderMoved(int position);
    void on_test8_event_volume(int position);
    void on_test7_event_volume();
    void on_test7_event_mute(bool value);
    void on_progressbar_event_progress(int position);
    void on_test4_etatchanged(bool value);
    void on_tempsactuel_event_temps(int temps);
    void on_metadata_event(QString title, QString artist);
    void sliderProgressMoved(int position);
    void set_duration(int temps);
    void set_cover(QString filename);
    void set_speed(int value);


private:
    Ui::MainWindow *ui;
    Serveur *serveur;
};



#endif // MAINWINDOW_H
