#include <QApplication>

#include "Database/database.h"
#include "SignUpAndSignIn/signin.h"

int main(int argc, char *argv[])
{
    QApplication wordgame(argc, argv);
    Database db;
    db.init();
    SignIn signin;
    if(signin.exec() == QDialog::Accepted)
    {
        return wordgame.exec();
    }
    else
        return 0;
}
