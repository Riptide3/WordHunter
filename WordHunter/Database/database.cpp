#include "database.h"

Database::Database()
{

}

Database::~Database()
{

}

void Database::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("WordHunter");
    db.setUserName("yzy");
    db.setPassword("521521");
    if(!db.open())
    {
        qDebug() << "数据库创建失败" ;
    }
    else
    {
        qDebug() << "数据库创建成功" ;
        query = new QSqlQuery;
        query->exec("create table gamer(username varchar(20) primary key, \
                    nickname varchar(20), password varchar(20), \
                    level int, experiencePoint int, \
                    passedStageNumber int)");
        query->exec("create table examer(username varchar(20) primary key, \
                    nickname varchar(20), password varchar(20), \
                    level int, experiencePoint int, \
                    QuestionNumber int)");
        query->exec("create table words(word varchar(30) primary key)");
    }
}

bool Database::gamerSignin(QString username, QString password)
{
    query = new QSqlQuery;
    QString gamer = QString("select * from gamer where \
                            username = '%1' and password = '%2' ").arg(username).arg(password);
    query->exec(gamer);
    if(query->first())
        return true;
    else
        return false;
}

bool Database::gamerSignup(QString nickname, QString username, QString password)
{
    query = new QSqlQuery;
    QString gamer = QString("select * from gamer where \
                            username = '%1' ").arg(username);
    if(query->exec(gamer))
    {
        if(query->first())
        {
            return false;
        }
        else
        {
            QString nGamer = QString("insert into gamer values(?, ?, ?, ?, ?, ?)");
            query->prepare(nGamer);
            query->bindValue(0, username);
            query->bindValue(1, nickname);
            query->bindValue(2, password);
            query->bindValue(3, 0);
            query->bindValue(4, 0);
            query->bindValue(5, 0);
            query->exec();
            qDebug() << "注册成功";
            return true;
        }
    }
    else
    {
        qDebug() << query->lastError();
        return false;
    }
}

bool Database::examerSignin(QString username, QString password)
{
    query = new QSqlQuery;
    QString examer = QString("select * from examer where \
                             username = '%1' and password = '%2' ").arg(username).arg(password);
    if(query->exec(examer))
    {
        if(query->first())
            return true;
        else
            return false;
    }
    else
    {
        qDebug() << query->lastError();
        return false;
    }
}

bool Database::examerSignup(QString nickname, QString username, QString password)
{
    query = new QSqlQuery;
    QString examer = QString("select * from examer where \
                             username = '%1' ").arg(username);
    if(query->exec(examer))
    {
        if(query->first())
        {
            return false;
        }
        else
        {
            QString nExamer = QString("insert into examer values(?, ?, ?, ?, ?, ?)");
            query->prepare(nExamer);
            query->bindValue(0, username);
            query->bindValue(1, nickname);
            query->bindValue(2, password);
            query->bindValue(3, 0);
            query->bindValue(4, 0);
            query->bindValue(5, 0);
            query->exec();
            qDebug() << "注册成功";
            return true;
        }
    }
    else
    {
        qDebug() << query->lastError();
        return false;
    }
}

Gamer Database::getGamerInfo(QString username)
{
    query = new QSqlQuery;
    QString getInfo = QString("select * from gamer where \
                                username = '%1' ").arg(username);
    query->exec(getInfo);
    QString nickname;
    int level = 0, exp = 0, passedStageNum = 0;
    if(query->first())
    {
        nickname = query->value(1).toString();
        level = query->value(3).toInt();
        exp = query->value(4).toInt();
        passedStageNum = query->value(5).toInt();
    }
    Gamer gamer(nickname, username, level, exp, passedStageNum);
    return gamer;
}

Examer Database::getExamerInfo(QString username)
{
    query = new QSqlQuery;
    QString getInfo = QString("select * from gamer where \
                                username = '%1' ").arg(username);
    query->exec(getInfo);
    QString nickname;
    int level = 0, exp = 0, questionNum = 0;
    if(query->first())
    {
        nickname = query->value(1).toString();
        level = query->value(3).toInt();
        exp = query->value(4).toInt();
        questionNum = query->value(5).toInt();
    }
    Examer examer(nickname, username, level, exp, questionNum);
    return examer;
}

bool Database::addWord(QString word)
{
    query = new QSqlQuery;
    QString isExisting = QString("select * from words where \
                           word = '%1' ").arg(word);
    if(query->exec(isExisting))
    {
        if(query->first())
        {
            return false;
        }
        else
        {
            QString isNewWord = QString("insert into words values(?)");
            query->prepare(isNewWord);
            query->bindValue(0, word);
            query->exec(isNewWord);
            qDebug() << word << "success!!!";
            return true;
        }
    }
    else
    {
        qDebug() << query->lastError();
        return false;
    }
}

QString Database::getWord(int difficultDegree)
{
    query = new QSqlQuery;
    QString getword = QString("select * from words where \
                                length(word)=" + QString::number(difficultDegree) \
                                + "order by rand() limit 1");
    query->exec(getword);
    return query->value(0).toString();
}
