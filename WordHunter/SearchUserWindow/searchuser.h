#ifndef SEARCHUSER_H
#define SEARCHUSER_H

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>

#include "User/gamer.h"
#include "User/examer.h"
#include "userinformation.h"

class SearchUser: public QWidget
{
    Q_OBJECT

public:
    SearchUser(QWidget *parent = nullptr);
    ~SearchUser();
private slots:
    void on_searchGamerButton_clicked();
    void on_searchExamerButton_clicked();
private:
    QLineEdit *usernameLineEdit;
    QPushButton *searchGamerButton;
    QPushButton *searchExamerButton;
    QGridLayout *searchButton;
    QGridLayout *mainLayout;
};

#endif // SEARCHUSER_H
