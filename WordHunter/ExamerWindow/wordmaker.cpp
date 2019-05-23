#include "wordmaker.h"

WordMaker::WordMaker(Examer *_examer, QWidget *parent)
    : QWidget(parent), examer(_examer)
{
    welcomeLabel = new QLabel;
    QFont welcomeLabelFont("STXingkai", 22, 50);
    welcomeLabel->setFont(welcomeLabelFont);
    welcomeLabel->setText(examer->getNickname() + tr("，欢迎！"));
    wordInputTextEdit = new QPlainTextEdit;
    wordInputTextEdit->setPlaceholderText(tr("请输入长度小于15的单词，以换行分割\n注意：单词中不允许出现特殊符号！词库中已有的单词不会被添加！"));
    wordInputDoc = new QTextDocument;
    submitButton = new QPushButton;
    submitButton->setText(tr("确认添加"));

    wordmakerLayout = new QGridLayout(this);
    wordmakerLayout->addWidget(welcomeLabel, 0, 0);
    wordmakerLayout->addWidget(wordInputTextEdit, 1, 0);
    wordmakerLayout->addWidget(submitButton, 2, 0, 1, 1, Qt::AlignCenter);


    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(submitButton, SIGNAL(clicked()), this, SLOT(on_submitButton_clicked()));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
}

WordMaker::~WordMaker()
{

}

void WordMaker::on_submitButton_clicked()
{
    wordInputDoc = wordInputTextEdit->document();
    QTextBlock block;
    successCount = 0;

    for (block = wordInputDoc->begin(); block != wordInputDoc->end(); block = block.next())
    {
        word = block.text().trimmed();
        if(isValid(word))
        {
            client->sendInfo(ADDWORD, word);
            while(adding || updating)
            {
                QTime t;
                t.start();
                while(t.elapsed() < 100)
                    QCoreApplication::processEvents();
            }
            adding = true;
            updating = true;
        }
    }
    QMessageBox::information(this, tr("提示信息"), tr("成功添加") + QString::number(successCount) + tr("个单词"), QMessageBox::Ok);
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
    else if(word.length() > 15)
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

void WordMaker::readInfo()
{
    QJsonObject receivedInfo = client->getInfo();
    FUNCTION func = static_cast<FUNCTION>(receivedInfo.take("function").toInt());
    if(func == ADDWORD)
    {
        bool success = receivedInfo.take("success").toBool();
        adding = false;
        if(success)
        {
            examer->addExp(word.length());
            examer->addQuestionNumber(1);
            updateInfo(*examer);
            qDebug() << "即将更新信息";
            successCount++;
        }
        else
        {
            updating = false;
        }
    }
    else if(func == UPDATE_EXAMERINFO)
    {
        updating = false;
        qDebug() << "信息更新";
    }
}

void WordMaker::updateInfo(const Examer &examer)
{
    ExamerInfo examerinfo;
    examerinfo.nickname = examer.getNickname();
    examerinfo.username = examer.getUsername();
    examerinfo.level = examer.getLevel();
    examerinfo.exp = examer.getExperiencePoint();
    examerinfo.questionNum = examer.getQuestionNumber();

    client->sendInfo(UPDATE_EXAMERINFO, examerinfo);
}
