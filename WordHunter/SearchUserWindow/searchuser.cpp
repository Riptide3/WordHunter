#include "searchuser.h"

SearchUser::SearchUser(QWidget *parent)
    : QWidget(parent)
{
    usernameLineEdit = new QLineEdit;
    usernameLineEdit->setPlaceholderText(tr("请输入您要查找用户的账号"));
    searchGamerButton = new QPushButton;
    searchGamerButton->setText(tr("查找玩家"));
    searchExamerButton = new QPushButton;
    searchExamerButton->setText(tr("查找出题人"));

    searchButton = new QGridLayout;
    searchButton->addWidget(searchGamerButton, 0, 0);
    searchButton->addWidget(searchExamerButton, 0, 1);
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(usernameLineEdit, 0, 0);
    mainLayout->addLayout(searchButton, 1, 0);

    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(searchGamerButton, SIGNAL(clicked()), this, SLOT(on_searchGamerButton_clicked()));
    connect(searchExamerButton, SIGNAL(clicked()), this, SLOT(on_searchExamerButton_clicked()));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
}

SearchUser::~SearchUser()
{

}

void SearchUser::on_searchGamerButton_clicked()
{
    QString username = usernameLineEdit->text().trimmed();
    if(username.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("账号不能为空!"), QMessageBox::Ok);
    }
    else
    {
        client->sendInfo(GET_GAMERINFO, username);
    }
}

void SearchUser::on_searchExamerButton_clicked()
{
    QString username = usernameLineEdit->text().trimmed();
    if(username.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("账号不能为空!"), QMessageBox::Ok);
    }
    else
    {
        client->sendInfo(GET_EXAMERINFO, username);
    }
}

void SearchUser::readInfo()
{
    QJsonObject receivedInfo = client->getInfo();
    FUNCTION func = static_cast<FUNCTION>(receivedInfo.take("function").toInt());
    qDebug() << "查找用户";
    if(func == GET_GAMERINFO)
    {
        QString nickname = receivedInfo.take("nickname").toString();
        QString username = receivedInfo.take("username").toString();
        int level = receivedInfo.take("level").toInt();
        int exp = receivedInfo.take("exp").toInt();
        int passedStage = receivedInfo.take("passedStage").toInt();

        if(username.isEmpty())
        {
            QMessageBox::information(this, tr("提示信息"), tr("抱歉，您查找的用户不存在"), QMessageBox::Ok);
        }
        else
        {
            Gamer gamer(nickname, username, level, exp, passedStage);
            UserInformation(gamer).exec();
        }
        usernameLineEdit->clear();
        usernameLineEdit->setFocus();
    }
    else if(func == GET_EXAMERINFO)
    {
        QString nickname = receivedInfo.take("nickname").toString();
        QString username = receivedInfo.take("username").toString();
        int level = receivedInfo.take("level").toInt();
        int exp = receivedInfo.take("exp").toInt();
        int questionNum = receivedInfo.take("questionNum").toInt();

        if(username.isEmpty())
        {
            QMessageBox::information(this, tr("提示信息"), tr("抱歉，您查找的用户不存在"), QMessageBox::Ok);
        }
        else
        {
            Examer examer(nickname, username, level, exp, questionNum);
            UserInformation(examer).exec();
        }
        usernameLineEdit->clear();
        usernameLineEdit->setFocus();
    }
}
