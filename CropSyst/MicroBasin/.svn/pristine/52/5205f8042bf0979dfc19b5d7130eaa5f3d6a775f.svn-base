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
            ../../../../../CORN \
            ../../../../../../../../dev


DEFINES += USE_OS_FS CS_VERSION=5 \
        MICROBASIN_VERSION LIU_DEBUG USE_WEATHER_PROVIDER_V5 \
        MBVB_HYDROLOGY MBVB_SOIL_PROPERTIES CHEMICAL_TRANSPORT xMBVB_INFILTRATION MBVB_FD\
        xLIU_FD_RICHARD CHECK_MASS_BALANCE \
        CORN_DATE \
        CROPSYST_SOIL \
        xTRIVIAL_TEST \
        xCROPSYST_VERSION=5

contains(DEFINES,"CORN_DATE"){
    message("CORN_Date defined")
    DEFINES += MB_Date=CORN::Date
} else {
    message("BAO_Date defined")
    DEFINES += MB_Date=BAO::Date
}

#Destruct_Monitor
#HOURLY_MET

TEMPLATE = app


SOURCES += ../../../main.cpp \
    ../../../weather/weatherstateclass.cpp \
    ../../../util/pubtools.cpp \
    ../../../weather/weathersingleyearclass.cpp \
    ../../../util/constants.cpp \
    ../../../weather/weatherlocationinputclass.cpp \
    ../../../weather/weatherreadfilesclass.cpp \
    ../../../weather/weatherpmetclass.cpp \
    ../../../time/timestateclass.cpp \
    ../../../basin/basinclass.cpp \
    ../../../basin/basincellclass.cpp \
    ../../../control/allcontrolclass.cpp \
    ../../../soil/soilprocessesclass.cpp \
    ../../../soil/soilstateclass.cpp \
    ../../../util/esrigridclass.cpp \
    ../../../control/globalvariable.cpp \
    ../../../soil/soilprofileclass2.cpp \
    ../../../time/BAO_date.cpp \
    ../../../weather/weathersingleyearhourlyclass.cpp \
    ../../../util/cout_mp.cpp \
    ../../../weather/weatherstatedailyclass.cpp \
    ../../../crop/clscrop.cpp \
    ../../../snow/clssnow.cpp \
    ../../../control/clssimulation.cpp \
    ../../../control/simulationrotationclass.cpp \
    ../../../crop/cropstateclass.cpp \
    ../../../util/simulationdefineconstantsclass.cpp \
    ../../../output/outputmainclass.cpp \
    ../../../control/simulationbalanceclass.cpp \
    ../../../crop/cropinputclass.cpp \
    ../../../crop/cropbiomassclass.cpp \
    ../../../crop/cropcanopygrowthclass.cpp \
    ../../../crop/cropdevelopmentclass.cpp \
    ../../../crop/croppotentialtranspirationclass.cpp \
    ../../../crop/croppotsoluteuptakeclass.cpp \
    ../../../soil/clssoil.cpp \
    ../../../soil/soiltemperatureclass.cpp \
    ../../../management/manageeventstateclass.cpp \
    ../../../management/managescheduleclass.cpp \
    ../../../management/clsmanagement.cpp \
    ../../../organicresidual/organicresiduestateclass.cpp \
    ../../../organicresidual/organicresidueclass.cpp \
    ../../../organicresidual/organicresiduepoolclass.cpp \
    ../../../organicresidual/soilomandresiduemasterclass.cpp \
    ../../../soil/soilorganiccarbonclass.cpp \
    ../../../soil/soilnitrogentransformationclass.cpp \
    ../../../soil/soilabioticfunctionsclass.cpp \
    ../../../soil/soilchemicaltransportclass.cpp \
    ../../../control/debugstateclass.cpp \
    ../../../crop/croprootclass.cpp \
    ../../../crop/cropwateruptakeclass.cpp \
    ../../../crop/cropactualnitrogenuptakeclass.cpp \
    ../../../parameters/cropresidueparameterclass.cpp \
    ../../../parameters/manureparameterclass.cpp \
    ../../../parameters/organicresidueparameterclass.cpp \
    ../../../crop/cropparametercollection.cpp \
    ../../../output/outputdailysoilclass.cpp \
    ../../../output/outputgrowthclass.cpp \
    ../../../output/outputgrowthseasonclass.cpp \
    ../../../output/outputhourclass.cpp \
    ../../../output/outputannualclass.cpp


contains(DEFINES,"CORN_DATE"){
    message("Configureing source files for CORN date...")
    SOURCES += ../../../../../CORN/datetime/temporal_base.cpp \
    ../../../../../CORN/datetime/date_format.cpp \
    ../../../../../CORN/datetime/date.cpp \
    ../../../../../CORN/datetime/date_translator.cpp
}

contains(DEFINES,"CROPSYST_SOIL"){
    message("Configureing source files for CROPSYST_SOIL...")
    SOURCES += ../../../../../CORN/container/unilist.cpp \
    ../../../../../CORN/container/text_list.cpp \
    ../../../../../CORN/container/item.cpp \
    ../../../../../CORN/container/enumlist.cpp \
    ../../../../../CORN/container/container.cpp \
    ../../../../../CORN/container/bilist.cpp \
    ../../../../../CORN/container/association.cpp \
    ../../../../../CORN/data_source/vv_file.cpp \
    ../../../../../CORN/data_source/vv_entry.cpp \
    ../../../../../CORN/data_source/vv_datasrc.cpp \
    ../../../../../CORN/data_source/datasrc.cpp \
    ../../../../../CORN/data_source/datarec.cpp \
    ../../../../source/soil/surface_infiltration_green_ampt.cpp \
    ../../../../source/soil/sublayers.cpp \
    ../../../../source/soil/soil_properties_sublayers.cpp \
    ../../../../source/soil/soil_param_V5.cpp \
    ../../../../source/soil/soil_param_struct.cpp \
    ../../../../source/soil/soil_param_class.cpp \
    ../../../../source/soil/soil_interface.cpp \
    ../../../../source/soil/runoff.cpp \
    ../../../../source/soil/profile_texture.cpp \
    ../../../../source/soil/layers.cpp \
    ../../../../source/soil/infiltration_cascade_hourly.cpp \
    ../../../../source/soil/infiltration_cascade_common.cpp \
    ../../../../source/soil/infiltration.cpp \
    ../../../../source/soil/hydrology.cpp \
    ../../../../source/soil/hydraulic_properties.cpp \
    ../../../../../CS_suite/simulation/CS_variable_recorder.cpp \
    ../../../../../USDA/NRCS/soil/survey/domains.cpp \
    ../../../../../common/physics/property.cpp \
    ../../../../../common/physics/mass_common.cpp \
    ../../../../../common/physics/mass.cpp \
    ../../../../../common/soil/txtrhydr.cpp \
    ../../../../../common/soil/layering.cpp \
    ../../../../../common/soil/SCS/SCS.cpp \
    ../../../../../common/weather/parameter/WP_precipitation.cpp \
    ../../../../../common/weather/parameter/weather_parameter.cpp \
    ../../../../source/static_phrases.cpp \
    ../../../../source/pond.cpp \
    ../../../../../CORN/math/statistical/stats.cpp \
    ../../../../../CORN/math/statistical/statistics_types.cpp \
    ../../../../../CORN/measure/unitconv.cpp \
    ../../../../../CORN/measure/measures.cpp \
    ../../../../../CORN/metrology/units_symbology.cpp \
    ../../../../../CORN/metrology/units_clad.cpp \
    ../../../../../CORN/metrology/timestep.cpp \
    ../../../../../CORN/parameters/parameters_datarec.cpp \
    ../../../../../CORN/parameters/parameters.cpp \
    ../../../../../CORN/parameters/parameter.cpp \
    ../../../../../CORN/string/strconv.cpp \
    ../../../../../CORN/validate/validtyp.cpp \
    ../../../../../CORN/quality.cpp \
    ../../../../../CORN/labeled_enum.cpp
}


HEADERS += \
    ../../../weather/weatherstateclass.h \
    ../../../weather/weathersingleyearclass.h \
    ../../../util/constants.h \
    ../../../util/pubtools.h \
    ../../../weather/weatherlocationinputclass.h \
    ../../../weather/weatherreadfilesclass.h \
    ../../../weather/weatherpmetclass.h \
    ../../../time/timestateclass.h \
    ../../../soil/soilprofileclass2.h \
    ../../../basin/basinclass.h \
    ../../../basin/basincellclass.h \
    ../../../control/allcontrolclass.h \
    ../../../time/BAO_date.h \
    ../../../soil/soilprocessesclass.h \
    ../../../soil/soilstateclass.h \
    ../../../util/esrigridclass.h \
    ../../../control/globalvariable.h \
    ../../../weather/weathersingleyearhourlyclass.h \
    ../../../util/cout_mp.h \
    ../../../weather/weatherstatedailyclass.h \
    ../../../crop/clscrop.h \
    ../../../snow/clssnow.h \
    ../../../control/clssimulation.h \
    ../../../control/simulationrotationclass.h \
    ../../../crop/cropstateclass.h \
    ../../../util/simulationdefineconstantsclass.h \
    ../../../output/outputmainclass.h \
    ../../../control/simulationbalanceclass.h \
    ../../../crop/cropinputclass.h \
    ../../../crop/cropbiomassclass.h \
    ../../../crop/cropcanopygrowthclass.h \
    ../../../crop/cropdevelopmentclass.h \
    ../../../crop/croppotentialtranspirationclass.h \
    ../../../crop/croppotsoluteuptakeclass.h \
    ../../../soil/clssoil.h \
    ../../../soil/soiltemperatureclass.h \
    ../../../management/manageeventstateclass.h \
    ../../../management/managescheduleclass.h \
    ../../../management/clsmanagement.h \
    ../../../organicresidual/organicresiduestateclass.h \
    ../../../organicresidual/organicresidueclass.h \
    ../../../organicresidual/organicresiduepoolclass.h \
    ../../../organicresidual/soilomandresiduemasterclass.h \
    ../../../soil/soilorganiccarbonclass.h \
    ../../../soil/soilnitrogentransformationclass.h \
    ../../../soil/soilabioticfunctionsclass.h \
    ../../../soil/soilchemicaltransportclass.h \
    ../../../control/debugstateclass.h \
    ../../../crop/croprootclass.h \
    ../../../crop/cropwateruptakeclass.h \
    ../../../crop/cropactualnitrogenuptakeclass.h \
    ../../../parameters/cropresidueparameterclass.h \
    ../../../parameters/manureparameterclass.h \
    ../../../parameters/organicresidueparameterclass.h \
    ../../../crop/cropparametercollection.h \
    ../../../output/outputdailysoilclass.h \
    ../../../output/outputgrowthclass.h \
    ../../../output/outputgrowthseasonclass.h \
    ../../../output/outputhourclass.h \
    ../../../output/outputannualclass.h

contains(DEFINES,"CORN_DATE"){
    message("Configureing head files for CORN date...")
    HEADERS +=  ../../../../../CORN/datetime/date.hpp
}

#OTHER_FILES += \
#    ../../../../../CORN/OS/ESCSEQ.CPP





