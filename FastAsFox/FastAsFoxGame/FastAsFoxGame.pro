QT       += core gui multimedia sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animatedsprite.cpp \
    animationhelper.cpp \
    berriespile.cpp \
    berry.cpp \
    clickablelabel.cpp \
    gameobject.cpp \
    gifitem.cpp \
    heart.cpp \
    hedgehog.cpp \
    imageloader.cpp \
    levelmenubutton.cpp \
    logolabel.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mapsection.cpp \
    menuwidget.cpp \
    player.cpp \
    powerup.cpp \
    spike.cpp \
    tile.cpp \
    tileset.cpp \
    level.cpp

HEADERS += \
    animatedsprite.h \
    animationhelper.h \
    berriespile.h \
    berry.h \
    clickablelabel.h \
    collisionside.h \
    constants.h \
    gameobject.h \
    gifitem.h \
    heart.h \
    hedgehog.h \
    imageloader.h \
    levelmenubutton.h \
    logolabel.h \
    mainwindow.h \
    map.h \
    mapsection.h \
    menuwidget.h \
    player.h \
    powerup.h \
    poweruptype.h \
    spike.h \
    tile.h \
    tileset.h \
    mainwindow.h \
    level.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    level.qrc \
    sprites.qrc
