#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T14:41:33
#
#-------------------------------------------------

QT       -= core gui

TARGET = CS_suite_static
TEMPLATE = lib
CONFIG += staticlib
DEFINES  += CS_VERSION=5 CROPSYST_VERSION=5 VERBOSE REACCH_VERSION MICROBASIN_VERSION VIC_CROPSYST_VERSION=3

INCLUDEPATH += ../CS_suite_static . ../../../../common ../../../.. ../../../../CropSyst/source

QMAKE_CXXFLAGS  += -fpermissive -w -g

SOURCES += \
      ../../../simulation/CS_event_scheduler.cpp \
      ../../../simulation/CS_identification.cpp \
      ../../../simulation/CS_land_unit_meteorological.cpp \
      ../../../simulation/CS_simulation_control.cpp \
      ../../../simulation/CS_simulation_element.cpp \
      ../../../simulation/CS_simulation_engine.cpp \
      ../../../simulation/CS_simulation_unit.cpp \
      ../../../simulation/CS_simulation_rotator.cpp \
      ../../../simulation/CS_simulation_element_plugin.cpp \
      ../../../file_system/CS_database_directory.cpp \
      ../../../file_system/CS_databases.cpp \
      ../../../application/CS_arguments.cpp \
      ../../../file_system/CS_context_discovery.cpp \
      ../../../file_system/CS_context_discovery_common.cpp \
      ../../../file_system/CS_file_ext.cpp \
      ../../../../common/simulation/event_types.cpp \
      ../../../observation/CS_emanator.cpp \
      ../../../observation/CS_examination.cpp \
      ../../../observation/CS_inspection.cpp \
      ../../../observation/CS_inspector.cpp \
      ../../../observation/CS_UED_recorder.cpp \
      ../../../observation/CS_desired_vars.cpp \
      ../../../observation/CS_recording.cpp \
      ../../../parameters/param_stores.cpp \
      ../../../ontology/CS_ontology.cpp \
      ../../../../common/simulation/event.cpp \
      ../../../UED/database_file_substitution.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    ../../../simulation/CS_simulation_element_plugin.h \
    ../../../simulation/CS_simulation_unit.h \
    ../../../simulation/CS_simulation_engine.h \
    ../../../simulation/CS_simulation_element.h \
    ../../../simulation/CS_simulation_control.h \
    ../../../simulation/CS_reporter.h \
    ../../../simulation/CS_land_unit.h \
    ../../../simulation/CS_land_unit_meteorological.h \
    ../../../simulation/CS_inspector.h \
    ../../../simulation/CS_inspection.h \
    ../../../simulation/CS_identification.h \
    ../../../simulation/CS_event_scheduler.h \
    ../../../simulation/CS_emanator.h \
    ../../../file_system/CS_context_discovery_common.h \
    ../../../file_system/CS_context_discovery.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Windows_MinGW/bin/Release/ -lCS_directory
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Windows_MinGW/bin/Debug/ -lCS_directory
else:unix: LIBS += -L$$PWD/../Windows_MinGW/bin/ -lCS_directory

INCLUDEPATH += $$PWD/../Windows_MinGW/bin/release
DEPENDPATH += $$PWD/../Windows_MinGW/bin/release


