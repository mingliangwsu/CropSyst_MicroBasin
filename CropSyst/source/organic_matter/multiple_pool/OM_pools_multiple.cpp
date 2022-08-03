#include "organic_matter/multiple_pool/OM_pools_multiple.h"
#include "soil/abiotic_environment.h"
#include "soil/nitrogen_interface.h"
#include "soil/disturbance.h"
#include "soil/texture_interface.h"
#include "organic_matter/OM_const.h"
#include "organic_matter/OM_params.h"
#include <math.h>
#ifdef DETAILED_BALANCES
extern C_Balance *C_balance;                                                     //111005
#endif
//______________________________________________________________________________
Organic_matter_pools_multiple::Organic_matter_pools_multiple
(const Organic_matter_decomposition_parameters &OM_decomposition_params_         //120912
,Soil_abiotic_environment_profile      &soil_abiotic_env_profile_                //060726
,const Soil_layers_interface           &soil_layers_                             //060726
,unmodifiable_ Soil_structure_interface &soil_structure_                         //070725
,Soil_nitrogen_interface               *soil_N_
,const Soil_texture_interface &soil_texture_)                                    //070707
: Organic_matter_pools_common                                                    //070707
(OM_decomposition_params_                                                        //120912
,soil_abiotic_env_profile_                                                       //070707
,soil_layers_                                                                    //070707
,soil_structure_                                                                 //070726
,soil_N_                                                                         //070707
,soil_texture_)                                                                  //070707
{  for (nat8 layer = 0; layer < MAX_soil_layers; layer++)
   {   microbial_biomass_ref[layer] = 0;
       metastable_SOM_ref   [layer] = 0;                                         //060524
   }
}
//_2006_________________________________________________________________________
void Organic_matter_pools_multiple::calculate_C_contributions
(float64 sand_fraction
,float64 &C_Fraction_From_MB_To_MetastableSOM
,float64 &C_Fraction_From_MB_To_LabileSOM
,float64 &C_Fraction_From_LabileSOM_To_PassiveSOM
,float64 &C_Fraction_From_LabileSOM_To_CO2
,float64 &C_Fraction_From_LabileSOM_To_MB
,float64 &C_Fraction_From_MetastableSOM_To_PassiveSOM
,float64 &C_Fraction_From_MetastableSOM_To_CO2
,float64 &C_Fraction_From_MetastableSOM_To_MB
,float64 &C_Fraction_From_PassiveSOM_To_CO2
,float64 &C_Fraction_From_PassiveSOM_To_MB)
{
   float64 alpha = 0.3+ (0.2 / (1.0 + (pow((sand_fraction / 0.25), 3))));        //090414
                       // alpha is microbial_to_metastable
   C_Fraction_From_MB_To_MetastableSOM = alpha;                                  //060307
   C_Fraction_From_MB_To_LabileSOM = (1.0 - alpha);                              //060307
   // Labile Active SOM pool
   C_Fraction_From_LabileSOM_To_PassiveSOM = organic_matter_decomposition_parameters.C_fraction_from_labile_to_passive_SOM; //090515
   C_Fraction_From_LabileSOM_To_CO2 = 0.75 * (1.0 - C_Fraction_From_LabileSOM_To_PassiveSOM);  //060307
   C_Fraction_From_LabileSOM_To_MB  = 0.25 * (1.0 - C_Fraction_From_LabileSOM_To_PassiveSOM);  //060307
   // Metastable Active SOM pool
   C_Fraction_From_MetastableSOM_To_PassiveSOM =organic_matter_decomposition_parameters.C_fraction_from_metastable_to_passive_SOM ;  //090515
   C_Fraction_From_MetastableSOM_To_CO2 = 0.8 * (1.0 - C_Fraction_From_MetastableSOM_To_PassiveSOM);   //060307
   C_Fraction_From_MetastableSOM_To_MB  = 0.2 * (1.0 - C_Fraction_From_MetastableSOM_To_PassiveSOM);    //060307
   // Passive SOM pool
   C_Fraction_From_PassiveSOM_To_CO2 = 0.8;                                      //060307
   C_Fraction_From_PassiveSOM_To_MB = 1.0 - C_Fraction_From_PassiveSOM_To_CO2;   //060307
}
//_2012-09-12___________________________________________________________________
bool Organic_matter_pools_multiple::initialize_layer
(nat8  horizon,nat8  layer
,float64 sand_fraction                                                           //060418
,float64 initial_organic_matter_carbon_mass
,float64 microbial_decomposition_const
,const Organic_matter_initialization_parameters &OM_initialization_parameters    //060215
,Soil_abiotic_environment_layer *point_soil_environment)
{  float64 labile_active_SOM_decomposition_const       = organic_matter_decomposition_parameters.labile_active_SOM_decomposition_const;
   float64 metastable_active_SOM_decomposition_const   = organic_matter_decomposition_parameters.metastable_active_SOM_decomposition_const;
   float64 passive_SOM_decomposition_const             = organic_matter_decomposition_parameters.passive_SOM_decomposition_const;
   float64 initial_C_to_microbial_biomass_percent      = OM_initialization_parameters.microbial_biomass_percent[horizon];   //040610
   float64 initial_C_to_labile_SOM_percent             = OM_initialization_parameters.labile_SOM_percent[horizon];          //040610
   float64 initial_C_to_metastable_SOM_percent         = OM_initialization_parameters.metastable_SOM_percent[horizon];      //040610
   float64 initial_C_to_passive_SOM_percent            = OM_initialization_parameters.passive_SOM_percent[horizon];         //040610
   float64 initial_C_fraction_to_microbial_biomass = (float64)initial_C_to_microbial_biomass_percent/100.0;
   float64 initial_C_fraction_to_labile_SOM        = (float64)initial_C_to_labile_SOM_percent/100.0;  //060307
   // Initialize C and N mass for each conceptual model pool (kg/m2)
   // Microbial biomass pool
   float64 MB_C_mass             = initial_organic_matter_carbon_mass * initial_C_fraction_to_microbial_biomass;
   float64 labile_SOM_C_mass     = initial_organic_matter_carbon_mass * initial_C_fraction_to_labile_SOM;                     //040610
   float64 metastable_SOM_C_mass = initial_organic_matter_carbon_mass * (float64)initial_C_to_metastable_SOM_percent/100.0;   //040610
   float64 passive_SOM_C_mass    = initial_organic_matter_carbon_mass * (float64)initial_C_to_passive_SOM_percent/100.0;      //040610
   /*170217 unused but dont delete
   float64 MB_N_mass             = MB_C_mass             / organic_matter_decomposition_parameters.microbial_CN_ratio;
   float64 labile_SOM_N_mass     = labile_SOM_C_mass     / organic_matter_decomposition_parameters.labile_active_SOM_CN_ratio;
   float64 metastable_SOM_N_mass = metastable_SOM_C_mass / organic_matter_decomposition_parameters.metastable_active_SOM_CN_ratio;
   float64 passive_SOM_N_mass    = passive_SOM_C_mass    / organic_matter_decomposition_parameters.passive_SOM_CN_ratio;
   */

//       In version 4.2 the following fractions could be calcualted from
//       user specified or "previously intensly cultivated" mode parameters.

   // Microbial biomass pool
   float64 C_Fraction_From_MB_To_MetastableSOM           = 0;
   float64 C_Fraction_From_MB_To_LabileSOM               = 0;
   float64 C_Fraction_From_LabileSOM_To_PassiveSOM       = 0;
   float64 C_Fraction_From_LabileSOM_To_CO2              = 0;
   float64  C_Fraction_From_LabileSOM_To_MB              = 0;
   float64  C_Fraction_From_MetastableSOM_To_PassiveSOM  = 0;
   float64  C_Fraction_From_MetastableSOM_To_CO2         = 0;
   float64  C_Fraction_From_MetastableSOM_To_MB          = 0;
   float64  C_Fraction_From_PassiveSOM_To_CO2            = 0;
   float64  C_Fraction_From_PassiveSOM_To_MB             = 0;
   calculate_C_contributions                                                     //120912
      (sand_fraction
      ,C_Fraction_From_MB_To_MetastableSOM
      ,C_Fraction_From_MB_To_LabileSOM
      ,C_Fraction_From_LabileSOM_To_PassiveSOM
      ,C_Fraction_From_LabileSOM_To_CO2
      ,C_Fraction_From_LabileSOM_To_MB
      ,C_Fraction_From_MetastableSOM_To_PassiveSOM
      ,C_Fraction_From_MetastableSOM_To_CO2
      ,C_Fraction_From_MetastableSOM_To_MB
      ,C_Fraction_From_PassiveSOM_To_CO2
      ,C_Fraction_From_PassiveSOM_To_MB);
   float64 MB_mass =  MB_C_mass / microbial_carbon_fraction ;                    //060425
   Organic_biomatter_multiple_pool  *microbial_biomass = new Organic_biomatter_multiple_pool
      (MICROBIAL_BM
      ,layer
      ,MB_mass
      ,microbial_carbon_fraction
      ,organic_matter_decomposition_parameters.microbial_CN_ratio
      ,microbial_decomposition_const
      ,0.0                                   // _area_per_mass       // = 0.0  stubble and surface residue_only?
      ,subsurface_contact_fraction
      ,soil_texture                                                              //070707
      ,point_soil_environment);
   float64 labile_SOM_mass = labile_SOM_C_mass / SOM_carbon_fraction;            //060425
   Organic_biomatter_multiple_pool  *labile_active_SOM = new Organic_biomatter_multiple_pool
      (LABILE_ACTIVE_SOM
      ,layer
      ,labile_SOM_mass
      ,SOM_carbon_fraction
      ,organic_matter_decomposition_parameters.labile_active_SOM_CN_ratio
      ,labile_active_SOM_decomposition_const
      ,0.0                                      // _area_per_mass       // = 0.0  stubble and surface residue_only?
      ,subsurface_contact_fraction
      ,soil_texture                                                              //070707
      ,point_soil_environment);
   float64 metastable_SOM_mass = metastable_SOM_C_mass / SOM_carbon_fraction;    //060425
   Organic_biomatter_multiple_pool  *metastable_active_SOM = new Organic_biomatter_multiple_pool
      (METASTABLE_ACTIVE_SOM
      ,layer
      ,metastable_SOM_mass
      ,SOM_carbon_fraction
      ,organic_matter_decomposition_parameters.metastable_active_SOM_CN_ratio
      ,metastable_active_SOM_decomposition_const
      ,0.0                                         // _area_per_mass       // = 0.0  stubble and surface residue_only?
      ,subsurface_contact_fraction
      ,soil_texture                                                              //070707
      ,point_soil_environment);
   float64  passive_SOM_mass = passive_SOM_C_mass / SOM_carbon_fraction;         //060425
   Organic_biomatter_multiple_pool  *passive_SOM = new Organic_biomatter_multiple_pool
      (PASSIVE_SOM
      ,layer
      ,passive_SOM_mass
      ,SOM_carbon_fraction
      ,organic_matter_decomposition_parameters.passive_SOM_CN_ratio
      ,passive_SOM_decomposition_const
      ,0.0                                      // _area_per_mass       // = 0.0  stubble and surface residue_only?
      ,subsurface_contact_fraction
      ,soil_texture                                                              //070707
      ,point_soil_environment);
      microbial_biomass    ->contribute_to
         (0  //060307 now no C transfer from MB to CO2
         ,labile_active_SOM     ,C_Fraction_From_MB_To_LabileSOM
         ,metastable_active_SOM ,C_Fraction_From_MB_To_MetastableSOM
         );
      labile_active_SOM    ->contribute_to
         (C_Fraction_From_LabileSOM_To_CO2
         ,microbial_biomass     ,C_Fraction_From_LabileSOM_To_MB
         ,passive_SOM           ,C_Fraction_From_LabileSOM_To_PassiveSOM);
      metastable_active_SOM->contribute_to
         (C_Fraction_From_MetastableSOM_To_CO2
         ,microbial_biomass     ,C_Fraction_From_MetastableSOM_To_MB
         ,passive_SOM           ,C_Fraction_From_MetastableSOM_To_PassiveSOM);
      passive_SOM          ->contribute_to
         (C_Fraction_From_PassiveSOM_To_CO2
         ,microbial_biomass     ,C_Fraction_From_PassiveSOM_To_MB);
      append(microbial_biomass);
      append(labile_active_SOM);
      append(metastable_active_SOM);
      append(passive_SOM);
      // add reference points to the organic matter pool for fast lookup         //060803
      #ifdef DETAILED_BALANCES
      C_balance->OM.initial += microbial_biomass    ->get_carbon_kg();           //111005
      C_balance->OM.initial += labile_active_SOM    ->get_carbon_kg();           //111005
      C_balance->OM.initial += metastable_active_SOM->get_carbon_kg();           //111005
      C_balance->OM.initial += passive_SOM          ->get_carbon_kg();           //111005
      #endif
      organic_matter[MICROBIAL_BM]         [layer] = microbial_biomass;          //060803
      organic_matter[LABILE_ACTIVE_SOM]    [layer] = labile_active_SOM;          //060803
      organic_matter[METASTABLE_ACTIVE_SOM][layer] = metastable_active_SOM;      //060803
      organic_matter[PASSIVE_SOM]          [layer] = passive_SOM;                //060803
      microbial_biomass_ref[layer] = microbial_biomass;
      metastable_SOM_ref   [layer] = metastable_active_SOM;                      //060524
     return true;
}
//______________________________________________________________________________
Organic_biomatter_common *
Organic_matter_pools_multiple::provide_organic_matter_pool
(Organic_matter_type type,nat8  layer)
{  Organic_biomatter_common *provided_pool = organic_matter[type][layer];        //070707
   if (!provided_pool)
   {  provided_pool = organic_matter[type][layer] = new
            Organic_biomatter_multiple_pool
               (type,layer,subsurface_contact_fraction,soil_texture,soil_abiotic_environment_profile.point_soil_abiotic_environment_layer( layer));
   }
   return provided_pool;
}
//_2006-07-26___________________________________________________________________
Organic_biomatter_common  *Organic_matter_pools_multiple::render_OM_pool
(Organic_matter_type     _type
,Organic_matter_position _position
,nat8                    _layer
,Organic_matter_cycling  _cycling
,RUSLE2_Residue_type     _RUSLE2_residue_type                                    //060731
,float64                 _biomass
,float64                 _carbon_fraction
,float64                 _carbon_nitrogen_ratio
,float64                 _decomposition_constant                                 //090703
,float64                 _detrition_constant // _decomposition_constant_nonmicrobial   //090413
,float64                 _area_per_mass      // = 0.0  stubble and surface residue_only?
,float64                 &_contact_fraction
,const Soil_texture_interface &_soil_texture                                     //070707
, Soil_abiotic_environment_layer * _soil_abiotic_environment_layer) rendition_
{  return new Organic_biomatter_multiple_pool    // for residue
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
//120912 this was added so we can store historical equilibrated OM for futher future scenario runs
nat32 Organic_matter_pools_multiple::write(std::ostream &stream)      stream_IO_
{  nat32 written = 0;                                                            //150728
   for (nat8 layer = 0; layer <= soil_layers.get_number_layers(); layer++)
      for (nat8 OM_type = 0; OM_type < ORGANIC_MATTER_TYPE_COUNT; OM_type++)
         if (organic_matter[OM_type][layer])
         {   written++;                                                          //150728
             organic_matter[OM_type][layer]->write(stream);
             stream << std::endl;
         }
   return written;                                                               //150728
}
//_2012-09-12__________________________________________________________________/
/*161116 moved to Organic_matter_pools_common
bool Organic_matter_pools_multiple::read(std::istream &stream)                   //140210
{  bool read_success = false;                                                    //140213
   int start_record_pos = stream.tellg();
   std::string header;
   std::getline(stream,header);
   start_record_pos = stream.tellg();
   while (stream.good() && !stream.eof())
   {  start_record_pos = stream.tellg(); //      remember file position
      nat16 type_buff;
      stream >> type_buff;                 //      read type
      Organic_matter_type OM_type = (Organic_matter_type)type_buff;
      if (type_buff <= ORGANIC_MATTER_TYPE_COUNT) // Some times we have garbage at end of file //121009
      {  Organic_biomatter_multiple_pool *OM_pool =
         //NYI           (OM_type >= MICROBIAL_BM) ?
            new Organic_biomatter_multiple_pool
            ((Organic_matter_type)0,(nat8)0 // type and layer values will be loaded
            ,subsurface_contact_fraction
            ,soil_texture
            ,soil_abiotic_environment_profile.point_soil_abiotic_environment_layer(1));  // the actual layer will be set below
         // NYI         : new Residue(xxxx);
         stream.seekg(start_record_pos,std::ios::beg);
         OM_pool->read(stream);
         if  ((OM_pool->type >= MICROBIAL_BM) && (OM_pool->type < ORGANIC_MATTER_TYPE_COUNT))
         {  Organic_biomatter_common *existing_OM = find_similar_organic_biomatter(*OM_pool); //121009
            if (existing_OM)
            {  existing_OM->update_value_with_units(OM_pool->kg(),UC_kg_mass);   //150227
               //150227 existing_OM->set(OM_pool->kg(),UC_kg_mass);
               existing_OM->set_carbon_nitrogen_ratio(OM_pool->get_carbon_nitrogen_ratio());
               delete OM_pool; OM_pool = 0;
            } else
            {  append(OM_pool);
               nat8 layer = OM_pool->layer;
               if (organic_matter[OM_pool->type][layer])
               {  std::cerr << "Duplicate OM pool loaded:" << (nat16)(OM_pool->type) << " layer:" << layer << std::endl;
                  // this might happen with residues, residues should be consolidated
                  // when writing historical OM pool files.
                  organic_matter[OM_pool->type][layer] = OM_pool;
                  delete OM_pool;
               };
               organic_matter[OM_pool->type][layer] = OM_pool;
               if (OM_pool->type == MICROBIAL_BM)           microbial_biomass_ref[layer] = OM_pool;
               if (OM_pool->type == METASTABLE_ACTIVE_SOM)  metastable_SOM_ref   [layer] = OM_pool;
               OM_pool->ref_soil_abiotic_environment_layer = soil_abiotic_environment_profile.point_soil_abiotic_environment_layer(layer);
            }
         } else if (OM_pool->type < MICROBIAL_BM) // residue
         {
            // Unlike organic matter pools which have already been instanciated
            // there are no preestablished residues pools

            // This was never implemented, now implemented in  Organic_matter_pools_common
             Temporary disable Residue
               {delete OM_pool; OM_pool = 0;}
               // currently not loading initial residue mainly because it is crashing,
               //  should instanciated specifically residue

         }
      } // is a valid OM type
      read_success = true;                                                       //140213
   } // while not end of stream
   return read_success;                                                          //140213
}
*/
//_2012-09-12__________________________________________________________________/
/*170228 moved to Organic_matter_pools_common::take_OM_pool
because single pool now needs essentially the same thing
bool Organic_matter_pools_multiple::take_OM_pool
(Organic_biomatter_common_pool *OM_pool_common)                   appropriation_
{  bool took = false;
   Organic_biomatter_multiple_pool *OM_pool = dynamic_cast<Organic_biomatter_multiple_pool *>(OM_pool_common); //161116
   if  ((OM_pool->type >= MICROBIAL_BM) && (OM_pool->type < ORGANIC_MATTER_TYPE_COUNT))
   {  Organic_biomatter_common *existing_OM = find_similar_organic_biomatter(*OM_pool); //121009
      if (existing_OM)
      {  existing_OM->update_value_with_units(OM_pool->kg(),UC_kg_mass);         //150227
         existing_OM->set_carbon_nitrogen_ratio(OM_pool->get_carbon_nitrogen_ratio());
         delete OM_pool; OM_pool = 0;
      } else
      {
         append(OM_pool);
         nat8 layer = OM_pool->layer;
         if (organic_matter[OM_pool->type][layer])
         {
            // Dont delete: This message needs to be an explination
            //std::clog << "Duplicate OM pool loaded:" << (nat16)(OM_pool->type) << " layer:" << layer << std::endl;
            // this might happen with residues, residues should be consolidated
            // when writing historical OM pool files.
            organic_matter[OM_pool->type][layer] = OM_pool;
            delete OM_pool;
         }
         organic_matter[OM_pool->type][layer] = OM_pool;
         if (OM_pool->type == MICROBIAL_BM)           microbial_biomass_ref[layer] = OM_pool;
         if (OM_pool->type == METASTABLE_ACTIVE_SOM)  metastable_SOM_ref   [layer] = OM_pool;
         OM_pool->ref_soil_abiotic_environment_layer = soil_abiotic_environment_profile.point_soil_abiotic_environment_layer(layer);
      }
      took = true;
   }
   //170228 else // residue type is handled by  Organic_matter_pools_common
      took = Organic_matter_pools_common::take_OM_pool(OM_pool_common);
   return took;
}
//_2016-11-16___________________________________________________________________
*/

bool Organic_matter_pools_multiple::specialized_reference
(Organic_biomatter_common_pool *OM_pool_common)
{
   Organic_biomatter_multiple_pool *OM_pool
      = dynamic_cast<Organic_biomatter_multiple_pool *>(OM_pool_common);
   nat8 layer = OM_pool->layer;
   if (OM_pool->type == MICROBIAL_BM)           microbial_biomass_ref[layer] = OM_pool;
   if (OM_pool->type == METASTABLE_ACTIVE_SOM)  metastable_SOM_ref   [layer] = OM_pool;
   return true;
}
//_2017-02-28___________________________________________________________________
Organic_biomatter_common_pool *Organic_matter_pools_multiple::render_OM_pool_for_read
(/*Organic_matter_type OM_type*/)        rendition_
{
   return
   new Organic_biomatter_multiple_pool
   ((Organic_matter_type)0,(nat8)0 // type and layer values will be loaded
   ,const_cast<float64 &>(subsurface_contact_fraction)
   ,soil_texture
   ,soil_abiotic_environment_profile.point_soil_abiotic_environment_layer(1));
      // the actual layer will be set later by take_OM_pool
}
//_2016-11-16___________________________________________________________________

