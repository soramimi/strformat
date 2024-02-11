TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $$PWD/_bin

#DEFINES += STRFORMAT_NO_FP

SOURCES += \
	main.cpp \
    test.cpp

HEADERS += \
    strformat.h
