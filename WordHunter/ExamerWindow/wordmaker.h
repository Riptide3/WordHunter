#ifndef WORDMAKER_H
#define WORDMAKER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextDocument>
#include <QTextBlock>
#include <QGridLayout>
#include <QMessageBox>

#include "User/examer.h"
#include "Client/client.h"

class WordMaker: public QWidget
{
    Q_OBJECT

public:
    WordMaker(Examer *_examer, QWidget *parent = nullptr);
    ~WordMaker();

private:
    bool isValid(const QString &word);
    void updateInfo(const Examer &examer);

public slots:
    void on_submitButton_clicked();
    void readInfo();

private:
    QString word;
    int successCount;
    bool updating = true;
    bool adding = true;
    Client *client;

    Examer *examer;

    QLabel *welcomeLabel;
    QPushButton *submitButton;
    QGridLayout *wordmakerLayout;

    QPlainTextEdit *wordInputTextEdit;
    QTextDocument *wordInputDoc;
};

#endif // WORDMAKER_H
