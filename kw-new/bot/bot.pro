# Libs
QT += widgets \
      xml \
      network \
      core \

# Defines
DEFINES += KOLOBOK_BOT \
    NET_VERSION=1 \
    NET_SUBVERSION=0 \
    COMMON_LIBRARY

unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

INCLUDEPATH += $$PWD/../common
INCLUDEPATH += $$PWD/../Server
DEPENDPATH += $$PWD/../common

HEADERS += \
    aibot.h \
    aiprocessor.h \
    utilityalgorithms.h

SOURCES += \
    aibot.cpp \
    aiprocessor.cpp \
    utilityalgorithms.cpp
