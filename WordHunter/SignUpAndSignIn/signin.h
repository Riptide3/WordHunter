#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QButtonGroup>
#include <QDebug>

#include "MainWindow/wordgame.h"
#include "User/gamer.h"
#include "User/examer.h"
#include "Client/client.h"

class SignIn: public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();
protected:
    void initUI();
private:
    QLabel *usernameLabel, *passwordLabel;
    QLineEdit *usernameLineEdit, *passwordLineEdit;
    QRadioButton *gamerButton, *examerButton;
    QPushButton *signinButton, *signupButton;
    QButtonGroup *selectButton;

    QGridLayout *selectUserLayout;
    QGridLayout *signinLayout;

    WordGame *wordgame;

    Client *client;
private slots:
    void on_signinButton_clicked();
    void on_signupButton_clicked();
    void readInfo();
};

#endif // SIGNIN_H
