#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T13:55:09
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocialCrm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    groupform.cpp \
    json.cpp

HEADERS  += mainwindow.h \
    groupform.h \
    json.h

FORMS    += mainwindow.ui \
    groupform.ui

