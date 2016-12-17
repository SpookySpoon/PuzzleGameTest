QT  += core gui
QT  += widgets
QT  += testlib

CONFIG += c++11
CONFIG += console
TARGET = Mainer

TEMPLATE = app

SOURCES += \
    gameenginetest.cpp \
    puzzlemanagertest.cpp \
    staticfunctest.cpp
#    congratulatortest.cpp \


win32: LIBS += -L$$PWD/../../../Projects/build-SandBox2-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug/ -lSomeLib

INCLUDEPATH += $$PWD/../../../Projects/build-SandBox2-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug
INCLUDEPATH += $$PWD/../../../Projects/build-SandBox2-Desktop_Qt_5_6_2_MinGW_32bit-Debug
INCLUDEPATH += $$PWD/../../../Projects/SandBox2
DEPENDPATH += $$PWD/../../../Projects/build-SandBox2-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../Projects/build-SandBox2-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug/SomeLib.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../Projects/build-SandBox2-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug/libSomeLib.a

HEADERS +=
