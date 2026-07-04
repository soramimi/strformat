include(common.pri)
TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $$PWD/../_bin

# CONFIG += ubsan
ubsan {
    gcc:QMAKE_CXXFLAGS += -fsanitize=undefined
    gcc:LIBS += -lubsan
}

INCLUDEPATH += $$PWD/../include

#DEFINES += STRFORMAT_NO_FP

SOURCES += \
    ../main.cpp \
    ../test.cpp

HEADERS += \
    ../include/strformat.h \
    pragma.h
