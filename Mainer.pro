QT  += core gui
QT  += widgets

#CONFIG += c++11
QT += testlib

TARGET = PuzButtonTest
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    puzbuttontest.cpp



win32: LIBS += -L$$PWD/../SomeLib/debug/ -lSomeLib

INCLUDEPATH += $$PWD/../SomeLib
INCLUDEPATH += $$PWD/../SomeLib/debug
DEPENDPATH += $$PWD/../SomeLib/debug

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../SomeLib/debug/SomeLib.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../SomeLib/debug/libSomeLib.a
