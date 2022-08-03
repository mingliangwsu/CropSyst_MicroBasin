QT += core
QT -= gui

TARGET = scheduler
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../../.. ../../../../../common


SOURCES += \
    ../../scenarios_scheduler_main.cpp \
    ../../scenarios_scheduler_engine.cpp


unix:!macx: LIBS += -L$$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/ -lcorn_complete_static

INCLUDEPATH += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release
DEPENDPATH += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/libcorn_complete_static.a
