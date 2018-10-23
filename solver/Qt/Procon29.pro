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
    gamefield.cpp \
    ../src/structure/Field.cpp \
    ../src/structure/Cell.cpp \
#    ../QR/QR.cpp


HEADERS += \
        mainwindow.h \
    gamefield.h \
    ../include/structure/Cell.hpp \
    ../include/structure/Field.hpp \
    ../include/structure/Position.hpp \
    ../QR/QR.hpp \
#    ../../../OpenSiv3D(0.3.0)/include/Siv3D.hpp


FORMS += \
        mainwindow.ui \
    gamefield.ui \

QMAKE_CXXFLAGS += /std:c++latest


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../OpenSiv3D(0.3.0)/lib/Windows(x64)/' -lSiv3D_d
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../OpenSiv3D(0.3.0)/lib/Windows(x64)/' -lSiv3D_d

#INCLUDEPATH += $$PWD/'../../../OpenSiv3D(0.3.0)/include'
#DEPENDPATH += $$PWD/'../../../OpenSiv3D(0.3.0)/include'
#INCLUDEPATH += $$PWD/'../../../OpenSiv3D(0.3.0)/include/ThirdParty'
#DEPENDPATH += $$PWD/'../../../OpenSiv3D(0.3.0)/include/ThirdParty'

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/'../../../OpenSiv3D(0.3.0)/lib/Windows(x64)/libSiv3D_.a'
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/'../../../OpenSiv3D(0.3.0)/lib/Windows(x64)/libSiv3D_d.a'
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/'../../../OpenSiv3D(0.3.0)/lib/Windows(x64)/Siv3D_d.lib'
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/'../../../OpenSiv3D(0.3.0)/lib/Windows(x64)/Siv3D_d.lib'
