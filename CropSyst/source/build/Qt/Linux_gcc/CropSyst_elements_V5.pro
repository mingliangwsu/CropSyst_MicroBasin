#-------------------------------------------------
#
# Project created by QtCreator 2012-04-04T06:46:28
#
#-------------------------------------------------

QT       -= gui

TARGET = CropSyst_element_V5
CONFIG += staticlib
DEFINES  += CS_VERSION=5 CROPSYST_VERSION=5 USE_WEATHER_PROVIDER MICROBASIN_VERSION
INCLUDEPATH += ../../../../.. ../../.. ../.. ../../../../../common ../../../../../USDA/NRCS ../../../../../corn
QMAKE_CXXFLAGS  += -fpermissive -Wno-unused-parameter -Wno-reorder -Wno-used-but-set-parameter -Wno-unused-but-set-variable -g
TEMPLATE = lib


SOURCES += \
    ../../../unstressed_growth.cpp \
    ../../../static_phrases.cpp \
    ../../../soil.cpp \
    ../../../seeding_param.cpp \
    ../../../rprtclss.cpp \
    ../../../rot_param.cpp \
    ../../../pond.cpp \
    ../../../perform_op.cpp \
    ../../../N_sources.cpp \
    ../../../model_options.cpp \
    ../../../mgmt_types.cpp \
    ../../../land_unit_sim.cpp \
    ../../../inorganic_NH4.cpp \
    ../../../desired_vars.cpp \
    ../../../cs_vars.cpp \
    ../../../cs_scenario.cpp \
    ../../../cs_operation_codes.cpp \
    ../../../cs_operation.cpp \
    ../../../cs_mgmt.cpp \
    ../../../cs_event.cpp \
    ../../../cs_ET.cpp \
    ../../../soil/abiotic_environment.cpp \
    ../../../soil/tillage_effect.cpp \
    ../../../soil/texture_interface.cpp \
    ../../../soil/temperature_profile.cpp \
    ../../../soil/temperature_hourly.cpp \
    ../../../soil/temperature_functions.cpp \
    ../../../soil/surface_temperature.cpp \
    ../../../soil/sublayers.cpp \
    ../../../soil/structure_interface.cpp \
    ../../../soil/structure_common.cpp \
    ../../../soil/soil_param_struct.cpp \
    ../../../soil/soil_param_class.cpp \
    ../../../soil/soil_param.cpp \
    ../../../soil/soil_interface.cpp \
    ../../../soil/soil_base.cpp \
    ../../../soil/runoff.cpp \
    ../../../soil/nitrogen_profile.cpp \
    ../../../soil/nitrogen_common.cpp \
    ../../../soil/infiltration_finite_diff.cpp \
    ../../../soil/infiltration_cascade_hourly.cpp \
    ../../../soil/infiltration_cascade_daily.cpp \
    ../../../soil/infiltration_cascade_common.cpp \
    ../../../soil/infiltration.cpp \
    ../../../soil/hydrology_finite_diff.cpp \
    ../../../soil/hydrology_cascade.cpp \
    ../../../soil/hydrology.cpp \
    ../../../soil/hydraulic_properties.cpp \
    ../../../soil/freezing_jumakis.cpp \
    ../../../soil/dynamic_water_entering.cpp \
    ../../../soil/disturbance.cpp \
    ../../../soil/chemicals_profile.cpp \
    ../../../soil/chemical_profile.cpp \
    ../../../soil/chemical_mass_profile.cpp \
    ../../../soil/chemical_balance.cpp \
    ../../../crop/transpiration_interface.cpp \
    ../../../crop/transpiration_dependent_growth.cpp \
    ../../../crop/phenology_interface.cpp \
    ../../../crop/growth_stages.cpp \
    ../../../crop/crop_types.cpp \
    ../../../crop/crop_transpiration_2.cpp \
    ../../../crop/crop_thermal_time.cpp \
    ../../../crop/crop_root.cpp \
    ../../../crop/crop_param_struct.cpp \
    ../../../crop/crop_param_class.cpp \
    ../../../crop/crop_n.cpp \
    ../../../crop/crop_interfaced_cropsyst.cpp \
    ../../../crop/crop_interfaced.cpp \
    ../../../crop/crop_inactive_period.cpp \
    ../../../crop/crop_emergence.cpp \
    ../../../crop/crop_cropsyst.cpp \
    ../../../crop/crop_common.cpp \
    ../../../crop/CO2_response.cpp \
    ../../../crop/canopy_growth_portioned.cpp \
    ../../../crop/canopy_growth_LAI_based.cpp \
    ../../../crop/canopy_growth_cover_based.cpp \
    ../../../crop/canopy_cover_continuum.cpp \
    ../../../../../USDA/NRCS/soil/survey/domains.cpp \
    ../../../../../USDA/NRCS/RUSLE2/SDR_field_ops.cpp \
    ../../../../../common/soil/layering.cpp \
    ../../../../../common/residue/residues_cycling.cpp \
    ../../../../../common/residue/residues_common.cpp \
    ../../../../../common/residue/residue_single_pool.cpp \
    ../../../../../common/residue/residue_V4_common.cpp \
    ../../../../../common/residue/residue_decomposition_param.cpp \
    ../../../../../common/residue/residue_decomposition_limitations.cpp \
    ../../../../../common/residue/residue_const.cpp \
    ../../../../../common/residue/residue_biomatter_profile_simple.cpp \
    ../../../../../common/residue/residue_balancer.cpp \
    ../../../../../common/biomatter/manure_form.cpp \
    ../../../../../common/biomatter/biomass_decomposition_param.cpp \
    ../../../../../common/biomatter/biomass_abstract.cpp \
    ../../../../../common/biomatter/biomass.cpp \
    ../../../../../common/environment/environment_base.cpp \
    ../../../../../common/physics/property.cpp \
    ../../../../../common/physics/mass_common.cpp \
    ../../../../../common/physics/mass.cpp \
    ../../../../../common/geodesy/geolocation.cpp \
    ../../../../../common/geodesy/geocoordinate.cpp \
    ../../../../../common/soil/SCS/SCS.cpp \
    ../../../watertab.cpp \
    ../../../organic_matter/OM_residues_profile_common.cpp \
    ../../../organic_matter/OM_residues_profile_abstract.cpp \
    ../../../organic_matter/OM_pools_common.cpp \
    ../../../organic_matter/OM_types.cpp \
    ../../../organic_matter/OM_params.cpp \
    ../../../organic_matter/OM_common.cpp \
    ../../../organic_matter/multiple_pool/OM_pools_multiple.cpp \
    ../../../organic_matter/multiple_pool/OM_multiple_pool.cpp \
    ../../../../../common/soil/USDA_texture.cpp \
    ../../../../../common/soil/txtrhydr.cpp \
    ../../../../../common/soil/texttri.cpp \
    ../../../../../common/soil/texture.cpp \
    ../../../organic_matter/single_pool/OM_pools_single.cpp \
    ../../../organic_matter/single_pool/OM_single_pool.cpp \
    ../../../management/management_param_struct.cpp \
    ../../../management/management_param_class.cpp \
    ../../../crop/extreme_temperature_response.cpp \
    ../../../../../common/weather/database/weather_UED_database.cpp \
    ../../../crop/canopy_cover_curve.cpp \
    ../../../crop/canopy_growth_LAI_based_V5.cpp \
    ../../../crop/crop_root_V5.cpp \
    ../../../crop/canopy_growth_LAI_based_V4.cpp \
    ../../../crop/phenology_common.cpp \
    ../../../soil/layers.cpp \
    ../../../management/management_param_V5.cpp \
    ../../../soil/soil_param_V5.cpp \
    ../../../soil/evaporation_abstract.cpp \
    ../../../../../common/physics/property/P_vapor_pressure.cpp \
    ../../../../../common/physical_parameter.cpp \
    ../../../../../common/simulation/synchronization.cpp \
    ../../../../../common/simulation/simulation.cpp \
    ../../../../../common/simulation/scenario.cpp \
    ../../../../../common/simulation/operation.cpp \
    ../../../../../common/simulation/log.cpp \
    ../../../../../common/simulation/event_types.cpp \
    ../../../../../common/simulation/event.cpp \
    ../../../../../common/simulation/event_status.cpp \
    ../../../../../common/simulation/balancer.cpp \
    ../../../../../CS_suite/simulation/CS_simulation_unit.cpp \
    ../../../../../CS_suite/simulation/CS_simulation_element.cpp \
    ../../../../../CS_suite/simulation/CS_simulation_control.cpp \
    ../../../../../CS_suite/simulation/CS_land_unit.cpp \
    ../../../../../CS_suite/simulation/CS_event_scheduler.cpp \
    ../../../crop/crop_param_V5.cpp \
    ../../../cs_accum.cpp \
    ../../../cs_vars_abbrv.cpp \
    ../../../crop/phenology_sequencer.cpp \
    ../../../friction_velocity.cpp \
    ../../../../../common/biometeorology/ET_reference.cpp \
    ../../../../../common/biometeorology/ET_reference_FAO.cpp \
    ../../../../../common/biometeorology/ET_model.cpp \
    ../../../../../common/biometeorology/ET_common.cpp \
    ../../../../../common/biometeorology/aerodynamics.cpp

HEADERS += \
    ../../../../../corn/measure/common_units.h
