
unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

# Libs
QT += network

DEFINES += KOLOBOK_SERVER \
    NET_VERSION=1 \
    NET_SUBVERSION=0 \

HEADERS += \
    BroadcastSender.h \
    Versions.h \
    udpserver.h

SOURCES += \
    broadcastSender.cpp \
    udpserver.cpp

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
