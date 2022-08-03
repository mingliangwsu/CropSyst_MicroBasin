#ifndef freezing_jumakisH
#define freezing_jumakisH
#include "soil/freezing_interface.h"
#include "corn/container/unilist.h"
#include "soil/temperature_profile.h"

class Soil_layers_interface;
class Soil_hydrology_interface;
class Soil_hydraulic_properties_interface;
class Soil_structure_interface;
class Soil_temperature_interface;
// Soil freezing loosely based on the Jumakis model

class Soil_freezing_profile_jumakis; // forward decl
//______________________________________________________________________________
class Soil_freezing_profile_jumakis
: public implements_ Soil_freezing_profile_interface                                         //070824
{
 protected: // Soil interfaces references
   unmodifiable_ Soil_layers_interface               &soil_layers;               //070825  // These were moved from  Soil_freezing_profile_abstract
   unmodifiable_ Soil_structure_interface            &soil_structure;            //070825
   unmodifiable_ Soil_hydraulic_properties_interface &soil_hydraulic_properties; //070825
   unmodifiable_ Soil_hydrology_interface            &soil_hydrology;            //070825

 private:// Nested classes
   class Lenses_manager : public CORN::Unidirectional_list                       //981014
   {  //  Keeps a list of frozen lenses
   public: // Nested classes
      class Lens : public CORN::Item
      { friend class Soil_freezing_profile_jumakis::Lenses_manager;
        friend class Soil_freezing_profile_jumakis;
      protected:
          float64 top;     // m depth to the top of the frozen region
          float64 bottom;  // m depth to the bottom of the frozen region
      public:
         Lens(float64 _top,float64 _bottom);
      public:
         inline virtual int compare(const CORN::Item &other)              const  { return 0;};  // NOT CURRENTLY USED
         float64 get_fract_frozen(float64 from_depth , float64 to_depth ) const;
         inline void resize(float64 new_top , float64  new_bottom )
            {  top = new_top;
               bottom = new_bottom;
            };
      };
      //_1998-10-14_________________________________________________
   public: // Lenses_manager 'structors
      Lenses_manager();
   public:
      void         add_lens(float64 top ,float64 bottom);
      float64      get_fract_frozen(float64 from_depth, float64 to_depth) const;
      Lens *get_highest_lens()                                            const;
      Lens *get_next_highest_lens(Lens *below_lense )                     const;
      Lens *get_lowest_lens()                                             const;
      Lens *get_next_lowest_lens(Lens *above_lens )                       const;
      float64      get_highest_lens_top()                                 const;
      float64      get_lowest_lens_bottom()                               const;
   };
   //______________________________________________________________________________
 private:
   float64      freezing_index;    //degree days C
   int16        freezing_days;                 //  <- This should be a property  of Weather class!!!!
   Lenses_manager frozen_lenses;                                                 //981014
 public:
   bool layer_freeze_or_thaw_occured[MAX_soil_layers_alloc];
 protected:
   unmodifiable_ Soil_temperature_interface  &temperature_profile;               //080123
   const         Air_temperature_average     &air_temperature_avg;               //151022
 public:
   Soil_freezing_profile_jumakis                                                 //990308
      (unmodifiable_ Soil_layers_interface                &soil_layers           //051201
      ,unmodifiable_ Soil_structure_interface             &soil_structure        //070725
      ,unmodifiable_ Soil_hydraulic_properties_interface  &soil_hydraulic_properties  //051201
      ,  modifiable_ Soil_hydrology_interface             &soil_hydrology        //051201
      ,unmodifiable_ Soil_temperature_interface           &soil_temperature
      ,const         Air_temperature_average              &air_temperature_avg); //151022
   virtual bool is_frozen(nat8 layer)                              affirmation_; //981014
   inline virtual float64 get_ultimate_freezing_depth()                    const //981014
      { return frozen_lenses.get_lowest_lens_bottom(); };
   inline virtual float64 get_top_thaw_depth()                             const //981015
      { return frozen_lenses.get_highest_lens_top(); };
   virtual void freezing_and_thawing                                             //981015
    (const Snow_pack *snow_pack)                                  modification_; //151022
    // May be 0 if no snow
 private:
   float64 heat_capacity                                                         //980612
      (nat8 layer
      ,float64 water_content_layer
      ,bool get_frozen_heat_capacity);
   void perform_freezing()                                        modification_;
   void perform_thawing(bool thaw_from_both_top_and_bottom)       modification_;
   bool thaw                                                                     //981014
      (Lenses_manager::Lens *lens
      ,bool from_top
      ,float64 &thawing_index_left
      ,soil_layer_array64(required_thawing_index))                modification_;
   virtual float64 get_fract_frozen(nat8 layer)                           const; //981014
   inline bool any_frozen_zones()                                         const //981015
      { return  frozen_lenses.count() > 0; };
   float64 get_frozen_thickness_m(nat8 layer)                             const;
   inline virtual bool freeze_or_thaw_occured(nat8 layer)                 const //070827
      { return layer_freeze_or_thaw_occured[layer]; };
 public:
   virtual float64 calc_liquid_and_ice_water_content_volumentric                 //990311
      (nat8 layer
      ,float64 &vol_liquid_water_content
      ,float64 &vol_ice_content)                                          const;
      // Partitions the full water content of the layer into ice and water
      // (liquid_water_content and ice_content are modified), the values are also returned.
      // The function returns the fraction of the layer that is frozen.
};
//_1998-07-29___________________________________________________________________
#endif
//soilfrzj.h

