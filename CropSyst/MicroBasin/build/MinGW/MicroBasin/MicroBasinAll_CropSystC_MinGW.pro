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
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS += -fpermissive

LIBS += -fopenmp
INCLUDEPATH += ../../../ \
            ../../../../../ \
            ../../../../../common \
            ../../../../source \
            ../../../../../USDA/NRCS \
            ../../../../../CORN \
            ../../../../../../../../dev

CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h



DEFINES += USE_OS_FS CS_VERSION=5 \
        MICROBASIN_VERSION LIU_DEBUG USE_WEATHER_PROVIDER_V5 \
        xMBVB_HYDROLOGY MBVB_SOIL_PROPERTIES CHEMICAL_TRANSPORT MBVB_INFILTRATION \
        xMBVB_FD CROPSYST_FD \
        xDestruct_Monitor \
        xLIU_FD_RICHARD \
        CHECK_MASS_BALANCE \
        xCORN_DATE \
        xMSVB_CASCADE_INFILTRATION_HOUR \
        xCROPSYST_VERSION=5 \
        VBBASIN_STRUCTURE \
        FROZEN_SOIL \
        HOURLY_BASIN_OUTPUT \
        xCROPSYST_SOILFILE \
        xMACA_V1_MBMET \
        xNONE_DRINAGE \
        xREPEAT_MANAGEMENT \
        xQUICK_DIRTY_RUN_FOR_DEBUG_MEM_USE
        #MB_Date=CORN::Date
#LML 140902 FROZEN_SOIL will be undefined after the freezing class same as CropSyst is implemented
#contains(DEFINES,"CORN_DATE"){
#    message("CORN_Date defined")
#    DEFINES += MB_Date=CORN::Date
#} else {
#    message("BAO_Date defined")
#    DEFINES += MB_Date=BAO::Date
#}
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
    ../../../../source/soil/hydrology_cascade.cpp \
    ../../../../source/soil/structure_interface.cpp \
    ../../../../../common/soil/layering.cpp \
    ../../../../../CORN/math/statistical/stats.cpp \
    ../../../../../CORN/measure/measures.cpp \
    ../../../../source/pond.cpp \
    ../../../../../CORN/metrology/units_clad.cpp \
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
    #../../../../../common/physics/property.cpp \
    #../../../../../common/physics/mass_common.cpp \
    #../../../../../common/physics/mass.cpp \
    #../../../../../common/soil/txtrhydr.cpp \
    ../../../../../common/soil/SCS/SCS.cpp \
    #../../../../../common/weather/parameter/WP_precipitation.cpp \
    #../../../../../common/weather/parameter/weather_parameter.cpp \
    ../../../../source/static_phrases.cpp \
    ../../../../../CORN/math/statistical/statistics_types.cpp \
    ../../../../../CORN/measure/unitconv.cpp \
    ../../../../../CORN/metrology/units_symbology.cpp \
    ../../../../../CORN/metrology/timestep.cpp \
    ../../../../../CORN/parameters/parameters_datarec.cpp \
    ../../../../../CORN/parameters/parameters.cpp \
    ../../../../../CORN/parameters/parameter.cpp \
    ../../../../../CORN/string/strconv.cpp \
    ../../../../../CORN/validate/validtyp.cpp \
    ../../../../../CORN/quality.cpp \
    ../../../../../CORN/container/unilist.cpp \
    ../../../../../CORN/labeled_enum.cpp \
    ../../../../source/soil/hydrology.cpp \
    ../../../../source/soil/hydrology_finite_diff.cpp \
    ../../../../source/soil/infiltration_finite_diff.cpp \
    ../../../../source/soil/evaporation_without_vapor_path.cpp \
    ../../../../source/soil/evaporation_abstract.cpp \
    #../../../../../common/physical_parameter.cpp \
    ../../../soil/soilprocessesclass_MBVB_FD.cpp \
    ../../../soil/soilprocessesclass_MBVB_CH.cpp \
    ../../../soil/soilprofileclass2_MBVB_CH.cpp \
    ../../../soil/soilstateclass_MBVB_FD.cpp \
    ../../../control/balanceitem.cpp \
    ../../../../../CORN/parameters/number_keyed.cpp \
    ../../../../../CORN/measure/units_enum.cpp \
    ../../../../source/soil/infiltration_cascade_hourly.cpp \
    ../../../../source/soil/infiltration_cascade_common.cpp \
    ../../../../source/soil/surface_infiltration_green_ampt.cpp \
    ../../../../../CORN/datetime/temporal_base.cpp \
    ../../../../../CORN/datetime/date_format.cpp \
    ../../../../../CORN/datetime/date_translator.cpp \
    ../../../../../CORN/datetime/date.cpp

HEADERS += \
    stable.h \
    ../../../control/allcontrolclass.h \
    ../../../control/balanceitem.h \
    ../../../control/clssimulation.h \
    ../../../control/debugstateclass.h \
    ../../../control/globalvariable.h \
    ../../../control/simulationbalanceclass.h \
    ../../../control/simulationrotationclass.h \
    ../../../basin/basincellclass.h \
    ../../../basin/basinclass.h \
    ../../../crop/clscrop.h \
    ../../../crop/cropactualnitrogenuptakeclass.h \
    ../../../crop/cropbiomassclass.h \
    ../../../crop/cropcanopygrowthclass.h \
    ../../../crop/cropdevelopmentclass.h \
    ../../../crop/cropinputclass.h \
    ../../../crop/cropparametercollection.h \
    ../../../crop/croppotentialtranspirationclass.h \
    ../../../crop/croppotsoluteuptakeclass.h \
    ../../../crop/croprootclass.h \
    ../../../crop/cropstateclass.h \
    ../../../crop/cropwateruptakeclass.h \
    ../../../management/clsmanagement.h \
    ../../../management/manageeventstateclass.h \
    ../../../management/managescheduleclass.h \
    ../../../organicresidual/organicresidueclass.h \
    ../../../organicresidual/organicresiduepoolclass.h \
    ../../../organicresidual/organicresiduestateclass.h \
    ../../../organicresidual/soilomandresiduemasterclass.h \
    ../../../output/outputannualclass.h \
    ../../../output/outputdailysoilclass.h \
    ../../../output/outputgrowthclass.h \
    ../../../output/outputgrowthseasonclass.h \
    ../../../output/outputhourclass.h \
    ../../../output/outputmainclass.h \
    ../../../parameters/cropresidueparameterclass.h \
    ../../../parameters/manureparameterclass.h \
    ../../../parameters/organicresidueparameterclass.h \
    ../../../snow/clssnow.h \
    ../../../soil/clssoil.h \
    ../../../soil/complete.h \
    ../../../soil/soilabioticfunctionsclass.h \
    ../../../soil/soilchemicaltransportclass.h \
    ../../../soil/soilnitrogentransformationclass.h \
    ../../../soil/soilorganiccarbonclass.h \
    ../../../soil/soilprocessesclass.h \
    ../../../soil/soilprofileclass2.h \
    ../../../soil/soilstateclass.h \
    ../../../soil/soiltemperatureclass.h \
    ../../../time/timestateclass.h \
    ../../../util/constants.h \
    ../../../util/cout_mp.h \
    ../../../util/esrigridclass.h \
    ../../../util/pubtools.h \
    ../../../util/simulationdefineconstantsclass.h \
    ../../../weather/weatherlocationinputclass.h \
    ../../../weather/weatherpmetclass.h \
    ../../../weather/weatherreadfilesclass.h \
    ../../../weather/weathersingleyearclass.h \
    ../../../weather/weathersingleyearhourlyclass.h \
    ../../../weather/weatherstateclass.h \
    ../../../weather/weatherstatedailyclass.h




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/release/ -lcommon_sim_static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/debug/ -lcommon_sim_static
else:unix: LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/ -lcommon_sim_static

INCLUDEPATH += $$PWD/../../../../../common/simulation/build/Qt/Debug/debug
DEPENDPATH += $$PWD/../../../../../common/simulation/build/Qt/Debug/debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../common/weather/build/Qt/Debug/release/ -lweather_static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../common/weather/build/Qt/Debug/debug/ -lweather_static
else:unix: LIBS += -L$$PWD/../../../../../common/weather/build/Qt/Debug/ -lweather_static

INCLUDEPATH += $$PWD/../../../../../common/weather/build/Qt/Debug/debug
DEPENDPATH += $$PWD/../../../../../common/weather/build/Qt/Debug/debug
