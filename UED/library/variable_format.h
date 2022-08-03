#ifndef variable_formatH
#define variable_formatH
#include "corn/container/enumlist.h"
#include "corn/metrology/units_code.hpp"
#include "UED/library/varcodes.h"
#include "corn/parameters/parameter.h"
namespace UED {
//______________________________________________________________________________
class Variable_format_abstract
: public extends_ CORN::Enumeration
{
 public:
   Variable_code_clad   code_clad;
   CORN::Units_clad     preferred_units_clad; // this is simply the smart representation of preferred_units_code, could probaby get rid and make local when used //990512
 public:
   Variable_format_abstract();
   Variable_format_abstract
      (UED::Variable_code code
      ,CORN::Units_code  preferred_units_code);
   Variable_format_abstract(const Variable_format_abstract &original);
   inline virtual bool is_key_nat32(nat32 key)                     affirmation_  //180820
      { return code_clad.get() == key; }
   inline virtual nat32 get_key_nat32()        const { return code_clad.get(); } //020319
 public: // accessors
   inline const Variable_code_clad &ref_smart_variable_code()              const { return code_clad;} //010216
   virtual const std::string &ref_description()                            const=0;
};
//_2016-06-20___________________________________________________________________
class Variable_format_ontological
: public extends_ Variable_format_abstract
{
 public:
   std::string          ontology; // should be qualified (but not fully)
 public:
   Variable_format_ontological();
   Variable_format_ontological
      (UED::Variable_code code
      ,CORN::Units_code  preferred_units_code
      ,const char *ontology);
   virtual nat32        compute_variable_format_size()                    const;
   virtual int          compare(const CORN::Item &other)                  const; //980210
   virtual const char  *label_string(std::string &buffer)                 const; //170423
   virtual const std::string &ref_description()                           const  { return ontology; } //160620
#ifdef UED_DUMP
   virtual void dumpX(std::ostream &txt_strm) ;
#endif
   virtual void write_YAML(std::ostream &YAML_strm,nat16 indent_level);          //180108
};
//_2016-06-20___________________________________________________________________
class Variable_format_0
: public extends_ Variable_format_abstract                                       //160619
, public extends_ CORN::Parameter_range
{
 private:
   bool owns_description_and_abbreviation; // This is true when this allocated and must deallocate the description and abbreviation strings //070223
 public:
   std::string description; // Can be left blank if smart variable code can compose a description //980623
   std::string abbreviation;                                                     //020906
 public: // Constructors
      // constructor for definitions in the database file
   Variable_format_0();                                                          //971106
      // constructor for standard definitions.
   Variable_format_0                                                             //971106
      (UED::Variable_code code
      ,CORN::Units_code  preferred_units_code                                    //980818
      ,float32     min_warning
      ,float32     max_warning
      ,float32     min_error
      ,float32     max_error
      ,const char *description
      ,const char *abbreviation);
      // copy constructor
   Variable_format_0(const Variable_format_0 &original);                         //971208
 public:
   inline bool          is_local()                                        const  //040909
      { return (code_clad.get() & 0x80000000) > 0; }
   virtual nat32        compute_variable_format_size()                    const;
   virtual int          compare(const CORN::Item &other)                  const; //980210
   virtual const char  *label_string(std::string &buffer)                 const; //170423
   virtual const std::string &ref_description()                           const
      { return description; }
#ifdef UED_DUMP
   virtual void dump(std::ostream &txt_strm) ;
#endif
   virtual void write_YAML(std::ostream &YAML_strm,nat16 indent_level);          //180108
};
//_1998-02-10_______________________________________________Variable_format_0__/
extern Variable_format_0  STD_VD_date;                                           //020907
extern Variable_format_0  STD_VD_precipitation;               // Day or less
extern Variable_format_0  STD_VD_avg_temperature;             // any timestep    //000908
extern Variable_format_0  STD_VD_obs_temperature;             // any timestep    //020427
extern Variable_format_0  STD_VD_max_temperature;             // any timestep
extern Variable_format_0  STD_VD_min_temperature;             // any timestep
extern Variable_format_0  STD_VD_max_dew_point_temperature;   // any timestep
extern Variable_format_0  STD_VD_min_dew_point_temperature;   // any timestep
extern Variable_format_0  STD_VD_avg_dew_point_temperature;   // any timestep    //050601
extern Variable_format_0  STD_VD_max_relative_humidity;       // any timestep
extern Variable_format_0  STD_VD_min_relative_humidity;       // any timestep
extern Variable_format_0  STD_VD_avg_relative_humidity;       // any timestep    //050419
extern Variable_format_0  STD_VD_solar_radiation_global;      // daily           //131013
extern Variable_format_0  STD_VD_net_radiation;               // daily           //070204
extern Variable_format_0  STD_VD_isothermal_longwave_net_radiation;     // daily //070204
//170901 #if ((CS_VERSION >0) && (CS_VERSION <= 4))
/*170926 obsolete
#if ((CS_VERSION >0) && (CS_VERSION < 6))
extern Variable_format_0  STD_VD_solar_radiation_deprecated;             // daily
#endif
*/

//extern Variable_format_0  STD_VD_isothermal_longwave_net_radiation;//daily //110126
//131013 no such thing as total extern Variable_format_0  STD_VD_net_radiation_tota;               // daily     //110126
#if (CS_VERSION<6)
//110126 for version 5 to handle version 4 files
extern Variable_format_0  STD_VD_solar_radiation_ERRONEOUS;          // daily    //110126
extern Variable_format_0  STD_VD_isothermal_longwave_net_radiation_ERRONEOUS; // daily //110126
extern Variable_format_0  STD_VD_net_radiation_ERRONEOUS;            // daily    //110126
#endif

extern Variable_format_0  STD_VD_solar_radiation_avg_hourly;         // hourly   //100222
extern Variable_format_0  STD_VD_sunshine_hours;                     // daily    //100222
extern Variable_format_0  STD_VD_wind_speed;                  // daily
extern Variable_format_0  STD_VD_wind_direction;              // any timestep    //050419
extern Variable_format_0  STD_VD_pan_evaporation;             // day or less (intended daily) //000611

extern Variable_format_0  STD_VD_pot_evapotranspiration;      // day or less (intended daily)   //000611
extern Variable_format_0  STD_VD_act_evapotranspiration;      // day or less (intended daily)   //000611
extern Variable_format_0  STD_VD_ref_ET_Penman_Monteith;      // day or less (intended daily)   //000611
extern Variable_format_0  STD_VD_ref_ET_Priestly_Taylor;      // day or less (intended daily)   //000611
extern Variable_format_0  STD_VD_ref_ET_Hargreaves;           // day or less (intended daily)   //000611
extern Variable_format_0  STD_VD_ref_ET_ASCE_EWRI_short_crop; // day or less (intended daily)  (short crop) //091005
extern Variable_format_0  STD_VD_ref_ET_ASCE_EWRI_tall_crop;      // day or less (intended daily)  //091005
extern Variable_format_0  STD_VD_avg_daytime_vapor_pressure_deficit;   // daily  //000611
extern Variable_format_0  STD_VD_avg_fullday_vapor_pressure_deficit;   // daily  //011009
extern Variable_format_0  STD_VD_max_vapor_pressure_deficit;  // daily?          //000611
extern Variable_format_0  STD_VD_cloud_cover;                 // day time step (intended daily) //000611
extern Variable_format_0  STD_VD_snow_fall;                   // daily?          //020427
extern Variable_format_0  STD_VD_snow_depth;                  // any time step but intended daily) //020427
//______________________________________________________________________________
} // namespace UED
#endif
//variable_format.h

