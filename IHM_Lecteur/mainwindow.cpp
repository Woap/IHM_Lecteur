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



    ClickableLabel* test2 = new ClickableLabel("MY LABEL",this);
    test2->setGeometry(160,200,61,61);
    test2->setPixmap(QPixmap(":/img/back.png"));

    ClickableLabel* test3 = new ClickableLabel("MY LABEL",this);
    test3->setGeometry(220,200,61,61);
    test3->setPixmap(QPixmap(":/img/fastback.png"));
    test3->value = -3;

    test4 = new ClickableLabel("MY LABEL",this);
    test4->setGeometry(290,200,61,61);
    test4->setPixmap(QPixmap(":/img/stop.png"));

    ClickableLabel* test5 = new ClickableLabel("MY LABEL",this);
    test5->setGeometry(350,200,61,61);
    test5->setPixmap(QPixmap(":/img/fast.png"));
    test5->value = 3;

    ClickableLabel* test6 = new ClickableLabel("MY LABEL",this);
    test6->setGeometry(410,200,61,61);
    test6->setPixmap(QPixmap(":/img/next.png"));

    /*ClickableLabel* test = new ClickableLabel("MY LABEL",this);
    test->setGeometry(10,200,61,61);
    test->setPixmap(QPixmap(":/img/shuffle.png"));*/


    test7 = new ClickableLabel("MY LABEL",this);
    test7->setGeometry(510,200,61,61);
    test7->setPixmap(QPixmap(":/img/audio.png"));
    test7->setObjectName("unmute");

    test8 = new MySlider(this);
    test8->setOrientation(Qt::Horizontal);
    test8->setGeometry(580,215,131,29);

    std::list<liste> liste_playlist = serveur->loadradioList(QDir::currentPath() + "/../IHM_Lecteur/musique/radioplaylist.m3u");
    //std::list<liste> liste_playlist = serveur->loadList(QDir::currentPath() + "/../IHM_Lecteur/musique/playlist1.m3u");


    /*for(std::list<liste>::iterator list_iter = liste_playlist.begin();
        list_iter != liste_playlist.end(); list_iter++)
    {
        ui->listwidget->addItem(list_iter->artist + " - " + list_iter->title + " - " + list_iter->duration);
    }*/


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
    QObject::connect(serveur, SIGNAL(metadataradiochanged(QString, QString,QString)), this, SLOT(on_metadataradio_event(QString, QString,QString))) ;
    QObject::connect(serveur, SIGNAL(duration_info(int)), this, SLOT(set_duration(int))) ;
    QObject::connect(serveur, SIGNAL(filenamechanged(QString)), this, SLOT(set_cover(QString)));


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
    QObject::connect(test7, SIGNAL(clicked()), this, SLOT(on_test7_event_volume())) ;
    QObject::connect(test6, SIGNAL(clicked()), this, SLOT(event_next())) ;
    QObject::connect(test2, SIGNAL(clicked()), this, SLOT(event_previous())) ;
    QObject::connect(test, SIGNAL(clicked()), this, SLOT(event_shuffle())) ;

    /*QSignalMapper* signalMapper3 = new QSignalMapper (this) ;
    QObject::connect(test5, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    QObject::connect(test3, SIGNAL(clicked()), signalMapper3, SLOT(map())) ;
    signalMapper3->setMapping(test5,2);
    signalMapper3->setMapping(test3,-2);

    QObject::connect(signalMapper3, SIGNAL(mapped(int)), this, SLOT(event_seek(int)));*/


    QObject::connect(test5, SIGNAL(clicked(int)), this, SLOT(set_speed(int)));
    QObject::connect(test3, SIGNAL(clicked(int)), this, SLOT(event_seek(int))) ;

  //  QObject::connect(listwidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onListSongItemClicked(QListWidgetItem*))); // A REMETTRE






}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onListSongItemClicked(QListWidgetItem* item )
{
   int row = item->listWidget()->row( item );
   qDebug() << row;
   serveur->demarremusique(row);

}


void MainWindow::set_speed(int value)
{
    serveur->speed(value);
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
}

void MainWindow::event_seek(int value)
{
        serveur->seek(value);
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
    serveur->setVolume(position);
}

void MainWindow::sliderProgressMoved(int position)
{
    serveur->setProgress(position);
}

void MainWindow::on_test8_event_volume(int position)
{
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

void MainWindow::on_metadataradio_event(QString title, QString artist,QString radio)
{
    ui->titre->setText(title);
    ui->artiste->setText(artist);
    ui->radio->setText(radio);
}


void MainWindow::set_cover(QString filename)
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
