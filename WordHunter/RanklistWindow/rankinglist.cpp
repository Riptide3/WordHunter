#include <QHeaderView>

#include "rankinglist.h"
#include "Database/database.h"

RankingList::RankingList(QWidget *parent)
    : QWidget(parent)
{
    gamerRanklist = new QTableWidget;
    examerRanklist = new QTableWidget;
    gamerRanklist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    examerRanklist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    initRanklist();

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(gamerRanklist, 0, 0);
    mainLayout->addWidget(examerRanklist, 0, 1);
}

RankingList::~RankingList()
{

}

void RankingList::initRanklist()
{
    Database db;
    QVector<Gamer> gamers = db.getGamerRanklist();
    QVector<Examer> examers = db.getExamerRanklist();

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

    int rowIndex;
    QVector<Gamer>::iterator gamerIter;
    for (gamerIter = gamers.begin(); gamerIter != gamers.end(); gamerIter++)
    {
        rowIndex = gamerRanklist->rowCount();
        gamerRanklist->setRowCount(rowIndex + 1);
        gamerRanklist->setItem(rowIndex, 0, new QTableWidgetItem(gamerIter->getNickname()));
        gamerRanklist->setItem(rowIndex, 1, new QTableWidgetItem(gamerIter->getUsername()));
        gamerRanklist->setItem(rowIndex, 2, new QTableWidgetItem(QString::number(gamerIter->getLevel())));
        gamerRanklist->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(gamerIter->getPassedStageNumber())));
    }
    QVector<Examer>::iterator examerIter;
    for (examerIter = examers.begin(); examerIter != examers.end(); examerIter++)
    {
        rowIndex = examerRanklist->rowCount();
        examerRanklist->setRowCount(rowIndex + 1);
        examerRanklist->setItem(rowIndex, 0, new QTableWidgetItem(examerIter->getNickname()));
        examerRanklist->setItem(rowIndex, 1, new QTableWidgetItem(examerIter->getUsername()));
        examerRanklist->setItem(rowIndex, 2, new QTableWidgetItem(QString::number(examerIter->getLevel())));
        examerRanklist->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(examerIter->getQuestionNumber())));
    }
}
