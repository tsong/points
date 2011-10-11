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
    mstalgorithm.cpp \
    convexhullalgorithm.cpp \
    triangulationalgorithm.cpp \
    voronoialgorithm.cpp

HEADERS  += mainwindow.h \
    drawsurfacewidget.h \
    matrix.h \
    vector.h \
    glutils.h \
    pointsalgorithm.h \
    mstalgorithm.h \
    convexhullalgorithm.h \
    triangulationalgorithm.h \
    voronoialgorithm.h

FORMS    +=

OTHER_FILES += \
    README
