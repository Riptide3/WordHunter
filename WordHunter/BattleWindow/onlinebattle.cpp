#include "onlinebattle.h"

OnlineBattle::OnlineBattle(Gamer *_gamer, QWidget *parent)
    : QWidget(parent), gamer(_gamer)
{

    matchDialog = new MatchDialog(this);
    waitingDialog = new WaitingDialog(this);
    waitingDialog->setModal(true);

    client = new Client(this);
    client->initClient();
    client->connectServer();

    initUI();

    connect(matchButton, SIGNAL(clicked()), this, SLOT(on_matchButton_clicked()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(on_submitButton_clicked()));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
    connect(countdownTimer, SIGNAL(timeout()), this, SLOT(countdown()));
    connect(endGameTimer, SIGNAL(timeout()), this, SLOT(on_endGameTimer_timeout()));
    connect(wordInputLineEdit, SIGNAL(returnPressed()), this, SLOT(on_submitButton_clicked()));
}

OnlineBattle::~OnlineBattle()
{

}

void OnlineBattle::initUI()
{
    matchButton = new QPushButton;
    matchButton->setText(tr("开始匹配"));
    wordLabel = new QLabel;
    QFont font ("Comic Sans MS", 20, 75);
    wordLabel->setFont(font);
    wordLabel->hide();
    deadlineProgressBar = new QProgressBar;
    deadlineProgressBar->setTextVisible(false);
    deadlineProgressBar->hide();
    wordInputLineEdit = new QLineEdit;
    wordInputLineEdit->hide();
    submitButton = new QPushButton;
    submitButton->setText(tr("提交"));
    submitButton->hide();
    countdownTimer = new QTimer(this);
    endGameTimer = new QTimer(this);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(matchButton, 0, 0, Qt::AlignCenter);
    mainLayout->addWidget(wordLabel, 0, 0, Qt::AlignCenter);
    mainLayout->addWidget(deadlineProgressBar, 1, 0, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(wordInputLineEdit, 1, 0, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(submitButton, 2, 0, 1, 1, Qt::AlignCenter);
}

void OnlineBattle::on_matchButton_clicked()
{
    client->sendInfo(GAMERMATCH, gamer->getUsername());
    if(matchDialog->exec() == QDialog::Accepted)
    {
        qDebug() << "取消匹配";
        client->sendInfo(CANCELMATCH, gamer->getUsername());
    }
}

void OnlineBattle::on_submitButton_clicked()
{
    if(wordInputLineEdit->text().trimmed().isEmpty())
    {
        ; // do nothing
    }
    else if(wordInputLineEdit->text().trimmed() == words[wordNum])
    {
        correctNum++;
        wordInputLineEdit->clear();
        wordInputLineEdit->setFocus();
        qDebug() << "已答" << wordNum << "题";
        if(wordNum < 9)
        {
            nextWord();
        }
        else
        {
            endGame();
        }
    }
    else
    {
        wordInputLineEdit->clear();
        wordInputLineEdit->setFocus();
        qDebug() << "已答" << wordNum << "题";
        if(wordNum < 9)
        {
            nextWord();
        }
        else
        {
            endGame();
        }
    }
}

void OnlineBattle::startGame()
{
    matchButton->hide();
    wordLabel->show();
    deadlineProgressBar->show();
    countdownTimer->start(50);
    deadlineProgressBar->setRange(0, 40);
    deadlineProgressBar->setValue(40);
    endGameTimer->start(60000);

    wordNum = 0;
    correctNum = 0;
    timecost.start();
    wordLabel->setText(words[wordNum]);
}

void OnlineBattle::nextWord()
{
    wordInputLineEdit->hide();
    submitButton->hide();
    deadlineProgressBar->show();
    // 更改单词显示时间
    deadlineProgressBar->setRange(0, 40);
    deadlineProgressBar->setValue(40);

    wordNum++;
    wordLabel->setText(words[wordNum]);
}

void OnlineBattle::endGame()
{
    endGameTimer->stop();
    matchButton->show();
    wordLabel->hide();
    deadlineProgressBar->hide();
    wordInputLineEdit->clear();
    wordInputLineEdit->hide();
    submitButton->hide();
    countdownTimer->stop();
    words.clear();
    client->sendInfo(GET_PKRESULT, gamer->getUsername(), correctNum, timecost.elapsed());
}

void OnlineBattle::countdown()
{
    if(deadlineProgressBar->value() - 1 >= deadlineProgressBar->minimum())
    {
        deadlineProgressBar->setValue(deadlineProgressBar->value() - 1);
    }
    else
    {
        deadlineProgressBar->hide();
        deadlineProgressBar->setValue(deadlineProgressBar->minimum());
        wordLabel->clear();
        wordInputLineEdit->show();
        wordInputLineEdit->setFocus();
        submitButton->show();
    }
}

void OnlineBattle::on_endGameTimer_timeout()
{
    QMessageBox::warning(this, tr("警告"), tr("抱歉一分钟答题时间已到"), QMessageBox::Ok);
    endGame();
}

void OnlineBattle::updateInfo(const Gamer &gamer)
{
    GamerInfo gamerinfo;
    gamerinfo.nickname = gamer.getNickname();
    gamerinfo.username = gamer.getUsername();
    gamerinfo.level = gamer.getLevel();
    gamerinfo.exp = gamer.getExperiencePoint();
    gamerinfo.passedStage = gamer.getPassedStageNumber();

    client->sendInfo(UPDAT_PKINFO, gamerinfo);
}

void OnlineBattle::readInfo()
{
    QJsonArray receivedArrayInfo = client->getArrayInfo();
    QJsonObject receivedObjectInfo = receivedArrayInfo.at(0).toObject();
    FUNCTION func = static_cast<FUNCTION>(receivedObjectInfo.take("function").toInt());
    STATE state = static_cast<STATE>(receivedObjectInfo.take("state").toInt());

    qDebug() << gamer->getUsername() << "收到服务器发送来的" << func;

    if(func == GAMERMATCH)
    {
        if(state == MATCHSUCCESS)
        {
            qDebug() << "匹配成功，即将开始对战";
            matchDialog->close();
            receivedObjectInfo = receivedArrayInfo.at(1).toObject();
            for (int i = 0; i < 10; i++)
            {
                words.append(receivedObjectInfo.take("word" + QString::number(i)).toString());
            }
            startGame();
        }
        else
        {
            ; // do nothing just wait
        }
    }
    else if(func == GET_PKRESULT)
    {
        switch (state)
        {
            case WAIT:
                qDebug() << "收到等待消息";
                waiting = true;
                waitingDialog->show();
                break;
            case WIN:
                qDebug() << "pk获胜";
                gamer->addExp(30);
                updateInfo(*gamer);
                if(waiting)
                {
                    waitingDialog->close();
                }
                QMessageBox::information(this, tr("提示信息"), tr("恭喜您获胜！"), QMessageBox::Ok);
                break;
            case LOSE:
                qDebug() << "pk失败";
                gamer->subExp(30);
                updateInfo(*gamer);
                if(waiting)
                {
                    waitingDialog->close();
                }
                QMessageBox::information(this, tr("提示信息"), tr("很遗憾，您输了！"), QMessageBox::Ok);
                break;
            case DRAW:
                qDebug() << "平局";
                if(waiting)
                {
                    waitingDialog->close();
                }
                QMessageBox::information(this, tr("提示信息"), tr("平局，再接再厉！"), QMessageBox::Ok);
                break;
            default:
                // do nothing
                break;
        }
    }
}
