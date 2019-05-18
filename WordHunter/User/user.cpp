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

QString User::getNickname() const
{
    return nickname;
}

QString User::getUsername() const
{
    return username;
}

int User::getLevel() const
{
    return level;
}

int User::getExperiencePoint() const
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
    while(experiencePoint >= maxExp)
    {
        experiencePoint = experiencePoint - maxExp;
        addLevel(1);
    }
}

void User::subExp(int subtrahend)
{
    experiencePoint -= subtrahend;
    if(experiencePoint < 0)
        experiencePoint = 0;
}
