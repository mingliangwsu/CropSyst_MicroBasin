//---------------------------------------------------------------------------

#pragma hdrstop

#include "crop_greenhouse.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef NYI

Crop_greenhouse::Parameters::Parameters
:  Common_parameters_data_record()              // Spreadsheet
,  specific_leaf_area         (18.0)            // A4
,  base_temperature           (10.0)            // A5
,  opt_temperature            (30)              // A6
,  max_temperature            (40)              // A7
,  transplanting_density      (2.105)           // A8
,  crop_coef_min              (0.2)             // A15
,  crop_coef_max              (1.4)             // A16
,  TTA_maturity               (1479.9)          // A9

,  ATTf                       (1462.293)        // B29

,  PAR_extinction_coef        ( 0.64)           // A17
,  radiation_use_efficiency   (0.0032)          // A18
,  transpiration_use_efficiency_coef(0.005)     // A19
,  a_uptake_coef              ( -0.0000003)     // A24
,  b_uptake_coef              (0.0667)          // A25
,  c_uptake_coef              (100.77)          // A26
,// Growth
,  Lo                         (0.009453)        // B27
,  Lf                         (9)               // B28
,  L50                        (2.862305)        // B30
,  ATT50                      (720).0)          // B31

,  ff                         (0.3)             //
{
}
//______________________________________________________________________________
Crop_greenhouse::Crop_greenhouse
(Parameters &_parameters
,Weather_for_crop_interface   &_weather
)
: CropSyst::Crop_interfaced()                                                    //131008NS
, thermal_time_accum(0.0)
, environment(_weather)
, above_ground_biomass_total_TUE_based(0)
{
}
//______________________________________________________________________________
/*
I have taken out the equations from the spreadsheet and 'converted' it
to more code like version to more easily identify the equations.
Below shows the respective column/equations with the original Excel equation
and my conversion.

I would probably start by taking the CropSyst crop model and create a
new derived subclass (As I did for CropGro, and Fruit tree models) since it
looks like we will still need some of the basic equations from CropSyst.
I think two elements we will probably want to use directly from CropSyst
instead of from this spreadsheet model is thermal time accumulation and
the canopy LAI/Biomass 'canopy history array'.

See my notes (RLN) in the text.

These equations are taken from the tomato spreadsheet.
Assuming the other spreadsheets are the same but I haven't checked in
detail yet (I only did a cursorary look and dont yet see any
differences other than columns that may have been added in later
'versions' of the spreadsheets.
Do you happen to know if the equations are the same in each  of the
spreadsheets before I take time to check these in detail?)

 note that:
    melon spreadsheet have different column placement.
    pepper spreadsheet has more columns.

I have provided suggested variables names
some appear to be the same as currently used in CropSyst or new as noted.
Some equations use values from the previous day, in this case
I have a second variable with the suffix _prev

The approach to crop nitrogen is much simpler than the CropSyst implementation,
I am not sure what you would want to implement in this case.
Also I am not sure how to represent soil in what I assume would be containers.
________________________________________________________________________________
The followings are column based calculations:
[A] DAT (Days after ?transplant?)
[B] DOY (Day of year)
RLN: May need new 'planting' mode in scenario editor (similar to single season
and Orchard/Vinyard- No rotation)
*/

________________________________________________________________________________
float64 Crop_greenhouse::update_thermal_time
(float64 weather_air_temperature_max
,float64 weather_air_temperature_min
,float64 weather_air_temperature_avg_2days_ago)
{  float64 air_temp_avg_today = (weather_air_temperature_max + weather_air_temperature_min) / 2.0
   float64 TTP_opt_temperature   = parameters.opt_temperature;  // TTP - Thermal Time Parameter
   float64 TTP_base_temperature  = parameters.base_temperature;
   float64 TTP_max_temperature   = parameters.max_temperature;
   float64 thermal_time_daily =
        +   (weather_air_temperature_max > TTP_opt_temperature)                           // + IF(C41>$A$6
            ? (1.0 / (weather_air_temperature_max - weather_air_temperature_min) )        //     ,(1/(C41-D41))
              * ( pow((TTP_opt_temperature - weather_air_temperature_min) , 2.0)          //       *(($A$6-D41)^2
                 / 2.0 +  (weather_air_temperature_min - TTP_base_temperature)            //         /2+(D41-$A$5)
                        * (TTP_opt_temperature - weather_air_temperature_min)             //            *($A$6-D41)
                       + ( (weather_air_temperature_max - TTP_opt_temperature)            //       +((C41-$A$6)
                         * (TTP.opt_temperature - TTP_base_temperature)                   //         *($A$6-$A$5)
                         * (0.5 + (0.5 * (parameters.max_temperature                      //         *(0.5+(0.5*($A$7
                                         - weather_air_temperature_max))                  //                     -C41))
                                 / (parameters.max_temperature - TTP_opt_temperature))))  //               /($A$7-$A$6))))
            :  (weather_air_temperature_min < TTP_base_temperature)                       //     ,IF(D41<$A$5
               ? ( pow((weather_air_temperature_max - TTP_base_temperature) , 2.0)        //        ,((C41-$A$5)^2
                   /(2.0 * (weather_air_temperature_max                                   //          /(2*(C41
                           -weather_air_temperature_min)))                                //               -D41)))
               :  (weather_air_temperature_min > TTP_base_temperature)                    //        ,IF(D41>$A$5
                  ?  (0.5 * (weather_air_temperature_min                                  //           ,(0.5*(D41
                           + weather_air_temperature_max)                                 //                  +C41)
                            - TTP.base_temperature)                                       //                 -$A$5)
                  :  (weather_air_temperature_min == TTP_base_temperature)                //          ,IF(D41=$A$5
                     ? (weather_air_temperature_avg_2days_ago - TTP_base_temperature)     //              ,(0.5*(D38+C38)-$A$5)
                     : 0.0 ;                                                                              ))))
   thermal_time_accum += thermal_time_accum + thermal_time_daily;                         // G41 = ....
   return thermal_time_accum;
}
________________________________________________________________________________
void Crop_greenhouse::initialize()
{
   // RLN note: In the tomato spreadsheet this was calculated every day,
   // but is it appears essentially constant - need to check the other spreadsheets.
   // (ln is natural logrithm).
   Gompertz_coef =                                                                        //    J =(
      - CORN_ln(  (CORN_ln(L50 / Lf)                                                      //        -LN((LN($B$30/$B$28)
                / (CORN_ln(Lo / Lf))))                                                                  /(LN($B$27/$B$28))))
        / ATT50;                                                                                    /$B$31)
   LAI_gain_cum      = Lo;
   LAI_gain_cum_prev = Lo;
   LAI_gain          = Lo;
   LAI_standing_cum  = Lo;
   biomass_aboveground        =  Lo / parameters.specific_leaf_area;                      // U =Lo/parameters.specific_leaf_area
   biomass_aboveground_prev   =  biomass_aboveground;
   above_ground_biomass_total_TUE_based=Lo/$A$4
   above_ground_biomass_total = biomass_aboveground;                                      // AE=$B$27/$A$4
}
________________________________________________________________________________
void Crop_greenhouse::start_day()
{  total_biomass_gain_TUE_based_prev = total_biomass_gain_TUE_based;
   total_biomass_gain_prev = total_biomass_gain;
   LAI_gain_cum_prev = LAI_gain_cum;
   biomass_aboveground_prev = biomass_aboveground;
   total_biomass_gain_prev = total_biomass_gain; //
   above_ground_biomass_total_prev =  above_ground_biomass_total;
}
//______________________________________________________________________________
bool Crop_greenhouse::process(uint32 today32)
{
   float64 Tmax_today      = environment.get_curr_max_temperature();                      // from column C
   float64 Tmin_today      = environment.get_curr_min_temperature();                      // from column D
   float64 Tavg_2days_ago  = environment.get_avg_temperature(2 days ago);                 // from column C, but 2 rows/days before
   need average air temperature from 2 days agao

   float64 thermal_time_cum = update_thermal_time(Tmax_today,Tmin_today,Tavg_2days_ago);

   //check used   float64 daytime_VPD                 = weather.get_curr_avg_daytime_vapor_pressure_deficit();

   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   {  // Cumulative LAI Gain
      float64  b = -CORN_ln(parameter.Lo / parameter.Lf);
      // Unlike the CropSyst Crop model,
      // - we compute the cumulative curve then determine the change as the daily value.
      // - we donot store the GAI/LAI in a history array.
      LAI_gain_cum =                                                                         // K =
         (thermal_time_cum <= ATTf)  // In the original spreadsheet equation, the < and = conditions appear to be the same and the documentation uses <= so I consolidated them
      //          (thermal_time_cum < ATTf)                                                          // =IF(G41<$B$29
      //          ?   Lf * exp(-b * exp(-Gompertz_coef * thermal_time_cum))                          //     ,($B$28)*EXP((-(-LN($B$27/($B$28))))*(EXP(-J41*G41)))
      //          :   (thermal_time_cum = ATTf)                                                      //     ,IF(G41=$B$29
            ? Lf * exp(-b * exp(-Gompertz_coef * thermal_time_cum))                          //         ,($B$28)*EXP((-(-LN($B$27/($B$28))))*(EXP(-J41*G41)))
            :  (thermal_time_cum > ATTf)                                                     //         ,IF(G41>$B$29
               ? LAI_gain_cum_prev + (LAI_gain_cum_prev * ff / 100.0)                        //             ,(K40+(K40*$B$34/100))
               : 0.0);                                                                       //             ,0 )))
      LAI_gain =  LAI_gain_cum - LAI_gain_cum_prev;   // In CropSyst this is daily GAI
      LAI_standing_cum += LAI_gain;
   }
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // Fraction intereption PAR total biomass
    float64 param_PAR_extinction_coef = parameters.PAR_extinction_coef; // Quick local
    fract_interception_PAR_total_biomass                                                      // O =1-EXP(-$A$17*K40)
       = 1.0 - exp( - PAR_extinction_coef * LAI_gain_cum);
    //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // Crop Coefficient (FAO radiation model)
    float64 param_crop_coef_min = parameters.crop_coef_min;
    float64 param_crop_coef_max = parameters.crop_coef_max;
    // Note In CropSyst this is a constant?
    float64 crop_coef                                                                         // P =
       = param_crop_coef_min                                                                  //   $A$15
        + (( (param_crop_coef_max                                                             //   +((($A$16
              * (1.0 - exp(- param_PAR_extinction_coef * LAI_standing_cum)))                  //       *(1-EXP(-$A$17 * N40)))
            / (1.0 - exp(-PAR_extinction_coef * 4.0)))                                        //      /(1-EXP(-$A$17*4)))
           * (param_crop_coef_max - param_crop_coef_min)                                      //     *($A$16-$A$15))
          );                                                                                  //
    crop_coef = CORN_must_be_between(crop_coef,param_crop_coef_min,param_crop_coef_max);
    //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // Corrected crop coefficient (FAO)
    crop_coef_corrected                                                                       // Q
       =  (crop_coef < param_crop_coef_min)                                                   //  =IF(P40<$A$15
          ? crop_coef                                                                         //     ,$A$15
          : (crop_coef > param_crop_coef_max)                                                 //     ,IF(P40>$A$16
             ? crop_coef_max                                                                  //        ,$A$16
             :(crop_coef_min < crop_coef)                                                     //        ,IF($A$15<P40
                   ? (param_crop_coef_min                                                     //           ,($A$15
                        + ( ( (param_crop_coef_max                                            //               +((($A$16
                               * (1.0 - EXP(-PAR_extinction_coef * LAI_standing_cum)))        //                   *(1-EXP(-$A$17*N40)))
                              / (1.0 - EXP(-PAR_extinction_coef * 4.0)))                      //                  /(1-EXP(-$A$17*4)))
                            * (param_crop_coef_max - param_crop_coef_min)))                   //                 *($A$16-$A$15)))
                   : (crop_coef < param_crop_coef_max)                                        //           ,IF(P40<$A$16
                      ?(param_crop_coef_min                                                   //              ,($A$15
                        + ( ( (param_crop_coef_max max                                        //                +((($A$16
                               * (1.0 - exp(-PAR_extinction_coef * LAI_standing_cum)))        //                    *(1-EXP(-$A$17*N40)))
                              / (1.0 - EXP(-PAR_extinction_coef * 4.0)))                      //                  /(1-EXP(-$A$17*4)))
                            *(param_crop_coef_max-param_crop_coef_min)))                      //                   *($A$16-$A$15)))))))
                      : 0.0;                                                                  // Not in original spreadsheet equation, could be problematic

          // RLN: reminder to self, the repeated terms in this conditional
          // expression can be optimized, but I want to look at
          // mellon and pepper spreadsheets to see how this is done.
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   // Crop Transpiration (kg/m2/day) (FAO)
   // I believe this is the same a CropSyst pot_transpiration_kg_m2
   float64 crop_transpiration  // kg/m2
      = ET_pot_reference * crop_coef_corrected;                                              // R = H40 * Q40
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   // PAR Interception (MJ/m2/day)
   float64 solar_irradience= weather.get_curr_solar_radiation_MJ_m2();
   float64 PAR_interception=solar_irradience * 0.45 * fract_interception_PAR_total_biomass;  // S=E40*0.45*O40
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   // Total biomass Gain (kg/m2/day)
   // RLN: above ground or total plant????
   // RLN: Probably essentially the same variable as intercepted_PAR_dependent_growth?
   biomass_gain = radiation_use_efficiency * PAR_interception;                               // T=$A$18 * 0.45 * E40 * O40
/*
RLN: I presume 0.45 is a conversion from solar_irradience to
photosythetically active radiation. CropSyst uses 0.5 for this,
would 0.45 be a 'greenhouse' (5%) adjustment?
There does not appear to be transpiration or temperature limitation
applied in this model (temperature and water stress are not factors,
probably not applicable to greenhouse conditions and management?)
Isn't the temperature limitiation either/both a low or high high
temperature stress),
wouldn't that (at least high) be more likely in a green house?
(We could probably assume that in 'greenhouse mode' there is
'optimal' management, no nitrogen or water limitations or
automatic management.)
*/
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   // Aboveground total biomass (kg/m2)
   biomass_aboveground =biomass_gain + biomass_aboveground_prev                              // U=T40+U40
/*
The spreadsheet reports two biomasses labeled as 'TUE based' and 'results'
do we need to calculate/report both?
*/
/*_______*/    //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
/* These spreadsheet has the following columns of measured data
V Above ground (Measured)
W Transpration (Measured)
X Total LAI (measured)
Y Standing (LAI) measured
*/
   //_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
   // N Uptake total biomass
                                                                                             // Z =($A$24*(AE40*10000)*(AE40*10000))+($A$25*(AE40*10000))+$A$26
   float64 N_uptake_total_biomass (kg/ha)
         = (parameters.a_uptake_coef * kg_per_m2_to_kg_per_ha(above_ground_biomass_total)
                                     * kg_per_m2_to_kg_per_ha(above_ground_biomass_total))
         + (parameters.b_uptake_coef * kg_per_m2_to_kg_per_ha(above_ground_biomass_total))
         +  parameters.c_uptake_coef;
   ________________________________________________________________________________
   // AA N uptake
   // This column in the spreadsheet stores measured values.
   // ________________________________________________________________________________
   //  Total biomass Gain (kg/m2/day)  (TUE based (FAO/Rad model))
   float64 total_biomass_gain_TUE_based                                                      // AB=$A$19*R40
           = transpiration_use_efficiency_coef * crop_transpiration;
   // The spreadsheet reports two biomasses labeled as 'TUE based' and 'results'
   //  do we need to calculate/report both?
   //________________________________________________________________________________
   float64 above_ground_biomass_total_TUE_based   //(TUE based (FAO/Rad model))              // AC =$B$27/$A$4
        above_ground_biomass_total_TUE_based += total_biomass_gain_TUE_based;                // =AB40+AC40
   // ? xxx = total_biomass_gain_TUE_based_prev + above_ground_biomass_total_TUE_based
   // The spreadsheet reports two biomasses labeled as 'TUE based' and 'results'
   // do we need to calculate/report both?
   //________________________________________________________________________________
   //  Total biomass gain
   float64 total_biomass_gain                                                                // AD = MIN(T40,AB40)
      =std::min<float64>(biomass_gain,total_biomass_gain_TUE_based)
   //________________________________________________________________________________
   // Total above ground biomass                                                             // AE =AD40+AE40
   float64  above_ground_biomass_total
      += total_biomass_gain_prev + total_biomass_gain;
}
//______________________________________________________________________________
Crop_mass_fate_biomass_and_nitrogen *
Crop_greenhouse::process_biomass_fate
(Biomass_fated_cause fated_cause
,Harvest_amount_mode harvest_amount_mode                                         //050822
,float64 remove_amount_kg_m2                                                     //050822
   // remove_fixed_amount_kg_ha if harvest_amount_mode=HARVEST_REMOVE_FIXED_AMOUNT_BIOMASS  else 0.0
,float64 management_retain_GAI                                                   //050822
   // if harvest_amount_mode=HARVEST_RETAIN_GAI                   else 0.0
,float64 management_retain_biomass                                               //110603
,const Biomass_fate_parameters  &biomass_fate_parameters
,bool terminate
,float64 yield_now)
{
/*
M LAI_loss_per_pruning
LAI loss per pruning
In CropSyst, we would simply perform the clipping/prunning operation
which would removed (GAI) from the 'history array'.
(WHY IS BIOMASS NOT ALSO REMOVED IN THESE EQUATIONS?
I think something is missing here)

N  LAI_standing_cum
   LAI_standing_cum_prev (from previous_day)
   Cumulative Standing LAI (m2/m2)
In CropSyst the history array provides clipped and unclipped
 GAI/Biomass, so this would probably the same as CropSyst (Canopy portions).
First day
=L40-M40
=LAI_gain - LAI_loss_per_pruning
Thereafter
=N40+(L41-M41)
=LAI_standing_cum_prev + (LAI_gain - LAI_loss_per_pruning)
*/
}
//_2007-06-25___________________________________________________________________
#endif

