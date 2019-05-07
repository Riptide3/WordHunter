#include "detailinformation.h"

DetailInformation::DetailInformation(Gamer &gamer) : gamer(gamer)
{
    nicknameLabel = new QLabel;
    nicknameLabel->setText(tr("昵称: ") + gamer.getNickname());
    usernameLabel = new QLabel;
    usernameLabel->setText(tr("用户名: ") + gamer.getUsername());
    levelLabel = new QLabel;
    levelLabel->setText(tr("等级: ") + QString::number(gamer.getLevel()));
    expLabel = new QLabel;
    expLabel->setText(tr("经验: ") + QString::number(gamer.getExperiencePoint()));
    passedStageNumLabel = new QLabel;
    passedStageNumLabel->setText(tr("已闯关数: ") + QString::number(gamer.getPassedStageNumber()));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nicknameLabel, 0, 0);
    mainLayout->addWidget(usernameLabel, 1, 0);
    mainLayout->addWidget(levelLabel, 2, 0);
    mainLayout->addWidget(expLabel, 3, 0);
    mainLayout->addWidget(passedStageNumLabel, 4, 0);
}

DetailInformation::DetailInformation(Examer &examer) : examer(examer)
{
    nicknameLabel = new QLabel;
    nicknameLabel->setText(tr("昵称:") + examer.getNickname());
    usernameLabel = new QLabel;
    usernameLabel->setText(tr("用户名: ") + examer.getUsername());
    levelLabel = new QLabel;
    levelLabel->setText(tr("等级: ") + QString::number(examer.getLevel()));
    expLabel = new QLabel;
    expLabel->setText(tr("经验: ") + QString::number(examer.getExperiencePoint()));
    questionNumLabel = new QLabel;
    questionNumLabel->setText(tr("出题数: ") + QString::number(examer.getQuestionNumber()));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nicknameLabel, 0, 0);
    mainLayout->addWidget(usernameLabel, 1, 0);
    mainLayout->addWidget(levelLabel, 2, 0);
    mainLayout->addWidget(expLabel, 3, 0);
    mainLayout->addWidget(questionNumLabel, 4, 0);
}

DetailInformation::~DetailInformation()
{

}
