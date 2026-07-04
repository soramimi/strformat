TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $$PWD/../_bin

gcc:QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic -Werror -fsanitize=undefined
gcc:LIBS += -lubsan

INCLUDEPATH += $$PWD/../include

#DEFINES += STRFORMAT_NO_FP

SOURCES += \
    ../main.cpp \
    ../test.cpp

HEADERS += \
    ../include/strformat.h
