#include "userinformation.h"

UserInformation::UserInformation(const Gamer &gamer, QWidget *parent)
    : QDialog(parent)
{
    this->setMinimumSize(300, 200);
    this->setWindowTitle(tr("玩家信息"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    nicknameLabel = new QLabel;
    nicknameLabel->setText(tr("昵称: ") + gamer.getNickname());
    usernameLabel = new QLabel;
    usernameLabel->setText(tr("用户名: ") + gamer.getUsername());
    levelLabel = new QLabel;
    levelLabel->setText(tr("等级: ") + QString::number(gamer.getLevel()));
    expLabel = new QLabel;
    expLabel->setText(tr("经验: ") + QString::number(gamer.getExperiencePoint()) + \
                      "/" + QString::number((gamer.getLevel() + 1) * 10));
    passedStageNumLabel = new QLabel;
    passedStageNumLabel->setText(tr("已闯关数: ") + QString::number(gamer.getPassedStageNumber()));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nicknameLabel, 0, 0);
    mainLayout->addWidget(usernameLabel, 1, 0);
    mainLayout->addWidget(levelLabel, 2, 0);
    mainLayout->addWidget(expLabel, 3, 0);
    mainLayout->addWidget(passedStageNumLabel, 4, 0);
}

UserInformation::UserInformation(const Examer &examer, QWidget *parent)
    : QDialog(parent)
{
    this->setMinimumSize(300, 200);
    this->setWindowTitle(tr("出题人信息"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    nicknameLabel = new QLabel;
    nicknameLabel->setText(tr("昵称:") + examer.getNickname());
    usernameLabel = new QLabel;
    usernameLabel->setText(tr("用户名: ") + examer.getUsername());
    levelLabel = new QLabel;
    levelLabel->setText(tr("等级: ") + QString::number(examer.getLevel()));
    expLabel = new QLabel;
    expLabel->setText(tr("经验: ") + QString::number(examer.getExperiencePoint()) + \
                      "/" + QString::number((examer.getLevel() + 1) * 10));
    questionNumLabel = new QLabel;
    questionNumLabel->setText(tr("出题数: ") + QString::number(examer.getQuestionNumber()));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nicknameLabel, 0, 0);
    mainLayout->addWidget(usernameLabel, 1, 0);
    mainLayout->addWidget(levelLabel, 2, 0);
    mainLayout->addWidget(expLabel, 3, 0);
    mainLayout->addWidget(questionNumLabel, 4, 0);
}
