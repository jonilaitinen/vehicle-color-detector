#-------------------------------------------------
#
# Project created by QtCreator 2014-03-26T17:05:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorChooser
TEMPLATE = app

# OpenCV
win* {
    LIBS += -LD:/Libraries/OpenCV-2.4.8/build/x86/vc10/lib \
        -lopencv_core248 \
        -lopencv_highgui248 \
        -lopencv_calib3d248 \
        -lopencv_contrib248 \
        -lopencv_imgproc248
}

INCLUDEPATH += D:/Libraries/OpenCV-2.4.8/build/include

SOURCES += main.cpp\
        mainwindow.cpp \
        colordetector.cpp

HEADERS  += mainwindow.h \
         colordetector.h

FORMS    += mainwindow.ui
