#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString nn, QString un, int lv, int exp);
    User();
    ~User();

    QString getNickname() const;
    QString getUsername() const;
    int getLevel() const;
    int getExperiencePoint() const;
    void changeNickname(QString newNickname);
    void addExp(int expAddition);
protected:
    void addLevel(int levelAddition);
private:
    QString nickname;
    QString username;
    int level;
    int experiencePoint;
};

#endif // USER_H
