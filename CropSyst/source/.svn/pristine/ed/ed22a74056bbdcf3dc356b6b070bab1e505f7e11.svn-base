#ifndef FMT_to_TDFH
#define FMT_to_TDFH

/*
This class converts CropSyst format files to tabular data format description files

A directory is created with the same name as the .FMT file containing the following files.
These file are created only if the variables are selected.
daily.tdf
annual.tdf
season.tdf
harvest.tdf

soil/water_content.tdf
soil/NO3
soil/xxxx
soil/xxxx
soil/xxxx
soil/xxxx
soil/xxxx
*/

#include "UED/convert/ED_tabular_format.h"
#include "rptoptns.h"
#include "fmt_param.h"
//______________________________________________________________________________
class FMT_to_TDF_Convertor
{
   class Soil_profile_tabular_format
   : public ED_tabular_file_format
   {  Ustring                 report_name;
      UED::Smart_variable_code smart_var_code;
      CORN::Units_clad      smart_units_code;
      int                     time_step;
   public:
      Soil_profile_tabular_format(const char *i_report_name,UED_variable_code i_var_code,Units_code i_smart_units_code,int i_timestep);
      void convert(Format_file_type format_file_type,const char *tdf_filename);
//050327 moved to Common_parameters      virtual bool has_associated_directory() const { return false;}
   };
   //___________________________________________________________________________
   class Report_tabular_format
   : public ED_tabular_file_format
   {  Ustring                        report_name;
      Report_options                &report_options;
      int                            report_var_count;
      report_var_layout_with_graph  *report_var_opts;
      UED::Smart_record_code         record_type_code_used_by_all_records;
   public:
       Report_tabular_format
          (const char                   *_report_name
          ,Report_options               &_report_options
          ,int                           _report_var_count
          ,report_var_layout_with_graph *_report_var_opts  // array of these
          ,Units_code                    _time_step_units
          ,Record_code                   _record_type_code);
      void convert(Format_file_type format_file_type,const char *tdf_filename);
      virtual bool has_associated_directory() const { return false;}
   };
   //___________________________________________________________________________
//now use associated directory   CORN::Directory_name    format_dir;

   Report_formats_parameters  &CS_format;
   Report_tabular_format    *daily_tabular_format;
   Report_tabular_format    *annual_tabular_format;
   Report_tabular_format    *season_tabular_format;
   Report_tabular_format    *harvest_tabular_format;

   Format_file_type     format_file_type;

   // NYI also need N reports

   Soil_profile_tabular_format    *hydraulic_properties_format;
   Soil_profile_tabular_format    *ammonium_format;
   Soil_profile_tabular_format    *nitrate_format;
   Soil_profile_tabular_format    *denitrification_format;
   Soil_profile_tabular_format    *nitrification_format;
   Soil_profile_tabular_format    *mineralization_format;
   Soil_profile_tabular_format    *organic_matter_format;
   Soil_profile_tabular_format    *plant_residue_format;
   Soil_profile_tabular_format    *manure_residue_format;
   Soil_profile_tabular_format    *temperature_format;
   Soil_profile_tabular_format    *water_content_format;
   Soil_profile_tabular_format    *water_potential_format;
   Soil_profile_tabular_format    *salinity_format;
   Soil_profile_tabular_format    *root_fraction_format;
public:
   FMT_to_TDF_Convertor(Report_formats_parameters  &_CS_format,Format_file_type  _format_file_type_labeled);
   void convert(const char *param_file_name);
};
//______________________________________________________________________________

#endif
