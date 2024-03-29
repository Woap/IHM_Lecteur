/**
 * \file mainwindow.h
 * \author CHIBOUT Yanis et IBIS Ibrahim
 *
 * Aud.io lecteur audio pour mpv
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clickablelabel.h>
#include "serveur.h"
#include <QSlider>
#include <QMessageBox>
#include <QListWidget>

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
    bool radio_on=false;

    QSlider *test8;
    QMutex mutex;
    ClickableLabel *test4;
    ClickableLabel *shuffle;
    ClickableLabel *back;
    ClickableLabel *fastback;
    ClickableLabel *fast;
    ClickableLabel *next;
    ClickableLabel *fm;
    ClickableLabel *audio;
    ClickableLabel *audio_slider;
    ClickableLabel *menu;

    QSlider *progressbar;
    QLabel *tempsactuel;
    QLabel *duration;
    QListWidget *listwidget;


private slots:
    void changer_mode();
    void play_pause(QWidget *wid);
    void switchmode();
    void event_previous();
    void event_next();
    void event_radio();
    void event_seek(int value);
    void onListSongItemClicked(QListWidgetItem* item );
    void event_shuffle();
    void test8_sliderMoved(int position);
    void test8_event_volume(int position);
    void test7_event_volume();
    void test7_event_mute(bool value);
    void progressbar_event_progress(int position);
    void test4_etatchanged(bool value);
    void tempsactuel_event_temps(int temps);
    void metadata_event(QString title, QString artist);
    void metadataradio_event(QString title, QString artist,QString radio);
    void sliderProgressMoved(int position);
    void set_duration(int temps);
    void set_cover(QString filename);
    void set_speed(int value);
    void start();


private:
    Ui::MainWindow *ui;
    Serveur *serveur;
};



#endif // MAINWINDOW_H
