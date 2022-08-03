#-------------------------------------------------
#
# Project created by QtCreator 2013-09-18T13:05:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MicroBasin
CONFIG   += console
CONFIG   -= app_bundle

#for gcc
#QMAKE_CXXFLAGS += -fopenmp
#QMAKE_LFLAGS += -fopenmp

#for msvc
#QMAKE_CXXFLAGS+= -openmp
#QMAKE_LFLAGS +=  -openmp

LIBS += -fopenmp
INCLUDEPATH += ../../../ \
            ../../../../../ \
            ../../../../../common \
            ../../../../source \
            ../../../../../USDA/NRCS \
            ../../../../../corn \
            c:/dev/

DEFINES += USE_OS_FS CS_VERSION=5 CROPSYST_VERSION=5  \
MICROBASIN_VERSION LIU_DEBUG MB_Date=CORN::Date TRIVIAL_TEST USE_WEATHER_PROVIDER_V5 \
MBVB_HYDROLOGY MBVB_SOIL_PROPERTIES CHEMICAL_TRANSPORT MBVB_INFILTRATION

#xUSE_VARIABLE_RECORDERS

#Destruct_Monitor
#HOURLY_MET

TEMPLATE = app


SOURCES += ../../../main.cpp \
    ../../../util/pubtools.cpp \
    ../../../util/constants.cpp \
    ../../../time/timestateclass.cpp \
    ../../../basin/basinclass.cpp \
    ../../../basin/basincellclass.cpp \
    ../../../control/allcontrolclass.cpp \
    ../../../soil/soilprocessesclass.cpp \
    ../../../soil/soilstateclass.cpp \
    ../../../util/esrigridclass.cpp \
    ../../../control/globalvariable.cpp \
    ../../../../../common/soil/layering.cpp \
    ../../../../../common/soil/SCS/SCS.cpp \
    ../../../../source/soil/layers.cpp \
    ../../../../source/soil/hydrology.cpp \
    ../../../../source/soil/hydraulic_properties.cpp \
    ../../../../../USDA/NRCS/soil/survey/domains.cpp \
    ../../../soil/soilprofileclass2.cpp \
    ../../../soil/complete.cpp \
    ../../../../../CORN/labeled_enum.cpp \
    ../../../../../CORN/container/item.cpp \
    ../../../../../CORN/container/container.cpp \
    ../../../../../CORN/container/bilist.cpp \
    ../../../../../CORN/container/association.cpp \
    ../../../../../CORN/measure/measures.cpp \
    ../../../../../CORN/container/unilist.cpp \
    ../../../../../CORN/metrology/units_symbology.cpp \
    ../../../../../CORN/metrology/units_clad.cpp \
    ../../../../../CORN/metrology/timestep.cpp \
    ../../../../../CORN/data_source/vv_file.cpp \
    ../../../../../CORN/data_source/vv_entry.cpp \
    ../../../../../CORN/data_source/datasrc.cpp \
    ../../../../../CORN/data_source/datarec.cpp \
    ../../../../../CORN/container/text_list.cpp \
    ../../../../../CORN/container/enumlist.cpp \
    ../../../../../CORN/string/strconv.cpp \
    ../../../../../CORN/data_source/vv_datasrc.cpp \
    ../../../../../common/physics/property.cpp \
    ../../../../../common/physics/mass_common.cpp \
    ../../../../../common/physics/mass.cpp \
    ../../../../source/soil/soil_param_struct.cpp \
    ../../../../source/soil/soil_param_class.cpp \
    ../../../../../CORN/datetime/temporal_base.cpp \
    ../../../../../CORN/quality.cpp \
    ../../../../source/soil/soil_param_V5.cpp \
    ../../../../source/soil/soil_interface.cpp \
    ../../../../../CORN/parameters/parameters_datarec.cpp \
    ../../../../../CORN/parameters/parameters.cpp \
    ../../../../../CORN/parameters/parameter.cpp \
    ../../../../../CORN/measure/unitconv.cpp \
    ../../../../source/static_phrases.cpp \
    ../../../../source/soil/sublayers.cpp \
    ../../../../../common/soil/txtrhydr.cpp \
    ../../../../../CORN/validate/validtyp.cpp \
    ../../../../../CORN/math/statistical/stats.cpp \
    ../../../../../CS_suite/simulation/CS_variable_recorder.cpp \
    ../../../time/BAO_date.cpp \
    ../../../../../CORN/math/statistical/statistics_types.cpp \
    ../../../util/cout_mp.cpp \
    ../../../util/simulationdefineconstantsclass.cpp \
    ../../../soil/clssoil.cpp \
    ../../../soil/soilchemicaltransportclass.cpp \
    ../../../control/debugstateclass.cpp \
    ../../../../source/soil/soil_properties_sublayers.cpp \
    ../../../../../common/weather/parameter/WP_precipitation.cpp \
    ../../../../../common/weather/parameter/weather_parameter.cpp \
    ../../../../../CORN/datetime/date_format.cpp \
    ../../../../../CORN/datetime/date.cpp \
    ../../../../../CORN/datetime/date_translator.cpp \
    ../../../weather/weatherstatedailyclass.cpp \
    ../../../weather/weatherstateclass.cpp \
    ../../../weather/weathersingleyearhourlyclass.cpp \
    ../../../weather/weathersingleyearclass.cpp \
    ../../../weather/weatherreadfilesclass.cpp \
    ../../../weather/weatherpmetclass.cpp \
    ../../../weather/weatherlocationinputclass.cpp \
    ../../../snow/clssnow.cpp \
    ../../../output/outputmainclass.cpp \
    ../../../output/outputhourclass.cpp \
    ../../../output/outputgrowthseasonclass.cpp \
    ../../../output/outputgrowthclass.cpp \
    ../../../output/outputdailysoilclass.cpp \
    ../../../output/outputannualclass.cpp \
    ../../../../source/soil/profile_texture.cpp \
    ../../../../source/soil/surface_infiltration_green_ampt.cpp \
    ../../../../source/pond.cpp \
    ../../../../source/soil/runoff.cpp \
    ../../../../source/soil/infiltration_cascade_hourly.cpp \
    ../../../../source/soil/infiltration_cascade_common.cpp \
    ../../../../source/soil/infiltration.cpp


HEADERS += \
    ../../../util/constants.h \
    ../../../util/pubtools.h \
    ../../../time/timestateclass.h \
    ../../../soil/soilprofileclass2.h \
    ../../../basin/basinclass.h \
    ../../../basin/basincellclass.h \
    ../../../control/allcontrolclass.h \
    ../../../time/date.h \
    ../../../soil/soilprocessesclass.h \
    ../../../soil/soilstateclass.h \
    ../../../util/esrigridclass.h \
    ../../../control/globalvariable.h \
    ../../../util/cout_mp.h \
    ../../../util/simulationdefineconstantsclass.h \
    ../../../soil/clssoil.h \
    ../../../soil/soilchemicaltransportclass.h \
    ../../../control/debugstateclass.h \
    ../../../../source/soil/infiltration.h

OTHER_FILES += \
    ../../../../../CORN/OS/ESCSEQ.CPP




