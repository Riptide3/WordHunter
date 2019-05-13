#include <QApplication>

#include "SignUpAndSignIn/signin.h"

int main(int argc, char *argv[])
{

    QApplication wordgame(argc, argv);
    SignIn signin;

    if(signin.exec() == QDialog::Accepted)
    {
        return wordgame.exec();
    }
    else
        return 0;
}
