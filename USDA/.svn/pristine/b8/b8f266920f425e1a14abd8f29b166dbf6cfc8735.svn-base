#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T17:18:27
#
#-------------------------------------------------

QT       -= gui

TARGET = STATSGO2_SSURGO_static
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ../../../../../../../../../dev ../../../../../../../../../dev/USDA/NRCS
DEFINES +=
SOURCES += \
    ../../../STATSGO_SSURGO_database.cpp \
    ../../../STATSGO_SSURGO_types.cpp \
    ../../../../domains.cpp \
    ../../../tabular/mapunit_struct.cpp \
    ../../../tabular/mapunit.cpp \
    ../../../tabular/component_struct.cpp \
    ../../../tabular/component.cpp \
    ../../../tabular/chtexturegrp_struct.cpp \
    ../../../tabular/chtexturegrp.cpp \
    ../../../tabular/chorizon_struct.cpp \
    ../../../tabular/chorizon.cpp \
    ../../../tabular/index/indexer.cpp

HEADERS += STATSGO2_SSURGO_static.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
