#-------------------------------------------------
#
# Project created by QtCreator 2020-04-12T01:24:38
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2d
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    GDrawler/displaywidget.cpp \
    GDrawler/helper.cpp \
    main.cpp \
    window.cpp \
    GParser/GParser.cpp \
    GStreamer/GSerialStream/SerialAPI/serialapi.cpp \
    GStreamer/GSerialStream/Serial.cpp \
    GPacker/PacketCreator.cpp \
    GParser/gcode.cpp

HEADERS += \
    GDrawler/displaywidget.h \
    GDrawler/helper.h \
    window.h \
    GParser/GCode.h \
    GParser/GParser.h \
    GPacker/GPacket.h \
    GPacker/PacketCreator.h \
    GStreamer/GSerialStream/SerialAPI/serialapi.h \
    GStreamer/GSerialStream/Serial.h

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
