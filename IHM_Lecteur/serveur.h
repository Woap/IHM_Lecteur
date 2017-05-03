
#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
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


class Serveur: public QObject
{
    Q_OBJECT

public:
    explicit Serveur(QObject *parent = 0);
    ~Serveur();
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
    void setMute(bool val);
    void observeDuration();
    void previous();
    void next();
    void seek(int value);
    void shuffle();

private slots:
    void readSocket();


signals:
    void volumechanged(int value);
    void event_mute(bool value);
    void progressionchanged(int value);
    void timechanged(int value);
    void etatchanged(bool value);
    void metadatachanged (QString title, QString artist);
    void duration_info(int value);

private:
    QLocalSocket *mpv=NULL;

    void writeSocket(QJsonObject j);

    void loadFile(QString path);
    void loadList(QString path);


};

#endif // SERVEUR_H
