#-------------------------------------------------
#
# Project created by QtCreator 2011-02-10T21:43:18
#
#-------------------------------------------------

QT       += core gui sql

TARGET = fod-dbbrowser
TEMPLATE = app


SOURCES += main.cpp\
        dbwindow.cpp \
    dbsyncronizewindow.cpp \
    dbmanager.cpp \
    dbconnectiondetails.cpp \
    dbconnectiondescriptor.cpp \
    sqleditor.cpp \
    sqlsyntaxhighlighter.cpp \
    dbmisc.cpp

HEADERS  += dbwindow.h \
    dbsyncronizewindow.h \
    dbmanager.h \
    dbconnectiondetails.h \
    dbconnectiondescriptor.h \
    sqleditor.h \
    sqlsyntaxhighlighter.h \
    dbmisc.h

FORMS    += dbwindow.ui \
    dbsyncronizewindow.ui \
    dbpreferences.ui \
    dbconnectiondetails.ui
