/* avgprob.cpp


   This program takes as input a set of files with numbered filenames
   starting with 1.

   The files consist of a table of numbers,  I.e

      45  43  24  1  43
      100 23 543 22 123
      34  23  12 12  34

   There may be any number of spaces between the numbers,
   there must be the same number of columns in all rows of the file.
   The numbers may be integer or floating point representations.
   There may be up to 200 rows.

   The program computes the average and coefficient of variance for a selected
   column of numbers, and optionally the probability.
*/
#include "corn/std/std_fstream.h"
#include "corn/math/compare.h"
#include "corn/format/spreadsheet/biff.h"
#include <math.h>
#include <stdlib.h>
#include "Project/GIS/avgprob.h"
#include "Project/cs_project_editor_params.h"
#include "cs_project.h"
#include "Project/GIS/GIS_params.h"
#include "corn/math/statistical/stats.h"
#include "ued/library/controls.h"
#include "land_unit_output.h"

using namespace std;
//______________________________________________________________________________
Avg_prob_map_tallier::Avg_prob_map_tallier
(const char *dbf_filename
,const CropSyst::Project_editor_parameters &_project_parameters
,const GIS_Project_parameters              *_GIS_project_parameters
,bool _annual_tally
,bool _aggregate_all_sequences_mode)
: Dynamic_int32_indexed_dBase_data_source(dbf_filename,
      "scenario_ID",std::ios::out)  //I appear to be writing here
,project_parameters(_project_parameters)
,GIS_project_parameters(_GIS_project_parameters)
,record_count(0)
,annual_tally(_annual_tally)
,aggregate_all_sequences_mode(_aggregate_all_sequences_mode)
,record_scenario(100,100,0)
{
   // We need to tell the DBF up front what the fields are going to be.
   // Normally this wouldn't be necessary but in the cases where the
   // first scenario does not have a particular crop in the rotation
   // there would be no variables in the first data record when
   // expect structure is called.                                    //091030
   expect_field_for_write("scenario_ID",'N',10,0);
   if (GIS_project_parameters)         // there may not be GIS_project_parameters if not a GIS simulation runn
      expect_field_for_write(GIS_project_parameters->polygon_ID_attribute.c_str(),'N',10,0);
//140222   if (!project_parameters) return;    // Just incase the project parameters are not provided
   for (uint16 report_options_index = 0
       ; report_options_index < (annual_tally ? MAX_YLY_entries : GS_MAX_IDS)
       ; report_options_index++)
   {  nat32 tally_var_code =
         ( annual_tally ?  YLY_report_var_opts[report_options_index].ID : GS_report_var_opts[report_options_index].ID);
            const char *variable_description_abbrv = Cropsyst_smart_variable_code(tally_var_code).get_abbreviation();
      std::string  variable_field_name_suffix(variable_description_abbrv);
      for (int bs = 0; bs < BASIC_STATS_ALLOC; bs++)
      if ((annual_tally ? project_parameters.ANNL_statistics[report_options_index] : project_parameters.GS_statistics[report_options_index]) & (1 << bs))
      {  std::string complete_code(statistic_code_label_table[bs]);
         complete_code.append(variable_field_name_suffix);
         expect_field_for_write(complete_code.c_str(),'N',12,5);
      }
      for (int p10 = 0; p10 < PROB_10_STATS_ALLOC; p10++)
      if ((annual_tally ? project_parameters.ANNL_probability_10[report_options_index] : project_parameters.GS_probability_10[report_options_index]) & (1 << p10))
      {  std::string complete_code(statistic_probablity_10_label_table[p10]);
         complete_code.resize(complete_code.length()-1); // remove the % sign
         complete_code.append(variable_field_name_suffix);
         expect_field_for_write(complete_code.c_str(),'N',12,5);
      }
      for (int p5 = 0; p5 < PROB_5_STATS_ALLOC; p5++)
      if ((annual_tally ? project_parameters.ANNL_probability_5[report_options_index] : project_parameters.GS_probability_5[report_options_index]) & (1 << p5))
      {  std::string complete_code(statistic_probablity_5_label_table[p5]);
         complete_code.resize(complete_code.length()-1); // remove the % sign
         complete_code.append(variable_field_name_suffix);
         expect_field_for_write(complete_code.c_str(),'N',12,5);
      }
   } // for report_options_index
}
//_2009-10-30___________________________________________________________________
Scenario_tally_data_record::Scenario_tally_data_record
(nat32  _scenario_ID                                                             //050920
,const char *_polygon_ID_attribute
,sint32  _polygon_ID                                                             //050630
,nat16  _max_variables
,const nat32  _selected_statistics[]
,const nat32  _selected_probability_10[]
,const nat32  _selected_probability_5[])
: CORN::Data_record        ("polygon_summary")
, scenario_ID(_scenario_ID)                                                      //050920
, polygon_ID_attribute(_polygon_ID_attribute)
, polygon_ID(_polygon_ID)                                                        //050630
, max_variables(_max_variables)
#ifdef TEMP_DISABLED
, selected_statistics      (_selected_statistics)
, selected_probability_10  (_selected_probability_10)
, selected_probability_5   (_selected_probability_5)
#endif
, units_convertor()                                                              //050711
{}
//______________________________________________________________________________
void Scenario_tally_data_record::expect_structure(bool for_write)
{  Data_record::expect_structure(for_write);
   expect_uint32("scenario_ID",scenario_ID,10);                                  //050920
   expect_uint32(polygon_ID_attribute.c_str(),polygon_ID,10);
   FOR_EACH_IN(tally_var,Tally_variable,tally_list,each_tally_var)
   {  nat16 report_options_index = tally_var->report_options_index;
      std::string  variable_field_name_suffix(tally_var->variable_field_name_suffix);
      for (int bs = 0; bs < BASIC_STATS_ALLOC; bs++)
      if (selected_statistics[report_options_index] & (1 << bs))
      {  std::string complete_code(statistic_code_label_table[bs]);
         complete_code.append(variable_field_name_suffix);
         expect_float32(complete_code.c_str(),tally_var->basic_stats[bs]);
      }
      for (int p10 = 0; p10 < PROB_10_STATS_ALLOC; p10++)
      if (selected_probability_10[report_options_index] & (1 << p10))
      {  std::string complete_code(statistic_probablity_10_label_table[p10]);
         complete_code.resize(complete_code.length()-1); // remove the % sign
         complete_code.append(variable_field_name_suffix);
         expect_float32(complete_code.c_str(),tally_var->prob_10_stats[p10]);
      }
      for (int p5 = 0; p5 < PROB_5_STATS_ALLOC; p5++)
      if (selected_probability_5[report_options_index] & (1 << p5))
      {  std::string complete_code(statistic_probablity_5_label_table[p5]);
         complete_code.resize(complete_code.length()-1); // remove the % sign
         complete_code.append(variable_field_name_suffix);
         expect_float32(complete_code.c_str(),tally_var->prob_5_stats[p5]);
      }
   } FOR_EACH_END(each_tally_var)
   structure_defined = true;                                                     //120314
}
//_2005-05-05_________________________________________________expect_structure_/
Tally_variable::Tally_variable
(UED_variable_code _variable_code
,uint16 _report_options_index)
//180408: Statistical_data_set()
: CORN::Statistical_sample_with_dataset<float32,float32,float32>()           //180408
, variable_code(_variable_code)
, report_options_index(_report_options_index) // will be assigned later
{  for (int i = 0; i < BASIC_STATS_ALLOC; i++)
   {  basic_stats    [i] = 0;
      prob_10_stats  [i] = 0;
      prob_5_stats   [i] = 0;
   }
}
//_2005-07-05___________________________________________________________________
void Tally_variable::clear()
{  for (int i = 0; i < BASIC_STATS_ALLOC;    i++)  basic_stats[i] = 0;
   for (int i = 0; i < PROB_10_STATS_ALLOC;  i++)  prob_10_stats[i] = 0;
   for (int i = 0; i < PROB_5_STATS_ALLOC;   i++)  prob_5_stats[i] = 0;
   resize(0);
}
//_2005-05-05___________________________________________________________________
void Tally_variable::recompute()                                  modification_
{
   //180408 Statistical_data_set
   CORN::Statistical_sample_with_dataset<float32,float32,float32>                //180408
   ::recompute();
     basic_stats[0] = get_current();  // Doesn't really have meaning in this context.
     basic_stats[1] = get_sum();
     basic_stats[2] = get_mean();
     basic_stats[3] = get_standard_deviation();
     basic_stats[4] = get_coefficient_of_variation();
     basic_stats[5] = get_sum_of_squares();
     basic_stats[6] = get_median();
     basic_stats[7] = get_min();
     basic_stats[8] = get_max();
     basic_stats[9] = get_count();

     prob_10_stats[0] = get_probability_value(10);
     prob_10_stats[1] = get_probability_value(20);
     prob_10_stats[2] = get_probability_value(30);
     prob_10_stats[3] = get_probability_value(40);
     prob_10_stats[4] = get_probability_value(50);
     prob_10_stats[5] = get_probability_value(60);
     prob_10_stats[6] = get_probability_value(70);
     prob_10_stats[7] = get_probability_value(80);
     prob_10_stats[8] = get_probability_value(90);
     prob_10_stats[9] = get_probability_value(100);

     prob_5_stats[0] = get_probability_value(5);
     prob_5_stats[1] = get_probability_value(15);
     prob_5_stats[2] = get_probability_value(25);
     prob_5_stats[3] = get_probability_value(35);
     prob_5_stats[4] = get_probability_value(45);
     prob_5_stats[5] = get_probability_value(55);
     prob_5_stats[6] = get_probability_value(65);
     prob_5_stats[7] = get_probability_value(75);
     prob_5_stats[8] = get_probability_value(85);
     prob_5_stats[9] = get_probability_value(95);
}
//_2005-05-05___________________________________________________________________
void Scenario_tally_data_record::append_value
(UED_variable_code variable_code,float32 value,Units_code value_units,bool annual_tally)
{  //                      find/create tally indexed by variable code,rotation number
   Tally_variable *tally_var = (Tally_variable *)tally_list.find(variable_code);
   if (!tally_var) // create a tally variable if necessary.
   {  nat32 report_options_index = 0;
      for (int i = 0; i < (annual_tally ? MAX_YLY_entries : GS_MAX_IDS) ; i++)
      {  UED_variable_code tally_var_code =
            (annual_tally ? YLY_report_var_opts[i].ID : GS_report_var_opts[i].ID);
         if (tally_var_code == variable_code)
             report_options_index = i;
      }
      if (report_options_index)
      {  tally_var = new Tally_variable(variable_code,report_options_index);
         tally_list.append(tally_var);
      }
      else
         cerr << "Could not find report options for matching variable code" << endl;
   }
   //  append value to tally stats.
   Units_code preferred_units
   = annual_tally
   ? YLY_report_var_opts[tally_var->report_options_index].units_code
   : GS_report_var_opts[tally_var->report_options_index].units_code;
   float32 preferred_value = 0;
   bool converted  = units_convertor.convert(value,value_units,preferred_value,preferred_units);
   if ((value_units > UT_time) && (value_units < UT_END_TIME_CODES))
   {  // if it is a date then convert get doy and use that as the preferred value
      CORN::Date_time_64 date64(value);
       preferred_value = date64.get_DOY();
   }
   tally_var->append(preferred_value);
}
//__2005-07-11__2005-11-10______________________________________________________
bool Scenario_tally_data_record ::set_start()
{  // compute stats and move to write fields
   FOR_EACH_IN(tally_var,Tally_variable,tally_list,each_tally_var)
   {  tally_var->recompute();  // do the statistics
   } FOR_EACH_END(each_tally_var)
   return CORN::Data_record ::set_start();                                       //161023
}
//_2005-05-07 __________________________________________________________________
bool Avg_prob_map_tallier::tally_UED_file
(const char *UED_filename
,nat32 scenario_ID                                                               //050920
,int32 polygon_ID // signed because negative values indicate offsite values
,const char *crop_description                                                    //050708
,std::string &status_log)                                                        //091105
// this is when separating by crop.
{
   int data_rows = 0;
   int data_cols = 0;
   float32 value1 = 0.0;
   Scenario_tally_data_record scenario_tally                                     //050920
      (scenario_ID
      ,GIS_project_parameters->polygon_ID_attribute.c_str()
      ,polygon_ID
      ,(annual_tally ? MAX_YLY_entries : GS_MAX_IDS)                // This is the maximum number of variables that are reported (I.e.  GS_MAX_IDS MAX_YLY_entries
      ,(annual_tally ? project_parameters.ANNL_statistics      : project_parameters.GS_statistics)
      ,(annual_tally ? project_parameters.ANNL_probability_10  : project_parameters.GS_probability_10)
      ,(annual_tally ? project_parameters.ANNL_probability_5   : project_parameters.GS_probability_5));
   //140222 UED_indexed_database ued_file(UED_filename,false);
   UED::Database_file_indexed ued_file(UED_filename,std::ios_base::in);          //140222


   CORN::Datetime64 earliest_datetime64 = ued_file.get_earliest_date_time(UED_FOR_ALL_RECORD_TYPES,UED_FOR_ALL_VARIABLES);
   Date_time_64 earliest_date(earliest_datetime64);
   Year first_year_after_equilibrate = earliest_date.get_year() + GIS_project_parameters->equilibrate_years;
   ued_file.goto_BOF();
   for (UED::Binary_data_record *data_rec = ued_file.goto_next_data_record()     //140222
         ; data_rec
         ; data_rec = ued_file.goto_next_data_record())
   {  // for each data record in each database
      UED_variable_code variable_code =  data_rec->get_variable_code();
      // Will want to output the units to some status file so user knows what he is importing to ArcGIS
      Units_code value_units  = data_rec->get_units_code();
      bool tally_this_variable = false;
      for (int i = 0; i < (annual_tally ? MAX_YLY_entries : GS_MAX_IDS) ; i++)      //050705
      {  UED_variable_code tally_var_code =
            (annual_tally ? YLY_report_var_opts[i].ID : GS_report_var_opts[i].ID);
         if (variable_code == tally_var_code)
            tally_this_variable = scenario_tally.selected_statistics[i] ||scenario_tally.selected_probability_10[i] || scenario_tally.selected_probability_5[i];
      }
      if (tally_this_variable)
      {  value1 = 0.0;
         for (int value_i = 0; value_i < data_rec->data_values_get_count(); value_i++)
         {  //  for each time step/value in the data record  (for each data value index of the data record)
            CORN::Datetime64 date_time_i = data_rec->get_date_time_for_index(value_i);
            Date_time_64 date_time_64_i(date_time_i);
            CORN::Quality datum_attribute(measured_quality);                     //101018
            value1 = data_rec->get_value(datum_attribute,date_time_i);
            if (date_time_64_i.get_year() >= first_year_after_equilibrate)
            {  if (annual_tally)   // append all values in annual mode
                  scenario_tally.append_value(variable_code,value1,value_units,annual_tally);   //050920
               else
               {  // check that database has any rotation periods matching this date   //050120
                  // if so that must be the rotation entry
                  const UED::Period_record *crop_season_period = ued_file.get_period //140222_041011
                  (/*consider_options*/ UED_period_start_date_option|UED_period_end_date_option|UED_period_application_code_option/*8|UED_period_index_option|UED_period_variable_code_option*/|UED_period_variable_code_option
                  ,/*at_date         */ date_time_i
                  ,/*application code*/ GROWING_SEASON_PERIOD
                  ,/*enumeration     */ 0
                  ,/*index           */ 0
                  ,/*variable_code   */ CSVC_crop_base_name
                  );
                  if (crop_season_period) // append value only for matching crop cycle index
                     if (crop_season_period->get_text() ==crop_description)
                     {
//if (crop_season_period->get_text() == "Barley (winter)")
//cout << crop_description << '|' << crop_season_period->get_text() << endl;

if ((value1 > 99999999.0) || (value1 < -99999999.0))
{  char buffer[1000];
//   ;
//   Ustring status(buffer);
   std::string status(Cropsyst_smart_variable_code(variable_code).get_abbreviation());
   status.append(" Value out of range:");
//   status.append(ftoa(value));
   status.append(" This may be because the variable was not properly initialized or accumulated in CropSyst\n");
   if (status_log.find(status) == std::string::npos)
      status_log.append(status);
//   cout <<  << value <<  << endl;;
   value1 = 0;
}

                        scenario_tally.append_value(variable_code,value1,value_units,annual_tally); //050920
                     }
               }
            } // else we exclude the first equilibrate years
         }
      } // end for each time step value
   } // end for each data record
   {  // Identify variable code names
      for (int i = 0; i < (annual_tally ? MAX_YLY_entries : GS_MAX_IDS) ; i++)
      {  UED_variable_code tally_var_code =
            (annual_tally ? YLY_report_var_opts[i].ID : GS_report_var_opts[i].ID);
         Tally_variable *tally_var = (Tally_variable *)scenario_tally.tally_list.find(tally_var_code);  // ID is now UED variable code
         if (tally_var)
         {
/*NYI
I haven't yet output CropSyst variable codes to the UED file, now just using abbreviation table
                        std::string variable_description(ued_file.get_variable_description(tally_var_code));
                        char variable_description_abbrv[50];
                        shrink_to(8,variable_description.c_str(),variable_description_abbrv);
*/
            const char *variable_description_abbrv = Cropsyst_smart_variable_code(tally_var_code).get_abbreviation();
            tally_var->variable_field_name_suffix =variable_description_abbrv;
            tally_var->report_options_index = i;   // index to the
         }
      }
   }
   goto_EOF(); // Make sure the record is committed                              //010130
   scenario_tally.set_position(0);                                               //051110
      // make sure the record is appended (because we are reusing it).
   set(scenario_tally);                                                          //050920
   record_count = get_record_number();                                           //010130
   record_scenario.set(record_count,scenario_ID);                                //091019
   return true;                                                                  //010608
}
//______________________________________________________________________________

#define command_line_mode  7
//#define single_file_mode   3
#define interactive_mode   1
#define command_line_mode_single_file 4

#ifdef STANDALONE_AVGPROB

std::string column_headers[200];
std::string units[200];
//______________________________________________________________________________
int32 get_largest_file_num(CORN_filename &pattern)                               //140203
{
  //read all the file names in the current directory
  //if the filename is a number std::string
  //   convert the filename to a number.
  //   largest = max(largest,filenumber);

   int32 largest = 0;                                                            //140203
   struct ffblk file_block;
   int file_found_status = findfirst(pattern.c_str(),&file_block,0);
   while (file_found_status == 0)
   {  if (isdigit(file_block.ff_name[0]))  // should provide a more robust check if the filename is a number
      {  int32 file_num = atol /*140203 atoi*/(file_block.ff_name);              //140203
         largest = std::max<int32>(largest,file_num);                            //140203
         //cout << file_num << '/' << largest << endl;
         pattern.set(file_block.ff_name);
      }
      file_found_status = findnext(&file_block);
   }
   return largest;
}
//______________________________________________________________________________
int get_tally_column(CORN_filename filename)
{
   //open the spreadsheet file
   //list all the column headers entries
   //  note that the spreadsheet columns are index by 0
   //
   //prompt the user for the column number indexed by 1
   //
   //close the spreadsheet file

   int num_cols = 0;
   biff_file SS_file(filename.c_str());                                          //990607
   if (SS_file.good())
   {  while (!SS_file.eof())
      { SS_file.read_record();
         if (( SS_file.data_type == Common_spreadsheet_file::type_str) &&
           (SS_file.row >= 4) && (SS_file.row <= 9))
         {  num_cols = max(num_cols,SS_file.col+1);
            column_headers[SS_file.col].append(" ");
            column_headers[SS_file.col].append(SS_file.str_value);
            if (SS_file.row == 9)
               units[SS_file.col].assign(SS_file.str_value);
         }
      }
   }
   if (num_cols)
   {  int sel_col = 0;
      while ((sel_col < 1) || (sel_col > num_cols))
      {  int col;
         for (col = 0; col <= num_cols; col++)
            cout << (col+1) << column_headers[col] << endl;
         cout << "Enter column number to tally (enter 0 to relist)" << endl;
         cin >> sel_col;
      }
      return sel_col;
   }
   return 0;
}
//______________________________________________________________________________
char  extension[10];
//______________________________________________________________________________
int main(int argc, char *argv[])
{
   int tally_column = -1;
   std::string ID_name;
   std::string sim_ID;
   std::string column_ID;
   CORN_filename single_filename;
   int HRV_report_crop_variable_column;                                          //990507
   int mode = argc;

   if ((mode != command_line_mode) &&
       (mode != command_line_mode_single_file) &&
       (mode != interactive_mode))
   {
    printf("This program takes as input a set of CropSyst WKx spreadsheet output files\n");
    printf("with numbered filenames starting with 1.\n\n");
    printf("A file is generated for the averages and coefficient of variance for one of the columns.\n\n");
    printf("The output file is a dBase file with the following data:\n\n");
    printf("   For every input file, one record is generated in the output file\n");
    printf("   containing the  input file number, the average, the C.V., the\n\n") ;
    printf("   probablity for 10, 20, ... 90 and 95%\n");
    printf("the output file will have a .DBF extension\n");

    printf("This program requires the following arguments,\n");
    printf("1. The extension of the input files (ie:  .WKH)\n");
    printf("2. The name of the Arc/Info table polygon _ID field (I.e. MYMAP_ID)\n");
    printf("3. A code identifying the simulation run (4 chars)\n");
    printf("4. A code identifying the column being tallied (4 chars).\n");
    printf("5. The number of the column to be tallied (indexed from 1).\n");
    printf("6. Number of data record lines to skip (usually 0) (I.e. # of years for CropSyst to equilibrate)");

    printf("or\n");
    printf("1. The filename of a single file to tally (with extension)\n");
    printf("2. The number of the column to be tallied.\n");
    printf("2. The number of the column containing the crop filename.\n");
    exit(1);
   }
   switch (mode)
   {
     case command_line_mode :
       strcpy(extension,   argv[1]);
       ID_name.assign(     argv[2]);
       sim_ID.assign(      argv[3]);
       column_ID.assign(   argv[4]);
       tally_column = atoi(argv[5]);
     break;
     case command_line_mode_single_file :                                        //990607
          single_filename.assign(argv[1]);                                       //990607
          tally_column = atoi(argv[2]);                                          //990607
          HRV_report_crop_variable_column = atoi(argv[3]);
     break;
     case interactive_mode :
        cout << "Enter the extension of the input files (XLD XLY XLH no dot)" << endl;
        cin  >> extension;
        cout << "Enter the name of the polygon _ID field" << endl;
        cin  >> ID_name;
        cout << "Enter a code identifying the simulation run (4 chars)" << endl;
        cin  >> sim_ID;
        cout << "Enter a code identifying the column being tallied (4 chars)." << endl;
        cin  >> column_ID;
        cout << "Number of data record lines to skip (usually 0) (I.e. # of years for CropSyst to equilibrate)" << endl;
        cin >> record_skip;
     break;
   }
   CORN_filename pattern("*.*");
   pattern.set_ext(extension);
   int32 largest_file_num = get_largest_file_num(pattern);                       //140203
   // get_largest_file_num, returns the last filename found
   if (mode == interactive_mode)
      tally_column = get_tally_column(pattern);
   CORN::OS::File_name_logical output_filename(sim_ID,"DBF");
   Avg_prob_map_tallier tallier(output_filename,ID_name,record_skip);
   tallier.add_variable_option_set(column_ID,tally_column,
        MASK_average
        | MASK_CV
        | MASK_prob10
        | MASK_prob20
        | MASK_prob30
        | MASK_prob40
        | MASK_prob50
        | MASK_prob60
        | MASK_prob70
        | MASK_prob80
        | MASK_prob90
        | MASK_prob95
        | MASK_sum                                                               //000223
        );
   if (mode == command_line_mode_single_file)
   {  CORN_association_list separate_crop_tallies;
      int multiple_crops = identify_different_crops(
                   single_filename
                  ,HRV_report_crop_variable_column,separate_crop_tallies);
      Avg_prob_map_tallier *single_H_tally_file = new Avg_prob_map_tallier
      (
      single_filename
      , ""/*polygon_ID_attribute*/,0 );

      if (multiple_crops > 1)
      {
                 for (separate_crop *crop_tally = (separate_crop *)separate_crop_tallies.move_to_head()
                     ; crop_tally
                     ; crop_tally = (separate_crop *)separate_crop_tallies.move_to_next())
                 {
                    // create a unique H_tally_file for each crop with the same properties of the generic H_tally_file
                    std::string short_crop_name;
                    shrink_to(8,crop_tally->crop_name,short_crop_name);
                    CORN_filename crop_tally_filename(single_filename);
                    crop_tally_filename.set_file(short_crop_name.c_str());
                    crop_tally->crop_tally_file = new Avg_prob_map_tallier(crop_tally_filename,*single_H_tally_file);
                    crop_tally->crop_tally_file->goto_BOF();
                 }
      }
      if (multiple_crops > 1)
                 for (separate_crop *crop_tally = (separate_crop *)separate_crop_tallies.move_to_head()
                     ; crop_tally
                     ; crop_tally = (separate_crop *)separate_crop_tallies.move_to_next())
                  crop_tally->crop_tally_file->tally_spreadsheet_file(single_filename
                     ,0/*polygon_ID*/,crop_tally->crop_name);
      else
                single_H_tally_file->tally_spreadsheet_file(single_filename
                     ,0/*polygon_ID*/,std::string(""));
   }
   else
   for (int32 ID = 1; ID <= largest_file_num; ID++)
   {  char ID_str[10];
      CORN_int32_to_str(ID,ID_str,10);                                           //140203
      CORN_filename id_WKx_filename(ID_str,extension);
      CORN_association_list separate_crop_tallies;
      if (id_WKx_filename.exists())
      {  cout << id_WKx_filename << endl;
         tallier.tally_spreadsheet_file((CORN_filename)id_WKx_filename,ID,std::string(""));
      }
   }
   return(0);
}
#endif
//______________________________________________________________________________
bool Avg_prob_map_tallier::duplicate_scenario_record(int32 scenario_to_duplicate, nat32 as_scenario)
{  for (nat32 i = 1; i <=record_count; i++)
      if (record_scenario.get(i,false) == scenario_to_duplicate)
      {  goto_record(i);
         Scenario_tally_data_record scenario_tally_to_copy
            (scenario_to_duplicate
            , GIS_project_parameters->polygon_ID_attribute.c_str()
            ,scenario_to_duplicate     // was polygon_to_duplicate
            // 050920 Warning need to check this second parameter,
            // for simple GIS, the scenario ID is the same as the polygon ID
            // for aggregated GIS then the Polygon ID is simply copied.
            ,(annual_tally ? MAX_YLY_entries : GS_MAX_IDS)                // This is the maximum number of variables that are reported (I.e.  GS_MAX_IDS MAX_YLY_entries
            ,(annual_tally ? project_parameters.ANNL_statistics      : project_parameters.GS_statistics)
            ,(annual_tally ? project_parameters.ANNL_probability_10  : project_parameters.GS_probability_10)
            ,(annual_tally ? project_parameters.ANNL_probability_5   : project_parameters.GS_probability_5));
         get(scenario_tally_to_copy);
         if (!aggregate_all_sequences_mode)
            scenario_tally_to_copy.polygon_ID = as_scenario;
         scenario_tally_to_copy.scenario_ID = as_scenario;
         append(scenario_tally_to_copy);
         return true;
      }
   return false;
}
//_2005-09-20________________________________________duplicate_scenario_record_/
//060706 759 lines
//140222 596

