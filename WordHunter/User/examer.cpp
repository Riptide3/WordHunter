#include "examer.h"
#include "Database/database.h"

Examer::Examer()
{

}

Examer::Examer(QString nn, QString un, int lv, int exp, int questionNum)
    : User(nn, un, lv, exp), questionNumber(questionNum)
{

}

Examer::~Examer()
{

}

int Examer::getQuestionNumber() const
{
    return questionNumber;
}

void Examer::addQuestionNumber(int questionAddition)
{
    questionNumber += questionAddition;
}

void Examer::updateInfo(const Examer &examer)
{
    Database db;
    db.updateInfo(examer);
}
