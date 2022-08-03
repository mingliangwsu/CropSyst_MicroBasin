#include "corn/data_source/data_source_pch.h"

#include "fmt_to_tdf.h"
#include "UED/library/record.h"
#include "corn/measure/units.h"
#include "corn/parameters/parameters_directory.h"
#include "corn/measure/units_enum.h"
#include "corn/data_source/vv_file.h"
//______________________________________________________________________________
FMT_to_TDF_Convertor::FMT_to_TDF_Convertor(Report_formats_parameters  &i_CS_format,Format_file_type  _format_file_type)
: CS_format(i_CS_format)
, daily_tabular_format(0)
, annual_tabular_format(0)
, season_tabular_format(0)
, harvest_tabular_format(0)
, hydraulic_properties_format(0)
, ammonium_format(0)
, nitrate_format(0)
, denitrification_format(0)
, nitrification_format(0)
, mineralization_format(0)
, organic_matter_format(0)
, plant_residue_format(0)
, manure_residue_format(0)
, temperature_format(0)
, water_content_format(0)
, water_potential_format(0)
, salinity_format(0)
, root_fraction_format(0)
, format_file_type(_format_file_type)
{
   int rtc = Record_type_distinguisher_interface::UED_data_value_year_var_units;

   if (CS_format.DLY_options.num_vars_to_print) daily_tabular_format    = new Report_tabular_format("Daily report"   ,CS_format.DLY_options  ,DLY_MAX_IDS     ,DLY_report_var_opts,UT_day,Record_type_distinguisher_interface::UED_data_set_year_var_units ); // Record_type_distinguisher_interface::UED_data_value_year_var_units);
   if (CS_format.YLY_options.num_vars_to_print) annual_tabular_format   = new Report_tabular_format("Annual report"  ,CS_format.YLY_options  ,MAX_YLY_entries ,YLY_report_var_opts,UT_year,Record_type_distinguisher_interface::UED_data_set_year_var_units);
   if (CS_format.GS_options.num_vars_to_print)  season_tabular_format   = new Report_tabular_format("Season report"  ,CS_format.GS_options   ,GS_MAX_IDS      ,GS_report_var_opts, 0/*no timestep*/,Record_type_distinguisher_interface::UED_data_value_date_var_units);
//NYI   if (CS_format.DLY_options.num_vars_to_print)  harvest_tabular_format  = new Report_tabular_format();

// NYI   if (CS_format.SS_hydraulic_properties) hydraulic_properties_format= new Soil_profile_tabular_format(i_report_name,i_var_code,i_units_code,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_water_content      )  water_content_format       = new Soil_profile_tabular_format("Soil water content"   ,CSVC_soil_base_water_content                ,UC_m3_m3   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_water_potential    )  water_potential_format     = new Soil_profile_tabular_format("Soil water potential" ,CSVC_soil_base_water_potential              ,UC_J_kg    ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_temperature        )  temperature_format         = new Soil_profile_tabular_format("Soil temperature"     ,CSVC_soil_base_temperature_time_step_avg    ,UC_celcius ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_plant_residue      )  plant_residue_format       = new Soil_profile_tabular_format("Soil plant residue"  ,CSVC_residue_plant_incorporated             ,UC_kg_ha   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_manure_residue     )  manure_residue_format      = new Soil_profile_tabular_format("Soil manure residue" ,CSVC_residue_manure_incorporated            ,UC_kg_ha   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_salinity           )  salinity_format            = new Soil_profile_tabular_format("Soil Salinity"       ,CSVC_soil_base_salinity                     ,UC_dS_m    ,CS_format.profile_spreadsheet_timestep);

   if (CS_format.SS_ammonium           )  ammonium_format            = new Soil_profile_tabular_format("Soil ammonium (NH4-N) elemental nitrogen weight" ,CSVC_soil_N_NH4_amount                      ,UC_kg_ha   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_nitrate            )  nitrate_format             = new Soil_profile_tabular_format("Soil nitrate (NO3-N) elemental nitrogen weight"  ,CSVC_soil_N_NO3_amount                      ,UC_kg_ha   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_denitrification    )  denitrification_format     = new Soil_profile_tabular_format("Soil denitrification elemental nitrogen weight"  ,CSVC_soil_N_denitrification_time_step_sum   ,UC_kg_ha   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_nitrification      )  nitrification_format       = new Soil_profile_tabular_format("Soil nitrification elemental nitrogen weight"    ,CSVC_soil_N_nitrification_time_step_sum     ,UC_kg_ha   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_NH4_mineralization )  mineralization_format      = new Soil_profile_tabular_format("Soil mineralization elemental nitrogen weight"   ,CSVC_soil_N_mineralization_time_step_sum    ,UC_kg_ha   ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_organic_matter     )  organic_matter_format      = new Soil_profile_tabular_format("Organic matter"                                  ,CSVC_organic_matter_percent_time_step_sum   ,UC_percent ,CS_format.profile_spreadsheet_timestep);
   if (CS_format.SS_root_fraction      )  root_fraction_format       = new Soil_profile_tabular_format("Root fraction"                                   ,CSVC_crop_base_root_fraction                ,UC_fraction,CS_format.profile_spreadsheet_timestep);
};
//______________________________________________________________________________
void FMT_to_TDF_Convertor::convert(const char *param_file_name)
{
//   CS_format.directory_qual.create();
//060627   const Common_parameters_directory &format_dir = *CS_format.provide_associated_directory(true);
   Common_parameters_directory format_dir(param_file_name,OPTIONAL_ASSOCIATED_DIRECTORY,true);
   format_dir.set_ext(""); format_dir.create();                                  //111121

   CORN::File_name   daily_tdf_filename("daily.tdf");                               daily_tdf_filename               .set_path(format_dir);
   CORN::File_name   annual_tdf_filename("annual.tdf");                             annual_tdf_filename              .set_path(format_dir);
   CORN::File_name   season_tdf_filename("season.tdf");                             season_tdf_filename              .set_path(format_dir);
   CORN::File_name   harvest_tdf_filename("harvest.tdf");                           harvest_tdf_filename             .set_path(format_dir);
   CORN::File_name   hydraulic_properties_tdf_filename("hydraulic_properties.tdf"); hydraulic_properties_tdf_filename.set_path(format_dir);
   CORN::File_name   ammonium_tdf_filename("ammonium.tdf");                         ammonium_tdf_filename            .set_path(format_dir);
   CORN::File_name   nitrate_tdf_filename("nitrate.tdf");                           nitrate_tdf_filename             .set_path(format_dir);
   CORN::File_name   denitrification_tdf_filename("denitrification.tdf");           denitrification_tdf_filename     .set_path(format_dir);
   CORN::File_name   nitrification_tdf_filename("nitrification.tdf");               nitrification_tdf_filename       .set_path(format_dir);
   CORN::File_name   mineralization_tdf_filename("mineralization.tdf");             mineralization_tdf_filename      .set_path(format_dir);
   CORN::File_name   organic_matter_tdf_filename("organic_matter.tdf");             organic_matter_tdf_filename      .set_path(format_dir);
   CORN::File_name   plant_residue_tdf_filename("plant_residue.tdf");               plant_residue_tdf_filename       .set_path(format_dir);
   CORN::File_name   manure_residue_tdf_filename("manure_residue.tdf");             manure_residue_tdf_filename      .set_path(format_dir);
   CORN::File_name   temperature_tdf_filename("temperature.tdf");                   temperature_tdf_filename         .set_path(format_dir);
   CORN::File_name   water_content_tdf_filename("water_content.tdf");               water_content_tdf_filename       .set_path(format_dir);
   CORN::File_name   water_potential_tdf_filename("water_potential.tdf");           water_potential_tdf_filename     .set_path(format_dir);
   CORN::File_name   salinity_tdf_filename("salinity.tdf");                         salinity_tdf_filename            .set_path(format_dir);
   CORN::File_name   root_fraction_tdf_filename("root_fraction.tdf");               root_fraction_tdf_filename       .set_path(format_dir);

   if (daily_tabular_format)        daily_tabular_format       ->convert(format_file_type,daily_tdf_filename.c_str());
   if (annual_tabular_format)       annual_tabular_format      ->convert(format_file_type,annual_tdf_filename.c_str());
   if (season_tabular_format)       season_tabular_format      ->convert(format_file_type,season_tdf_filename.c_str());
   if (harvest_tabular_format)      harvest_tabular_format     ->convert(format_file_type,harvest_tdf_filename.c_str());

   // NYI also need N reports
   if (hydraulic_properties_format) hydraulic_properties_format->convert(format_file_type,hydraulic_properties_tdf_filename.c_str());
   if (ammonium_format)             ammonium_format            ->convert(format_file_type,ammonium_tdf_filename.c_str());
   if (nitrate_format)              nitrate_format             ->convert(format_file_type,nitrate_tdf_filename.c_str());
   if (denitrification_format)      denitrification_format     ->convert(format_file_type,denitrification_tdf_filename.c_str());
   if (nitrification_format)        nitrification_format       ->convert(format_file_type,nitrification_tdf_filename.c_str());
   if (mineralization_format)       mineralization_format      ->convert(format_file_type,mineralization_tdf_filename.c_str());
   if (organic_matter_format)       organic_matter_format      ->convert(format_file_type,organic_matter_tdf_filename.c_str());
   if (plant_residue_format)        plant_residue_format       ->convert(format_file_type,plant_residue_tdf_filename.c_str());
   if (manure_residue_format)       manure_residue_format      ->convert(format_file_type,manure_residue_tdf_filename.c_str());
   if (temperature_format)          temperature_format         ->convert(format_file_type,temperature_tdf_filename.c_str());
   if (water_content_format)        water_content_format       ->convert(format_file_type,water_content_tdf_filename.c_str());
   if (water_potential_format)      water_potential_format     ->convert(format_file_type,water_potential_tdf_filename.c_str());
   if (salinity_format)             salinity_format            ->convert(format_file_type,salinity_tdf_filename.c_str());
   if (root_fraction_format)        root_fraction_format       ->convert(format_file_type,root_fraction_tdf_filename.c_str());
};
//______________________________________________________________________________
FMT_to_TDF_Convertor::Report_tabular_format::Report_tabular_format
(const char                   *i_report_name
,Report_options               &i_report_options
,int                           i_report_var_count
,report_var_layout_with_graph *i_report_var_opts // array of these
,Units_code                    i_time_step_units
,Record_code                   i_record_type_code
)
: ED_tabular_file_format()
, report_options(i_report_options)
, report_var_count(i_report_var_count)
, report_var_opts(i_report_var_opts)
, report_name(i_report_name)
,record_type_code_used_by_all_records(i_record_type_code)
{
   detail_lines_delineation.time_step_units_enum.set(i_time_step_units);
};
//______________________________________________________________________________
void FMT_to_TDF_Convertor::Report_tabular_format::convert(Format_file_type format_file_type,const char *tdf_filename)
{
   format_file_type_labeled.set(format_file_type /*FILE_TYPE_Excel*/);
   big_endian=false;
   carriage_return_line_feed=true;
   FORTRAN_carriage_control = false;
   header_terminator = 0;
   defined_by="CropSyst fmt_to_tdf convertor (contact rnelson@mail.wsu.edu)";
   // defined_date = already set as default today
#ifdef NYI
check where these are
/*______*/     delimit_mode_labeled.set(DELIMIT_character);
/*______*/
/*______*/     continuous_delimiter = false;
/*______*/     delimiter_space      = false;
/*______*/     delimiter_comma      = true;
/*______*/     delimiter_tab        = false;
/*______*/     delimiter_semicolon  = false;
/*______*/     delimiter_other      = false;
/*______*/     other_delimiter_16   = " "; // N/A

/*______*/     text_quote_mode_labeled.set(DOUBLE_QUOTE);
/*050402_*/    decimal_mark  = ".";
//NYI /*050517_*/    notes = "";
#endif
   records_per_UED_record = 0; // Does not apply to this application we are not importing
//   UED_record_type_code = xxxx;
   // timestep units set in constructor

   // Headers
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // Daily report static
      //101017 Header_field *report_label = new Header_field;
      Metadata_field *report_label = new Metadata_field;     //101017
      report_label->description = "report name label";
      report_label->col_num = 1; //120115col = 0;
      report_label->row_num = 1; //120115row  = 0;
      report_label->field_data_labeled.set(ED_tabular_file_format::Metadata_field::FD_static_text);
      report_label->static_text.assign(report_name);
      // N/A report_label->database_description=1;
      // N/A report_label->UED_scalar_record_code = xxxxx
      // N/A report_label->UED_scalar_variable_code = xxxxx
      // N/A report_label->UED_scalar_units_code = xxxxx
      // N/A report_label->UED_scalar_time_stamp = xxxxx
      // N/A report_label->UED_scalar_precision = xxxxx
      //101017 header_fields_1based
      metadata_fields_1based.append(report_label);                               //101017

   }
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // scenario name
      //101017 Header_field *scenario_name = new Header_field;
      Metadata_field *scenario_name = new Metadata_field;
      scenario_name->description = "scenario name";
      scenario_name->col_num = 1; //120115 col = 0;
      scenario_name->row_num = 2; //120115 row = 1;
      scenario_name->field_data_labeled.set(ED_tabular_file_format::Metadata_field::FD_UED_database_description);
      // N/A scenario_name->static_text.assign(xxxx);
      scenario_name->database_description_index=1;   // Not sure which index is the scenario name
      // N/A scenario_name->UED_scalar_record_code = xxxxx
      // N/A scenario_name->UED_scalar_variable_code = xxxxx
      // N/A scenario_name->UED_scalar_units_code = xxxxx
      // N/A scenario_name->UED_scalar_time_stamp = xxxxx
      // N/A scenario_name->UED_scalar_precision = xxxxx
      //101017 header_fields_1based
      metadata_fields_1based.append(scenario_name);                              //101017
   }
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // soil name
      //101017Header_field *soil_name = new Header_field;
      Metadata_field *soil_name = new Metadata_field;
      soil_name->description = "soil name";
      soil_name->col_num = 1; //120115 = 0;
      soil_name->row_num = 2; //120115 = 1;
      soil_name->field_data_labeled.set(ED_tabular_file_format::Metadata_field::FD_UED_database_description);
      // N/A soil_name->static_text.assign(xxxx);
      soil_name->database_description_index=2;   // Not sure which index is the soil name
      // N/A soil_name->UED_scalar_record_code = xxxxx
      // N/A soil_name->UED_scalar_variable_code = xxxxx
      // N/A soil_name->UED_scalar_units_code = xxxxx
      // N/A soil_name->UED_scalar_time_stamp = xxxxx
      // N/A soil_name->UED_scalar_precision = xxxxx
      //101017 header_fields_1based
      metadata_fields_1based.append(soil_name);                                  //101017
   }
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // location name
      //101017Header_field *location_name = new Header_field;
      Metadata_field *location_name = new Metadata_field;
      location_name->description = "location name";
      location_name->col_num = 1;
      location_name->row_num = 2;
      location_name->field_data_labeled.set(ED_tabular_file_format::Metadata_field::FD_UED_database_description);
      // N/A scenario_name.static_text.assign(xxxx);
      location_name->database_description_index=3;   // Not sure which index is the location_name
      // N/A location_name->UED_scalar_record_code = xxxxx
      // N/A location_name->UED_scalar_variable_code = xxxxx
      // N/A location_name->UED_scalar_units_code = xxxxx
      // N/A location_name->UED_scalar_time_stamp = xxxxx
      // N/A location_name->UED_scalar_precision = xxxxx
      //101017 header_fields_1based
      metadata_fields_1based.append(location_name);                              //101017
   }
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // version label static
      //101017 Header_field *version_label = new Header_field;
      Metadata_field *version_label = new Metadata_field;     //101017
      version_label->description = "version label";
      version_label->col_num = 3; //120115 col = 0;
      version_label->row_num = 1; //120115  = 0;
      version_label->field_data_labeled.set(ED_tabular_file_format::Metadata_field::FD_static_text);
      version_label->static_text.assign("Version:");
      // N/A version_label->database_description=1;
      // N/A version_label->UED_scalar_record_code = xxxxx
      // N/A version_label->UED_scalar_variable_code = xxxxx
      // N/A version_label->UED_scalar_units_code = xxxxx
      // N/A version_label->UED_scalar_time_stamp = xxxxx
      // N/A version_label->UED_scalar_precision = xxxxx
      //101017 header_fields_1based
      metadata_fields_1based.append(version_label);                              //101017
   }
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // version number
      //101017Header_field *version_number= new Header_field;
      Metadata_field *version_number = new Metadata_field;     //101017
      version_number->description = "version number";
      version_number->col_num = 4; //120115 col = 0;
      version_number->row_num = 1; //120115 row = 0;
      version_number->field_data_labeled.set(ED_tabular_file_format::Metadata_field::FD_UED_generating_application);
      version_number->generating_application_var_labeled.set(ED_tabular_file_format::Metadata_field::GEN_APP_version);
      // N/A version_number.static_text.assign();
      // N/A version_number.database_description=1;
      // N/A version_number.UED_scalar_record_code = xxxxx
      // N/A version_number.UED_scalar_variable_code = xxxxx
      // N/A version_number.UED_scalar_units_code = xxxxx
      // N/A version_number.UED_scalar_time_stamp = xxxxx
      // N/A version_number.UED_scalar_precision = xxxxx
      //101017header_fields_1based
      metadata_fields_1based.append(version_number);                             //101017
   }
#ifdef NYI
   I will need to implement a new UED record type
   where I can output additional application information such as
   the build date and the run date etc....
   {  // build date label static
      Header_field *build_date_label = new Header_field;
      build_date_label->description = "build date label";
      build_date_label->col_num = 1; //120115col = 0;
      build_date_label->row_num = 1; //120115row = 0;
      build_date_label->field_data=UD_tabular_file_format::Metadata_field::FD_static_text;
      build_date_label->static_text.assign("Build date:");
      // N/A build_date_label->database_description=1;
      // N/A build_date_label->UED_scalar_record_code = xxxxx
      // N/A build_date_label->UED_scalar_variable_code = xxxxx
      // N/A build_date_label->UED_scalar_units_code = xxxxx
      // N/A build_date_label->UED_scalar_time_stamp = xxxxx
      // N/A build_date_label->UED_scalar_precision = xxxxx
      header_fields_1based.append(build_date_label);
   }
   {  // build date value
   }
   {  // rundate static label
   }
   {  // run date value
   }
#endif

   // column_headers delineation
   switch (format_file_type)
   {  case FILE_TYPE_Excel :
      {  // column headers deliniation
         column_headers_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_intrinsic);
         column_headers_delineation.text_quote_mode_labeled.set(Delineation_layout::DOUBLE_QUOTE);
         column_headers_delineation.start_row_1_based =  6 ;
         // delimiters don't apply to Excel format
         column_headers_delineation.rows        = 4 ;
         column_headers_delineation.units_row_offset   =  4 ; // offset from column header start row
         column_headers_delineation.units_rows  = 1;
         // detail line delineation
         detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_intrinsic);
         detail_lines_delineation.start_row_1_based= 12 ;
         detail_lines_delineation.text_quote_mode_labeled.set(Delineation_layout::DOUBLE_QUOTE);
         // delimiters don't apply to Excel format
      } break;
     case FILE_TYPE_text:
      {  // column headers deliniation
         column_headers_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_character);
         column_headers_delineation.text_quote_mode_labeled.set(Delineation_layout::DOUBLE_QUOTE);
         column_headers_delineation.start_row_1_based   = 1;
         column_headers_delineation.continuous_delimiter = false;
         column_headers_delineation.delimiter_space      = false;
         column_headers_delineation.delimiter_comma      = true;
         column_headers_delineation.delimiter_tab        = false;
         column_headers_delineation.delimiter_semicolon  = false;
         column_headers_delineation.delimiter_other      = false;
         column_headers_delineation.other_delimiter_16   = ' '; // N/A
         column_headers_delineation.decimal_mark         = ".";
         column_headers_delineation.rows                 = 1;
         column_headers_delineation.units_row_offset     =  1; // offset from column header start row
         column_headers_delineation.units_rows           = 1;
         // detail line delineation
         detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_character);
         detail_lines_delineation.start_row_1_based=3;
         detail_lines_delineation.text_quote_mode_labeled.set(Delineation_layout::DOUBLE_QUOTE);
         detail_lines_delineation.continuous_delimiter = false;
         detail_lines_delineation.delimiter_space      = false;
         detail_lines_delineation.delimiter_comma      = true;
         detail_lines_delineation.delimiter_tab        = false;
         detail_lines_delineation.delimiter_semicolon  = false;
         detail_lines_delineation.delimiter_other      = false;
         detail_lines_delineation.other_delimiter_16   = ' '; // N/A
         detail_lines_delineation.decimal_mark  = ".";
      } break;
      // 050830 NYI for other file format.
   }; // switch


   int text_column_start = 1; // 070525
   for (int i = 1; i <= report_options.num_vars_to_print; i++)
   {  // sel_var_code is 1 based.
      // create a new column
      Column *column = new Column;
      CS_UED_variable_code variable_code = report_options.sel_var_code[i];

      column->smart_variable_code = variable_code;

      CORN/*::Tabular_column*/::Data_type data_type = CORN/*::Tabular_column*/::DT_float32;

      // For harvest report, only CSVC_crop_base_planting_date_YD is stored in the UED database
      // we need to create a column in the TDF file that uses this date for the following dates:
      if (variable_code == CSVC_crop_base_planting_date_YMD)      {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_planting_date_YD;      };
      if (variable_code == CSVC_crop_base_planting_date_YMD)      {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_planting_date_YD;      };
      if (variable_code == CSVC_crop_base_emergence_date_YMD)     {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_emergence_date_YD;     };
      if (variable_code == CSVC_crop_base_flowering_date_YMD)     {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_flowering_date_YD;     };
      if (variable_code == CSVC_crop_base_grain_filling_date_YMD) {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_grain_filling_date_YD; };
      if (variable_code == CSVC_crop_base_peak_LAI_date_YMD)      {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_peak_LAI_date_YD;      };
      if (variable_code == CSVC_crop_base_maturity_date_YMD)      {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_maturity_date_YD;      };
      if (variable_code == CSVC_crop_base_harvest_date_YMD)       {data_type = CORN::/*Tabular_column::*/DT_date;column->smart_variable_code =CSVC_crop_base_harvest_date_YD;       };
      if ( (variable_code == CSVC_weather_date_year_day)
         ||(variable_code == CSVC_weather_date_year)
         ||(variable_code == CSVC_weather_date_DOY)
         ||(variable_code == CSVC_weather_date_month)
         ||(variable_code == CSVC_weather_date_DOM)
         )
      {  column->record_date = true;
         data_type =  CORN::/*Tabular_column::*/DT_int16;;
      };

      // (This is not in if block)
      {

            // create a new detail line layout
            for (int rvo = 1 // index 0 is reserved
                ;rvo <= report_var_count
                ;rvo++)
            {  // column header and rows are the same
               if (report_var_opts[rvo].ID == variable_code)
              {
                  if (variable_code == CSVC_crop_base_growth_stage)  column->period = 2;
                  if (variable_code == CSVC_crop_base_name   )       column->period = 1;

                  //NYI column->label = the label is used in dBase like tables, currently not needed but may eventually use for LADSS

                  //            Warning will need to set data type for dates and strings
                  if (column->period >= 0)
                     column->data_type_labeled.set(CORN::/*Tabular_column::*/DT_string);
                  else
                     column->data_type_labeled.set(data_type); //CORN::/*Tabular_column::*/DT_float32);
#ifdef NYI
/*______*/        {DT_char
/*______*/        ,DT_string
/*______*/        ,DT_integer
/*______*/        ,DT_int16
/*______*/        ,DT_int32
/*______*/        ,DT_float
/*______*/        ,DT_float32
/*______*/        ,DT_float64
/*______*/        ,DT_date
/*______*/        };
#endif
            switch (format_file_type)
            {  case FILE_TYPE_Excel :  column->start_1based           = i/*120115 - 1*/; break;
               case FILE_TYPE_text  :
                     if (detail_lines_delineation.delimit_mode_labeled.get() == Delineation_layout::DELIMIT_fixed_width)
                     {
                        column->start_1based           = text_column_start;
                        text_column_start += report_var_opts[rvo].w;  //append the width of this column to the next so we don't override
                     } else
                        column->start_1based           = 0;
                  break;
            };
            column->field_width/*101017 width */          = report_var_opts[rvo].w; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
            column->precision/*101017 precision_16*/       = report_var_opts[rvo].d;
            // column->delimiter = ","  Does not apply, to excel file type
            column->spread_over_columns = false; // does not apply to CropSyst reports
            column->spread_columns         = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)

            // This units description is here only for appearance maching
            // the old CropSyst Excel outputs.
            column->units_caption/*101017units_description*/ = report_var_opts[rvo].u;     // Should show units
//            if (YMD_date) column->units_description == "YYYY/Mmm/DD";


            column->UED_import_to_smart_units_code_enum.set(report_var_opts[rvo].units_code);

//            if (format_file_type== FILE_TYPE_text)
            {  // Actually I will probably use this for all format in the future
               if (column->UED_import_to_smart_units_code_enum.get_int32())  // if not specified derived the units description of units_code
               {
                  column->units_caption = column->UED_import_to_smart_units_code_enum.get_label();
                  if (!column->units_caption.length())
                      column->units_caption= report_var_opts[rvo].u;
               };
            };
            column->smart_record_type = record_type_code_used_by_all_records; //.set(record_type_code_used_by_all_records.get());
            //compose the description in System Data Format
            char description[255]; int descr_row_i = 0;
            description[descr_row_i++] = '"';
            for (int i = 0; i < strlen(report_var_opts[rvo].desc); i++)
            {
               char desc_i = report_var_opts[rvo].desc[i];
               switch (desc_i)
               {
                  case '_' : description[descr_row_i++] = ' ';    break; // under score is used as a non breaking space
                  case ' ' : description[descr_row_i++] = '"';
                             description[descr_row_i++] = ',';
                             description[descr_row_i++] = '"';     break;
                  case '"' : description[descr_row_i++] = '"';  // double quote is represented with two adjacent double quotes in SDF
                             description[descr_row_i++] = '"';     break;
                  default :  description[descr_row_i++] = desc_i; break;
               };
            };
            description[descr_row_i++] = '"';
            description[descr_row_i++] = 0;

            // report_var_opts[rvo].ID

            nat8 var_qualifier = column->smart_variable_code.get_qualifier();
            if (var_qualifier)
            {
               strcat(description,",\"");
               char *qual = "";
               switch (var_qualifier)
               {  //
                  case  UED_average_for_time_step              : qual = "avg"; break;
                  case  UED_maximum_for_time_step              : qual = "max"; break;
                  case  UED_minimum_for_time_step              : qual = "min"; break;
                  case  UED_standard_deviation_for_time_step   : qual = "std"; break;
                  case  UED_total_for_time_step                : qual = "cum(timestep)"; break;
                  case  UED_accumulation_to_date_time          : qual = "accum(to date)"; break;
                  // case  UED_at_time_step :  // the default is to not append at time step qualifier
                  // default : break; // the default is to not append at time step qualifier
               };
               strcat(description,qual);
               strcat(description,"\"");
            };
            column->caption = description;

            column->statistic_labeled.set(value_statistic);
         }; // if variable code
      }; // for rvo
      }

      columns_1based.append(column);
   };
   FOR_EACH_IN(column,Column,columns_1based,each_column)
   {  // Columns
      if (column->caption.length() == 0)
      {
         char label_buffer[20];
         ltoa(column->smart_variable_code.get(),label_buffer,16);
         column->caption.assign(label_buffer);
      };
   } FOR_EACH_END(each_column);

   CORN::VV_File tdf_file(tdf_filename);
   tdf_file.set(*this);

};
//______________________________________________________________________________
#ifdef NYI
FMT_to_TDF_Convertor::Soil_profile_tabular_format::Soil_profile_tabular_format()
{


};
#endif
//______________________________________________________________________________
FMT_to_TDF_Convertor::Soil_profile_tabular_format::Soil_profile_tabular_format
(const char *i_report_name
,UED_variable_code i_var_code
,Units_code i_units_code
,int i_timestep
)
: ED_tabular_file_format()
, report_name     (i_report_name)
, smart_var_code  (i_var_code)
, smart_units_code(i_units_code)
{
//060627   detail_lines_delineation.time_step_units = UT_day;
   detail_lines_delineation.time_step_units_enum.set(UT_day);
   time_step = i_timestep;
};
//______________________________________________________________________________
void FMT_to_TDF_Convertor::Soil_profile_tabular_format::convert(Format_file_type format_file_type,const char *tdf_filename)
{
   format_file_type_labeled.set(format_file_type /*FILE_TYPE_Excel*/);
   big_endian=false;
   carriage_return_line_feed=true;
   FORTRAN_carriage_control = false;
   header_terminator = 0;
   defined_by="CropSyst fmt_to_tdf convertor (contact rnelson@mail.wsu.edu)";
   // defined_date = already set as default today
#ifdef NYI
check where these are

/*______*/     delimit_mode_labeled.set(DELIMIT_character);
/*______*/
/*______*/     continuous_delimiter = false;
/*______*/     delimiter_space      = false;
/*______*/     delimiter_comma      = true;
/*______*/     delimiter_tab        = false;
/*______*/     delimiter_semicolon  = false;
/*______*/     delimiter_other      = false;
/*______*/     other_delimiter_16   = " "; // N/A

/*______*/     text_quote_mode_labeled.set(DOUBLE_QUOTE);
/*050402_*/    decimal_mark  = ".";
//NYI /*050517_*/    notes = "";
#endif

   int text_column_start = 1;  // 070521

   // column_headers delineation
   column_headers_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_intrinsic);
   column_headers_delineation.text_quote_mode_labeled.set(Delineation_layout::DOUBLE_QUOTE);
   column_headers_delineation.start_row_1_based   = 12;
   // delimiters don't apply to Excel format
   column_headers_delineation.rows        = 1;
   column_headers_delineation.units_row_offset   = 1; // offset from column header start row
   column_headers_delineation.units_rows  = 1;

   // detail line delineation
   detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_intrinsic);
   detail_lines_delineation.start_row_1_based=14;
   detail_lines_delineation.text_quote_mode_labeled.set(Delineation_layout::DOUBLE_QUOTE);
   // delimiters don't apply to Excel format

   records_per_UED_record = 0; // Does not apply to this application we are not importing
//   time_step = xxx; // Applies only the Daily reports

//   UED_record_type_code = xxxx;
   // timestep units set in constructor

   // Headers
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // Daily report static
      //101017 Header_field *report_label = new Header_field;
      Metadata_field *report_label = new Metadata_field;
      report_label->description = "report name label";
      report_label->col_num = 2; //120115 col = 1;
      report_label->row_num = 4; //120115 row = 3;
      report_label->field_data_labeled.set(ED_tabular_file_format::Metadata_field/*Header_field*/::FD_static_text);
      report_label->static_text.assign(report_name);
      // N/A report_label->database_description=1;
      // N/A report_label->UED_scalar_record_code = xxxxx
      // N/A report_label->UED_scalar_variable_code = xxxxx
      // N/A report_label->UED_scalar_units_code = xxxxx
      // N/A report_label->UED_scalar_time_stamp = xxxxx
      // N/A report_label->UED_scalar_precision = xxxxx
      //101017header_fields_1based
      metadata_fields_1based        //101017
         .append(report_label);
   }

   // Headers
   if (format_file_type == FILE_TYPE_Excel)   //050830 Currently the text format does not have headers
   {  // units static
      //101017 Header_field *report_label = new Header_field;
      Metadata_field *report_label = new Metadata_field;                         //101017

      report_label->description = "units";
      report_label->col_num = 2;
      report_label->row_num = 5;
      report_label->field_data_labeled.set(ED_tabular_file_format::Metadata_field/*Header_field*/::FD_static_text);
      char units_description[100];
      char units_abbrev[100];
      smart_units_code.compose_description(units_description,units_abbrev);
      report_label->static_text.assign(units_abbrev);
      // N/A report_label->database_description=1;
      // N/A report_label->UED_scalar_record_code = xxxxx
      // N/A report_label->UED_scalar_variable_code = xxxxx
      // N/A report_label->UED_scalar_units_code = xxxxx
      // N/A report_label->UED_scalar_time_stamp = xxxxx
      // N/A report_label->UED_scalar_precision = xxxxx
      //101017 header_fields_1based
      metadata_fields_1based        //101017
         .append(report_label);
   };
/*Not needed, column headers will have layer number
   for (int i = 1; i <= MAX_soil_sublayers; i++)
   {  // sublayer numbers
      Header_field *report_label = new Header_field;
      char sublayer_str[10];
      report_label->description = itoa(i,sublayer_str,10);
      report_label->col = i+5;
      report_label->row = 13;
      report_label->field_data_labeled.set(ED_tabular_file_format::Header_field::FD_static_text);
      report_label->static_text.assign(report_name);
      // N/A report_label->database_description=1;
      // N/A report_label->UED_scalar_record_code = xxxxx
      // N/A report_label->UED_scalar_variable_code = xxxxx
      // N/A report_label->UED_scalar_units_code = xxxxx
      // N/A report_label->UED_scalar_time_stamp = xxxxx
      // N/A report_label->UED_scalar_precision = xxxxx
      header_fields_1based.append(report_label);
   };
*/
#ifdef check_needed
    currently outputting separte columns for the date
   {  // date
      Column *column = new Column;
      column->smart_variable_code = CSVC_weather_date_year_day;
      column->data_type_labeled.set(CORN::/*Tabular_column::*/DT_float32);
      column->start           = 1;
      column->field_width/*101017width*/           = 8; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
      column->precision/*101017 precision_16*/      = 5;
      column->spread_over_columns = false; // does not apply to CropSyst reports
      column->columns         = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)
      column->smart_units_code      = UT_date;
      column->smart_record_type = Record_type_distinguisher_interface::UED_data_set_year_var_units; //.set(record_type_code_used_by_all_records.get());
      column->units_caption/*101017units_description*/ = "YYYY/MM/DD(DDD)";
      column->statistic_labeled.set(value_statistic);
      columns.append(column);
   }

#endif
   {  // Year
      Column *column                = new Column;
      column->caption               = "Date";
      column->record_date           = true;
      column->smart_variable_code   = CSVC_weather_date_year;
      column->data_type_labeled.set(CORN::/*Tabular_column::*/DT_int16);
      column->start_1based          = FILE_TYPE_Excel ? 1 : 1 ;   // Warning this is only for delimited mode need to increment text_column_start with a width
      column->field_width           = 4; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
      column->precision             = 0;
      column->spread_over_columns   = false; // does not apply to CropSyst reports
      column->spread_columns        = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)
      column->UED_import_to_smart_units_code_enum.set(UT_year);
      column->units_caption         = "Year";
      columns_1based.append(column);
   }
   {  // Month
      Column *column                = new Column;
      column->caption               = "Date";
      column->record_date           = true;
      column->smart_variable_code   = CSVC_weather_date_month;
      column->data_type_labeled.set(CORN::DT_int16);
      column->start_1based          = FILE_TYPE_Excel ? 1 : 1 ;   // Warning this is only for delimited mode need to increment text_column_start with a width
      column->field_width           = 4; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
      column->precision             = 0;
      column->spread_over_columns   = false; // does not apply to CropSyst reports
      column->spread_columns        = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)

      column->UED_import_to_smart_units_code_enum.set(UT_month);
//      column->smart_record_type = Record_type_distinguisher_interface::UED_data_set_year_var_units; //.set(record_type_code_used_by_all_records.get());
      column->units_caption = "Month";
//      column->statistic_labeled.set(value_statistic);
      columns_1based.append(column);
   }
   {  // DOM
      Column *column                = new Column;
      column->caption               = "Date";
      column->record_date           = true;
      column->smart_variable_code   = CSVC_weather_date_DOM;
      column->data_type_labeled.set(CORN::DT_int16);
      column->start_1based          = FILE_TYPE_Excel ? 1 : 1 ;   // Warning this is only for delimited mode need to increment text_column_start with a width
      column->field_width           = 4; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
      column->precision             = 0;
      column->spread_over_columns   = false; // does not apply to CropSyst reports
      column->spread_columns        = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)
      column->UED_import_to_smart_units_code_enum.set(UT_day_of_month);
      column->units_caption         = "DOM";
      columns_1based.append(column);
   }
   {  // DOY
      Column *column                = new Column;
      column->caption               = "Date";
      column->record_date           = true;
      column->smart_variable_code   = CSVC_weather_date_DOY;
      column->data_type_labeled.set(CORN::DT_int16);
      column->start_1based          = FILE_TYPE_Excel ? 1 : 1 ;   // Warning this is only for delimited mode need to increment text_column_start with a width
      column->field_width           = 4; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
      column->precision             = 0;
      column->spread_over_columns   = false; // does not apply to CropSyst reports
      column->spread_columns        = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)
      column->UED_import_to_smart_units_code_enum.set(UT_day_of_year);
      column->units_caption         = "DOY";
      columns_1based.append(column);
   }
   {  // root depth column
      Column *column                = new Column;
      column->caption               = "root depth";
      column->units_caption         = "m"; //
      column->smart_variable_code   = CSVC_crop_base_root_depth;
      column->data_type_labeled.set(CORN::DT_float32);
      column->start_1based          = 5;
      column->field_width           = 8; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
      column->precision             = 5;
      column->spread_over_columns   = false; // does not apply to CropSyst reports
      column->spread_columns        = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)
      column->UED_import_to_smart_units_code_enum.set(UC_m);
      column->smart_record_type = Record_type_distinguisher_interface::UED_data_set_year_var_units; //.set(record_type_code_used_by_all_records.get());
      column->statistic_labeled.set(value_statistic);
      columns_1based.append(column);
   }
   for (int i = 1; i <= MAX_soil_sublayers; i++)
   {
      char i_cstr[10];
      itoa (i,i_cstr,10);
      Column *column = new Column;

      column->smart_variable_code = smart_var_code;
      column->smart_variable_code.(i);

            column->caption  = i_cstr;
            column->units_caption =""; //
            column->data_type_labeled.set(CORN::DT_float32);

            switch (format_file_type)
            {  case FILE_TYPE_Excel :  column->start_1based           = i; break;
                  case FILE_TYPE_text  :
                     if (detail_lines_delineation.delimit_mode_labeled.get() == Delineation_layout::DELIMIT_fixed_width)
                     {
                        column->start_1based           = text_column_start;
                        text_column_start += 8;  //append the width of this column to the next so we don't override
                     } else
                        column->start_1based           = 0;
                  break;
            };

            column->field_width           = 8; // Doesn't really apply to spreadsheets, but we may use eventually it for cell formatting
            column->precision      = 5;
            column->spread_over_columns = false; // does not apply to CropSyst reports
            column->spread_columns         = 1;    // This is the number of columns including this column to reserve for spreading data set and layered variables / (not character columns)
            column->UED_import_to_smart_units_code_enum.set(smart_units_code.get());
            column->smart_record_type = Record_type_distinguisher_interface::UED_data_set_year_var_units;
            column->statistic_labeled.set(value_statistic);
      columns_1based.append(column);
   };
   FOR_EACH_IN(column,Column,columns_1based,each_column)
   {  // Columns
      if (column->caption.length() == 0)
      {
         char label_buffer[20];
         ltoa(column->smart_variable_code.get(),label_buffer,16);
         column->caption.assign(label_buffer);
      };
   } FOR_EACH_END(each_column);
   CORN::VV_File tdf_file(tdf_filename);
   tdf_file.set(*this);
};
//______________________________________________________________________________
