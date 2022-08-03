#ifndef FMTREC_H
#define FMTREC_H

/* The new report file format uses the INI file format
[options]
format=1
[daily]
header=1
column_heads=1
paginate=1
separate_years=1
lines=60
timestep=1
variables=1,2,3,4,5,....
[yearly]

[harvest]

[profile]
dates=1990001,....
timestep=0
*/

#include "corn/file_sys/filename.h"
#include "corn/validtyp.h"
#include "corn/datetime/date.hpp"
#include "cs_glob.h"
#include "cs_vars.h"
#include "corn/data_source/vv_file.h"

#define MAX_entries           100
#define MAX_entries_alloc     101
#define MAX_PRINT_DATES       100
#define MAX_PRINT_DATES_ALLOC 101
//______________________________________________________________________________
enum accumulation_modes {NO_ACCUM,GROWTH_PERIOD_ACCUM,ANNUAL_ACCUM,CONTINUOUS_ACCUM,FALLOW_ACCUM};

#define  chem_var_applied         1
#define  chem_var_transformation  2
#define  chem_var_uptake          3
#define  chem_var_leached         4
#define  chem_var_content         5
#define  chem_var_initial_content 5
#define  chem_var_depletion       6
#define  chem_var_final_content   6
#define  chem_var_balance         7
//______________________________________________________________________________
class FMT_filename
: public CORN::Filtered_name
{
 public:
   inline FMT_filename(const char *i_filename)
      : CORN::Filtered_name(i_filename ? i_filename : "noname","FMT","Report format","*.FMT")
      {};
   inline FMT_filename(const CORN::File_name &i_filename)
      : CORN::Filtered_name(i_filename.c_str(),"FMT","Report format","*.FMT")
      {};
};
//_1999-02-28___________________________________________________________________
class report_options_class
{public:
   CORN_string section;
   bool write_enabled;
   //      True if the file is to be opened for output
   //      (Format file must have been specified and output variables selected)
   bool header;
   bool column_heads;
   bool paginate       ;
   bool separate_years ; // { daily report only }
   CORN_enum /*accumulation_modes*/  Xaccumulation_mode; // {daily report only }
      // When outputing water balance accumulation the report may report either
      //   ANNL_ variables or GP_ variables.
      //   ANNL_ variables should be used when checking the water balance.
      //   GP_ variables should be used when graphing especially crops which grow in december and january.
   int16 line_width;
   int16 lines_per_page;
   int16 time_step;  // daily report only
   CORN_valid_int16_translating_optional v_lines_per_page;
   CORN_valid_int16 v_time_step;
   bool water_budget;                                                            //000414
   bool nitrogen_budgets;
   // Not available yet
   //   P_budget       : bool;
   //   K_budget       : bool;
   bool salinity_budget;
   bool pesticide_budgets;
   //   { The following elements are not saved to the file: }
   int16 num_vars_to_print;
   CS_UED_variable_code sel_var_code[MAX_entries_alloc];                         //000926
 public:
   report_options_class();
      // Copy constructor
   report_options_class(const report_options_class &options_to_copy);            //981203
   report_options_class(const char *section);                                    //981203
   virtual bool setup_structure(Data_record &data_rec,bool for_write) not_const;
   void setup_write_enabled();                                                   //981203
   void require_variable
      (CS_UED_variable_code variable);                                           //000926
//             This method is used by analysis simulation functions
//             To insure that required output variables have been selected.

 public:  // For parameter editor
   bool modified;
   CORN_string accumulation_mode_str;  // used only for I/O
   void count_SRO();                                                             //991121
};
//______________________________________________________________________________
class report_formats_file
: public
#ifdef         USE_CORN_TRANSLATOR_CLASS
   VV_file_translating
#else
   VV_file
#endif
{
public:
    CORN_string description;                                                      //981124
    report_options_class  DLY_options;
    report_options_class  HRV_options;
    report_options_class  YLY_options;

    CORN_date  profile_print_date_data[MAX_PRINT_DATES_ALLOC];   // 1 indexed     //991105

 public: // Profile spreadsheets
    int16 profile_spreadsheet_timestep;

    CORN_valid_int16/*_translating_optional*/ v_profile_spreadsheet_timestep;
    bool at_planting;
    bool at_emergence;
    bool at_flowering;
    bool at_maturity;
    bool at_harvest;
    // Available spreadsheets;

    bool SS_hydraulic_properties;
    bool SS_water_content;
    bool SS_water_potential;
    bool SS_temperature;
    bool SS_plant_residue;
    bool SS_manure_residue;
    bool SS_salinity;

    bool SS_ammonium;
    bool SS_nitrate;
    bool SS_denitrification;
    bool SS_nitrification;
    bool SS_NH4_mineralization;
    bool SS_organic_matter;
 public:
   report_formats_file(const FMT_filename &i_filename);

   virtual void expect_structure(bool for_write = false);
   virtual void load_start();                                                    //981208
   virtual void load_end();                                                      //981208
   bool add_profile_date(const CORN_date &new_date);                               //991105
   bool delete_profile_date(const CORN_date &del_date);                            //991105

//           returns false if the date could not be added.

   bool profile_print_date_exists(const CORN_date &find_date);                   //980527
   void require_variable(uint8 for_report,CS_UED_variable_code variable);        //991120
      // This method is used by analysis simulation functions
      // To insure that required output variables have been selected.
 public:   // For parameter editor
   bool modified;
   int16 num_profile_print_dates;
   void sort_profile_print_dates();
 private:
   void save_start();                                                            //991121
};
//______________________________________________________________________________
#endif
//vmtfile.h

