#include "searchuser.h"
#include "Database/database.h"

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

    connect(searchGamerButton, SIGNAL(clicked()), this, SLOT(on_searchGamerButton_clicked()));
    connect(searchExamerButton, SIGNAL(clicked()), this, SLOT(on_searchExamerButton_clicked()));
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
        Database db;
        Gamer gamer = db.findGamer(username);
        if(gamer.getUsername().isEmpty())
        {
            QMessageBox::information(this, tr("提示信息"), tr("抱歉，您查找的用户不存在"), QMessageBox::Ok);
        }
        else
        {
            UserInformation(gamer).exec();
        }
    }
    usernameLineEdit->clear();
    usernameLineEdit->setFocus();
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
        Database db;
        Examer examer = db.findExamer(username);
        if(examer.getUsername().isEmpty())
        {
            QMessageBox::information(this, tr("提示信息"), tr("抱歉，您查找的用户不存在"), QMessageBox::Ok);
        }
        else
        {
            UserInformation(examer).exec();
        }
    }
    usernameLineEdit->clear();
    usernameLineEdit->setFocus();
}
