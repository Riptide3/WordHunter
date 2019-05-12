#include "signup.h"

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
{
    initUI();

    client = new Client(this);
    client->initClient();
    client->connectServer();

    connect(signupButton, SIGNAL(clicked()), this, SLOT(on_signupButton_clicked()));
    connect(client->getInfoSender(), SIGNAL(readyRead()), this, SLOT(readInfo()));
}

SignUp::~SignUp()
{

}

void SignUp::initUI()
{
    this->setMinimumSize(300, 230);
    this->setWindowTitle(tr("注册"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    nicknameLabel = new QLabel;
    nicknameLabel->setText(tr("昵称:"));
    nicknameLabel->setAlignment(Qt::AlignRight);
    nicknameLineEdit = new QLineEdit;
    usernameLabel = new QLabel;
    usernameLabel->setText(tr("用户名:"));
    usernameLabel->setAlignment(Qt::AlignRight);
    usernameLineEdit = new QLineEdit;
    passwordLabel = new QLabel;
    passwordLabel->setText(tr("密码:"));
    passwordLabel->setAlignment(Qt::AlignRight);
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    rePasswordLabel = new QLabel;
    rePasswordLabel->setText(tr("确认密码:"));
    rePasswordLabel->setAlignment(Qt::AlignRight);
    rePasswordLineEdit = new QLineEdit;
    rePasswordLineEdit->setEchoMode(QLineEdit::Password);
    signupButton = new QPushButton;
    signupButton->setText(tr("确认注册"));
    gamerButton = new QRadioButton;
    gamerButton->setText(tr("玩家"));
    gamerButton->setChecked(true);
    examerButton = new QRadioButton;
    examerButton->setText(tr("出题人"));
    selectButton = new QButtonGroup;
    selectButton->addButton(gamerButton, 0);
    selectButton->addButton(examerButton, 1);

    QGridLayout *selectUserLayout = new QGridLayout;
    selectUserLayout->addWidget(gamerButton, 0, 0);
    selectUserLayout->addWidget(examerButton, 0, 1);
    QGridLayout *signupLayout = new QGridLayout(this);
    signupLayout->addWidget(nicknameLabel, 0, 0);
    signupLayout->addWidget(nicknameLineEdit, 0, 1);
    signupLayout->addWidget(usernameLabel, 1, 0);
    signupLayout->addWidget(usernameLineEdit, 1, 1);
    signupLayout->addWidget(passwordLabel, 2, 0);
    signupLayout->addWidget(passwordLineEdit, 2, 1);
    signupLayout->addWidget(rePasswordLabel, 3, 0);
    signupLayout->addWidget(rePasswordLineEdit, 3, 1);
    signupLayout->addLayout(selectUserLayout, 4, 0, 1, 2, Qt::AlignCenter);
    signupLayout->addWidget(signupButton, 5, 0, 1, 2, Qt::AlignCenter);
}

void SignUp::on_signupButton_clicked()
{
    QString nickname = nicknameLineEdit->text().trimmed();
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text().trimmed();
    QString repassword = rePasswordLineEdit->text().trimmed();

    if(nickname.isEmpty() || username.isEmpty() || password.isEmpty() || repassword.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("个人资料不能为空"), QMessageBox::Ok);
    }
    else
    {
        if(password == repassword)
        {
            if(selectButton->checkedId() == 0)
            {
                client->sendInfo(GAMER_SIGNUP, nickname, username, password);
            }
            else if(selectButton->checkedId() == 1)
            {
                client->sendInfo(EXAMER_SIGNUP, nickname, username, password);
            }
        }
        else
        {
            passwordLineEdit->clear();
            rePasswordLineEdit->clear();
            passwordLineEdit->setFocus();
            QMessageBox::warning(this, tr("警告"), tr("两次输入密码不一致"), QMessageBox::Ok);
        }
    }
}

void SignUp::readInfo()
{
    qDebug() << "客户端收到服务器发来的信息";
    QJsonObject receivedInfo = client->getInfo();
    FUNCTION func = static_cast<FUNCTION>(receivedInfo.take("function").toInt());
    bool success = receivedInfo.take("success").toBool();
    qDebug() << func << "注册是否成功" << success;
    if((func == GAMER_SIGNUP || func == EXAMER_SIGNUP) && success)
    {
        QMessageBox::information(this, tr("提示信息"), tr("注册成功！"), QMessageBox::Ok);
        nicknameLineEdit->clear();
        usernameLineEdit->clear();
        passwordLineEdit->clear();
        rePasswordLineEdit->clear();
        nicknameLineEdit->setFocus();
    }
    else if((func == GAMER_SIGNUP || func == EXAMER_SIGNUP) && !success)
    {
        QMessageBox::warning(this, tr("警告"), tr("注册失败，用户名已存在！"), QMessageBox::Ok);

        usernameLineEdit->clear();
        usernameLineEdit->setFocus();
    }
}
