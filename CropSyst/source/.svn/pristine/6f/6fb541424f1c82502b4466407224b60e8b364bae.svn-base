#ifndef structure_commonH
#define structure_commonH
//______________________________________________________________________________
#include "soil/structure_interface.h"
//180408#include "corn/math/statistical/stats.h"
#include "corn/math/statistical/sample_dataset_T.h"
#include "common/soil/layering.h"
class Soil_layers_interface;
class Soil_parameters_class;
//______________________________________________________________________________
class Soil_structure_common
: public Soil_structure_interface
{
protected:
   const Soil_layers_interface    &layers;    // Provides convenient access to soil layering
   soil_layer_array64(bulk_density_g_cm3);
   //180408 CORN::Statistical_data_set
   CORN::Statistical_sample_with_dataset<float32,float32,float32>                //180408
      bulk_density_stats_g_cm3;
   // using_statistical data set because because we need average for profile.
public: // structors
   Soil_structure_common(const Soil_layers_interface    &_layers);
   Soil_structure_common                                                         //150926
      (const Soil_layers_interface &_layers
      ,const Soil_parameters_class &parameters);
   Soil_structure_common(const Soil_structure_common &from_copy);
   inline virtual ~Soil_structure_common() {}                                    //170217
   void copy(const Soil_structure_common &copy_from);
   virtual void expand_last_layer_for_boundary_conditions
      (nat8 number_layers, nat8 number_expanded_layers)            modification_; //080130
public:
   virtual float64 get_bulk_density_g_cm3(nat8 layer)                      const;
   virtual float64 set_bulk_density_g_cm3(nat8 layer,float64 bulk_density_g_cm3);
   virtual float64 set_bulk_density_kg_m3(nat8 layer,float64 bulk_density_kg_m3);//141207RLN
   virtual float64 get_bulk_density_kg_m3(nat8 layer)                      const;//LML 150526
   virtual float64 get_bulk_density_avg_g_cm3()                            const;
public: // Units of mass conversion
   virtual float64 kg_per_m2_to_micrograms_per_g
      ( nat8 layer, float64 amount_kg_ha)                                  const;
    // alias this to kg_per_m2_to_concentration
   virtual float64 micrograms_per_g_to_kg_per_m2
      ( nat8 layer, float64 concentration)                                 const;
    // alias this to concentration_to_kg_per_m2
   virtual float64 get_mass_kg_m2(nat8 layer)                              const;//110927
};
//_2007-07-25___________________________________________________________________
#endif

