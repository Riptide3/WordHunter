#ifndef WORDGAME_H
#define WORDGAME_H

#include <QMainWindow>
#include <QTabWidget>
#include <QGridLayout>

#include "gamer.h"
#include "examer.h"
#include "wordhunter.h"
#include "wordmaker.h"
#include "rankinglist.h"
#include "detailinformation.h"

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
