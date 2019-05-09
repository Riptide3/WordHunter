#ifndef WORDHUNTER_H
#define WORDHUNTER_H

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

#include "User/gamer.h"
#include "Database/database.h"

class WordHunter: public QWidget
{
    Q_OBJECT

public:
    WordHunter(Gamer *_gamer, QWidget *parent = nullptr);
    ~WordHunter();
protected:
    void initUI();
signals:
public slots:
    void on_startButton_clicked();
    void on_endButton_clicked();
    void on_submitButton_clicked();
    void countdown();
private:
    void startGame();
    void endGame();
    void showNextWord();
    bool isCorrect();
private:
    Gamer *gamer;
    Database db;
    QString word;
    int wordNum;
    int stage;

    QLabel *welcomeLabel;
    QPushButton *startButton;
    QPushButton *endButton;
    QPushButton *submitButton;
    QLabel *wordLabel;
    QTimer *countdownTimer;
    QProgressBar *deadlineProgressBar;
    QLineEdit *wordInputLineEdit;
    QGridLayout *wordhunterLayout;
};

#endif // WORDHUNTER_H
