QT += testlib
QT += widgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_mapsectiontest.cpp \
    ../FastAsFoxGame/animatedsprite.cpp \
    ../FastAsFoxGame/gameobject.cpp \
    ../FastAsFoxGame/mainwindow.cpp \
    ../FastAsFoxGame/mapsection.cpp \
    ../FastAsFoxGame/tile.cpp \
    ../FastAsFoxGame/tileset.cpp

HEADERS += \
    ../FastAsFoxGame/animatedsprite.h \
    ../FastAsFoxGame/constants.h \
    ../FastAsFoxGame/gameobject.h \
    ../FastAsFoxGame/mainwindow.h \
    ../FastAsFoxGame/mapsection.h \
    ../FastAsFoxGame/tile.h \
    ../FastAsFoxGame/tileset.h

RESOURCES += \
    ../FastAsFoxGame/level.qrc
