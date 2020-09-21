#ifndef MYJSON_H
#define MYJSON_H
#include <iostream>
#include <QtNetwork/QUdpSocket>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>

using namespace std;

class MyJson : public QObject
{
    Q_OBJECT

private:
    QUdpSocket *sender_;
    QJsonObject record_;
    QJsonObject identity_;
    QJsonArray grades_;

public:
    explicit MyJson(QObject *parent = 0);

    void setRecord(QJsonObject getRecord);
    void setIdentity(QJsonObject getIdentity);
    void setGrades(QJsonArray getGrades);

signals:
public slots:
    void clientSend();
    void clientReceive();
};


#endif // MYJSON_H
