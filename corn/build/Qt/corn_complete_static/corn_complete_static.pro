#-------------------------------------------------
#
# Project created by QtCreator 2012-03-30T01:33:25
#
#-------------------------------------------------

QT       -= gui

TARGET = corn_complete_static
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ../../../.. ../../..
#150428RLN DEFINES += _Windows

win32:CONFIG(release, debug|release): DEFINES += _Windows
else:win32:CONFIG(debug, debug|release): DEFINES += _Windows

win32:CONFIG(release, debug|release): QMAKE_CXXFLAGS += -w -fpermissive
else:win32:CONFIG(debug, debug|release): QMAKE_CXXFLAGS += -w -fpermissive
else:symbian: QMAKE_CXXFLAGS += -w -fpermissive
else:unix: QMAKE_CXXFLAGS += -Wno-reorder -Wno-unused-parameter -Wno-unused-but-set-parameter -fpermissive  -w -g





#QMAKE_CXXFLAGS += -std=c++0x

#QMAKE_CXX		+= ccache g++

# -std=c++0x    <- this flag is to use regex, but not working

SOURCES += \
    ../../../labeled_enum.cpp \
    ../../../data_type_enum.cpp \
    ../../../validate/validtyp.cpp \
    ../../../tabular/delineation.cpp \
    ../../../tabular/tabular_text.cpp \
    ../../../tabular/tabular.cpp \
    ../../../string/uiostring.cpp \
    ../../../string/ustring.cpp \
    ../../../application/explaination/explaination_location.cpp \
    ../../../application/explaination/explainations.cpp \
    ../../../application/user/settings.cpp \
    ../../../application/translations.cpp \
    ../../../container/unilist.cpp \
    ../../../container/text_list.cpp \
    ../../../container/search_tree.cpp \
    ../../../container/SDF_list.cpp \
    ../../../container/item.cpp \
    ../../../container/indexer.cpp \
    ../../../container/enumlist.cpp \
    ../../../container/container.cpp \
    ../../../container/binary_tree.cpp \
    ../../../container/bilist.cpp \
    ../../../container/array.cpp \
    ../../../data_source/vv_entry.cpp \
    ../../../data_source/generic_datarec.cpp \
    ../../../data_source/dbase_datasrc.cpp \
    ../../../data_source/datasrc.cpp \
    ../../../format/binary/binary_record_file.cpp \
    ../../../format/binary/binary_record.cpp \
    ../../../format/binary/binary_file_fstream.cpp \
    ../../../format/binary/binary_file_abstract.cpp \
    ../../../format/html/form_IO/content.cpp \
    ../../../format/MicroSoft/Access/import_export_table.cpp \
    ../../../measure/units_enum.cpp \
    ../../../measure/unitconv.cpp \
    ../../../measure/common_units.cpp \
    ../../../math/statistical/stats.cpp \
    ../../../metrology/timestep.cpp \
    ../../../metrology/units_symbology.cpp \
    ../../../metrology/units_clad.cpp \
    ../../../OS/file_system_logical.cpp \
    ../../../OS/file_system_engine_common.cpp \
    ../../../OS/file_system.cpp \
    ../../../parameters/parameters_datarec.cpp \
    ../../../parameters/parameters.cpp \
    ../../../parameters/parameter.cpp \
    ../../../parameters/parameters_directory_OS_FS.cpp \
    ../../../measure/measures.cpp \
    ../../../measure/units.cpp \
    ../../../format/excel/BIFF_record.cpp \
    ../../../format/spreadsheet/biff.cpp \
    ../../../format/spreadsheet/css_file.cpp \
    ../../../math/moremath.cpp \
    ../../../math/random.cpp \
    ../../../math/numerical/interpolate.cpp \
    ../../../math/statistical/stats_best.cpp \
    ../../../data_source/vv_file.cpp \
    ../../../application/application_directory_OS_FS.cpp \
    ../../../application/project_directory_OS_FS.cpp \
    ../../../data_source/vv_datasrc.cpp \
    ../../../data_source/datarec.cpp \
    ../../../quality.cpp \
    ../../../application/program_directory_OS_FS.cpp \
    ../../../application/adjunct_directory_OS_FS.cpp \
    ../../../application/documentation_directory_OS_FS.cpp \
    ../../../application/suite_directory_OS_FS.cpp \
    ../../../math/statistical/statistics_types.cpp \
    ../../../math/statistical/distribution_normal.cpp \
    ../../../OS/filtered_filename.cpp \
    ../../../tabular/tabular_format.cpp \
    ../../../OS/file_type_description.cpp \
    ../../../string/strconv.cpp \
    ../../../float16.cpp \
    ../../../OS/directory_entry_name.cpp \
    ../../../OS/directory_entry_name_abstract.cpp \
    ../../../application/user/appdata_directory_OS_FS.cpp \
    ../../../tabular/delineated_datarec.cpp \
    ../../../OS/directory_entry_name_concrete.cpp \
    ../../../parameters/number_keyed.cpp \
    ../../../OS/file_system_engine_Qt.cpp \
    ../../../OS/uniform_resource_identifier.cpp \
    ../../../OS/uniform_resource_locator.cpp \
    ../../../labeled_bitmask.cpp \
    ../../../data_source/command_options_datasrc.cpp \
    ../../../seclusion.cpp \
    ../../../application/project.cpp \
    ../../../application/arguments.cpp \
    ../../../data_source/vv_file.cpp \
    ../../../Internet/HTTP/request.cpp \
    ../../../OS/file_system_engine_Windows.cpp \
    ../../../application/progress.cpp \
    ../../../chronometry/temporal.cpp \
    ../../../chronometry/date_32.cpp \
    ../../../chronometry/date_A.cpp \
    ../../../chronometry/date_format.cpp \
    ../../../chronometry/date_translator.cpp \
    ../../../chronometry/time_format.cpp \
    ../../../chronometry/time_second.cpp \
    ../../../chronometry/date_time_64.cpp \
    ../../../chronometry/time_A.cpp \
    ../../../chronometry/date_time_A.cpp \
    ../../../chronometry/time_A.cpp \
    ../../../chronometry/date_A.cpp

#        ../../../file_sys/smart_filename.cpp \
#    ../../../file_sys/smart_dirname.cpp \
#    ../../../file_sys/filtered_filename.cpp \
#    ../../../file_sys/filename.cpp \
#    ../../../file_sys/file_system.cpp \
#    ../../../file_sys/dirname.cpp \

win32:CONFIG(release, debug|release): SOURCES +=
else:win32:CONFIG(debug, debug|release): SOURCES +=
else:symbian: SOURCES += ../../../OS/file_system_engine_Unix_and_Linux.cpp ../../../OS/file_system_engine_Unix_and_Linux.cpp
else:unix: SOURCES += ../../../OS/file_system_engine_Unix_and_Linux.cpp ../../../OS/file_system_engine_Unix_and_Linux.cpp


HEADERS += corn_complete_static.h \
    ../../../chronometry/time_types.h \
    ../../../OS/CSIDL.h \
    ../../../math/statistical/distribution_normal.h \
    ../../../OS/file_system_logical.h \
    ../../../OS/file_system_engine_Unix_and_Linux.h \
    ../../../OS/file_system_engine_common.h \
    ../../../OS/file_system_engine.h \
    ../../../OS/file_system.h \
    ../../../OS/directory_entry_name_logical.h \
    ../../../OS/directory_entry_name_abstract.h \
    ../../../OS/directory_entry_name.h \
    ../../../OS/directory.h \
    ../../../*.h \
    ../../../string/strconv.h \
    ../../../string/strconv.hpp \
    ../../../metrology/units_symbology.h \
    ../../../math/statistical/statistics_types.h \
    ../../../math/statistical/statistics_recorder.h \
    ../../../math/statistical/statistics_descriptive.h \
    ../../../math/statistical/statistics_common.h \
    ../../../math/statistical/sample_T.h \
    ../../../math/statistical/sample_dataset_T.h \
    ../../../math/statistical/sample_cumulative_T.h \
    ../../../math/statistical/distribution_Weibull.h \
    ../../../math/statistical/distribution_normal.h \
    ../../../math/statistical/statistics_types.hpp \
    ../../../OS/file_type_description.h \
    ../../../parameters/number_keyed.h \
    ../../../labeled_bitmask.h \
    ../../../data_source/vv_file.h \
    ../../../Internet/HTTP/request_cURL.c_cpp \
    ../../../chronometry/time_types.hpp \
    ../../../chronometry/time_types.hh \
    ../../../chronometry/time_second.h \
    ../../../chronometry/time_I.h \
    ../../../chronometry/time_format.h \
    ../../../chronometry/time_conversion.h \
    ../../../chronometry/time_A.h \
    ../../../chronometry/temporal.h \
    ../../../chronometry/date_types.hpp \
    ../../../chronometry/date_types.hh \
    ../../../chronometry/date_time_I.h \
    ../../../chronometry/date_time_A.h \
    ../../../chronometry/date_time_64.h \
    ../../../chronometry/date_I.h \
    ../../../chronometry/date_format.h \
    ../../../chronometry/date_const.hpp \
    ../../../chronometry/date_const.h \
    ../../../chronometry/date_A.h \
    ../../../chronometry/date_32.h \
    ../../../chronometry/date.hh \
    ../../../chronometry/time_fraction_T.h

unix:!symbian {
	 maemo5 {
		  target.path = /opt/usr/lib
	 } else {
		  target.path = /usr/lib
	 }
	 INSTALLS += target
}

#INCLUDEPATH += $$PWD/../../../../common/simulation/build/Qt/common_sim_static-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK__Release
#DEPENDPATH += $$PWD/../../../../common/simulation/build/Qt/common_sim_static-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK__Release
