# Defines
DEFINES += KOLOBOK_CLIENT \
    NET_VERSION=1 \
    NET_SUBVERSION=0 # \

CONFIG += sanitizer sanitize_address
CONFIG += debug


QT +=  network \
                core \
                widgets \
                opengl

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
    Statistics.h \
    ActivatableButton.h \
    GraphicsView.h \
    LanTab.h \
    MainMenuCanvas.h \
    MainMenuStyle.h \
    MainMenuButton.h \
    MainMenu.h \
    BaseWindow.h \
    DerivedWindows.h \
    FavoriteTab.h \
    WindowStyle.h \
    MainMenuStyle.h

SOURCES += \
    tcpClient.cpp \
    broadcastReceiver.cpp \
    udpClient.cpp \
    hud.cpp \
    console.cpp \
    gamePanel.cpp \
    statistics.cpp \
    gameScene.cpp \
    mainMenu.cpp \
    mainMenuButton.cpp \
    BaseWindow.cpp \
    DerivedWindows.cpp \
    FavoriteTab.cpp \
    GraphicsView.cpp \
    LanTab.cpp \
    MainMenuCanvas.cpp \
    kolobok-wars-client.cpp

unix:!macx: LIBS += -L$$PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
