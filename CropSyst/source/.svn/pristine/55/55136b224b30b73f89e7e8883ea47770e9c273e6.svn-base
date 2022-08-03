#ifndef freezing_numericalH
#define freezing_numericalH

// This is the new soil freezing class
//#include "soil/freezing_abstract.h"
#define     Lf  333700.0
#ifdef HEAT_SINK_FREEZING
//______________________________________________________________________________
class Soil_freezing_profile_numerical
: public virtual Soil_freezing_profile_interface
{public:
   Soil_freezing_profile_numerical();
   virtual bool is_frozen(nat8 sublayer)      const_adjusts_pointers;                //981014
   virtual float32 get_ultimate_freezing_depth() const_adjusts_pointers;            //981014
   float32 get_freezing_depth() const; //990120
   float32 find_ice_content                                          //990120
      (nat8    sublayer
      ,float32 temperature_sl);

#ifndef USE_VIRTUAL_BASE_CLASSES
#error reached
 public: // The following pure virtual methods will need to be provided in a derived class
   inline virtual float32 get_saturation_water_content(nat8  sublayer)     const = 0;
   inline virtual float32 get_air_entry_pot
      (nat8  sublayer,bool consider_ice_content, bool FC_PWP_based)        const = 0;  //990321
   inline virtual float32 get_soil_b(nat8  sublayer)                       const = 0;  //981030
#endif
};
#endif
//_1998-07-29_________________________________Soil_freezing_profile_numerical__/
#endif
//soilfrzn.h

