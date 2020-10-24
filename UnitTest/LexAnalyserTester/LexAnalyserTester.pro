#-------------------------------------------------
#
# Project created by QtCreator 2019-08-27T18:15:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LexAnalyserTester
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    compilationerror.cpp \
    lexicalanalyser.cpp \
    lexicalerror.cpp \
    token.cpp

HEADERS  += mainwindow.h \
    compilationerror.h \
    lexicalanalyser.h \
    lexicalerror.h \
    token.h

FORMS    += mainwindow.ui
