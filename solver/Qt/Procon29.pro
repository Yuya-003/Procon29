#-------------------------------------------------
#
# Project created by QtCreator 2018-06-28T18:47:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Procon29
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    ../include/ \

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    settingdialog.cpp \
    gamefield.cpp \
    qtcell.cpp \
    ../src/structure/Field.cpp \


HEADERS += \
        mainwindow.h \
    settingdialog.h \
    gamefield.h \
    qtcell.h \
    ../include/structure/Field.hpp \


FORMS += \
        mainwindow.ui \
    settingdialog.ui \
    settingdialog.ui \
    cell.ui \
    gamefield.ui \
