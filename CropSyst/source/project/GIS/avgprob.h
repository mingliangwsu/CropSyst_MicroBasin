#ifndef AVGPROBH
#define AVGPROBH

//continue here convert from XLS to ued reader

#include "corn/math/statistical/stats.h"
#include "corn/data_source/dbase_datasrc.h"
#include "corn/data_source/datarec.h"
#include "ued/library/UED_types.h"
#include "corn/container/enumlist.h"
#include "corn/measure/unitconv.h"
#include "corn/dynamic_array/dynamic_array_T.h"

#define  MASK_average   0x0001
#define  MASK_CV        0x0002
#define  MASK_prob10    0x0004
#define  MASK_prob20    0x0008
#define  MASK_prob30    0x0010
#define  MASK_prob40    0x0020
#define  MASK_prob50    0x0040
#define  MASK_prob60    0x0080
#define  MASK_prob70    0x0100
#define  MASK_prob80    0x0200
#define  MASK_prob90    0x0400
#define  MASK_prob95    0x0800
#define  MASK_sum       0x1000
#define  MASK_crop_separation 0x2000
#define MAX_ids 200
// Forward declarations_________________________________________________________
class GIS_Project_parameters;
class Avg_prob_map_tallier;
namespace CropSyst
{  class Project_editor_parameters;
}
using_namespace_CORN;
//______________________________________________________________________________
class Separate_crop_tally : public Association   // was separate_crop
{public:
   std::string             crop_name;        // This is actually the description, we link on the crop description which is output to the UED
   Avg_prob_map_tallier*   crop_tally_file;  // owned by this
 public:
   Separate_crop_tally                                                           //050619
      (const char* _crop_name,Avg_prob_map_tallier* _crop_tally_file)
      : Association()
      , crop_name(_crop_name)
      , crop_tally_file(_crop_tally_file)                                        //050708
      {}
   virtual ~Separate_crop_tally() {delete crop_tally_file; crop_tally_file = 0;} //050930
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return crop_name == key; }

/*180820  was probably only used for find_cstr now using is_key
   inline virtual const char *get_key() const                                    //970720
      { return crop_name.c_str(); }
*/      
};
//_class_Separate_crop_tally___________________________________________________________________1998-07-21_/
class Tally_variable
: public Enumeration
//180408 , public Statistical_data_set
, public CORN::Statistical_sample_with_dataset<float32,float32,float32>
{  friend class Avg_prob_map_tallier;
 public:
   UED::Variable_code   variable_code;  // can't be smart
   nat16                report_options_index;   // index to the
   std::string     variable_field_name_suffix; // This is the shorted name of the variable
#define BASIC_STATS_ALLOC 11
#define PROB_10_STATS_ALLOC  11
#define PROB_5_STATS_ALLOC  11
   float32  basic_stats[BASIC_STATS_ALLOC];                                      //050505
   float32  prob_10_stats[PROB_10_STATS_ALLOC];                                  //050505
   float32  prob_5_stats[PROB_5_STATS_ALLOC];                                    //050505
   //NYI need to identify where to store tally value (I think in a statistical data set
 public:
   Tally_variable(UED_variable_code _variable_code,uint16 _report_options_index); // // Must not require a parameter because this is used in an array
   inline virtual bool is_key(nat32 key)affirmation_{return variable_code==key;} //180820
   inline virtual nat32 get_key_nat32()            const {return variable_code;} //020319
   void clear();
   virtual void recompute()                                       modification_; //050705
   inline virtual int compare(const Item &other)             const { return 0; } // not currently used
};
//______________________________________________________________________________
class Scenario_tally_data_record                                                 //050920
: public CORN::Data_record
{public: // the following are not recorded
   nat16 max_variables;
   const nat32 *selected_statistics;        // Reference to the respective GIS_parameters (either annual or harvest)
   const nat32 *selected_probability_10;
   const nat32 *selected_probability_5;
   Units_convertor  units_convertor;                                             //050711
 public: // The following are recorded values
   nat32         scenario_ID;                                                    //050920
   nat32         polygon_ID;
   std::string   polygon_ID_attribute;
   Enumeration_list  tally_list;    // list of tally variables encountered in the database
 public:
   Scenario_tally_data_record
      (nat32  scenario_ID
      ,const char *polygon_ID_attribute                                            //050920
      ,sint32 polygon_ID // signed because negative values were used to indicate offsite values    050630
      ,nat16  max_variables                  // This is the maximum number of variables that are reported (I.e.  GS_MAX_IDS MAX_YLY_entries
      ,const nat32  selected_statistics[]
      ,const nat32  selected_probability_10[]
      ,const nat32  selected_probability_5[]);
   virtual void expect_structure(bool for_write) ;
   virtual bool set_start();                                                     //161023_050705
   void append_value(UED_variable_code variable_code,float32 value,Units_code value_units,bool annual_tally); // (UED_variable_code variable_code,float32 value);
};
//_class_Scenario_tally_data_record_________________________________________2005-05-05_/
class Avg_prob_map_tallier
: public Dynamic_int32_indexed_dBase_data_source   // Indexed by polygon ID
{
   // Each record in this dBase file corresponds to a polygon
   // We loop through all generated scenario folders
   // We run this for either annual or the harvest UED file
   Dynamic_array<nat32> record_scenario;                                         //101015
   // This records the scenario /* polygon */ associated with the record.
   nat32 record_count; // this is the number of records processed so far (used to identify the current polygon record) //010130

   bool  annual_tally; // false = growing season tally                           //050505
   const CropSyst::Project_editor_parameters &project_parameters;                //060706
   const GIS_Project_parameters              *GIS_project_parameters;            //050505
      // may be 0 if not a GIS simulation
   bool aggregate_all_sequences_mode;                                            //050920
 public:
   Avg_prob_map_tallier
   (const char * dbf_filename       // file to be generated                      //050505
   ,const CropSyst::Project_editor_parameters &_project_parameters               //060706
   ,const GIS_Project_parameters              *_GIS_project_parameters           //050505
   ,bool _annual_tally                                                           //050630
   ,bool _aggregate_all_sequences_mode);                                         //050920
   bool tally_UED_file
   (const char *UED_filename
   ,nat32 scenario_ID                                                            //050920
   ,int32 polygon_ID // signed because negative values indicate ___
   ,const char *crop_description   // pass zero for annual tally                 //050708
   ,std::string &status_log);                                                    //091105
   ///< \return Scenario_tally_data_record for the tallied database.
   ///< or returns 0 if the database could not be tallied
   bool duplicate_scenario_record(int32 scenario_to_duplicate, nat32 as_scenario); //050920
 private:
   float get_probability_value(int col, int num_values,float percentage);
   void setup_probabilities(int col,int num_values);
//unused?   void column_stats(int col, float data_set[], int count, float &mean, float &coef_var);
   Tally_variable *get_tally_variable_for_column(int16 column);
};
//_class_Avg_prob_map_tallier_____________________________________________________________________________
#endif

