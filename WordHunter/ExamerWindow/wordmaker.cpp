#include "wordmaker.h"

WordMaker::WordMaker(Examer *_examer, QWidget *parent)
    : QWidget(parent), examer(_examer)
{
    welcomeLabel = new QLabel;
    welcomeLabel->setText(examer->getNickname() + tr("，欢迎登录！"));
    wordInputLineEdit = new QLineEdit;
    wordInputLineEdit->setFocus();
    submitButton = new QPushButton;
    submitButton->setText(tr("确认添加"));

    wordmakerLayout = new QGridLayout(this);
    wordmakerLayout->addWidget(welcomeLabel, 0, 0);
    wordmakerLayout->addWidget(wordInputLineEdit, 1, 0, 1, 1, Qt::AlignCenter);
    wordmakerLayout->addWidget(submitButton, 2, 0, 1, 1, Qt::AlignCenter);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(on_submitButton_clicked()));
}

WordMaker::~WordMaker()
{

}

void WordMaker::on_submitButton_clicked()
{
    if(database.addWord(wordInputLineEdit->text().trimmed()))
    {
        QMessageBox::information(this, tr("提示信息"), tr("添加成功"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, tr("提示信息"), tr("添加失败，单词已存在"), QMessageBox::Ok);
    }
    wordInputLineEdit->clear();
    wordInputLineEdit->setFocus();
}
