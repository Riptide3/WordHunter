#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>

#include "User/gamer.h"
#include "User/examer.h"

class UserInformation : public QDialog
{
    Q_OBJECT
public:
    explicit UserInformation(const Gamer &gamer, QWidget *parent = nullptr);
    explicit UserInformation(const Examer &examer, QWidget *parent = nullptr);

private:
    QLabel *nicknameLabel;
    QLabel *usernameLabel;
    QLabel *levelLabel;
    QLabel *expLabel;
    QLabel *passedStageNumLabel;
    QLabel *questionNumLabel;

    QGridLayout *mainLayout;
};

#endif // USERINFORMATION_H
