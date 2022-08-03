// This file is intended to be #include,  do not add it to and ID project or makefile source file list
//_____________________________________________________________________________/

class Canopy_biomass_continuum_abstract       // rename to Above_ground_biomass_abstract
{
protected:
   const Biomass_parameters         &biomass_parameters;
   const Canopy_parameters          &canopy_parameters;
   const Thermal_time_parameters    &thermaltime_parameters;
   cognate_ const CropSyst::Phenology_interface       *phenology;                //101101
protected:
   cognate_ const CropSyst::Canopy_cover_abstract     *canopy;          // required
   cognate_ const Transpiration_interface             *transpiration;   //110825 required
   const Air_temperature_average                      &air_temperature_average;
   const Solar_radiation                              &solar_radiation;
   const Vapor_pressure_deficit_daytime               &VPD_daytime;
   cognate_ const CropSyst::Crop_CO2_response         *CO2_response;    // optional       //110913
protected:
   float64 production_daily_raw;
   float64 production_cum_raw;
   float64 biomass_harvestable_cum;                                              //110325 Cumulative_Harvestable_Biomass or CumulativeHarvestableBiomass  or  CumulativePotentialHarvestableBiomass
protected:
   inline const float64 */*140810  Ref_to_const_float*/  ref_production_daily_raw()                          { return &production_daily_raw; };
   inline const float64 */*140810  Ref_to_const_float*/  ref_production_cum_raw()                            { return &production_cum_raw; };
protected:  // constructor
   Canopy_biomass_continuum_abstract
      (const Biomass_parameters        &_biomass_parameters
      ,const Canopy_parameters         &_canopy_parameters
      ,const Thermal_time_parameters   &_thermaltime_parameters
      ,const Air_temperature_average         &_air_temperature_average           //140815
      ,const Solar_radiation                 &_solar_radiation                   //140815
      ,const Vapor_pressure_deficit_daytime  &_VPD_daytime                       //140815

      //140815,const Weather_provider          &_weather
      );                               //101204
public:
   inline void know
      (const CropSyst::Canopy_cover_abstract *_canopy
      ,const Transpiration_interface         *_transpiration
      ,const CropSyst::Phenology_interface   *_phenology                         //110825
      ,const CropSyst::Crop_CO2_response     *_CO2_response_optional = 0) cognition_
      {  canopy         = _canopy;
         transpiration  = _transpiration;
         CO2_response   = _CO2_response_optional ;
         phenology      = _phenology;
      };
public:
   virtual float64 grow_potential()                                modification_;// CalculatePotentialGrowth();
   virtual float64 start();
   virtual float64 remove_yield(float64 yield)                     modification_;//100827
      /**< returns the initial biomass;
      */
   inline virtual float64 get_harvestable_biomass_cum()                    const { return biomass_harvestable_cum; };// NYI
   virtual bool start_season();
   virtual bool start_dormancy();
   virtual bool respond_to_clipping()                              modification_ = 0;//110421
};
//_____________________________________________________________________________/
class Canopy_biomass_continuum_reference           // rename to Above_ground_biomass_reference
: public Canopy_biomass_continuum_abstract
{
   float64 &production_daily_potential;        // reference to production_daily_raw     rename to production_daily_potential   //was PotentialBiomassToday
   float64 &PotentialCumulativeBiomass;   // reference to production_cum_raw  rename to production_cumulative_potential
public:
   Canopy_biomass_continuum_reference
      (const Biomass_parameters        &_biomass_parameters
      ,const Canopy_parameters         &_canopy_parameters
      ,const Thermal_time_parameters   &_thermaltime_parameters
      ,const Air_temperature_average         &_air_temperature_average                 //140815
      ,const Solar_radiation                 &_solar_radiation                         //140815
      ,const Vapor_pressure_deficit_daytime  &_VPD_daytime                             //140815
      //140815,const Weather_provider          &_weather
      );                               //101204
   inline const float64 */*140810  Ref_to_const_float*/
                         ref_production_cum()                              const { return &PotentialCumulativeBiomass; };
   inline float64 get_production_cum()                                     const { return PotentialCumulativeBiomass; };
   virtual bool respond_to_clipping()                              modification_;
};
//_____________________________________________________________________________/
class Canopy_biomass_continuum_actual               // rename to Above_ground_biomass_actual
: public Canopy_biomass_continuum_abstract
{
   const float64 &AttainableBiomassToday; // reference to production_daily_raw     rename to production_daily_attainable
   const float64 &CumulativeAttainableBiomass; // reference to production_cum_raw  rename to production_cumulative_attainable

   float64 AttainableBiomassDuringYieldFormation;     // rename to production_cumulative_attainable_during_yield_formation;
   float64 BiomassToday;            // rename to production_daily
   float64 CumulativeBiomass;       // rename to production_cumulative
   float64 CumulativeFruitBiomassGrowth; // rename to fruit_production_cumulative
   float64 produced_before_yield_formation; // was BiomassProducedBeforeYieldFormation
   float64 produced_during_yield_formation; // was BiomassProducedDuringYieldFormation
   float64 water_limited_biomass_growth;    // was WaterLimitedBiomassGrowth
   bool    is_fruit_tree;
protected:
   float64 calc_water_limited_growth()                                     const;
   float64 grow_actual()                                           modification_;
   float64 update_water_limited_growth()                           modification_;
public:
   Canopy_biomass_continuum_actual
      (const Biomass_parameters        &_biomass_parameters
      ,const Canopy_parameters         &_canopy_parameters
      ,const Thermal_time_parameters   &_thermaltime_parameters
      ,bool  _is_fruit_tree                                                      //110427
      ,const Air_temperature_average         &_air_temperature_average                 //140815
      ,const Solar_radiation                 &_solar_radiation                         //140815
      ,const Vapor_pressure_deficit_daytime  &_VPD_daytime                             //140815
      //140815,const Weather_provider          &_weather
      );                               //101204
   bool process();
   virtual float64 start();
   virtual float64 grow_potential()                                modification_;
   inline const float64 */*140810  Ref_to_const_float*/  ref_production_cum()                          const { return &CumulativeBiomass;};
   inline float64 get_production_cum()                                     const { return CumulativeBiomass;};
   inline float64 get_produced_during_yield_formation()                    const { return produced_during_yield_formation; };
   inline float64 get_produced_before_yield_formation()                    const { return produced_before_yield_formation; };
   inline float64 get_production_daily()                                   const { return BiomassToday; };
   inline float64 get_production_fruit()                                   const { return CumulativeFruitBiomassGrowth; };
   virtual float64 remove_yield(float64 yield)                     modification_; //110331
   virtual bool respond_to_clipping()                              modification_;
   virtual bool start_dormancy()                                   modification_; //110421
};
//_____________________________________________________________________________/
