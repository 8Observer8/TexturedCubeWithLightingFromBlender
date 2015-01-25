#-------------------------------------------------
#
# Project created by QtCreator 2015-01-19T18:12:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TexturedCubeWithLightingFromBlender
TEMPLATE = app

INCLUDEPATH += "C:/Assimp-3.1.1/include"
LIBS += "C:/Assimp-3.1.1/libs/libassimp.dll"

SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp \
    MeshLoader.cpp \
    Cube.cpp

HEADERS  += Dialog.h \
    Scene.h \
    MeshLoader.h \
    Cube.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc \
    Textures.qrc
