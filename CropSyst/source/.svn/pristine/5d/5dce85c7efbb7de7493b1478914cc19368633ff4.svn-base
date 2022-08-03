#if (CS_VERSION==4)
#include "cs_project.h"
#include "static_phrases.h"
#ifdef USE_OLD_CS_PATHS
#include "cs_paths.h"
#include "cs_project_directory.h"
#else
#include "CS_suite/application/CS_suite_directory.h"
#endif
#include "CS_suite/observation/CS_desired_vars.h"
#include "corn/math/statistical/statistics_types.hpp"
//______________________________________________________________________________
CropSyst_project::CropSyst_project()
: Common_project_parameters(/*CS_VERSION_NUMBERS*/)
// If the program has a runtime error here, make sure to setup_cs_suite_paths(ParamStr(0).c_str()); in the main function.
   #if (__BCPLUSPLUS__ < 0x0570)

   #else

,active_scenario_filename(active_filename) // Set the alias reference to the active_filename //050618
#endif
,report_format_filename_rel("default")
,run_statistical_analysis(false)                                                 //060706
{
   for (int i = 0; i < GS_MAX_IDS; i++)
      GS_statistic_selection[i] = 0;
   for (int i = 0; i < MAX_YLY_entries; i++)
      ANNL_statistic_selection[i] = 0;
}
//_2005-02-04___________________________________________________________________
bool CropSyst_project::expect_structure(bool for_write)
{  bool expected = Common_project_parameters::expect_structure(for_write);       //161129_020328
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_project);                                           //021012
      expect_enum("type",project_type_labeled);                                  //050202
#ifndef LADSS_UNIX
// not needed for LADSS
   // The following are for when running scenarios in batch mode.
   set_current_section(LABEL_output);
      expect_file_name(LABEL_report_format,report_format_filename_rel);          //030406
   set_current_section("analysis");                                              //060706
      expect_bool("statistical",run_statistical_analysis);                       //060706
      expect_nat32_array  ("growing_season_statistics" , GS_statistic_selection   ,0,GS_MAX_IDS     ,16,false);            //050204
      expect_nat32_array  ("annual_statistics"         , ANNL_statistic_selection ,0,MAX_YLY_entries,16,false);            //050204
   if (!for_write)                                                               //060706
   {  // These parameters are now common (not just for GIS) these are here to read older version file (remove in version 5)
      set_current_section(LABEL_GIS);                                            //060706
         expect_nat32_array  ("GIS_growing_season_statistics" , GS_statistic_selection   ,0,GS_MAX_IDS     ,16,false);     //060706
         expect_nat32_array  ("GIS_annual_statistics"         , ANNL_statistic_selection ,0,MAX_YLY_entries,16,false);     //050204
   }
#endif
   structure_defined = true;                                                     //120314
   return expected;                                                              //161129
}
//______________________________________________________________________________
#if (CROPSYST_VERSION < 5)
#define  old_STAT_value_bit     1
#define  old_STAT_sum_bit       2
#define  old_STAT_mean_bit      4
// This should be named Arithmetic mean
#define  old_STAT_std_dev_bit   8
#define  old_STAT_coef_var_bit 16
#define  old_STAT_sum_sqrs_bit 32
#define  old_STAT_min_bit      64
#define  old_STAT_max_bit     128
#define  old_STAT_count_bit	  256
// The following require dataset
#define  old_STAT_median_bit  512
//______________________________________________________________________________
nat32 convert_stat_bits_old_new(nat32 old_stat_bits)
{  nat32 new_stat_bits =
      ((old_stat_bits & old_STAT_value_bit)     ? STAT_value_bit : 0)
     |((old_stat_bits & old_STAT_sum_bit)       ? STAT_sum_bit : 0)
     |((old_stat_bits & old_STAT_mean_bit)      ? STAT_arithmetic_mean_bit : 0)
     |((old_stat_bits & old_STAT_std_dev_bit)   ? STAT_std_dev_bit : 0)
     |((old_stat_bits & old_STAT_coef_var_bit)  ? STAT_coef_var_bit : 0)
     |((old_stat_bits & old_STAT_sum_sqrs_bit)  ? STAT_sum_sqrs_bit : 0)
     |((old_stat_bits & old_STAT_min_bit)       ? STAT_min_bit : 0)
     |((old_stat_bits & old_STAT_max_bit)       ? STAT_max_bit : 0)
     |((old_stat_bits & old_STAT_count_bit)     ? STAT_count_bit : 0)
     |((old_stat_bits & old_STAT_median_bit)    ? STAT_median_bit : 0);
   return new_stat_bits;
}
//______________________________________________________________________________
/*180626 obsolete, the statistics are now specified differently
bool CropSyst_project::get_end()                                                 //161129
{  bool ended = Common_project_parameters::get_end();                            //140316
   if (data_source_version.get_number() < 0x041210)
   {  for (nat8 gs_s = 0; gs_s <GS_MAX_IDS; gs_s++)
         GS_statistic_selection[gs_s] = convert_stat_bits_old_new(GS_statistic_selection[gs_s]);
      for (nat8 a_s = 0; a_s <GS_MAX_IDS; a_s++)
         ANNL_statistic_selection[a_s] = convert_stat_bits_old_new(ANNL_statistic_selection[a_s]);
   }
   return ended;                                                                 //161129
}
*/
#endif
//______________________________________________________________________________
#if (defined(XLS_OUTPUT) || defined(UED_OUTPUT))
void CropSyst_project::list_required_variables(CS::Desired_variables &required_variables) const
{  for (int i = 0; i <= GS_MAX_IDS; i++)
      if (GS_statistic_selection[i] ) // <- If I recall correctly this is the only one really needed to check
         required_variables.append(GS_report_var_opts[i].ID);
   for (int i = 0; i <= MAX_YLY_entries; i++)
      if (ANNL_statistic_selection[i]) // <- If I recall correctly this is the only one really needed to check
         required_variables.append(YLY_report_var_opts[i].ID);
}
#endif
//_2009-10-07___________________________________________________________________
#endif
