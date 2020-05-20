# Template
TEMPLATE = lib

# Libs
QT += widgets \
            xml \
            network \
            core \

# Defines
DEFINES += KOLOBOK_CLIENT \
    NET_VERSION=1 \
    NET_SUBVERSION=0 \
    COMMON_LIBRARY

CONFIG += sanitizer sanitize_address \
	debug

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
    Utils.h \
    Weapon.h \
    Versions.h \
    XmlParser.h \
    MetaRegistrator.h

SOURCES += \
    bullet.cpp \
    datagramms.cpp \
    entity.cpp \
    geometryAlgorithms.cpp \
    map.cpp \
    player.cpp \
    serializable.cpp \
    utils.cpp \
    weapon.cpp \
    xmlParser.cpp \
    main.cpp
