#include "serveur.h"
#include <QDebug>

Serveur::Serveur(QObject *parent) :
    QObject(parent),
    mpv(new QLocalSocket(this))
{
    connect(mpv, SIGNAL(readyRead()), this, SLOT(readSocket()));

    mpv->connectToServer( "/tmp/mpv" );

    if (mpv->waitForConnected())
        qDebug() << "connected to mpv";
    else {
        mpv->error();
    }

    observePause();
    observeVolume();
    observePos();

    loadFile("3500.mp3");
    getVolume();
}

Serveur::~Serveur() {
    mpv->disconnectFromServer();
}

void Serveur::readSocket()
{
    while (mpv->canReadLine()) {
        QByteArray line = mpv->readLine().trimmed();
        QJsonParseError error;
        QJsonDocument jDoc=QJsonDocument::fromJson(line, &error);
        QJsonObject jsonObject=jDoc.object();
        if ( jsonObject["id"] == 22 )
        {
            qDebug() << "Changement volume" ;
            qDebug() << jsonObject["data"];
            emit volumechanged(jsonObject["data"].toInt());
        }

        if ( jsonObject["id"] == 14 )
        {
            qDebug() << "Changement progress" ;
            qDebug() << round(jsonObject["data"].toDouble());
            emit progressionchanged(round(jsonObject["data"].toDouble()));
        }

        if ( jsonObject["id"] == 12 )
        {
            qDebug() << "play pause" ;
            qDebug() << jsonObject["data"].toBool();
            emit etatchanged(jsonObject["data"].toBool());
        }

        if ( jsonObject["id"] == 13 )
        {
            qDebug() << "Changement time" ;
            //qDebug() << round(jsonObject["data"].toDouble());
            //qDebug() << round(floor((jsonObject["data"].toDouble())/60));
            //qDebug() << fmod(round(jsonObject["data"].toDouble()),60) ;
            emit timechanged(round(jsonObject["data"].toDouble()));
        }
        qDebug() << jsonObject;
    }
}

void Serveur::writeSocket(QJsonObject j)
{
    QByteArray bytes = QJsonDocument(j).toJson(QJsonDocument::Compact)+"\n";
    if (mpv!=NULL) {
      mpv->write(bytes.data(), bytes.length());
      mpv->flush();
    }
}





/*********** Commandes à MPV ************/

void Serveur::loadFile(QString path){
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("loadfile"));
    a.append(path);

    QJsonArray b;
    b.append(1);

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}


void Serveur::play(){
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("pause"));
    a.append(false);

    QJsonArray b;
    b.append(10);

    jsonObject["command"]=a;
    jsonObject["request_id"]=b;

    writeSocket(jsonObject);
}


void Serveur::pause(){
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("pause"));
    a.append(true);

    QJsonArray b;
    b.append(11);

    jsonObject["command"]=a;
    jsonObject["request_id"]=b;

    writeSocket(jsonObject);
}


void Serveur::observePause(){
    QJsonObject jsonObject;
    QJsonArray a;
    a.append(QStringLiteral("observe_property"));
    a.append(12);
    a.append(QStringLiteral("pause"));

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}


void Serveur::observePos(){
    QJsonObject jsonObject;
    QJsonArray a;
    a.append(QStringLiteral("observe_property"));
    a.append(13);
    a.append(QStringLiteral("time-pos"));

    QJsonObject jsonObject1;
    QJsonArray b;
    b.append(QStringLiteral("observe_property"));
    b.append(14);
    b.append(QStringLiteral("percent-pos"));

    jsonObject["command"]=a;
    jsonObject1["command"]=b;

    writeSocket(jsonObject);
    writeSocket(jsonObject1);
}


void Serveur::getVolume(){
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("get_property"));
    a.append(QStringLiteral("volume"));

    QJsonArray b;
    b.append(20);

    jsonObject["command"]=a;
    jsonObject["request_id"]=b;

    writeSocket(jsonObject);
}


void Serveur::setVolume(int vol) {
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("volume"));
    a.append(vol);

    QJsonArray b;
    b.append(21);

    jsonObject["command"]=a;
    jsonObject["request_id"]=b;

    writeSocket(jsonObject);
}


void Serveur::observeVolume(){
    QJsonObject jsonObject;
    QJsonArray a;
    a.append(QStringLiteral("observe_property"));
    a.append(22);
    a.append(QStringLiteral("volume"));

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}
