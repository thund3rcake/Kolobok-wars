# Libs
QT += network


unix:!macx: LIBS += -L$$PWD/../build-common-Desktop-Debug/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
