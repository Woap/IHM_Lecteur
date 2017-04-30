#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QTextStream>
#include <QSignalMapper>
#include <QLocalServer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->statusBar()->setSizeGripEnabled(false);

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

    ClickableLabel* test4 = new ClickableLabel("MY LABEL",this);
    test4->setGeometry(290,200,61,61);
    test4->setPixmap(QPixmap(":/img/play.png"));

    ClickableLabel* test5 = new ClickableLabel("MY LABEL",this);
    test5->setGeometry(350,200,61,61);
    test5->setPixmap(QPixmap(":/img/fast.png"));

    ClickableLabel* test6 = new ClickableLabel("MY LABEL",this);
    test6->setGeometry(410,200,61,61);
    test6->setPixmap(QPixmap(":/img/next.png"));

    ClickableLabel* test7 = new ClickableLabel("MY LABEL",this);
    test7->setGeometry(510,200,61,61);
    test7->setPixmap(QPixmap(":/img/audio.png"));

    QSlider* test8 = new QSlider(this);
    test8->setOrientation(Qt::Horizontal);
    test8->setGeometry(580,215,131,29);


    ClickableLabel* test9 = new ClickableLabel("MY LABEL",this);
    test9->setGeometry(720,200,61,61);
    test9->setPixmap(QPixmap(":/img/menu.png"));






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
    if (((ClickableLabel*)wid)->objectName() == "stop")
    {
        ((ClickableLabel*)wid)->setPixmap(QPixmap(":/img/play.png"));
        ((ClickableLabel*)wid)->setObjectName("play");
    }
    else
    {
        ((ClickableLabel*)wid)->setPixmap(QPixmap(":/img/stop.png"));
        ((ClickableLabel*)wid)->setObjectName("stop");
    }


}

