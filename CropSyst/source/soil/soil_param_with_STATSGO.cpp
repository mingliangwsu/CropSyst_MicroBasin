#error This is obsolete the original STATSGO database nolonger exists , now use STATSGO2_to_CS_soil
#ifndef __unix
// Not currently implemented in Unix / Linux
#include "soil/soil_param_with_STATSGO.h"
#include <STATSGO/library/misc_codes.h>

#     include <STATSGO/library/STATSGO_database.h>
#  	include <STATSGO/library/comp_dbf.h>
#  	include <STATSGO/library/layer_dbf.h>
#  include <common/soil/txtrhydr.h>
#include <common/soil/texture.h>
#include <corn/math/compare.hpp>
#include <corn/measure/measures.h>

using namespace STATSGO;
//______________________________________________________________________________
void Smart_soil_parameters_with_STATSGO::expect_structure(bool for_write)
{  Smart_soil_parameters::expect_structure( for_write);
   structure_defined = false;                                                    //120314
   set_current_section("STATSGO");
   expect_string("STATSGO_path" ,STATSGO_path,255);
   expect_string("MUID"          ,MUID,10);
   expect_int16("SEQNUM"        ,SEQNUM);
   expect_int16("COMPPCT",    COMPPCT);                                          //080303
   structure_defined = true;                                                     //120314
};
//_2005-09-21___________________________________________________________________
bool Smart_soil_parameters_with_STATSGO::interpret_STATSGO_layer
(nat8 curr_layer,STATSGO::LAYER_data_record &layer_record)
{
   // get texture class:
   Soil_texture curr_texture(layer_record.TEXTURE1.c_str());
   bool is_root_penetratable  = curr_texture.is_root_penetratable();
   // We now store pH and CEC by layer.                                          //011130
   pH[curr_layer]                        = (layer_record.PHL + layer_record.PHH) / 2.0;
   cation_exchange_capacity[curr_layer]  = (layer_record.CECL + layer_record.CECH) / 2.0;
   organic_matter[curr_layer]           = (layer_record.OML + layer_record.OMH) /2.0;
   organic_matter_low[curr_layer]        = layer_record.OML;            //070607
   organic_matter_high[curr_layer]       = layer_record.OMH;            //070607
   if (is_root_penetratable)
   {
      horizon_thickness_32[curr_layer] = inch_to_m(layer_record.LAYDEPH - layer_record.LAYDEPL);
      // Get clay range: (not currently used)
      // not currently used     uint16 curr_clay_low = layer_record.CLAYL;
      // not currently used     uint16 curr_clay_high = layer_record.CLAYH;

      this->horizon_sand[curr_layer] = curr_texture.get_sand();
      this->horizon_clay[curr_layer] = curr_texture.get_clay();
      this->horizon_silt[curr_layer] = curr_texture.get_silt();
      // Clay data is is available in STATSGO for some layer
      float32 mean_clay =(layer_record.CLAYH + layer_record.CLAYL) / 2.0;
      if (!CORN::is_approximately<float32>(mean_clay,0.0,0.000001))   // (may be  recorded as 0.0 for unknown clay or bedrock etc.
      {  // readjust silt based on fixed clay value
                  this->horizon_clay[curr_layer] = mean_clay;
                  this->horizon_silt[curr_layer] = 100.0 - (this->horizon_sand[curr_layer] + mean_clay);
      };
      // Bulk density is available in STATSGO
      // we could set bulk density as fixed value.
      float32 mean_bulk_density = (layer_record.BDH + layer_record.BDL) / 2.0;
      if (!CORN::is_approximately<float32>(mean_bulk_density,0.0,0.000001))   // (Bulk density is recorded as 0.0 for bedrock etc.
         layer_texture_hydraulics[curr_layer]->set_bulk_density(mean_bulk_density   ,  Soil_texture_hydraulics::fixed);

//                      Compute:
//                      bulk_density_16
//                      perm_wilt_point_16
//                      field_capacity_16
//                      vol_WC_at_1500_16
//                      vol_WC_at_33_16
//                      sat_hydraul_cond_m_d
//                      SFair_entry_pot
//                      SFsoil_b
      layer_texture_hydraulics[curr_layer]->recompute_every_thing();
      horizon_permanent_wilt_point_32[curr_layer] = vol_WC_at_1500_32[curr_layer];
      horizon_field_capacity_32[curr_layer] = vol_WC_at_33_32[curr_layer];
      number_horizons = std::max<nat8>(number_horizons,curr_layer);
   };
   return is_root_penetratable;
};
//_2006-01-27___________________________________________________________________
bool Smart_soil_parameters_with_STATSGO::read_available_STATSGO_data
(STATSGO::Database::State_tables &state_tables
,const char *_MUID  // I.e. WA0001
,uint8       _SEQNUM // sequence number
,uint8       _COMPPCT
,float32     _max_evap_layer_thickness_m)
{  bool database_file_and_entries_found = false;
   Map_unit_component_data_record map_unit_comp_rec;
   if (state_tables.get_map_unit_component(_MUID, _SEQNUM,map_unit_comp_rec))
   {  // Transfer relevent data to soil data:
      description.assign(map_unit_comp_rec.MUIDSEQNUM);
      description.append(" ");
      description.append(map_unit_comp_rec.COMPNAME);
      MUID.assign(_MUID);
      SEQNUM = (int16)_SEQNUM;
      COMPPCT = (int16)_COMPPCT;
      // Actually, for description lookup muid in mapunit.dbf and get MUNAME + COMPNAME
      // override_leaching_depth use default false
      // override_leaching_depth N/A leave default
      // float32 leaching_depth_16 N/A leave default
      hydrologic_group_labeled.set(map_unit_comp_rec.HYDGRP.get());
      switch (map_unit_comp_rec.DRAINAGE)
      {  case very_poor :
         case poor      :
         case somewhat_poor      : hydrologic_condition_labeled.set(POOR);
         break;
         case moderate           : hydrologic_condition_labeled.set(GOOD); // FAIR;
         break;
         case well :
         case somewhat_excessive :
         case excessive          : hydrologic_condition_labeled.set(GOOD);
         break;
         default : hydrologic_condition_labeled.set(GOOD) ; break;
      };
      // override_curve_number_16; N/A leave default
      // user_fallow_curve_number_16; N/A leave default
      // compute_surface_storage N/A Leave user selected value
      // surface_storage_mm_16 N/A
      set_steepness_percent((map_unit_comp_rec.SLOPEL + map_unit_comp_rec.SLOPEH) / 2);
      // slope_length_16  use default value
      //  texture is now available by soil layer
      //int16  percent_sand;  // % 0-100  we could use the surface texture
      //int16  percent_clay;  // % 0-100
      //int16  percent_silt;  // % 0-100
      database_file_and_entries_found = true;
   };
   bool evap_layer_split = false;                                             //000327
   {
      number_horizons = 0;  // Reset number of layers so we can use what is in the database 000323
      bool more_layers = true;                                                   //050921
      for (int statsgo_layer = 1; (statsgo_layer <= 20) && more_layers; statsgo_layer++)  //050921
      {  STATSGO::LAYER_data_record layer_record;  // Map_unit_layer_data_record //030220
         more_layers =
            state_tables.get_map_unit_layer(_MUID, _SEQNUM,statsgo_layer,layer_record);   //060127
         if (more_layers)
         {  // Get layer number
            uint8 curr_layer = layer_record.LAYERNUM + evap_layer_split;
            database_file_and_entries_found = interpret_STATSGO_layer(curr_layer,layer_record); //060131
            user[curr_layer] = 0xFFFF;                                           //070808
//                             specified_texture           |   1
//                             specified_FC                |   2
//                             specified_PWP               |   4
//                             pecified_bulk_density      |   8
//                             specified_vol_WC_1500       |  16
//                             specified_vol_WC_33         |  32
//                             specified_sat_hydraul_cond  |  64
//                             specified_air_entry_pot     | 128 // currently either present or not (always calculated)
//                             specified_soil_B            | 256 // currently either present or not
//                             specified_sand              | 512
//                             specified_clay              |1024
//                             specified_silt              |2048

//                         If layer 1 is thicker than 5mm, then split the layer for Proper cascade functioning
            if ((curr_layer == 1) && (horizon_thickness_32[curr_layer] > _max_evap_layer_thickness_m /*051201 0.05*/))
            {  evap_layer_split = true;
               horizon_thickness_32[2] = horizon_thickness_32[curr_layer] - _max_evap_layer_thickness_m /*051201 0.05*/;
               horizon_thickness_32[1] = _max_evap_layer_thickness_m /*051201 0.05*/;
               user[2] = user[1];                                                //070808
               number_horizons = 2; // So far, atleast 2 layers.
               // texture is split below
            };
         };
      };
   };
   if (evap_layer_split)
   {  // Horizon 1 has been split to give a thin evaporative layer
      // Copy all the properties to the second layer.
      // (Thickness already set above)
         copy_horizon(1,2);
   };
   return database_file_and_entries_found;
};
//_2006-01-27__2000-03-27_______________________________________________________
bool Smart_soil_parameters_with_STATSGO::read_available_STATSGO_data
(STATSGO::Database  &STATSGO_database                                            //060213
,const char *_MUID  // I.e. WA0001
,uint8       _SEQNUM // sequence number
,uint8       _COMPPCT                                                            //080303
,float32     _max_evap_layer_thickness_m)                                        //051201
{
//          Read any relevent data from the STATSGO database.
//          Also derive any relevent data I.e. compute hydraulic properties from texture.
   bool database_file_and_entries_found = false;
   if (STATSGO_database.good())
   {  char state_code[3];  state_code[0] = MUID[0]; state_code[1] = MUID[1]; state_code[2] = 0;
      STATSGO::Database::State_tables *state_tables = STATSGO_database.provide_state_tables(state_code) ;
      database_file_and_entries_found = read_available_STATSGO_data(*state_tables,_MUID,_SEQNUM,_COMPPCT,_max_evap_layer_thickness_m);
   };
   return database_file_and_entries_found;
};
//_2005-09-21__2000-01-13_______________________________________________________
#endif
