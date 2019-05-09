#include "signin.h"
#include "signup.h"
#include "Database/database.h"

SignIn::SignIn(QWidget *parent)
    : QDialog(parent)
{
    initUI();

    connect(signinButton, SIGNAL(clicked()), this, SLOT(on_signinButton_clicked()));
    connect(signupButton, SIGNAL(clicked()), this, SLOT(on_signupButton_clicked()));
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
    Database db;
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text().trimmed();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("账号密码不能为空!"), QMessageBox::Ok);
    }
    else
    {
        bool success = false;
        if(selectButton->checkedId() == 0)
        {
            success = db.gamerSignin(username, password);
        }
        else if(selectButton->checkedId() == 1)
        {
            success = db.examerSignin(username, password);
        }

        if(success && selectButton->checkedId() == 0)
        {
            QMessageBox::information(this, tr("提示信息"), tr("登录成功!"), QMessageBox::Ok);
            accept();
            Gamer gamer = db.getGamerInfo(username);

            wordgame = new WordGame(gamer);
            wordgame->setAttribute(Qt::WA_DeleteOnClose);
            wordgame->show();
        }
        else if(success && selectButton->checkedId() == 1)
        {
            QMessageBox::information(this, tr("提示信息"), tr("登录成功!"), QMessageBox::Ok);
            accept();
            Examer examer = db.getExamerInfo(username);
            wordgame = new WordGame(examer);
            wordgame->setAttribute(Qt::WA_DeleteOnClose);
            wordgame->show();
        }
        else
        {
            QMessageBox::warning(this, tr("警告!"), tr("用户名、密码或用户类型错误！"), QMessageBox::Ok);
            usernameLineEdit->clear();
            passwordLineEdit->clear();
            usernameLineEdit->setFocus();
        }
    }
}

void SignIn::on_signupButton_clicked()
{
    SignUp signup;
    signup.exec();
}
