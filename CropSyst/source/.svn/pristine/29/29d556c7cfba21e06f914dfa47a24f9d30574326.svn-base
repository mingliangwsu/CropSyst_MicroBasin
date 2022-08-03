#ifndef crop_greenhouseH
#define crop_greenhouseH
//---------------------------------------------------------------------------
/*
The equations and model in this class were developed by Carolina Martinez
And implemented by Roger Nelson for linking to CropSyst 4


*/
#ifdef NYI
#include <corn/parameters/parameters_datarec.h>
//______________________________________________________________________________
class Crop_greenhouse
: public CropSyst::Crop_interfaced                                               //131008NS
{
public:
   Parameters
   : public Common_parameters_data_record
   {public:
      float32  specific_leaf_area;     // Specific leaf area (m2/kg)
   // Thermal time
      float32 base_temperature;                                  // probably the same as in CropSyst
      float32 opt_temperature;         // Optimum temperature    // probably the same as in CropSyst
      float32 max_temperature;         // Maximum temperature    // probably the same as in CropSyst
   // Sowing/Planting:
      float32 transplanting_density    // Density transplanting (per plant m2)    RLN: Does not appear to be used for tomato (Obsolete?)  (may be used in the other sheets, I need to check.)
   // Phenology??
      float32 TTA_maturity;            // RLN: Don't know what TTA is (Accumulated thermal time?)    (it does not appear to be used for tomato -- Obsolete?)
      float32 ATTf;                    // accumulated thermal time when ??? (RLN I think end of vegetative growth so may be the same as CropSyst end_vegetative_growth_deg_day).
      float32 ATT50;                   // accumulated thermal time when LAI reaches the middle of ATTf (RLN:  Not sure exactly what this 'middle of ATTf' means)
   // ???
      float32 crop_coef_min;           // Minimum crop coefficient   (RLN new parameter?)
      float32 crop_coef_max;           // Maximum crop coefficient    (RLN new parameter?)
      float32 PAR_extinction_coef;              // PAR extinction coeffcicient    (probably same as CropSyst where it is called kc?)
      float32 radiation_use_efficiency;         // Radiation-Use Efficiency (kg/MJ) (probably same as CropSyst where it is called reference_light_to_biomass_kg_MJ not sure which variable name would be more accurate)
      float32 transpiration_use_efficiency_coef;// Transpiration use efficiency coefficient (kg biomass/kg water transpired)   (May be the same of CropSyst as ???ET_coef (units unknown)???? but check units.)
   // Nitrogen:
      float32 a_uptake_coef;           // These do not appear to Correspond to CropSyst parameters
      float32 b_uptake_coef;
      float32 c_uptake_coef;
   // Growth
      float32 Lo;                      // (LAI) (Actually L sub 0) LAI at transplanting
      float32 Lf;                      // (LAI) (Actually L sub f) potential leaf area index reached with maximum slope in growth equation
      float32 L50;                     // (LAI) LAI reached at middle of ATTF
      float32 ff;                      // (coef) decreasing/increasing coefficients after “peak LAI”
   public:  // constructor
      Parameters();
   };
//______________________________________________________________________________
protected:
   const Parameters parameters
protected: // computed parameters
   float32 Gompertz_coef;

protected:  // state
   Weather_for_crop_interface &environment;  // Weather is within the greenhouse
      // Currently not const because operations may mutate
   float64  ET_pot_reference;          // also known as ET0 was column H in tomato spreadsheet
      // Will probably simply use the existing reference ET as calculated in CropSyst,
      // Penman-Monteith, Hargreaves or Priestley-Taylor as selected
      // or as data is available (stored in weather file)?

protected: // Computed daily
   float64 thermal_time_accum;

protected: // Computed daily used locally but stored and provided as output
   float64 LAI_gain_cum;               // (LAI) total ever produced
   float64 LAI_gain_cum_prev;          // (LAI) total ever produced from previous day
   float64 LAI_standing_cum;           // (LAI) current LAI accounting for any pruning. (In CropSyst this is GAI or LAI)
   float64 fract_interception_PAR_total_biomass; // RLN: I think this may be the similar as CropSyst GAI_fract_canopy_cover_for_PAR
                                                 // but without clumping terms.
protected: // Intended outputs
   float64 biomass_aboveground;
   float64 biomass_aboveground_prev;
protected: // Accumulations
   float64 above_ground_biomass_total_TUE_based;

   private: // state from previous day.
      float64 total_biomass_gain_TUE_based_prev;
      float64 total_biomass_gain_prev;
      float64 LAI_gain_cum_prev;
      float64 biomass_aboveground_prev;
//NYN float64 above_ground_biomass_total_prev; //  (from previous day)


public:
   Crop_greenhouse
   (Parameters &_parameters
   ,Weather_for_crop_interface   &_weather
   );

   virtual void initialize();

   inline float64 set_ET_reference(float64 _ET_reference) { return ET_reference = _ET_reference; };
      // make sure to call set_ET_reference before calling process();
};



#endif
#endif
