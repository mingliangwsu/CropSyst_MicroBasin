#-------------------------------------------------
#
# Project created by QtCreator 2012-04-05T17:39:05
#
#-------------------------------------------------

QT       -= gui

TARGET = common_sim_static
TEMPLATE = lib
CONFIG += staticlib
DEFINES  += CS_VERSION=5 REACCH_VERSION=2
INCLUDEPATH += ../../../../.. ../../../.. ../../../../../CropSyst/source
QMAKE_CXXFLAGS += -fpermissive  -w -g
QMAKE_CXXFLAGS += -Wno-reorder -Wno-unused-parameter -Wno-unused-but-set-parameter
#QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    ../../../synchronization.cpp \
    ../../../simulation_project_directory.cpp \
    ../../../scenario.cpp \
        ../../../operation.cpp \
    ../../../log.cpp \
    ../../../exit_codes.cpp \
    ../../../event_types.cpp \
    ../../../event_status.cpp \
    ../../../balancer.cpp \
    ../../../scenario_directory.cpp \
    ../../../../physics/property.cpp

HEADERS += common_sim_static.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
