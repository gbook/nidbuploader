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
        anonymize.cpp

HEADERS  += mainwindow.h \
         anonymize.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/gdcm/Source/Attribute
INCLUDEPATH += $$PWD/gdcm/Source/Common
INCLUDEPATH += $$PWD/gdcm/Source/DataDictionary
INCLUDEPATH += $$PWD/gdcm/Source/DataStructureAndEncodingDefinition
INCLUDEPATH += $$PWD/gdcm/Source/InformationObjectDefinition
INCLUDEPATH += $$PWD/gdcm/Source/MediaStorageAndFileFormat
INCLUDEPATH += $$PWD/gdcm/Source/MessageExchangeDefinition
INCLUDEPATH += $$PWD/gdcm-win7/Source/Common # for gdcmConfigure.h

linux-g++: {
    LIBS += -L$$PWD/gdcm-centos7/bin
}
else {
    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/gdcm-win7/bin/Release/
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/gdcm-win7/bin/Debug/
}

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
    -lgdcmopenjpeg \
    -lgdcmzlib \
    -lsocketxx

