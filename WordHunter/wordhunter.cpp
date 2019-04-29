#include "wordhunter.h"

WordHunter::WordHunter(Gamer *gamer, QWidget *parent)
    : QWidget(parent), gamer(gamer)
{
    initUI();

    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(endButton, SIGNAL(clicked()), this, SLOT(on_endButton_clicked()));
}

WordHunter::~WordHunter()
{

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
    submitIsPressed = true;
}

void WordHunter::startGame()
{
    int stage = gamer->getPassedStageNumber();

    if(nextStage(stage))
    {
        // TODO: 更新用户信息
        stage++;
    }
    else
    {
        // TODO: 弹出闯关失败界面
    }
}

bool WordHunter::nextStage(int stage)
{
    bool passed = false;
    for (int i = 0;i < stage / 10 + 1;i++)
    {
        word = db.getWord(3);

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
        connect(countdownTimer, SIGNAL(timeout()), this, SLOT(countdown()));

        while(!submitIsPressed)
        {
            QTime t;
            t.start();
            while(t.elapsed() < 100)
            QCoreApplication::processEvents();
        }

        if(wordInputLineEdit->text().trimmed() == word)
        {
            submitIsPressed = false;
            passed = true;
        }
        else
        {
            submitIsPressed = false;
            passed = false;
            return passed;
        }
    }
    return passed;
}

void WordHunter::endGame()
{
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
        deadlineProgressBar->setValue(deadlineProgressBar->minimum());
    }
}
