#ifndef MATCHDIALOG_H
#define MATCHDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>

class MatchDialog: public QDialog
{
    Q_OBJECT

public:
    explicit MatchDialog(QWidget *parent = nullptr);
    ~MatchDialog();
private slots:
    void on_cancelButton_clicked();
    void waiting();
private:
    QLabel *waitingLabel;
    QPushButton *cancelButton;
    QGridLayout *mainLayout;
    QTimer *waitingTimer;
};

#endif // MATCHDIALOG_H
