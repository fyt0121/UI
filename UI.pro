#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T09:54:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI
TEMPLATE = app


SOURCES += main.cpp\
    MainWinWithVBar.cpp \
    Utils/stylehelper.cpp \
    Utils/styledbar.cpp \
    codeeditor.cpp \
    VerBarWidget.cpp

HEADERS  += \
    MainWinWithVBar.h \
    Utils/stylehelper.h \
    Utils/styledbar.h \
    codeeditor.h \
    VerBarWidget.h

RESOURCES += \
    resource.qrc
