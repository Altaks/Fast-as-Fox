QT += testlib
QT += gui
QT += gui widgets core
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_test_tile.cpp \
    ../FastAsFoxGame/animatedsprite.cpp \
    ../FastAsFoxGame/gameobject.cpp \
    ../FastAsFoxGame/level.cpp \
    ../FastAsFoxGame/map.cpp \
    ../FastAsFoxGame/mapsection.cpp \
    ../FastAsFoxGame/player.cpp \
    ../FastAsFoxGame/tile.cpp \
    ../FastAsFoxGame/tileset.cpp

HEADERS += \
    ../FastAsFoxGame/animatedsprite.h \
    ../FastAsFoxGame/collisionside.h \
    ../FastAsFoxGame/constants.h \
    ../FastAsFoxGame/gameobject.h \
    ../FastAsFoxGame/level.h \
    ../FastAsFoxGame/map.h \
    ../FastAsFoxGame/mapsection.h \
    ../FastAsFoxGame/player.h \
    ../FastAsFoxGame/tile.h \
    ../FastAsFoxGame/tileset.h
