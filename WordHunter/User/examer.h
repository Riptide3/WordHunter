#ifndef EXAMER_H
#define EXAMER_H

#include "user.h"

class Examer: public User
{
public:
    Examer();
    Examer(QString nn, QString un, int lv, int exp, int questionNum);
    ~Examer();

    int getQuestionNumber();
private:
    int questionNumber;
};

#endif // EXAMER_H
