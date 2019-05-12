#include "rankinglist.h"

RankingList::RankingList(QWidget *parent)
    : QWidget(parent)
{
    gamerRanklist = new QTableWidget;
    examerRanklist = new QTableWidget;
    gamerRanklist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    examerRanklist->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(gamerRanklist, 0, 0);
    mainLayout->addWidget(examerRanklist, 0, 1);

    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(gamerRanklist->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortGamerColumn(int)));
    connect(examerRanklist->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortExamerColumn(int)));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));

    initRanklist();
}

RankingList::~RankingList()
{

}

void RankingList::initRanklist()
{
    gamerRanklist->setColumnCount(4);
    examerRanklist->setColumnCount(4);

    QStringList gamerHeader;
    gamerHeader << tr("昵称") << tr("账号") << tr("等级") << tr("闯关数");
    gamerRanklist->setHorizontalHeaderLabels(gamerHeader);
    QStringList examerHeader;
    examerHeader << tr("昵称") << tr("账号") << tr("等级") << tr("出题数");
    examerRanklist->setHorizontalHeaderLabels(examerHeader);

    QFont font = gamerRanklist->horizontalHeader()->font();
    font.setBold(true);
    gamerRanklist->horizontalHeader()->setFont(font);
    examerRanklist->horizontalHeader()->setFont(font);
    client->sendInfo(GET_GAMERRANKLIST);

}

void RankingList::refreshRanklist()
{
    gamerRanklist->clearContents();
    examerRanklist->clearContents();
    gamerRanklist->setRowCount(0);
    examerRanklist->setRowCount(0);
    client->sendInfo(GET_GAMERRANKLIST);
}

void RankingList::sortGamerColumn(int index)
{
    switch(index)
    {
        case 0:
        case 1:
            gamerRanklist->sortByColumn(index, Qt::AscendingOrder);
            break;
        default:
            gamerRanklist->sortByColumn(index, Qt::DescendingOrder);
            break;
    }
}

void RankingList::sortExamerColumn(int index)
{
    switch(index)
    {
        case 0:
        case 1:
            examerRanklist->sortByColumn(index, Qt::AscendingOrder);
            break;
        default:
            examerRanklist->sortByColumn(index, Qt::DescendingOrder);
            break;
    }
}

void RankingList::readInfo()
{
    QJsonArray receivedArrayInfo = client->getArrayInfo();
    QVector<GamerInfo> gamerList;
    QVector<ExamerInfo> examerList;
    GamerInfo gamer;
    ExamerInfo examer;
    QJsonObject receivedObjectInfo = receivedArrayInfo.at(0).toObject();
    FUNCTION func = static_cast<FUNCTION>(receivedObjectInfo.take("function").toInt());

    if(func == GET_GAMERRANKLIST)
    {
        qDebug() << "获取到了用户列表";
        for (auto it = receivedArrayInfo.begin(); it != receivedArrayInfo.end(); it++)
        {
            receivedObjectInfo = it->toObject();
            gamer.nickname = receivedObjectInfo.take("nickname").toString();
            gamer.username = receivedObjectInfo.take("username").toString();
            gamer.level = receivedObjectInfo.take("level").toInt();
            gamer.exp = receivedObjectInfo.take("exp").toInt();
            gamer.passedStage = receivedObjectInfo.take("passedStage").toInt();
            gamerList.append(gamer);
        }
        client->sendInfo(GET_EXAMERRANKLIST);
    }
    else if(func == GET_EXAMERRANKLIST)
    {
        for (auto it = receivedArrayInfo.begin(); it != receivedArrayInfo.end(); it++)
        {
            receivedObjectInfo = it->toObject();
            examer.nickname = receivedObjectInfo.take("nickname").toString();
            examer.username = receivedObjectInfo.take("username").toString();
            examer.level = receivedObjectInfo.take("level").toInt();
            examer.exp = receivedObjectInfo.take("exp").toInt();
            examer.questionNum = receivedObjectInfo.take("questionNum").toInt();
            examerList.append(examer);
        }
    }

    int rowIndex;
    for (auto gamerIter = gamerList.begin(); gamerIter != gamerList.end(); gamerIter++)
    {
        rowIndex = gamerRanklist->rowCount();
        gamerRanklist->setRowCount(rowIndex + 1);
        gamerRanklist->setItem(rowIndex, 0, new QTableWidgetItem(gamerIter->nickname));
        gamerRanklist->setItem(rowIndex, 1, new QTableWidgetItem(gamerIter->username));
        gamerRanklist->setItem(rowIndex, 2, new QTableWidgetItem(QString::number(gamerIter->level)));
        gamerRanklist->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(gamerIter->passedStage)));
    }

    for (auto examerIter = examerList.begin(); examerIter != examerList.end(); examerIter++)
    {
        rowIndex = examerRanklist->rowCount();
        examerRanklist->setRowCount(rowIndex + 1);
        examerRanklist->setItem(rowIndex, 0, new QTableWidgetItem(examerIter->nickname));
        examerRanklist->setItem(rowIndex, 1, new QTableWidgetItem(examerIter->username));
        examerRanklist->setItem(rowIndex, 2, new QTableWidgetItem(QString::number(examerIter->level)));
        examerRanklist->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(examerIter->questionNum)));
    }
}
