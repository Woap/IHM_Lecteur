/**
 * \file mainwindow.cpp
 * \author CHIBOUT Yanis et IBIS Ibrahim
 *
 * Aud.io lecteur audio pour mpv
 * Gestion de l'UI, reception des events, envoie des commandes
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QTextStream>
#include <QSignalMapper>
#include <QLocalServer>
#include "serveur.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serveur(new Serveur)
{
    ui->setupUi(this);


    this->statusBar()->setSizeGripEnabled(false);
    minimal = 1;
    tempsactuel = ui->tempsactuel;
    progressbar = ui->progressbar;
    duration = ui->duration;
    listwidget = ui->listwidget;



    ui->cover->setScaledContents(true);

    // Boutons
    ClickableLabel* test = new ClickableLabel("MY LABEL",this);
    test->setGeometry(10,200,61,61);
    test->setPixmap(QPixmap(":/img/shuffle.png"));
    shuffle = test;

    ClickableLabel* test2 = new ClickableLabel("MY LABEL",this);
    test2->setGeometry(160,200,61,61);
    test2->setPixmap(QPixmap(":/img/back.png"));

    ClickableLabel* test3 = new ClickableLabel("MY LABEL",this);
    test3->setGeometry(220,200,61,61);
    test3->setPixmap(QPixmap(":/img/fastback.png"));
    test3->value = -3;
    fastback = test3;

    test4 = new ClickableLabel("MY LABEL",this);
    test4->setGeometry(290,200,61,61);
    test4->setPixmap(QPixmap(":/img/stop.png"));

    ClickableLabel* test5 = new ClickableLabel("MY LABEL",this);
    test5->setGeometry(350,200,61,61);
    test5->setPixmap(QPixmap(":/img/fast.png"));
    test5->value = 3;
    fast=test5;

    ClickableLabel* test6 = new ClickableLabel("MY LABEL",this);
    test6->setGeometry(410,200,61,61);
    test6->setPixmap(QPixmap(":/img/next.png"));

    fm = new ClickableLabel("MY LABEL",this);
    fm->setGeometry(750,30,61,61);
    fm->setPixmap(QPixmap(":/img/fm_off.png"));

    audio = new ClickableLabel("MY LABEL",this);
    audio->setGeometry(510,200,61,61);
    audio->setPixmap(QPixmap(":/img/audio.png"));
    audio->setObjectName("unmute");

    test8 = new MySlider(this);
    test8->setOrientation(Qt::Horizontal);
    test8->setGeometry(580,215,131,29);




    ClickableLabel* test9 = new ClickableLabel("MY LABEL",this);
    test9->setGeometry(720,200,61,61);
    test9->setPixmap(QPixmap(":/img/menu.png"));

    menu = test9;



    // INIT MPV DONNEES
    QObject::connect(serveur, SIGNAL(volumechanged(int)), this, SLOT(test8_event_volume(int))) ;
    QObject::connect(serveur, SIGNAL(progressionchanged(int)), this, SLOT(progressbar_event_progress(int))) ;
    QObject::connect(serveur, SIGNAL(etatchanged(bool)), this, SLOT(test4_etatchanged(bool))) ;
    QObject::connect(serveur, SIGNAL(event_mute(bool)), this, SLOT(test7_event_mute(bool))) ;
    QObject::connect(serveur, SIGNAL(timechanged(int)), this, SLOT(tempsactuel_event_temps(int))) ;
    QObject::connect(serveur, SIGNAL(metadatachanged(QString, QString)), this, SLOT(metadata_event(QString, QString))) ;
    QObject::connect(serveur, SIGNAL(metadataradiochanged(QString, QString,QString)), this, SLOT(metadataradio_event(QString, QString,QString))) ;
    QObject::connect(serveur, SIGNAL(duration_info(int)), this, SLOT(set_duration(int))) ;
    QObject::connect(serveur, SIGNAL(filenamechanged(QString)), this, SLOT(set_cover(QString)));
    QObject::connect(serveur, SIGNAL(event_mode()), this, SLOT(switchmode()));


    // Changement mode étendu / mode normal
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    QObject::connect(test9, SIGNAL(clicked()), signalMapper, SLOT(map())) ;

    signalMapper->setMapping(test9,1) ;
    QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(changer_mode()));

    // Changement bouton play/pause


    QSignalMapper* signalMapper2 = new QSignalMapper (this) ;
    QObject::connect(test4, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    // QObject::connect(test13, SIGNAL(clicked()), signalMapper2, SLOT(map()));

    signalMapper2->setMapping(test4,test4);
    //signalMapper2->setMapping(test13,test13);

    QObject::connect(signalMapper2, SIGNAL(mapped(QWidget*)), this, SLOT(play_pause(QWidget*)));

    // SLIDER VOLUME
    QObject::connect(test8, SIGNAL(sliderMoved(int)), this, SLOT(test8_sliderMoved(int))) ;

    // SLIDER PROGRESS BAR
    QObject::connect(ui->progressbar, SIGNAL(sliderMoved(int)), this, SLOT(sliderProgressMoved(int))) ;

    // AUDIO BUTTON CLICKED
    QObject::connect(audio, SIGNAL(clicked()), this, SLOT(test7_event_volume())) ;

    // NEXT BUTTON CLICKED
    QObject::connect(test6, SIGNAL(clicked()), this, SLOT(event_next())) ;

    // PREVIOUS CLICKED
    QObject::connect(test2, SIGNAL(clicked()), this, SLOT(event_previous())) ;

    // SHUFFLE CLICKED
    QObject::connect(test, SIGNAL(clicked()), this, SLOT(event_shuffle())) ;

    // FM CLICKED
    QObject::connect(fm, SIGNAL(clicked()), this, SLOT(event_radio())) ;

    // FORWARD
    QObject::connect(test5, SIGNAL(clicked(int)), this, SLOT(set_speed(int)));

    // SEEK
    QObject::connect(test3, SIGNAL(clicked(int)), this, SLOT(event_seek(int))) ;

    // AFFICHAGE LISTE
    QObject::connect(listwidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onListSongItemClicked(QListWidgetItem*))); // A REMETTRE

    start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    if ( radio_on == true)
    {
        std::list<liste> liste_playlist = serveur->loadradioList(QDir::currentPath() + "/../IHM_Lecteur/musique/radioplaylist.m3u");
    }
    else
    {
        std::list<liste> liste_playlist = serveur->loadList(QDir::currentPath() + "/../IHM_Lecteur/musique/playlist1.m3u");

        for(std::list<liste>::iterator list_iter = liste_playlist.begin();
            list_iter != liste_playlist.end(); list_iter++)
        {
            ui->listwidget->addItem(list_iter->artist + " - " + list_iter->title + " - " + list_iter->duration);
        }
    }
}

void MainWindow::switchmode()
{
    mutex.lock();
    if ( radio_on == false)
    {
        fm->setPixmap(QPixmap(":/img/fm.png"));
        menu->setDisabled(true);
        shuffle->setDisabled(true);
        fastback->setDisabled(true);
        fast->setDisabled(true);
        progressbar->setDisabled(true);
        minimal=0;
        changer_mode();

        radio_on = true;
        std::list<liste> liste_playlist = serveur->loadradioList(QDir::currentPath() + "/../IHM_Lecteur/musique/radioplaylist.m3u");

    }
    else
    {
        fm->setPixmap(QPixmap(":/img/fm_off.png"));
        menu->setDisabled(false);
        shuffle->setDisabled(false);
        fast->setDisabled(false);
        progressbar->setDisabled(false);
        fastback->setDisabled(false);

        radio_on = false;
        std::list<liste> liste_playlist = serveur->loadList(QDir::currentPath() + "/../IHM_Lecteur/musique/playlist1.m3u");

        ui->listwidget->clear();
        for(std::list<liste>::iterator list_iter = liste_playlist.begin();
            list_iter != liste_playlist.end(); list_iter++)
        {
            ui->listwidget->addItem(list_iter->artist + " - " + list_iter->title + " - " + list_iter->duration);
        }

    }
    mutex.unlock();

}

void MainWindow::onListSongItemClicked(QListWidgetItem* item )
{
    int row = item->listWidget()->row( item );
    serveur->demarremusique(row);

}


void MainWindow::set_speed(int value)
{
    serveur->speed(value);
}

void MainWindow::event_radio()
{
    serveur->eventmode();
}

void MainWindow::changer_mode()
{

    QRect r = geometry();
    if (minimal == 1)
    {
        this->setGeometry(r.x(),r.y(),831,438);
        ui->stackedWidget->setCurrentIndex(1);
        minimal=0;
    }
    else
    {
        this->setGeometry(r.x(),r.y(),831,300);
        ui->stackedWidget->setCurrentIndex(0);
        minimal=1;
    }


}

void MainWindow::play_pause(QWidget *wid)
{
    if (((ClickableLabel*)wid)->objectName() == "pause")
    {

        ((ClickableLabel*)wid)->setPixmap(QPixmap(":/img/pause.png"));
        ((ClickableLabel*)wid)->setObjectName("pause");
        serveur->pause();

    }
    else
    {
        ((ClickableLabel*)wid)->setPixmap(QPixmap(":/img/play.png"));
        ((ClickableLabel*)wid)->setObjectName("play");
        serveur->play();
    }


}

void MainWindow::event_next()
{
    serveur->next();
}

void MainWindow::event_previous()
{
    serveur->previous();
}

void MainWindow::event_shuffle()
{
    serveur->shuffle();
    shuffle->setPixmap(QPixmap(":/img/shuffle_on.png"));
}

void MainWindow::event_seek(int value)
{
    serveur->seek(value);
}

void MainWindow::test4_etatchanged(bool value)
{
    if ( value )
    {
        test4->setPixmap(QPixmap(":/img/play.png"));
        test4->setObjectName("play");
    }
    else
    {
        test4->setPixmap(QPixmap(":/img/pause.png"));
        test4->setObjectName("pause");
    }
}


void MainWindow::set_duration(int temps)
{
    int min = floor(temps / 60);
    int sec = temps % 60;

    std::string arguments;
    if ( min < 10 && sec < 10 )
        arguments="0"+ std::to_string(min) + ":0" + std::to_string(sec);
    else if ( min < 10 && sec >= 10)
        arguments="0" + std::to_string(min) + ":" + std::to_string(sec);
    else if ( min >= 10 && sec >= 10)
        arguments="" + std::to_string(min) + ":" + std::to_string(sec);
    else if ( min >= 10 && sec < 10)
        arguments="" + std::to_string(min) + ":0" + std::to_string(sec);
    const QString qstr = QString::fromStdString(arguments);
    duration->setText( qstr );
}

void MainWindow::test8_sliderMoved(int position)
{
    serveur->setVolume(position);
}

void MainWindow::sliderProgressMoved(int position)
{
    serveur->setProgress(position);
}

void MainWindow::test8_event_volume(int position)
{
    test8->setValue(position);
}

void MainWindow::test7_event_volume()
{
    if ( audio->objectName() == "unmute" )
    {
        audio->setPixmap(QPixmap(":/img/audio_mute.png"));
        audio->setObjectName("muted");
        serveur->setMute(true);
        test8->setEnabled(false);

    }
    else
    {
        audio->setPixmap(QPixmap(":/img/audio.png"));
        audio->setObjectName("unmute");
        serveur->setMute(false);
        test8->setEnabled(true);
    }
}

void MainWindow::test7_event_mute(bool value)
{
    if ( value )
    {
        audio->setPixmap(QPixmap(":/img/audio.png"));
        audio->setObjectName("unmute");
        test8->setEnabled(true);
    }
    else
    {
        audio->setPixmap(QPixmap(":/img/audio_mute.png"));
        audio->setObjectName("muted");
        test8->setEnabled(false);
    }

}

void MainWindow::progressbar_event_progress(int position)
{

    progressbar->setValue(position);
}


void MainWindow::tempsactuel_event_temps(int temps)
{

    int min = floor(temps / 60);
    int sec = temps % 60;

    std::string arguments;
    if ( min < 10 && sec < 10 )
        arguments="0"+ std::to_string(min) + ":0" + std::to_string(sec);
    else if ( min < 10 && sec >= 10)
        arguments="0" + std::to_string(min) + ":" + std::to_string(sec);
    else if ( min >= 10 && sec >= 10)
        arguments="" + std::to_string(min) + ":" + std::to_string(sec);
    else if ( min >= 10 && sec < 10)
        arguments="" + std::to_string(min) + ":0" + std::to_string(sec);
    const QString qstr = QString::fromStdString(arguments);
    tempsactuel->setText( qstr );

}




void MainWindow::metadata_event(QString title, QString artist)
{
    ui->titre->setText(title);
    ui->artiste->setText(artist);
}

void MainWindow::metadataradio_event(QString title, QString artist,QString radio)
{
    ui->titre->setText(title);
    ui->artiste->setText(artist);
    ui->radio->setText(radio);
}


void MainWindow::set_cover(QString filename)
{
    if (filename != "fm" && filename != "pt-1")
    {
        const QString path = "../IHM_Lecteur/musique/"+filename;
        TagLib::MPEG::File file( path.toStdString().data()); //var d'environnement
        TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);
        TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");

        if(frameList.isEmpty()) {
            qDebug() << "Liste vide.";
        }

        TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());

        QImage coverQImg;
        coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
        coverQImg.save("../IHM_Lecteur/actuel.jpg");

        QPixmap img("../IHM_Lecteur/actuel.jpg");
        ui->cover->setPixmap(img);
    }
    else
    {
        QPixmap img(":/img/radio.png");
        ui->cover->setPixmap(img);
    }



}
