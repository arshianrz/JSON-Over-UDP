#include "jsonserver.h"
#include <QtNetwork/QUdpSocket>
#include <iostream>

JSONserver::JSONserver(QObject *parent):QObject(parent)
{
    receiver_ = new QUdpSocket(this);

    receiver_->bind(QHostAddress::LocalHost,1313);

    connect(receiver_,SIGNAL(readyRead()),this,SLOT(serverReceive()));

    sum=0;
    counter=0;
}

void JSONserver::serverReceive()
{

    qDebug()<<"Data receiving by server ...";

    QByteArray buffer;

    buffer.resize(receiver_->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    receiver_->readDatagram(buffer.data(), buffer.size(), &sender , &senderPort);

    qDebug(buffer);

    string buffStr;
    buffStr=buffer.toStdString();

    QString QbuffStr = QString::fromStdString(buffStr);
    QJsonDocument buffResponse = QJsonDocument::fromJson(QbuffStr.toUtf8());

    QJsonObject jsonObj = buffResponse.object();
    QJsonArray buffArray = jsonObj["Grades"].toArray();

    qDebug()<<buffArray;

    int grades[buffArray.size()];
    int temp;


    for(int i=0 ; i<buffArray.size() ; i++)
    {
        temp = buffArray[counter].toInt();
        sum += temp;
        grades[counter]=temp;
        ++counter;
    }
    serverFeedBack();
}

void JSONserver::serverFeedBack()
{
    avg=sum/counter;

    QJsonObject record;
    QJsonArray Average;
    QJsonValue temp(avg);
    Average.push_back(temp);

    record.insert("average",Average);
    QJsonDocument recordDoc(record);


    QByteArray Data;
    Data.append(recordDoc.toJson());

    receiver_->writeDatagram(Data, QHostAddress::LocalHost,1244);

    qDebug()<<"Server average :"<<avg;
    counter=0;
    sum=0;
}

