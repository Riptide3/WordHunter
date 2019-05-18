#include <QApplication>

#include "SignUpAndSignIn/signin.h"

int main(int argc, char *argv[])
{

    QApplication wordgame(argc, argv);
    QFont wordgameFont("KaiTi", 13);
    wordgame.setFont(wordgameFont);
    SignIn signin;

    if(signin.exec() == QDialog::Accepted)
    {
        return wordgame.exec();
    }
    else
        return 0;
}
