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

    tempsactuel = ui->tempsactuel;
    progressbar = ui->progressbar;


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

    ClickableLabel* test7 = new ClickableLabel("MY LABEL",this);
    test7->setGeometry(510,200,61,61);
    test7->setPixmap(QPixmap(":/img/audio.png"));

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
    QObject::connect(serveur, SIGNAL(timechanged(int)), this, SLOT(on_tempsactuel_event_temps(int))) ;


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


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changer_mode()
{

    QRect r = geometry();
    if (r.height() == 300)
    {
        this->setGeometry(r.x(),r.y(),831,438);
         ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        this->setGeometry(r.x(),r.y(),831,300);
         ui->stackedWidget->setCurrentIndex(0);
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


void MainWindow::on_test8_sliderMoved(int position)
{
    qDebug() << position;
    serveur->setVolume(position);
}

void MainWindow::on_test8_event_volume(int position)
{
    qDebug() << position;
    test8->setValue(position);
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
