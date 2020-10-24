TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core
SOURCES += main.cpp \
    String.cpp \
    Char.cpp \
    list.cpp

HEADERS += \
    String.h \
    Char.h \
    list.h

DISTFILES += \
    temp.txt
