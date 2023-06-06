QT += testlib
QT -= gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_maptest.cpp \
    ../FastAsFoxGame/animatedsprite.cpp \
    ../FastAsFoxGame/gameobject.cpp \
    ../FastAsFoxGame/mainwindow.cpp \
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
    ../FastAsFoxGame/mainwindow.h \
    ../FastAsFoxGame/map.h \
    ../FastAsFoxGame/mapsection.h \
    ../FastAsFoxGame/player.h \
    ../FastAsFoxGame/tile.h \
    ../FastAsFoxGame/tileset.h

DISTFILES += \
    ../FastAsFoxGame/level/level1.json \
    ../FastAsFoxGame/sprites/font/font.ttf \
    ../FastAsFoxGame/sprites/fox/crouch.png \
    ../FastAsFoxGame/sprites/fox/dead.png \
    ../FastAsFoxGame/sprites/fox/hang.png \
    ../FastAsFoxGame/sprites/fox/hurt.png \
    ../FastAsFoxGame/sprites/fox/landing.png \
    ../FastAsFoxGame/sprites/fox/modfox.png \
    ../FastAsFoxGame/sprites/fox/pounce.png \
    ../FastAsFoxGame/sprites/fox/run.png \
    ../FastAsFoxGame/sprites/fox/sniff.png \
    ../FastAsFoxGame/sprites/fox/standing.png \
    ../FastAsFoxGame/sprites/fox/standsit.png \
    ../FastAsFoxGame/sprites/fox/thumb.gif \
    ../FastAsFoxGame/sprites/fox/transitionsit.png \
    ../FastAsFoxGame/sprites/fox/walk.png \
    ../FastAsFoxGame/sprites/fruits/fruits.png \
    ../FastAsFoxGame/sprites/texture/TX Chest Animation.png \
    ../FastAsFoxGame/sprites/texture/TX FX Flame.png \
    ../FastAsFoxGame/sprites/texture/TX FX Torch Flame.png \
    ../FastAsFoxGame/sprites/texture/TX Tileset Ground.png \
    ../FastAsFoxGame/sprites/texture/TX Village Props.png \
    ../FastAsFoxGame/sprites/userInterface/Spritesheet_UI_Flat.png \
    ../FastAsFoxGame/sprites/userInterface/Spritesheet_UI_Flat_Button_01.png \
    ../FastAsFoxGame/sprites/userInterface/Spritesheet_UI_Flat_Button_02.png \
    ../FastAsFoxGame/sprites/userInterface/Spritesheet_UI_Flat_Select_01.png \
    ../FastAsFoxGame/sprites/userInterface/Spritesheet_UI_Flat_Select_02.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Banner_01_Downward.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Banner_01_Upward.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Banner_02_Downward.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Banner_02_Upward.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Lock_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Press_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Large_Release_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Lock_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Press_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Medium_Release_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Lock_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Press_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Button_Small_Release_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Checkmark_Large.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Checkmark_Medium.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Checkmark_Small.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Cross_Large.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Cross_Medium.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Cross_Small.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Dropdown.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Dropdown_Handle.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Fillbar_01_Block.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Fillbar_01_Flat.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Fillbar_01_Hollow.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Fillbar_02_Block.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Fillbar_02_Flat.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Fillbar_02_Hollow.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Filler_01.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Filler_02.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Filler_03.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Filler_04.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Filler_05.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_01_Horizontal.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_01_Inward.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_01_Lite.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_01_Standard.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_01_Vertical.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_02_Horizontal.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_02_Inward.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_02_Lite.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_02_Standard.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Frame_02_Vertical.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_01.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_02.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_03.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_04.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_Handle_01.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_Handle_02.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_Handle_03.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Scrollbar_Handle_04.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_01a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_01a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_01a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_01a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_02a1.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_02a2.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_02a3.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Select_02a4.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slider.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slider_Filler.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slot_01_Available.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slot_01_Selected.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slot_01_Unavailable.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slot_02_Available.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slot_02_Selected.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Slot_02_Unavailable.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Textfield_01.png \
    ../FastAsFoxGame/sprites/userInterface/UI_Flat_Textfield_02.png

RESOURCES += \
    ../FastAsFoxGame/level.qrc \
    ../FastAsFoxGame/sprites.qrc
