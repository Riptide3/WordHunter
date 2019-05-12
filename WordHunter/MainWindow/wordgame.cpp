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
    contentTab->addTab(wordhunter, tr("单词猎人"));
    contentTab->addTab(rankingList, tr("排行榜"));
    contentTab->addTab(detailInfo, tr("用户信息"));
    contentTab->addTab(searchUser, tr("查找用户"));

    centralWidget = new QWidget(this);
    mainLayout = new QGridLayout;
    mainLayout->addWidget(contentTab);
    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);

    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(contentTab, SIGNAL(tabBarClicked(int)), this, SLOT(refreshGamerInfo(int)));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
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
    contentTab->addTab(wordmaker, tr("单词生产户"));
    contentTab->addTab(rankingList, tr("排行榜"));
    contentTab->addTab(detailInfo, tr("用户信息"));
    contentTab->addTab(searchUser, tr("查找用户"));

    centralWidget = new QWidget(this);
    mainLayout = new QGridLayout;
    mainLayout->addWidget(contentTab);
    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);

    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(contentTab, SIGNAL(tabBarClicked(int)), this, SLOT(refreshExamerInfo(int)));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
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
        if(gamer.getUsername().isEmpty())
        {
            client->sendInfo(EXAMER_SIGNOUT, examer.getUsername());
            qDebug() << "出题人退出登录";
        }
        else
        {
            client->sendInfo(GAMER_SIGNOUT, gamer.getUsername());
            qDebug() << "玩家退出登录";
        }
        while(online)
        {
            QTime t;
            t.start();
            while(t.elapsed() < 100)
            QCoreApplication::processEvents();
        }
        event->accept();
    }
}

void WordGame::readInfo()
{
    QJsonObject receivedInfo = client->getInfo();
    FUNCTION func = static_cast<FUNCTION>(receivedInfo.take("function").toInt());
    qDebug() << "退出成功";
    if(func == GAMER_SIGNOUT || func == EXAMER_SIGNOUT)
    {
        online = false;
    }
}
