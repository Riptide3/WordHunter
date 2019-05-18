#include "waitingdialog.h"

WaitingDialog::WaitingDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setMinimumSize(200, 200);
    this->setWindowTitle(tr("等待"));
    this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);

    waitingLabel = new QLabel;
    waitingLabel->setText(tr("正在等待对方完成"));
    waitingTimer = new QTimer(this);
    waitingTimer->start(300);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(waitingLabel, 0, 0, Qt::AlignCenter);

    connect(waitingTimer, SIGNAL(timeout()), this, SLOT(waiting()));
}

WaitingDialog::~WaitingDialog()
{

}

void WaitingDialog::waiting()
{
    if(waitingLabel->text() == tr("正在等待对方完成"))
    {
        waitingLabel->setText(tr("正在等待对方完成."));
    }
    else if(waitingLabel->text() == tr("正在等待对方完成."))
    {
        waitingLabel->setText(tr("正在等待对方完成.."));
    }
    else if(waitingLabel->text() == tr("正在等待对方完成.."))
    {
        waitingLabel->setText(tr("正在等待对方完成..."));
    }
    else if(waitingLabel->text() == tr("正在等待对方完成..."))
    {
        waitingLabel->setText(tr("正在等待对方完成"));
    }
}

void WaitingDialog::selfClose()
{
    accept();
}
