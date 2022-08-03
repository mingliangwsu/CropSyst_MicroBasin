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

QMAKE_CXXFLAGS += -fpermissive -Wno-unused-parameter -Wno-reorder -Wno-used-but-set-parameter -Wno-unused-but-set-variable -g
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


DEFINES += CS_VERSION=5 \
        CROPSYST_VERSION=5 MICROBASIN_VERSION WEATHER_PROVIDER_VERSION=5 \
        MBVB_HYDROLOGY CHEMICAL_TRANSPORT MBVB_INFILTRATION \
        CROPSYST_FD \
        CS_REPORTER_VERSION SOIL_TEMPERATURE MBVB_SOIL_PROPERTIES HOURLY_BASIN_OUTPUT REPEAT_MANAGEMENT\
        VBBASIN_STRUCTURE \
        FROZEN_SOIL VB_SAME_CSV_OUTPUT

#LML 140902 FROZEN_SOIL will be undefined after the freezing class same as CropSyst is implemented

#Destruct_Monitor
#HOURLY_MET

TEMPLATE = app


SOURCES += ../../../main.cpp \
    ../../../util/pubtools.cpp \
    ../../../util/constants.cpp \
    ../../../weather/weatherlocationinputclass.cpp \
    ../../../basin/basinclass.cpp \
    ../../../basin/basincellclass.cpp \
    ../../../control/allcontrolclass.cpp \
    ../../../soil/soilprocessesclass.cpp \
    ../../../soil/soilstateclass.cpp \
    ../../../util/esrigridclass.cpp \
    ../../../soil/soilprofileclass2.cpp \
    ../../../weather/weathersingleyearhourlyclass.cpp \
    ../../../weather/weatherstatedailyclass.cpp \
    ../../../snow/clssnow.cpp \
    ../../../util/simulationdefineconstantsclass.cpp \
    ../../../output/outputmainclass.cpp \
    ../../../control/simulationbalanceclass.cpp \
    ../../../soil/clssoil.cpp \
    ../../../soil/soiltemperatureclass.cpp \
    ../../../soil/soilabioticfunctionsclass.cpp \
    ../../../soil/soilchemicaltransportclass.cpp \
    ../../../control/debugstateclass.cpp \
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
    ../../../../../USDA/NRCS/soil/survey/domains.cpp \
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
    ../../../../../corn/measure/units_enum.cpp \
    ../../../../../corn/parameters/number_keyed.cpp \
    ../../../../../corn/datetime/temporal_base.cpp \
    ../../../../../corn/datetime/date_format.cpp \
    ../../../../../corn/datetime/date_translator.cpp \
    ../../../../../corn/datetime/date.cpp \
    ../../../../../corn/datetime/time.cpp \
    ../../../../../corn/datetime/datetime64.cpp \
    ../../../../../corn/measure/common_units.cpp \
    ../../../../../UED/library/UED_fname.cpp \
    ../../../../../corn/math/numerical/interpolate.cpp \
    ../../../../../common/biometeorology/ET_reference.cpp \
    ../../../control/balanceitem.cpp \
    ../../../control/globalvariable.cpp \
    ../../../../../UED/convert/ED_tabular_format.cpp \
    ../../../../../common/weather/seasons.cpp


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
    ../../../../../corn/datetime/date.hpp \
    ../../../../../UED/convert/ED_tabular_format.h \
    ../../../../../common/weather/seasons.h



unix:!macx: LIBS += -L$$PWD/../../../../../corn/build/Qt/Linux_gcc/Release/ -lcorn_complete_static

INCLUDEPATH += $$PWD/../../../../../corn/build/Qt/Linux_gcc/Release
DEPENDPATH += $$PWD/../../../../../corn/build/Qt/Linux_gcc/Release

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../corn/build/Qt/Linux_gcc/Release/libcorn_complete_static.a

unix:!macx: LIBS += -L$$PWD/../../../../../CS_suite/build/Qt/CS_suite_static/Release/ -lCS_suite_static

INCLUDEPATH += $$PWD/../../../../../CS_suite/build/Qt/CS_suite_static/Release
DEPENDPATH += $$PWD/../../../../../CS_suite/build/Qt/CS_suite_static/Release

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../CS_suite/build/Qt/CS_suite_static/Release/libCS_suite_static.a

unix:!macx: LIBS += -L$$PWD/../../../../../UED/library/build/Qt/UED_static/Release/ -lUED_static

INCLUDEPATH += $$PWD/../../../../../UED/library/build/Qt/UED_static/Release
DEPENDPATH += $$PWD/../../../../../UED/library/build/Qt/UED_static/Release

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../UED/library/build/Qt/UED_static/Release/libUED_static.a

unix:!macx: LIBS += -L$$PWD/../../../../../common/weather/build/Qt/Linux_gcc/Release/ -lweather_static

INCLUDEPATH += $$PWD/../../../../../common/weather/build/Qt/Linux_gcc/Release
DEPENDPATH += $$PWD/../../../../../common/weather/build/Qt/Linux_gcc/Release

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../common/weather/build/Qt/Linux_gcc/Release/libweather_static.a

unix:!macx: LIBS += -L$$PWD/../../../../source/build/Qt/Linux_gcc/Release_MicroBasin/ -lCropSyst_elements_V5_for_MicroBasin

INCLUDEPATH += $$PWD/../../../../source/build/Qt/Linux_gcc/Release_MicroBasin
DEPENDPATH += $$PWD/../../../../source/build/Qt/Linux_gcc/Release_MicroBasin

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../source/build/Qt/Linux_gcc/Release_MicroBasin/libCropSyst_elements_V5_for_MicroBasin.a

