#include "wordhunter.h"

WordHunter::WordHunter(Gamer *_gamer, QWidget *parent)
    : QWidget(parent), gamer(_gamer)
{
    initUI();

    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(endButton, SIGNAL(clicked()), this, SLOT(on_endButton_clicked()));
    connect(countdownTimer, SIGNAL(timeout()), this, SLOT(countdown()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(on_submitButton_clicked()));
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
    wordhunterLayout->addWidget(wordLabel, 2, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(deadlineProgressBar, 3, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(wordInputLineEdit, 4, 0, 1, 1, Qt::AlignCenter);
    wordhunterLayout->addWidget(submitButton, 5, 0, 1, 1, Qt::AlignCenter);
}

void WordHunter::on_startButton_clicked()
{
    startButton->hide();
    endButton->show();
    submitButton->show();
    wordLabel->show();
    deadlineProgressBar->show();
    wordInputLineEdit->show();

    startGame();
}

void WordHunter::on_endButton_clicked()
{
    endButton->hide();
    submitButton->hide();
    wordLabel->hide();
    deadlineProgressBar->hide();
    wordInputLineEdit->hide();
    startButton->show();

    endGame();
}

void WordHunter::on_submitButton_clicked()
{
    if(isCorrect())
    {
        wordInputLineEdit->clear();

        wordNum--;
        if(wordNum == 0)
        {
            stage++;
            wordNum = stage / 10 + 1;
        }
        showNextWord();
        // TODO: 更新用户信息
    }
    else if(wordInputLineEdit->text().trimmed().isEmpty())
    {
        ; // do nothing
    }
    else
    {
        wordInputLineEdit->clear();

        endGame();
        // TODO: 更新用户信息，弹出闯关失败界面，回到开始界面
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
    word = db.getWord(4);
    wordLabel->setText(word);

    deadlineProgressBar->setRange(0, 100);
    deadlineProgressBar->setValue(100);

    if(stage < 100)
    {
        countdownTimer->start(60 - 5 * (stage / 10));
    }
    else
    {
        countdownTimer->start(20);
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
    }
}
