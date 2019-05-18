#ifndef WORDHUNTER_H
#define WORDHUNTER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
#include <QCoreApplication>
#include <QtGlobal>
#include <QMessageBox>

#include "User/gamer.h"
#include "Client/client.h"

class WordHunter: public QWidget
{
    Q_OBJECT

public:
    WordHunter(Gamer *_gamer, QWidget *parent = nullptr);
    ~WordHunter();
protected:
    void initUI();
signals:
private slots:
    void on_startButton_clicked();
    void on_endButton_clicked();
    void on_submitButton_clicked();
    void countdown();
    void readInfo();
private:
    void startGame();
    void endGame();
    void showNextWord();
    bool isCorrect();
    void updateInfo(const Gamer &gamer);
private:
    Client *client;
    Gamer *gamer;
    QString word;
    int wordNum;
    int stage;
    bool updating = true;

    QLabel *welcomeLabel;
    QPushButton *startButton;
    QPushButton *endButton;
    QPushButton *submitButton;
    QLabel *stageLabel;
    QLabel *wordLabel;
    QTimer *countdownTimer;
    QProgressBar *deadlineProgressBar;
    QLineEdit *wordInputLineEdit;
    QGridLayout *wordhunterLayout;
};

#endif // WORDHUNTER_H
