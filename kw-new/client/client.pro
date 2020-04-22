

# Defines
DEFINES += KOLOBOK_CLIENT \
    NET_VERSION=1 \
    NET_SUBVERSION=0 # \


QT +=  network \
                core \
                widgets

HEADERS += \
    TcpClient.h \
    NetDataContainer.h \
    BroadcastReceiver.h \
    GameScene.h \
    UdpClient.h \
    HUD.h \
    GamePanel.h \
    HUDStyleSheets.h \
    Console.h \
    Statistics.h

SOURCES += \
    tcpClient.cpp \
    broadcastReceiver.cpp \
    udpClient.cpp \
    hud.cpp \
    console.cpp \
    gamePanel.cpp \
    statistics.cpp \
    gameScene.cpp

unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
