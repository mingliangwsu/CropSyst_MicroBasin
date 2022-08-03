#ifndef cs_UED_seasonH
#define cs_UED_seasonH
#include "corn/data_source/datarec.h"
//170525#include "corn/datetime/date.hpp"
#include "UED/library/UED_tuple_datasrc.h"
//______________________________________________________________________________
class Chemical_balance_accumulators;
class Residues_interface;
namespace CropSyst {
class Crop_interfaced;
}
namespace CropSyst                                                               //130308
{  class Pond;
   class Period_accumulators;
   class Soil   ;
}
using namespace CORN;
//______________________________________________________________________________
class Season_data_record : public CORN::Data_record
{
   std::string crop_name;
   int32       s_out_ID;     // used only by LADSS
   int32       alloc_ID;     // used only by LADSS
   int32       land_use_ID;  // used only by LADSS Essentially the crop name     //030331
   CORN::Date_clad_32 planting_date;    // date stored as a float                //041205
   CORN::Date_clad_32 restart_date;     // date stored as a float                //041205
   CORN::Date_clad_32 emergence_date;   // Eventually I want to output periods in UED files
   CORN::Date_clad_32 flowering_date;
   CORN::Date_clad_32 tuber_init_date;                                           //081111
   CORN::Date_clad_32 grain_filling_date;
   CORN::Date_clad_32 peak_LAI_date;  // rename to LAI_max_date 180413
   CORN::Date_clad_32 maturity_date;
   CORN::Date_clad_32 harvest_date;
#ifdef CROP_ORCHARD
   CORN::Date_clad_32 bud_break_date;                                            //081013
   CORN::Date_clad_32 initial_fruit_growth_date;                                 //081013
   CORN::Date_clad_32 rapid_fruit_growth_date;                                   //081013
   CORN::Date_clad_32 chill_requirement_satisfied_date;                          //081013
   float32  fruit_canopy_biomass;                                                //091104
   float32  nonfruit_canopy_biomass;                                             //091104
#endif
   CORN::Date_clad_32 inactive_begin_date;                                       //081013
   CORN::Date_clad_32 inactive_end_date;                                         //081013
   // Mass yields are in kg/m2
   float32  peak_LAI;
   float32  yield;
   float32  used_biomass;
   float32  grazed_biomass;
   float32  residue_biomass;
   float32  disposed_biomass;
   float32  dry_biomass;  // This is actually total biomass produced
   float32  daytime_VPD_avg;
   float32  intercepted_PAR_accum;
   float32  root_depth;
   float32  root_biomass;                                                        //091104
   float32  surface_residue_biomass;
   float32  surface_plant_residue_biomass;                                       //091104
   float32  surface_manure_biomass;                                              //091104
   float32  incorporated_residue;   // biomass   add                             //091104
   float32  incorporated_plant_residue; // biomass
   float32  incorporated_manure;  // biomass
   float32  erosion_index;
   float32  soil_loss;
   float32  ET_pot;
   float32  ET_act;
   float32  ET_ref;                                                              //130723
   float32  transp_pot;
   float32  transp_act;
   float32  evap_soil_pot;
   float32  evap_soil_act;
   float32  evap_residue_pot;
   float32  evap_residue_act;
   float32  irrig;
   float32  precip;
   float32  air_temp_avg_mean;                                                   //160324
   float32  crop_water_intrcpt_today; // remove_today                            //160414
   float32  residue_water_intrcpt;
   float32  surface_water_runoff;
   float32  ponded_water;
   float32  water_enter_soil;
   float32  soil_water_drainage;
   public: // special outputs
      float32 soil_water_profile_init;                                           //151227
      float32 soil_water_profile_final;                                          //151227
      float32 soil_available_water_15_init;                                      //160601
      float32 soil_available_water_15_final;                                     //160601
 private:
   float32  avg_water_stress_index;
   float32  avg_temperature_stress_index;
   float32  avg_flower_temperature_stress_index;                                 //091103
#if (CROPSYST_VERSION==4)
   float32  avg_filling_duration_index;                                          //091103
#endif
   float32  avg_tuber_init_temp_stress_index;                                    //091103
   float32  avg_tuber_filling_temp_stress;                                       //091103
#ifdef NITROGEN
   float32  N_leached;
   float32  N_total_applied;                                                     //160323
   float32  N_auto_uptake;
   float32  N_available;
   float32  N_mineralized_residue;
   float32  N_mineralized_org_fert;
   float32  N_mineralized_OM;
   float32  N_immobilization;
   float32  N_mineralization;
   float32  N_inorganic_applied;                                                 //160323
   float32  N_organic_applied;
   float32  N_organic_gaseous_loss;    // NH3 volatilization
   float32  N_inorganic_gaseous_loss;
   float32  N_fixation;

   float32  N_stress_index_avg;              // avg_nitrogen_stress_index;
   float32  N_uptake;
   float32  N_mass_canopy;  //110915 N_canopy_assimilation //070209 N_uptake_above_ground;
   float32  N_mass_yield;                                                        //120117

   float32  N_max_expected_conc_at_flowering;                                    //061213
   float32  N_max_expected_conc_at_maturity;                                     //061213
   float32  N_max_expected_conc_flower_mature_ratio;                             //061213
   float32  N_uptake_excess_or_deficit;                                          //061213
   float32  nitrification;                                                       //110917
   float32  denitrification;
 public:
   float32  N_soil_profile_initial; // Mineral N in the soil                     //161130
   float32  N_soil_profile_final;   // Mineral N in the soil
 private:
   float32  N_N2O_loss_denitrification;                                          //150624
   float32  N_N2O_loss_nitrification;                                            //150624
   #ifdef NYI
   float32  N_soil_inputs;       // total N inputs to the soil     (check that N applied include organic N) // this is only for luca
   float32  N_soil_output; // total N outputs from the soil  // this is only for luca
   #endif
   // NYN N_N2O_N_loss_denitrification  // Currently we have only needed annual N losses
   // NYN N_N2O_N_loss_nitrification
#endif
#ifdef PHOSPHORUS
   float32 P_uptake;
   float32 P_applied;
   float32 P_soil_profile;
#endif
#           define season_section  "growing_season"
 // special outputs
   float32 degree_hours_above_30_flowering_fortnight;
   float32 degree_hours_above_34_flowering_fortnight;
   float32 Srad_mean;
   float32 Tmax_mean;
   float32 Tmin_mean;
   float32 Tavg_mean;
   float32 WUE;
   float32 days_to_flowering;                                                    //160523
   float32 duration_season;                                                      //160527
   float32 canopy_cover_max;                                                     //180413
   float32 canopy_cover_green_final;                                             //180413

 public: // constructor
   Season_data_record();
   void update
      (const CropSyst::Crop_interfaced   &crop                                   //131008NS
      ,const CropSyst::Soil &soil                                                //141106
      ,CropSyst::Period_accumulators    *GP_accumulators
      #ifdef NITROGEN
      ,Chemical_balance_accumulators  *NO3_GP_bal_accums                         //050114
      ,Chemical_balance_accumulators  *NH4_GP_bal_accums                         //050114
      #endif
      ,CropSyst::Pond         &pond
      ,Residues_interface     *residue_pools_kg_m2 // rename this to residues_kg_m2  050726
      ,int32                   alloc_ID );  // Only for LADSS
   virtual bool expect_structure(bool for_write);                                //161025
   void clear();                                                                    //110115
};
//______________________________________________________________________________
class Season_data_source : public UED::Tuple_data_source
, public Season_data_record
{
//    Keep a single data record which is updated as needed.
//    This will require the structure to be setup only once.
public: // Constructor
   Season_data_source(UED::Database_file_indexed *_database);
   void record(datetime64 date_time);
};
//_____________________________________________________________________________/
#endif


