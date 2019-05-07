#include "gamer.h"

Gamer::Gamer()
{

}

Gamer::Gamer(QString nn, QString un, int lv, int exp, int passNum)
    : User(nn, un, lv, exp), passedStageNumber(passNum)
{

}

Gamer::~Gamer()
{

}

int Gamer::getPassedStageNumber()
{
    return passedStageNumber;
}
