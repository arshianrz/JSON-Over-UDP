#include "myjson.h"
using namespace std;

//Constructor

MyJson::MyJson(QObject *parent) : QObject(parent)
{
    sender_ = new QUdpSocket(this);

    sender_->bind(QHostAddress::LocalHost,1244);

    clientSend();

    connect(sender_,SIGNAL(readyRead()),this,SLOT(clientReceive()));
}

//Creating Accessors

void MyJson::setRecord(QJsonObject record)
{
    record_ = record;
}

void MyJson::setIdentity(QJsonObject identity)
{
    identity_ = identity;
}

void MyJson::setGrades(QJsonArray grades)
{
    grades_ = grades;
}

//______***End of creating Accessors***______//

void MyJson::clientSend()
{

    while(true)
    {
        QByteArray Data;
        int counter;

        QJsonObject localRecord;
        QJsonObject localIdentity;
        QJsonArray localGrades;

        setRecord(localRecord);
        setIdentity(localIdentity);
        setGrades(localGrades);
        localRecord.insert("Grades",localGrades);

        string nameStr;
        string lastnameStr;

        qDebug("Enter your first name .");
        cin>>nameStr;
        qDebug("Enter your last name ");
        cin>>lastnameStr;

        QString nameQstr = QString::fromStdString(nameStr);
        nameQstr.fromStdString(nameStr);
        QString lastnameQstr = QString::fromStdString(lastnameStr);
        lastnameQstr.fromStdString(lastnameStr);

        QJsonValue nameJSvalue(nameQstr);
        QJsonValue lastnameJSvalue(lastnameQstr);


        localIdentity.insert("first_name",nameJSvalue);
        localIdentity.insert("last_name",lastnameJSvalue);
        localRecord.insert("ID",localIdentity);

        qDebug()<<"How many grades you want to commit? ";
        cin>>counter;

        int innerTemp;

        for(int i=0 ; i<counter ; i++)
        {
            qDebug()<<"Enter your grades.";
            cin>>innerTemp;
            QJsonValue temp(innerTemp);
            localGrades.push_back(temp);
        }

        localRecord.insert("Grades",localGrades);

        QJsonDocument doc(localRecord);

        qDebug("Client is going to send this JSON to server ...");

        qDebug(doc.toJson());

        Data.append(doc.toJson());

        sender_->writeDatagram(Data, QHostAddress::LocalHost,1313);

        clientReceive();
    }

}

void MyJson::clientReceive()
{
    //clientSend();

    jump:
    QByteArray buffer;
    QHostAddress receiver;
    quint16 receiverPort;
    buffer.resize(sender_->pendingDatagramSize());

    sender_->readDatagram(buffer.data(), buffer.size(), &receiver , &receiverPort);

    string buffStr;
    buffStr=buffer.toStdString();

    QString QbuffStr = QString::fromStdString(buffStr);
    QJsonDocument buffResponse = QJsonDocument::fromJson(QbuffStr.toUtf8());

    QJsonObject jsonObj = buffResponse.object();
    QJsonArray buffArray = jsonObj["average"].toArray();
    int temp;

    temp = buffArray[0].toInt();

    if(temp==0)
    {
        goto jump;
    }

    qDebug()<<"Average is :"<<temp;

    //clientSend();
}




