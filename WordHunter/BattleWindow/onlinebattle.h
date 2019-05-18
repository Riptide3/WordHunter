#ifndef ONLINEBATTLE_H
#define ONLINEBATTLE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QtGlobal>
#include <QMessageBox>

#include "User/gamer.h"
#include "Client/client.h"
#include "BattleWindow/matchdialog.h"
#include "BattleWindow/waitingdialog.h"

class OnlineBattle : public QWidget
{
    Q_OBJECT
public:
    explicit OnlineBattle(Gamer *_gamer, QWidget *parent = nullptr);
    ~OnlineBattle();
private:
    void initUI();
    void startGame();
    void nextWord();
    void endGame();
    void updateInfo(const Gamer &gamer);
signals:

public slots:
    void on_matchButton_clicked();
    void on_submitButton_clicked();
    void readInfo();
    void countdown();
    void on_endGameTimer_timeout();
private:
    Client *client;
    Gamer *gamer;
    bool cancelMatch;
    bool waiting = false;
    QTime timecost;
    QVector<QString> words;
    int wordNum;
    int correctNum;

    QPushButton *matchButton;
    QLabel *wordLabel;
    QTimer *endGameTimer;
    QTimer *countdownTimer;
    QProgressBar *deadlineProgressBar;
    QLineEdit *wordInputLineEdit;
    QPushButton *submitButton;
    QGridLayout *mainLayout;

    WaitingDialog *waitingDialog;
    MatchDialog *matchDialog;
};

#endif // ONLINEBATTLE_H
