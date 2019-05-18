#include "signin.h"
#include "signup.h"

SignIn::SignIn(QWidget *parent)
    : QDialog(parent)
{
    initUI();

    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(signinButton, SIGNAL(clicked()), this, SLOT(on_signinButton_clicked()));
    connect(signupButton, SIGNAL(clicked()), this, SLOT(on_signupButton_clicked()));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
}

SignIn::~SignIn()
{

}

void SignIn::initUI()
{
    this->setMinimumSize(300, 200);
    this->setWindowTitle(tr("登录"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    usernameLabel = new QLabel;
    usernameLabel->setText(tr("账号:"));
    usernameLineEdit = new QLineEdit;
    usernameLineEdit->setPlaceholderText(tr("请输入用户名!"));
    passwordLabel = new QLabel;
    passwordLabel->setText(tr("密码:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setPlaceholderText(tr("请输入密码!"));
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    gamerButton = new QRadioButton;
    gamerButton->setText(tr("玩家"));
    gamerButton->setChecked(true);
    examerButton = new QRadioButton;
    examerButton->setText(tr("出题人"));
    signinButton = new QPushButton;
    signinButton->setText(tr("登录"));
    signupButton = new QPushButton;
    signupButton->setText(tr("注册"));
    selectButton = new QButtonGroup;
    selectButton->addButton(gamerButton, 0);
    selectButton->addButton(examerButton, 1);

    selectUserLayout = new QGridLayout;
    selectUserLayout->addWidget(gamerButton, 0, 0);
    selectUserLayout->addWidget(examerButton, 0, 1);
    signinLayout = new QGridLayout(this);
    signinLayout->addWidget(usernameLabel, 0, 0);
    signinLayout->addWidget(usernameLineEdit, 0,1);
    signinLayout->addWidget(passwordLabel, 1, 0);
    signinLayout->addWidget(passwordLineEdit, 1,1);
    signinLayout->addLayout(selectUserLayout, 2, 0, 1, 2, Qt::AlignCenter);
    signinLayout->addWidget(signinButton, 3, 0, 1, 2, Qt::AlignCenter);
    signinLayout->addWidget(signupButton, 4, 0, 1, 2, Qt::AlignCenter);
}

void SignIn::on_signinButton_clicked()
{
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text().trimmed();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("账号密码不能为空!"), QMessageBox::Ok);
    }
    else
    {
        if(selectButton->checkedId() == 0)
        {
            client->sendInfo(GAMER_SIGNIN, username, password);
        }
        else if(selectButton->checkedId() == 1)
        {
            client->sendInfo(EXAMER_SIGNIN, username, password);
        }
    }
}

void SignIn::on_signupButton_clicked()
{
    SignUp signup;
    signup.exec();
}

void SignIn::readInfo()
{
    QJsonObject receivedInfo = client->getInfo();
    QString username = usernameLineEdit->text().trimmed();
    FUNCTION func = static_cast<FUNCTION>(receivedInfo.take("function").toInt());
    qDebug() << "不知道什么时候又收到了消息" << func;
    if(func == GAMER_SIGNIN || func == EXAMER_SIGNIN)
    {
        qDebug() << "收到登录反馈信息";
        STATE state = static_cast<STATE>(receivedInfo.take("state").toInt());
        if(state == OFFLINE && selectButton->checkedId() == 0)
        {
            QMessageBox::information(this, tr("提示信息"), tr("登录成功!"), QMessageBox::Ok);
            client->sendInfo(GET_GAMERINFO, username);
        }
        else if(state == OFFLINE && selectButton->checkedId() == 1)
        {
            QMessageBox::information(this, tr("提示信息"), tr("登录成功!"), QMessageBox::Ok);

            client->sendInfo(GET_EXAMERINFO, username);
        }
        else if(state == ONLINE)
        {
            QMessageBox::warning(this, tr("警告"), tr("该用户已经登录"), QMessageBox::Ok);
            usernameLineEdit->clear();
            passwordLineEdit->clear();
            usernameLineEdit->setFocus();
        }
        else if(state == WRONGPASSWD)
        {
            QMessageBox::warning(this, tr("警告"), tr("密码错误!"), QMessageBox::Ok);
            usernameLineEdit->clear();
            passwordLineEdit->clear();
            usernameLineEdit->setFocus();
        }
        else if(state == NOUSER)
        {
            QMessageBox::warning(this, tr("警告"), tr("用户不存在!"), QMessageBox::Ok);
            usernameLineEdit->clear();
            passwordLineEdit->clear();
            usernameLineEdit->setFocus();
        }
    }
    else if(func == GET_GAMERINFO)
    {
        QString nickname = receivedInfo.take("nickname").toString();
        QString username = receivedInfo.take("username").toString();
        int level = receivedInfo.take("level").toInt();
        int exp = receivedInfo.take("exp").toInt();
        int passedStage = receivedInfo.take("passedStage").toInt();

        Gamer gamer(nickname, username, level, exp, passedStage);
        qDebug() << nickname << "开启游戏";
        accept();
        wordgame = new WordGame(gamer);
        wordgame->setAttribute(Qt::WA_DeleteOnClose);
        wordgame->show();
    }
    else if(func == GET_EXAMERINFO)
    {
        QString nickname = receivedInfo.take("nickname").toString();
        QString username = receivedInfo.take("username").toString();
        int level = receivedInfo.take("level").toInt();
        int exp = receivedInfo.take("exp").toInt();
        int questionNum = receivedInfo.take("questionNum").toInt();

        Examer examer(nickname, username, level, exp, questionNum);
        accept();
        wordgame = new WordGame(examer);
        wordgame->setAttribute(Qt::WA_DeleteOnClose);
        wordgame->show();
    }
}
