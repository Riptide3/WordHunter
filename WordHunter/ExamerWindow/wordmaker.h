#ifndef WORDMAKER_H
#define WORDMAKER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextDocument>
#include <QTextBlock>
#include <QGridLayout>

#include "User/examer.h"
#include "Database/database.h"

class WordMaker: public QWidget
{
    Q_OBJECT

public:
    WordMaker(Examer *_examer, QWidget *parent = nullptr);
    ~WordMaker();

private:
    bool isValid(const QString &word);

signals:

public slots:
    void on_submitButton_clicked();

private:
    Database database;

    Examer *examer;

    QLabel *welcomeLabel;
    QPushButton *submitButton;
    QGridLayout *wordmakerLayout;

    QPlainTextEdit *wordInputTextEdit;
    QTextDocument *wordInputDoc;
};

#endif // WORDMAKER_H
