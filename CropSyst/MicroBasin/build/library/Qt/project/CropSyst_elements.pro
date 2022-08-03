#-------------------------------------------------
#
# Project created by QtCreator 2012-04-04T06:46:28
#
#-------------------------------------------------

QT       -= gui

TARGET = CropSyst_elements
CONFIG += staticlib
DEFINES  += UNICODE CS_VERSION=5 CROPSYST_VERSION=5 MICROBASIN_VERSION \
            EVENT_SCHEDULER_VERSION=1 WEATHER_PROVIDER_VERSION=5 \
            SOIL_TEMPERATURE OLD_PHENOLOGY_SEQUENCER
INCLUDEPATH += . ../../../../../.. ../../../../../../CropSyst/source ../../../../../../corn ../../../../../../common ../../../../../../USDA/NRCS
# ../../../../.. ../../.. ../.. ../../../../../common ../../../../../USDA/NRCS  ../../../../../../dev/corn
QMAKE_CXXFLAGS += -fpermissive
QMAKE_CXXFLAGS += -Wno-reorder -Wno-unused-parameter -Wno-unused-but-set-parameter
TEMPLATE = lib


SOURCES += \
      ../../../../../../CropSyst/source/arguments_CropSyst.cpp \
      ../../../../../../CropSyst/source/CropSyst_inspection.cpp \
      ../../../../../../CropSyst/source/cs_accum.cpp \
      ../../../../../../CropSyst/source/cs_scenario.cpp \
      ../../../../../../CropSyst/source/cs_event.cpp \
      ../../../../../../CropSyst/source/cs_ET.cpp \
      ../../../../../../CropSyst/source/cs_mgmt.cpp \
      ../../../../../../CropSyst/source/cs_operation_codes.cpp \
      ../../../../../../CropSyst/source/cs_operation.cpp \
      ../../../../../../CropSyst/source/cs_scenario_directory.cpp \
      ../../../../../../CropSyst/source/cs_vars.cpp \
      ../../../../../../CropSyst/source/cs_vars_abbrv.cpp \
      ../../../../../../CropSyst/source/friction_velocity.cpp \
      ../../../../../../CropSyst/source/inorganic_NH4.cpp \
      ../../../../../../CropSyst/source/land_unit_sim.cpp \
      ../../../../../../CropSyst/source/mgmt_types.cpp \
      ../../../../../../CropSyst/source/model_options.cpp \
      ../../../../../../CropSyst/source/N_sources.cpp \
      ../../../../../../CropSyst/source/pond.cpp \
      ../../../../../../CropSyst/source/perform_op.cpp \
      ../../../../../../CropSyst/source/rprtclss.cpp \
      ../../../../../../CropSyst/source/rot_param.cpp \
      ../../../../../../CropSyst/source/soil.cpp \
      ../../../../../../CropSyst/source/seeding_param.cpp \
      ../../../../../../CropSyst/source/static_phrases.cpp \
      ../../../../../../CropSyst/source/watertab.cpp \
      ../../../../../../CropSyst/source/crop/crop_common.cpp \
      ../../../../../../CropSyst/source/crop/transpiration_interface.cpp \
      ../../../../../../CropSyst/source/crop/phenology_interface.cpp \
      ../../../../../../CropSyst/source/crop/growth_stages.cpp \
      ../../../../../../CropSyst/source/crop/canopy_cover_curve.cpp \
        ../../../../../../CropSyst/source/crop/crop_element.cpp \
      ../../../../../../CropSyst/source/crop/canopy_growth_LAI_based_V4.cpp \
      ../../../../../../CropSyst/source/crop/canopy_growth_LAI_based_V5.cpp \
      ../../../../../../CropSyst/source/crop/crop_root_V5.cpp \
      ../../../../../../CropSyst/source/crop/crop_types.cpp \
      ../../../../../../CropSyst/source/crop/crop_root.cpp \
      ../../../../../../CropSyst/source/crop/crop_param_struct.cpp \
      ../../../../../../CropSyst/source/crop/crop_param_class.cpp \
      ../../../../../../CropSyst/source/crop/crop_param_V4.cpp \
      ../../../../../../CropSyst/source/crop/crop_interfaced_cropsyst.cpp \
      ../../../../../../CropSyst/source/crop/crop_interfaced.cpp \
      ../../../../../../CropSyst/source/crop/crop_emergence.cpp \
      ../../../../../../CropSyst/source/crop/crop_cropsyst.cpp \
      ../../../../../../CropSyst/source/crop/crop_N_common.cpp \
      ../../../../../../CropSyst/source/crop/crop_N_V5.cpp \
      ../../../../../../CropSyst/source/crop/CO2_response.cpp \
      ../../../../../../CropSyst/source/crop/canopy_growth_portioned.cpp \
      ../../../../../../CropSyst/source/crop/canopy_growth_LAI_based.cpp \
      ../../../../../../CropSyst/source/crop/canopy_growth_cover_based.cpp \
      ../../../../../../CropSyst/source/crop/canopy_cover_continuum.cpp \
      ../../../../../../CropSyst/source/crop/event_scheduler_crop.cpp \
      ../../../../../../CropSyst/source/crop/extreme_temperature_response.cpp \
      ../../../../../../CropSyst/source/crop/quiescence.cpp \
      ../../../../../../CropSyst/source/crop/phenology_common.cpp \
      ../../../../../../CropSyst/source/crop/phenology_sequencer.cpp \
      ../../../../../../CropSyst/source/crop/thermal_time_common.cpp \
      ../../../../../../CropSyst/source/crop/thermal_time_daily.cpp \
      ../../../../../../CropSyst/source/crop/transpiration.cpp \
      ../../../../../../CropSyst/source/crop/transpiration_dependent_growth.cpp \
      ../../../../../../CropSyst/source/crop/transpiration_dependent_growth_V4.cpp \
      ../../../../../../CropSyst/source/crop/yield.cpp \
      ../../../../../../CropSyst/source/management/management_param_class.cpp \
      ../../../../../../CropSyst/source/management/management_param_struct.cpp \
      ../../../../../../CropSyst/source/management/management_param_V4.cpp \
      ../../../../../../CropSyst/source/organic_matter/OM_residues_profile_common.cpp \
      ../../../../../../CropSyst/source/organic_matter/OM_residues_profile_abstract.cpp \
      ../../../../../../CropSyst/source/organic_matter/OM_pools_common.cpp \
      ../../../../../../CropSyst/source/organic_matter/OM_types.cpp \
      ../../../../../../CropSyst/source/organic_matter/OM_params.cpp \
      ../../../../../../CropSyst/source/organic_matter/OM_common.cpp \
      ../../../../../../CropSyst/source/organic_matter/multiple_pool/OM_pools_multiple.cpp \
      ../../../../../../CropSyst/source/organic_matter/multiple_pool/OM_multiple_pool.cpp \
      ../../../../../../CropSyst/source/organic_matter/single_pool/OM_pools_single.cpp \
      ../../../../../../CropSyst/source/organic_matter/single_pool/OM_single_pool.cpp \
      ../../../../../../CropSyst/source/soil/abiotic_environment.cpp \
      ../../../../../../CropSyst/source/soil/chemicals_profile.cpp \
      ../../../../../../CropSyst/source/soil/chemical_profile.cpp \
      ../../../../../../CropSyst/source/soil/chemical_mass_profile.cpp \
      ../../../../../../CropSyst/source/soil/chemical_balance.cpp \
      ../../../../../../CropSyst/source/soil/disturbance.cpp \
      ../../../../../../CropSyst/source/soil/dynamic_water_entering.cpp \
      ../../../../../../CropSyst/source/soil/freezing_jumakis.cpp \
      ../../../../../../CropSyst/source/soil/hydrology_cascade.cpp \
      ../../../../../../CropSyst/source/soil/hydrology.cpp \
      ../../../../../../CropSyst/source/soil/hydraulic_properties.cpp \
      ../../../../../../CropSyst/source/soil/layers.cpp \
      ../../../../../../CropSyst/source/soil/nitrogen_profile.cpp \
      ../../../../../../CropSyst/source/soil/nitrogen_common.cpp \
      ../../../../../../CropSyst/source/soil/profile_texture.cpp \
      ../../../../../../CropSyst/source/soil/runoff.cpp \
      ../../../../../../CropSyst/source/soil/soil_param_V5.cpp \
      ../../../../../../CropSyst/source/soil/surface_temperature.cpp \
      ../../../../../../CropSyst/source/soil/sublayers.cpp \
      ../../../../../../CropSyst/source/soil/structure_interface.cpp \
      ../../../../../../CropSyst/source/soil/structure_common.cpp \
      ../../../../../../CropSyst/source/soil/soil_base.cpp \
      ../../../../../../CropSyst/source/soil/soil_evaporator.cpp \
      ../../../../../../CropSyst/source/soil/soil_param_class.cpp \
      ../../../../../../CropSyst/source/soil/soil_param.cpp \
      ../../../../../../CropSyst/source/soil/soil_properties_sublayers.cpp \
      ../../../../../../CropSyst/source/soil/soil_interface.cpp \
      ../../../../../../CropSyst/source/soil/tillage_effect.cpp \
      ../../../../../../CropSyst/source/soil/texture_interface.cpp \
      ../../../../../../CropSyst/source/soil/temperature_profile.cpp \
      ../../../../../../CropSyst/source/soil/temperature_hourly.cpp \
      ../../../../../../CropSyst/source/soil/temperature_functions.cpp \
      ../../../../../../common/biomatter/manure_form.cpp \
      ../../../../../../common/biomatter/biomass_decomposition_param.cpp \
      ../../../../../../common/biomatter/biomass_abstract.cpp \
      ../../../../../../common/biomatter/biomass.cpp \
      ../../../../../../common/environment/environment_base.cpp \
      ../../../../../../common/geodesy/geocoordinate.cpp \
      ../../../../../../common/geodesy/geolocation.cpp \
      ../../../../../../common/physics/mass_common.cpp \
      ../../../../../../common/physics/mass.cpp \
      ../../../../../../common/physics/property.cpp \
      ../../../../../../common/physics/property/P_vapor_pressure.cpp \
      ../../../../../../common/physics/water_depth.cpp \
      ../../../../../../common/residue/residues_cycling.cpp \
      ../../../../../../common/residue/residues_common.cpp \
      ../../../../../../common/residue/residue_V4_common.cpp \
      ../../../../../../common/residue/residue_decomposition_param.cpp \
      ../../../../../../common/residue/residue_decomposition_limitations.cpp \
      ../../../../../../common/residue/residue_const.cpp \
      ../../../../../../common/residue/residue_biomatter_profile_simple.cpp \
      ../../../../../../common/residue/residue_balancer.cpp \
      ../../../../../../common/simulation/synchronization.cpp \
      ../../../../../../common/simulation/scenario.cpp \
      ../../../../../../common/simulation/operation.cpp \
      ../../../../../../common/simulation/log.cpp \
      ../../../../../../common/simulation/event_types.cpp \
      ../../../../../../common/simulation/event.cpp \
      ../../../../../../common/simulation/event_status.cpp \
      ../../../../../../common/simulation/balancer.cpp \
      ../../../../../../common/simulation/scenario_directory.cpp \
      ../../../../../../common/simulation/simulation_project_directory.cpp \
      ../../../../../../common/soil/layering.cpp \
      ../../../../../../common/soil/SCS/SCS.cpp \
      ../../../../../../common/soil/USDA_texture.cpp \
      ../../../../../../common/soil/txtrhydr.cpp \
      ../../../../../../common/soil/texttri.cpp \
      ../../../../../../common/soil/texture.cpp \
      ../../../../../../common/evaporator.cpp \
      ../../../../../../common/weather/database/weather_UED_database.cpp \
      ../../../../../../CS_suite/CropSyst/file_system/project_directory_CropSyst.cpp \
      ../../../../../../UED/convert/ED_tabular_format.cpp \
      ../../../../../../USDA/NRCS/soil/survey/domains.cpp \
      ../../../../../../USDA/NRCS/RUSLE2/SDR_field_ops.cpp \
        ../../../../../../CropSyst/source/crop/biomass_growth_RUE_TUE.cpp



