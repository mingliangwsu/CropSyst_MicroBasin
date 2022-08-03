#-------------------------------------------------
#
# Project created by QtCreator 2012-04-05T20:28:37
#
#-------------------------------------------------

QT       -= gui

TARGET = weather_provider_static
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ../../../../../common ../../../../../../dev
DEFINES += CS_VERSION=5 REACCH_VERSION WEATHER_PROVIDER_VERSION=5
# USE_WEATHER_PROVIDER
QMAKE_CXXFLAGS += -fpermissive  -w -g
QMAKE_CXXFLAGS += -Wno-reorder -Wno-unused-parameter

SOURCES += \
    ../../../weather_types.cpp \
    ../../../stormgen.cpp \
    ../../../storm_event.cpp \
    ../../../loc_param.cpp \
    ../../../any_timestep/temperature_est.cpp \
    ../../../any_timestep/relhumid_est.cpp \
    ../../../any_timestep/min_max_to_timestep_estimator.cpp \
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
    ../../../atmospheric_CO2_change_interface.cpp \
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
    ../../../../physics/property/P_vapor_pressure.cpp \
    ../../../seasons.cpp \
    ../../../weather_provider.cpp \
    ../../../../solar/irradiance_extraterrestrial.cpp \
    ../../../../biometeorology/parameter/slope_SVP_curve_psychrometric_resistance.cpp \
    ../../../snow_pack.cpp \
    ../../../parameter/WC_ET_reference.cpp \
    ../../../subdaily.cpp \
    ../../../sky.cpp \
    ../../../parameter/WC_air_temperature.cpp \
    ../../../../physics/water_depth.cpp \
    ../../../database/weather_UED_database.cpp \
    ../../../daily.cpp \
    ../../../../biometeorology/ET_reference.cpp \
    ../../../database/CS_weather_daily_UED.cpp

#HEADERS += weather_static.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

HEADERS += \
    ../../../parameter/WC_relative_humidity.h \
    ../../../atmospheric_CO2_change_interface.h

