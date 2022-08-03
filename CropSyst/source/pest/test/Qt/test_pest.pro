#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T22:29:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = test_pest
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH +=  ../../.. ../../../.. ../../../../.. ../../../../../..  ../../../../../../.. ../../../../../../../CropSyst/source ../../../../../../../common
QMAKE_CXXFLAGS += -fpermissive
DEFINES += VERBOSE MATCH_EXCEL_VERSION

TEMPLATE = app

SOURCES += \
    ../../../../../CS_suite/simulation/CS_simulation_engine.cpp \
    ../../../../../CS_suite/simulation/CS_simulation_element.cpp \
    ../test_main.cpp \
    ../../insect.cpp \
    ../../../../../CS_suite/simulation/CS_event_scheduler.cpp \
    ../../../../../CS_suite/simulation/CS_simulation_control.cpp \
    ../../../../../common/weather/any_timestep/min_max_to_timestep_estimator.cpp \
    ../../../../../common/weather/any_timestep/temperature_est.cpp \
    ../../../crop/growth_stages.cpp

unix:!macx: LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/ -lcommon_sim_static

INCLUDEPATH += $$PWD/../../../../../common/simulation/build/Qt/Debug
DEPENDPATH += $$PWD/../../../../../common/simulation/build/Qt/Debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../common/simulation/build/Qt/Debug/libcommon_sim_static.a

unix:!macx: LIBS += -L$$PWD/../../../../../corn/build/Qt/Release/ -lcorn_complete_static

INCLUDEPATH += $$PWD/../../../../../corn/build/Qt/Release
DEPENDPATH += $$PWD/../../../../../corn/build/Qt/Release

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../corn/build/Qt/Release/libcorn_complete_static.a
