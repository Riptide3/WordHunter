#include "user.h"

User::User()
{

}

User::User(QString nn, QString un, int lv, int exp)
    : nickname(nn), username(un), level(lv), experiencePoint(exp)
{

}

User::~User()
{

}

QString User::getNickname()
{
    return nickname;
}

QString User::getUsername()
{
    return username;
}

int User::getLevel()
{
    return level;
}

int User::getExperiencePoint()
{
    return experiencePoint;
}

void User::changeNickname(QString newNickname)
{
    nickname = newNickname;
}

void User::addLevel(int levelAddition)
{
    level += levelAddition;
}

void User::addExp(int expAddition)
{
    const int maxExp = (level + 1) * 10;

    experiencePoint += expAddition;
    if(experiencePoint > maxExp)
    {
        experiencePoint = experiencePoint - maxExp - 1;
        addLevel(1);
    }
}
