#ifndef GAMER_H
#define GAMER_H

#include "user.h"

class Gamer: public User
{
public:
    Gamer();
    Gamer(QString nn, QString un, int lv, int exp, int passNum);
    ~Gamer();

    int getPassedStageNumber();
private:
    int passedStageNumber;
};

#endif // GAMER_H
