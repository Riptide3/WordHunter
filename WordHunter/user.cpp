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
