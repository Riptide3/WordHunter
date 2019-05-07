#include "examer.h"

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

int Examer::getQuestionNumber()
{
    return questionNumber;
}
