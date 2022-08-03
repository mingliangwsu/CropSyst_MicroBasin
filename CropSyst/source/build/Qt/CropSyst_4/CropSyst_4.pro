#-------------------------------------------------
#
# Project created by QtCreator 2012-04-04T06:46:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = CropSyst_4
CONFIG   += console
CONFIG   -= app_bundle
DEFINES  += CROPSYST CS_VERSION=4 CROPSYST_VERSION=4 CROPSYST_PROPER=4 CROP_PARAM_ADJUST OLD_PHENOLOGY_SEQUENCER CO2_V5 OLD_ORCHARD APPTYPE_CONSOLE
INCLUDEPATH += ../../../../.. ../../.. ../.. ../../../../../common ../../../../../USDA/NRCS
unix:LIBS += -L/home/rnelson/dev/corn/build/Qt/corn_complete_static-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK__Release -lcorn_complete_static
QMAKE_CXXFLAGS  += -fpermissive -Wno-unused-parameter -Wno-reorder -Wno-used-but-set-parameter -Wno-unused-but-set-variable -g

TEMPLATE = app


SOURCES += \
    ../../../cropsyst_main.cpp \
    ../../../arguments_CropSyst.cpp \
    ../../../static_phrases.cpp \
    ../../../soil.cpp \
    ../../../sim_param.cpp \
    ../../../seeding_param.cpp \
    ../../../rptoptns.cpp \
    ../../../rprtclss.cpp \
    ../../../rot_param.cpp \
    ../../../project_types.cpp \
    ../../../pond.cpp \
    ../../../perform_op.cpp \
    ../../../output.cpp \
    ../../../organicn.cpp \
    ../../../N_sources.cpp \
    ../../../model_options.cpp \
    ../../../mgmt_types.cpp \
    ../../../mgmt_param.cpp \
    ../../../land_unit_sim.cpp \
    ../../../land_unit_output.cpp \
    ../../../land_unit_output_V4.cpp \
    ../../../inorganic_NH4.cpp \
    ../../../friction_velocity.cpp \
    ../../../fastgraph_vars.cpp \
    ../../../desired_vars.cpp \
    ../../../watertab.cpp \
    ../../../CropSyst_inspection.cpp \
    ../../../csprofss.cpp \
    ../../../cs_vars_abbrv.cpp \
    ../../../cs_vars.cpp \
    ../../../cs_UED_season.cpp \
    ../../../cs_UED_harvest.cpp \
    ../../../cs_UED_db.cpp \
    ../../../CS_UED_datasrc.cpp \
    ../../../cs_UED_daily.cpp \
    ../../../cs_UED_annual.cpp \
    ../../../cs_till.cpp \
    ../../../cs_simulation.cpp \
    ../../../cs_scenario_directory.cpp \
    ../../../cs_scenario.cpp \
    ../../../cs_results.cpp \
    ../../../cs_report_V4.cpp \
    ../../../cs_project.cpp \
    ../../../cs_operation_codes.cpp \
    ../../../cs_operation.cpp \
    ../../../cs_mod.cpp \
    ../../../cs_mgmt.cpp \
    ../../../cs_events.cpp \
    ../../../cs_event.cpp \
    ../../../cs_ET.cpp \
    ../../../cs_datarec.cpp \
    ../../../cs_chem_pot_mineral_N.cpp \
    ../../../cs_accum.cpp \
    ../../../soil/abiotic_environment.cpp \
    ../../../soil/chemicals_profile.cpp \
    ../../../soil/chemical_profile.cpp \
    ../../../soil/chemical_mass_profile.cpp \
    ../../../soil/chemical_balance.cpp \
    ../../../soil/disturbance.cpp \
    ../../../soil/dynamic_water_entering.cpp \
    ../../../soil/erosion_RUSLE.cpp \
    ../../../soil/evaporation_abstract.cpp \
    ../../../soil/evaporation_without_vapor_path.cpp \
    ../../../soil/evaporation_interface.cpp \
    ../../../soil/freezing_numerical.cpp \
    ../../../soil/freezing_jumakis.cpp \
    ../../../soil/infiltration.cpp \
    ../../../soil/infiltration_cascade_hourly.cpp \
    ../../../soil/infiltration_cascade_daily.cpp \
    ../../../soil/infiltration_cascade_common.cpp \
    ../../../soil/infiltration_finite_diff.cpp \
    ../../../soil/hydrology.cpp \
    ../../../soil/hydrology_finite_diff.cpp \
    ../../../soil/hydrology_cascade.cpp \
    ../../../soil/hydraulic_properties.cpp \
    ../../../soil/layers.cpp \
    ../../../soil/nitrogen_profile.cpp \
    ../../../soil/nitrogen_common.cpp \
    ../../../soil/profile_texture.cpp \
    ../../../soil/runoff.cpp \
    ../../../soil/runoff_SCS.cpp \
    ../../../soil/salinity_profile.cpp \
    ../../../soil/soil_param_with_STATSGO.cpp \
    ../../../soil/soil_param_V4.cpp \
    ../../../soil/soil_param_struct.cpp \
    ../../../soil/soil_param_class.cpp \
    ../../../soil/soil_param.cpp \
    ../../../soil/soil_interface.cpp \
    ../../../soil/soil_base.cpp \
    ../../../soil/structure_interface.cpp \
    ../../../soil/structure_common.cpp \
    ../../../soil/surface_infiltration_green_ampt.cpp \
    ../../../soil/surface_temperature.cpp \
    ../../../soil/sublayers.cpp \
    ../../../soil/temperature_profile.cpp \
    ../../../soil/temperature_interface.cpp \
    ../../../soil/temperature_hourly.cpp \
    ../../../soil/temperature_functions.cpp \
    ../../../soil/texture_interface.cpp \
    ../../../soil/tillage_effect.cpp \
    ../../../crop/canopy_growth.cpp \
    ../../../crop/canopy_growth_portioned.cpp \
    ../../../crop/canopy_growth_LAI_based.cpp \
    ../../../crop/canopy_growth_cover_based.cpp \
    ../../../crop/canopy_growth_LAI_based_V4.cpp \
    ../../../crop/canopy_growth_LAI_based_V5.cpp \
    ../../../crop/canopy_cover_continuum.cpp \
    ../../../crop/canopy_cover_curve.cpp \
    ../../../crop/crop_biomass.cpp \
    ../../../crop/crop_common.cpp \
    ../../../crop/crop_CO2.cpp \
    ../../../crop/crop_cropsyst.cpp \
    ../../../crop/crop_emergence.cpp \
    ../../../crop/crop_fruit.cpp \
    ../../../crop/crop_interfaced_cropsyst.cpp \
    ../../../crop/crop_interfaced.cpp \
    ../../../crop/crop_orchard_common.cpp \
    ../../../crop/crop_orchard_Kemanian_Stockle.cpp \
    ../../../crop/crop_orchard_Oyarzun_Stockle.cpp \
    ../../../crop/crop_N_balancer.cpp \
    ../../../crop/crop_N_common.cpp \
    ../../../crop/crop_N_V5.cpp \
    ../../../crop/crop_N_V4.cpp \
    ../../../crop/crop_param_V4.cpp \
    ../../../crop/crop_param_struct.cpp \
    ../../../crop/crop_param_class.cpp \
    ../../../crop/crop_root.cpp \
    ../../../crop/crop_root_V4.cpp \
    ../../../crop/crop_root_V5.cpp \
    ../../../crop/crop_types.cpp \
    ../../../crop/extreme_temperature_response.cpp \
    ../../../crop/growth_stages.cpp \
    ../../../crop/phenology_interface.cpp \
    ../../../crop/phenology_common.cpp \
    ../../../crop/transpiration.cpp \
    ../../../crop/transpiration_interface.cpp \
    ../../../crop/transpiration_dependent_growth_V4.cpp \
    ../../../crop/thermal_time_common.cpp \
    ../../../crop/thermal_time_daily.cpp \
    ../../../crop/quiescence.cpp \
    ../../../crop/event_scheduler_crop.cpp \
    ../../../crop/yield.cpp \
    ../../../organic_matter/OM_residues_profile_common.cpp \
    ../../../organic_matter/OM_residues_profile_abstract.cpp \
    ../../../organic_matter/OM_pools_common.cpp \
    ../../../organic_matter/OM_types.cpp \
    ../../../organic_matter/OM_params.cpp \
    ../../../organic_matter/OM_common.cpp \
    ../../../organic_matter/multiple_pool/OM_pools_multiple.cpp \
    ../../../organic_matter/multiple_pool/OM_multiple_pool.cpp \
    ../../../organic_matter/simple/OM_residues_profile_simple_V4.cpp \
    ../../../organic_matter/simple/OM_simple.cpp \
    ../../../organic_matter/single_pool/OM_pools_single.cpp \
    ../../../organic_matter/single_pool/OM_single_pool.cpp \
    ../../../project/GIS/GIS_table.cpp \
    ../../../project/GIS/pat.cpp \
    ../../../management/management_param_struct.cpp \
    ../../../management/management_param_class.cpp \
    ../../../management/management_param_V4.cpp \
    ../../../../../common/weather/database/weather_UED_database.cpp \
    ../../../../../common/soil/layering.cpp \
    ../../../../../common/residue/residues_cycling.cpp \
    ../../../../../common/residue/residues_common.cpp \
    ../../../../../common/residue/residue_single_pool.cpp \
    ../../../../../common/residue/residue_V4_common.cpp \
    ../../../../../common/residue/residue_pools_simple.cpp \
    ../../../../../common/residue/residue_pool_simple.cpp \
    ../../../../../common/residue/residue_decomposition_param.cpp \
    ../../../../../common/residue/residue_decomposition_limitations.cpp \
    ../../../../../common/residue/residue_const.cpp \
    ../../../../../common/residue/residue_biomatter_profile_simple.cpp \
    ../../../../../common/residue/residue_balancer.cpp \
    ../../../../../common/biomatter/manure_form.cpp \
    ../../../../../common/biomatter/biomass_decomposition_param.cpp \
    ../../../../../common/biomatter/organic_biomatter_balance.cpp \
    ../../../../../common/biomatter/biomass_abstract.cpp \
    ../../../../../common/biomatter/biomass.cpp \
    ../../../../../common/environment/environment_base.cpp \
    ../../../../../common/physics/property.cpp \
    ../../../../../common/physics/mass_common.cpp \
    ../../../../../common/physics/mass.cpp \
    ../../../../../common/geodesy/geolocation.cpp \
    ../../../../../common/geodesy/geocoordinate.cpp \
    ../../../../../common/soil/SCS/SCS.cpp \
    ../../../../../common/soil/USDA_texture.cpp \
    ../../../../../common/soil/txtrhydr.cpp \
    ../../../../../common/soil/texttri.cpp \
    ../../../../../common/soil/texture.cpp \
    ../../../../../common/evaporator.cpp \
    ../../../../../common/physics/water_depth.cpp \
    ../../../../../common/weather/temperature_amplitude_phase_calibrator.cpp \
    ../../../../../UED/convert/ED_tabular_format.cpp \
    ../../../../../USDA/NRCS/soil/survey/domains.cpp \
    ../../../../../USDA/NRCS/RUSLE2/SDR_field_ops.cpp \
    ../../../../../corn/format/binary/oldbinrec/oldbinrec_s.cpp \
    ../../../../../common/weather/subdaily.cpp
