// This file is intended to be #include,  do not add it to an IDE project or makefile source file list
// (Not currently used in CropSyst, but used in VIC_crop_biomass
//_____________________________________________________________________________/
Canopy_biomass_continuum_abstract::Canopy_biomass_continuum_abstract
(const Biomass_parameters        &_biomass_parameters
,const Canopy_parameters         &_canopy_parameters
,const Thermal_time_parameters   &_thermaltime_parameters
,const Air_temperature_average         &_air_temperature_avg                     //140815
,const Solar_radiation                 &_solar_radiation                         //140815
,const Vapor_pressure_deficit_daytime  &_VPD_daytime                             //140815
//140815,const Weather_provider          &_weather
)                                      //101204
: biomass_parameters    (_biomass_parameters)
, canopy_parameters     (_canopy_parameters)
, thermaltime_parameters(_thermaltime_parameters)
, phenology             (0)                                                      //101101
, canopy                (0)
, transpiration         (0)
, air_temperature_average(_air_temperature_avg)                                  //140815
, solar_radiation        (_solar_radiation)                                      //140815
, VPD_daytime            (_VPD_daytime)                                          //140815
/*140815
, air_temperature_average(_weather.air_temperature_avg)
, solar_radiation        (_weather.solar_radiation)
, VPD_daytime            (_weather.vapor_pressure_deficit_daytime)
*/
, CO2_response          (0)
, production_daily_raw  (0.0)
, production_cum_raw    (0.0)
{
   // Assumes intial GAI = -ln(1-Fract Solar Interception)/0.5, where 0.5 is solar rad extinction coeff.
   // Also assumes leaf area density = 20 m2/kg
/*100608 moved to emerge
   float64 initial_biomass
      = (-log(1.0 - canopy_parameters.cover_initial) / 0.5) / 20.0;
            // RLN WARNING check log on ln in C++
   production_daily_raw = initial_biomass;
   production_cum_raw   = initial_biomass;
*/
}
//_____________________________________________________________________________/
float64 Canopy_biomass_continuum_abstract::remove_yield(float64 yield)         modification_
{
   production_cum_raw -= yield;
   return production_cum_raw;
}
//_2010-08-27__________________________________________________________________/
float64 Canopy_biomass_continuum_actual::remove_yield(float64 yield)           modification_
{  CumulativeBiomass -= yield;
   return CumulativeBiomass;
}
//_2011-03-31__________________________________________________________________/
Canopy_biomass_continuum_reference::Canopy_biomass_continuum_reference
(const Biomass_parameters        &_biomass_parameters
,const Canopy_parameters         &_canopy_parameters
,const Thermal_time_parameters   &_thermaltime_parameters
,const Air_temperature_average         &_air_temperature_average                 //140815
,const Solar_radiation                 &_solar_radiation                         //140815
,const Vapor_pressure_deficit_daytime  &_VPD_daytime                             //140815
//140815,const Weather_provider          &_weather
)                                      //101204
: Canopy_biomass_continuum_abstract
   (_biomass_parameters,_canopy_parameters,_thermaltime_parameters
   ,_air_temperature_average                                                     //140815
   ,_solar_radiation                                                             //140815
   ,_VPD_daytime                                                                 //140815
   //140815 , _weather
   )
, production_daily_potential       (production_daily_raw)
, PotentialCumulativeBiomass  (production_cum_raw)
{}
//_____________________________________________________________________________/
Canopy_biomass_continuum_actual::Canopy_biomass_continuum_actual
(const Biomass_parameters        &_biomass_parameters
,const Canopy_parameters         &_canopy_parameters
,const Thermal_time_parameters   &_thermaltime_parameters
,bool  _is_fruit_tree                                                            //110427
,const Air_temperature_average         &_air_temperature_avg                    //140815
,const Solar_radiation                 &_solar_radiation                         //140815
,const Vapor_pressure_deficit_daytime  &_VPD_daytime                             //140815
//140815,const Weather_provider          &_weather
)                                      //101204
: Canopy_biomass_continuum_abstract
   (_biomass_parameters,_canopy_parameters,_thermaltime_parameters
   ,_air_temperature_avg
   ,_solar_radiation
   ,_VPD_daytime
  //140814 , _weather
   )
, AttainableBiomassToday               (production_daily_raw)
, CumulativeAttainableBiomass          (production_cum_raw)
, BiomassToday                         (production_daily_raw)
, AttainableBiomassDuringYieldFormation(0.0)
, CumulativeBiomass                    (0.0)
, produced_before_yield_formation      (0.0)
, produced_during_yield_formation      (0.0)
, water_limited_biomass_growth         (0.0)
, is_fruit_tree                        (_is_fruit_tree)                          //110427
{}
//_____________________________________________________________________________/
float64 Canopy_biomass_continuum_abstract::grow_potential()                    modification_
{  float64 gain = 0.0;

   float64 RUE_PAR = g_to_kg(biomass_parameters.RUE_PAR);/*per MJ*/                  // CropParameters.GetRadiationUseEfficiency / 1000.0; //'Convert g/MJ to Kg/MJ



   // In CropSyst proper early_growth_limit_temp has been replaced with
   // "Limitation temperatures" parameters
   // Currently we are still using the old parameter until we recalibrate the crop.

   float64 mean_temperature_for_optimum_growth_param
         = biomass_parameters.early_growth_limit_temp;                   // OptimumMeanTemperatureForGrowth
            // 140317 was opt_mean_temperature_for_growth

   float64 air_temperature_mean = air_temperature_average.Celcius();
   float64 base_temperature_param = thermaltime_parameters.base_temperature;
   float64 temperature_adjustment_factor
      = (air_temperature_mean - base_temperature_param)
       /(mean_temperature_for_optimum_growth_param - base_temperature_param);
   temperature_adjustment_factor = CORN::must_be_between<float64>
      (temperature_adjustment_factor,0.0,1.0);
   float64 CO2_RUE_adjustment= CO2_response? CO2_response->actual_biomass_gain_ratio_in_response_to_CO2_RUE/*131209 RUE_adjustment*/ : 1.0; // CropState.CO2AdjustmentToRUE(TimeState.DaysAfterPlanting)
   float64 CO2_TUE_adjustment= CO2_response? CO2_response->get_TUE_adjustment() : 1.0; // CropState.CO2AdjustmentToTUE(TimeState.DaysAfterPlanting)
   float64 PAR_intercepted_fraction = canopy->get_PAR_solar_rad_intercepted_green_canopy() ;
   float64 solar_rad =  solar_radiation.get_MJ_m2();                             // WeatherData.GetSolRad(TimeState.CurrentYear, TimeState.DayOfYear))
   if (!phenology->is_mature())
   {
      float64 radiation_biomass_gain
            = CO2_RUE_adjustment
            * RUE_PAR
            * PAR_intercepted_fraction
            * (0.5 * solar_rad)      // PAR solar rad
            * temperature_adjustment_factor;
      //'Calculate transpiration-based biomass gain for the potential crop
      float64 daytime_VPD =
         VPD_daytime.get_in_units(UC_kPa);
      if (CORN::is_approximately<float64>(daytime_VPD,0.0,0.00001))              //101028 added by RLN for debugging
         return 0.0;
      float64 WUE_at_1_kPa_VPD_kg_kg =  biomass_parameters.WUE_at_1_kPa_VPD / 1000.0;
      float64 slope_of_WUE_function_of_VPD  =
      #ifdef CROP_PARAMETERS_HARDCODED
           biomass_parameters.slope_of_water_use_efficiency_function_of_VPD;     // The V.B. version enters this as negative value
      #else
           biomass_parameters.TUE_scaling_coef[0];  // The C++ version enters this as positive value
      #endif
      float64 transpiration_potential_mm = transpiration->get_potential_mm();
      float64 transpiration_based_biomass_gain
            = CO2_TUE_adjustment                                                 // CO2_Adjustment_Factor_For_TUE
            * WUE_at_1_kPa_VPD_kg_kg
            * transpiration_potential_mm
              / pow(daytime_VPD                                                  // WeatherState.DayTimeVPD(Year_Count, DOY)
                ,slope_of_WUE_function_of_VPD);
      //'Today attainable biomass is the minimum of radiation and transpiration-based biomass gain
      gain =

      // make 1.0 parameter

         ((radiation_biomass_gain > transpiration_based_biomass_gain) && (daytime_VPD > 1.0))                                                     //110826
         ? transpiration_based_biomass_gain                                      //110826
         : radiation_biomass_gain;
      production_cum_raw += gain;
   }                                                                            //100720
   production_daily_raw = gain;
   return  gain;
}
//____________________________Canopy_biomass_continuum_abstract::CalculatePotentialGrowth__/
float64 Canopy_biomass_continuum_actual::grow_potential()                      modification_
{  float64 biomass_gain = Canopy_biomass_continuum_abstract::grow_potential();
   if (phenology->is_in_yield_formation())
      AttainableBiomassDuringYieldFormation += biomass_gain;
   return biomass_gain;
}
//______________________________Canopy_biomass_continuum_actual::CalculatePotentialGrowth__/
float64 Canopy_biomass_continuum_actual::update_water_limited_growth()         modification_   //was DetermineWaterLimitedBiomassGrowth // CalculateWaterLimitedBiomassGrowth
{  float64 Tr_pot =  transpiration->get_potential_mm();
   float64 WSfact_yesterday =  transpiration->get_water_stress_factor_yesterday();
   water_limited_biomass_growth =  // RLN now member
      (Tr_pot  > 0)                                                              // CropState.ActualCropPotentialTranspiration(DACE)
      ? WSfact_yesterday * AttainableBiomassToday
      : 0.0;                                                                     // CropState.WaterLimitedBiomassGrowth(DACE) = water_limited_biomass_growth;
   return water_limited_biomass_growth;
}
//__________________________________________________calc_water_limited_growth__/
float64 Canopy_biomass_continuum_actual::grow_actual()                                       // was DetermineActualBiomassGrowth //was  CalculateActualBiomassGrowth
{                                                                                // now a member float64 water_limited_biomass_growth = WaterLimitedBiomassGrowth; // CropState.WaterLimitedBiomassGrowth(DACE)
   BiomassToday = water_limited_biomass_growth;
   CumulativeBiomass += water_limited_biomass_growth;
   if (phenology->is_in_yield_formation())                                       // was forming_yield
      produced_during_yield_formation += water_limited_biomass_growth;
   else
      if (phenology->get_days_since_start_of(NGS_BULK_FILLING) == 0)
         produced_before_yield_formation += water_limited_biomass_growth;
      // else we are after yield production
   if (is_fruit_tree)                                                            //   If CropParameters.TreeFruitCrop And CropState.DevelopmentStage(DACE) = "Fruit Growth" Then
   {  static const float64 Biomass_Partitioning_To_Fruit = 1.0;
      CumulativeFruitBiomassGrowth +=
         water_limited_biomass_growth * Biomass_Partitioning_To_Fruit;           //      CropState.CumulativeFruitBiomassGrowth = CropState.CumulativeFruitBiomassGrowth + Water_Limited_Biomass_Growth * Biomass_Partitioning_To_Fruit
   }                                                                            //   End If
   return BiomassToday;
}
//________________________________________________________________grow_actual__/
bool Canopy_biomass_continuum_actual::process()
{  update_water_limited_growth();                                                // Call ActBiom.CalculateWaterLimitedBiomassGrowth(CropState, TimeState)
   //'Calculate actual biomass growth
   grow_actual();                                                                // Call ActBiom.CalculateActualBiomassGrowth(CropState, TimeState)
   return true;
}
//____________________________________________________________________process__/
float64 Canopy_biomass_continuum_abstract::start()                                           //101020 was emerge
{  float64  initial_biomass
      = (-log(1.0 - canopy_parameters.initial_cover) / 0.5) / 20.0;
   production_daily_raw    = initial_biomass;
   production_cum_raw      = initial_biomass;
   biomass_harvestable_cum = initial_biomass;                                    //110623
   return initial_biomass;
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _/
float64 Canopy_biomass_continuum_actual::start()
{  float64  initial_biomass = Canopy_biomass_continuum_abstract::start();                    //101101
   if (is_fruit_tree)                                                            //110510
   {  initial_biomass = 0;                                                       //110510
      production_daily_raw = initial_biomass;                                    //110512
      production_cum_raw   = initial_biomass;                                    //110512
   }
   CumulativeFruitBiomassGrowth     = 0.0;                                       //110512
   BiomassToday                     = initial_biomass; // rename to production_daily
   CumulativeBiomass                = initial_biomass; // rename to production_cumulative
   produced_before_yield_formation  = initial_biomass; // was BiomassProducedBeforeYieldFormation
   produced_during_yield_formation  = initial_biomass; // was BiomassProducedDuringYieldFormation
   AttainableBiomassDuringYieldFormation = 0;                                    //110624
   return initial_biomass;
}
//_____________________________________________________________________________/
bool Canopy_biomass_continuum_abstract::start_season()
{  start();
   return true;
}
//_2011-06-17____________________________________________________start_season__/
bool Canopy_biomass_continuum_abstract::start_dormancy()
{  // In VB Version this is done in Crop Development class when entering dormancy
   production_cum_raw = 0.0;                                                     // CropState.CumulativeBiomass(DACE) = 0 '110325
                                                                                 // CropState.PotentialCumulativeBiomass(DACE) = 0 '110325
//   biomass_harvestable_cum = 0.0;    // Warning this should be added to V.B. version
   production_daily_raw = 0;
   return true;
}
//_2011-04-05__________________________________________________start_dormancy__/
/*
bool Canopy_biomass_continuum_abstract::start_season()
{  biomass_harvestable_cum = 0.0;
   production_cum_raw = 0.0;                                                     // CropState.CumulativeBiomass(DACE) = 0 '110325
   production_daily_raw = 0;
   return true;
}
//_2011-06-17_________________________________________________________start_season()
*/
bool Canopy_biomass_continuum_actual::start_dormancy()
{  // In VB Version this is done in Crop Development class when entering dormancy
   AttainableBiomassDuringYieldFormation = 0;
   BiomassToday = 0;            // rename to production_daily
   /*Currently not clearing until dormancy ends.
   CumulativeBiomass = 0;       // rename to production_cumulative
   CumulativeFruitBiomassGrowth = 0; // rename to fruit_production_cumulative
   */
   produced_before_yield_formation = 0; // was BiomassProducedBeforeYieldFormation
   produced_during_yield_formation = 0; // was BiomassProducedDuringYieldFormation
   water_limited_biomass_growth = 0;    // was WaterLimitedBiomassGrowth
   CumulativeBiomass = 0;
   return Canopy_biomass_continuum_abstract::start_dormancy();
}
//_2001-04-05__________________________________________________start_dormancy__/
bool Canopy_biomass_continuum_reference::respond_to_clipping()
{  biomass_harvestable_cum = PotentialCumulativeBiomass;                         // CropState.CumulativePotentialHarvestableBiomass = CropState.PotentialCumulativeBiomass(DACE) 'XXX ROGER LATEST March 25 2011
   return true;
}
//_2004_04-21___________________________________________________________________
bool Canopy_biomass_continuum_actual::respond_to_clipping()
{
   biomass_harvestable_cum = CumulativeBiomass;                                  // CropState.CumulativeHarvestableBiomass = CropState.CumulativeBiomass(DACE) 'XXX ROGER LATEST March 25 2011
   return true;
}
//_2004_04-21___________________________________________________________________

