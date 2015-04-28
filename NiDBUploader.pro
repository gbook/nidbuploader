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

#CONFIG += static
#CONFIG += staticlib

SOURCES += main.cpp\
        mainwindow.cpp \
        anonymize.cpp

HEADERS  += mainwindow.h \
         anonymize.h

FORMS    += mainwindow.ui

#win32 {
#DEFINES += BUILDTIME=\\\"$$system('echo %time%')\\\"
#DEFINES += BUILDDATE=\\\"$$system('echo %date%')\\\"
#} else {
#DEFINES += BUILDTIME=\\\"$$system(date '+%H:%M.%s')\\\"
#DEFINES += BUILDDATE=\\\"$$system(date '+%d/%m/%y')\\\"
#}

INCLUDEPATH += $$PWD/gdcm/Source/Attribute
INCLUDEPATH += $$PWD/gdcm/Source/Common
INCLUDEPATH += $$PWD/gdcm/Source/DataDictionary
INCLUDEPATH += $$PWD/gdcm/Source/DataStructureAndEncodingDefinition
INCLUDEPATH += $$PWD/gdcm/Source/InformationObjectDefinition
INCLUDEPATH += $$PWD/gdcm/Source/MediaStorageAndFileFormat
INCLUDEPATH += $$PWD/gdcm/Source/MessageExchangeDefinition
INCLUDEPATH += $$PWD/gdcm-win7/Source/Common # for gdcmConfigure.h

#win32-msvc*:contains(QMAKE_TARGET.arch, x86_64):{
#    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/min-gdcm64-win7/bin/Release/
#    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/min-gdcm64-win7/bin/Debug/
#}
#else {
    win32-msvc2010: {
        LIBS += -LC:\Qt5\5.3\msvc2010_opengl\plugins\platforms

        LIBS += -L$$PWD/min-gdcm32-win7/bin/Debug/
        LIBS += -lopengl32 -limm32 -lwinmm -lWs2_32 -lQt5PlatformSupport
    }
    else {
        linux-g++: {
            LIBS += -L$$PWD/gdcm-centos7/bin
        }
        else {
            win32:CONFIG(release, debug|release): LIBS += -L$$PWD/gdcm-win7/bin/Release/
            else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/gdcm-win7/bin/Debug/
        }
    }
#}

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
#    -lgdcmgetopt \
    -lsocketxx

