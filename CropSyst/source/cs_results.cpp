#  include "cs_accum.h"
#  include "crop/crop_param.h"
#  include "crop/crop_interfaced.h"
//170213RLN #  include "land_unit_with_output.h"
#ifndef REACCH_VERSION
# if (CROPSYST_VERSION==4)
#  include "cs_report_V4.h"
# else
   #define MAX_PRINT_DATES_ALLOC 101
# endif
#endif
#  include "soil/chemicals_profile.h"
#  include "static_phrases.h"
#  include "soil/runoff.h"
#  include "cs_event.h"
#  include "soil/freezing_interface.h"
#  include "soil/nitrogen_profile.h"
#  include "organic_matter/OM_residues_profile_abstract.h"

#  include "common/weather/weather.h"
#  include "common/weather/database/weather_database.h"
#  include "cs_scenario_directory.h"
#  include "cs_ET.h"
#ifndef REACCH_VERSION
# if (CROPSYST_VERSION==4)
#  include "cs_mod.h"
# endif
#endif
#  include "csprofss.h"
//#include "land_unit_output.h"

#define delim ','
#define TAB ((char)9)

#ifdef _Windows
#  include <conio.h>
#endif
#include <iomanip>
#include "crop/phenology_interface.h"

using namespace std;
using namespace CropSyst; 
//______________________________________________________________________________

extern bool harvest_event_failed_today; // This is here only for Mike Rivington's spreadsheet

float64 check_used_last_ACC_NO3_transformed_to; // special variable because we dont keep denitrification as a chemcial}
#ifdef LISTVARS
ofstream list_var_file;
bool list_var_file_open;
#endif
/*111130
// used by RON H., dont delete yet
ofstream chem_infiltrate_file;
ofstream chem_et_file;
*/
//______________________________________________________________________________
std::string &PAW_bar(float64 PAW , std::string &bar)
{  float spaces = 51.0;
   int tab = (int)(spaces * PAW);
   if (tab > 50) tab = 50;
   if (tab < 0) tab = 1;
   std::string tabs(tab,(char)219);                                              //140318
   bar.assign(tabs);
   bar.resize(51);
   return bar;
}
//_1997-12-31__________________________________________________________PAW_bar_/
#if (CROPSYST_VERSION == 4)
#ifdef PRINT_PROFILE
void CropSyst_V4::CropSyst_Model::setup_profile_print_events
(const CORN::Date  profile_print_date_data[]
   ,Year sim_start_year, Year sim_end_year )                                     //051201
{
   /*151203 disabled because I need to access the event queue

   for (int16 i = 1  ; i < MAX_PRINT_DATES_ALLOC  ; i++)
   {  if (profile_print_date_data[i].get())
      {  if (profile_print_date_data[i].get_year() == 0)
         {  // The user can now use dates with year 0 to print every year of the simulation run
            for (Year year = sim_start_year; year <= sim_end_year; year++)
            {  CORN::Date date_i(profile_print_date_data[i]);
               date_i.set_year(year);
               event_queue->append(new profile_print_event(date_i,record_soil_profile_today));
         }  }  else
            event_queue->append(new profile_print_event(profile_print_date_data[i],record_soil_profile_today));   //020309
      } // Else not a listed date
   }
   */

}
//_2005-12-01__2000-05-26___________________________setup_profile_print_events_/
#endif
#endif

#if (CROPSYST_VERSION == 4)
#if defined (PRINT_PROFILE) || defined(DISPLAY_PROFILE)
void CropSyst::Land_unit_simulation::print_profile
(std::ostream &profile
,bool // obsolete limit_layers // If displaying to screen 000511
,const CORN::Date_const &today
,const char *crop_description
,const char *growth_stage
,float64 root_depth)
{
   profile.flags(ios::fixed);
   profile << today.as_string() << ' ' << crop_description << ' ' << growth_stage << std::endl; //020618
   if (scenario_control_and_model_options.run_nitrogen)                          //130827
     profile << ' ' << (TL_TOTALHEAD1)  <<std::endl
             << " # #   m    m   m3/m3  %    øC     kg/ha   kg/ha   kg/ha   kg/ha   kg/ha  % O.M"<< endl;
   else
     profile << ' ' << (TL_TOTALHEAD2) << std::endl
             << " # #   m    m   m3/m3  %                                                        " << endl;
   const CropSyst::Soil *soil = ref_soil();                                      //060803
   if (soil)                                                                     //060803
   {
      const Soil_layers_interface *layers = soil->ref_layers();
      for (nat8 sublayer = 1; sublayer <= std::min<nat8>(20,layers->get_number_layers() ); sublayer++)
      {
         profile.width(2);
         profile << (int) layers->get_horizon_at_layer( sublayer);               //051116
         profile.width(3);
         profile << (int)sublayer;
         char depth_marker = soil->ref_hydrology()->is_frozen(sublayer) ? 'Û' : ' '; //160412_981015
         profile << depth_marker;
         profile << setw(4) << setprecision(2) << layers ->get_depth_m(sublayer);
         CropSyst::Crop_interfaced *crop_active =                                //131008NS
         #ifdef INTERCROPPING
            get_predominant_crop();                                              //130716
         #else
            crop_active_or_intercrop;
         #endif
         if (!crop_active || crop_active->ref_phenology().get_growth_stage_sequence() == NGS_GERMINATION) depth_marker = ' ';
         else if (root_depth > layers ->get_depth_m(sublayer))                                    depth_marker = 'Û';
         else if (root_depth > layers ->get_layer_center_depth(sublayer))                         depth_marker = 'Û';
         else if (root_depth < (layers ->get_depth_m(sublayer) - layers->get_thickness_m(sublayer))) depth_marker = ' ';
         else if (root_depth <= layers ->get_layer_center_depth(sublayer))                        depth_marker = 'ß';
         profile << depth_marker;
         profile << setw(3) << setprecision(2) << layers->get_thickness_m(sublayer)              << ' ';
         profile << setw(4) << setprecision(2) << (float)
            soil->hydrology->get_water_plus_ice_content_volumetric(sublayer)     //130930
            << ' ';                                                              //990311
         profile << setw(4) << setprecision(1) << (float)soil->get_plant_avail_water(sublayer) << ' ';

#ifdef NITROGEN
         if (scenario_control_and_model_options.run_nitrogen && soil->chemicals) //130827
         {
            // This is just a check that these functions a the same: get_elemental_N_from_NO3 is probably redundent
            float64 NO3_N_x = soil->chemicals->get_NO3_N_mass_kg_m2(sublayer);
            float64 NO3_N_y = soil->chemicals->get_elemental_N_from_NO3(sublayer);
            assert (NO3_N_x == NO3_N_y);


            profile <<  setw(5) << setprecision(1)<<  (float)soil->get_temperature(sublayer) << ' ';
            profile <<  setw(8) << setprecision(3)<< soil->chemicals->get_elemental_N_from_NO3(sublayer) *over_m2_to_ha;
            profile <<  setw(8) << setprecision(3)<< soil->chemicals->get_elemental_N_from_NH4(sublayer) *over_m2_to_ha << ' ';
            profile <<  setw(7) << setprecision(3)<< (organic_matter_residues_profile_kg_m2 ? ((organic_matter_residues_profile_kg_m2->get_soil_organic_matter_mineralization_N(sublayer))*over_m2_to_ha) : 0.0 )<< ' '; /*mineralized from PMN*/ //040524
            profile <<  setw(7) << setprecision(3)<<
               (over_m2_to_ha * soil->chemicals->NO3->
               #ifdef OLD_N_XFER
               chem_to_element_factor*(soil->chemicals->NO3->transformed_from_M[sublayer])
               #else
               denitrified_N_output.get(sublayer)                                //170502
               #endif
               ) << ' ';  /*nitrified from NH4*/
            profile <<  setw(7) << setprecision(3)<< (soil->chemicals->
                  #ifdef OLD_N_XFER
                  //170503
                  denitrification_N_E_output[sublayer]                           //131004
                  #else
                  NO3->denitrified_N_output.get(sublayer)                        //170503
                  #endif
                  *over_m2_to_ha) << ' ' ;
//NYI Note this (where  converted to elemental) can be replaced by denitrification_N_E_output which is the elemental amount
//NYI              profile <<  setw(7) << setprecision(3)<< ((soil->chemicals->denitrification_N_E_output[sublayer])*over_m2_to_ha) << ' ' ;


            float64 OM_percent = organic_matter_residues_profile_kg_m2
            ?  organic_matter_residues_profile_kg_m2->get_percent_organic_matter(sublayer)
            : 0.0;
            profile <<  setw(6) << setprecision(3)<< OM_percent;
         } else
#endif

         {  std::string buffer;
            profile << PAW_bar( soil->get_plant_avail_water(sublayer),buffer);
         }
         profile << endl;
      }
      if (layers->get_number_layers() > 21)
         profile << "(Remaining layers not displayed)" << endl;

      profile.width(6);profile.precision(3);
      float64 ultimate_freezing_depth =  soil_freezing_optional ? soil_freezing_optional->get_ultimate_freezing_depth() : 0.0;   //070824
      profile << ultimate_freezing_depth;                                        //981015
#ifdef NITROGEN
   if (scenario_control_and_model_options.run_nitrogen && soil->chemicals)       //130827
   {
      profile << "      ( N kg/ha)          ";
      profile.width(8); profile.precision(3);
      profile << (float)soil->chemicals->NO3->chem_to_element_factor*(soil->chemicals->NO3->get_current_profile_content_M()) *over_m2_to_ha<< ' '; //981028
      profile.width(7); profile.precision(3);
      profile << (float)soil->chemicals->NH4->chem_to_element_factor*(soil->chemicals->NH4->get_current_profile_content_M()) *over_m2_to_ha << ' ';   //981028
      profile.width(7); profile.precision(3);    /*ACC_mineralization*/

      float64 X_transformed = soil->chemicals->NH4->ANNL_bal_accums
      ? soil->chemicals->NH4->chem_to_element_factor*(soil->chemicals->NH4->ANNL_bal_accums->transformed_from_M)*over_m2_to_ha
      : 0.0;
      profile << X_transformed << ' ';

      float64 Y_transformed = soil->chemicals->NO3->ANNL_bal_accums
      ? soil->chemicals->NO3->chem_to_element_factor*(soil->chemicals->NO3->ANNL_bal_accums->transformed_from_M) *over_m2_to_ha
      : 0.0;
      profile.width(7); profile.precision(3);    /*ACC_nitrification*/
      profile << (float)Y_transformed << ' ' ;

      profile.width(7);profile.precision(3);     /*ACC_denitrification*/
      float64 Z_transformed =  soil->chemicals->NO3->ANNL_bal_accums
      ? soil->chemicals->NO3->chem_to_element_factor*(soil->chemicals->NO3->ANNL_bal_accums->transformed_to_M) *over_m2_to_ha
      : 0.0;
      profile << (float)Z_transformed
      << endl;
   }
   else
#endif
      profile << endl ;
   }
   else // soil (optional) not available to print profile
      profile << endl ;                                                          //060803

}
#endif
#endif
//______________________________________________________________________________
// 060316 733 lines
// 060922 643 lines
// 090309 576 lines

