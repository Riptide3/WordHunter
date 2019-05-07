#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString nn, QString un, int lv, int exp);
    User();
    ~User();

    QString getNickname();
    QString getUsername();
    int getLevel();
    int getExperiencePoint();
private:
    QString nickname;
    QString username;
    int level;
    int experiencePoint;
};

#endif // USER_H
