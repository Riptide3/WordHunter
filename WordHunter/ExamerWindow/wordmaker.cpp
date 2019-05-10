#include "wordmaker.h"

WordMaker::WordMaker(Examer *_examer, QWidget *parent)
    : QWidget(parent), examer(_examer)
{
    welcomeLabel = new QLabel;
    welcomeLabel->setText(examer->getNickname() + tr("，欢迎登录！"));
    wordInputTextEdit = new QPlainTextEdit;
    wordInputTextEdit->setPlaceholderText(tr("请输入单词，以换行分割\n注意：单词中不允许出现特殊符号！"));
    wordInputDoc = new QTextDocument;
    submitButton = new QPushButton;
    submitButton->setText(tr("确认添加"));

    wordmakerLayout = new QGridLayout(this);
    wordmakerLayout->addWidget(welcomeLabel, 0, 0);
    wordmakerLayout->addWidget(wordInputTextEdit, 1, 0);
    wordmakerLayout->addWidget(submitButton, 2, 0, 1, 1, Qt::AlignCenter);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(on_submitButton_clicked()));
}

WordMaker::~WordMaker()
{

}

void WordMaker::on_submitButton_clicked()
{
    wordInputDoc = wordInputTextEdit->document();
    QTextBlock block;
    int count = 0;
    QString word;

    for (block = wordInputDoc->begin(); block != wordInputDoc->end(); block = block.next())
    {
        word = block.text().trimmed();
        if(isValid(word))
        {
            if(database.addWord(word))
            {
                examer->addExp(word.length());
                examer->addQuestionNumber(1);
                examer->updateInfo(*examer);
                count++;
            }
        }
    }

    QMessageBox::information(this, tr("提示信息"), tr("成功添加") + QString::number(count) + tr("个单词"), QMessageBox::Ok);
    wordInputTextEdit->clear();
    wordInputTextEdit->setFocus();
}

bool WordMaker::isValid(const QString &word)
{
    bool valid = true;
    if(word.isEmpty())
    {
        valid = false;
    }
    else
    {
        for (auto it = word.begin(); it != word.end(); it++)
        {
            if((('A'<= *it) && (*it <= 'Z')) || (('a' <= *it) && (*it <= 'z')))
            {
                ; // do nothing
            }
            else
            {
                valid = false;
                return valid;
            }
        }
    }
    return  valid;
}
