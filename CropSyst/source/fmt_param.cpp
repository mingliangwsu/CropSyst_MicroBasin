#if (CROPSYST_VERSION>=1 && CROPSYST_VERSION <=4)
// This is obsolete in V5 which outputs only UED files
// I dont think this is used in V4 anymore either.

#include <ctype.h>
#include "fmt_param.h"
#include "rptoptns.h"

#include "corn/parameters/parameters_directory_OS_FS.h"
#include "csvc.h"

#include "CS_suite/observation/CS_desired_vars.h"
#include "options.h"

#include "corn/chronometry/date_const.hpp"

using namespace CORN;

#define LABEL_column_heads    "column_heads"
#define LABEL_accumulation_mode "accumulation_mode"
#define LABEL_daily           "daily"
#define LABEL_dates           "dates"
#define LABEL_format          "format"
#define LABEL_harvest         "harvest"
#define LABEL_header          "header"
#define LABEL_lines           "lines"
#define LABEL_options         "options"
#define LABEL_paginate        "paginate"
#define LABEL_profile         "profile"
#define LABEL_separate_years  "separate_years"
#define LABEL_timestep        "timestep"
#define LABEL_variables       "variables"
#define LABEL_yearly          "yearly"

#define LABEL_at_planting     "at_planting"
#define LABEL_at_emergence    "at_emergence"
#define LABEL_at_flowering    "at_flowering"
#define LABEL_at_maturity     "at_maturity"
#define LABEL_at_harvest      "at_harvest"

#define LABEL_profile_spreadsheets   "profile_spreadsheets"
#define LABEL_hydraulic_properties   "hydraulic_properties"
#define LABEL_ammonium               "ammonium"
#define LABEL_nitrate                "nitrate"
#define LABEL_denitrification        "denitrification"
#define LABEL_nitrification          "nitrification"
#define LABEL_mineralization         "mineralization"
#define LABEL_organic_matter         "organic_matter"
#define LABEL_plant_residue          "plant_residue"
#define LABEL_manure_residue         "manure_residue"
#define LABEL_temperature            "temperature"
#define LABEL_water_content          "water_content"
#define LABEL_water_potential        "water_potential"
#define LABEL_salinity               "salinity"
#define LABEL_root_fraction          "root_fraction"

#define LABEL_ANNUAL           "ANNUAL"
#define LABEL_GROWTH_PERIOD   "GROWTH_PERIOD"
#define LABEL_CONTINUOUS      "CONTINUOUS"

#define LABEL_water_budget    "water_budget"

#define MAX_VAR_STR_LEN 1000
#include "corn/measure/units.ph"
#include "CropSyst/phrases/fmtfile.ph"
#include "CropSyst/phrases/cs_rprt.ph"
//______________________________________________________________________________
const char *accumulation_mode_label_table[] =
{"NONE"
,LABEL_GROWTH_PERIOD
,LABEL_ANNUAL
,LABEL_CONTINUOUS
//NYI ,LABEL_FALLOW
,0
};
//_2003-01-03___________________________________________________________________
Report_options::Report_options()
:section("")
,write_enabled(false)
,header(1)
,column_heads(1)
,paginate(0)
,separate_years(0)
,accumulation_mode_labeled(CONTINUOUS_ACCUM)                                     //020324
,line_width(80)
,lines_per_page(60)
,time_step(1)       // daily report only
,salinity_budget(false)
,pesticide_budgets(false)
,nitrogen_budgets(false)                                                         //981203
,water_budget(false)                                                             //000414
,num_vars_to_print(0)
,v_lines_per_page(lines_per_page,LABEL_lines,65,0,999,0,999,TU_unitless,TL_Lines_per_page)
,v_time_step(time_step,LABEL_time_step,1,0,999,0,999,T_date_Days,TL_Time_step_days)  //000929
{
    for (int i = 0; i <= MAX_entries; i++)                                       //991119
       sel_var_code[i] = 0;                                                      //000926
}
//______________________________________________________________________________
Report_options::Report_options(const char *i_section)
:section(i_section)
,write_enabled(false)
,header(1)
,column_heads(1)
,paginate(0)
,separate_years(0)
,accumulation_mode_labeled(CONTINUOUS_ACCUM)                                     //020324
,line_width(80)
,lines_per_page(60)
,time_step(1)       // daily report only
,salinity_budget(false)
,pesticide_budgets(false)
,nitrogen_budgets(false)                                                         //981203
,water_budget(false)                                                             //000414
,num_vars_to_print(0)
,v_lines_per_page(lines_per_page,LABEL_lines,65,0,999,0,999,TU_unitless,TL_Lines_per_page)
,v_time_step(time_step,LABEL_time_step,1,0,999,0,999,T_date_Days,TL_Time_step_days)  //020329
{
    for (int i = 0; i <= MAX_entries; i++)                                       //991119
       sel_var_code[i] = 0;                                                      //000926
}
//_1998-12-03_____________________________________________________________________________
Report_options::Report_options(const Report_options &options_to_copy)
:section(options_to_copy.section)
,write_enabled(options_to_copy.write_enabled)
,header(options_to_copy.header)
,column_heads(options_to_copy.column_heads)
,paginate(options_to_copy.paginate)
,separate_years(options_to_copy.separate_years)
,accumulation_mode_labeled((Accumulation_mode)options_to_copy.accumulation_mode_labeled.get())   //020324
,line_width(options_to_copy.line_width)
,lines_per_page(options_to_copy.lines_per_page)
,time_step(options_to_copy.time_step)       // daily report only
,salinity_budget(options_to_copy.salinity_budget)
,pesticide_budgets(options_to_copy.pesticide_budgets)
,nitrogen_budgets(options_to_copy.nitrogen_budgets)
,water_budget(options_to_copy.water_budget)                                      //000414
,num_vars_to_print(options_to_copy.num_vars_to_print)
,v_lines_per_page(options_to_copy.v_lines_per_page)
,v_time_step(options_to_copy.v_time_step)
{
    for (int i = 0; i <= MAX_entries; i++)
       sel_var_code[i] = options_to_copy.sel_var_code[i];                        //000926
}
//_1998-12-03___________________________________________________________________
void Report_options::setup_write_enabled()                         modification_
{
   write_enabled =
   ((num_vars_to_print > 0)
             || (water_budget)                                                   //000414
             || (nitrogen_budgets)
             || (salinity_budget)
             || (pesticide_budgets));
}
//_1998-12-03___________________________________________________________________
void Report_options::require_variable
(CS_UED_variable_code variable)                                                  //000926
{
   int first_0_entry = 0;                                                        //991119
   for (int i = 0; i < MAX_entries; i++)                                         //991119
   {
      if ((sel_var_code[i] == 0)&& !first_0_entry)
         first_0_entry = i;
      if (sel_var_code[i] == variable)                                           //000926
         return; // The variable is already selected
   }
   sel_var_code[first_0_entry] = variable; // Append the required variable       //000926
}
//_1999-11-20___________________________________________________________________
void Report_options::count_SRO()                                   modification_
{
   num_vars_to_print = 0;
   for (int i = 0; i < MAX_entries; i++)
      num_vars_to_print += (int16)(sel_var_code[i] > 0);
}
//_1999-11-21___________________________________________________________________
void Report_options::list_required_variables(CS::Desired_variables &required_variables) const
{
   for (int i = 0; i <= MAX_entries; i++)
      if (sel_var_code[i] > 0)
         required_variables.append(sel_var_code[i]);
}
//_2004-10-02___________________________________________________________________
Report_formats_parameters::Report_formats_parameters()
: Common_parameters_data_record(OPTIONAL_ASSOCIATED_DIRECTORY,LABEL_format       //050323
,CS_VERSION
//180626 ,CS_VERSION_NUMBERS
)
,description("")                                                                 //981124
,create_TDF(true)                                                                //040927
,profile_spreadsheet_timestep(1)
,num_profile_print_dates(0)
,DLY_options(LABEL_daily)                                                        //000924
,YLY_options(LABEL_annual)                                                       //000924
,GS_options("growing_season")                                                    //000924
,v_profile_spreadsheet_timestep(profile_spreadsheet_timestep,LABEL_time_step,0,0,9999,0,9999,T_date_Days,TL_Daily_soil_profile_spreadsheet_timestep)   //000929
,at_planting(false)                                                              //981124
,at_emergence(false)                                                             //981124
,at_flowering(false)                                                             //981124
,at_maturity(false)                                                              //981124
,at_harvest(false)                                                               //981124
,SS_hydraulic_properties(false)                                                  //000911
#ifdef NITROGEN
,SS_ammonium(false)
,SS_nitrate(false)
,SS_denitrification(false)
,SS_nitrification(false)
,SS_NH4_mineralization(false)
,SS_immobilization(false)                                                        //160326
,SS_organic_matter(false)
#endif
#ifdef RESIDUES
,SS_plant_residue(false)
,SS_manure_residue(false)
#endif
#ifdef SOIL_TEMPERATURE
,SS_temperature(false)
#endif
,SS_water_content(false)                                                         //000911
,SS_water_potential(false)                                                       //000911
#ifdef SALINITY
,SS_salinity(false)
#endif
{                                                                                //991105
    for (nat16 i = 0; i <= MAX_PRINT_DATES; i++)
       profile_print_date_data[i] = 0;                                           //170525
       //170525profile_print_date_data[i].set_YD((Year)0,(DOY)0);
}
//______________________________________________________________________________
bool  Report_options::setup_structure(CORN::Data_record &data_rec,bool /*not used here for_write*/)
{
   data_rec.set_current_section(section.c_str());
   data_rec.expect_bool(LABEL_header,header,CROPSYST_VV_BOOL_FORM);
   data_rec.expect_bool(LABEL_column_headers,column_heads,CROPSYST_VV_BOOL_FORM);
   data_rec.expect_bool(LABEL_paginate,paginate,CROPSYST_VV_BOOL_FORM);
   data_rec.expect_bool(LABEL_separate_years,separate_years,CROPSYST_VV_BOOL_FORM);
   data_rec.expect_bool(LABEL_fertilizer_budget,nitrogen_budgets,CROPSYST_VV_BOOL_FORM);
   data_rec.expect_bool(LABEL_salinity_budget,salinity_budget,CROPSYST_VV_BOOL_FORM);
   data_rec.expect_bool(LABEL_water_budget,water_budget,CROPSYST_VV_BOOL_FORM);         //000414
   data_rec.expect_bool(LABEL_pesticide_budget,pesticide_budgets,CROPSYST_VV_BOOL_FORM);
   data_rec.expect_enum(LABEL_accumulation_mode,accumulation_mode_labeled,TL_Accumulation_mode); //020324
   data_rec.expect_valid_int16(v_lines_per_page);
   data_rec.expect_valid_int16(v_time_step);
   data_rec.expect_int16(LABEL_count,num_vars_to_print);
   data_rec.expect_nat32_array(section.c_str(),sel_var_code,1,MAX_entries,16,false);   //000926
   return true;
}
//______________________________________________________________________________
bool Report_formats_parameters::expect_structure(bool for_write)
{
   bool expected = Common_parameters_data_record::expect_structure(for_write);   //161129_020812
   structure_defined = false;                                                    //120314
   expect_bool("create_TDF",create_TDF);                                         //040927
   set_current_section(LABEL_profile_print);
      expect_valid_int16(v_profile_spreadsheet_timestep);
      expect_bool(LABEL_at_planting,at_planting,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_at_emergence,at_emergence,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_at_flowering,at_flowering,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_at_maturity,at_maturity,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_at_harvest,at_harvest,CROPSYST_VV_BOOL_FORM);
      expect_int16(LABEL_count,num_profile_print_dates);

      expect_int32_array(LABEL_profile_print,profile_print_date_data,false,MAX_PRINT_DATES,false);                                               //000926


      //170525 expect_date_array(LABEL_profile_print, profile_print_date_data,false,1 , MAX_PRINT_DATES,false);
   set_current_section(LABEL_profile_spreadsheets);                              //000911
      expect_bool(LABEL_hydraulic_properties,SS_hydraulic_properties,CROPSYST_VV_BOOL_FORM); //000911
      #ifdef NITROGEN
      expect_bool(LABEL_ammonium,SS_ammonium,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_nitrate,SS_nitrate,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_denitrification,SS_denitrification,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_nitrification,SS_nitrification,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_mineralization,SS_NH4_mineralization,CROPSYST_VV_BOOL_FORM);
      expect_bool("immobilization",SS_immobilization,CROPSYST_VV_BOOL_FORM);     //160326
      expect_bool(LABEL_organic_matter,SS_organic_matter,CROPSYST_VV_BOOL_FORM);
      #endif
#ifdef RESIDUES
      expect_bool(LABEL_plant_residue,SS_plant_residue,CROPSYST_VV_BOOL_FORM);
      expect_bool(LABEL_manure_residue,SS_manure_residue,CROPSYST_VV_BOOL_FORM);
#endif
#ifdef SOIL_TEMPERATURE
      expect_bool(LABEL_temperature,SS_temperature,CROPSYST_VV_BOOL_FORM);
#endif
      expect_bool(LABEL_water_content,SS_water_content,CROPSYST_VV_BOOL_FORM);   //000911
      expect_bool(LABEL_water_potential,SS_water_potential,CROPSYST_VV_BOOL_FORM);  //000911
#ifdef SALINITY
      expect_bool(LABEL_salinity,SS_salinity,CROPSYST_VV_BOOL_FORM);
      expect_bool("salt",SS_salt,CROPSYST_VV_BOOL_FORM);                         //070927
#endif
      expect_bool(LABEL_root_fraction,SS_root_fraction,CROPSYST_VV_BOOL_FORM);   //010316
      expect_bool("root_biomass",SS_root_biomass,CROPSYST_VV_BOOL_FORM);         //071214
   expected &= DLY_options.setup_structure(*this,for_write);                                 //981203
   expected &= YLY_options.setup_structure(*this,for_write);                                 //981203
   expected &= GS_options.setup_structure(*this,for_write);                                  //981203
   structure_defined = true;                                                     //120314
   return expected;                                                              //161129
}
//_1999-11-05_________________________________________________expect_structure_/
bool Report_formats_parameters::get_start()
{  for (nat16 i_clr = 0; i_clr <= MAX_entries; i_clr++)
   {  DLY_options.sel_var_code[i_clr] = 0;
      YLY_options.sel_var_code[i_clr] = 0;                                       //000926
      GS_options.sel_var_code[i_clr] = 0;                                        //000926
   }
   for (nat16 i = 0; i <= MAX_PRINT_DATES; i++)
      profile_print_date_data[i] = 0;                                            //170525
      //170525 profile_print_date_data[i].set_YD((Year)0,(DOY)0);
   return Common_parameters_data_record::get_start();                            //161023
}
//_2001-01-09___________________________________________________________________
bool Report_formats_parameters::get_end()
{
   bool ended = Common_parameters_data_record::get_end();                        //051028
   DLY_options.setup_write_enabled();                                            //981203
   YLY_options.setup_write_enabled();                                            //981203
   GS_options.setup_write_enabled();                                             //981203

   // This is a hack until I can added immobilization in format editor.          //160326
   bool add_immobilization = false;                                              //160326
   for (int vc_i = 0; vc_i <= GS_options.num_vars_to_print; vc_i++)              //160326
   if ( (GS_options.sel_var_code[vc_i] == CSVC_soil_N_mineralization_period_sum)
      ||(GS_options.sel_var_code[vc_i] == CSVC_residue_mineralized_period_sum)
      ||(GS_options.sel_var_code[vc_i] == CSVC_residue_manure_mineralized_period_sum)
      ||(GS_options.sel_var_code[vc_i] == CSVC_organic_matter_mineralized_period_sum))
      add_immobilization = true;
   if (add_immobilization)                                                       //160326
   {  GS_options.sel_var_code[GS_options.num_vars_to_print+1] = CSVC_soil_N_immobilization_period_sum;
      GS_options.num_vars_to_print++;
   }
   return ended;
}
//_2001-01-09___________________________________________________________________
bool Report_formats_parameters::set_start()
{
   DLY_options.count_SRO(); // Count selected variables
   YLY_options.count_SRO(); // (For backwards compatibility)
   GS_options.count_SRO();
   num_profile_print_dates = 0;  // This count is for old pascal version only
   for (nat16 i = 0; i <= MAX_PRINT_DATES; i++)
      num_profile_print_dates += (int16)(profile_print_date_data[i]) > 0;
   return Common_parameters_data_record::set_start();                            //051028
}
//_1999-11-21___________________________________________________________________
bool Report_formats_parameters::profile_print_date_exists(const CORN::Date_const &find_date) const
{ // See if the specified date exists in this list.
   for (int i = 0; i <= MAX_PRINT_DATES; i++)
      if (profile_print_date_data[i] == find_date.get_date32())                  //170525
         return true;
   return false;
}
//_1998-05-27___________________________________________________________________
bool Report_formats_parameters::add_profile_date(const CORN::Date_const &new_date)
{  // Avoid duplicate dates
   if (profile_print_date_exists(new_date))
      return true;
   // Find free entry (0) date
   for (int i = 1; i <= MAX_PRINT_DATES; i++)
   {  if (!profile_print_date_data[i]/*170525 .get()*/)
      {  profile_print_date_data[i] = new_date.get_date32();                     //170525
         //170525 profile_print_date_data[i] = new_date.set(new_date*;
         return true;
      }
   }
   return false; // output of room in the table.
}
//______________________________________________________________________________
bool Report_formats_parameters::delete_profile_date(const CORN::Date_const &del_date)
{  // Avoid duplicate dates
   for (int i = 0; i <= MAX_PRINT_DATES; i++)
      if (profile_print_date_data[i] == del_date.get_date32())                   //170525
         profile_print_date_data[i] = 0;                                         //170525
         //170525profile_print_date_data[i].set_YD((Year)0,(DOY)0); // there could be multiple entries, delete each
   return true;
}
//______________________________________________________________________________
bool Report_formats_parameters::clear_profile_dates()
{  for (int i = 0; i <= MAX_PRINT_DATES; i++)
         profile_print_date_data[i] = 0; // there could be multiple entries, delete each //170525
         //170525 profile_print_date_data[i].set_YD((Year)0,(DOY)0); // there could be multiple entries, delete each
   return true;
}
//_2003-05-20___________________________________________________________________
void Report_formats_parameters::require_variable(uint8 for_report,CS_UED_variable_code variable)
{  switch (for_report)
   { case DLY : DLY_options.require_variable(variable); break;
     case GS  : GS_options.require_variable(variable);  break;                   //030516
     case YLY : YLY_options.require_variable(variable); break;
   }
}
//_1999-11-20___________________________________________________________________
void Report_formats_parameters::list_required_profile_variable(CS::Desired_variables &required_variables,UED_variable_code base_var_code ,int sublayers) const
{  for (int i = 0; i <= sublayers; i++)
   {  UED::Variable_code_clad layer_var_code(base_var_code);
      layer_var_code.set_layer(i);
      required_variables.append(layer_var_code.get());
    }
}
//_2004-09-20___________________________________________________________________
void Report_formats_parameters::list_required_variables(CS::Desired_variables &required_variables,int sublayers) const
{  DLY_options.list_required_variables(required_variables);
   GS_options.list_required_variables(required_variables);
   YLY_options.list_required_variables(required_variables);
   if (SS_water_content       )  list_required_profile_variable(required_variables,CSVC_soil_base_water_content,sublayers);
   if (SS_water_potential     )  list_required_profile_variable(required_variables,CSVC_soil_base_water_potential,sublayers);
   if (SS_temperature         )  list_required_profile_variable(required_variables,CSVC_soil_base_temperature_time_step_avg,sublayers);
   if (SS_plant_residue       )  list_required_profile_variable(required_variables,CSVC_residue_plant_incorporated,sublayers);
   if (SS_manure_residue      )  list_required_profile_variable(required_variables,CSVC_residue_manure_incorporated,sublayers);
   if (SS_salinity            )  list_required_profile_variable(required_variables,CSVC_soil_base_salinity,sublayers);
   if (SS_salt                )  list_required_profile_variable(required_variables,CSVC_soil_base_salt    ,sublayers);     //070927
   if (SS_ammonium            )  list_required_profile_variable(required_variables,CSVC_soil_N_NH4_amount,sublayers);
   if (SS_nitrate             )  list_required_profile_variable(required_variables,CSVC_soil_N_NO3_amount,sublayers);
   if (SS_denitrification     )  list_required_profile_variable(required_variables,CSVC_soil_N_denitrification_time_step_sum,sublayers);
   if (SS_nitrification       )  list_required_profile_variable(required_variables,CSVC_soil_N_nitrification_time_step_sum,sublayers);
   if (SS_NH4_mineralization  )  list_required_profile_variable(required_variables,CSVC_soil_N_mineralization_time_step_sum,sublayers);
   if (SS_immobilization      )  list_required_profile_variable(required_variables,CSVC_soil_N_immobilization_time_step_sum,sublayers); //160326

   // This is a hack if mineralization also list immobilization
   // because currently (seasonal) immobilization is not available in format editor.
   if (SS_NH4_mineralization  )  list_required_profile_variable(required_variables,CSVC_soil_N_immobilization_time_step_sum,sublayers); //160326


   if (SS_organic_matter      )  list_required_profile_variable(required_variables,CSVC_organic_matter_percent_time_step_sum,sublayers);
   if (SS_root_fraction       )  list_required_profile_variable(required_variables,CSVC_crop_base_root_fraction,sublayers);
//NYI 071214     if (SS_root_biomass        )  list_required_profile_variable(required_variables,CSVC_crop_base_root_fraction,sublayers);
}
//_2004-09-02__________________________________________list_required_variables_/
void Report_formats_parameters::sort_profile_print_dates()
{  // simple bubble sort because the array will already be mostly sorted
   bool sorted = false;
   nat16 first_unsorted = 0;
   nat16 last_unsorted = MAX_PRINT_DATES_ALLOC;
   while (!sorted)
   {  sorted = true;
      nat16 sorted_index = last_unsorted;
      // Null entries need to be put last (Index 0 not used)
      for (nat16 i = 1; i < sorted_index-1; i++)
      {
         if (profile_print_date_data[i] > profile_print_date_data[i+1])          //170525
         {
            CORN::date32 hold_date = profile_print_date_data[i];                       //170525
            profile_print_date_data[i] = profile_print_date_data[i+1];           //170525
            profile_print_date_data[i+1] = hold_date;                            //170525
            last_unsorted  = (nat16)i + 1;
            sorted = false;
         }
      }
   }
}
//______________________________________________________________________________
#ifndef REACCH_VERSION
CORN::OS_FS::Parameters_directory *Report_formats_parameters
::create_associated_directory(const char *param_file_name_cstr) performs_IO_
{ // This directory is created when using the TDF export option.
   CORN::OS::File_name_concrete param_file_name(param_file_name_cstr);
   CORN::OS::Directory_entry_name_concrete param_dir(param_file_name
      ,CORN::OS::Directory_entry_name::include_all_except_extension);
   return new CORN::OS_FS::Parameters_directory(param_dir,false);  //090820
}
#endif
//_2005-08-30___________________________________________________________________
#endif
