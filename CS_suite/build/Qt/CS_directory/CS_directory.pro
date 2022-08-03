#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T19:54:23
#
#-------------------------------------------------

QT       -= gui

TARGET = CS_directory
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ../../../../../dev
DEFINES += CS_VERSION=4


SOURCES += \
    ../../../CS_application_directory.cpp \
    ../../../CS_suite_directory.cpp \
    ../../../CANMS/CANMS_directory.cpp \
    ../../../ClimGen/ClimGen_directory.cpp \
    ../../../CropSyst/CropSyst_directory.cpp \
    ../../../UED/UED_directory.cpp \
    ../../../file_system/CS_database_directory.cpp

HEADERS += \
    ../../../CS_suite_directory.h \
    ../../../CS_application_directory.h \
    ../../../../corn/application/adjunct_directory_OS_FS.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
