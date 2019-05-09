#include "wordgame.h"

WordGame::WordGame(Gamer _gamer, QWidget *parent)
    : QWidget(parent), gamer(_gamer)
{
    this->resize(QSize(800, 600));

    wordhunter = new WordHunter(&gamer);
    rankingList = new RankingList;
    detailInfo = new DetailInformation(&gamer);
    contentTab = new QTabWidget;
    contentTab->addTab(wordhunter, tr("游戏"));
    contentTab->addTab(rankingList, tr("排行榜"));
    contentTab->addTab(detailInfo, tr("用户信息"));

    mainLayout = new QGridLayout(this);

    mainLayout->addWidget(contentTab, 0, 0);

    connect(contentTab, SIGNAL(tabBarClicked(int)), this, SLOT(refreshGamerInfo(int)));
}

WordGame::WordGame(Examer _examer, QWidget *parent)
    : QWidget(parent), examer(_examer)
{
    this->resize(QSize(800, 600));

    wordmaker = new WordMaker(&examer);
    rankingList = new RankingList;
    detailInfo = new DetailInformation(&examer);
    contentTab = new QTabWidget;
    contentTab->addTab(wordmaker, tr("出题"));
    contentTab->addTab(rankingList, tr("排行榜"));
    contentTab->addTab(detailInfo, tr("用户信息"));

    mainLayout = new QGridLayout(this);

    mainLayout->addWidget(contentTab, 0, 0);

    connect(contentTab, SIGNAL(tabBarClicked(int)), this, SLOT(refreshExamerInfo(int)));
}

WordGame::~WordGame()
{

}

void WordGame::refreshGamerInfo(int index)
{
    switch(index)
    {
        case 1:
            rankingList->refreshRanklist();
            break;

        case 2:
            detailInfo->gamerInfoRefresh();
            break;

        default:
            break;
    }
}

void WordGame::refreshExamerInfo(int index)
{
    switch(index)
    {
        case 1:
            rankingList->refreshRanklist();
            break;

        case 2:
            detailInfo->examerInfoRefresh();
            break;

        default:
            break;
    }
}
