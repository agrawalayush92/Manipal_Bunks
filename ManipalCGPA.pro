#-------------------------------------------------
#
# Project created by QtCreator 2013-02-28T06:03:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManipalCGPA
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    GetCG.cpp \
    TheGui.cpp

HEADERS  += widget.h \
    GetCG.h \
    TheGui.h

FORMS    += widget.ui

QT += network
