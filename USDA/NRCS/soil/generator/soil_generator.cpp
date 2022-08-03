#include "soil_generator.h"
#include "USDA/NRCS/soil/survey/database/tabular/chtexturegrp.h"
#include "USDA/NRCS/soil/survey/database/tabular/chorizon.h"
#include "corn/container/search_tree.h"
#include "corn/measure/measures.h"
#include <stdlib.h>
#include "corn/data_source/generic_datarec.h"
#include <assert.h>
//std::ofstream verbose_out ("C:\\temp\\verbose.out");

#ifndef __CONSOLE__
#  ifdef __BCPLUSPLUS__
      #include <vcl.h>
      extern TLabel *ref_label_STATSGO2_curr_mukey    ;
      extern TCheckBox *ref_checkbox_STATSGO2_continue;
      extern TProgressBar *ref_progress_bar;
#  endif
#endif
using namespace USDA_NRCS;
using namespace USDA_NRCS::STATSGO2_SSURGO;
using namespace CORN;
namespace STATSGO2
{
USDA_NRCS::STATSGO2_SSURGO::Database *STATSGO2_database_ref;
// ______________________________________________________________________________
Soil_generator::Soil_generator
(
 const USDA_NRCS::STATSGO2_SSURGO::Database::Arguments &arguments_               //170831
,const CORN::Seclusion &mapunit_seclusion_                                       //170903
/*170831 moved to arguments
 const CORN::OS::Directory_name &STATSGO2_database_directory
,const CORN::OS::Directory_name &table_index_directory
,nat8 _aggregation_option
*/
)
: CS::Soil_provider()
, STATSGO2_database
   (arguments_                                                                   //170831
   ,mapunit_seclusion_                                                           //170903
   /*170831
    STATSGO2_database_directory.c_str()
   ,table_index_directory.c_str()
   */
   )
//moved to arguments, aggregation_option(_aggregation_option)
, arguments(arguments_)                                                          //170831
, searching_for_specific_mapunit(0)
, found_specific_mapunit(0)
{  STATSGO2_database_ref = &STATSGO2_database;
}
//_2011-11-07___________________________________________________________________
/*170903 obsolete because now using mapunit_seclusion
nat32 Soil_generator::filter_mapunits_in_table(CORN::Data_table &table)
{
   Generic_data_record *data_rec = table.render_generic_data_record();
   for (bool valid = table.goto_first(); valid;valid = table.goto_next())
   {
      table.get(*data_rec);
      VV_abstract_entry *mukey_entry = data_rec->get_entry(0,"mukey");           //111107
      if (!mukey_entry) // it may be uppercase in the file (I.e. dDase)
      mukey_entry = data_rec->get_entry(0,"MUKEY");                              //111107
      if (mukey_entry)
      {
         std::string mukey_str;                                                  //150903
         mukey_entry->append_to_string(mukey_str);                               //150903
         nat32 mukey = atoi(mukey_str.c_str());                                  //150903
         nat32 already_found_pos = 0;
         if (!STATSGO2_database.mapunit_filter.is_in_array(mukey,already_found_pos))
            STATSGO2_database.mapunit_filter.append(mukey);
      }
   }
   delete data_rec;
   return  STATSGO2_database.mapunit_filter.get_count();
}
//_2011-11-07___________________________________________________________________
nat32 Soil_generator::filter_mapunits_in_list_string(const std::string &mukey_list)
{  nat32 mukey = 0;
   for (nat32 i = 0; i < mukey_list.length(); i++)
   {  char c_i = mukey_list.c_str()[i];
      if (std::isdigit(c_i))
      {  nat8 digit = c_i - 0x30;
         mukey *= 10;
         mukey + digit;
      } else
      {  STATSGO2_database.mapunit_filter.append(mukey);
         mukey = 0;
      }
   }
   return  STATSGO2_database.mapunit_filter.get_count();
}
//_2011-11-07___________________________________________________________________
*/
nat32 Soil_generator::generate()                                      rendition_
{  nat32 generated = 0;
   found_specific_mapunit = 0;                                                   //141230
   CORN::MicroSoft::Access::Import_export_table &chorizon_table = dynamic_cast<CORN::MicroSoft::Access::Import_export_table &>(STATSGO2_database.provide_chorizon_table());
//std::clog << "providing chorizon index" << std::endl;
   const Table_indexer &chorizon_index = STATSGO2_database.provide_chorizon_index(true);
   CORN::MicroSoft::Access::Import_export_table &mapunit_table =  dynamic_cast<CORN::MicroSoft::Access::Import_export_table &>(STATSGO2_database.provide_mapunit_table());
//std::clog << "providing  mapunit index" << std::endl;
   const Table_indexer &mapunit_index = STATSGO2_database.provide_mapunit_index(true);
//std::clog << "soil generating" << std::endl;
//   STATSGO2_database.filter_map_units(map_unit_filter); // narrow indexes by deleting keys that are not in list of desired mukeys

   Mapunit_composition *curr_mapunit_composition = 0;
   FOR_EACH_IN(chorizon_i, Table_indexer::Indice,chorizon_index,each_chorizon)
   {

      if (curr_mapunit_composition && (chorizon_i->MUkey_nat32 != curr_mapunit_composition->mapunit.get_mukey()))
      {  if ((searching_for_specific_mapunit ==0) ||
             ((nat32)atoi(curr_mapunit_composition->mapunit.mukey.c_str())
               == searching_for_specific_mapunit))
         {  generated += commit(*curr_mapunit_composition);
            take(curr_mapunit_composition);                                      //111111
         }
         if (found_specific_mapunit) return generated;                           //111111
         curr_mapunit_composition = 0;
      }
      if (!searching_for_specific_mapunit || (chorizon_i->MUkey_nat32 == searching_for_specific_mapunit))
      {  if (!curr_mapunit_composition)
         {  curr_mapunit_composition = new Mapunit_composition();
            Table_indexer::Indice *MUindice = dynamic_cast<Table_indexer::Indice *>(mapunit_index.find(chorizon_i->MUkey_nat32));
            if (MUindice)
            {  mapunit_table.goto_file_position(MUindice->file_pos);
               mapunit_table.get(curr_mapunit_composition->mapunit);
            } else
            { delete curr_mapunit_composition; curr_mapunit_composition = 0;}
         }
         if (curr_mapunit_composition)
         {  bool horizon_found = chorizon_table.goto_file_position(chorizon_i->file_pos);
            if (horizon_found)
            {  CHorizon chorizon;
               chorizon_table.get(chorizon);
               #ifndef __CONSOLE__
               #  ifdef __BCPLUSPLUS__
               if (ref_label_STATSGO2_curr_mukey)
                   ref_label_STATSGO2_curr_mukey->Caption = chorizon.chkey.c_str();
                  Application->ProcessMessages();
               #  endif
               #endif
              curr_mapunit_composition->compose(chorizon);
            } // if (horizon_found)
         }
      }
   } FOR_EACH_END(each_chorizon)
   return generated;
}
//_2011-11-07___________________________________________________________________
bool Mapunit_composition::commit()
{
   nat8 component_count = 0;
   predominate_component = dynamic_cast<Component_composition *>(components.get_at(0));
   FOR_EACH_IN(component_comp, Component_composition,components, each_component)
   {  component_count += component_comp->compose_meta(mapunit);                                     //1101023
      component_comp->soil_params.set_start();   // This is needed to update both sets of PWP and FC
      if (is_more_agricultural_than_predominant(component_comp->component))
          predominate_component = component_comp;
   } FOR_EACH_END(each_component)
   bool commited = (predominate_component);
   if (commited)
     predominate_component_composition = predominate_component;                    // 141228
   return commited;
}
//_2014-10-14___________________________________________________________________
bool Soil_generator::commit(Mapunit_composition &mapunit_comp)      contribution_ performs_IO_
{  // process    all chorizons of the predominate component
   bool commited = mapunit_comp.commit();                                        //141014
   switch (arguments.aggregation_option)                                         //170831
   {  case  0 : //Extract map unit soil components
      {
         //NYI
      }break;
      case 1: // Aggregate soil sequences in each map unit to create an aggregated representitive pseudopedon
      {  //NYI
      } break;
      case 2: // Use primary component as a representitive pedon
      {  if (mapunit_comp.predominate_component)
         mapunit_comp.predominate_component->soil_params.description.brief.append(" (derived from predominate component of STATSGO map unit)");
      } break;
   }
   return commited;
}
//______________________________________________________________________________
bool Component_composition::compose(const CHorizon &chorizon)
{  nat8 horizon = chorizon.desgnvert;
   if (horizon &&
         /* There were some cases where desgnvert was 0 */
      !soil_params.bound_by_bedrock
         /* There was a case (667015:990268)
            where layer 4 was bedrock but then a layer 5 with texture
            We are stopping at the first bedrock layer.
         */
      )
   {
   soil_params.number_horizons = std::max<int16>
      (soil_params.number_horizons, horizon);
   soil_params.properties.thickness[horizon]                                     //180728
      = cm_to_m(
       CORN::is_approximately<float32>(chorizon.hzthk.repr,0.0,0.00001)
      // Some times the horizon thickness is not specified, so
      // need to compute from depth
      ?(chorizon.hzdepb.repr - chorizon.hzdept.repr)
      : chorizon.hzthk.repr);
   // NYI soil_params.bypass_coef_32[horizon] =  chorizon.
   // NYI the bypass coefficient could possible be derived from STATSGO2 cpores
   // chorizon has the following elements, but I am not sure how complete these are
   // so I use the pedotransfer functions (setup_layer_texture_hydraulics)
   soil_params.properties.sand[horizon] = chorizon.sandtotal.repr; // %          //180728
   soil_params.properties.clay[horizon] = chorizon.claytotal.repr; // %          //180728
   soil_params.properties.silt[horizon] = chorizon.silttotal.repr; // %          //180728
   soil_params.properties.pH[horizon] = chorizon.ph1to1h2o.repr;
   // Soil pH in water  (not buffer)
   // chorizon has CEC-7 (CEC normalized at pH 7?)  and ECEC (effective CEC?)
   // I am not sure which type of  cation_exchange_capacity is used by CropSyst
   //NYI soil_params.cation_exchange_capacity[horizon] = chorizon.cec7.repr or ecec.repr // (cMol_c/kg soil) centimole of positive char/ kilogram soil (equivelent to meq/100g) milliequivelents of cations per 100 grams soil this equal to  For ammonium volitalization
   soil_params.properties.organic_matter[horizon] = chorizon.om.repr;            //170828
   soil_params.properties.organic_matter_low[horizon] = chorizon.om.low;         //170828
   soil_params.properties.organic_matter_high[horizon] = chorizon.om.high;       //170828
   soil_params.texture_available_in_layer[horizon] =
      !(  CORN::is_approximately<float32>(soil_params.properties.sand[horizon],0.0,0.0001)  //170828
       || CORN::is_approximately<float32>(soil_params.properties.clay[horizon],0.0,0.0001)  //170828
       || CORN::is_approximately<float32>(soil_params.properties.silt[horizon],0.0,0.0001)) //170828
      // The texture should also sum to at least 95% (this is generous)
      && ((soil_params.properties.sand[horizon]           //170828_111204
          +soil_params.properties.clay[horizon]           //170828
          +soil_params.properties.silt[horizon]) > 95.0); //170828
   if (!soil_params.texture_available_in_layer[horizon])
   {  // The texture is not entered in this record so attempt to
      // derive the texture from the texture description.
      USDA_texture::Texture_code texture_code =
         (lookup_texture_description
            (chorizon.chkey
            ,soil_params.properties.sand[horizon]                                //170828
            ,soil_params.properties.clay[horizon]                                //170828
            ,soil_params.properties.silt[horizon]));                             //170828
      if ((texture_code == USDA_texture::unweathered_bedrock) ||                 //110613
          (texture_code == USDA_texture::weathered_bedrock) ||
          (texture_code == USDA_texture::unknown))
      {
         soil_params.bound_by_bedrock= true;
         soil_params.texture_available_in_layer[horizon] = false;
      } else
      {  soil_params.texture_available_in_layer[horizon] = true;
      }
      if (!soil_params.texture_available_in_layer[horizon])
      {
         soil_params.number_horizons = horizon-1;;
         soil_params.properties.sand[horizon] = 0.0;
         soil_params.properties.clay[horizon] = 0.0;
         soil_params.properties.silt[horizon] = 0.0;
      }
   }
   if ((horizon > 1)
      && CORN::is_approximately<float32>(soil_params.properties.sand[horizon],1.0,0.0001)
      && CORN::is_approximately<float32>(soil_params.properties.clay[horizon],1.0,0.0001)
      && CORN::is_approximately<float32>(soil_params.properties.silt[horizon],1.0,0.0001)) //110606
   {  // There were some wierdo cases where sand silt and clay were all 1
      // often the last layer
      // In this case copy the values from the previous layer
      soil_params.properties.sand[horizon] = soil_params.properties.sand[horizon-1];
      soil_params.properties.clay[horizon] = soil_params.properties.clay[horizon-1];
      soil_params.properties.silt[horizon] = soil_params.properties.silt[horizon-1];
      soil_params.bound_by_bedrock = false;                                      //111204
      soil_params.texture_available_in_layer[horizon] = true;                    //111204
   }
   if (soil_params.texture_available_in_layer[horizon])                          //111205
   {
      // may want to instanciate each layer hydraulics as needed
      //abandoned soil_params.setup_layer_texture_hydraulics();                                       //170904
      soil_params.setup_texture_hydraulics_layer(horizon);                       //170904

      if ((horizon > 1)                                                          //111204
         // && soil_params.texture_available_in_layer[horizon]
          && !soil_params.texture_available_in_layer[horizon-1])
      {
         soil_params.setup_texture_hydraulics_layer(horizon-1);                       //170904
         // This is a wierdo where a horizon above has not been encountered yet (probably missing)
         // It is assumed the previous layer is similar to this layer
         if (CORN::is_approximately<float32>(soil_params.properties.thickness[horizon-1],0.0,0.0001))
            soil_params.properties.thickness[horizon-1] =
               soil_params.properties.thickness[horizon];
         soil_params.properties.sand[horizon-1] = soil_params.properties.sand[horizon];
         soil_params.properties.clay[horizon-1] = soil_params.properties.clay[horizon];
         soil_params.properties.silt[horizon-1] = soil_params.properties.silt[horizon];
         soil_params.bound_by_bedrock = false;                                   //111204
         soil_params.texture_available_in_layer[horizon-1] = true;               //111204
         soil_params.layer_texture_hydraulics[horizon-1]->recompute_every_thing();
         soil_params.user[horizon-1] |= Soil_parameters_class::specified_texture;
      }
      soil_params.user[horizon] |= Soil_parameters_class::specified_texture;
      if (soil_params.layer_texture_hydraulics[horizon])
          soil_params.layer_texture_hydraulics[horizon]->recompute_every_thing();
      if (horizon)
         profile_depth_m += soil_params.properties.thickness[horizon];
   }
   }
   return profile_depth_m > 0.00001;
      // If there are no soil layers, this is not a viable component.
}
//______________________________________________________________________________
bool Mapunit_composition::compose(CHorizon &horizon)
{  bool valid = false;
   Component_composition *component = provide_component_composition(horizon.cokey);
   if (component)
   {
       valid = component->compose(horizon);
       if (!valid)
         components.remove(component);
   }
  return valid;
}
//_2011-11-07___________________________________________________________________
Component_composition *Mapunit_composition::provide_component_composition(const std::string & cokey)
{  Component_composition *found_component_comp = dynamic_cast<Component_composition *>(components.find_string(cokey)); //120921
   if (!found_component_comp )
   {  found_component_comp = new Component_composition();
      CORN::MicroSoft::Access::Import_export_table &component_table =  dynamic_cast<CORN::MicroSoft::Access::Import_export_table &>(STATSGO2_database_ref->provide_component_table());
      const Table_indexer &component_index = STATSGO2_database_ref->provide_component_index(true);
      const Table_indexer::Indice *co_indice = dynamic_cast<Table_indexer::Indice *>(component_index.find(render_key_ID(cokey.c_str())));
      if (co_indice)
      {  bool component_indexed = component_table.goto_file_position(co_indice->file_pos);
         if (component_indexed)
            component_table.get(found_component_comp->component);
         components.append(found_component_comp);
      }
   }
   return found_component_comp;
}
//_2011-11-07___________________________________________________________________
USDA_texture::Texture_code Component_composition::lookup_texture_description
   (const std::string chorizon_chkey
   ,float32 &horizon_sand
   ,float32 &horizon_clay
   ,float32 &horizon_silt)
{
   USDA_texture::Texture_code texture_code = USDA_texture::unknown;
   CORN::MicroSoft::Access::Import_export_table &texturegrp_table = dynamic_cast<CORN::MicroSoft::Access::Import_export_table &>(STATSGO2_database_ref->provide_chtexturegrp_table());
   const Table_indexer &chtexturegrp_index = STATSGO2_database_ref->provide_chtexturegrp_index(true);
   const Table_indexer::Indice *indice =  dynamic_cast<const Table_indexer::Indice *>(chtexturegrp_index.find(render_key_ID(chorizon_chkey.c_str())));
   if (indice)
   {  texturegrp_table.goto_file_position(indice->file_pos);
      USDA_NRCS::CHtexturegrp horizon_texture;
      /*bool valid = */texturegrp_table.get(horizon_texture);
         // keyfield
      CS::Soil_texture soil_texture(horizon_texture.texture.c_str());
      horizon_sand = soil_texture.get_sand();
      horizon_clay = soil_texture.get_clay();
      horizon_silt = soil_texture.get_silt();
      texture_code = soil_texture.get_code();
   }
   return texture_code; // chtexturegrp != NULL;
}
//_2001-03-24___________________________________________________________________
bool Mapunit_composition::is_more_agricultural_than_predominant
   (const Component &new_component)                                        const
{  bool is_agricultural =
       ((new_component.nirrcapcl.get_int32() > 0) &&(new_component.nirrcapcl.get_int32() < 5))
     ||((new_component.irrcapcl.get_int32() > 0)&&(new_component.irrcapcl.get_int32() < 5));
   bool better_agriculturally = // The lower the capability class, the better the soil agriculturally
   (is_agricultural && (new_component.nirrcapcl.get_int32() < predominate_component->component.nirrcapcl.get_int32())
   || (new_component.irrcapcl.get_int32() < predominate_component->component.irrcapcl.get_int32()));
   bool same_agriculturally = // The lower the capability class, the better the soil agriculturally
   ( (new_component.nirrcapcl.get_int32() == predominate_component->component.nirrcapcl.get_int32()))
   ||((new_component.irrcapcl.get_int32() ==predominate_component->component.irrcapcl.get_int32()));
   bool more_coverage =  new_component.comppct.repr >
      predominate_component->component.comppct.repr;
   //111111 (better_agriculturally || (same_agriculturally && more_coverage));
   //11111 return (is_agricultural || same_agriculturally) && more_coverage;             //111111
   return (is_agricultural && more_coverage) || ((better_agriculturally || same_agriculturally) && more_coverage);             //111111
}
// ______________________________________________________________________________
bool Component_composition::compose_meta(const USDA_NRCS::Mapunit &map_unit)
{  bool composed = true;
   //Smart_soil_parameters &soil_params = map_unit.soil_params;

         // not sure if if is needed
         // if (!soil_params.layer_texture_hydraulics)                           //170904
//abandoned         soil_params.setup_layer_texture_hydraulics();                                       //170904

   if (soil_params.number_horizons)
   {
         // not sure if if is needed
         // if (!soil_params.layer_texture_hydraulics)                           //170904
      soil_params.setup_layer_texture_hydraulics();                                       //170904
      if (! soil_params.bound_by_bedrock && profile_depth_m < 3.0)               //110611
      {  // The soil surveys only sample to
         nat8 extended_horizon = soil_params.number_horizons+1;
         soil_params.setup_texture_hydraulics_layer(extended_horizon);                       //170904
         soil_params.properties.thickness[extended_horizon] = 3.0 - profile_depth_m;
         soil_params.properties.sand[extended_horizon] = soil_params.properties.sand[extended_horizon-1] ;
         soil_params.properties.clay[extended_horizon] = soil_params.properties.clay[extended_horizon-1] ;
         soil_params.properties.silt[extended_horizon] = soil_params.properties.silt[extended_horizon-1] ;

         soil_params.layer_texture_hydraulics[extended_horizon]->recompute_every_thing();
         soil_params.number_horizons  +=1;
      }
   }
   soil_params.description.details_URL = "http://soils.usda.gov/survey/geography/statsgo";
   soil_params.description.brief.assign(component.compname);
   soil_params.steepness_percent    = component.slope.repr;
   soil_params.slope_length         = component.slopelenusle.repr;
   if (soil_params.slope_length) soil_params.slope_length = 100;//meters default
   /* NYI
   soil_params.mukey                = component.mukey;
   soil_params.cokey                = component.cokey;
   */
   soil_params.COMPPCT              = component.comppct.repr;
   soil_params.save_only_specified_layers = true; ;

   // NYI STATSGO_path; // I.e. C:\Simulation\Database\STATSGO

   soil_params.capability_class_irrigated =component.irrcapcl.get_int32();
   soil_params.capability_class_dryland =  component.nirrcapcl.get_int32();
   soil_params.agricultural_dryland = soil_params.capability_class_dryland > 0.0001;
   soil_params.agricultural_irrigated = soil_params.capability_class_irrigated > 0.0001;
   // NYI soil_params.float32 water_holding_capacity_to_1m;            // (value meter depth) to 1.5meter
   // NYI aggregated_water_holding_capacity_to_1m;

   soil_params.hydrologic_group_labeled.set(component.hydgrp.get());
   // NYI soil_params.hydrologic_condition_labeled
   // NYI soil_params.override_curve_number_16; // runoff curve number override (also for models without hydro cond/group)
   // NYI soil_params.user_fallow_curve_number_16;
   // NYI soil_params.compute_surface_storage = true;
   // NYI soil_params.surface_storage_mm_32 = map_unit.predominate_component->xxxxx;
   soil_params.albedo_dry = component.albedodry.repr;
   if (CORN::is_approximately<float32>(soil_params.albedo_dry,0.0,0.000001)) soil_params.albedo_dry = 0.08;
   // STATSOGO doesn't have wet albedo but is is usually between 1.6 and 1.8
   // times the dry albedo
   soil_params.albedo_wet = soil_params.albedo_dry  * 1.7;
   // soil_params.water_vapor_conductance_atmosphere_adj = include_mapunit->predominate_component->xxxxx;         // 080213  This may be obsolete
   // soil_params.SLPF_CropGro = include_mapunit->predominate_component->xxxxx;  //   Soil ?Limitation? ?productivity? factor   1.0 = no limitation. used only for CropGro
   return composed;
}
//_2011-10-25___________________________________________________________________
Mapunit_composition * Soil_generator::render_selected_map_unit(const std::string &MUkey) rendition_
{  return render_selected_map_unit(atoi(MUkey.c_str()));
}
//_2011-10-30___________________________________________________________________
Mapunit_composition *Soil_generator::render_selected_map_unit(nat32 MUkey) rendition_
{  searching_for_specific_mapunit = MUkey;
   if (MUkey)
      generate();
   return found_specific_mapunit; //? found_specific_mapunit : 0;
}
//_2011-10-30___________________________________________________________________
bool Soil_generator::take( Mapunit_composition *map_unit)          contribution_
{
   //170904 Check that this is actually used because
   // I think is is overridden by STATSGO2_CropSyst_soil_generator
   // but check if STATSGO2_CropSyst_soil_generator is the only implements of this method
   if ((searching_for_specific_mapunit ==0) || ((nat32)atoi(map_unit->mapunit.mukey.c_str()) == searching_for_specific_mapunit))
      found_specific_mapunit = map_unit;
   else delete map_unit;
   return true;
}
//_2011-11-11___________________________________________________________________

/*NYI
bool Soil_generator::done_with
(const std::string &MUkey_or_POLY_ID)
{

}
*/
//_2014-12-25___________________________________________________________________
/*
Mapunit_composition *Soil_generator::render_selected_map_unit
      (const std::string &MUkey_or_POLY_ID)                           rendition_
{  // Currently Database to VIC converter does provide the map unit
   // so this method is not currently used
   assert(false);
   return 0;
}
//_2015-09-28___________________________________________________________________
*/
Mapunit_composition *Soil_generator::render_at_geocoordinate
      (const Geocoordinate &geocoordinate)                            rendition_
{  // Currently Database to VIC converter does provide the map unit
   // so this method is not currently used
   assert(false);
   return 0;
}
//_2015-09-28___________________________________________________________________


} // namespaces STATSGO2

