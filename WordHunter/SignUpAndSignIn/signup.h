#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QButtonGroup>
#include <QGridLayout>

#include "Client/client.h"

class SignUp: public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();
protected:
    void initUI();
private:
    QLabel *nicknameLabel, *usernameLabel, *passwordLabel, *rePasswordLabel;
    QLineEdit *nicknameLineEdit, *usernameLineEdit, *passwordLineEdit, *rePasswordLineEdit;
    QRadioButton *gamerButton, *examerButton;
    QPushButton *signupButton;
    QButtonGroup *selectButton;

    Client *client;
private slots:
    void on_signupButton_clicked();
    void readInfo();
};

#endif // SIGNUP_H
