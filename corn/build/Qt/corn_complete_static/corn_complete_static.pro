#-------------------------------------------------
#
# Project created by QtCreator 2012-03-30T01:33:25
#
#-------------------------------------------------

QT       -= gui

TARGET = corn_complete_static
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ../corn_complete_static . ../../../.. ../../../../corn
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
      #../../../data_source/dbase_datasrc.cpp \
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
      ../../../OS/uniform_resource_identifier.cpp \
      ../../../OS/uniform_resource_locator.cpp \
      ../../../labeled_bitmask.cpp \
      ../../../data_source/command_options_datasrc.cpp \
      ../../../seclusion.cpp \
      ../../../application/project.cpp \
      ../../../application/arguments.cpp \
      ../../../application/progress.cpp \
      ../../../chronometry/temporal.cpp\
      ../../../chronometry/date_32.cpp \
      ../../../chronometry/date_A.cpp \
      ../../../chronometry/date_format.cpp \
      ../../../chronometry/date_time_64.cpp \
      ../../../chronometry/date_time_A.cpp \
      ../../../chronometry/date_translator.cpp \
      ../../../chronometry/time_A.cpp \
      ../../../chronometry/time_conversion.cpp \
      ../../../chronometry/time_format.cpp \
      ../../../chronometry/time_second.cpp \
      ../../../OS/file_system_engine_Unix_and_Linux.cpp \
                ../../../math/numerical/interpolate_2D_3D.cpp \
                ../../../math/numerical/interpolation/interpolation_A.cpp \
                ../../../math/numerical/interpolation/interpolator_temporal.cpp \
                ../../../math/numerical/interpolation/linear.cpp \
                ../../../math/numerical/interpolation/proximal.cpp \
                ../../../math/numerical/interpolation/spline_cubic.cpp \
                ../../../math/numerical/interpolation/step.cpp \
                ../../../math/numerical/observation.cpp
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
