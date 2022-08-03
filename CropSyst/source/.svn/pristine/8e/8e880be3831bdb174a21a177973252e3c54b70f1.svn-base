//#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
// Obsolete in V5 which only Outputs UED files
// but still used for GIS module variable selection
#ifndef rptoptnsH
#define rptoptnsH

/*
  How to add entries to the available variables for output:

  Add the entry in the list for the respective DLY,YLY, or HRV report.

  Increment the respective MAX_xxx_entries (where xxx is dly,yly,or hrv).

  Renumber the ID: numbers. (yearly report variables are numbered starting
  at 0, yearly starts at 100, and harvest starts at 200). ID numbers
  0,100 and 200 should be blank.

  Make sure that the rpt: field has the correct DLY,YLY,or HRV designation.

  For daily report variables, you must specify either graph:TRUE or graph:FALSE
  depending whether the variable is to be available for graphing using
  the view graph utility.

  Variables which are text (ie crop_name) must have graph:FALSE and d:0.
  Variables which are integer must have d:0;

*/


#include "csvc.h"
//170525#include "corn/datetime/date.hpp"
#include "options.h"
#include "cs_events.h"
#include "cs_vars.h"

#include "cs_vars.h"

#define   LABEL_header          "header"
#define   LABEL_column_headers  "column_headers"
#define   LABEL_paginate        "paginate"
#define   LABEL_separate_years  "separate_years"
#define   LABEL_page_length     "page_length"
#define   LABEL_time_step       "time_step"
#define   LABEL_count           "count"
#define   LABEL_options         "options"
#define   LABEL_fertilizer_budget   "fertilizer_budget"
#define   LABEL_salinity_budget      "salinity_budget"
#define   LABEL_pesticide_budget     "pesticide_budget"

#define   LABEL_SPREADSHEET          "SPREADSHEET"
#define   LABEL_TEXT                 "TEXT"
#define   LABEL_DELIMITED            "DELIMITED"

#define   LABEL_daily                     "daily"
#define   LABEL_harvest                   "harvest"
#define   LABEL_annual                    "annual"

#define   LABEL_profile_print        "profile_print"
#define   LABEL_file_type            "file_type"

#define   MAX_YLY_entries  42
#define   MAX_entries_1 78
                        /*^-1 plus Largest of these */
#define   MAX_NB_entries 33
//______________________________________________________________________________
enum report_types {UNKNOWN_REPORT_TYPE,DLY,YLY,GS /*HRV*/,FLW};
enum format_types {UNKNOWN_FORMAT_TYPE,TEXT_file,DELIMITED_file,LOTUS_file};

enum runtime_graphs {RTG_none
   ,RTG_weather   ,RTG_weather_accum
   ,RTG_Crop      ,RTG_Crop_accum
   ,RTG_Stress
   ,RTG_Residue   ,RTG_Residue_accum
   ,RTG_Soil      ,RTG_Soil_accum
   ,RTG_Management,RTG_Management_accum};


#define DLY_MAX_IDS  98
#define GS_MAX_IDS  91

//NYI
//// Accumulated daily variables:
//accum_format_var_CS_var_assoc DLY_accum_format_CS_var_assoc[] =
//{
////                                     CS variable code
//// report option ID                    For annual accum                          For Growth period accum
// {CSVC_crop_N_fixation_time_step_sum                  ,CSVC_crop_N_fixation_AN_accum_to_date_time              ,CSVC_crop_N_fixation_GP_period_accum}
//};
//                        //  0
////#define YLY_year                       //  1
////corresponding annual report options, variable codes
//format_var_CS_var_assoc YLY_format_CS_var_assoc[] =
//{

// For annual output we use timestep sum variables because the time step is one year


#include "rptoptns_var_defs.h"
using namespace CORN;                                                            //130514
//_____________________________________________________________________________/
enum YLY_HRV_CHEM_IDS
{YLY_HRV_CHEM_ID
,YLY_HRV_applied
,YLY_HRV_transformation
,YLY_HRV_uptake
,YLY_HRV_leached
,YLY_HRV_initial_profile_content
,YLY_HRV_final_profile_content
,YLY_HRV_balance
};
//_____________________________________________________________________________/
struct report_var_layout_with_graph
{
   nat32    ID;    // Using UED variable code for ID                             //000919
   nat8     w;     // Maximum column width
   nat8     d;     // Number of columns reserved for decimal (real variables)
   Phrase_ID_or_label u;       //Should show units
   CORN::Units_code         units_code;                                                 //040927
   Phrase_ID_or_label desc;  //description
   bool      graphable_tallyable;   // if DLY variable is suitable for graphing or tallying
   runtime_graphs runtime_graph_check_obsolete;
   int16 default_color;
   bool used;    // used by cropsyst, don't change
};
#define LAYOUT_NO_OPTIONS RTG_none,0,false
//_____________________________________________________________________________/
//000926 lookup_description is temporary until I make sure that CS_variables are all generating the correct description
//       This description is currently only used where we generate arc_CS 15 character abbreviations.
//       This will be replaced with abbreviations.
const char *lookup_description(report_var_layout_with_graph variable_set[], int set_count, CS_UED_variable_code var_code);
report_var_layout_with_graph *lookup_report_var_layout(report_var_layout_with_graph variable_set[], int set_count, CS_UED_variable_code var_code);
uint16 lookup_variable_index(report_var_layout_with_graph variable_set[], int set_count, CS_UED_variable_code var_code);
//_2000-09-26__________________________________________________________________/
struct group_report_var_layout
{  unsigned char  w;     // Maximum column width
   unsigned char  d;     // Number of columns reserved for decimal (real variables)
   Phrase_ID_or_label      u;     // Should show units
   CORN::Units_code         units_code;      // preferred units code to be used in report  //040927
   Phrase_ID_or_label      group; // Grouping I.e.  NH4, NO3, Total N
   Phrase_ID_or_label      desc;  // description
};
//_____________________________________________________________________________/
extern group_report_var_layout NB_report_var_opts[];
#define DLY_DOY_POS  2
#define DLY_YEAR_POS 1
#define YLY_YEAR_POS 1
// The four entry in the daily report variables must be RDate DAY
extern report_var_layout_with_graph DLY_report_var_opts[];
extern report_var_layout_with_graph YLY_report_var_opts[];
extern report_var_layout_with_graph GS_report_var_opts[];
extern std::string     &column_header(std::string CH, int16 num, int16 N, std::string &buffer);  //040909
//_____________________________________________________________________________/
#endif

//rptoptns.h


