
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

private slots:
    void readSocket();

private:
    QLocalSocket *mpv=NULL;

    void writeSocket(QJsonObject j);

    void loadFile(QString path);

    void play();
    void pause();
    void observePause();

    void getVolume();
    void setVolume(int vol);
    void observeVolume();
    void observePos();
};

#endif // SERVEUR_H
