#ifndef pedotransfer_saxton_1986H
#define pedotransfer_saxton_1986H
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#define soil_water_pot_at_PWP  -1500.0
//140416 obsolete #define soil_water_pot_at_FC   -33.0
#include "common/soil/hydrology/pedotransfer_abstract.h"
/*
   This class is fairly easy to use:

   You will need a set of variables to store the values calculated by the
   class method recompute_every_thing().

   Some of the variables may be fixed input parameters others may be calculated.
   The percent sand silt and clay are always fixed and will not be changed
   by this class.

   They are passed by reference to the constructor because the program using this class may
   change the texture and then recompute_every_thing().
*/
class smart_soil_file;
class Soil_texture_hydraulics;                                                   //981030
//______________________________________________________________________________
class Pedotransfer_functions_Saxton_1986
: public Pedotransfer_functions_abstract
{  CORN::Quality_clad acoef_quality; float acoef;
   CORN::Quality_clad bcoef_quality; float bcoef;
 friend class smart_soil_file;
 public:  // Constructors
   Pedotransfer_functions_Saxton_1986
   (float32 & _sand, float32 &_clay, float32 &_silt
   ,float32 & _saturation              ,bool saturation_fixed
   ,float32 & _vol_WC_at_1500          ,bool vol_WC_at_1500_fixed
   ,float32 & _vol_WC_at_FC            ,bool vol_WC_at_FC_fixed
   ,float32 & _sat_hydraul_cond_m_d    ,bool sat_hydraul_cond_m_d_fixed
   ,float32 & _bulk_density            ,bool bulk_density_fixed
   ,float32 & _soil_b                  ,bool soil_b_fixed
   ,float32 & _air_entry_pot           ,bool air_entry_pot_fixed
   ,float32 & _porosity                ,bool porosity_fixed
   ,float32 & _water_pot_at_FC         ,bool water_pot_at_FC_fixed               //130326
   );
 public:  // The only functions the programmer will really need to use
    virtual bool recompute_every_thing();
    // returns false if data is inconsistant (I.e. (sand+clay+slit) does not sum to 100);
 public:  // Functions usually used by the class but may be used by the programmer
          // These functions get the best actual, estimated, or computed value
   virtual float get_bulk_density_based_on_texture(CORN::Quality &bulk_density_based_on_texture_quality);
//   virtual float calc_bulk_density_based_on_best_saturation();                   //080313
   virtual float get_WC_at_based_on_texture
       (float potential); // -1500 or -33
   virtual float get_WC_at
     (float potential // -1500 or -33
     ,float current_vol_WC
     ,CORN::Quality &vol_WC_quality
     ,bool fixed_based_on_texture_only);
   virtual float get_vol_WC_at_1500(bool fixed_or_based_on_texture_only);       // m3/m3
   virtual float get_vol_WC_at_FC(bool fixed_or_based_on_texture_only);         // m3/m3 //140416
   virtual float provide_water_pot_at_FC();                                      //140416
   //140416 virtual float get_vol_WC_at_33(bool fixed_or_based_on_texture_only);         // m3/m3
   virtual float calc_saturation_based_on_texture(CORN::Quality &returned_quality); //981030
   virtual float get_sat_hydraul_cond_cm_hr(); // cm/hr                          //980528
   virtual float get_sat_hydraul_cond_m_d();   // m/day                          //980528
           float get_geometric_mean_particle_size();   // I think in micro meters
   virtual float get_air_entry_pot();          // J/kg                           //980528
   virtual float get_soil_b();                 // -                              //980528
   float set_soil_b(float _soil_b, CORN::Quality_code new_quality = fixed_quality);    //980528
 private: // Functions to compute intermediate steps
   float get_acoef();
   float get_bcoef();
 public: // Functions also used by CropSyst for special situations
   float calc_soil_b                                                             //990321
      (float WC_at_33_or_FC,float PC_at_1500_or_PWP);
   float calc_air_entry_pot                                                      //990321
      (float WC_at_33_or_FC,float saturation,float soil_b);
   float  calc_WC_at                                                             //990525
      (float potential,float air_entry_pot,float soil_b,float saturation);
 protected:
   virtual void  reset_questionable_states();
};
//______________________________________________________________________________
#endif
