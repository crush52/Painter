#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T12:17:07
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QMAKE_CXXFLAGS += -std=c++0x

TARGET = painter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    imagearea.cpp \
    rectangleinstr.cpp \
    commoninstr.cpp \
    ellipseinstr.cpp \
    zoominstr.cpp \
    fillinstr.cpp \
    lineinstr.cpp \
    pencilinstr.cpp \
    brushinstr.cpp \
    cutinstr.cpp \
    textinstr.cpp \
    textdialog.cpp \
    pipetteinstr.cpp \
    polygonalchaininstr.cpp

HEADERS  += mainwindow.h \
    imagearea.h \
    rectangleinstr.h \
    commoninstr.h \
    enuminstruments.h \
    ellipseinstr.h \
    zoominstr.h \
    fillinstr.h \
    lineinstr.h \
    pencilinstr.h \
    brushinstr.h \
    cutinstr.h \
    textinstr.h \
    textdialog.h \
    pipetteinstr.h \
    polygonalchaininstr.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
