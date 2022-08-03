#ifndef pedotransfer_saxton_2006H
#define pedotransfer_saxton_2006H
#include <common/soil/hydrology/pedotransfer_abstract.h>

// The are from the basic regression equations, unadjusted except for organic matter
// and correspond to the type of output of the 1986 paper (if
//______________________________________________________________________________
class Pedotransfer_functions_Saxton_2006 // unadjusted except for organic matter.
: public Pedotransfer_functions_abstract
{protected:
   float32 vol_WC_at_S_FC;    // Not sure exactly what this is (computed from fixed)
 protected:
   float32 &organic_matter;         // I am pretty sure % but need to check
 public: // constructor
   Pedotransfer_functions_Saxton_2006
      (float32 &_sand, float32 &_clay, float32 &_silt
      // The following terms are specific to Saxton2006
      ,float32 &_organic_matter              // Assumed fixed
      // The following are the output terms.
      ,float32 & _saturation                  ,bool saturation_fixed
      ,float32 & _vol_WC_at_1500              ,bool vol_WC_at_1500_fixed
      ,float32 & _vol_WC_at_FC                ,bool vol_WC_at_FC_fixed           //140416
//140616 ,float32 & _vol_WC_at_33                ,bool vol_WC_at_33_fixed
      ,float32 & _sat_hydraul_cond_m_d        ,bool sat_hydraul_cond_m_d_fixed
      ,float32 & _bulk_density                ,bool bulk_density_fixed
      ,float32 & _soil_b                     //140416 ,bool soil_b_fixed
      ,float32 & _air_entry_pot              //140416  ,bool air_entry_pot_fixed
      ,float32 & _porosity                    ,bool porosity_fixed
      ,float32 & _water_pot_at_FC             ,bool water_pot_at_FC_fixed               //140416
      );
 public: // overrides
   virtual float get_vol_WC_at_1500(bool fixed_or_based_on_texture_only);        // m3/m3
//140416   virtual float get_vol_WC_at_33(bool fixed_or_based_on_texture_only)  ;        // m3/m3
   virtual float get_vol_WC_at_FC(bool fixed_or_based_on_texture_only)  ;        // m3/m3
   virtual float calc_saturation_based_on_texture(CORN::Quality &returned_quality); // m3/m3 //981030_
   virtual float get_air_entry_pot();          // J/kg                           //980528
   virtual float get_porosity(); // In this case the normal porosity             //080430
 protected: // Currently used only by this model
   virtual float get_vol_WC_at_S_FC();
//140416    virtual float get_vol_WC_at_S_33();
};
//______________________________________________________________________________
class Pedotransfer_functions_Saxton_2006_effective
: public Pedotransfer_functions_Saxton_2006
{  float32 &salinity;               // dS/m
   float32 &gravel_pct_by_weight;   // %
   float32 &compaction;             // ???
 public: // constructor
   Pedotransfer_functions_Saxton_2006_effective
      (float32 &_sand, float32 &_clay, float32 &_silt
      // The following terms are specific to Saxton2006
      ,float32 &_organic_matter              // Assumed fixed
      ,float32 &_salinity                    // Assumed fixed
      ,float32 &_gravel_pct_by_weight        // Assumed fixed
      ,float32 &_compaction                  // Assumed fixed
      // The following are the output terms.
      ,float32 & _saturation                  ,bool saturation_fixed
      ,float32 & _vol_WC_at_1500              ,bool vol_WC_at_1500_fixed
      ,float32 & _vol_WC_at_FC                ,bool vol_WC_at_FC_fixed           //140416
//140416    ,float32 & _vol_WC_at_33                ,bool vol_WC_at_33_fixed
      ,float32 & _sat_hydraul_cond_m_d        ,bool sat_hydraul_cond_m_d_fixed
      ,float32 & _bulk_density                ,bool bulk_density_fixed
      ,float32 & _soil_b                      ,bool soil_b_fixed
      ,float32 & _air_entry_pot               ,bool air_entry_pot_fixed
      ,float32 & _porosity                    ,bool porosity_fixed
      ,float32 & _water_pot_at_FC             ,bool water_pot_at_FC_fixed               //140416
      );
 public: //
   virtual float get_porosity(); // In this case the normal porosity
   virtual float get_bulk_density_with_compaction();
};
//_2008-04-30___________________________________________________________________
#endif
