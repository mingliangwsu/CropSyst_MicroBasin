#-------------------------------------------------
#
# Project created by QtCreator 2012-04-03T14:27:43
#
#-------------------------------------------------

QT       -= gui

TARGET = UED_static


TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ../../../../..
DEFINES += CS_VERSION=5


SOURCES += \
    ../../../codes.cpp \
    ../../../varrec.cpp \
    ../../../variable_format.cpp \
    ../../../varcodes.cpp \
    ../../../unitsrec.cpp \
    ../../../units_def.cpp \
    ../../../UED_tuple_datasrc.cpp \
    ../../../UED_fname.cpp \
    ../../../std_variables.cpp \
    ../../../timeqry.cpp \
    ../../../std_codes.cpp \
    ../../../record.cpp \
    ../../../rec_io.cpp \
    ../../../index.cpp \
    ../../../datasetrec_creation.cpp \
    ../../../datasetrec.cpp \
    ../../../database_file.cpp \
    ../../../locrec.cpp

HEADERS += ued_static.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
