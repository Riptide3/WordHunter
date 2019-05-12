#include "examer.h"

Examer::Examer()
    : User("", "", 0, 0), questionNumber(0)
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

