#include "matchdialog.h"

MatchDialog::MatchDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setMinimumSize(200, 200);
    this->setWindowTitle(tr("匹配"));
    this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);

    waitingLabel = new QLabel;
    waitingLabel->setText(tr("正在匹配"));
    cancelButton = new QPushButton;
    cancelButton->setText(tr("取消匹配"));
    waitingTimer = new QTimer(this);
    waitingTimer->start(300);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(waitingLabel, 0, 0, Qt::AlignCenter);
    mainLayout->addWidget(cancelButton, 1, 0, Qt::AlignCenter);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));
    connect(waitingTimer, SIGNAL(timeout()), this, SLOT(waiting()));
}

MatchDialog::~MatchDialog()
{

}

void MatchDialog::waiting()
{
    if(waitingLabel->text() == tr("正在匹配"))
    {
        waitingLabel->setText(tr("正在匹配."));
    }
    else if(waitingLabel->text() == tr("正在匹配."))
    {
        waitingLabel->setText(tr("正在匹配.."));
    }
    else if(waitingLabel->text() == tr("正在匹配.."))
    {
        waitingLabel->setText(tr("正在匹配..."));
    }
    else if(waitingLabel->text() == tr("正在匹配..."))
    {
        waitingLabel->setText(tr("正在匹配"));
    }
}

void MatchDialog::on_cancelButton_clicked()
{
    accept();
}
