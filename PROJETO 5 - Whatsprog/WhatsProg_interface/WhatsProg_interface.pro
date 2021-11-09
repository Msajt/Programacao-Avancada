#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T18:42:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsProg
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


SOURCES +=\
    dados_cliente.cpp \
    dados_whatsprog.cpp \
    logindialog.cpp \
    mysocket.cpp \
    whatsprogmain.cpp \
    main_cliente.cpp \
    novaconversa.cpp

HEADERS  += \
    dados_cliente.h \
    dados_whatsprog.h \
    logindialog.h \
    mysocket.h \
    whatsprogmain.h \
    novaconversa.h

FORMS    += \
    logindialog.ui \
    whatsprogmain.ui \
    novaconversa.ui

LIBS   += \
    -lWs2_32

DISTFILES += \
    status0.png \
    status1.png \
    status2.png \
    status3.png \
    status_other.png \
    whatsprog_icon.png

RESOURCES += \
    resources.qrc
