# Libs
QT += widgets \
            xml \
            network \
            core \

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
    XmlParser.h

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
