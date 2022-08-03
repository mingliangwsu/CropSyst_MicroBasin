#include "organic_matter/single_pool/OM_pools_single.h"
#include "organic_matter/single_pool/OM_single_pool.h"
#include "soil/abiotic_environment.h"
#include "soil/nitrogen_interface.h"
#include "soil/disturbance.h"
#include "organic_matter/OM_const.h"
#include "organic_matter/OM_params.h"
#include <math.h>
#include "soil/structure_interface.h"
#ifdef DETAILED_BALANCES
extern C_Balance *C_balance;                                                     //111005
#endif
//_2011-09-29_____________________________________________________________________________
Organic_matter_pools_single::Organic_matter_pools_single
(const Organic_matter_decomposition_parameters &_organic_matter_decomposition_parameters //120912
,Soil_abiotic_environment_profile      &_soil_abiotic_environment_profile
,const Soil_layers_interface           &_soil_layers                             
,unmodifiable_ Soil_structure_interface &_soil_structure                         
,Soil_nitrogen_interface               *_soil_N
,const Soil_texture_interface &_soil_texture)                                    
: Organic_matter_pools_common                                                    
(_organic_matter_decomposition_parameters
,_soil_abiotic_environment_profile
,_soil_layers                                                                    
,_soil_structure
,_soil_N
,_soil_texture)
{  for (nat8  layer = 0; layer < MAX_soil_layers; layer++)
      SOM_ref[layer] = 0;                                                        //110929
}
//_2011-09-29_____________________________________________________________________________
bool Organic_matter_pools_single::initialize_layer
(nat8  horizon,nat8  layer
,float64 sand_fraction
,float64 initial_organic_matter_carbon_mass
,float64 microbial_decomposition_const  // Not used by this model
,const Organic_matter_initialization_parameters &organic_matter_initialization_parameters
,Soil_abiotic_environment_layer *point_soil_environment)
{  float64 SOM_C_mass             = initial_organic_matter_carbon_mass;
   float64 SOM_mass =  SOM_C_mass / SOM_carbon_fraction ;
   Organic_biomatter_single_pool  *SOM = new Organic_biomatter_single_pool
      (SINGLE_SOM
      ,layer
      ,SOM_mass
      ,SOM_carbon_fraction
      ,(float64)organic_matter_decomposition_parameters.single_SOM_CN_ratio
      ,(float64)organic_matter_decomposition_parameters.max_apparent_soil_C_decomposition_const  //110929
      ,0.0  // area_per_mass       // = 0.0  stubble and surface residue_only?
      ,subsurface_contact_fraction
      ,soil_texture                                                              //070707
      ,point_soil_environment);
   SOM    ->contribute_to(1.0,0,0);
   append(SOM);
   #ifdef DETAILED_BALANCES
   C_balance->OM.initial+=SOM->get_carbon_kg();                                  //111005
   #endif
   organic_matter[SINGLE_SOM][layer] = SOM;                                      //060803
   SOM_ref[layer] = SOM;
   return true;
}
//_2011-09-29_____________________________________________________________________________
// can be common to single and multiple
Organic_biomatter_common *
Organic_matter_pools_single::provide_organic_matter_pool
(Organic_matter_type type,nat8  layer)
{  Organic_biomatter_common *provided_pool = organic_matter[type][layer];        //070707
   if (!provided_pool)
   {  provided_pool = organic_matter[type][layer] = new
            Organic_biomatter_single_pool
               (type,layer,subsurface_contact_fraction,soil_texture,soil_abiotic_environment_profile.point_soil_abiotic_environment_layer( layer));
   }
   return provided_pool;
}
//_2011-09-29_____________________________________________________________________________
Organic_biomatter_common  *Organic_matter_pools_single::render_OM_pool
(Organic_matter_type     _type
,Organic_matter_position _position
,nat8                    _layer
,Organic_matter_cycling  _cycling
,RUSLE2_Residue_type     _RUSLE2_residue_type                                    //060731
,float64                 _biomass
,float64                 _carbon_fraction
,float64                 _carbon_nitrogen_ratio
,float64                 _decomposition_constant                                 //090703
,float64                 _detrition_constant                                     //090413
,float64                 _area_per_mass      // = 0.0  stubble and surface residue_only?
,float64                 &_contact_fraction
,const Soil_texture_interface &_soil_texture                                     //070707
, Soil_abiotic_environment_layer * _soil_abiotic_environment_layer)   rendition_
{  return new Organic_biomatter_single_pool    // for residue
      (_type
      ,_position
      ,_layer
      ,_cycling
      ,_RUSLE2_residue_type                                                      //060721
      ,_biomass
      ,_carbon_fraction
      ,_carbon_nitrogen_ratio
      ,_decomposition_constant
      ,_detrition_constant                                                       //090702_090513
      ,_area_per_mass       // = 0.0  stubble and surface residue_only?
      ,_contact_fraction
      ,_soil_texture                                                             //070707
      ,_soil_abiotic_environment_layer);
}
//_2011-10-01___________________________________________________________________
Organic_biomatter_common_pool *Organic_matter_pools_single::render_OM_pool_for_read() rendition_
{
   Organic_biomatter_single_pool * OM =
   new Organic_biomatter_single_pool
   ((Organic_matter_type)0,(nat8)0 // type and layer values will be loaded from file
   ,0 // mass will be loaded from file
   ,SOM_carbon_fraction // probably loaded from file
   ,(float64)organic_matter_decomposition_parameters.single_SOM_CN_ratio
   ,(float64)organic_matter_decomposition_parameters.max_apparent_soil_C_decomposition_const  //110929
      // For residue the CN_ratio and decomp const should be setup separately
      ,0.0  // area_per_mass       // = 0.0  stubble and surface residue_only?
   ,const_cast<float64 &>(subsurface_contact_fraction)
   ,soil_texture
   ,soil_abiotic_environment_profile.point_soil_abiotic_environment_layer(1));
      // the actual layer will be set later by take_OM_pool
   return OM;
}
//_2016-11-16___________________________________________________________________
modifiable_ Organic_biomatter_common_pool  *Organic_matter_pools_single::get_metastable_SOM_ref(nat8 layer)
{  return SOM_ref[layer];
}
//_2011-09-29___________________________________________________________________
modifiable_ Organic_biomatter_common_pool  *Organic_matter_pools_single::get_microbial_biomass_ref(nat8 layer)
{  return SOM_ref[layer];
}
//_2011-09-29___________________________________________________________________
/*161116  NYI  Currently assuming the initial organic matter file
   we are reading from is also from a run that used single pool model
   For completeness,should merge various types of organic matter
   (I.e. if the file was generated from
   a multi pool run) into the single pool.
   I am not sure how to do this.
*/
bool Organic_matter_pools_single::specialized_reference
(Organic_biomatter_common_pool *OM_pool_common)
{  Organic_biomatter_single_pool *OM_pool
      = dynamic_cast<Organic_biomatter_single_pool *>(OM_pool_common);
   if (OM_pool->is_straw_or_manure_residue())
   {  // WARNING this is assuming the SOM_ref (SOM pools) have been
      // instantiated and initialized before residues
      float64 C_fraction_from_residue_to_CO2 = 0.55;
         // 0.55 is the default value for a little bit more than single cycling residues.
         // see get_carbon_fraction_from_residue_to_OM_pool()
      float64 C_fraction_from_residue_to_pool = 1.0 - C_fraction_from_residue_to_CO2;
      Organic_biomatter_common_pool *receiving_OM_pool
         = SOM_ref[OM_pool->layer];
      OM_pool->contribute_to
      (C_fraction_from_residue_to_CO2
      ,receiving_OM_pool
      ,C_fraction_from_residue_to_pool);
   } else // is soil OM
   {  SOM_ref[OM_pool->layer] = OM_pool;
      OM_pool->contribute_to(1.0,0); // all SOM decomposed C is to CO2
   }
   return true;
}
//_2017-02-28___________________________________________________________________

