#ifdef USE_PCH
#include "simulation/CropSyst_sim_pch.h"
#else
#  include <corn/strconv.h>
#  include <corn/format/biff.h>
#  include <corn/os.h>
#  include "soil_param.h"
#  include "cs_paths.h"
#endif
#pragma hdrstop
#define template_simulation_filename active_scenario_filename_rel
#include "arccs_coop.h"
#include "analysis/pat.h"

#  include "arccs_table.h>
#  include <corn/format/dbase_datasrc.h>
#ifdef OWL_API
#include <corn/rui/bsysemod/completed.h>
#endif
bool  keep_temporary_files = true;                                               //981110

extern int identify_different_crops                                              //980721
(const CORN::File_name &XLH_filename                                             //980721
,int crop_name_column
,Association_list &separate_crop_tallies);                                       //980721
//______________________________________________________________________________
ArcCS_cooperator_simulation::ArcCS_cooperator_simulation()
:GIS_project_parameters()                                                        //010112
{  for (int h = 0; h < HRV_MAX_IDS ; h++) harvest_tally_options[h] = 0;          //001002
   for (int y = 0; y < YLY_MAX_IDS ; y++) annual_tally_options [y] = 0;          //001002
   for (int16 eq = 0; eq < equivalences_allocate; eq++)                          //981218
   {  record_equivalences[eq] = 0;                                               //981218
      polygon_equivalences[eq] = equiv_polygon_not_present;                      //981218
   }                                                                             //010130
}
//_1999-04-17___________________________________________________________________
void ArcCS_cooperator_simulation::expect_structure(bool for_write)
{  GIS_project_parameters::expect_structure();
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_harvest);                                           //000925
   char var_code_str[10];                                                        //001002
   for (int i = 1; i < HRV_MAX_IDS; i++)
   {  CORN_uint32_to_str(HRV_report_var_opts[i].ID,var_code_str,16);             //001002
      expect_uint16(var_code_str,harvest_tally_options[i],16);                   //001002
   }
   set_current_section(LABEL_annual);
   for (int i = 0; i < YLY_MAX_IDS; i++)
   {  CORN_uint32_to_str(YLY_report_var_opts[i].ID,var_code_str,16);             //001002
      expect_uint16(var_code_str,annual_tally_options[i],16);                    //001002
   }
   structure_defined = true; //120314
}
//______________________________________________________________________________
int ArcCS_cooperator_simulation::identify_different_crops
(const CORN::File_name &XLH_filename                                             //980721
,int crop_name_column
,Association_list &separate_crop_tallies)                                        //980721
{  Biff_file  infile(XLH_filename.c_str());
   if (infile.good())
   {
      while (!infile.eof())
      {
         bool process_this_row = true;
         infile.read_next(Common_spreadsheet_file::data_cell_record);
         int data_row = infile.row - 11;  // FIRST_DATA_LINE_ROW
         int data_col = infile.col + 1;  // columns are 0 indexed in spreadsheet, but 1 indexed in SRO and tally options

         if ((infile.data_type == Common_spreadsheet_file::type_str)
           && (data_col == crop_name_column)
           && (data_row > 11))  // <- Check this
         {
            CORN_string crop_name(infile.str_value);
            if (!separate_crop_tallies.find(infile.str_value))
               separate_crop_tallies.append(new separate_crop(crop_name));
         }
      }
   }
   return separate_crop_tallies.count();;
}
//_1998-07-21___________________________________________________________________
void ArcCS_cooperator_simulation::donatelli_analysis_variable_selection()
{
   // This method makes sure that the cropsyst output variables
   // needed for the analysis are selected in the report format.
   Report_formats_parameters report_format;                                      //010112
   VV_File report_format_file(report_format_filename_rel.c_str());               //030220
   report_format_file.get(report_format);                                        //010112
   report_format.require_variable(YLY,YLY_year);
   report_format.require_variable(YLY,YLY_soil_water_drainage);
   report_format.require_variable(YLY,YLY_nitrogen_leached_total);
   report_format.require_variable(YLY,YLY_total_mineralization);
   report_format.require_variable(YLY,YLY_ET_pot);
   report_format.require_variable(YLY,YLY_irrigation);

   report_format.require_variable(HRV,HRV_maturity_date_YD);
   report_format.require_variable(HRV,HRV_planting_date_YD);
   report_format.require_variable(HRV,HRV_yield);
   report_format.require_variable(HRV,HRV_soil_water_drainage);
   report_format.require_variable(HRV,HRV_nitrogen_leached_total);
   report_format_file.set(report_format);
}
//_1999-11-20___________________________________________________________________
void ArcCS_cooperator_simulation::donatelli_analysis
(TApplication *app
,GUI_progress_bar *progress_gauge)                                               //010608
{  setup_common_analysis_structures(true);
   CORN::File_name soil_template_path_file(template_sim->soil_filename);         //980717
   Report_formats_parameters format;                                             //010112
   VV_File report_formats_file(report_format_filename_rel.c_str());              //010112
   report_formats_file.get(format);                                              //010112

   // Once all the simulations have been run we can perform          //981217
   // Marcello's analysis:
   // The run of this should be an ARCCS simulation option (check box)
   average_years
      (format  //  report format
      ,default_model_options.starting_date.get_year()
      ,  default_model_options.ending_date.get_year()
       - default_model_options.starting_date.get_year()
      ,template_sim->years_in_rotation
      ,record_equivalences
      ,polygon_equivalences
      ,*pat);
}
//______________________________________________________________________________
 void ArcCS_cooperator_simulation::setup_common_analysis_structures
 (bool equivalence_optimization)
 {
   if (!pat && equivalence_optimization)
   { pat = new Polygon_attribute_table                                          //981217
       (coverage_PAT_filename.c_str()
       ,polygon_ID_attribute.c_str()
       ,soil_attribute.c_str()
       ,steepness_attribute.c_str()
       ,init_PAW_attribute.c_str()
       ,init_NO3_attribute.c_str()
       ,weather_attribute.c_str()
       ,rotation_attribute.c_str()
       ,record_equivalences
       ,polygon_equivalences);
    }
    // base setup_common_analysis_structures must be called last:
    GIS_project_parameters::setup_common_analysis_structures();
}
//_1998-12-18___________________________________________________________________
void ArcCS_cooperator_simulation::load_previous_run
(const File_name &override_dbase_fname)
{  Data_source_dBase override_dbase(override_dbase_fname.c_str());               //010129
   for (bool went = override_dbase.goto_BOF()
        ; went
        ;went = override_dbase.goto_next())
   {  Simulation_override_record *override_record = new Simulation_override_record();
      override_dbase.get(*override_record);
      unique_sim_combinations.append(override_record);
   }
}
//______________________________________________________________________________
void ArcCS_cooperator_simulation::run
(bool &continue_run
,bool      equivalence_optimization
,TApplication *app
,GUI_progress_bar *progress_gauge)
{}
//______________________________________________________________________________
void ArcCS_cooperator_simulation::copy_results_files(int32 from_polygon_ID,int32 to_polygon_ID)
{  char from_polygon_ID_str[10];                                                 //980902
   CORN_int32_to_str(from_polygon_ID,from_polygon_ID_str,10);                    //010514
   CORN::File_name from_results_filename("results\\xxx.xlh");
   if (from_polygon_ID < 0)
         from_results_filename.set("temp.xlh");
   else  from_results_filename.set_file(from_polygon_ID_str);                    //980902
   char to_polygon_ID_str[10];                                                   //980902
   CORN_int32_to_str(to_polygon_ID,to_polygon_ID_str,10);                        //140203_980902
   CORN::File_name to_results_filename("results\\xxx.xlh");
   to_results_filename.set_file(to_polygon_ID_str);                              //980902
   OS_copy_file(from_results_filename.c_str(),to_results_filename.c_str());
   from_results_filename.set_ext(".xly");
   to_results_filename.set_ext(".xly");
   OS_copy_file(from_results_filename.c_str(),to_results_filename.c_str());
   from_results_filename.set_ext(".xls");
   to_results_filename.set_ext(".xls");
   OS_copy_file(from_results_filename.c_str(),to_results_filename.c_str());
}
//_2001-05-14___________________________________________________________________
void ArcCS_cooperator_simulation::compute_relevent_soil_WHC()
{  // Create a Spreadsheet file containing notes about the exempler polygons
   CORN::File_name notes_filename(get_relative_filename("notes","xls"));         //030220
   Biff_file notes_sheet(notes_filename.c_str(),0,1000,0,20);
   notes_sheet.write_label_cell(0,0,Common_spreadsheet_file::CSS_justify_left,"Exemplar");
   notes_sheet.write_label_cell(3,0,Common_spreadsheet_file::CSS_justify_left,"Water holding capacity(mm)");
   notes_sheet.write_label_cell(0,1,Common_spreadsheet_file::CSS_justify_left,"polygon_ID");
   notes_sheet.write_label_cell(1,1,Common_spreadsheet_file::CSS_justify_left,"soil");
   notes_sheet.write_label_cell(2,1,Common_spreadsheet_file::CSS_justify_left,"depth (m)");
   notes_sheet.write_label_cell(3,1,Common_spreadsheet_file::CSS_justify_left,"profile");
   notes_sheet.write_label_cell(4,1,Common_spreadsheet_file::CSS_justify_left,"1-meter depth");
   notes_sheet.row = 2;
   setup_common_analysis_structures(true);
   bool at_eof = !pat->goto_first();                                             //981218
   while (!at_eof)                                                               //981218
   {  Polygon_attribute_data_record  polygon_attr_DR                             //030224
      (polygon_ID_attribute.c_str()
      ,soil_attribute.c_str()
      ,steepness_attribute.c_str()
      ,init_PAW_attribute.c_str()
      ,init_NO3_attribute.c_str()
      ,weather_attribute.c_str()
      ,rotation_attribute.c_str());
      pat->get(polygon_attr_DR);

      int16 polygon_ID = polygon_attr_DR.polygon_ID;                             //030224
      int32 record_num = pat->get_record_number();
      if (polygon_equivalences[record_num] == -1)
      {
         Smart_soil_parameters soil;
         VV_File soil_file(polygon_attr_DR.get_record_soil_filename(template_sim->soil_filename.c_str()));
         soil_file.get(soil);
         // determine if the corresponding soil is high water holding capacity.
         float64  WHC_1meter = soil.get_water_holding_capacity(1.0);
         notes_sheet.write_integer(polygon_ID ,6);                               //030224
         notes_sheet.write_string(Common_spreadsheet_file::CSS_justify_left,polygon_attr_DR.soil_code.c_str());   //030224
         notes_sheet.write_float(soil.get_profile_depth(),8,3);
         notes_sheet.write_float(m_to_mm(soil.get_water_holding_capacity()),8,3); // profile WHC
         notes_sheet.write_float(m_to_mm(WHC_1meter),8,3);
         notes_sheet.endl();
      }
      at_eof = !pat->goto_next();
   }
}
//_1998-12-18___________________________________________________________________

