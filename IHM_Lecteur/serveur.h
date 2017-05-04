
#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QJsonArray>
#include <QLocalServer>
#include <QLocalSocket>
#include <QtConcurrent/QtConcurrent>
#include <string>

#include "taglib/tag.h"
#include <fileref.h>
#include "taglib/tpropertymap.h"
#include "taglib/mpegfile.h"
#include "taglib/id3v2tag.h"
#include "taglib/id3v2frame.h"
#include "taglib/attachedpictureframe.h"

typedef struct l_liste {
    QString filename;
    QString title;
    QString artist;
    QString album;
    QString duration;
} liste;


class Serveur: public QObject
{
    Q_OBJECT

public:
    explicit Serveur(QObject *parent = 0);
    ~Serveur();

    std::list<liste> loadList(QString path);
    std::list<liste> loadradioList(QString path);
    std::list<liste> liste_playlist;
    bool radio_on=false;

    void play();
    void pause();

    void observePause();

    void getVolume();
    void setVolume(int vol);
    void setProgress(int p);
    void observeVolume();
    void observePos();
    void observeMetadata();
    void observeMute();
    void observeFile();
    void setMute(bool val);
    void observeDuration();
    void previous();
    void next();
    void seek(int value);
    void shuffle();
    void speed(int value);
    void demarremusique(int row);

private slots:
    void readSocket();


signals:
    void volumechanged(int value);
    void event_mute(bool value);
    void progressionchanged(int value);
    void timechanged(int value);
    void etatchanged(bool value);
    void metadatachanged (QString title, QString artist);
    void metadataradiochanged (QString title, QString artist,QString radio);
    void duration_info(int value);
    void filenamechanged(QString filename);

private:
    QLocalSocket *mpv=NULL;

    void writeSocket(QJsonObject j);

    void loadFile(QString path);


};

#endif // SERVEUR_H
