#ifndef weather_typesH
#define weather_typesH

#ifndef labeled_enumH
#include "corn/labeled_enum.h"
#endif
//______________________________________________________________________________
extern const char *snow_pack_model_label_table[];
enum Snow_pack_model {NO_SNOW_PACK,SIMPLE_SNOW_PACK,ENERGY_SNOW_PACK};
DECLARE_LABELED_ENUM(Snow_pack_model_labeled,Snow_pack_model,snow_pack_model_label_table);
//_1999-10-04___________________________________________________________________
enum Season_S_S_F_W{UNKNOWN_SEASON_S_S_F_W,SPRING_SEASON,SUMMER_SEASON,FALL_SEASON,WINTER_SEASON,SEASON_S_S_F_W_COUNT};
extern const char *season_S_S_F_W_label_table[];
DECLARE_LABELED_ENUM(Season_S_S_F_W_labeled,Season_S_S_F_W,season_S_S_F_W_label_table);
//_2004-01-15___________________________________________________________________
enum Season_S_W_SF{UNKNOWN_SEASON_S_W_SF,SUMMER_ONLY_SEASON,WINTER_ONLY_SEASON,SPRING_OR_FALL_SEASON,SEASON_S_W_SF_COUNT};
extern const char *season_S_W_SF_label_table[];
DECLARE_LABELED_ENUM(Season_S_W_SF_labeled,Season_S_W_SF,season_S_W_SF_label_table);
//_2004-01-15___________________________________________________________________
 enum Wind_speed_classification{WIND_SPEED_VERY_LOW,WIND_SPEED_LOW,WIND_SPEED_MEDIUM,WIND_SPEED_MEDIUM_HIGH,WIND_SPEED_HIGH,WIND_SPEED_VERY_HIGH,WIND_SPEED_SPECIFIED,WIND_SPEED_UNKNOWN};
 extern const char *wind_speed_class_label_table[];                              //020322
 DECLARE_LABELED_ENUM(Wind_speed_classification_labeled,Wind_speed_classification,wind_speed_class_label_table); //020322
//_1998-02-20___________________________________________________________________
namespace CS {
struct Annual_temperature                                                        //141222
{  // Used by hourly soil temperature
   float32                 avg;
   float32                 avg_half_amplitude;
   int16                   phase;
 public:
   bool is_calibrated()                                             affirmation_;//150430
};
} // namespace CS
//_2015-04-24___________________________________________________________________


#define  LABEL_simple      "simple"
#define  LABEL_energy      "energy"

#define  LABEL_very_low     "very_low"
#define  LABEL_low          "low"
#define  LABEL_medium       "medium"
#define  LABEL_medium_high  "medium_high"
#define  LABEL_high         "high"
#define  LABEL_very_high    "very_high"
#define  LABEL_specified    "specified"


#define max_valid_temperature 50   /*C; temperature data above this value are rejected*/
#define min_valid_temperature -100   /*C; temperature data above this value are rejected*/

#define max_valid_precipitation_m 0.4  /*  precip. data above this value are rejected*/
#define min_valid_precipitation_m -0.000000001

#define max_valid_solar_rad 50   /*    solar rad data above this value are rejected */
#define min_valid_solar_rad 0.00001 /* -0.000001 min solar radiation */

#define min_valid_relative_humidity 1
#define max_valid_relative_humidity 100
/* We allow relative humidity to be a little higher than 100 percent, apparently this happens.*/

#define max_wind_speed_m_d   99999999 /* Don't know this also 020610 claudio said there is to be no limit*/
#define min_wind_speed_m_d          1 /* Min Can't be zero othersize missing may be picked up as real */

#define max_valid_pot_ET_m 0.400  /*mm; ET data above this value are rejected*/
#define min_valid_pot_ET_m -0.000000001

#define max_valid_avg_vapor_pressure_deficit_kPa      6.0 /* acrd. Claudio 000612 */
#define min_valid_avg_vapor_pressure_deficit_kPa      0.0

#define max_valid_max_vapor_pressure_deficit_kPa     10.0 /* acrd. Claudio 000612 */
#define min_valid_max_vapor_pressure_deficit_kPa      0.0


#define     Stephan_Boltzmann_MJ_K4_m2_day 4.903e-9  /* MJ/m2/day */
#endif

