#ifndef CLIENT_H
#define CLIENT_H

#include <QByteArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QtNetwork>
#include <QWidget>

enum FUNCTION
{
    GAMER_SIGNIN,
    EXAMER_SIGNIN,
    GAMER_SIGNUP,
    EXAMER_SIGNUP,
    GAMER_SIGNOUT,
    EXAMER_SIGNOUT,
    GET_GAMERINFO,
    GET_EXAMERINFO,
    ADDWORD,
    GETWORD,
    GET_GAMERRANKLIST,
    GET_EXAMERRANKLIST,
    UPDATE_GAMERINFO,
    UPDATE_EXAMERINFO,
    GAMERMATCH,
    GET_PKRESULT,
    CANCELMATCH,
    UPDAT_PKINFO
};

enum STATE
{
    OFFLINE,
    ONLINE,
    WRONGPASSWD,
    NOUSER,
    MATCHING,
    PKING,
    PKEND,
    MATCHSUCCESS,
    MATCHFAILURE_MATCHING,
    MATCHFAILURE_PKING,
    WIN,
    LOSE,
    DRAW,
    WAIT
};

struct GamerInfo
{
    QString nickname;
    QString username;
    int level;
    int exp;
    int passedStage;
};

struct ExamerInfo
{
    QString nickname;
    QString username;
    int level;
    int exp;
    int questionNum;
};

class Client: public QWidget
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();
    void initClient();
    void connectServer();
    QTcpSocket* getInfoSender();
    void sendInfo(FUNCTION func, QString username, QString password);
    void sendInfo(FUNCTION func, QString nickname, QString username, QString password);
    void sendInfo(FUNCTION func, GamerInfo gamer);
    void sendInfo(FUNCTION func, ExamerInfo examer);
    void sendInfo(FUNCTION func, int difficultDegree);
    void sendInfo(FUNCTION func);
    void sendInfo(FUNCTION func, QString str);
    void sendInfo(FUNCTION func, QString username, int correctNum, int time);
    QJsonObject getInfo();
    QJsonArray getArrayInfo();
private:
    void sendInfo(QJsonObject infoObject);
private slots:
    void displayError(QAbstractSocket::SocketError);
private:
    QTcpSocket *infoSender;
};

#endif // CLIENT_H
