#-------------------------------------------------
#
# Project created by QtCreator 2011-09-26T22:45:42
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = points
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawsurfacewidget.cpp \
    matrix.cpp

HEADERS  += mainwindow.h \
    drawsurfacewidget.h \
    matrix.h \
    vector.h \
    glutils.h

FORMS    +=

OTHER_FILES += \
    README
