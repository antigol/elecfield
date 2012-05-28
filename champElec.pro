#-------------------------------------------------
#
# Project created by QtCreator 2012-05-15T07:19:40
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = champElec
TEMPLATE = app


SOURCES += main.cpp\
        glwidget.cpp \
    cube.cpp \
    sphere.cpp \
    glshape.cpp

HEADERS  += glwidget.h \
    cube.h \
    sphere.h \
    glshape.h

OTHER_FILES += \
    gl.vert \
    gl.frag

RESOURCES += \
    data.qrc
