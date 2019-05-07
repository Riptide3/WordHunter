#-------------------------------------------------
#
# Project created by QtCreator 2019-03-19T23:30:22
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WordHunter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    Database/database.cpp \
    DetailinfoWindow/detailinformation.cpp \
    ExamerWindow/wordmaker.cpp \
    GamerWindow/wordhunter.cpp \
    MainWindow/wordgame.cpp \
    RanklistWindow/rankinglist.cpp \
    SignUpAndSignIn/signin.cpp \
    SignUpAndSignIn/signup.cpp \
    User/examer.cpp \
    User/gamer.cpp \
    User/user.cpp

HEADERS  += \
    Database/database.h \
    DetailinfoWindow/detailinformation.h \
    ExamerWindow/wordmaker.h \
    GamerWindow/wordhunter.h \
    MainWindow/wordgame.h \
    RanklistWindow/rankinglist.h \
    SignUpAndSignIn/signin.h \
    SignUpAndSignIn/signup.h \
    User/examer.h \
    User/gamer.h \
    User/user.h

SUBDIRS += WordHunter.pro