#include "client.h"

const QString IP = "192.168.43.160";
const int PORT = 8000;

Client::Client(QWidget *parent)
    : QWidget(parent)
{

}

Client::~Client()
{

}

void Client::initClient()
{
    infoSender = new QTcpSocket(this);
    connect(infoSender, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void Client::connectServer()
{
    infoSender->abort();
    infoSender->connectToHost(IP, PORT);
}

QTcpSocket* Client::getInfoSender()
{
    return infoSender;
}

void Client::sendInfo(FUNCTION func, QString username, QString password)
{
    QJsonObject infoObject;
    infoObject.insert("function", func);
    infoObject.insert("username", username);
    infoObject.insert("password", password);

    sendInfo(infoObject);
}

void Client::sendInfo(FUNCTION func, QString nickname, QString username, QString password)
{
    QJsonObject infoObject;
    infoObject.insert("function", func);
    infoObject.insert("nickname", nickname);
    infoObject.insert("username", username);
    infoObject.insert("password", password);
    qDebug() << func << username << "玩家注册第一步";
    sendInfo(infoObject);
}

void Client::sendInfo(FUNCTION func, GamerInfo gamer)
{
    QJsonObject infoObject;
    infoObject.insert("function", func);
    infoObject.insert("nickname", gamer.nickname);
    infoObject.insert("username", gamer.username);
    infoObject.insert("level", gamer.level);
    infoObject.insert("exp", gamer.exp);
    infoObject.insert("passedStage", gamer.passedStage);

    sendInfo(infoObject);
}

void Client::sendInfo(FUNCTION func, ExamerInfo examer)
{
    QJsonObject infoObject;
    infoObject.insert("function", func);
    infoObject.insert("nickname", examer.nickname);
    infoObject.insert("username", examer.username);
    infoObject.insert("level", examer.level);
    infoObject.insert("exp", examer.exp);
    infoObject.insert("questionNum", examer.questionNum);

    sendInfo(infoObject);
}

void Client::sendInfo(FUNCTION func, int difficultDegree)
{
    QJsonObject infoObject;
    infoObject.insert("function", func);
    infoObject.insert("difficulty", difficultDegree);

    sendInfo(infoObject);
}

void Client::sendInfo(FUNCTION func, QString str)
{
    QJsonObject infoObject;
    infoObject.insert("function", func);
    infoObject.insert("string", str);

    sendInfo(infoObject);
}
void Client::sendInfo(FUNCTION func)
{
    qDebug() << "发送获取玩家列表的请求" << func;
    QJsonObject infoObject;
    infoObject.insert("function", func);

    sendInfo(infoObject);
}

void Client::sendInfo(FUNCTION func, QString username, int correctNum, int time)
{
    QJsonObject infoObject;
    infoObject.insert("function", func);
    infoObject.insert("username", username);
    infoObject.insert("correctNum", correctNum);
    infoObject.insert("time", time);

    sendInfo(infoObject);
}

void Client::sendInfo(QJsonObject infoObject)
{
    QJsonDocument infoDocument;
    infoDocument.setObject(infoObject);

    QByteArray infoByteArray;
    infoByteArray = infoDocument.toJson(QJsonDocument::Compact);
    qDebug() << "向服务器发送信息";
    infoSender->write(infoByteArray);
}

QJsonObject Client::getInfo()
{
    QByteArray receivedInfo;
    QJsonParseError infoParse;
    QJsonDocument parseDocument;
    QJsonObject receivedInfoObject;
    receivedInfo = infoSender->readAll();
    parseDocument = QJsonDocument::fromJson(receivedInfo, &infoParse);
    receivedInfoObject = parseDocument.object();
    return  receivedInfoObject;
}

QJsonArray Client::getArrayInfo()
{
    QByteArray receivedInfo;
    QJsonParseError infoParse;
    QJsonDocument parseDocument;
    QJsonArray receivedInfoArray;
    receivedInfo = infoSender->readAll();
    parseDocument = QJsonDocument::fromJson(receivedInfo, &infoParse);
    receivedInfoArray = parseDocument.array();
    return receivedInfoArray;
}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << infoSender->errorString();
    infoSender->close();
}
