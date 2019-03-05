#-------------------------------------------------
#
# Project created by QtCreator 2014-04-16T12:57:27
#
#-------------------------------------------------

QT += core gui
QT += network
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NiDBUploader
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    remotestatus.cpp

HEADERS  += mainwindow.h \
    remotestatus.h

FORMS    += mainwindow.ui \
    remotestatus.ui

INCLUDEPATH += $$PWD/gdcm/Source/Attribute
INCLUDEPATH += $$PWD/gdcm/Source/Common
INCLUDEPATH += $$PWD/gdcm/Source/DataDictionary
INCLUDEPATH += $$PWD/gdcm/Source/DataStructureAndEncodingDefinition
INCLUDEPATH += $$PWD/gdcm/Source/InformationObjectDefinition
INCLUDEPATH += $$PWD/gdcm/Source/MediaStorageAndFileFormat
INCLUDEPATH += $$PWD/gdcm/Source/MessageExchangeDefinition
INCLUDEPATH += $$PWD/gdcmbin/Source/Common # for gdcmConfigure.h
HEADERS += $$PWD/gdcmbin/Source/Common/gdcmConfigure.h

LIBS += -L$$PWD/gdcmbin/bin/Release/

LIBS += -lgdcmMSFF \
    -lgdcmCommon \
    -lgdcmDICT \
    -lgdcmDSED \
    -lgdcmIOD \
    -lgdcmMEXD \
    -lgdcmcharls \
    -lgdcmexpat \
    -lgdcmjpeg12 \
    -lgdcmjpeg16 \
    -lgdcmjpeg8 \
    -lgdcmopenjp2 \
    -lgdcmzlib \
    -lsocketxx

DISTFILES += \
    squirrel.ico

