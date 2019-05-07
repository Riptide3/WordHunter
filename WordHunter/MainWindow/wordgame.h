#ifndef WORDGAME_H
#define WORDGAME_H

#include <QMainWindow>
#include <QTabWidget>
#include <QGridLayout>

#include "User/gamer.h"
#include "User/examer.h"
#include "GamerWindow/wordhunter.h"
#include "ExamerWindow/wordmaker.h"
#include "RanklistWindow/rankinglist.h"
#include "DetailinfoWindow/detailinformation.h"

class WordGame: public QWidget
{
    Q_OBJECT

public:
    WordGame(Gamer gamer);
    WordGame(Examer examer);
    ~WordGame();
private:

    QTabWidget *contentTab;
    WordHunter *wordhunter;
    WordMaker *wordmaker;
    RankingList *rankingList;
    DetailInformation *detailInfo;

    QGridLayout *mainLayout;
};

#endif // WORDGAME_H
