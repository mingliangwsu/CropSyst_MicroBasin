#include "management_param_class.h"

#include "common/biomatter/biomass_decomposition_param.h"
#include "corn/math/compare.hpp"
#include "CropSyst/source/static_phrases.h"
#include "corn/measure/measures.h"
#include "corn/data_source/vv_file.h"
#include "mgmtevnt.h"
#include "corn/string/strconv.hpp"

namespace CropSyst {
DECLARE_CONTAINER_ENUMERATED_SECTION(Tillage_event                   ,tillage_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Residue_event                   ,residue_operation_section_VV,true); //180418

DECLARE_CONTAINER_ENUMERATED_SECTION(Harvest_or_clipping_event       ,harvest_or_clipping_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Irrigation_event                ,irrigation_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Inorganic_nitrogen_event        ,inorganic_nitrogen_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Biomatter_application_event     ,biomatter_application_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Chemical_event                  ,chemical_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Automatic_N_event               ,auto_N_appl_section_VV,true);

DECLARE_CONTAINER_ENUMERATED_SECTION(N_application_soil_observation_mode_event, N_application_soil_observation_mode_section_VV,true); //151027

DECLARE_CONTAINER_ENUMERATED_SECTION(Automatic_clip_biomass_mode_event,auto_clip_biomass_section_VV,true);

//170420 I intended to redo autoirrigation in V5
//170420 #if ((CROPSYST_VERSION < 5) || defined(VIC_CROPSYST_VERSION) || defined(VIC_CROPSYST_VERSION))
//I dont think this needs to be implemented in V4
DECLARE_CONTAINER_ENUMERATED_SECTION(Automatic_irrigation_mode_event ,auto_irrigation_section_VV,true);
//170420 #endif
} // namespace CropSyst

namespace CropSyst {                                                             //120419
//______________________________________________________________________________
Tillage_operation_class::Tillage_operation_class()
:CropSyst_field_operation_VX()
{  oxidation_effect.sand     =1.5;
   oxidation_effect.clay     =0.5;
   dust_mulch_enable         =false;                                             //051206
   dust_mulch_depth_cm       =10;                                                //051206
   dust_mulch_effective_days =30;                                                //051206
   dust_mulch_intensity      =0;                                                 //051212
}
//_2011-01-13___________________________________________________________________
void Tillage_operation_class::setup_parameters(CORN::Data_record &record,bool for_write)    modification_
{  CropSyst_field_operation_VX::setup_parameters(record, for_write);
   record.expect_bool(LABEL_terminate_crop,terminate_crop,CORN::VV_bool_entry::form_true);     //970616
   record.expect_bool("dust_mulch",dust_mulch_enable,CORN::VV_bool_entry::form_true);          //051206
}
//_2011-01-13___________________________________________________________________
/*170426 replaced with label_string
const char *Tillage_operation_class::label_cstr(char *result)              const
{  CropSyst_field_operation_VX::label_cstr(result);
   strcat(result,": ");                                                          //020507
   if (terminate_crop)                                                           //981007
   {  strcat(result," ");                                                        //981007
      strcat(result,TL_Terminate_crop);                                          //981007
                  // NYI   dust mulch parameters
   }
   return result;
}
//_2011-01-13___________________________________________________________________
*/
const char *Tillage_operation_class::label_string(std::string &result)     const
{  CropSyst_field_operation_VX::label_string(result);
   result += ": ";
   if (terminate_crop)
   {  result += " ";
      result.append(TL_Terminate_crop);
      // NYI   dust mulch parameters
   }
   return result.c_str();
}
//_2017-04-23___________________________________________________________________
void Tillage_operation_class::log(std::ostream &log_file)                const
{  CropSyst_field_operation_VX::log(log_file);
   log_file << LABEL_terminate_crop << "="
   << ((terminate_crop) ? "true" : "false") << std::endl;
}
//_2011-01-13___________________________________________________________________
Organic_nitrogen_operation_abstract_class::Organic_nitrogen_operation_abstract_class(CropSyst_Op cs_op)
: CropSyst_field_operation_VX(cs_op)
, organic_matter_source_cowl      (organic_matter_source,swine_manure)           //110831
, org_N_appl_method_cowl(org_N_appl_method,SURFACE_BROADCAST_NO_INCORPORATION)
{  org_N_kg_ha          = 0.0;
   NH3_N_kg_ha          = 0.0;
   total_solids_kg_ha   = 0.0;
   dry_matter_percent   =  13;
   long_term_org_N_volatilization_loss_percent =  0.0;                           //020525x
   water_depth_mm       = 0;                                                     //110816 added for CAFE dairy
   water_volume_m3      = 0;                                                     //110816 added for CAFE dairy
   injection_depth_cm   = 10.0;                                                  //160119
}
//_2011-01-XX___________________________________________________________________
bool Organic_nitrogen_operation_abstract_class::multiply_amount_by(float32 multiplier) modification_
{  org_N_kg_ha*= multiplier;
   NH3_N_kg_ha*= multiplier;
   water_depth_mm *= multiplier;                                                 //110816
   water_volume_m3 *= multiplier;                                                //110816
   return true;
}
//_2007-07-16___________________________________________________________________
void Organic_nitrogen_operation_abstract_class::setup_parameters(CORN::Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec, for_write);
   data_rec.expect_enum(LABEL_org_N_appl_method,org_N_appl_method_cowl);         //020322
   data_rec.expect_enum("source",organic_matter_source_cowl);                    //110831
      // Currently this is input with a simple field
      // but probably will use parameter_property   110113
}
//_1998-12-28___________________________________________________________________
bool Organic_nitrogen_operation_abstract_class::is_liquid()                const
{  //170217unused bool liquid = false;
   return dry_matter_percent < 20;
}
//_2002-03-22___________________________________________________________________
void Organic_nitrogen_operation_abstract_class::log(std::ostream &log_file) const
{  CropSyst_field_operation_VX::log(log_file);
   //170217unused char buffer[255];                                                             //030123_
   log_file << LABEL_org_N_appl_method << '=' << org_N_appl_method_cowl.get_label() <<std::endl;  //021105
   log_file << "water_depth=" <<water_depth_mm << " mm" << std::endl;            //110816 added for CAFE dairy
   log_file << "water_volume=" << water_volume_m3 << " m3" << std::endl;         //110816 added for CAFE dairy
   log_file << "source=" << organic_matter_source_cowl.get_label() << std::endl; //110816 added for CAFE dairy
}
//_2002-??-??___________________________________________________________________
Inorganic_nitrogen_operation_class::Inorganic_nitrogen_operation_class()
:CropSyst_field_operation_VX(CS_OP_MGMT_INORGANIC_NITROGEN)
,NH4_source_cowl      (NH4_source      ,UREA)
,NH4_appl_method_cowl (NH4_appl_method ,SURFACE_BROADCAST)
{  NO3_N =0.0;
   NH4_N =0.0;
   NH4_volatilization_calculated=true;
   NH4_volatilization =0.0;
   injection_depth_cm = 10;                                                      //160119
   NO3_N = 0.0;                                                                  //160328
   NH4_N = 100.0;                                                                //160328
      // These defaults are for auto N application, the N values are %.
      // Currently 100% as NH4.
   condition.N_soil_critical  = 0.0;   // 0 disables condition                   //170630
   condition.sampling_depth     = 0.0;   // 0 disables condition                   //170630
}
//______________________________________________________________________________
void Inorganic_nitrogen_operation_class::setup_parameters(Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec, for_write);
   data_rec.expect_enum(LABEL_ammonium_source,NH4_source_cowl);                  //020322
   data_rec.expect_enum(LABEL_NH4_appl_method,NH4_appl_method_cowl);             //020322
   data_rec.expect_bool(LABEL_NH4_volatilization_calculated,NH4_volatilization_calculated/*180326,CROPSYST_VV_BOOL_FORM*/); //990227
   data_rec.expect_float32("NO3_N",NO3_N);
   data_rec.expect_float32("NH4_N",NH4_N );
   data_rec.expect_float32("injection_depth",injection_depth_cm);                //160119
   data_rec.expect_float32(LABEL_NH4_volatilization,NH4_volatilization);         //990216

   data_rec.expect_float32("N_soil_critical" ,condition.N_soil_critical);        //170630
   data_rec.expect_float32("sampling_depth"  ,condition.sampling_depth);           //170630
}
//_1998-10-07___________________________________________________________________
/*170426 replaced with label_string
const char *Inorganic_nitrogen_operation_class::label_cstr(char *result)   const
{  CropSyst_field_operation_VX::label_cstr(result);
   strcat(result,TL_Nitrate);
   strcat(result,":");
   strcat(result,CORN::float32_to_cstr(NO3_N,3));
   strcat(result," kg N/ha|");
   strcat(result,TL_Ammonium);
   strcat(result,":");
   strcat(result,CORN::float32_to_cstr(NH4_N,3));
   strcat(result," kg N/ha|");
   return result;
}
//______________________________________________________________________________
*/
const char *Inorganic_nitrogen_operation_class::label_string(std::string &result)   const
{  CropSyst_field_operation_VX::label_string(result);
   result.append(TL_Nitrate); result += ":";
   CORN::append_float32_to_string(NO3_N,3,result);
   result += " kg N/ha|";
   result.append(TL_Ammonium);
   result += ":";
   CORN::append_float32_to_string(NH4_N,3,result);
   result += " kg N/ha|";
   return result.c_str();
}
//_2017-04-23___________________________________________________________________
void Inorganic_nitrogen_operation_class::log(std::ostream &log_file) const
{  CropSyst_field_operation_VX::log(log_file);
   log_file << LABEL_ammonium_source << '=' << NH4_source_cowl.get_label() << std::endl; //021105
   log_file << LABEL_NH4_appl_method << '=' << NH4_appl_method_cowl.get_label() << std::endl;  //021105
}
//______________________________________________________________________________
Harvest_or_clipping_operation_class::Harvest_or_clipping_operation_class()
: CropSyst_field_operation_VX(CS_OP_MGMT_HARVEST_OR_CLIPPING)
, harvest_amount_mode_cowl(harvest_amount_mode,HARVEST_CROP_PARAMETER_BASED)     //110115 050822
, harvest_fate_mode_cowl(harvest_fate_mode,HARVEST_ONCE)
{  clear_biomass_fate_parameters(biomass_fate_percents);                         //050718
   remove_amount_kg_ha           =(0);                                           //050825
   accept_less                   =(false);                                       //051020
   min_retain_GAI                =(0.0);                                         //051103
   min_LAI_required              =(0.0);                                         //020314
   min_biomass_required_kg_ha    =(0.0);                                         //020314
   reserve_biomass_kg_ha         =(0.0);                                         //040807
   grazing_percent_N_as_OM       =(50);                                          //040126
   grazing_percent_N_as_NH3      =(50);                                          //040126
   pasture_composition_legumes_percent=(0.0);                                    //040917
}
//_2011-01-XX___________________________________________________________________
void Harvest_or_clipping_operation_class::setup_parameters(CORN::Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec, for_write);           //970709
   if (get_type() == CS_OP_MGMT_AUTO_CLIP_BIOMASS)                               //110808 teminate does not apply to auto clip mode    //040204
      terminate_crop = false;                                                    //110428
   data_rec.expect_enum("biomass_fate",harvest_fate_mode_cowl);                  //050822
   data_rec.expect_float32("legumes",pasture_composition_legumes_percent);       //040917
   data_rec.expect_enum("harvest_amount_mode",harvest_amount_mode_cowl);         //050822
   data_rec.expect_bool("accept_less",accept_less);                              //051020
}
//_2003-10-14___________________________________________________________________
/*170426 replaced with label_string
const char *Harvest_or_clipping_operation_class::label_cstr(char *result)        const
{  CropSyst_field_operation_VX::label_cstr(result);
   strcat(result," ");
   strcat(result,TL_Remove_from_field);
   char percent_str[10];
   strcat(result," ");
   strcat(result,percent_str);
   strcat(result,"%");
   return result;
}
//_2009-10-14___________________________________________________________________
*/
const char *Harvest_or_clipping_operation_class::label_string(std::string &result)        const
{  CropSyst_field_operation_VX::label_string(result);
   char percent_str[10];
   // warning need to get the percent
   result += " ";
   result.append(TL_Remove_from_field);
   result += " ";
   result.append(percent_str); result+="%";
   return result.c_str();
}
//_2017-04-24___________________________________________________________________
void Harvest_or_clipping_operation_class::log(std::ostream &log_file) const
{  CropSyst_field_operation_VX::log(log_file);
   //NYI
}
//_2002-03-14___________________________________________________________________
Auto_clip_biomass_mode_class::Auto_clip_biomass_mode_class()
: Harvest_or_clipping_operation_class()
{  op_ID = CS_OP_MGMT_AUTO_CLIP_BIOMASS;
   terminate_crop = false;                                                       //040701
   adj_relative_growth_rate = 1.0;                                               //970521
   LAI_forces_clipping      = 0.0;  // 0.0 = option disabled                     //040830
   biomass_forces_clipping  = 4000.0;
   flowering_forces_clipping=0;                                                  //040830
}
//_2010-10-27___________________________________________________________________
Auto_clip_biomass_mode_class::Auto_clip_biomass_mode_class
(const Auto_clip_biomass_mode_class& to_be_copied)
: Harvest_or_clipping_operation_class  (to_be_copied)                            //040204
, Auto_clip_biomass_mode_struct()                                                //171107
{  op_ID = CS_OP_MGMT_AUTO_CLIP_BIOMASS;                                         //040204
   terminate_crop = false;                                                       //040701
   adj_relative_growth_rate       =(to_be_copied.adj_relative_growth_rate);      //011208
   LAI_forces_clipping            =(to_be_copied.LAI_forces_clipping);
   biomass_forces_clipping        =(to_be_copied.biomass_forces_clipping);
   flowering_forces_clipping      =(to_be_copied.flowering_forces_clipping) ;    //040830
}
//_2002-03-14___________________________________________________________________
void Auto_clip_biomass_mode_class::update_considerations()
{  consider_adjust_rate = !CORN::is_approximately<float32>(adj_relative_growth_rate ,NO_adj_relative_growth_rate,0.0001);
   consider_LAI         = !CORN::is_approximately<float32>(LAI_forces_clipping      ,NO_LAI_forces_clipping,0.0001);
   consider_biomass     = !CORN::is_approximately<float32>(biomass_forces_clipping  ,NO_biomass_forces_clipping,0.000001);
   consider_flowering   = flowering_forces_clipping !=  NO_flowering_forces_clipping;
}
//_2004-08-31___________________________________________________________________
void Auto_clip_biomass_mode_class::set_considerations()
{  if (!consider_adjust_rate) adj_relative_growth_rate =NO_adj_relative_growth_rate;
   if (!consider_LAI)         LAI_forces_clipping      =NO_LAI_forces_clipping;
   if (!consider_biomass)     biomass_forces_clipping  =NO_biomass_forces_clipping;
   if (!consider_flowering)   flowering_forces_clipping =  NO_flowering_forces_clipping;
}
//_2004-08-31___________________________________________________________________
void Auto_clip_biomass_mode_class::setup_parameters(Data_record &data_rec,bool for_write)
{  Harvest_or_clipping_operation_class::setup_parameters(data_rec, for_write);
}
//_2002-03-14___________________________________________________________________
Irrigation_operation_class::Irrigation_operation_class(CropSyst_Op  irrig_or_auto_irrig_code )
:CropSyst_field_operation_VX(irrig_or_auto_irrig_code/*,UNKNOWN_NRCS_SDR_operation_number,UNKNOWN_SCS_CODE*/)
,application_mode_cowl(application_mode,irrigate_fixed_amount)
,consideration_mode_cowl(consideration_mode,consider_soil_water_depletion)
,depletion_observation_depth_mode_cowl(depletion_observation_depth_mode,constant_fixed_depth_mode)
{  chemical_name              .assign(""); // In the case of pesticides (NYI)
   amount_mm                  =0;
   salinity                   =0;
   ECw_to_TDS                 =0.64;   // Usually this value, previously hardcoded
   NO3_N_concentration        =0;
   NH4_N_concentration        =0;
   net_irrigation_mult        =1.0;
   refill_point               =1.0;  // default refill to field capacity
   max_allowable_depletion    =0.5;
   depletion_observe_depth_m  =1.0;
   depletion_observe_root_zone_fract=1.0;
   leaf_water_potential       =-1000;
   min_application_mm         =0.0;
   max_application_mm         =200.0;
   soil_wetting.surface_evaporation_area_fraction  = 1.0;                        //130313
   soil_wetting.profile_volume_fraction            = 1.0;                        //130313
}
//_2005-05-11___________________________Irrigation_operation_class:constructor_/
void Irrigation_operation_class::setup_parameters(Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec, for_write);
   data_rec.expect_string(LABEL_chemical,chemical_name/*,CROPSYST_VV_BOOL_FORM*/);
   data_rec.expect_enum("application_mode",application_mode_cowl);               //041106
   data_rec.expect_enum("consideration_mode",consideration_mode_cowl);           //091201
   data_rec.expect_enum("depletion_observation_depth_mode",depletion_observation_depth_mode_cowl); //070606

   // Need to create validators for these and move to management_param_V4 and management_param_V5
   data_rec.expect_float32("wetting_surface_evaporation_area_fraction",soil_wetting.surface_evaporation_area_fraction); //130313
   data_rec.expect_float32("wetting_profile_volume_fraction"          ,soil_wetting.profile_volume_fraction);           //130313
   data_rec.expect_nat16("irrigation_type",irrigation_type,10);                  //150701LML
}
//_1998-10-07___________________________________________________________________
float64 Irrigation_operation_class::get_min_application_m()                const { return (application_mode==irrigate_fixed_amount) ? 0.0      : mm_to_m(min_application_mm); } //060719
float64 Irrigation_operation_class::get_max_application_m()                const { return (application_mode==irrigate_fixed_amount) ? 999999.0 : mm_to_m(max_application_mm); } //981212
//_2011-01-XX___________________________________________________________________
bool Irrigation_operation_class::multiply_amount_by(float32 multiplier) modification_
{  amount_mm *= multiplier;
   return true;
}
//_2009-07-16___________________________________________________________________
const char *Irrigation_operation_class::label_string(std::string &result)  const
{  CropSyst_field_operation_VX::label_string(result);
   std::string buffer1(TL_Refill_plant_available_water);
   std::string buffer2(std::string(CORN::float32_to_cstr(amount_mm,3)) + std::string(" mm "));
   std::string practice((amount_mm == 0.0) ? buffer1 : buffer2);
   practice += CORN::float32_to_cstr(  salinity,3);
   practice += " (dS/m) ";
   practice += CORN::float32_to_cstr( NO3_N_concentration,3);
   practice += " (kgN/m³H2O) ";
   practice += CORN::float32_to_cstr(  NH4_N_concentration,3);
   practice += " (kgN/m³H2O) ";
   // 080402 New ECw to TDS conversion factor is not currently output here.
#ifdef NYI
   buffer2.assign(std::string(" kg ") +chemical_name + std::string("/m3 water"));
#endif
   practice += (chemical_name == LABEL_salt) ? buffer1 : buffer2;
   result.append(TL_Irrigation);
   result += " " + practice;
   return result.c_str();
}
//_2017-04-23___________________________________________________________________
void Irrigation_operation_class::log(std::ostream &log_file)               const
{  CropSyst_field_operation_VX::log(log_file);
   if (CORN::is_approximately<float32>(amount_mm,0.0,0.00001))                   //120427
      log_file << "refill_PAW=true" << std::endl;
}
//______________________________________________________________________________
Automatic_irrigation_mode_class::Automatic_irrigation_mode_class()
:  Irrigation_operation_class(CS_OP_MGMT_AUTO_IRRIGATION)                        //040511
{}
//_2002-03-13___________________________________________________________________
const char *Automatic_irrigation_mode_class::label_string(std::string &buffer)      const
{  Irrigation_operation_class::label_string(buffer);
   buffer += TL_Automatic_irrigation;
   return buffer.c_str();
}
//_2017-04-23___________________________________________________________________
void N_application_soil_observation_mode_class::Split_application::setup_parameters
(Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec, for_write);
   data_rec.expect_int16(LABEL_percent,percent_of_application);
   Inorganic_nitrogen_operation_class::setup_parameters(data_rec,for_write);     //120711
}
//_1999-11-22___________________________________________________________________
const char *N_application_soil_observation_mode_class::Split_application::label_string(std::string &result) const
{  CropSyst_field_operation_VX::label_string(result);
   result.append(TL_Percent_of_seasonal_application);
   result += " NO3: ";
   CORN::append_int16_to_string(percent_of_application,result,10);
   result += "%";
   // During runtime we will calculate the actual amount (this will not be printed in the parameter editor).
   if (!CORN::is_approximately<float32>(actual_NO3_kg_m2,0.0,0.000001))
   {  result += " (";
      CORN::append_float32_to_string((float32)per_m2_to_per_ha(actual_NO3_kg_m2),1,result);
      result += ") ";
      result.append(TU_kg_ha);
   }
   result += " NH4: ";
   CORN::append_int16_to_string(percent_of_application,result,10);
   result += "%";
   // During runtime we will calculate the actual amount (this will not be printed in the parameter editor).
   if (!CORN::is_approximately<float32>(actual_NH4_kg_m2,0.0,0.000001))
   {  result += " (";
      CORN::append_float32_to_string((float32)per_m2_to_per_ha(actual_NH4_kg_m2),1,result);
      result += ") ";
      result.append(TU_kg_ha);
   }
   return result.c_str();
}
//_2017-04-24___________________________________________________________________
void N_application_soil_observation_mode_class::setup_parameters(CORN::Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec,for_write);
   data_rec.expect_bool(LABEL_split_applications,split_applications/*,CROPSYST_VV_BOOL_FORM*/); //020611
/*1706023 obsolete now Supplemental application is achieved with
normal fixed management but now condition for application is added
   data_rec.expect_bool   ("supplemental.enabled"        ,supplemental.enabled,CROPSYST_VV_BOOL_FORM);   //161201
   data_rec.expect_float32("supplemental.critical_soil_N",supplemental.critical_soil_N_kg_ha);           //161201
   data_rec.expect_float32("supplemental.fraction"       ,supplemental.fraction);   //161205
*/
}
//_1997-07-09___________________________________________________________________
N_application_soil_observation_mode_class::N_application_soil_observation_mode_class()
: CropSyst_field_operation_VX(CS_OP_MGMT_SOIL_N_SAMPLING)                        //120625_030824
,automatic_N_mode_cowl(automatic_N_mode,AUTO_NITRO_DISABLED)                     //020322
{  target_yield_N_uptake_kg_ha            =(0.0);
   #if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION <=4))
   critical_soil_N_for_no_response_kg_ha  =(0.0);
   #endif
   fertilizer_use_efficiency              =(100.0) ;
   soil_N_sampling_depth                  =(1.0);
   split_applications                     =(false) ;
   total_N_application_kg_m2              =(0.0);
   name = "Soil N sampling";                                                     //120625
   estimated_mineralization_kg_ha         = 30.0;                                //120711
/*1706023 obsolete now Supplemental application is achieved with
normal fixed management but now condition for application is added
   supplemental.enabled = false;                                                 //161201
   supplemental.critical_soil_N_kg_ha = 0.0;                                     //161201
   supplemental.fraction = 0.0;
*/
}
//______________________________________________________________________________
void N_application_soil_observation_mode_class::log(std::ostream &log_file) const
{  CropSyst_field_operation_VX::log(log_file);
   log_file << LABEL_automatic_N_mode << '=' << automatic_N_mode_cowl.get_label() << std::endl;  //021105
   log_file << "total_N_application=" << per_m2_to_per_ha(total_N_application_kg_m2) << std::endl;
   log_file << "total_N_application_units=" <<  TU_kgN_ha << std::endl;
}
//_2002-03-11___________________________________________________________________
const char *N_application_soil_observation_mode_class::label_string(std::string &buffer) const
{  buffer.append(TL_Soil_N_sampling_depth );
   buffer +=  " ";
   append_float32_to_string(soil_N_sampling_depth,1,buffer);
   buffer += ". ";
   buffer.append(TL_Total_seasonal_application);
   buffer += ": ";
   if (CORN::is_approximately<float32>(total_N_application_kg_m2,0.0,0.000001))
      buffer += "calculated when sampling is performed at runtime.";
   else
   {  append_float32_to_string(per_m2_to_per_ha(total_N_application_kg_m2),1,buffer);
      buffer +=" ";
      buffer.append(TU_kgN_ha);
   }
   return buffer.c_str();
}
//_2017-04-23___________________________________________________________________
void N_application_soil_observation_mode_class::Split_application::log(std::ostream &log_file) const
{  CropSyst_field_operation_VX::log(log_file);
   log_file << "percent_of_application=" << (int)get_percent_of_application() << std::endl;
   log_file << "amount="
      << per_m2_to_per_ha(actual_NO3_kg_m2+actual_NH4_kg_m2)
      << " " << TU_kg_ha << std::endl;
}
//_2011-01-XX___________________________________________________________________
Management_parameters_class::Management_parameters_class()
:Common_parameters_data_record         (NO_ASSOCIATED_DIRECTORY,LABEL_management,CS_VERSION) //180626_ CS_VERSION_NUMBERS)  //050323
,crop_management                       (true)                                    //030606
,land_treatment_labeled                (DEFAULT_land_treatment)                  //020322
,irrigation_operations                 ()                                        //981007
,inorganic_nitrogen_operations         ()                                        //981007
,biomatter_application_operations      ()                                        //080902
,tillage_operations                    ()                                        //981007
,residue_operations                    ()                                        //981007
,harvest_or_clipping_operations        ()                                        //031014
,chemical_operations                   ()                                        //981007
,auto_irrigation_mode_operations       ()                                        //020313
,auto_clip_biomass_mode_operations     ()                                        //011207
,automatic_nitrogen                    (false)                                   //060810
,soil_conservation_factor(DEFAULT_soil_conservation_factor)
,seasonal_carbon_footprint_kgCO2e_ha(0)                                          //120430
,seasonal_irrigation_carbon_footprint_kgCO2e_ha(0)                               //120430
,irrigation_application_carbon_footprint_kgCO2e_ha_mm(0)                         //120430
,CANMS_support(false)                                                            //060103
{  N_application_soil_observation_event = new N_application_soil_observation_mode_event;  //060804
}
//______________________________________________________________________________
bool Management_parameters_class::expect_structure(bool for_write)
{  bool expected = Common_parameters_data_record::expect_structure(for_write);   //161025_040614
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_management);
   expect_enum(LABEL_land_treatment,land_treatment_labeled);
   expect_bool("crop_management",crop_management);                               //030606
   expect_bool("automatic_nitrogen",automatic_nitrogen);                         //060804
//NYI
//   expect_bool("recommended_automatic_irrigation",recommended_automatic_irrigation); //110719
//   expect_enum("irrigation_system", irrigation_system_labeled);
   set_current_section("carbon_footprint");
   expect_float32("seasonal",seasonal_carbon_footprint_kgCO2e_ha);               //120430
   expect_float32("seasonal_irrigation",seasonal_irrigation_carbon_footprint_kgCO2e_ha); //120430
   expect_float32("irrigation_application",irrigation_application_carbon_footprint_kgCO2e_ha_mm); //120430

   set_current_section(LABEL_management);                                                                                                    //990225
   EXPECT_ENUMERATED_SECTION(LABEL_tillage               ,tillage_operation_section_VV             ,tillage_operations);                     //020617
   EXPECT_ENUMERATED_SECTION(LABEL_harvest               ,harvest_or_clipping_operation_section_VV ,harvest_or_clipping_operations);         //020617
   EXPECT_ENUMERATED_SECTION(LABEL_irrigation            ,irrigation_operation_section_VV          ,irrigation_operations);                  //020617
   EXPECT_ENUMERATED_SECTION(LABEL_fertilization         ,inorganic_nitrogen_operation_section_VV  ,inorganic_nitrogen_operations);          //020617
   EXPECT_ENUMERATED_SECTION("biomatter_application"    ,biomatter_application_operation_section_VV,biomatter_application_operations);       //080902
   EXPECT_ENUMERATED_SECTION(LABEL_chemical              ,chemical_operation_section_VV            ,chemical_operations);                    //020617
   EXPECT_ENUMERATED_SECTION(LABEL_auto_clip_biomass     ,auto_clip_biomass_section_VV             ,auto_clip_biomass_mode_operations);      //020617
/* NYI  Not sure how I am going to handle Auto irrig event in V5

this does need to be implemented
*/
//170420 #if (CROPSYST_VERSION < 5 || defined(VIC_CROPSYST_VERSION))
   EXPECT_ENUMERATED_SECTION(LABEL_automatic_irrigation  ,auto_irrigation_section_VV               ,auto_irrigation_mode_operations);        //020617
//170420 #endif
   {  set_current_section("automatic_nitrogen");                                 //040712
         expect_enum(LABEL_automatic_N_mode, N_application_soil_observation_event->automatic_N_mode_cowl);  //120710
         expect_bool("split_N_applications",N_application_soil_observation_event->split_applications);      //040712
         if (!for_write)                                                         //040712
            expect_bool(
               "split_auto_N_applications"
               ,N_application_soil_observation_event->split_applications);       //040712
         /*170630 now supplementat N application is acheived with repeating conditional fixed applications
         expect_bool   ("supplemental.enabled"        ,N_application_soil_observation_event->supplemental.enabled,CROPSYST_VV_BOOL_FORM);   //161205
         expect_float32("supplemental.critical_soil_N",N_application_soil_observation_event->supplemental.critical_soil_N_kg_ha);           //161205
         expect_float32("supplemental.fraction"       ,N_application_soil_observation_event->supplemental.fraction);   //161205
         */

      set_current_section("soil_N_sampling");                                    //040712
         N_application_soil_observation_event->begin_sync.setup_structure(*this,for_write,0); //120625
         #if (MANAGEMENT == 4)
         //expect_valid_float32      (N_application_soil_observation_event->v_soil_N_sampling_depth);
         // Move this to V4
         #else
         // Need to implement in V5 ???
         #endif
   }
   EXPECT_ENUMERATED_SECTION("auto_N_application",auto_N_appl_section_VV ,auto_N_applications); //020617
   set_current_section("CANMS");                                                 //060103
      expect_bool("CANMS_support",CANMS_support);                                //060103
   // currently we only have one period, but we may add more.
   set_current_section(LABEL_management);                                        //990225
   structure_defined = true;                                                     //120314
   return expected;                                                              //161025
}
//______________________________________________________________________________
bool Inorganic_nitrogen_operation_class::multiply_amount_by(float32 multiplier) modification_
{  NO3_N *= multiplier;
   NH4_N *= multiplier;
   return true;
}
//_2009-07-16___________________________________________________________________
void Automatic_irrigation_mode_class::setup_parameters(Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec, for_write);           //120427
   Irrigation_operation_class::setup_parameters(data_rec, for_write);
}
//_1997-07-09___________________________________________________________________
Chemical_operation_class::Chemical_operation_class()
:CropSyst_field_operation_VX(CS_OP_MGMT_CHEMICAL)
{  chemical_name             ="";
   chemical_concentration = 0.0;
}
//______________________________________________________________________________
/*170426 replaced with label_string
const char *Chemical_operation_class::label_cstr(char *result)             const
{  CropSyst_field_operation_VX::label_cstr(result);
   // Not currently implemented
   return result;
}
//______________________________________________________________________________
*/
const char *Chemical_operation_class::label_string(std::string &result)             const
{  CropSyst_field_operation_VX::label_string(result);
   // Not currently implemented
   return result.c_str();
}
//_2017-04-24___________________________________________________________________
void Chemical_operation_class::log(std::ostream &log_file)                 const
{  CropSyst_field_operation_VX::log(log_file);
   // NYI
}
//______________________________________________________________________________
void Chemical_operation_class::setup_parameters(Data_record &data_rec,bool for_write)
{  CropSyst_field_operation_VX::setup_parameters(data_rec, for_write);
   data_rec.expect_string(LABEL_chemical,chemical_name,32);
   data_rec.expect_float32(LABEL_concentration,chemical_concentration);
}
//_1998-10-07___________________________________________________________________
int16 Management_parameters_class::total_automatic_N_applications()        const
{  int16 total = 0;
   FOR_EACH_IN(auto_N_split_event,Automatic_N_event,auto_N_applications,each_appl) //030709
      total += auto_N_split_event->get_percent_of_application();
   FOR_EACH_END(each_appl)
   return total;
}
//_2002-04-03___________________________________________________________________
nat32 Management_parameters_class::irrigation_multiply_by(float32 multiplier) modification_
{  // This is used by Management generation when
   // generating adjusted irrigation amounts
   nat32 count = 0;
   FOR_EACH_IN(irrig,Irrigation_operation,irrigation_operations,each_irrig)
       count += irrig->multiply_amount_by(multiplier);
   FOR_EACH_END(each_irrig)
   FOR_EACH_IN(auto_irrig,Automatic_irrigation_mode,auto_irrigation_mode_operations,each_irrig)
       count += auto_irrig->multiply_amount_by(multiplier);
   FOR_EACH_END(each_irrig)
   return count;
}
//_2007-07-16___________________________________________________________________
nat32 Management_parameters_class::fertilization_nitrogen_multiply_by(float multiplier) modification_
{  nat32 count = 0;
   FOR_EACH_IN(inorg_N,Inorganic_nitrogen_operation,inorganic_nitrogen_operations,each_inorg_N)
       count += inorg_N->multiply_amount_by(multiplier);
   FOR_EACH_END(each_inorg_N)
   FOR_EACH_IN(biomatter_op,Biomatter_application_operation
              ,biomatter_application_operations,each_biomatter_op)               //080902
      count += biomatter_op->multiply_amount_by(multiplier);                     //080902
   FOR_EACH_END(each_biomatter_op)
   return count;
}
//_2007-07-16___________________________________________________________________
bool Management_parameters_class::delete_event(Common_event *delete_event) modification_
{
   // We don't know which type op operation.
   // just delete it in which ever list has it
   return
      irrigation_operations            .remove(delete_event)
   || auto_irrigation_mode_operations  .remove(delete_event)
   || inorganic_nitrogen_operations    .remove(delete_event)
   || biomatter_application_operations .remove(delete_event)
   || tillage_operations               .remove(delete_event)
   || residue_operations               .remove(delete_event)
   || chemical_operations              .remove(delete_event)
   || harvest_or_clipping_operations   .remove(delete_event)
   || auto_N_applications              .remove(delete_event)
   || auto_clip_biomass_mode_operations.remove(delete_event);
}
//_2017-07-01___________________________________________________________________


} // namespace CropSyst

/* 131011
Conceptuatal
Need some mechanism to remove biomass

This may be with harvest event
% of yield disposed
with one of the following fate options:
sold (low value)
disposed (off farm/field - loss)
fodder (to be used as animal feed)
residue (dump/left on the field)
*/

