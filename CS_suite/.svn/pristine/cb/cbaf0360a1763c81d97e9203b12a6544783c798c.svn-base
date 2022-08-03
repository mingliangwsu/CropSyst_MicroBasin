QT += core
QT -= gui

TARGET = generator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += VERBOSE_DEBUG

INCLUDEPATH += ../../../../.. ../../../../../common

SOURCES +=  \
    ../../scenarios_generator_main.cpp \
    ../../scenarios_generator_engine.cpp \
    ../../REACCH_generate.cpp  \
    ../../../../../common/geodesy/geocoordinate.cpp \
    ../../../../../common/geodesy/geocoordinates.cpp \
    ../../../../../common/geodesy/geolocation.cpp \
    ../../../../../common/geodesy/geolocation_item.cpp \
    ../../../../../common/geodesy/geometry/terrestrial_geometry.cpp \
    ../../../../file_system/CS_databases.cpp \
    ../../../../file_system/CS_file_discovery.cpp \
    ../../../../file_system/CS_database_directory.cpp \
    ../../../../file_system/CS_context_discovery.cpp \
    ../../../../file_system/CS_context_discovery_common.cpp



unix:!macx: LIBS += -L$$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/ -lcorn_complete_static

INCLUDEPATH += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/
DEPENDPATH += $$PWD/../../../../../corn/build/QQt/corn_complete_static/bin/Release/

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/libcorn_complete_static.a

HEADERS += \
    ../../../../../CropSyst/REACCH/procedures/generator_REACCH.h \
    REACCH_generator.h
