# Libs
QT += widgets \
            xml \
            network \
            core \

# Defines
DEFINES += KOLOBOK_CLIENT \
    NET_VERSION=1 \
    NET_SUBVERSION=0 # \

HEADERS += \
    Bullet.h \
    CommonGlobal.h \
    Datagramms.h \
    Entity.h \
    GameWorldConsts.h \
    GeometryAlgorithms.h \
    Map.h \
    Player.h \
    Serializable.h \
    Weapon.h \
    Versions.h \
    XmlParser.h \
    MetaRegistrator.h

SOURCES += \
    bullet.cpp \
    commonGlobal.cpp \
    datagramms.cpp \
    entity.cpp \
    geometryAlgorithms.cpp \
    map.cpp \
    player.cpp \
    serializable.cpp \
    weapon.cpp \
    xmlParser.cpp \
    main.cpp
