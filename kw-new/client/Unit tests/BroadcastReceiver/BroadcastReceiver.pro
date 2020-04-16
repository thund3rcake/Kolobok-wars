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

INCLUDEPATH += $$PWD/../../../common
DEPENDPATH += $$PWD/../../../common


INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../


TEMPLATE = app

SOURCES +=  $$PWD/../../broadcastReceiver.cpp \
    $$PWD/../../../common/serializable.cpp \
    $$PWD/../../../common/datagramms.cpp \
    $$PWD/../../../common/weapon.cpp \
    testreceiver.cpp \
    tst_testreceiving.cpp

HEADERS += \
    $$PWD/../../BroadcastReceiver.h \
    $$PWD/../../../common/Serializable.h \
    $$PWD/../../../common/Datagramms.h \
    $$PWD/../../../common/Weapon.h \
    testreceiver.h
