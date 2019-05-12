#ifndef RANKINGLIST_H
#define RANKINGLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QGridLayout>
#include <QHeaderView>

#include "Client/client.h"

class RankingList: public QWidget
{
    Q_OBJECT

public:
    RankingList(QWidget *parent = nullptr);
    ~RankingList();
    void refreshRanklist();
private slots:
    void sortGamerColumn(int index);
    void sortExamerColumn(int index);
    void readInfo();
private:
    void initRanklist();
private:
    Client *client;

    QTableWidget *gamerRanklist;
    QTableWidget *examerRanklist;

    QGridLayout *mainLayout;
};

#endif // RANKINGLIST_H
