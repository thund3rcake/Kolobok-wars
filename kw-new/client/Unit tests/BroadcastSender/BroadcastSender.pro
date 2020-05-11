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

INCLUDEPATH += $$PWD/../../../Server
DEPENDPATH += $$PWD/../../../Server


TEMPLATE = app

SOURCES +=  main.cpp \
    testsender.cpp \
    $$PWD/../../../Server/broadcastSender.cpp \
    $$PWD/../../../common/serializable.cpp \
    $$PWD/../../../common/datagramms.cpp \
    $$PWD/../../../common/weapon.cpp

HEADERS += \
    testsender.h \
    $$PWD/../../../Server/BroadcastSender.h \
    $$PWD/../../../common/Serializable.h \
    $$PWD/../../../common/Datagramms.h \
    $$PWD/../../../common/Weapon.h
