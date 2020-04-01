
unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

DEFINES += KOLOBOK_SERVER \
    NET_VERSION=1 \
    NET_SUBVERSION=0 \

HEADERS += \
    BroadcastSender.h

SOURCES += \
    broadcastSender.cpp

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
