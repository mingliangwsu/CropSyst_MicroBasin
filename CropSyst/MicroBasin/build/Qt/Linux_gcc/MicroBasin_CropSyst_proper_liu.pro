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
#QMAKE_LFLAGS += -fopenmp -Wl,-Map=testmap.txt
#LIBS += -fopenmp

QMAKE_CXXFLAGS += -fpermissive -w -g
QMAKE_CXXFLAGS += -Wno-reorder -Wno-unused-parameter -Wno-unused-but-set-parameter

#LIBS += -ldl
INCLUDEPATH += ../../../ \
            ../../../../../ \
            ../../../../../common \
            ../../../../source \
            ../../../../../USDA/NRCS \
            ../../../../../corn

#CONFIG += precompile_header
#PRECOMPILED_HEADER = stable.h



DEFINES += CS_VERSION=5 \
        CROPSYST_VERSION=5 \
        MICROBASIN_VERSION \
        CROPSYST_CHEMICAL_TRANSPORT \
        xCROPSYST_WEATHER \
        xCELL_METEOROLOGY \
        MBVB_HYDROLOGY \
        MBVB_INFILTRATION \
        CHEMICAL_TRANSPORT \
        SOIL_TEMPERATURE \
        CROPSYST_FD \
        WEATHER_PROVIDER_VERSION=5 \
        LIU_DEBUG \
        MBVB_SOIL \
        xMBVB_SNOW \
        obs_MBVB_SOIL_TEMPERATURE \
        xCROPSYST_SOILFILE \
        xMBVB_FD \
        xDestruct_Monitor \
        xLIU_FD_RICHARD \
        CHECK_MASS_BALANCE \
        xMSVB_CASCADE_INFILTRATION_HOUR \
        VBBASIN_STRUCTURE \
        FROZEN_SOIL \
        HOURLY_BASIN_OUTPUT \
        xMACA_V1_MBMET \
        xNONE_DRINAGE \
        REPEAT_MANAGEMENT \
        EVENT_SCHEDULER_VERSION=1 \
        xQUICK_xDIRTY_RUN_FOR_DEBUG_MEM_USE \
        VERBOSE \
        xDEBUG_LIU_OUT_CSV \
        VB_SAME_CSV_OUTPUT \
        xCLOSE_CROPSYST_CROP_AND_SOIL_BIOGEOCHEMICAL_PROCESS_FOR_DEBUG \
        xCHECK_OVERLANDFLOW_WATER_AND_NITROGEN_FOR_DEBUG \
        xCHECK_SOIL_LATERALFLOW_WATER_AND_NITROGEN_FOR_DEBUG \
        xCHECK_SOIL_EVAPORATION_FOR_DEBUG \
        xCHECK_HOURLY_CASCADE_FOR_DEBUG \
        xNUMCORES_TO_USE=4 \
        xCELL_METEOROLOGY \
        xNO_INFILTRATION \
        xHARD_CODED_INITIAL_MINERAL_NITROGEN_AND_MOISTURE \
         OLD_PHENOLOGY_SEQUENCER \
        xPREDEFINE_N_APPLICATION_PER_CELL

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
SOURCES += \
../../../main.cpp \
      ../../../util/pubtools.cpp \
      ../../../util/constants.cpp \
      ../../../weather/weatherlocationinputclass.cpp \
      ../../../basin/basinclass.cpp \
      ../../../basin/basincellclass.cpp \
      ../../../control/allcontrolclass.cpp \
      ../../../soil/soilprocessesclass.cpp \
      ../../../soil/soilstateclass.cpp \
      ../../../util/esrigridclass.cpp \
      ../../../control/globalvariable.cpp \
      ../../../soil/soilprofileclass2.cpp \
      ../../../weather/weathersingleyearhourlyclass.cpp \
      ../../../weather/weatherstatedailyclass.cpp \
      ../../../snow/clssnow.cpp \
      ../../../util/simulationdefineconstantsclass.cpp \
      ../../../output/outputmainclass.cpp \
      ../../../soil/clssoil.cpp \
      ../../../soil/soiltemperatureclass.cpp \
      ../../../soil/soilorganiccarbonclass.cpp \
      ../../../soil/soilnitrogentransformationclass.cpp \
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
      ../../../../../common/soil/SCS/SCS.cpp \
      ../../../../source/static_phrases.cpp \
      ../../../../../corn/math/statistical/statistics_types.cpp \
      ../../../../../corn/measure/unitconv.cpp \
      ../../../../../corn/metrology/units_symbology.cpp \
      ../../../../../corn/metrology/timestep.cpp \
      ../../../../../corn/parameters/parameters_datarec.cpp \
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
      ../../../control/balanceitem.cpp \
      ../../../../../corn/parameters/number_keyed.cpp \
      ../../../../../corn/measure/units_enum.cpp \
      ../../../../source/soil/infiltration_cascade_hourly.cpp \
      ../../../../source/soil/infiltration_cascade_common.cpp \
      ../../../../source/soil/surface_infiltration_green_ampt.cpp \
      ../../../../../common/soil/txtrhydr.cpp \
      ../../../../../common/biometeorology/ET_reference.cpp \
      ../../../../../CS_suite/simulation/CS_simulation_element_plugin.cpp \
      ../../../../source/crop/yield.cpp \
      ../../../../../common/geodesy/geocoordinate.cpp \
      ../../../../../common/geodesy/geolocation.cpp \
      ../../../../../UED/convert/ED_tabular_format.cpp \
      ../../../../../corn/application/explaination/explainations.cpp \
      ../../../../../common/biometeorology/parameter/slope_SVP_curve_psychrometric_resistance.cpp \
      ../../../../../corn/parameters/parameters_directory_OS_FS.cpp \
      ../../../../../corn/measure/common_units.cpp \
      ../../../../../common/biometeorology/ET_model.cpp \
      ../../../../../CS_suite/observation/CS_inspector.cpp \
      ../../../../../corn/chronometry/temporal.cpp






unix:!macx: LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/ -lcommon_sim_static

INCLUDEPATH += $$PWD/../../../../../common/simulation/build/Qt/Debug
DEPENDPATH += $$PWD/../../../../../common/simulation/build/Qt/Debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../common/simulation/build/Qt/Debug/libcommon_sim_static.a
