#include "wordhunter.h"

WordHunter::WordHunter(Gamer *_gamer, QWidget *parent)
    : QWidget(parent), gamer(_gamer)
{
    initUI();

    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(endButton, SIGNAL(clicked()), this, SLOT(on_endButton_clicked()));
    connect(countdownTimer, SIGNAL(timeout()), this, SLOT(countdown()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(on_submitButton_clicked()));
    connect(wordInputLineEdit, SIGNAL(returnPressed()), this, SLOT(on_submitButton_clicked()));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
}

WordHunter::~WordHunter()
{
    endGame();
}

void WordHunter::initUI()
{
    welcomeLabel = new QLabel;
    QFont welcomeLabelFont("STXingkai", 22, 50);
    welcomeLabel->setFont(welcomeLabelFont);
    welcomeLabel->setText(gamer->getNickname() + tr("，欢迎！"));
    startButton = new QPushButton;
    startButton->setText(tr("我准备好了┗|*｀0′*|┛"));
    endButton = new QPushButton;
    endButton->setText(tr("我不想玩了o(╥﹏╥)o"));
    endButton->hide();
    submitButton = new QPushButton;
    submitButton->setText(tr("提交"));
    submitButton->hide();
    stageLabel = new QLabel;
    QFont stageLabelFont("KaiTi", 24, 75);
    stageLabel->setFont(stageLabelFont);
    stageLabel->hide();
    wordLabel = new QLabel;
    QFont wordLabelFont ("Comic Sans MS", 20, 75);
    wordLabel->setFont(wordLabelFont);
    wordLabel->hide();
    deadlineProgressBar = new QProgressBar;
    deadlineProgressBar->setTextVisible(false);
    deadlineProgressBar->hide();
    wordInputLineEdit = new QLineEdit;
    wordInputLineEdit->hide();
    countdownTimer = new QTimer(this);

    wordhunterLayout = new QGridLayout(this);
    wordhunterLayout->addWidget(welcomeLabel, 0, 0);
    wordhunterLayout->addWidget(startButton, 1, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(endButton, 1, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(stageLabel, 2, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(wordLabel, 3, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(deadlineProgressBar, 4, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(wordInputLineEdit, 4, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(submitButton, 5, 0, 1, 1, Qt::AlignCenter);
}

void WordHunter::on_startButton_clicked()
{
    startButton->hide();
    endButton->show();
    stageLabel->show();
    wordLabel->show();
    deadlineProgressBar->show();

    startGame();
}

void WordHunter::on_endButton_clicked()
{
    endGame();
}

void WordHunter::on_submitButton_clicked()
{
    if(isCorrect())
    {
        wordInputLineEdit->clear();
        wordInputLineEdit->hide();
        submitButton->hide();

        gamer->addExp(stage + 5);

        wordNum--;
        if(wordNum == 0)
        {
            stage++;
            gamer->addStage(1);
            wordNum = stage / 10 + 1;
        }
        updateInfo(*gamer);
        while(updating)
        {
            QTime t;
            t.start();
            while(t.elapsed() < 100)
                QCoreApplication::processEvents();
        }
        updating = true;
        word = "";
        showNextWord();
    }
    else if(wordInputLineEdit->text().trimmed().isEmpty())
    {
        ; // do nothing
    }
    else
    {
        gamer->addExp(1);
        updateInfo(*gamer);
        while(updating)
        {
            QTime t;
            t.start();
            while(t.elapsed() < 100)
                QCoreApplication::processEvents();
        }
        updating = true;
        wordInputLineEdit->clear();
        word = "";
        QMessageBox::warning(this, tr("警告!"), tr("挑战失败，请重新来过!"), QMessageBox::Ok);
        endGame();
    }
}

void WordHunter::startGame()
{
    stage = gamer->getPassedStageNumber();
    wordNum = stage / 10 + 1;
    showNextWord();
}

void WordHunter::showNextWord()
{
    /* 单词难度调整 */
    int difficulty;
    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
    if(stage < 30)
    {
        difficulty = stage / 10 + rand() % 3 + 3;
        client->sendInfo(GETWORD, difficulty);
    }
    else
    {
        difficulty = 7 + rand() % 9;
        client->sendInfo(GETWORD, difficulty);
    }
    stageLabel->setText(tr("关卡 ") + QString::number(stage));
}

bool WordHunter::isCorrect()
{
    if(wordInputLineEdit->text().trimmed() == word)
    {
        qDebug() << "正确";
        return true;
    }
    else
    {
        qDebug() << "错误";
        return false;
    }
}

void WordHunter::endGame()
{
    endButton->hide();
    submitButton->hide();
    stageLabel->hide();
    wordLabel->hide();
    deadlineProgressBar->hide();
    wordInputLineEdit->hide();
    startButton->show();

    countdownTimer->stop();
}

void WordHunter::countdown()
{
    if(deadlineProgressBar->value() - 1 >= deadlineProgressBar->minimum())
    {
        deadlineProgressBar->setValue(deadlineProgressBar->value() - 1);
    }
    else
    {
        countdownTimer->stop();
        deadlineProgressBar->setValue(deadlineProgressBar->minimum());
        deadlineProgressBar->hide();
        wordLabel->clear();
        wordInputLineEdit->show();
        wordInputLineEdit->setFocus();
        submitButton->show();
    }
}

void WordHunter::readInfo()
{
    QJsonObject receivedInfo = client->getInfo();
    FUNCTION func = static_cast<FUNCTION>(receivedInfo.take("function").toInt());
    word = receivedInfo.take("word").toString();
    if(func == GETWORD)
    {
        qDebug() << "从服务器中取出单词" << word;

        countdownTimer->start(50);

        /* 计时时间调整 */
        if(stage < 70)
        {
            deadlineProgressBar->setRange(0, 80 - stage);
            deadlineProgressBar->setValue(80 - stage);
        }
        else
        {
            deadlineProgressBar->setRange(0, 10);
            deadlineProgressBar->setValue(10);
        }
        QTime t;
        t.start();
        while(t.elapsed() < 60)
            QCoreApplication::processEvents();
        deadlineProgressBar->show();
        wordLabel->setText(word);
    }
    else if(func == UPDATE_GAMERINFO)
    {
        updating = false;
        qDebug() << "信息更新";
    }
}

void WordHunter::updateInfo(const Gamer &gamer)
{
    GamerInfo gamerinfo;
    gamerinfo.nickname = gamer.getNickname();
    gamerinfo.username = gamer.getUsername();
    gamerinfo.level = gamer.getLevel();
    gamerinfo.exp = gamer.getExperiencePoint();
    gamerinfo.passedStage = gamer.getPassedStageNumber();

    client->sendInfo(UPDATE_GAMERINFO, gamerinfo);
}

