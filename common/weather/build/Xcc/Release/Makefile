#############################################################################
# Makefile for building: libweather_static.a
# Project:  ../weather_static/weather_static.pro
# Template: lib
#############################################################################

####### Compiler, tools and options

# This file included by the gcc and icc Makefiles

DEFINES       = -DCS_VERSION=5 -DREACCH_VERSION -DWEATHER_PROVIDER_VERSION=5 -DMICROBASIN_VERSION 
CFLAGS        = $(TARGET_64_32_BIT) -pipe -O2 -fPIC -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = $(TARGET_64_32_BIT) -pipe -fpermissive -w -g -Wno-reorder -Wno-unused-parameter  -O2 -fPIC -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../weather_static -I/usr/include -I../../../../../common -I../../../../.. -I../../../../../CS_suite -I. -I../weather_static -I.
AR            = ar cqs
RANLIB        = 
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../../../weather_types.cpp \
		../../../stormgen.cpp \
		../../../storm_event.cpp \
		../../../sky.cpp \
		../../../loc_param.cpp \
		../../../any_timestep/temperature_est.cpp \
		../../../any_timestep/relhumid_est.cpp \
		../../../any_timestep/min_max_to_timestep_estimator.cpp \
		../../../day/weather_day.cpp \
		../../../day/sun_days.cpp \
		../../../database/common_weather_creators.cpp \
		../../../hour/weather_hours.cpp \
		../../../hour/sun_hours.cpp \
		../../../hour/solar_irrad_hour.cpp \
		../../../parameter/WP_wind_speed.cpp \
		../../../parameter/WP_vapor_pressure.cpp \
		../../../parameter/WP_dew_point_temperature.cpp \
		../../../parameter/WP_atmospheric_pressure.cpp \
		../../../phrases.cpp \
		../../../atmospheric_CO2_change_recalibration.cpp \
		../../../atmospheric_CO2_change_linear.cpp \
		../../../../biometeorology/ET_reference_FAO.cpp \
		../../../../biometeorology/ET_model.cpp \
		../../../../biometeorology/ET_common.cpp \
		../../../../biometeorology/aerodynamics.cpp \
		../../../sun.cpp \
		../../../storms.cpp \
		../../../parameter/WC_vapor_pressure.cpp \
		../../../parameter/WC_vapor_pressure_saturation_slope.cpp \
		../../../parameter/WC_vapor_pressure_deficit.cpp \
		../../../parameter/WC_vapor_pressure_act.cpp \
		../../../parameter/WC_solar_radiation.cpp \
		../../../parameter/WC_relative_humidity.cpp \
		../../../parameter/WC_psychrometric_const.cpp \
		../../../parameter/WC_dew_point_temperature.cpp \
		../../../parameter/WC_air_temperature.cpp \
		../../../parameter/WC_ET_reference.cpp \
		../../../database/weather_UED_database.cpp \
		../../../../physics/property/P_vapor_pressure.cpp \
		../../../seasons.cpp \
		../../../temperature_amplitude_phase_calibrator.cpp \
		../../../../biometeorology/parameter/CO2_atmospheric_conc.cpp \
		../../../../solar/irradiance_extraterrestrial.cpp \
		../../../../biometeorology/parameter/slope_SVP_curve_psychrometric_resistance.cpp \
		../../../weather_provider.cpp \
		../../../snow_pack.cpp \
		../../../subdaily.cpp \
		../../../weather.cpp \
		../../../daily.cpp \
		../../../wthr.cpp \
		../../../wthrbase.cpp \
		../../../database/CS_weather_daily_UED.cpp \
		../../../../biometeorology/ET_reference.cpp \
		../../../../biometeorology/ET_reference_Priestley_Taylor.cpp \
        ../../../parameter/WC_humidity_specific.cpp \
        ../../../../../corn/math/numerical/interpolation/interpolator_temporal.cpp \
        ../../../../../corn/chronometry/time_conversion.cpp \
        ../../../../../corn/math/numerical/observation.cpp \
        ../../../../../corn/math/numerical/interpolation/linear.cpp \
        ../../../../../corn/math/numerical/interpolation/interpolation_A.cpp \
        ../../../../../corn/math/numerical/interpolation/step.cpp
OBJECTS       = weather_types.o \
		stormgen.o \
		storm_event.o \
		sky.o \
		loc_param.o \
		temperature_est.o \
		relhumid_est.o \
		min_max_to_timestep_estimator.o \
		weather_day.o \
		sun_days.o \
		common_weather_creators.o \
		weather_hours.o \
		sun_hours.o \
		solar_irrad_hour.o \
		WP_wind_speed.o \
		WP_vapor_pressure.o \
		WP_dew_point_temperature.o \
		WP_atmospheric_pressure.o \
		phrases.o \
		atmospheric_CO2_change_recalibration.o \
		atmospheric_CO2_change_linear.o \
		ET_reference_FAO.o \
		ET_model.o \
		ET_common.o \
		aerodynamics.o \
		sun.o \
		storms.o \
		WC_vapor_pressure.o \
		WC_vapor_pressure_saturation_slope.o \
		WC_vapor_pressure_deficit.o \
		WC_vapor_pressure_act.o \
		WC_solar_radiation.o \
		WC_relative_humidity.o \
		WC_psychrometric_const.o \
		WC_dew_point_temperature.o \
		WC_air_temperature.o \
		WC_ET_reference.o \
		weather_UED_database.o \
		P_vapor_pressure.o \
		seasons.o \
		temperature_amplitude_phase_calibrator.o \
		CO2_atmospheric_conc.o \
		irradiance_extraterrestrial.o \
		slope_SVP_curve_psychrometric_resistance.o \
		weather_provider.o \
		snow_pack.o \
		subdaily.o \
		weather.o \
		daily.o \
		wthr.o \
		wthrbase.o \
		CS_weather_daily_UED.o \
		ET_reference.o \
		ET_reference_Priestley_Taylor.o \
        WC_humidity_specific.o \
        interpolator_temporal.o \
        time_conversion.o \
        observation.o \
        linear.o \
        interpolation_A.o \
        step.o
TARGET        = libweather_static.a

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

all:  $(TARGET) 

staticlib: $(TARGET)

$(TARGET):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGET)
	$(AR) $(TARGET) $(OBJECTS)



clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

weather_types.o: ../../../weather_types.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o weather_types.o ../../../weather_types.cpp

stormgen.o: ../../../stormgen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stormgen.o ../../../stormgen.cpp

storm_event.o: ../../../storm_event.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o storm_event.o ../../../storm_event.cpp

sky.o: ../../../sky.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sky.o ../../../sky.cpp

loc_param.o: ../../../loc_param.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o loc_param.o ../../../loc_param.cpp

temperature_est.o: ../../../any_timestep/temperature_est.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o temperature_est.o ../../../any_timestep/temperature_est.cpp

relhumid_est.o: ../../../any_timestep/relhumid_est.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o relhumid_est.o ../../../any_timestep/relhumid_est.cpp

min_max_to_timestep_estimator.o: ../../../any_timestep/min_max_to_timestep_estimator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o min_max_to_timestep_estimator.o ../../../any_timestep/min_max_to_timestep_estimator.cpp

weather_day.o: ../../../day/weather_day.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o weather_day.o ../../../day/weather_day.cpp

sun_days.o: ../../../day/sun_days.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sun_days.o ../../../day/sun_days.cpp

common_weather_creators.o: ../../../database/common_weather_creators.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o common_weather_creators.o ../../../database/common_weather_creators.cpp

weather_hours.o: ../../../hour/weather_hours.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o weather_hours.o ../../../hour/weather_hours.cpp

sun_hours.o: ../../../hour/sun_hours.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sun_hours.o ../../../hour/sun_hours.cpp

solar_irrad_hour.o: ../../../hour/solar_irrad_hour.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o solar_irrad_hour.o ../../../hour/solar_irrad_hour.cpp

WP_wind_speed.o: ../../../parameter/WP_wind_speed.cpp ../../../parameter/WP_wind_speed.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WP_wind_speed.o ../../../parameter/WP_wind_speed.cpp

WP_vapor_pressure.o: ../../../parameter/WP_vapor_pressure.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WP_vapor_pressure.o ../../../parameter/WP_vapor_pressure.cpp

WP_dew_point_temperature.o: ../../../parameter/WP_dew_point_temperature.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WP_dew_point_temperature.o ../../../parameter/WP_dew_point_temperature.cpp

WP_atmospheric_pressure.o: ../../../parameter/WP_atmospheric_pressure.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WP_atmospheric_pressure.o ../../../parameter/WP_atmospheric_pressure.cpp

phrases.o: ../../../phrases.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o phrases.o ../../../phrases.cpp

atmospheric_CO2_change_recalibration.o: ../../../atmospheric_CO2_change_recalibration.cpp ../../../atmospheric_CO2_change_recalibration.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o atmospheric_CO2_change_recalibration.o ../../../atmospheric_CO2_change_recalibration.cpp

atmospheric_CO2_change_linear.o: ../../../atmospheric_CO2_change_linear.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o atmospheric_CO2_change_linear.o ../../../atmospheric_CO2_change_linear.cpp

ET_reference_FAO.o: ../../../../biometeorology/ET_reference_FAO.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ET_reference_FAO.o ../../../../biometeorology/ET_reference_FAO.cpp

ET_model.o: ../../../../biometeorology/ET_model.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ET_model.o ../../../../biometeorology/ET_model.cpp

ET_common.o: ../../../../biometeorology/ET_common.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ET_common.o ../../../../biometeorology/ET_common.cpp

aerodynamics.o: ../../../../biometeorology/aerodynamics.cpp ../../../../biometeorology/aerodynamics.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o aerodynamics.o ../../../../biometeorology/aerodynamics.cpp

sun.o: ../../../sun.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sun.o ../../../sun.cpp

storms.o: ../../../storms.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o storms.o ../../../storms.cpp

WC_vapor_pressure.o: ../../../parameter/WC_vapor_pressure.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_vapor_pressure.o ../../../parameter/WC_vapor_pressure.cpp

WC_vapor_pressure_saturation_slope.o: ../../../parameter/WC_vapor_pressure_saturation_slope.cpp ../../../parameter/WC_vapor_pressure_saturation_slope.h \
		../../../parameter/WP_vapor_pressure_saturation_slope.h \
		../../../parameter/WP_vapor_pressure.h \
		../../../parameter/WP_air_temperature.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_vapor_pressure_saturation_slope.o ../../../parameter/WC_vapor_pressure_saturation_slope.cpp

WC_vapor_pressure_deficit.o: ../../../parameter/WC_vapor_pressure_deficit.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_vapor_pressure_deficit.o ../../../parameter/WC_vapor_pressure_deficit.cpp

WC_vapor_pressure_act.o: ../../../parameter/WC_vapor_pressure_act.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_vapor_pressure_act.o ../../../parameter/WC_vapor_pressure_act.cpp

WC_solar_radiation.o: ../../../parameter/WC_solar_radiation.cpp ../../../parameter/WC_solar_radiation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_solar_radiation.o ../../../parameter/WC_solar_radiation.cpp

WC_relative_humidity.o: ../../../parameter/WC_relative_humidity.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_relative_humidity.o ../../../parameter/WC_relative_humidity.cpp

WC_psychrometric_const.o: ../../../parameter/WC_psychrometric_const.cpp ../../../parameter/WC_psychrometric_const.h \
		../../../parameter/WP_atmospheric_pressure.h \
		../../../parameter/WP_latent_heat_vaporization.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_psychrometric_const.o ../../../parameter/WC_psychrometric_const.cpp

WC_dew_point_temperature.o: ../../../parameter/WC_dew_point_temperature.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_dew_point_temperature.o ../../../parameter/WC_dew_point_temperature.cpp

WC_air_temperature.o: ../../../parameter/WC_air_temperature.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_air_temperature.o ../../../parameter/WC_air_temperature.cpp

WC_ET_reference.o: ../../../parameter/WC_ET_reference.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_ET_reference.o ../../../parameter/WC_ET_reference.cpp

weather_UED_database.o: ../../../database/weather_UED_database.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o weather_UED_database.o ../../../database/weather_UED_database.cpp

P_vapor_pressure.o: ../../../../physics/property/P_vapor_pressure.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o P_vapor_pressure.o ../../../../physics/property/P_vapor_pressure.cpp

seasons.o: ../../../seasons.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o seasons.o ../../../seasons.cpp

temperature_amplitude_phase_calibrator.o: ../../../temperature_amplitude_phase_calibrator.cpp ../../../temperature_amplitude_phase_calibrator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o temperature_amplitude_phase_calibrator.o ../../../temperature_amplitude_phase_calibrator.cpp

CO2_atmospheric_conc.o: ../../../../biometeorology/parameter/CO2_atmospheric_conc.cpp ../../../../biometeorology/parameter/CO2_atmospheric_conc.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CO2_atmospheric_conc.o ../../../../biometeorology/parameter/CO2_atmospheric_conc.cpp

irradiance_extraterrestrial.o: ../../../../solar/irradiance_extraterrestrial.cpp ../../../../solar/irradiance_extraterrestrial.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o irradiance_extraterrestrial.o ../../../../solar/irradiance_extraterrestrial.cpp

slope_SVP_curve_psychrometric_resistance.o: ../../../../biometeorology/parameter/slope_SVP_curve_psychrometric_resistance.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o slope_SVP_curve_psychrometric_resistance.o ../../../../biometeorology/parameter/slope_SVP_curve_psychrometric_resistance.cpp

weather_provider.o: ../../../weather_provider.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o weather_provider.o ../../../weather_provider.cpp

snow_pack.o: ../../../snow_pack.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o snow_pack.o ../../../snow_pack.cpp

subdaily.o: ../../../subdaily.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o subdaily.o ../../../subdaily.cpp

weather.o: ../../../weather.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o weather.o ../../../weather.cpp

daily.o: ../../../daily.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o daily.o ../../../daily.cpp

wthr.o: ../../../wthr.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wthr.o ../../../wthr.cpp

wthrbase.o: ../../../wthrbase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wthrbase.o ../../../wthrbase.cpp

CS_weather_daily_UED.o: ../../../database/CS_weather_daily_UED.cpp ../../../database/CS_weather_daily_UED.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CS_weather_daily_UED.o ../../../database/CS_weather_daily_UED.cpp

ET_reference.o: ../../../../biometeorology/ET_reference.cpp ../../../../biometeorology/ET_reference.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ET_reference.o ../../../../biometeorology/ET_reference.cpp

ET_reference_Priestley_Taylor.o: ../../../../../common/biometeorology/ET_reference_Priestley_Taylor.cpp ../../../../../common/biometeorology/ET_reference_Priestley_Taylor.h \
		../../../../../corn/primitive.h \
		../../../../../corn/const.h \
		../../../../../common/CS_parameter_float64.h \
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
		../../../../../common/CS_parameter_cowl_T.h \
		../../../../../common/physics/property_cowl_T.h \
		../../../../../common/physics/property.h \
		../../../../../corn/measure/unitconv.h \
		../../../../../corn/math/compare.hpp \
		../../../../../common/CS_parameter.h \
		../../../../../common/physics/property_complete.h \
		../../../../../common/weather/parameter/WP_vapor_pressure_deficit.h \
		../../../../../common/weather/parameter/WP_vapor_pressure.h \
		../../../../../common/physics/property/P_vapor_pressure.h \
		../../../../../common/physics/property/P_pressure.h \
		../../../../../corn/measure/measures.h \
		../../../../../common/weather/weather_types.h \
		../../../../../corn/data_source/datarec.h \
		../../../../../corn/data_source/vv_entry.h \
		../../../../../corn/container/association.h \
		../../../../../corn/container/bilist.h \
		../../../../../corn/container/unilist.h \
		../../../../../corn/container/container.h \
		../../../../../corn/container/item.h \
		../../../../../corn/data_type_enum.h \
		../../../../../corn/parameters/parameter.h \
		../../../../../corn/measure/units_enum.h \
		../../../../../corn/parameters/number_keyed.h \
		../../../../../corn/format/field.h \
		../../../../../corn/chronometry/date_time_64.h \
		../../../../../corn/chronometry/date_time_T.h \
		../../../../../corn/chronometry/date_time_A.h \
		../../../../../corn/chronometry/date_time_I.h \
		../../../../../corn/chronometry/date_I.h \
		../../../../../corn/chronometry/temporal.h \
		../../../../../corn/chronometry/date_types.hpp \
		../../../../../corn/chronometry/date_types.hh \
		../../../../../corn/chronometry/time_types.hpp \
		../../../../../corn/chronometry/time_types.hh \
		../../../../../corn/chronometry/time_I.h \
		../../../../../corn/chronometry/date_A.h \
		../../../../../corn/chronometry/date_format.h \
		../../../../../corn/chronometry/time_A.h \
		../../../../../corn/chronometry/time_format.h \
		../../../../../corn/chronometry/time_fraction_T.h \
		../../../../../corn/chronometry/date_T.h \
		../../../../../corn/chronometry/date_32.h \
		../../../../../corn/container/enumlist.h \
		../../../../../corn/container/text_list.h \
		../../../../../corn/string/strconv.hpp \
		../../../../../corn/string/strconv.h \
		../../../../../corn/OS/directory_entry_name.h \
		../../../../../corn/OS/file_system_types.h \
		../../../../../corn/dynamic_array/dynamic_array_T.h \
		../../../../../corn/math/moremath.h \
		../../../../../corn/std/std_iomanip.h \
		../../../../../corn/std/std_check.h \
		../../../../../corn/std/std_iostream.h \
		../../../../../common/biometeorology/ET_model.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ET_reference_Priestley_Taylor.o ../../../../../common/biometeorology/ET_reference_Priestley_Taylor.cpp

WC_humidity_specific.o: ../../../parameter/WC_humidity_specific.cpp ../../../parameter/WC_humidity_specific.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WC_humidity_specific.o ../../../parameter/WC_humidity_specific.cpp
    
interpolator_temporal.o: ../../../../../corn/math/numerical/interpolation/interpolator_temporal.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o interpolator_temporal.o ../../../../../corn/math/numerical/interpolation/interpolator_temporal.cpp

time_conversion.o: ../../../../../corn/chronometry/time_conversion.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o time_conversion.o ../../../../../corn/chronometry/time_conversion.cpp

observation.o : ../../../../../corn/math/numerical/observation.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o observation.o ../../../../../corn/math/numerical/observation.cpp

linear.o: ../../../../../corn/math/numerical/interpolation/linear.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o linear.o ../../../../../corn/math/numerical/interpolation/linear.cpp

interpolation_A.o: ../../../../../corn/math/numerical/interpolation/interpolation_A.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o interpolation_A.o ../../../../../corn/math/numerical/interpolation/interpolation_A.cpp

step.o: ../../../../../corn/math/numerical/interpolation/step.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o step.o ../../../../../corn/math/numerical/interpolation/step.cpp
####### Install

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/usr/lib/ || $(MKDIR) $(INSTALL_ROOT)/usr/lib/ 
	-$(INSTALL_FILE) "$(TARGET)" "$(INSTALL_ROOT)/usr/lib/$(TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/usr/lib/$(TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/lib/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

