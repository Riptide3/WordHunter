#ifndef DATABASE_H
#define DATABASE_H

#include <Qtsql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QString>

#include "gamer.h"
#include "examer.h"

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
    Gamer getGamerInfo(QString username);
    Examer getExamerInfo(QString username);
    bool addWord(QString w);
    QString getWord(int difficultDegree);
private:
    QSqlQuery *query;
};

#endif // DATABASE_H
