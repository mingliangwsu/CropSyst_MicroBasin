#ifndef txtrhydrH
#define txtrhydrH

#include "corn/primitive.h"
#define soil_water_pot_at_PWP  -1500.0
#define soil_water_pot_at_FC   -33.0

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
//______________________________________________________________________________
class Soil_texture_hydraulics
{
 friend class smart_soil_file;
 public:
   enum Status {unknown,estimated,computed_from_fixed,fixed,other};
   Status texture_status;
   Status saturation_status;
   Status water_pot_at_FC_status;                                                //130326

   Status vol_WC_at_1500_status;
   Status vol_WC_at_33_status;

   Status sat_hydraul_cond_m_d_status;
   Status bulk_density_status;
   Status Campbell_b_status;
   Status air_entry_pot_status;
 
 private:
   float32 &sand;
   float32 &clay;
   float32 &silt;
 private:
   Status acoef_status;                   float acoef;
   Status bcoef_status;                   float bcoef;
   Status GM_particle_size_status;        float32 geometric_mean_particle_size;
 protected: // Communicated with external application
   float32 &saturation;             // m3/m3 not sure units ???
   float32 &vol_WC_at_1500;         // m3/m3
   float32 &vol_WC_at_33;           // m3/m3
   float32 &sat_hydraul_cond_m_d;   // m/day
   float32 &bulk_density;           // grams/cm3
   float32 &Campbell_b;
   float32 &air_entry_pot;          // J/kg
 private: // Functions to compute intermediate steps
   float get_acoef();
   float get_bcoef();
   void  reset_questionable_states();
 public:  // Constructors
   Soil_texture_hydraulics
   (float32 &_sand, float32 &_clay, float32 &_silt
   ,float32 &_saturation                  ,bool saturation_fixed
   ,float32 &_vol_WC_at_1500              ,bool vol_WC_at_1500_fixed
   ,float32 &_vol_WC_at_33                ,bool vol_WC_at_33_fixed
   ,float32 &_sat_hydraul_cond_m_d        ,bool sat_hydraul_cond_m_d_fixed
   ,float32 &_bulk_density                ,bool bulk_density_fixed
   ,float32 &_Campbell_b                  ,bool Campbell_b_fixed
   ,float32 &_air_entry_pot               ,bool air_entry_pot_fixed);
   inline virtual ~Soil_texture_hydraulics() {}                                  //170217
 public:  // The only functions the programmer will really need to use
    virtual bool recompute_every_thing();
    // returns false if data is inconsistant (I.e. (sand+clay+slit) does not sum to 100);
 public:  // Functions usually used by the class but may be used by the programmer
         // These functions get the best actual, estimated, or computed value
   virtual float get_bulk_density_based_on_texture();
   virtual float calc_bulk_density_based_on_best_saturation();                   //080313
   virtual float get_bulk_density();        // gm/cm3
   virtual float get_WC_at_based_on_texture
      (float potential); // -1500 or -33
   virtual float get_WC_at
      (float potential // -1500 or -33
      ,float current_vol_WC
      ,Status &vol_WC_status
      ,bool based_on_texture_only);
   virtual float get_vol_WC_at_1500(bool fixed_or_based_on_texture_only);//m3/m3
   virtual float get_vol_WC_at_33(bool fixed_or_based_on_texture_only);  //m3/m3
   virtual float get_saturation_based_on_texture();                              //981030
   virtual float get_saturation();
   virtual float get_sat_hydraul_cond_cm_hr(); // cm/hr                          //980528
   virtual float get_sat_hydraul_cond_m_d();   // m/day                          //980528
           float get_geometric_mean_particle_size();   // I think in micro meters
   virtual float get_air_entry_pot();          // J/kg                           //980528
   virtual float get_Campbell_b();                 // -                          //980528
   float set_bulk_density  (float _bulk_density   , Status status = fixed); // grams/cm3
   float set_vol_WC_at_1500(float _vol_WC_at_1500 , Status status = fixed); // m3/m3
   float set_vol_WC_at_33  (float _vol_WC_at_33   , Status status = fixed); // m3/m3
   float set_sat_hydraul_cond_m_d(float _sat_hydraul_cond_m_d , Status status = fixed);// m/day //980528

//080313 Warning may need to set_saturation()
   float set_saturation(float _saturation, Status status = fixed);// m3/m3      //080313
   float set_air_entry_pot(float _air_entry_pot, Status status = fixed); //J/kg  //980528p
   float set_Campbell_b   (float _Campbell_b   , Status status = fixed); // -    //980528
 public: // Functions also used by CropSyst for special situations
   float calc_Campbell_b                                                         //990321
      (float WC_at_33_or_FC
      ,float WC_at_1500_or_PWP);
   float calc_air_entry_pot                                                      //990321
      (float WC_at_33_or_FC
      ,float saturation
      ,float Campbell_b);
   float calc_WC_at                                                              //990525
      (float potential
      ,float air_entry_pot
      ,float Campbell_b
      ,float saturation);
};
//_1998-10-30___________________________________________________________________
#endif

