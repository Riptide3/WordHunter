#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>
#include <QMessageBox>
#include <QString>

#include "User/gamer.h"
#include "User/examer.h"

class Database
{
public:
    Database();
    ~Database();
    void init();
    bool gamerSignin(QString username, QString password);
    bool gamerSignup(QString nickname, QString username, QString password);
    bool examerSignin(QString username, QString password);
    bool examerSignup(QString nickname, QString username, QString password);
    void updateInfo(Gamer gamer);
    void updateInfo(Examer examer);
    Gamer getGamerInfo(QString username);
    Examer getExamerInfo(QString username);
    bool addWord(QString word);
    QString getWord(int difficultDegree);
private:
    QSqlQuery *query;
};

#endif // DATABASE_H
