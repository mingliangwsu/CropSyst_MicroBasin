#ifndef land_unit_output_V4H
#define land_unit_output_V4H
#include "land_unit_with_output.h"

class Report_formats_parameters;                                                 //131008
#include "cs_report_V4.h"

class Soil_profile_spreadsheet_set;
namespace CropSyst {                                                             //141206
//______________________________________________________________________________
// In V5 these reports will all go away
class Land_unit_with_output_V4
: public extends_ Land_unit_with_output
{
#ifdef XLS_OUTPUT
 public: // These used to be global vars, the following I may need to move to land_unit_with_reports so other models using land block frag can also create reports
   CropSyst_DLY_report *DLY_report;
   #ifndef SOILR
   CropSyst_YLY_report *YLY_report;
   CORN::Date_clad_32 last_YLY_report_detail_write_date;
   CropSyst_GS_report *GS_report;
   CropSyst_N_balance_report *DLY_N_balance_report;
   CropSyst_N_balance_report *YLY_N_balance_report;
   CropSyst_N_balance_report *GS_N_balance_report;
   #endif
#endif

#ifndef __linux
   std::ofstream                *detail_txt_stream;                              //090803
#if (!defined(REACCH_VERSION) && !defined(OFOOT_VERSION))
 public: // Quick outputs                                                        //070314
   std::ofstream                 organic_matter_percents_file;                   //070314
   #ifdef DETAIL_DENITR
   provided_ std::ofstream      *denitr_detail_stream;                           //160128
   #endif
#endif
#endif

#ifdef RUSLE_DETAIL
   std::ofstream     *RUSLE_detail_txt_file;
#endif
 protected: // objects shared by all the simulations
    #if (((CS_VERSION >= 1) && (CS_VERSION < 5)) && !defined(REACCH_VERSION))
   const CORN::OS::File_name/*180416 _concrete*/ &format_filename;                          //120505
   #endif
 public:
   Report_formats_parameters *reports;  // if 0 then no report output            //010110
   bool record_soil_profile_today;
 protected:
   Soil_profile_spreadsheet_set *profile_spreadsheet_set;                        //000827
   #ifndef __linux
   // now use verbose bool batch_mode;
   bool verbose;                                                                 //160311
   std::ofstream tot_txt_file;  // Vista doesn't allow files to be open for write and then reopen for read //020507
   #endif
   void open_out_files();
   void write_headers();
   void close_out_files();
   void yearly_output(Year cropyear );
   void harvest_totals_output(Year cropyear );     // May make this V4 only
   #ifdef LISTVARS
   bool list_variables ;
   #endif
   #ifdef TXT_OUTPUT
               std::ofstream output_file;
   #endif
public:
   Land_unit_with_output_V4
      (const CS::Identification           &LBF_ID_                               //151128
      ,nat32                               cycle_shift_                          //151026
      ,CropSyst::Scenario                 &scenario_control_and_model_options_   //130827
      ,const CORN::date32                 &today_                                //170525
      ,const Geocoordinate                &geocoordinate_                        //151116
      ,
      #if (CROPSYST_VERSION==4)
         // temporarily remove const until I cleanup meteorology setup in cs_simulation
      #else
      const
      #endif
       CS::Land_unit_meteorological       &meteorology_                          //151128
      ,CS::Desired_variables              &desired_vars_
      #if (CS_VERSION==4)
      ,Common_simulation_log              &event_log_
      #endif
      ,const CropSyst::Scenario_directory *scenario_directory_                   //150209_050619
      ,const CORN::OS::File_name          *override_format_filename              //120505
      ,bool                                verbose_                              //160311
      ,bool                                output_daily_UED_
      );                   //130624
   inline virtual ~Land_unit_with_output_V4() {}                                 //151204
   virtual bool initialize()                                     initialization_;//131220
   virtual bool start();
   virtual bool start_year()                                       modification_;//010202
   virtual bool start_growing_season
      //180101       #if ((REACCH_VERSION==2) || (CROPSYST_VERSION >= 5) || defined(INTERCROPPING) || defined(OFOOT_VERSION))
      (modifiable_ Crop_interfaced &crop_at_start_season);                       //130716
      //180101       #else
      //180101       ();                                                                        //120505
      //180101       #endif
   virtual bool output_growing_season
      //180101       #if ((REACCH_VERSION==2) || (CROPSYST_VERSION >= 5) || defined(INTERCROPPING) || defined(OFOOT_VERSION))
      (const Crop_interfaced &crop_at_start_season);                             //130716
      //180101       #else
      //180101       ();                                                                        //050114
      //180101       #endif
   virtual bool end_day();
   virtual bool end_year();                                                      //131010_111031
   virtual bool stop(); // Stop recording to output file
   virtual void harvest_event
      (const CropSyst::Crop_interfaced &crop_at_harvest);                        //130716
 public: // special outputs
   void output_organic_matter_partitioning(bool at_start);                       //070314
   std::ofstream &provide_denitr_detail()                             provision_;//160128
};
//______________________________________________________________________________
} // namespace CropSyst                                                          //141206
#endif

