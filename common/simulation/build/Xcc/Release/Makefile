#############################################################################
# Makefile for building: libcommon_sim_static.a
# Generated by qmake (3.0) (Qt 5.5.0)
# Project:  ../common_sim_static/common_sim_static.pro
# Template: lib
#############################################################################


####### Compiler, tools and options

#CC            = gcc
#CXX           = g++
DEFINES       = -DCS_VERSION=5 -DREACCH_VERSION=2 
CFLAGS        = $(TARGET_64_32_BIT) -pipe -O2 -fPIC -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = $(TARGET_64_32_BIT) -pipe -fpermissive -w -g -Wno-reorder -Wno-unused-parameter -Wno-unused-but-set-parameter -Wno-unused-but-set-variable -O2 -fPIC -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../common_sim_static -I. -I../../../../.. -I../../../.. -I../../../../../CropSyst/source 

DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f

AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../../../synchronization.cpp \
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
OBJECTS       = synchronization.o \
		simulation_project_directory.o \
		scenario.o \
		operation.o \
		log.o \
		exit_codes.o \
		event_types.o \
		event_status.o \
		balancer.o \
		scenario_directory.o \
		property.o
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = libcommon_sim_static.a


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

staticlib: $(TARGET)

$(TARGET):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGET)
	$(AR) $(TARGET) $(OBJECTS)



all:  $(TARGET)


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

synchronization.o: ../../../synchronization.cpp ../../../../../corn/string/strconv.hpp \
		../../../../../corn/string/strconv.h \
		../../../../../corn/primitive.h \
		../../../synchronization.h \
		../../../../../corn/labeled_enum.h \
		../../../../../corn/const.h \
		../../../../../corn/chronometry/date_32.h \
		../../../../../corn/std/std_iostream.h \
		../../../../../corn/std/std_check.h \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date.hh \
		../../../../../CropSyst/source/crop/growth_stages.hpp \
		../../../../../CropSyst/source/crop/growth_stages.h \
		../../../../../corn/data_source/datarec.h \
		../../../../../corn/data_source/vv_entry.h \
		../../../../../corn/container/association.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/container/item.h \
		../../../../../corn/measure/units.h \
		../../../../../corn/metrology/units_code.hpp \
		../../../../../corn/metrology/units_code.h \
		../../../../../corn/metrology/units_code_SI.h \
		../../../../../corn/metrology/units_code_common.h \
		../../../../../corn/metrology/units_code_temporal.h \
		../../../../../corn/metrology/units_code_CU.h \
		../../../../../corn/metrology/units_measure.h \
		../../../../../corn/metrology/units_clad.h \
		../../../../../corn/metrology/units_symbology.h \
		../../../../../corn/metrology/timestep.h \
		../../../../../corn/measure/units_deprecated.h \
		../../../../../corn/validate/validtyp.h \
		../../../../../corn/values_MSC.h \
		../../../../../corn/data_type_enum.h \
		../../../../../corn/parameters/parameter.h \
		../../../../../corn/measure/units_enum.h \
		../../../../../corn/parameters/number_keyed.h \
		../../../../../corn/chronometry/time_64.h \
		../../../../../corn/chronometry/time_format.h \
		../../../../../corn/chronometry/date_time_64.h \
		../../../../../corn/container/enumlist.h \
		../../../../../corn/OS/directory_entry_name.h \
		../../../../../corn/OS/file_system_types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o synchronization.o ../../../synchronization.cpp

simulation_project_directory.o: ../../../simulation_project_directory.cpp ../../../simulation_project_directory.h \
		../../../../../corn/application/project_directory_OS_FS.h \
		../../../../../corn/parameters/parameters_directory_OS_FS.h \
		../../../../../corn/parameters/parameters_types.h \
		../../../../../corn/OS/file_system_logical.h \
		../../../../../corn/OS/file_system.h \
		../../../../../corn/const.h \
		../../../../../corn/OS/directory_entry_name.h \
		../../../../../corn/primitive.h \
		../../../../../corn/container/item.h \
		../../../../../corn/string/strconv.hpp \
		../../../../../corn/string/strconv.h \
		../../../../../corn/OS/file_system_types.h \
		../../../../../corn/container/association.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/chronometry/date_time_64.h \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_format.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date_const.hpp \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../../corn/OS/file_system_engine.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o simulation_project_directory.o ../../../simulation_project_directory.cpp

scenario.o: ../../../scenario.cpp ../../../scenario.h \
		../../../event.h \
		../../../event_types.h \
		../../../../../corn/labeled_enum.h \
		../../../../../corn/primitive.h \
		../../../../../corn/const.h \
		../../../../../corn/OS/file_system_logical.h \
		../../../../../corn/OS/file_system.h \
		../../../../../corn/OS/directory_entry_name.h \
		../../../../../corn/container/item.h \
		../../../../../corn/string/strconv.hpp \
		../../../../../corn/string/strconv.h \
		../../../../../corn/OS/file_system_types.h \
		../../../../../corn/container/association.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/chronometry/date_time_64.h \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_format.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date_const.hpp \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../../corn/OS/directory_entry_name_abstract.h \
		../../../synchronization.h \
		../../../../../corn/chronometry/date_32.h \
		../../../../../corn/std/std_iostream.h \
		../../../../../corn/std/std_check.h \
		../../../../../CropSyst/source/crop/growth_stages.hpp \
		../../../../../CropSyst/source/crop/growth_stages.h \
		../../../../../corn/parameters/parameters_datarec.h \
		../../../../../corn/data_source/datarec.h \
		../../../../../corn/data_source/vv_entry.h \
		../../../../../corn/measure/units.h \
		../../../../../corn/metrology/units_code.hpp \
		../../../../../corn/metrology/units_code.h \
		../../../../../corn/metrology/units_code_SI.h \
		../../../../../corn/metrology/units_code_common.h \
		../../../../../corn/metrology/units_code_temporal.h \
		../../../../../corn/metrology/units_code_CU.h \
		../../../../../corn/metrology/units_measure.h \
		../../../../../corn/metrology/units_clad.h \
		../../../../../corn/metrology/units_symbology.h \
		../../../../../corn/metrology/timestep.h \
		../../../../../corn/measure/units_deprecated.h \
		../../../../../corn/validate/validtyp.h \
		../../../../../corn/values_MSC.h \
		../../../../../corn/data_type_enum.h \
		../../../../../corn/parameters/parameter.h \
		../../../../../corn/measure/units_enum.h \
		../../../../../corn/parameters/number_keyed.h \
		../../../../../corn/chronometry/time_64.h \
		../../../../../corn/container/enumlist.h \
		../../../../../corn/parameters/parameters.h \
		../../../../../corn/string/ustring.h \
		../../../../../corn/string/str/include.h \
		../../../../../corn/string/str/str.h \
		../../../../../corn/string/str/myexcept.h \
		../../../../../corn/parameters/parameters_types.h \
		../../../../geodesy/geolocation.h \
		../../../../geodesy/geocoordinate.h \
		../../../../../corn/measure/measures.h \
		../../../../../corn/math/compare.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scenario.o ../../../scenario.cpp

operation.o: ../../../operation.cpp ../../../operation.h \
		../../../../../corn/primitive.h \
		../../../../../corn/const.h \
		../../../../../corn/parameters/parameters_datarec.h \
		../../../../../corn/data_source/datarec.h \
		../../../../../corn/data_source/vv_entry.h \
		../../../../../corn/container/association.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/container/item.h \
		../../../../../corn/labeled_enum.h \
		../../../../../corn/measure/units.h \
		../../../../../corn/metrology/units_code.hpp \
		../../../../../corn/metrology/units_code.h \
		../../../../../corn/metrology/units_code_SI.h \
		../../../../../corn/metrology/units_code_common.h \
		../../../../../corn/metrology/units_code_temporal.h \
		../../../../../corn/metrology/units_code_CU.h \
		../../../../../corn/metrology/units_measure.h \
		../../../../../corn/metrology/units_clad.h \
		../../../../../corn/metrology/units_symbology.h \
		../../../../../corn/metrology/timestep.h \
		../../../../../corn/measure/units_deprecated.h \
		../../../../../corn/validate/validtyp.h \
		../../../../../corn/values_MSC.h \
		../../../../../corn/data_type_enum.h \
		../../../../../corn/parameters/parameter.h \
		../../../../../corn/measure/units_enum.h \
		../../../../../corn/parameters/number_keyed.h \
		../../../../../corn/chronometry/date_32.h \
		../../../../../corn/std/std_iostream.h \
		../../../../../corn/std/std_check.h \
		../../../../../corn/chronometry/date_const.hpp \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date_32.h \
		../../../../../corn/chronometry/time_64.h \
		../../../../../corn/chronometry/time_format.h \
		../../../../../corn/chronometry/date_time_64.h \
		../../../../../corn/container/enumlist.h \
		../../../../../corn/OS/directory_entry_name.h \
		../../../../../corn/string/strconv.hpp \
		../../../../../corn/string/strconv.h \
		../../../../../corn/OS/file_system_types.h \
		../../../../../corn/parameters/parameters.h \
		../../../../../corn/string/ustring.h \
		../../../../../corn/string/str/include.h \
		../../../../../corn/string/str/str.h \
		../../../../../corn/string/str/myexcept.h \
		../../../../../corn/parameters/parameters_types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o operation.o ../../../operation.cpp

log.o: ../../../log.cpp ../../../../../corn/chronometry/date_32.h \
		../../../../../corn/std/std_iostream.h \
		../../../../../corn/std/std_check.h \
		../../../../../corn/chronometry/date_const.hpp \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/primitive.h \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/const.h \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date.hh \
		../../../log.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log.o ../../../log.cpp

exit_codes.o: ../../../exit_codes.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o exit_codes.o ../../../exit_codes.cpp

event_types.o: ../../../event_types.cpp ../../../event_types.h \
		../../../../../corn/labeled_enum.h \
		../../../../../corn/primitive.h \
		../../../../../corn/const.h \
		../../../../../corn/OS/file_system_logical.h \
		../../../../../corn/OS/file_system.h \
		../../../../../corn/OS/directory_entry_name.h \
		../../../../../corn/container/item.h \
		../../../../../corn/string/strconv.hpp \
		../../../../../corn/string/strconv.h \
		../../../../../corn/OS/file_system_types.h \
		../../../../../corn/container/association.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/chronometry/date_time_64.h \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_format.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date_const.hpp \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../../corn/OS/directory_entry_name_abstract.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o event_types.o ../../../event_types.cpp

event_status.o: ../../../event_status.cpp ../../../event_status.h \
		../../../../../corn/labeled_enum.h \
		../../../../../corn/primitive.h \
		../../../../../corn/const.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o event_status.o ../../../event_status.cpp

balancer.o: ../../../balancer.cpp ../../../balancer.h \
		../../../../../corn/primitive.h \
		../../../../../corn/dynamic_array/dynamic_array_T.h \
		../../../../../corn/const.h \
		../../../../../corn/math/moremath.h \
		../../../../../corn/math/compare.hpp \
		../../../../../corn/std/std_iomanip.h \
		../../../../../corn/std/std_check.h \
		../../../../../corn/std/std_iostream.h \
		../../../../../UED/library/UED_types.h \
		../../../../../UED/library/codes.h \
		../../../../../corn/validate/validtyp.h \
		../../../../../corn/values_MSC.h \
		../../../../../corn/measure/units.h \
		../../../../../corn/metrology/units_code.hpp \
		../../../../../corn/metrology/units_code.h \
		../../../../../corn/metrology/units_code_SI.h \
		../../../../../corn/metrology/units_code_common.h \
		../../../../../corn/metrology/units_code_temporal.h \
		../../../../../corn/metrology/units_code_CU.h \
		../../../../../corn/metrology/units_measure.h \
		../../../../../corn/metrology/units_clad.h \
		../../../../../corn/metrology/units_symbology.h \
		../../../../../corn/metrology/timestep.h \
		../../../../../corn/measure/units_deprecated.h \
		../../../../../corn/quality.hpp \
		../../../../../corn/labeled_enum.h \
		../../../../../corn/quality.h \
		../../../../../corn/math/compare.h \
		../../../../../CS_suite/simulation/CS_simulation_element.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/container/item.h \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../CS_suite/observation/CS_observation.h \
		../../../../../corn/math/statistical/statistics_types.hpp \
		../../../../../corn/math/statistical/statistics_types.h \
		../../../../../CS_suite/observation/CS_emanator.h \
		../../../../../corn/container/enumlist.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/text_list.h \
		../../../../../corn/chronometry/date_32.h \
		../../../../../corn/chronometry/date_const.hpp \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date.hh \
		../../../../../corn/measure/measures.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o balancer.o ../../../balancer.cpp

scenario_directory.o: ../../../scenario_directory.cpp ../../../scenario_directory.h \
		../../../../../corn/OS/file_system.h \
		../../../../../corn/const.h \
		../../../../../corn/OS/directory_entry_name.h \
		../../../../../corn/primitive.h \
		../../../../../corn/container/item.h \
		../../../../../corn/string/strconv.hpp \
		../../../../../corn/string/strconv.h \
		../../../../../corn/OS/file_system_types.h \
		../../../../../corn/container/association.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/chronometry/date_time_64.h \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/time_format.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/date_const.hpp \
		../../../../../corn/chronometry/date_const.h \
		../../../../../corn/parameters/parameters_directory_OS_FS.h \
		../../../../../corn/parameters/parameters_types.h \
		../../../../../corn/OS/file_system_logical.h \
		../../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../../corn/OS/file_system_engine.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scenario_directory.o ../../../scenario_directory.cpp

property.o: ../../../../physics/property.cpp ../../../../physics/property.h \
		../../../../../corn/const.h \
		../../../../../corn/primitive.h \
		../../../../../corn/metrology/units_code.hpp \
		../../../../../corn/metrology/units_code.h \
		../../../../../corn/metrology/units_code_SI.h \
		../../../../../corn/metrology/units_code_common.h \
		../../../../../corn/metrology/units_code_temporal.h \
		../../../../../corn/metrology/units_code_CU.h \
		../../../../../corn/metrology/units_measure.h \
		../../../../../corn/metrology/units_clad.h \
		../../../../../corn/quality.hpp \
		../../../../../corn/labeled_enum.h \
		../../../../../corn/quality.h \
		../../../../../corn/math/compare.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o property.o ../../../../physics/property.cpp

####### Install

install_target: first FORCE
	@test -d $(INSTALL_ROOT)/usr/lib || mkdir -p $(INSTALL_ROOT)/usr/lib
	-$(INSTALL_FILE) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET)

uninstall_target: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET)
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/lib/ 


install: install_target  FORCE

uninstall: uninstall_target  FORCE

FORCE:

