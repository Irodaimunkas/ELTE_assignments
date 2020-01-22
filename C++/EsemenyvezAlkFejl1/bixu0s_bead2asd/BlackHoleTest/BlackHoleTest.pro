#-------------------------------------------------
#
# Project created by QtCreator 2019-11-03T02:12:34
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = blackholetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += blackholetest.cpp \
    blackholemodel.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    blackholemodel.h \
    dataaccess.h \
    dataaccessmock.h
