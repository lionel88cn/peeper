QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myQT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    findWindowList.cpp \
    WindowList.cpp \
    BuddyList.cpp \
    ConnListener.cpp \
    Bot.cpp

HEADERS  += mainwindow.h \
    findWindowList.h \
    BuddyList.h \
    WindowList.h \
    ConnListener.h \
    Bot.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(C:\Users\user\Desktop\playWindow\gloox-1.0.9\src)

LIBS += -lC:/Users/user/Desktop/playWindow/gloox-1.0/Debug/gloox-1.0
