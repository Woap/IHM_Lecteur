/**
 * \file serveur.cpp
 * \author CHIBOUT Yanis et IBIS Ibrahim
 *
 * Aud.io lecteur audio pour mpv
 * Fichier permettant de communiquer avec le serveur MPV et recevoir les données
 */

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

    observeFile();
    observePause();
    observeVolume();
    observePos();
    observeMetadata();
    observeDuration();

}

Serveur::~Serveur() {
    mpv->disconnectFromServer();
}

// Lire la socket
void Serveur::readSocket()
{
    while (mpv->canReadLine()) {
        QByteArray line = mpv->readLine().trimmed();
        QJsonParseError error;
        QJsonDocument jDoc=QJsonDocument::fromJson(line, &error);
        QJsonObject jsonObject=jDoc.object();
        if ( jsonObject["id"] == 22 )
        {


            emit volumechanged(jsonObject["data"].toInt());
        }

        if ( jsonObject["id"] == 14 )
        {

            emit progressionchanged(round(jsonObject["data"].toDouble()));
        }

        if ( jsonObject["id"] == 12 )
        {

            emit etatchanged(jsonObject["data"].toBool());
        }

        if ( jsonObject["id"] == 13 )
        {

            emit timechanged(round(jsonObject["data"].toDouble()));
        }

        if ( jsonObject["id"] == 26 )
        {


            emit event_mute(jsonObject["data"].toBool());
        }


        if ( jsonObject["id"] == 30)
        {
            if ( radio_on == false)
            {
                QJsonObject d = jsonObject["data"].toObject();
                emit metadatachanged(d["title"].toString(), d["artist"].toString());
            }
            else
            {
                QJsonObject d = jsonObject["data"].toObject();
                emit metadataradiochanged(d["TITLE"].toString(), d["ARTIST"].toString(),d["icy-name"].toString());
                // "icy-genre":"90s","icy-name":"Radio 90 Hit"
            }
        }

        if ( jsonObject["id"] == 25)
        {

            emit duration_info(round(jsonObject["data"].toDouble()));
        }


        if ( jsonObject["request_id"] == 99)
        {

            emit event_mode();
        }


        if ( jsonObject["id"] == 666)
        {
            if ( radio_on == false)
            {

                emit filenamechanged(jsonObject["data"].toString());
            }
            else
            {
                emit filenamechanged("fm");
            }
        }

    }
}

// Ecrire sur la socket
void Serveur::writeSocket(QJsonObject j)
{
    QByteArray bytes = QJsonDocument(j).toJson(QJsonDocument::Compact)+"\n";
    if (mpv!=NULL) {
        mpv->write(bytes.data(), bytes.length());
        mpv->flush();
    }
}

/*********** Commandes à MPV ************/

void Serveur::eventmode()
{
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("pause"));
    a.append(false);


    jsonObject["command"]=a;
    jsonObject["request_id"]=99;

    writeSocket(jsonObject);
}



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

std::list<liste> Serveur::loadradioList(QString path){
    radio_on=true;
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("loadlist"));
    a.append(path);

    QJsonArray b;
    b.append(27);

    jsonObject["command"]=a;

    writeSocket(jsonObject);

    return liste_playlist;
}

std::list<liste> Serveur::loadList(QString path){
    radio_on=false;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << path;
    }

    QTextStream in(&file);
    liste_playlist.clear();


    while(!in.atEnd()) {
        QString line = in.readLine();
        QString line2 = QDir::currentPath() + "/../IHM_Lecteur/musique/" + line;
        TagLib::FileRef f(line2.toStdString().data());

        liste l;
        l.filename = line2;
        l.title = QString::fromStdString(f.tag()->title().to8Bit());
        l.artist = QString::fromStdString(f.tag()->artist().to8Bit());
        l.album = QString::fromStdString(f.tag()->album().to8Bit());
        int temps = f.audioProperties()->length();

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

        l.duration = qstr;
        liste_playlist.push_back(l);
    }

    for(std::list<liste>::iterator list_iter = liste_playlist.begin();
        list_iter != liste_playlist.end(); list_iter++)
    {
        //qDebug() << list_iter->title << endl;
    }

    file.close();

    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("loadlist"));
    a.append(path);

    QJsonArray b;
    b.append(2);

    jsonObject["command"]=a;

    writeSocket(jsonObject);

    return liste_playlist;
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

void Serveur::demarremusique(int row)
{
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("playlist-pos"));
    a.append(row);


    QJsonArray b;
    b.append(45);

    jsonObject["command"]=a;
    jsonObject["request_id"]=b;

    writeSocket(jsonObject);
}

void Serveur::speed(int value){
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("speed"));
    a.append(value);

    QJsonArray b;
    b.append(46);

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

void Serveur::observeDuration(){
    QJsonObject jsonObject;
    QJsonArray a;

    a.append(QStringLiteral("observe_property"));
    a.append(25);
    a.append(QStringLiteral("duration"));

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

void Serveur::setProgress(int p) {
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("percent-pos"));
    a.append(p);

    QJsonArray b;
    b.append(27);

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


void Serveur::observeMetadata(){
    QJsonObject jsonObject;
    QJsonArray a;
    a.append(QStringLiteral("observe_property"));
    a.append(30);
    a.append(QStringLiteral("metadata"));

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}

void Serveur::setMute(bool val){
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("set_property"));
    a.append(QStringLiteral("mute"));
    a.append(val);


    QJsonArray b;
    b.append(31);

    jsonObject["command"]=a;
    jsonObject["request_id"]=b;

    writeSocket(jsonObject);

}

void Serveur::next()
{
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("playlist-next"));

    QJsonArray b;
    b.append(3);

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}

void Serveur::seek(int value)
{
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("seek"));
    a.append(value);

    QJsonArray b;
    b.append(3);

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}

void Serveur::shuffle()
{
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("playlist-shuffle"));

    QJsonArray b;
    b.append(3);

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}


void Serveur::previous()
{

    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append(QStringLiteral("playlist-prev"));

    QJsonArray b;
    b.append(3);

    jsonObject["command"]=a;

    writeSocket(jsonObject);
}

void Serveur::observeMute(){
    QJsonObject jsonObject;
    QJsonArray a;
    a.append(QStringLiteral("observe_property"));
    a.append(26);
    a.append(QStringLiteral("mute"));

    jsonObject["command"]=a;

    writeSocket(jsonObject);

}


void Serveur::observeFile(){
    QJsonObject jsonObject;
    QJsonArray a;
    a.append(QStringLiteral("observe_property"));
    a.append(666);
    a.append(QStringLiteral("filename"));

    jsonObject["command"]=a;

    writeSocket(jsonObject);

}



