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

unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

INCLUDEPATH += $$PWD/../common
INCLUDEPATH += $$PWD/../Server
DEPENDPATH += $$PWD/../Server
DEPENDPATH += $$PWD/../common

HEADERS += \
    aibot.h \
    botthread.h \
    utilityalgorithms.h

SOURCES += \
    aibot.cpp \
    botthread.cpp \
    utilityalgorithms.cpp
