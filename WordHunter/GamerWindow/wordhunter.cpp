#include "wordhunter.h"

WordHunter::WordHunter(Gamer *_gamer, QWidget *parent)
    : QWidget(parent), gamer(_gamer)
{
    initUI();

    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(endButton, SIGNAL(clicked()), this, SLOT(on_endButton_clicked()));
    connect(countdownTimer, SIGNAL(timeout()), this, SLOT(countdown()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(on_submitButton_clicked()));
    connect(wordInputLineEdit, SIGNAL(returnPressed()), this, SLOT(on_submitButton_clicked()));
}

WordHunter::~WordHunter()
{
    endGame();
}

void WordHunter::initUI()
{
    welcomeLabel = new QLabel;
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
    stageLabel->hide();
    wordLabel = new QLabel;
    wordLabel->hide();
    deadlineProgressBar = new QProgressBar;
    deadlineProgressBar->hide();
    wordInputLineEdit = new QLineEdit;
    wordInputLineEdit->hide();
    countdownTimer = new QTimer;

    wordhunterLayout = new QGridLayout(this);
    wordhunterLayout->addWidget(welcomeLabel, 0, 0);
    wordhunterLayout->addWidget(startButton, 1, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(endButton, 1, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(stageLabel, 2, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(wordLabel, 3, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(deadlineProgressBar, 4, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(wordInputLineEdit, 5, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(submitButton, 6, 0, 1, 1, Qt::AlignCenter);
}

void WordHunter::on_startButton_clicked()
{
    startButton->hide();
    endButton->show();
    submitButton->show();
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

        gamer->addExp(stage + 5);

        wordNum--;
        if(wordNum == 0)
        {
            stage++;
            gamer->addStage(1);
            wordNum = stage / 10 + 1;
        }
        gamer->updateInfo(*gamer);
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
        gamer->updateInfo(*gamer);
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
    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
    if(stage < 30)
    {
        while(word.isEmpty())
        {
            word = db.getWord(stage / 10 + rand() % 3 + 1);
        }
    }
    else
    {
        while(word.isEmpty())
        {
            word = db.getWord(7 + rand() % 14);
        }
    }
    stageLabel->setText(tr("关卡 ") + QString::number(stage));
    wordLabel->setText(word);

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
    qDebug() << "停止";
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
        wordLabel->clear();
        wordInputLineEdit->show();
        wordInputLineEdit->setFocus();
    }
}
