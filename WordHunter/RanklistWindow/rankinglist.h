#ifndef RANKINGLIST_H
#define RANKINGLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QGridLayout>

class RankingList: public QWidget
{
    Q_OBJECT

public:
    RankingList(QWidget *parent = nullptr);
    ~RankingList();
private:
    void initRanklist();
private:
    QTableWidget *gamerRanklist;
    QTableWidget *examerRanklist;

    QGridLayout *mainLayout;
};

#endif // RANKINGLIST_H
