#ifndef WAITINGDIALOG_H
#define WAITINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QGridLayout>

class WaitingDialog: public QDialog
{    
    Q_OBJECT

public:
    explicit WaitingDialog(QWidget *parent = nullptr);
    ~WaitingDialog();
    void selfClose();
private slots:
    void waiting();
private:
    QLabel *waitingLabel;
    QTimer *waitingTimer;
    QGridLayout *mainLayout;
};

#endif // WAITINGDIALOG_H
