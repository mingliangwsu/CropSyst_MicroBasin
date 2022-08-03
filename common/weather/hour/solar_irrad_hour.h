#ifndef solar_irrad_hourH
#define solar_irrad_hourH

class Solar_radiation;                                                           //140715
namespace CS
{
   class Solar_irradiance_extraterrestrial_hourly;
}
//______________________________________________________________________________
class Solar_irradiance_hour
{
   const Solar_radiation                        &solar_irradiance_daily;         //140715
   const CS::Solar_irradiance_extraterrestrial_hourly &extraterrestrial_solar_irradiance;//150627
 private:  // The following may be moved to actual solar radiation
   float64 diffuse_solar_irradiance[24]; // the units are specified by the passed units code
   float64 direct_solar_irradiance[24]; // the units are specified by the passed units code
   float64 solar_irradiance[24];
 public: // constructor
   Solar_irradiance_hour
   (
    const Solar_radiation &_solar_irradiance_daily                               //140715
   ,const CS::Solar_irradiance_extraterrestrial_hourly &_extraterrestrial_solar_irradiance //150627
   );
 public: // processing
   virtual bool update();                                                        //140715
 public: // accessors
   inline float64 get_diffuse_solar_irradiance  (CORN::Hour hour)                const { return diffuse_solar_irradiance[hour];}
   inline float64 get_direct_solar_irradiance   (CORN::Hour hour)                const { return direct_solar_irradiance[hour];}
   inline float64 get_solar_irradiance          (CORN::Hour hour)                const { return solar_irradiance[hour];}
};
//______________________________________________________________________________
#endif
