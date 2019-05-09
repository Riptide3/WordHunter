#ifndef DETAILINFORMATION_H
#define DETAILINFORMATION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include "User/gamer.h"
#include "User/examer.h"

class DetailInformation: public QWidget
{
    Q_OBJECT

public:
    DetailInformation(Gamer *_gamer, QWidget *parent = nullptr);
    DetailInformation(Examer *_examer, QWidget *parent = nullptr);
    ~DetailInformation();

    void gamerInfoRefresh();
    void examerInfoRefresh();
private:
    Gamer *gamer;
    Examer *examer;

    QLabel *nicknameLabel;
    QLabel *usernameLabel;
    QLabel *levelLabel;
    QLabel *expLabel;
    QLabel *passedStageNumLabel;
    QLabel *questionNumLabel;

    QGridLayout *mainLayout;
};

#endif // DETAILINFORMATION_H
