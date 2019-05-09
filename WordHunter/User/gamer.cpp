#include "gamer.h"
#include "Database/database.h"

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

void Gamer::addStage(int stageAddition)
{
    passedStageNumber += stageAddition;
}

void Gamer::updateInfo(const Gamer &gamer)
{
    Database db;
    db.updateInfo(gamer);
}
