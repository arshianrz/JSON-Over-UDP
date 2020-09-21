#ifndef JSONSERVER_H
#define JSONSERVER_H
#include <iostream>
#include <QtNetwork/QUdpSocket>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>

using namespace std;

class JSONserver : public QObject
{
    Q_OBJECT

private:

    QUdpSocket *receiver_;
    int sum;
    int avg;
    int counter;

public:

    explicit JSONserver(QObject *parent = 0);

signals:
public slots:
    void serverReceive();
    void serverFeedBack();

};

#endif // JSONSERVER_H

