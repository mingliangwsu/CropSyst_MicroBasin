#-------------------------------------------------
#
# Project created by QtCreator 2015-01-02T16:12:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = convert_crop_V4_to_V5
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH +=  ../../.. ../../../.. ../../../../.. ../../../../../..  ../../../../../../.. ../../../../../../../CropSyst/source ../../../../../../../common
QMAKE_CXXFLAGS += -fpermissive
DEFINES += condcompH CS_VERSION=4 CROPSYST_VERSION=4 YAML_PARAM_VERSION

TEMPLATE = app


SOURCES += \
    ../../../../../../../CropSyst/source/crop/crop_param_YAML.cpp \
    ../../../../../../../CropSyst/source/crop/crop_param_struct.cpp \
    ../../../../../../../CropSyst/source/crop/crop_param_class.cpp \
    ../../../../../../../CropSyst/source/static_phrases.cpp \
    ../../../../../../../common/residue/residue_decomposition_param.cpp \
    ../../../../../../../common/simulation/synchronization.cpp \
    ../../../../../../../common/simulation/event.cpp \
    ../../../../../../../CropSyst/source/crop/crop_types.cpp \
    ../../../../../../../common/soil/SCS/SCS.cpp \
    ../../../../../../parameters/CS_YAML_document.cpp \
    ../../../../../../../corn/format/YAML/YAML_document.cpp \
    ../../../../../../../common/simulation/event_status.cpp \
    ../../../../../../../CropSyst/source/crop/growth_stages.cpp \
    ../../../../../../../common/residue/residue_const.cpp \
    ../../../../../../../CropSyst/source/mgmt_types.cpp \
    ../../../../../../../common/simulation/event_types.cpp \
    ../../../../../../../common/soil/layering.cpp \
    ../../../../../../../corn/parameters/number_keyed.cpp \
    ../../../../../../../corn/format/YAML/YAML_stream.cpp \
    ../../../convert_crop_V4_to_V5_main.cpp \
    ../../../../../../../CropSyst/source/crop/crop_param_V4.cpp \
    ../../../../../../../corn/parameters/parameter_interpolation.cpp \
    ../../../../../../../corn/format/structural.cpp


HEADERS += \
    ../../../options.h \
    ../../../../../../../CropSyst/source/crop/crop_param_V4.h \
    ../../../../../../../CropSyst/source/crop/crop_param_YAML.h \
    ../../../../../../../CropSyst/source/crop/crop_param_V5.h \
    ../../../../../../../corn/parameters/parameter_interpolation.h \
    ../../../../../../../corn/format/structural.h

unix:!macx: LIBS += -L$$PWD/../../../../../../../corn/build/Qt/Release/ -lcorn_complete_static

INCLUDEPATH += $$PWD/../../../../../../../corn/build/Qt/Release
DEPENDPATH += $$PWD/../../../../../../../corn/build/Qt/Release

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../../corn/build/Qt/Release/libcorn_complete_static.a
