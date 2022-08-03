#error obsolete
Crop_CropSyst_contained
(            const char *crop_parameter_file_name
,Transpiration_model     transpiration_model  = ORIGINAL_TRANSPIRATION_MODEL     //050331
)
{
   Crop_parameters *parameters= new Crop_parameters
      ((_nitrogen_model > CROP_NITROGEN_DISABLED) // nitrogen_simulation
      ,_run_salinity          // salinity_simulation
      ,true    // now always reading residue parameters
#ifdef CO2_CHANGE
      ,_simulate_CO2           // CO2_simulation
#else
      ,false
#endif
      );


   VV_File crop_file(crop_parameter_file_name);
   crop_file.get(*parameters);
   crop = new Crop_interfaced_complete
      (parameters // relinquished to Crop_cropsyst
      ,_weather
      ,_soil
      ,_soil_chem
      ,_soil_salinity
      ,_transpiration_model
      ,_seeding_parameters
      ,_nitrogen_model
NITRO       ,_ET      // Optional. Although ET is optional, if it is not specified, there will be no correction for transpiration
SALT        ,_run_salinity
CO2         ,_simulate_CO2
CO2         ,_current_CO2_conc
CROPROWS    ,0 // goahead and read the crop row parameters _crop_row
      );

060531      May need to /*060601_*/    if (organic_matter_and_residue_model_labeled.get() == V4_4_ORGANIC_MATTER_AND_RESIDUE) // Decomposing canopy is only available in this model
060531      May need to /*060531_*/       crop->know_residues(organic_matter_residues_profile_kg_m2->get_residues());
};

