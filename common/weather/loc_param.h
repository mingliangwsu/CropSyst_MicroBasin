#ifndef loc_paramH
#define loc_paramH
//______________________________________________________________________________
#  include "corn/OS/directory_entry_name_concrete.h"
#if ((CS_VERSION > 0) && (CS_VERSION <5) && (!defined(__linux) && (!defined(OFOOT_VERSION))))
#  define SUPPORT_OBSOLETE_LOC_FILE
#endif
#ifndef parameters_datarecH
#  include "corn/parameters/parameters_datarec.h"
#endif
#ifndef UED_fnameH
#  include "UED/library/UED_fname.h"
#endif
#ifndef strconvH
#  include "corn/string/strconv.h"
#endif
#ifndef datarecH
#  include "corn/data_source/datarec.h"
#endif
#ifndef geolocationH
#  include "common/geodesy/geolocation.h"
#endif
#ifndef codesH
#  include "UED/library/codes.h"
#endif
#if ((CS_VERSION==4) && !defined(REACCH_VERSION) && !defined(AGMIP))
#  ifndef loc_filenameH
#    include "weather/loc_filename.h"
#  endif
#endif
#ifdef SUPPORT_OBSOLETE_LOC_FILE
#  ifndef GET_DAT_filenameH
#     include "weather/GEN_DAT_filename.h"
#  endif
#endif
#ifndef ET_modelH
#  include "common/biometeorology/ET_model.h"
#endif
#include "common/weather/weather_types.h"
#include "common/weather/parameter/WC_vapor_pressure_deficit.h"
//______________________________________________________________________________

#define DEF_slope       1.0
#define DEF_intercept   0.0

#define DEF_aridity_factor          0.03
#define DEF_VPD_slope                1.0
#define DEF_VPD_intercept            0.0
#define DEF_dew_pt_slope             1.0
#define DEF_dew_pt_intercept         0.0
#define DEF_min_dew_pt_adj           1.0
#define DEF_ET_slope                 1.0
#define DEF_ET_intercept             0.0

#define DEF_ET_model                 PRIESTLEY_TAYLOR_MODEL
//moved to ET_model.h #define DEF_PT_constant               1.26

#define DEF_summer_B_solar_rad       0.3
#define DEF_winter_B_solar_rad       0.3

#define MISSING_fitted_B_solar_rad       0.0
// Missing value of 0.0 trigger estimation of summer and winter B
// Typical value would be about 0.3
#define TYPICAL_fitted_B_solar_rad  0.3
//050916 was #define DEF_fitted_B_solar_rad       0.0
// but now want to indicate that the default value of 0.0 indicates the data is missing

#define MISSING_Tnc_solar_rad            0
#define TYPICAL_Tnc_solar_rad           15
// typical value value would be 15  (10 to 30)

#define DEF_clear_sky_transmission_coef 0.75
#ifdef OBSOLETE
#define DEF_rain_to_snow_temperature  -1.5
#endif
#define   location_extension  ".loc"
#define   LABEL_location                "location"
#define   LABEL_weather_filename_V3        "weather_filename"
#define   LABEL_database               "database"
#define   LABEL_weather                 "weather"
#define   LABEL_summer                  "summer"
#define   LABEL_winter                  "winter"
#define   LABEL_spring_or_fall          "spring_or_fall"
#define   LABEL_aridity_factor          "aridity_factor"
#define   LABEL_VPD_slope               "VPD_slope"
#define   LABEL_VPD_intercept           "VPD_intercept"
#define   LABEL_dew_pt_slope            "dew_pt_slope"
#define   LABEL_dew_pt_intercept        "dew_pt_intercept"

#define  LABEL_ET                         "ET"
#define   LABEL_hargreaves_slope          "hargreaves_slope"
#define   LABEL_hargreaves_intercept      "hargreaves_intercept"

#if ((CS_VERSION >0 ) && (CS_VERSION < 5))
#  define   LABEL_fitted_B_solar_rad      "fitted_B_solar_rad"
#  define   LABEL_Tnc_solar_rad           "Tnc_solar_rad"
#  define   LABEL_clear_sky_transmission_coef "clear_sky_transmission_coef"
#endif

#define   LABEL_snow_insulation_factor  "snow_insulation_factor"
#define   LABEL_ET_model                "ET_model"
#define   LABEL_mean_peak_rainfall      "mean_peak_rainfall"
#define  LABEL_wind_speed_classification "wind_speed_classification"
#define  LABEL_wind_speed_spring_summer "wind_speed_spring_summer"
#define  LABEL_wind_speed_fall_winter   "wind_speed_fall_winter"

#define dec_degrees_to_radians(dd) (dd * CORN_pi / 180)

#define Monthly_values(x)  float32 x[13]

struct Vapor_pressure_night_time_parameters
{  float32 slope;
   float32 intercept;
   float32 random_range_slope;
public:
   inline void invalidate()
      {  slope = 1.0;              // defaults should disable
         intercept = 0.0;
         random_range_slope = 1.0;
      }
   inline void copy(const Vapor_pressure_night_time_parameters &copy_from)
      {  slope             =copy_from.slope;
         intercept         =copy_from.intercept;
         random_range_slope=copy_from.random_range_slope;
      }
};
//_2009-12-10___________________________________________________________________
struct Solar_radiation_parameters
{
   float32 fitted_B;                                                             //970711
   // Not a user parameter, this value will be computed
   // by ClimGen if solar radiation is available.
   // If 0.0, we will estimate summer and winter B.
   // Warning we need to move climate class from ClimGenF
   // and compute summer and winter  B on the fly from climate class.
   float32 Tnc;
   float32 clear_sky_transmission_coef; // 0.7 to 0.8 will be .75 unless computed by ClimGen  //970711
public:
   inline Solar_radiation_parameters()
      : fitted_B                    (TYPICAL_fitted_B_solar_rad)
      , Tnc                         (TYPICAL_Tnc_solar_rad)
      , clear_sky_transmission_coef (DEF_clear_sky_transmission_coef)
      {}
   inline void invalidate()
      {  fitted_B                   =MISSING_fitted_B_solar_rad;                 //970711_//050916 may be typical value, but need to check if want to trigger the summer and winter B
         Tnc                        =MISSING_Tnc_solar_rad;                      //970712
         clear_sky_transmission_coef=DEF_clear_sky_transmission_coef;            //970711
      }
   inline void copy(const Solar_radiation_parameters &copy_from)
      {  fitted_B                   = copy_from.fitted_B;
         Tnc                        = copy_from.Tnc;
         clear_sky_transmission_coef= copy_from.clear_sky_transmission_coef;
      }
};
//_2009-12-14______________________________________Solar_radiation_parameters__/
struct Relative_humidity_extremes
{  float32 typical[2][SEASON_S_W_SF_COUNT][2];   // [RHmin/RHmax][Summer/Non-summer][low/high]
   float32 &min_summer_low;
   float32 &min_summer_high;
   float32 &min_winter_low;
   float32 &min_winter_high;
   float32 &min_spring_fall_low;
   float32 &min_spring_fall_high;
   float32 &max_summer_low;
   float32 &max_summer_high;
   float32 &max_winter_low;
   float32 &max_winter_high;
   float32 &max_spring_fall_low;
   float32 &max_spring_fall_high;
public:
   inline Relative_humidity_extremes()
      : min_summer_low        (typical[0][SUMMER_ONLY_SEASON]     [0])
      , min_summer_high       (typical[0][SUMMER_ONLY_SEASON]     [1])
      , min_winter_low        (typical[0][WINTER_ONLY_SEASON]     [0])
      , min_winter_high       (typical[0][WINTER_ONLY_SEASON]     [1])
      , min_spring_fall_low   (typical[0][SPRING_OR_FALL_SEASON]  [0])
      , min_spring_fall_high  (typical[0][SPRING_OR_FALL_SEASON]  [1])
      , max_summer_low        (typical[1][SUMMER_ONLY_SEASON]     [0])
      , max_summer_high       (typical[1][SUMMER_ONLY_SEASON]     [1])
      , max_winter_low        (typical[1][WINTER_ONLY_SEASON]     [0])
      , max_winter_high       (typical[1][WINTER_ONLY_SEASON]     [1])
      , max_spring_fall_low   (typical[1][SPRING_OR_FALL_SEASON]  [0])
      , max_spring_fall_high  (typical[1][SPRING_OR_FALL_SEASON]  [1])
      { invalidate(); }
   inline void invalidate()
      {  for (int min_max = 0; min_max <=1; min_max++)
            for (int season = UNKNOWN_SEASON_S_W_SF; season <=SPRING_OR_FALL_SEASON; season++)
            {  // These default disable RH limitation.
                           // Although season[0] is not used we loop UNKNOWN_SEASON_S_W_SF
                           // in case we need to limit RH before the season has been set.
               typical[min_max][season][0] = 0.0;
               typical[min_max][season][1] = 100.0;
            }
      }
   inline void copy(const Relative_humidity_extremes &copy_from)
      {  for (int min_max = 0; min_max <=1; min_max++)
            for (int season = UNKNOWN_SEASON_S_W_SF; season <=SPRING_OR_FALL_SEASON; season++)
               for (int low_high = 0; low_high <= 1; low_high++)
               {  // These default disable RH limitation.
                           // Although season[0] is not used we loop UNKNOWN_SEASON_S_W_SF
                           // in case we need to limit RH before the season has been set.
                  typical[min_max][season][low_high] = copy_from.typical[min_max][season][low_high];
               }
      }
};
//_2009-12-16___________________________________________________________________
class Location_parameters
: public Common_parameters_data_record                                           //050322
{
 public:
   Geolocation    *geolocation;                                                  //050525
 public:
#define        LADSS_loc_ID station_number
   #if ((CS_VERSION>0) && (CS_VERSION<5))
   UED_File_name parameterization_UED_filename; // This is the name of the file used for parameterization //020401
   UED_File_name database_filename;                      // This is the name of the file to export to  //060221
   #else
   // Moving the filename to ClimGen site/location parameter file
   #endif
   //150411 RLN #if ((CS_VERSION==4) && !defined(REACCH_VERSION) &&!defined(AGMIP))
   #ifdef SUPPORT_OBSOLETE_LOC_FILE
   GEN_DAT_UED_filename weather_filename_V3;           // This is the weather file selected for older version of CropSyst/ClimGen   //020401
   // Note that if weather_filename is relative, it is relative to the           //010209
   // directory the location file is in.
   #endif
   //170803 Vapor_pressure_deficit_parameters VPD_parameters;                             //091214
   Vapor_pressure_deficit_max_calculator::Parameters VPDmax_parameters;          //170803_091214

            //rename to VPDmax_parameters

   float32 ET_slope;                                                             //000731
   float32 ET_intercept;                                                         //000731
   #if (CS_VERSION==4)
      //051230 these have been moved to the simulation control
   LOC_ET_Model_labeled        ET_model_labeled_V3;  // This is being moved to simulation scenario  (But need to keep for V3 and ClimGen //020318
   float32 PT_constant_32_V3;  // Priestley-Taylor constant   In V4 this is moved to simulation control, but still used for ClimGen
   #endif
   float32 wind_speed_spring_summer_ms_32;// m/s                                 //980220
   float32 wind_speed_fall_winter_ms_32;  // m/s                                 //980220
   Wind_speed_classification_labeled      wind_speed_classification_labeled;     //970723
   Monthly_values(mean_peak_rainfall); // fraction mm                            //990419
    // This is becoming obsolete, it is provided for CropSyst compatibility.
    // Eventually CropSyst will require climate generation
   Solar_radiation_parameters solar_radiation_parameters;                        //091214
   Vapor_pressure_night_time_parameters vapor_pressure_nighttime_parameters;     //091210
   Relative_humidity_extremes relative_humidity_extremes;
 public:  // parameter description and validators
   #if ((CS_VERSION==4) && !defined(REACCH_VERSION))
   CORN::Valid_float32 v_PT_constant_V3;
   //170804 CORN::Valid_float32 v_aridity_factor;                                               //000715
   CORN::Valid_float32 v_wind_speed_spring_summer_ms;// m/s                            //980220
   CORN::Valid_float32 v_wind_speed_fall_winter_ms;  // m/s                            //980220
   CORN::Valid_float32 v_mean_peak_rainfall_1;
   CORN::Valid_float32 v_mean_peak_rainfall_2;
   CORN::Valid_float32 v_mean_peak_rainfall_3;
   CORN::Valid_float32 v_mean_peak_rainfall_4;
   CORN::Valid_float32 v_mean_peak_rainfall_5;
   CORN::Valid_float32 v_mean_peak_rainfall_6;
   CORN::Valid_float32 v_mean_peak_rainfall_7;
   CORN::Valid_float32 v_mean_peak_rainfall_8;
   CORN::Valid_float32 v_mean_peak_rainfall_9;
   CORN::Valid_float32 v_mean_peak_rainfall_10;
   CORN::Valid_float32 v_mean_peak_rainfall_11;
   CORN::Valid_float32 v_mean_peak_rainfall_12;
   #else
   /*110124 Not yet implemented
   Xxxx_parameter p_PT_constant_V3;
   Xxxx_parameter p_aridity_factor;                                               //000715
   Xxxx_parameter p_wind_speed_spring_summer_ms;// m/s                            //980220
   Xxxx_parameter p_wind_speed_fall_winter_ms;  // m/s                            //980220
   Xxxx_parameter p_mean_peak_rainfall_1;
   Xxxx_parameter p_mean_peak_rainfall_2;
   Xxxx_parameter p_mean_peak_rainfall_3;
   Xxxx_parameter p_mean_peak_rainfall_4;
   Xxxx_parameter p_mean_peak_rainfall_5;
   Xxxx_parameter p_mean_peak_rainfall_6;
   Xxxx_parameter p_mean_peak_rainfall_7;
   Xxxx_parameter p_mean_peak_rainfall_8;
   Xxxx_parameter p_mean_peak_rainfall_9;
   Xxxx_parameter p_mean_peak_rainfall_10;
   Xxxx_parameter p_mean_peak_rainfall_11;
   Xxxx_parameter p_mean_peak_rainfall_12;
   */
   #endif
   std::string parameterized_from;  // This is a temporary special record of where solar rad, humid ect were parameterized from in the region weather database preparation program //050912_
 public:
   Location_parameters                                                           //990228
      (const char *weather_filename
      ,bool store_geolocation); // set to true when creating location file for old CropSyst location/weather file sets  //050525
      //180626 ,uint8 version_major,uint8 version_release,uint8 version_minor);  // version number for calling program //040416
   Location_parameters(const Geolocation &geoloc);
      //180626 ,nat32 version);                                                           //180626
      //180626 , uint8 version_major,uint8 version_release,uint8 version_minor); //050307
      // This copy constructor is used by CropSyst when loading location parameters from UED. //050307
   virtual ~Location_parameters();
   inline virtual const char *get_type_label()                            const  { return "CropSyst/ClimGen location";}     //051011
   CORN::Quality_code   get_aridity_factor_quality ()                     const; //050609
   CORN::Quality_code   get_dew_pt_curve_quality   ()                     const; //050610
   CORN::Quality_code   get_VPD_curve_quality      ()                     const; //050610
   virtual bool expect_structure(bool for_write = false);                        //161023
   inline virtual bool preserve_unexpected_entries()                      const  { return true; }   //020108
   inline virtual const char *get_primary_section_name()                  const  {return LABEL_location;}//020911
   virtual bool set_start();                                                     //161023_010110
   virtual bool get_end();                                                       //161023_010110
   virtual void invalidate_ClimGen_parameters();  // Only the constructor and ClimGen parameterization should call this function.
public: // CropSyst/ClimGen parameters
   inline float64  get_wind_speed_spring_summer_ms()                      const  {return wind_speed_spring_summer_ms_32;} //980220
   inline float64  get_wind_speed_fall_winter_ms()                        const  {return wind_speed_fall_winter_ms_32;}   //980220
#if ((CS_VERSION > 0) && (CS_VERSION < 5))
   inline float64  get_PT_constant_V3()                                   const  {return PT_constant_32_V3;}
   inline ET_Model get_ET_model_V3()                                      const  {return ET_model_labeled_V3.get(); }//020318
#endif
#if ((CS_VERSION>0) && (CS_VERSION<5) && !defined(REACCH_VERSION))
//#ifdef SUPPORT_OBSOLETE_LOC_FILE
  CORN::OS::File_name &get_database_or_weather_filename();                       //060221
#endif
//             Returns the database filename, or if it is an older location file, the weather_filename which could be a .DAT or .GEN filename.
public: // set accessors
   void set_VPD_night_parameters                                                 //091210
      (float32 _VP_slope                                                         //091210
      ,float32 _VP_intercept                                                     //091210
      ,float32 _random_range_slope)                               modification_; //091210
 public: // Things the location file knows about itself
   bool has_mean_peak_rainfall()                                          const; //990527
 public:
#ifndef REACCH_VERSION
    void qualify(const CORN::OS::Directory_name &loc_dir_name);                  //010209
#endif
};
//_2001-01-09___________________________________________________________________
#endif


