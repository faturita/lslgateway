QT += core
QT -= gui

CONFIG += c++11

TARGET = lslgateway
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


QMAKE_MAC_SDK = macosx10.11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9


#INCLUDEPATH += D:\opencv\build\include\
INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /Users/rramele/work/labstreaminglayer/build/install/lsl_Release/LSL/include

LIBS += -L/usr/local/lib -L/Users/rramele/work/labstreaminglayer/build/install/lsl_Release/LSL/lib \
-llsl64

