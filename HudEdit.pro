#-------------------------------------------------
#
# Project created by QtCreator 2014-02-16T22:28:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HudEdit
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    hud\huditem.cpp \
    hud\hudscene.cpp \
    ini\listfile.cpp \
    ini\inifile.cpp \
    ini\iniitem.cpp \
    ini/iniparam.cpp \
    selDial\selectscene.cpp \
    selDial\selectitem.cpp \
    selDial\selectdialog.cpp \
    base/baseitem.cpp \
    base/basescene.cpp \
    base/baseview.cpp

HEADERS  += mainwindow.h \
    hud\huditem.h \
    hud\hudscene.h \
    ini\listfile.h \
    ini\inifile.h \
    ini\iniitem.h \
    ini/iniparam.h \
    selDial\selectscene.h \
    selDial\selectitem.h \
    selDial\selectdialog.h \
    Hud.h \
    base/baseitem.h \
    base/basescene.h \
    base/baseview.h

FORMS    += mainwindow.ui \
    selDial\selectdialog.ui

OTHER_FILES +=

RESOURCES += \
    res/icons.qrc \
    res/actions.qrc
