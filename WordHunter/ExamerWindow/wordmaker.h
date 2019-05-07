#ifndef WORDMAKER_H
#define WORDMAKER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

#include "User/examer.h"
#include "Database/database.h"

class WordMaker: public QWidget
{
    Q_OBJECT

public:
    WordMaker(Examer *_examer, QWidget *parent = nullptr);
    ~WordMaker();

signals:

public slots:
    void on_submitButton_clicked();

private:
    Database database;

    Examer *examer;

    QLabel *welcomeLabel;
    QLineEdit *wordInputLineEdit;
    QPushButton *submitButton;
    QGridLayout *wordmakerLayout;
};

#endif // WORDMAKER_H
