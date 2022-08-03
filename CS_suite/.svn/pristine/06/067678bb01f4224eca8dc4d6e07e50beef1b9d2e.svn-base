#############################################################################
# Makefile for building: libCS_directory.a
# Template: lib
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DCS_VERSION=4 
CFLAGS        = $(TARGET_64_32_BIT) -pipe -O2 -fPIC -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = $(TARGET_64_32_BIT) -pipe -O2 -fPIC -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../CS_directory -I. -I../../../.. -I. 
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
DISTNAME      = CS_directory1.0.0
DISTDIR = ../../../../CS_suite/build/Qt/Release/.tmp/CS_directory1.0.0
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = \
		../../../CS_application_directory.cpp \
		../../../CS_suite_directory.cpp \
		../../../CANMS/CANMS_directory.cpp \
		../../../ClimGen/ClimGen_directory.cpp \
		../../../CropSyst/CropSyst_directory.cpp \
		../../../UED/UED_directory.cpp \
		../../../file_system/CS_database_directory.cpp 
OBJECTS       = \
		CS_application_directory.o \
		CS_suite_directory.o \
		CANMS_directory.o \
		ClimGen_directory.o \
		CropSyst_directory.o \
		UED_directory.o \
		CS_database_directory.o
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = libCS_directory.a


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



all: Makefile $(TARGET)


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

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


CS_application_directory.o: ../../../CS_application_directory.cpp ../../../CS_application_directory.h \
		../../../../corn/application/application_directory_OS_FS.h \
		../../../../corn/OS/file_system_logical.h \
		../../../../corn/OS/file_system.h \
		../../../../corn/const.h \
		../../../../corn/OS/directory_entry_name.h \
		../../../../corn/primitive.h \
		../../../../corn/container/item.h \
		../../../../corn/string/strconv.hpp \
		../../../../corn/string/strconv.h \
		../../../../corn/OS/file_system_types.h \
		../../../../corn/container/association.h \
		../../../../corn/container/bilist.h \
		../../../../corn/container/unilist.h \
		../../../../corn/container/container.h \
		../../../../corn/datetime/datetime64.h \
		../../../../corn/datetime/date_time_interface.h \
		../../../../corn/chronometry/date_types.hpp \
		../../../../corn/chronometry/date_types.hh \
		../../../../corn/chronometry/time_types.hpp \
		../../../../corn/chronometry/time_types.hh \
		../../../../corn/datetime/temporal_base.h \
		../../../../corn/datetime/time_format.h \
		../../../../corn/datetime/date_format.h \
		../../../../corn/datetime/date_const.hpp \
		../../../../corn/datetime/date_const.h \
		../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../corn/application/documentation_directory_OS_FS.h \
		../../../../corn/application/adjunct_directory_OS_FS.h \
		../../../CS_suite_directory.h \
		../../../../corn/application/suite_directory_OS_FS.h \
		../../../CAFE/CAFE_directory.h \
		../../../CropSyst/CropSyst_directory.h \
		../../../ClimGen/ClimGen_directory.h \
		../../../../corn/application/program_directory_OS_FS.h \
		../../../CANMS/CANMS_directory.h \
		../../../UED/UED_directory.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CS_application_directory.o ../../../CS_application_directory.cpp

CS_suite_directory.o: ../../../CS_suite_directory.cpp ../../../CS_suite_directory.h \
		../../../../corn/application/suite_directory_OS_FS.h \
		../../../../corn/application/documentation_directory_OS_FS.h \
		../../../../corn/application/adjunct_directory_OS_FS.h \
		../../../../corn/OS/file_system_logical.h \
		../../../../corn/OS/file_system.h \
		../../../../corn/const.h \
		../../../../corn/OS/directory_entry_name.h \
		../../../../corn/primitive.h \
		../../../../corn/container/item.h \
		../../../../corn/string/strconv.hpp \
		../../../../corn/string/strconv.h \
		../../../../corn/OS/file_system_types.h \
		../../../../corn/container/association.h \
		../../../../corn/container/bilist.h \
		../../../../corn/container/unilist.h \
		../../../../corn/container/container.h \
		../../../../corn/datetime/datetime64.h \
		../../../../corn/datetime/date_time_interface.h \
		../../../../corn/chronometry/date_types.hpp \
		../../../../corn/chronometry/date_types.hh \
		../../../../corn/chronometry/time_types.hpp \
		../../../../corn/chronometry/time_types.hh \
		../../../../corn/datetime/temporal_base.h \
		../../../../corn/datetime/time_format.h \
		../../../../corn/datetime/date_format.h \
		../../../../corn/datetime/date_const.hpp \
		../../../../corn/datetime/date_const.h \
		../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../corn/application/application_directory_OS_FS.h \
		../../../CAFE/CAFE_directory.h \
		../../../CropSyst/CropSyst_directory.h \
		../../../CS_application_directory.h \
		../../../ClimGen/ClimGen_directory.h \
		../../../../corn/application/program_directory_OS_FS.h \
		../../../CANMS/CANMS_directory.h \
		../../../UED/UED_directory.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CS_suite_directory.o ../../../CS_suite_directory.cpp

CANMS_directory.o: ../../../CANMS/CANMS_directory.cpp ../../../CANMS/CANMS_directory.h \
		../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../corn/const.h \
		../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../corn/OS/directory_entry_name.h \
		../../../../corn/primitive.h \
		../../../../corn/container/item.h \
		../../../../corn/string/strconv.hpp \
		../../../../corn/string/strconv.h \
		../../../../corn/OS/file_system_types.h \
		../../../CS_application_directory.h \
		../../../../corn/application/application_directory_OS_FS.h \
		../../../../corn/OS/file_system_logical.h \
		../../../../corn/OS/file_system.h \
		../../../../corn/container/association.h \
		../../../../corn/container/bilist.h \
		../../../../corn/container/unilist.h \
		../../../../corn/container/container.h \
		../../../../corn/datetime/datetime64.h \
		../../../../corn/datetime/date_time_interface.h \
		../../../../corn/chronometry/date_types.hpp \
		../../../../corn/chronometry/date_types.hh \
		../../../../corn/chronometry/time_types.hpp \
		../../../../corn/chronometry/time_types.hh \
		../../../../corn/datetime/temporal_base.h \
		../../../../corn/datetime/time_format.h \
		../../../../corn/datetime/date_format.h \
		../../../../corn/datetime/date_const.hpp \
		../../../../corn/datetime/date_const.h \
		../../../../corn/application/documentation_directory_OS_FS.h \
		../../../../corn/application/adjunct_directory_OS_FS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CANMS_directory.o ../../../CANMS/CANMS_directory.cpp

ClimGen_directory.o: ../../../ClimGen/ClimGen_directory.cpp ../../../ClimGen/ClimGen_directory.h \
		../../../../corn/application/program_directory_OS_FS.h \
		../../../../corn/application/adjunct_directory_OS_FS.h \
		../../../../corn/OS/file_system_logical.h \
		../../../../corn/OS/file_system.h \
		../../../../corn/const.h \
		../../../../corn/OS/directory_entry_name.h \
		../../../../corn/primitive.h \
		../../../../corn/container/item.h \
		../../../../corn/string/strconv.hpp \
		../../../../corn/string/strconv.h \
		../../../../corn/OS/file_system_types.h \
		../../../../corn/container/association.h \
		../../../../corn/container/bilist.h \
		../../../../corn/container/unilist.h \
		../../../../corn/container/container.h \
		../../../../corn/datetime/datetime64.h \
		../../../../corn/datetime/date_time_interface.h \
		../../../../corn/chronometry/date_types.hpp \
		../../../../corn/chronometry/date_types.hh \
		../../../../corn/chronometry/time_types.hpp \
		../../../../corn/chronometry/time_types.hh \
		../../../../corn/datetime/temporal_base.h \
		../../../../corn/datetime/time_format.h \
		../../../../corn/datetime/date_format.h \
		../../../../corn/datetime/date_const.hpp \
		../../../../corn/datetime/date_const.h \
		../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../corn/application/documentation_directory_OS_FS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ClimGen_directory.o ../../../ClimGen/ClimGen_directory.cpp

CropSyst_directory.o: ../../../CropSyst/CropSyst_directory.cpp ../../../CropSyst/CropSyst_directory.h \
		../../../CS_application_directory.h \
		../../../../corn/application/application_directory_OS_FS.h \
		../../../../corn/OS/file_system_logical.h \
		../../../../corn/OS/file_system.h \
		../../../../corn/const.h \
		../../../../corn/OS/directory_entry_name.h \
		../../../../corn/primitive.h \
		../../../../corn/container/item.h \
		../../../../corn/string/strconv.hpp \
		../../../../corn/string/strconv.h \
		../../../../corn/OS/file_system_types.h \
		../../../../corn/container/association.h \
		../../../../corn/container/bilist.h \
		../../../../corn/container/unilist.h \
		../../../../corn/container/container.h \
		../../../../corn/datetime/datetime64.h \
		../../../../corn/datetime/date_time_interface.h \
		../../../../corn/chronometry/date_types.hpp \
		../../../../corn/chronometry/date_types.hh \
		../../../../corn/chronometry/time_types.hpp \
		../../../../corn/chronometry/time_types.hh \
		../../../../corn/datetime/temporal_base.h \
		../../../../corn/datetime/time_format.h \
		../../../../corn/datetime/date_format.h \
		../../../../corn/datetime/date_const.hpp \
		../../../../corn/datetime/date_const.h \
		../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../corn/application/documentation_directory_OS_FS.h \
		../../../../corn/application/adjunct_directory_OS_FS.h \
		../../../CS_suite_directory.h \
		../../../../corn/application/suite_directory_OS_FS.h \
		../../../CAFE/CAFE_directory.h \
		../../../ClimGen/ClimGen_directory.h \
		../../../../corn/application/program_directory_OS_FS.h \
		../../../CANMS/CANMS_directory.h \
		../../../UED/UED_directory.h \
		../../../../corn/OS/file_system_engine.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CropSyst_directory.o ../../../CropSyst/CropSyst_directory.cpp

UED_directory.o: ../../../UED/UED_directory.cpp ../../../UED/UED_directory.h \
		../../../../corn/application/application_directory_OS_FS.h \
		../../../../corn/OS/file_system_logical.h \
		../../../../corn/OS/file_system.h \
		../../../../corn/const.h \
		../../../../corn/OS/directory_entry_name.h \
		../../../../corn/primitive.h \
		../../../../corn/container/item.h \
		../../../../corn/string/strconv.hpp \
		../../../../corn/string/strconv.h \
		../../../../corn/OS/file_system_types.h \
		../../../../corn/container/association.h \
		../../../../corn/container/bilist.h \
		../../../../corn/container/unilist.h \
		../../../../corn/container/container.h \
		../../../../corn/datetime/datetime64.h \
		../../../../corn/datetime/date_time_interface.h \
		../../../../corn/chronometry/date_types.hpp \
		../../../../corn/chronometry/date_types.hh \
		../../../../corn/chronometry/time_types.hpp \
		../../../../corn/chronometry/time_types.hh \
		../../../../corn/datetime/temporal_base.h \
		../../../../corn/datetime/time_format.h \
		../../../../corn/datetime/date_format.h \
		../../../../corn/datetime/date_const.hpp \
		../../../../corn/datetime/date_const.h \
		../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../corn/OS/directory_entry_name_abstract.h \
		../../../../corn/application/documentation_directory_OS_FS.h \
		../../../../corn/application/adjunct_directory_OS_FS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o UED_directory.o ../../../UED/UED_directory.cpp

CS_database_directory.o: ../../../file_system/CS_database_directory.cpp ../../../file_system/CS_database_directory.h \
		../../../../corn/OS/file_system_logical.h \
		../../../../corn/OS/file_system.h \
		../../../../corn/const.h \
		../../../../corn/OS/directory_entry_name.h \
		../../../../corn/primitive.h \
		../../../../corn/container/item.h \
		../../../../corn/string/strconv.hpp \
		../../../../corn/string/strconv.h \
		../../../../corn/OS/file_system_types.h \
		../../../../corn/container/association.h \
		../../../../corn/container/bilist.h \
		../../../../corn/container/unilist.h \
		../../../../corn/container/container.h \
		../../../../corn/datetime/datetime64.h \
		../../../../corn/datetime/date_time_interface.h \
		../../../../corn/chronometry/date_types.hpp \
		../../../../corn/chronometry/date_types.hh \
		../../../../corn/chronometry/time_types.hpp \
		../../../../corn/chronometry/time_types.hh \
		../../../../corn/datetime/temporal_base.h \
		../../../../corn/datetime/time_format.h \
		../../../../corn/datetime/date_format.h \
		../../../../corn/datetime/date_const.hpp \
		../../../../corn/datetime/date_const.h \
		../../../../corn/OS/directory_entry_name_concrete.h \
		../../../../corn/OS/directory_entry_name_abstract.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CS_database_directory.o ../../../file_system/CS_database_directory.cpp

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

