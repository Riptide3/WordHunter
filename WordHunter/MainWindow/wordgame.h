#ifndef WORDGAME_H
#define WORDGAME_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTime>

#include "User/gamer.h"
#include "User/examer.h"
#include "GamerWindow/wordhunter.h"
#include "ExamerWindow/wordmaker.h"
#include "RanklistWindow/rankinglist.h"
#include "DetailinfoWindow/detailinformation.h"
#include "SearchUserWindow/searchuser.h"
#include "Client/client.h"

class WordGame: public QMainWindow
{
    Q_OBJECT

public:
    WordGame(Gamer _gamer, QWidget *parent = nullptr);
    WordGame(Examer _examer, QWidget *parent = nullptr);
    ~WordGame();
private:
    Gamer gamer;
    Examer examer;
    Client *client;
    bool online = true;

    QTabWidget *contentTab;
    WordHunter *wordhunter;
    WordMaker *wordmaker;
    RankingList *rankingList;
    DetailInformation *detailInfo;
    SearchUser *searchUser;

    QWidget *centralWidget;
    QGridLayout *mainLayout;
private slots:
    void refreshGamerInfo(int index);
    void refreshExamerInfo(int index);
    void closeEvent(QCloseEvent *event);
    void readInfo();
};

#endif // WORDGAME_H
