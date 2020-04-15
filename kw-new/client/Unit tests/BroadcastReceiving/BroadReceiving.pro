QT +=  network \
       core \
       testlib \
       gui \
       widgets \
       xml

DEFINES += KOLOBOK_CLIENT \
    NET_VERSION=1 \
    NET_SUBVERSION=0 \
    COMMON_LIBRARY

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

#INCLUDEPATH += $$PWD/../../../common
#DEPENDPATH += $$PWD/../../../common

HEADERS += \
    BroadcastReceiver.h \
    CommonGlobal.h \
    Datagramms.h \
    GameWorldConsts.h \
    MetaRegistrator.h \
    Serializable.h \
    Utils.h \
    Versions.h \
    Weapon.h \

SOURCES +=  broadcastReceiver.cpp \
    datagramms.cpp \
    serializable.cpp \
    weapon.cpp \
    tst_testreceiving.cpp
