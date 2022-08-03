QT += core
QT -= gui

TARGET = UED_collate
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


win32:CONFIG(release, debug|release): DEFINES += _Windows
else:win32:CONFIG(debug, debug|release): DEFINES += _Windows

win32:CONFIG(release, debug|release): QMAKE_CXXFLAGS += -w -fpermissive
else:win32:CONFIG(debug, debug|release): QMAKE_CXXFLAGS += -w -fpermissive
else:symbian: QMAKE_CXXFLAGS += -w -fpermissive
else:unix: QMAKE_CXXFLAGS += -Wno-reorder -Wno-unused-parameter -Wno-unused-but-set-parameter -fpermissive  -w -g




INCLUDEPATH += ../../../../.. \
   ../../../../../common


SOURCES += \
    ../../../collate_main.cpp \
    ../../../collate_engine.cpp \
    ../../../../../corn/float16.cpp \
    ../../../../../common/geodesy/geocoordinate.cpp \
    ../../../../../common/geodesy/geolocation.cpp \
    ../../../../convert/text_dBase_Excel_with_TDF/text_dbase_excel_with_tdf_convertor.cpp \
    ../../../../convert/text_dBase_Excel_with_TDF/tabular_file_with_TDF_convertor.cpp \
    ../../../../convert/convert_response.cpp \
    ../../../../convert/ED_tabular_format.cpp \
    ../../../../convert/convertor.cpp \
    ../../../../../corn/format/binary/binary_record_file.cpp \
    ../../../../convert/text_dBase_Excel_with_TDF/tuple_index.cpp \
    ../../../../convert/text_dBase_Excel_with_TDF/import_column.cpp \
    ../../../../convert/text_dBase_Excel_with_TDF/export_column.cpp \
    ../../../../../corn/container/binary_tree.cpp


unix:!macx|win32: LIBS += -L$$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/ -lcorn_complete_static
INCLUDEPATH += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release
DEPENDPATH += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/corn_complete_static.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../corn/build/Qt/corn_complete_static/bin/Release/libcorn_complete_static.a

unix:!macx|win32: LIBS += -L$$PWD/../../../../library/build/Qt/UED_static/bin/Release/ -lUED_static
INCLUDEPATH += $$PWD/../../../../library/build/Qt/UED_static/bin/Release
DEPENDPATH += $$PWD/../../../../library/build/Qt/UED_static/bin/Release
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../library/build/Qt/UED_static/bin/Release/UED_static.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../library/build/Qt/UED_static/bin/Release/libUED_static.a

HEADERS +=
