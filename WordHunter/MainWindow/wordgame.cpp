#include "wordgame.h"

WordGame::WordGame(Gamer _gamer, QWidget *parent)
    : QMainWindow(parent), gamer(_gamer)
{
    this->resize(QSize(800, 600));

    wordhunter = new WordHunter(&gamer);
    rankingList = new RankingList;
    detailInfo = new DetailInformation(&gamer);
    searchUser = new SearchUser;
    contentTab = new QTabWidget;
    contentTab->addTab(wordhunter, tr("游戏"));
    contentTab->addTab(rankingList, tr("排行榜"));
    contentTab->addTab(detailInfo, tr("用户信息"));
    contentTab->addTab(searchUser, tr("查找用户"));

    this->setCentralWidget(contentTab);

    connect(contentTab, SIGNAL(tabBarClicked(int)), this, SLOT(refreshGamerInfo(int)));
}

WordGame::WordGame(Examer _examer, QWidget *parent)
    : QMainWindow(parent), examer(_examer)
{
    this->resize(QSize(800, 600));

    wordmaker = new WordMaker(&examer);
    rankingList = new RankingList;
    detailInfo = new DetailInformation(&examer);
    searchUser = new SearchUser;
    contentTab = new QTabWidget;
    contentTab->addTab(wordmaker, tr("出题"));
    contentTab->addTab(rankingList, tr("排行榜"));
    contentTab->addTab(detailInfo, tr("用户信息"));
    contentTab->addTab(searchUser, tr("查找用户"));

    this->setCentralWidget(contentTab);

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

void WordGame::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出"),
        QString(tr("退出游戏?")),
        QMessageBox::Yes | QMessageBox::No);

    if(button == QMessageBox::No)
    {
        event->ignore();
    }
    else
    {
        Database db;
        if(gamer.getUsername().isEmpty())
        {
            db.examerSignout(examer.getUsername());
            qDebug() << "出题人退出登录";
        }
        else
        {
            db.gamerSignout(gamer.getUsername());
            qDebug() << "玩家退出登录";
        }
        event->accept();
    }
}
