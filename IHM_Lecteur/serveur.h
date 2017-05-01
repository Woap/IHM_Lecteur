
#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QtConcurrent/QtConcurrent>
#include <string>
//#include <taglib/taglib.h>

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
    void observeVolume();
    void observePos();

private slots:
    void readSocket();


signals:
    void volumechanged(int value);
    void progressionchanged(int value);
    void timechanged(int value);
    void etatchanged(bool value);

private:
    QLocalSocket *mpv=NULL;

    void writeSocket(QJsonObject j);

    void loadFile(QString path);


};

#endif // SERVEUR_H
