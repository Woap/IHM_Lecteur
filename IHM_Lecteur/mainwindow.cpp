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



    // Boutons
    ClickableLabel* test = new ClickableLabel("MY LABEL",this);
    test->setGeometry(10,200,61,61);
    test->setPixmap(QPixmap(":/img/shuffle.png"));

    ClickableLabel* test2 = new ClickableLabel("MY LABEL",this);
    test2->setGeometry(160,200,61,61);
    test2->setPixmap(QPixmap(":/img/back.png"));

    ClickableLabel* test3 = new ClickableLabel("MY LABEL",this);
    test3->setGeometry(220,200,61,61);
    test3->setPixmap(QPixmap(":/img/fastback.png"));

    test4 = new ClickableLabel("MY LABEL",this);
    test4->setGeometry(290,200,61,61);
    test4->setPixmap(QPixmap(":/img/stop.png"));

    ClickableLabel* test5 = new ClickableLabel("MY LABEL",this);
    test5->setGeometry(350,200,61,61);
    test5->setPixmap(QPixmap(":/img/fast.png"));

    ClickableLabel* test6 = new ClickableLabel("MY LABEL",this);
    test6->setGeometry(410,200,61,61);
    test6->setPixmap(QPixmap(":/img/next.png"));

    test7 = new ClickableLabel("MY LABEL",this);
    test7->setGeometry(510,200,61,61);
    test7->setPixmap(QPixmap(":/img/audio.png"));
    test7->setObjectName("unmute");

    test8 = new QSlider(this);
    test8->setOrientation(Qt::Horizontal);
    test8->setGeometry(580,215,131,29);



    ClickableLabel* test9 = new ClickableLabel("MY LABEL",this);
    test9->setGeometry(720,200,61,61);
    test9->setPixmap(QPixmap(":/img/menu.png"));



    // INIT MPV DONNEES
    QObject::connect(serveur, SIGNAL(volumechanged(int)), this, SLOT(on_test8_event_volume(int))) ;

    QObject::connect(serveur, SIGNAL(progressionchanged(int)), this, SLOT(on_progressbar_event_progress(int))) ;
    QObject::connect(serveur, SIGNAL(etatchanged(bool)), this, SLOT(on_test4_etatchanged(bool))) ;
    QObject::connect(serveur, SIGNAL(event_mute(bool)), this, SLOT(on_test7_event_mute(bool))) ;
    QObject::connect(serveur, SIGNAL(timechanged(int)), this, SLOT(on_tempsactuel_event_temps(int))) ;
    QObject::connect(serveur, SIGNAL(metadatachanged(QString, QString)), this, SLOT(on_metadata_event(QString, QString))) ;
    QObject::connect(serveur, SIGNAL(duration_info(int)), this, SLOT(set_duration(int))) ;


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
    QObject::connect(test8, SIGNAL(sliderMoved(int)), this, SLOT(on_test8_sliderMoved(int))) ;

    // SLIDER PROGRESS BAR
    QObject::connect(ui->progressbar, SIGNAL(sliderMoved(int)), this, SLOT(sliderProgressMoved(int))) ;
    QObject::connect(ui->progressbar, SIGNAL(sliderMoved(int)), this, SLOT(sliderProgressMoved(int))) ;
    QObject::connect(test7, SIGNAL(clicked()), this, SLOT(on_test7_event_volume())) ;

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_test4_etatchanged(bool value)
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
    qDebug() << min;
    qDebug() << sec;
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

void MainWindow::on_test8_sliderMoved(int position)
{
    qDebug() << position;
    serveur->setVolume(position);
}

void MainWindow::sliderProgressMoved(int position)
{
    qDebug() << position;
    serveur->setProgress(position);
}

void MainWindow::on_test8_event_volume(int position)
{
    qDebug() << position;
    test8->setValue(position);
}

void MainWindow::on_test7_event_volume()
{
    if ( test7->objectName() == "unmute" )
    {
        test7->setPixmap(QPixmap(":/img/audio_mute.png"));
        test7->setObjectName("muted");
        serveur->setMute(true);
        test8->setEnabled(false);

    }
    else
    {
        test7->setPixmap(QPixmap(":/img/audio.png"));
        test7->setObjectName("unmute");
        serveur->setMute(false);
        test8->setEnabled(true);
    }
}

void MainWindow::on_test7_event_mute(bool value)
{
    if ( value )
    {
        test7->setPixmap(QPixmap(":/img/audio.png"));
        test7->setObjectName("unmute");
        test8->setEnabled(true);
    }
    else
    {
        test7->setPixmap(QPixmap(":/img/audio_mute.png"));
        test7->setObjectName("muted");
        test8->setEnabled(false);
    }

}

void MainWindow::on_progressbar_event_progress(int position)
{
    qDebug() << position;
    progressbar->setValue(position);
}


void MainWindow::on_tempsactuel_event_temps(int temps)
{
     //qDebug() << temps;
     int min = floor(temps / 60);
     int sec = temps % 60;
     qDebug() << min;
     qDebug() << sec;
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


void MainWindow::on_metadata_event(QString title, QString artist)
{
    ui->titre->setText(title);
    ui->artiste->setText(artist);
}
