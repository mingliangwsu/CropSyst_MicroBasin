#ifndef cs_scenarioH
#define cs_scenarioH
#include "options.h"
#include "organic_matter/OM_types.h"
#include "organic_matter/OM_params.h"
#include "corn/labeled_enum.h"
#include "CS_suite/simulation/CS_simulation_unit.h"
#include "CS_suite/simulation/CS_simulation_control.h"
#include "CS_suite/file_system/CS_databases.h"
#include "model_options.h"
#include "cs_filenames.h"
#include "common/geodesy/geolocation.h"

#ifdef REACCH_VERSION
#  define Monthly_values(x)  float32 x[13]
#else
#  include "common/weather/loc_param.h"
#endif
#include "common/weather/weather_types.h"
#if ((CS_VERSION==4)  && !defined(AGMIP))
#include "common/weather/loc_filename.h"
#endif
#include "common/soil/layering.h"
#include "soil/soil_N_param.h"
#include "UED/library/UED_fname.h"

class CropSyst_scenario_directory;
//______________________________________________________________________________
#define MAX_CHEM_PROFILES        20
#define MAX_CHEM_PROFILES_alloc  21

#define  LABEL_ID                   "ID"

#define LABEL_STATSGO "STATSGO"
// I am using the same labels as the statsgo nomenclature

#define     LABEL_muid      "muid"
#define     LABEL_seqnum    "seqnum"

#define    LABEL_adjust_mineralize    "adjust_mineralize"
#define    LABEL_adjust_nitrify       "adjust_nitrify"
#define    LABEL_adjust_denitrify     "adjust_denitrify"
#define    LABEL_max_transform_depth  "max_transform_depth"

#define    LABEL_adjustment           "adjustment"

#define    LABEL_soil_filename_OLD        "soil_filename"
#define    LABEL_location_filename_OLD    "location_filename"
#define    LABEL_management_filename_OLD  "management_filename"
#define    LABEL_rotation_filename_OLD    "rotation_filename"
#define    LABEL_recalibration_filename_OLD "recalibration_filename"
#define    LABEL_water_table_filename_OLD "water_table_filename"
#define    LABEL_grass_filename_OLD       "grass_filename"

#define LABEL_parameter_filenames      "parameter_filenames"
#define    LABEL_soil            "soil"
#define    LABEL_location        "location"
#define    LABEL_weather_database "weather_database"
#define    LABEL_fixed_management "fixed_management"
#define    LABEL_rotation        "rotation"
#define    LABEL_recalibration   "recalibration"
#define    LABEL_water_table     "water_table"
#define    LABEL_grass           "grass"

#define    LABEL_initial_residue       "initial_residue"
#define    LABEL_initial_manure        "initial_manure"
#define    LABEL_stubble_biomass       "stubble_biomass"
#define    LABEL_surface_biomass       "surface_biomass"
#define    LABEL_incorporated_biomass  "incorporated_biomass"
#define    LABEL_water_hold            "water_hold"
#define    LABEL_N_conc                "N_conc"
#define    LABEL_decomposition_time    "decomposition_time"
#define    LABEL_reset_residue         "reset_residue"

#define    LABEL_water_table_salinity "water_table_salinity"

#define    LABEL_H2O  "H2O"
#define    LABEL_NO3  "NO3"
#define    LABEL_NH4  "NH4"
#define    LABEL_recalibrate_date "recalibrate_date"

// The following are for Version 3 and LADSS compatibility
#define  LABEL_initialize_obsolete        "initialize"
#define     LABEL_surface_residue_obsolete      "surface_residue"
#define     LABEL_incorp_residue_obsolete       "incorp_residue"
#define     LABEL_residue_N_conc_obsolete       "residue_N_conc"
#define     LABEL_enable                        "enable"
//______________________________________________________________________________
enum Cropping_system_mode
{no_cropping_system,single_cropping_system,rotation_cropping_system,established_cropping_system};   //051231
extern Label_description  cropping_system_mode_label_table[];                    //051231
DECLARE_DESCRIPTIVE_LABELED_ENUM(Cropping_system_mode_labeled,Cropping_system_mode,cropping_system_mode_label_table) //051231
namespace CropSyst                                                               //130621
{
   class Simulation_override_record;                                             //140216
//______________________________________________________________________________
class Single_cropping_system
{
 public:
   CORN::Date_clad_32            sowing_date;
   CRP_filename                  crop_filename;
   MGT_filename                  management_filename;
 public:
   Single_cropping_system();
};
//_class_Single_cropping_system_____________________________________2018-04-25_/
class Scenario                                                                   //130621 was CropSyst_scenario
: public extends_ CS::Simulation_control                                         //130621
, public extends_ CropSyst_Model_options                                         //130826
{
 public: // public for parameter editor
   CS::Annual_temperature annual_temperature;                                    //150424
   Parameter_number p_annual_temperature_avg;
   Parameter_number p_annual_temperature_avg_half_amplitude;
   Parameter_number p_annual_temperature_phase;

   Monthly_values(mean_peak_rainfall); // fraction? mm?                                                                   //091206
                  // The mean peak rainfall used to be in the location file
                  // but when using UED file we need to enter these values here.
                  // Eventually I may move this to the UED file (this values could be computed in ClimGen)
                  // I am not sure the units, they appear to be mm
                  /* Claudio gave told me this is how to calculate
                     but my documentation says these are fraction
                     (I may have been in error when I wrote up the documentation
                      because the sample data looked like they were < 1.0
                      I need to verify the unit with the original model
                      Arnold, J. and William, J. R. (1989).
                      Stochastic generation of internal storm structure at a point.
                      Transactions of the ASAE, 32(1):161--167.)
                     What you do is sort all the half hour precipitation events by month.
                     Take the top 10% (highest values) of precipitation and average these for each month.
                     This give the monthly values used

                     If you only have hourly data, you can do the same but divide the average of the top 10% by two.
                     Similarly if you have 15 minute data you can multiply the average of the top 10% by two, or
                     sum the 15 minute values to get half hour values.
                     (The 10% is somewhat arbitrary, we just don't want to take only the highest events).
                  */

 public: // Topography
   float64 site_aspect_N0_E90 ;     // 0=North 90=East                           //060725
 public: // Parameter files
   // Optional statsgo database soil identifier.
   std::string statsgo_muid;                                                     //000118
   int16       statsgo_seqnum;   // actually uint8 will probably work            //000118
   Valid_int16 v_statsgo_seqnum;                                                 //000120

   // The following filenames are preferably relative to the .SIM file
   // They may be fully qualified for the master database.
   SIL_filename         soil_filename;                                           //000211
#if (((CS_VERSION>=1) && (CS_VERSION<=4))  &&!defined(AGMIP))
   LOC_filename         location_filename;
#endif
   CORN::OS::File_name_concrete weather_filename;                                //030206_110101 weather_database;
   CORN::OS::File_name_concrete rotation_filename;                               //000310
   MGT_filename         fixed_management_filename;                               //000106
       // Fixed management schedule
   CORN::OS::File_name_concrete organic_matter_initial_filename;                 //160315
      // organic_matter_initial_filename is predominately used for REACCH
      // where it is required for future scenarios and the filename is
      // determined at run time.
      // However it is potentially generally useful.

   CORN::OS::File_name_concrete  grass_filename_soil_regimens;                   //120924
   CORN::OS::File_name_concrete recalibration_filename;                          //130115_000310
   WTB_filename         water_table_filename;                                    //000504
   Cropping_system_mode_labeled  cropping_system_mode_labeled;                   //051231

   Single_cropping_system        single;                                         //180425
   /*180425 moved to Single_cropping_system
   CORN::Date_clad_32            single_sowing_date;                             //051231
   CRP_filename                  single_crop_filename;                           //051231
   MGT_filename                  single_management_filename;                     //051231
   */
/*
 Geolocation has been removed from the scenario file (this will also be done for V4)
  it is now a separate file can can be either in the scenario directory
  or a file in any parent, or a geocoordinate in name of any directory the path to the scenario.

#if (CS_VERSION==4)
   // Actually geocoordinate will be applicable to all versions
   // Currently we get geocoordinate from the weather datasource
   // but it is not necessarily the case that the weather data we are
   // using is actually from the site.
   // I need to use this geocoordinate instead of the weather file
   // The scenario can have a geolocation file in its directory
   // Or the scenario directory name itself may be geolocation
   provided_ Geolocation *geolocation;                                           //151115_131213
   contribute_ bool owns_geolocation;                                            //151115
      // This is the location of the study site.
      // It would be the centroid of a polygon/cell.
      // Previosly CropSyst was using  simpy the geolocation of the weather.
      // but the weather data geolocation is often not the study site geolocation.
#else
#endif
*/
 public: // field info for optimization and grazing regimen (not used by CropSyst itself);
   int16    field_number;  // usually 1 indexed                                  //040819
   float32  field_size_ha;  // ha
 #ifdef NITROGEN
 #if (CROPSYST_VERSION==4)
 public: // Nitrogen transformation initialization
  // Nitrogen initializations:
  float32 V3_adjust_mineralize_32;  Valid_float32 v_V3_adjust_mineralize;  //0-2    In version 4 mineralization is now a function of organic matter submodel
  float32 adjust_nitrify_V4_1;      Valid_float32 v_adjust_nitrify_V4_1;   //0-2
  float32 max_transform_depth_32;   Valid_float32 v_max_transform_depth;   // > 0 m
  float32 adjust_denitrify;         Valid_float32 v_adjust_denitrify;      //0-2  now applies to V4.1 and with_CO2 nitrogen model   090721
 #endif
   CropSyst::Denitrification_parameters denitrification_parameters;              //150824
 #endif
   struct Soil_root_activity_coef                                                //180416
   {  float32 dry;                                                               //170518
      float32 saturation;                                                         //170518
   } soil_root_activity_coef;                                                    //180416
 public: // Chemical profile initialization
   Bidirectional_list   initial_chemical_profiles;                               //180101_980731 //CHEM
   CORN::Date_clad_32   POM_recalibrate_date;                                      //CHEM
   soil_horizon_array32(horizon_percent_organic_matter); //{ 0-10 (0-100) }      //CHEM
   bool              use_soil_parameter_organic_matter;                          //090202
      // Longterm/histrical measure organic matter may be provided in soil database and thus
      // stored as a soil parameter, when enabled, use_soil_parameter_organic_matter
      // will load initial organic matter from the soil parameter (file/datasource).
#ifdef RESIDUES
 public: // residue initialization
   bool reset_residue_deprecated;// This option resets the residue pools every year (365 days) //010717
   CORN::Date_clad_32 residue_recalibration_date;                                //160126
   //CORN::Date residue_incorporated_recalibration_date;                         //160126
   // Residue Initializations:
   float32 water_hold_const_residue_32; //m (manual says m^3/kg)                 //980206
   // Residue Initializations:
   float32 stubble_residue_32; Parameter_number p_stubble_residue; //kg/m2       //170604 Valid_float32 v_stubble_residue;    //kg/m2    //060526
   float32 surface_residue_32; Parameter_number p_surface_residue;    //kg/m2    //170604 Valid_float32 v_surface_residue;    //kg/m2
   //170604 float32 incorporated_residue_32_obsolete_V4_4_1; Parameter_number p_incorporated_residue;     //kg/m2 //170604       Valid_float32 v_incorporated_residue;     //kg/m2
   soil_horizon_array32(horizon_incorporated_residue);                           //060405  kg/m2
   float32 N_conc_residue_32; Parameter_number p_N_conc_residue;     // kg N/kg biomass //170604              Valid_float32 v_N_conc_residue;     // kg N/kg biomass
   #if ((CS_VERSION==4) && !defined(REACCH_VERSION))
   int16   decomposition_time_residue_63; Parameter_number p_decomposition_time_residue_63; //days //040830 depricated, replacing with 50% basis Valid_int16   v_decomposition_time_residue_63; //days //040830 depricated, replacing with 50% basis
   // in later versions used only 50% decomp rate
   #endif
   int16   decomposition_time_residue_50; Parameter_number p_decomposition_time_residue_50; //days Valid_int16   v_decomposition_time_residue_50; //days
   CRP_filename   previous_residue_crop_filename;                                //060224
 public: // Residue manure initialization
   float32 water_hold_const_manure_32; //m (manual says m^3/kg)                  //010717
   float32 surface_manure_32;     /*kg/m2*/  Parameter_number p_surface_manure;  //170604 Valid_float32 v_surface_manure;      //010717
   float32 incorporated_manure_32;/*kg/m2*/  Parameter_number p_incorporated_manure; //170604    Valid_float32 v_incorporated_manure; //010717
   float32 N_conc_manure_32;      /*kg/m2*/  Parameter_number p_N_conc_manure;  //170604 Valid_float32 v_N_conc_manure;
   int16 decomposition_time_manure_50; Parameter_number p_decomposition_time_manure_50; //days  //170604  Valid_int16 v_decomposition_time_manure_50; //days  //010717
#endif
 public: // Organic matter history  (for new organic manure
   Organic_matter_initialization_parameters  organic_matter_initialization_parameters; //070303
   Organic_matter_decomposition_parameters   organic_matter_decomposition_parameters;  //070303
 public:
  int16 years_in_rotation;   // This is not used by cropsyst model itself
                             // But is useful in the user interface and
                             // is used by the RISK model.
                             // It is also used by SoilR
 public: // soil profile initialization
   CORN::Date_clad_32 H2O_recalibrate_date;                                      //011116
   Moisture_characterization_labeled moisture_initial_labeled;                   //170320
   soil_horizon_array32(horizon_H2O);    //{m3/m3 initial water content } // rename this to water_content_init
   // 970508  SoilR uses layer 1 for soil profile initial water content.
   bool has_mean_peak_rainfall()                                   affirmation_; //091205
#ifdef NITROGEN
 public: // soil nitrogen profile initialization
    // Unlike the DOS version, we don't have a NO3, NH4 and salinity arrays, they
    // go into the chemical profiles.

   CORN::Date_clad_32 N_NO3_recalibrate_date;                                    //170525_011117
   CORN::Date_clad_32 N_NH4_recalibrate_date;                                    //170525_011117
   soil_horizon_array32(horizon_N_NO3);   // kg N/ha initial N
   soil_horizon_array32(horizon_N_NH4);   // kg N/ha initial N
      // probably in the form of diphosphorous pentooxide
   float32 initial_water_table_N_NO3; Parameter_number p_initial_water_table_N_NO3; //170604 Valid_float32 v_initial_water_table_N_NO3; //080213
   float32 initial_water_table_N_NH4; Parameter_number p_initial_water_table_N_NH4; //170604 Valid_float32 v_initial_water_table_N_NH4; //080213
#endif
#ifdef PHOSPHORUS
   float32 phosphorus_in_profile;   // kg P/ha initial                              //110801
   Valid_float32 v_phosphorus_in_profile;
   //NYI   soil_horizon_array32(horizon_P);       valid_soil_horizon_array(v_P);         // kg P/ha   //110801
#endif
#ifdef SALINITY
 public: // soil salinity profile initialization
   soil_horizon_array32(horizon_salinity_dSm);     // dS/m
   valid_soil_horizon_array(v_salinity);
   float32 initial_water_table_salinity_32;        // dS/m
   Parameter_number p_initial_water_table_salinity;   // dS/m
   //170604Valid_float32 v_initial_water_table_salinity;   // dS/m
#endif
#if ((defined(SALINITY) || defined(NITROGEN)))
// Not sure why or nitrogen, need to check if really needed for nitrogen model. 090818
 public:
   float32 ECe_to_TDS;  Parameter_number p_ECe_to_TDS; //170624 Valid_float32 v_ECe_to_TDS; // Conversion factor electrical conductivity of soil to TDS concentration //80402
   float32 ECw_to_TDS;  Parameter_number p_ECw_to_TDS; //170624 Valid_float32 v_ECw_to_TDS;                              //080402
#endif
#ifdef SOILR
   CORN::Date  SoilR_latest_date_to_clip;                                        //980723
   float32 SoilR_adjust_relative_growth_rate_for_clipping; // 0-2
   float32 SoilR_minimum_biomass_required_for_clipping ; //kg/ha  function used kg/m2    //970521
   float32 SoilR_biomass_forces_clipping ; //kg/ha  function used kg/m2          //970521
   float32 SoilR_biomass_removed_clipping; // %
   Valid_float32 v_SoilR_adjust_relative_growth_rate_for_clipping;
   Valid_float32 v_SoilR_minimum_biomass_required_for_clipping;
   Valid_float32 v_SoilR_biomass_forces_clipping;
   Valid_float32 v_SoilR_biomass_removed_clipping;

   bool override_crop;
   float32        SoilR_max_root_depth;                                          //970608
   float32        SoilR_max_LAI;                                                 //970608
   float32        SoilR_ET_crop_coef;                                            //970608
   float32        SoilR_induce_dormancy_temp;          // 'C                     //970608
   CORN::Date     SoilR_start_dormancy_valid_date;                               //970608
   CORN::Date     SoilR_leave_dormancy_valid_date;                               //970608
   Valid_float32  v_SoilR_max_root_depth;                                        //970608
   Valid_float32  v_SoilR_max_LAI;                                               //970608
   Valid_float32  v_SoilR_ET_crop_coef;                                          //970608
   Valid_float32  v_SoilR_induce_dormancy_temp;                                  //970608
#endif
 protected:
#ifdef PESTICIDE
   std::string chemical_names[MAX_CHEM_PROFILES_alloc];                          //970726
#endif
 public:
   Scenario(bool CPF_mode = false);                                              //160222_160413LML added default value
   virtual bool expect_structure(bool for_write = false);                        //161023_981208
   /*180626 obsolete now using external mechanism for upgrade/coversion
   virtual Section_entry_change *get_section_entry_changes(nat16 &count)  const; //020408
   */
   virtual bool get_start();                                                     //161023_010110
   virtual bool get_end();                                                       //161023_010110
   virtual bool set_start();                                                     //161023_010110
 public:
   inline virtual const char *get_type_label() const{return"CropSyst scenario";} //051011
   virtual Common_operation *get_operation
      (const char                      */*operation_type_str */                  //030808
      ,const std::string               &/*operation_ID */
         // filename may be updated with qualification so not const (does not apply to cropsyst)   //030808
      ,modifiable_ CORN::OS::File_name &/*operation_filename  */
         // the fully qualified operation filename may be returned (currently CropSyst does not do this) //031215
      ,int32                            /*resource_set_ID*/
      ,bool                            &/*relinquish_op_to_event*/)              //030808
   #ifdef LADSS_MODE
      ;
   #else
      { return 0; }
   #endif
   #if (CROPSYST_VERSION==4)
   // GIS scenario generation is now provided by scenario generator              //170202
   nat8 assign_IDs_to_parameter_filenames()                       modification_; //140214
      // returns the number of ID's assigned
   #endif
   #if (CROPSYST_VERSION==4)
   // GIS scenario generation is now provided by scenario generator              //170202
   bool apply_simulation_override_record(const CropSyst::Simulation_override_record &GIS_record);
   #endif
 public: // 32bit accessors
#ifdef RESIDUES
   inline float64 param_stubble_residue()           const { return (float64)stubble_residue_32; }    //kg/m2                        060526
   //160126 removing accessor methods inline float64 param_surface_residue()           const { return (float64)surface_residue_32; }    //kg/m2
   //170604 inline float64 param_incorporated_residue()   	 const { return (float64)incorporated_residue_32_obsolete_V4_4_1; }     //kg/m2
   inline float64 param_water_hold_const_residue()  const { return (float64)water_hold_const_residue_32; } //m (manual says m^3/kg)   980206
   inline float64 param_N_conc_residue()            const { return (float64)N_conc_residue_32; }     //kg N/kg biomass
   inline float64 param_surface_manure()            const { return (float64)surface_manure_32; }    //kg/m2                           010717
   inline float64 param_incorporated_manure()       const { return (float64)incorporated_manure_32; }     //kg/m2                     010717
   inline float64 param_water_hold_const_manure()   const { return (float64)water_hold_const_manure_32; } //m (manual says m^3/kg)    010717
#endif
#ifdef NITROGEN
 public: // Accessors for nitrogen
   #ifdef RESIDUES
   inline float64 param_N_conc_manure()                        const { return (float64)N_conc_manure_32; }     //kg N/kg biomass
   #endif
   #if (CROPSYST_VERSION==4)
   inline float64 param_V3_adjust_mineralize()                 const { return (float64)V3_adjust_mineralize_32;}  //0-2
   inline float64 param_adjust_nitrify_V4_1()                  const { return (float64)adjust_nitrify_V4_1;}     //0-2
   inline float64 param_adjust_denitrify()                     const { return (float64)adjust_denitrify;}   //0-2   //081013
   inline float64 param_max_transform_depth()                  const { return (float64)max_transform_depth_32;}// > 0 m
   #endif
   inline float64 param_initial_water_table_N_NO3()            const { return (float64)initial_water_table_N_NO3; } //080213
   inline float64 param_initial_water_table_N_NH4()            const { return (float64)initial_water_table_N_NH4; } //080213
#endif
#ifdef SALINITY
 public: // accessors for salinity
   inline float64 param_initial_water_table_salinity()         const { return (float64)initial_water_table_salinity_32; }
#endif
/*171207 obsolete not used anywhere
#if (((CS_VERSION >= 1) && (CS_VERSION < 5)) && !defined(REACCH_VERSION))
#ifdef CO2_CHANGE
 public: // accessors for CO2                                                    //020308
      inline float64 param_initial_CO2_conc()          const { return (float64)initial_CO2_conc;}
      inline float64 param_annual_CO2_change()         const { return (float64)annual_CO2_change; }
#endif
#endif
*/
};
//_2002-03-08________________________________________________CropSyst_scenario_/
} // namespace CropSyst
#endif
//cs_scenario.h

