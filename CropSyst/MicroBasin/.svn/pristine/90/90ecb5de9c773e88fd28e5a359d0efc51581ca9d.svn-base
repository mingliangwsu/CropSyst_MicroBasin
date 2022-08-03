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

QMAKE_CXXFLAGS += -fpermissive
#-std=gnu++11
#-std=c++0x

#for gcc
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

LIBS += -fopenmp
INCLUDEPATH += ../../../ \
            ../../../../../ \
            ../../../../../common \
            ../../../../source \
            ../../../../../USDA/NRCS \
            ../../../../../corn \
            ../../../../../../../../dev


DEFINES += USE_OS_FS CS_VERSION=5 \
        MICROBASIN_VERSION LIU_DEBUG USE_WEATHER_PROVIDER_V5 \
        xMBVB_HYDROLOGY MBVB_SOIL_PROPERTIES CHEMICAL_TRANSPORT MBVB_INFILTRATION \
        xMBVB_FD CROPSYST_FD \
        xDestruct_Monitor \
        xLIU_FD_RICHARD \
        CHECK_MASS_BALANCE \
        xMSVB_CASCADE_INFILTRATION_HOUR \
        xCROPSYST_VERSION=5 \
        VBBASIN_STRUCTURE \
        FROZEN_SOIL \
        xHOURLY_BASIN_OUTPUT \
        xCROPSYST_SOILFILE \
        xMACA_V1_MBMET \
        xDAILY_UPDATE_WATERSHED_PROPER \
        xNONE_DRINAGE

#LML 140902 FROZEN_SOIL will be undefined after the freezing class same as CropSyst is implemented

#Destruct_Monitor
#HOURLY_MET

TEMPLATE = app


SOURCES += ../../../main.cpp \
    ../../../util/pubtools.cpp \
    ../../../util/constants.cpp \
    ../../../weather/weatherlocationinputclass.cpp \
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
    ../../../output/outputannualclass.cpp \
    ../../../../source/soil/infiltration.cpp \
    ../../../../source/soil/structure_common.cpp \
    ../../../../source/soil/surface_infiltration_green_ampt.cpp \
    ../../../../source/soil/infiltration_cascade_hourly.cpp \
    ../../../../source/soil/infiltration_cascade_common.cpp \
    ../../../../source/soil/hydrology_cascade.cpp \
    ../../../../source/soil/structure_interface.cpp \
    ../../../../../common/soil/layering.cpp \
    ../../../../../corn/math/statistical/stats.cpp \
    ../../../../../corn/measure/measures.cpp \
    ../../../../source/pond.cpp \
    ../../../../../corn/metrology/units_clad.cpp \
    ../../../../../corn/container/text_list.cpp \
    ../../../../../corn/container/item.cpp \
    ../../../../../corn/container/enumlist.cpp \
    ../../../../../corn/container/container.cpp \
    ../../../../../corn/container/bilist.cpp \
    ../../../../../corn/container/association.cpp \
    ../../../../../corn/data_source/vv_file.cpp \
    ../../../../../corn/data_source/vv_entry.cpp \
    ../../../../../corn/data_source/vv_datasrc.cpp \
    ../../../../../corn/data_source/datasrc.cpp \
    ../../../../../corn/data_source/datarec.cpp \
    ../../../../source/soil/sublayers.cpp \
    ../../../../source/soil/soil_properties_sublayers.cpp \
    ../../../../source/soil/soil_param_V5.cpp \
    ../../../../source/soil/soil_param_struct.cpp \
    ../../../../source/soil/soil_param_class.cpp \
    ../../../../source/soil/soil_interface.cpp \
    ../../../../source/soil/runoff.cpp \
    ../../../../source/soil/profile_texture.cpp \
    ../../../../source/soil/layers.cpp \
    ../../../../source/soil/hydraulic_properties.cpp \
    ../../../../../CS_suite/simulation/CS_variable_recorder.cpp \
    ../../../../../USDA/NRCS/soil/survey/domains.cpp \
    ../../../../../common/physics/property.cpp \
    ../../../../../common/physics/mass_common.cpp \
    ../../../../../common/physics/mass.cpp \
    ../../../../../common/soil/txtrhydr.cpp \
    ../../../../../common/soil/SCS/SCS.cpp \
    ../../../../../common/weather/parameter/WP_precipitation.cpp \
    ../../../../../common/weather/parameter/weather_parameter.cpp \
    ../../../../source/static_phrases.cpp \
    ../../../../../corn/math/statistical/statistics_types.cpp \
    ../../../../../corn/measure/unitconv.cpp \
    ../../../../../corn/metrology/units_symbology.cpp \
    ../../../../../corn/metrology/timestep.cpp \
    ../../../../../corn/parameters/parameters_datarec.cpp \
    ../../../../../corn/parameters/parameters.cpp \
    ../../../../../corn/parameters/parameter.cpp \
    ../../../../../corn/string/strconv.cpp \
    ../../../../../corn/validate/validtyp.cpp \
    ../../../../../corn/quality.cpp \
    ../../../../../corn/container/unilist.cpp \
    ../../../../../corn/labeled_enum.cpp \
    ../../../../source/soil/hydrology.cpp \
    ../../../../source/soil/hydrology_finite_diff.cpp \
    ../../../../source/soil/infiltration_finite_diff.cpp \
    ../../../../source/soil/evaporation_without_vapor_path.cpp \
    ../../../../source/soil/evaporation_abstract.cpp \
    ../../../../../common/physical_parameter.cpp \
    ../../../soil/soilprocessesclass_MBVB_FD.cpp \
    ../../../soil/soilprocessesclass_MBVB_CH.cpp \
    ../../../soil/soilprofileclass2_MBVB_CH.cpp \
    ../../../soil/soilstateclass_MBVB_FD.cpp \
    ../../../control/balanceitem.cpp \
    ../../../../../corn/measure/units_enum.cpp \
    ../../../../../corn/parameters/number_keyed.cpp \
    ../../../../../corn/datetime/temporal_base.cpp \
    ../../../../../corn/datetime/date_format.cpp \
    ../../../../../corn/datetime/date_translator.cpp \
    ../../../../../corn/datetime/date.cpp


#contains(DEFINES,"CROPSYST_SOIL"){
#    message("Configureing source files for CROPSYST_SOIL...")
#    SOURCES += ../../../../../corn/container/unilist.cpp \
#    ../../../../../corn/container/text_list.cpp \
 #   ../../../../../corn/container/item.cpp \
#    ../../../../../corn/container/enumlist.cpp \
#    ../../../../../corn/container/container.cpp \
#    ../../../../../corn/container/bilist.cpp \
#    ../../../../../corn/container/association.cpp \
#    ../../../../../corn/data_source/vv_file.cpp \
#    ../../../../../corn/data_source/vv_entry.cpp \
#    ../../../../../corn/data_source/vv_datasrc.cpp \
#    ../../../../../corn/data_source/datasrc.cpp \
#    ../../../../../corn/data_source/datarec.cpp \
#    ../../../../source/soil/sublayers.cpp \
#    ../../../../source/soil/soil_properties_sublayers.cpp \
#    ../../../../source/soil/soil_param_V5.cpp \
##    ../../../../source/soil/soil_param_struct.cpp \
#    ../../../../source/soil/soil_param_class.cpp \
#    ../../../../source/soil/soil_interface.cpp \
#    ../../../../source/soil/runoff.cpp \
##    ../../../../source/soil/profile_texture.cpp \
#    ../../../../source/soil/layers.cpp \
###    ../../../../source/soil/hydraulic_properties.cpp \
#    ../../../../../CS_suite/simulation/CS_variable_recorder.cpp \
##    ../../../../../USDA/NRCS/soil/survey/domains.cpp \
#    ../../../../../common/physics/property.cpp \
#    ../../../../../common/physics/mass_common.cpp \
#    ../../../../../common/physics/mass.cpp \
#    ../../../../../common/soil/txtrhydr.cpp \
#    ../../../../../common/soil/SCS/SCS.cpp \
#    ../../../../../common/weather/parameter/WP_precipitation.cpp \
###    ../../../../../common/weather/parameter/weather_parameter.cpp \
#    ../../../../source/static_phrases.cpp \
#    ../../../../../corn/math/statistical/statistics_types.cpp \
#    ../../../../../corn/measure/unitconv.cpp \
##    ../../../../../corn/metrology/units_symbology.cpp \
#    ../../../../../corn/metrology/timestep.cpp \
#    ../../../../../corn/parameters/parameters_datarec.cpp \
#    ../../../../../corn/parameters/parameters.cpp \
#    ../../../../../corn/parameters/parameter.cpp \
#    ../../../../../corn/string/strconv.cpp \
#    ../../../../../corn/validate/validtyp.cpp \
#    ../../../../../corn/quality.cpp \
#    ../../../../../corn/labeled_enum.cpp
#}


HEADERS += \
    ../../../util/constants.h \
    ../../../util/pubtools.h \
    ../../../weather/weatherlocationinputclass.h \
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
    ../../../output/outputannualclass.h \
    ../../../../../corn/datetime/date.h \
    ../../../../../common/parameter.h \
    ../../../../source/soil/hydrology_interface.h \
    ../../../../source/soil/infiltration.h \
    ../../../control/balanceitem.h \
    ../../../../../corn/datetime/date.hpp







