unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

QT += network \
    widgets \
    core \
    gui

DEFINES += KOLOBOK_SERVER \
    NET_VERSION=1 \
    NET_SUBVERSION=0 \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerAlpha
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

SOURCES += \
        broadcastsender.cpp \
        main.cpp \
        playerthread.cpp \
        servertools.cpp \
        serverui.cpp \
        sharedobject.cpp \
        tcpserver.cpp \
        udpserver.cpp

HEADERS += \
        broadcastsender.h \
        playerthread.h \
        servertools.h \
        serverui.h \
        sharedobject.h \
        sharedtypes.h \
        tcpserver.h \
        udpserver.h

FORMS += \
        serverui.ui

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
