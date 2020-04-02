

# Defines
DEFINES += KOLOBOK_CLIENT \
    NET_VERSION=1 \
    NET_SUBVERSION=0 # \


QT +=  network \
                core

HEADERS += \
    TcpClient.h \
    NetDataContainer.h \
    BroadcastReceiver.h

SOURCES += \
    tcpClient.cpp \
    broadcastReceiver.cpp

unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
