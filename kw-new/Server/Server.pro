
unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

HEADERS += \
    BroadcastSender.h

SOURCES += \
    broadcastSender.cpp

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
