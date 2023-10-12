#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T23:44:07
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleTanks
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


SOURCES += \
        main.cpp \
        widget.cpp \
    playertank.cpp \
    shell.cpp \
    brickwall.cpp \
    concretewall.cpp \
    enemytank.cpp \
    tank.cpp \
    button.cpp \
    symbols.cpp \
    emblem.cpp \
    effects.cpp \
    windowcounter.cpp

HEADERS += \
        widget.h \
    playertank.h \
    shell.h \
    brickwall.h \
    concretewall.h \
    enemytank.h \
    tank.h \
    button.h \
    symbols.h \
    emblem.h \
    effects.h \
    windowcounter.h

FORMS += \
        widget.ui

RESOURCES += \
    resources.qrc
