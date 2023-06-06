QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    level.cpp \
    animatedsprite.cpp \
    gameobject.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mapsection.cpp \
    player.cpp \
    tile.cpp \
    tileset.cpp

HEADERS += \
    level.h \
    animatedsprite.h \
    collisionside.h \
    constants.h \
    gameobject.h \
    mainwindow.h \
    map.h \
    mapsection.h \
    player.h \
    tile.h \
    tileset.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    level.qrc \
    sprites.qrc
