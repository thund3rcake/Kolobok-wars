
unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

# Libs
QT += network \
    widgets

DEFINES += KOLOBOK_SERVER \
    NET_VERSION=1 \
    NET_SUBVERSION=0 \

HEADERS += \
    BroadcastSender.h \
    thread.h \
    Versions.h \
    playerthread.h \
    servertools.h \
    sharedobject.h \
    sharedtypes.h \
    tcpserver.h \
    udpserver.h

SOURCES += \
    broadcastSender.cpp \
    playerthread.cpp \
    servertools.cpp \
    sharedobject.cpp \
    tcpserver.cpp \
    udpserver.cpp

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
