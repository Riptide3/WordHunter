#ifndef GAMER_H
#define GAMER_H

#include "user.h"

class Gamer: public User
{
public:
    Gamer();
    Gamer(QString nn, QString un, int lv, int exp, int passNum);
    ~Gamer();
    Gamer(const Gamer&) = default;

    int getPassedStageNumber() const;
    void addStage(int stageAddition);
private:
    int passedStageNumber;
};

#endif // GAMER_H
