#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T17:26:15
#
#-------------------------------------------------

QT       -= core gui

TARGET = CropSyst_V5_elements
TEMPLATE = lib

QMAKE_CXXFLAGS += -Wno-reorder -Wno-unused-parameter -Wno-unused-but-set-parameter
QMAKE_CXXFLAGS += -fpermissive  -w -g
DEFINES += \
    CROPSYST_ON CS_VERSION_NUMBERS="5,0,0" \
    CROPSYST_MAX_DESCRIPTION_LENGTH=128 CROPSYST_VV_BOOL_FORM=CORN::VV_bool_entry::form_true \
    Normal_crop_growth_stage=Normal_crop_event_sequence \
    USE_STD_STRING \
    LIU_DEBUG \
    CS_VERSION=5 \
    VIC_CROPSYST_VERSION=3 \
    CROPSYST_VERSION=5 \
    WEATHER_PROVIDER_VERSION=5 \
    USE_WEATHER_PROVIDER

INCLUDEPATH += ../../../../../ \
               ../../../../ \
               ../../../../../crop \
               ../../../../../../ \
               ../../../../../../common \
               ../../../../../../corn \
               ../../../../../../CropSyst \
               ../../../../../../CropSyst/source \
               ../../../../../../USDA/NRCS

SOURCES += \
                ../../../../../../CropSyst/source/static_phrases.cpp \
                ../../../../../../CropSyst/source/crop/growth_stages.cpp \
                ../../../../../../CropSyst/source/crop/crop_param_class.cpp \
                ../../../../../../CropSyst/source/crop/crop_param_struct.cpp \
                ../../../../../../CropSyst/source/crop/crop_param_V5.cpp \
                ../../../../../../CropSyst/source/crop/CO2_response.cpp \
                ../../../../../../CropSyst/source/crop/phenology_interface.cpp \
                ../../../../../../CropSyst/source/crop/canopy_cover_continuum.cpp \
                ../../../../../../CropSyst/source/crop/canopy_cover_curve.cpp \
                ../../../../../../CropSyst/source/crop/crop_types.cpp \
                ../../../../../../CropSyst/source/crop/crop_cropsyst.cpp \
                ../../../../../../CropSyst/source/crop/crop_common.cpp \
                ../../../../../../CropSyst/source/crop/crop_thermal_time.cpp \
                ../../../../../../CropSyst/source/crop/crop_inactive_period.cpp \
                ../../../../../../CropSyst/source/crop/canopy_growth_cover_based.cpp \
                ../../../../../../CropSyst/source/crop/transpiration_dependent_growth.cpp \
                ../../../../../../CropSyst/source/crop/canopy_growth_portioned.cpp \
                ../../../../../../CropSyst/source/crop/phenology_sequencer.cpp \
                ../../../../../../CropSyst/source/crop/crop_n.cpp \
                ../../../../../../CropSyst/source/crop/phenology_common.cpp \
                ../../../../../../CropSyst/source/crop/crop_transpiration_2.cpp \
                ../../../../../../CropSyst/source/crop/crop_root.cpp \
                ../../../../../../CropSyst/source/crop/crop_root_V5.cpp \
                ../../../../../../CropSyst/source/cs_vars.cpp \
                ../../../../../../CropSyst/source/mgmt_types.cpp \
                ../../../../../../CropSyst/source/management/management_param_struct.cpp \
                ../../../../../../CropSyst/source/management/management_param_class.cpp \
                ../../../../../../CropSyst/source/unstressed_growth.cpp \
                ../../../../../../CropSyst/source/soil/soil_interface.cpp \
                ../../../../../../CropSyst/source/organic_matter/OM_common.cpp \
                ../../../../../../CropSyst/source/organic_matter/OM_pools_common.cpp \
                ../../../../../../CropSyst/source/land_unit_sim.cpp \
                ../../../../../../CropSyst/source/crop/canopy_growth_LAI_based_V5.cpp \
                ../../../../../../CropSyst/source/cs_vars_abbrv.cpp \
                ../../../../../../CropSyst/source/management/management_param_V5.cpp \
                ../../../../../../CropSyst/source/N_sources.cpp \
                ../../../../../../CropSyst/source/cs_operation.cpp \
                ../../../../../../CropSyst/source/cs_operation_codes.cpp \
                ../../../../../../CropSyst/source/soil/abiotic_environment.cpp \
                ../../../../../../CropSyst/source/soil/disturbance.cpp \
                ../../../../../../CropSyst/source/friction_velocity.cpp \
                ../../../../../../CropSyst/source/pond.cpp \
                ../../../../../../CropSyst/source/rot_param.cpp \
                ../../../../../../CropSyst/source/cs_ET.cpp \
                ../../../../../../CropSyst/source/organic_matter/multiple_pool/OM_multiple_pool.cpp \
                ../../../../../../CropSyst/source/soil.cpp \
                ../../../../../../CropSyst/source/soil/tillage_effect.cpp \
                ../../../../../../CropSyst/source/soil/soil_base.cpp \
                ../../../../../../CropSyst/source/soil/chemicals_profile.cpp \
                ../../../../../../CropSyst/source/seeding_param.cpp \
                ../../../../../../CropSyst/source/soil/layers.cpp \
                ../../../../../../CropSyst/source/soil/sublayers.cpp \
                ../../../../../../CropSyst/source/soil/hydraulic_properties.cpp \
                ../../../../../../CropSyst/source/soil/structure_common.cpp \
                ../../../../../../CropSyst/source/soil/structure_interface.cpp \
                ../../../../../../CropSyst/source/soil/soil_param.cpp \
                ../../../../../../CropSyst/source/soil/soil_param_class.cpp \
                ../../../../../../CropSyst/source/soil/temperature_hourly.cpp \
                ../../../../../../CropSyst/source/soil/temperature_functions.cpp \
                ../../../../../../CropSyst/source/soil/nitrogen_common.cpp \
                ../../../../../../CropSyst/source/organic_matter/multiple_pool/OM_pools_multiple.cpp \
                ../../../../../../CropSyst/source/organic_matter/OM_residues_profile_common.cpp \
                ../../../../../../CropSyst/source/organic_matter/single_pool/OM_pools_single.cpp \
                ../../../../../../CropSyst/source/cs_event.cpp \
                ../../../../../../CropSyst/source/soil/temperature_profile.cpp \
                ../../../../../../CropSyst/source/cs_accum.cpp \
                #../../../../../../CropSyst/source/soil/infiltration_finite_diff.cpp \
                ../../../../../../CropSyst/source/perform_op.cpp \
                ../../../../../../CropSyst/source/cs_mgmt.cpp \
                ../../../../../../CropSyst/source/soil/profile_texture.cpp \
                ../../../../../../CropSyst/source/soil/nitrogen_profile.cpp \
                ../../../../../../CropSyst/source/soil/chemical_profile.cpp \
                ../../../../../../CropSyst/source/soil/soil_param_V5.cpp \
                ../../../../../../CropSyst/source/soil/hydrology.cpp \
                #../../../../../../CropSyst/source/soil/infiltration_cascade_common.cpp \
                #../../../../../../CropSyst/source/soil/infiltration.cpp \
                #../../../../../../CropSyst/source/soil/surface_infiltration_green_ampt.cpp \
                ../../../../../../CropSyst/source/organic_matter/OM_residues_profile_abstract.cpp \
                ../../../../../../CropSyst/source/organic_matter/single_pool/OM_single_pool.cpp \
                ../../../../../../CropSyst/source/soil/surface_temperature.cpp \
                ../../../../../../CropSyst/source/crop/crop_orchard_Kemanian_Stockle.cpp \
                ../../../../../../CropSyst/source/crop/crop_interfaced_cropsyst.cpp \
                ../../../../../../CropSyst/source/inorganic_NH4.cpp \
                ../../../../../../CropSyst/source/crop/crop_orchard_common.cpp \
                ../../../../../../CropSyst/source/crop/crop_interfaced.cpp \
                ../../../../../../CropSyst/source/soil/chemical_balance.cpp \
                ../../../../../../CropSyst/source/soil/chemical_mass_profile.cpp \
                ../../../../../../CropSyst/source/crop/crop_orchard_Oyarzun_Stockle.cpp \
                #../../../../../../CropSyst/source/soil/evaporation_without_vapor_path.cpp \
                #../../../../../../CropSyst/source/soil/evaporation_abstract.cpp \
                ../../../../../../CropSyst/source/cs_events.cpp \
                ../../../../../../CropSyst/source/crop/crop_biomass.cpp \
                ../../../../../../CropSyst/source/crop/canopy_growth.cpp \
                ../../../../../../CropSyst/source/crop/extreme_temperature_response.cpp \
                ../../../../../../CropSyst/source/cs_scenario.cpp \
                ../../../../../../CropSyst/source/model_options.cpp \
                ../../../../../../CropSyst/source/organic_matter/OM_params.cpp \
                ../../../../../../CropSyst/source/organic_matter/OM_types.cpp \
                ../../../../../../CropSyst/source/crop/canopy_growth_LAI_based.cpp \
                ../../../../../../CropSyst/source/soil/hydrology_cascade.cpp \
                ../../../../../../common/physical_parameter.cpp \
                ../../../../../../common/biomatter/biomass.cpp \
                ../../../../../../common/biomatter/biomass_abstract.cpp \
                ../../../../../../common/biomatter/biomass_decomposition_param.cpp \
                ../../../../../../common/biometeorology/ET_reference.cpp \
                ../../../../../../common/biometeorology/ET_model.cpp \
                ../../../../../../common/biometeorology/ET_common.cpp \
                ../../../../../../common/biometeorology/aerodynamics.cpp \
                ../../../../../../common/biometeorology/ET_reference_FAO.cpp \
                ../../../../../../common/geodesy/geolocation.cpp \
                ../../../../../../common/geodesy/geocoordinate.cpp \
                ../../../../../../common/physics/property.cpp \
                ../../../../../../common/physics/mass_common.cpp \
                ../../../../../../common/physics/mass.cpp \
                ../../../../../../common/soil/layering.cpp \
                ../../../../../../common/soil/SCS/SCS.cpp \
                ../../../../../../common/soil/txtrhydr.cpp \
                ../../../../../../common/residue/residue_const.cpp \
                ../../../../../../common/residue/residue_decomposition_param.cpp \
                ../../../../../../common/residue/residues_cycling.cpp \
                ../../../../../../common/residue/residues_common.cpp \
                ../../../../../../common/residue/residue_V4_common.cpp \
                ../../../../../../CS_suite/simulation/CS_simulation_element.cpp \
                ../../../../../../CS_suite/simulation/CS_land_unit.cpp \
                ../../../../../../CS_suite/simulation/CS_simulation_unit.cpp \
                ../../../../../../CS_suite/simulation/CS_event_scheduler.cpp \
                ../../../../../../CS_suite/simulation/CS_simulation_control.cpp \
                ../../../../../../UED/library/timeqry.cpp \
                ../../../../../../USDA/NRCS/RUSLE2/SDR_field_ops.cpp \
                ../../../../../../USDA/NRCS/soil/survey/domains.cpp \
                ../../../soil/temperature_interface.cpp


HEADERS +=

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../CORN/build/Qt/Debug/release/ -lcorn_complete_static
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../CORN/build/Qt/Debug/debug/ -lcorn_complete_static
#else:unix: LIBS += -L$$PWD/../../../../../CORN/build/Qt/Debug/ -lcorn_complete_static

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/release/ -lcommon_sim_static
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/debug/ -lcommon_sim_static
#else:unix: LIBS += -L$$PWD/../../../../../common/simulation/build/Qt/Debug/ -lcommon_sim_static

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../common/weather/build/Qt/Debug/release/ -lweather_static
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../common/weather/build/Qt/Debug/debug/ -lweather_static
#else:unix: LIBS += -L$$PWD/../../../../../common/weather/build/Qt/Debug/ -lweather_static

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../UED/library/build/Qt/Debug/release/ -lUED_static
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../UED/library/build/Qt/Debug/debug/ -lUED_static
#else:unix: LIBS += -L$$PWD/../../../../../UED/library/build/Qt/Debug/ -lUED_static

