#include "management/management_param_V5.h"
#if (MANAGEMENT!=4)

using namespace CORN;
#define NoAltFieldName ""
#define NotYetSubsection "NotYetSubsection"
#include "CropSyst/source/static_phrases.h"
#include "common/biomatter/biomass.h"
#include "common/biomatter/biomass_decomposition_param.h"
#include "corn/data_source/vv_file.h"
#include "mgmtevnt.h"

#include "common/residue/residue_decomposition_param.h"

#define ARIBTRARY_FIELD_WIDTH 8
// At this time field format widths have not been specifically designed
namespace CropSyst {

//______________________________________________________________________________
DECLARE_CONTAINER_ENUMERATED_SECTION(Tillage_event                   ,tillage_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Residue_event                   ,residue_operation_section_VV,true); //180418
DECLARE_CONTAINER_ENUMERATED_SECTION(Harvest_or_clipping_event       ,harvest_or_clipping_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Irrigation_event                ,irrigation_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Inorganic_nitrogen_event        ,inorganic_nitrogen_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Biomatter_application_event     ,biomatter_application_operation_section_VV,true);
DECLARE_CONTAINER_ENUMERATED_SECTION(Chemical_event                  ,chemical_operation_section_VV,true);

/* NYI  Not sure how I am going to handle auto NO3 event in V5

this does need to be implemented

DECLARE_CONTAINER_ENUMERATED_SECTION(Automatic_NO3_event             ,auto_NO3_appl_section_VV,true);

*/

DECLARE_CONTAINER_ENUMERATED_SECTION(Automatic_clip_biomass_mode_event,auto_clip_biomass_section_VV,true);

//170420 #ifdef VIC_CROPSYST_VERSION
//this does need to be implemented
DECLARE_CONTAINER_ENUMERATED_SECTION(Automatic_irrigation_mode_event ,auto_irrigation_section_VV,true);
//170420 #endif
//______________________________________________________________________________

//140314 Parameter_number_properties_literal  PPN_fraction_3decimals = {0.0,1.0,0.0,1.0,3};
Parameter_range  PPR_fraction           = {0.0,1.0,0.0,1.0};
//Parameter_format PPF_fraction_3decimals = {ARIBTRARY_FIELD_WIDTH,3};
Parameter_format PPF_arbitrary_0decimals= {ARIBTRARY_FIELD_WIDTH,0};
Parameter_format PPF_arbitrary_1decimals= {ARIBTRARY_FIELD_WIDTH,1};
Parameter_format PPF_arbitrary_2decimals= {ARIBTRARY_FIELD_WIDTH,2};
Parameter_format PPF_arbitrary_3decimals= {ARIBTRARY_FIELD_WIDTH,3};

// used for:
// surface_evaporation_area_fraction
// profile_volume_fraction
// refill point

Parameter_properties_literal PP_dust_mulch_depth      = {"dust_mulch_depth"         ,NoAltFieldName,NotYetSubsection,"Dust mulching depth"   ,"hint","%PROG_HOME%:path/document.HTM#anchor",UC_cm};                                                   Parameter_range PPR_dust_mulch_depth      = {0,100,0,300}; Parameter_format PPF_dust_mulch_depth      = {ARIBTRARY_FIELD_WIDTH,1}; //width =8 is arbitrary
Parameter_properties_literal PP_dust_mulch_effective  = {"dust_mulch_effective_days",NoAltFieldName,NotYetSubsection,"Number of days until mulch effect subsides"   ,"without precipitation","%PROG_HOME%:path/document.HTM#anchor",UT_day,"days"};   Parameter_range PPR_dust_mulch_effective  = {0, 60,0,365}; Parameter_format PPF_dust_mulch_effective  = {ARIBTRARY_FIELD_WIDTH,0};
Parameter_properties_literal PP_dust_mulch_intensity  = {"dust_mulch_intensity"     ,NoAltFieldName,NotYetSubsection,"Dust mulching intensity"   ,"(0.0 = no effect, 1.0 = sever)","%PROG_HOME%:path/document.HTM#anchor",UC_adjustment};             Parameter_range PPR_dust_mulch_intensity  = {0,0.9,0,1.0}; Parameter_format PPF_dust_mulch_intensity  = {ARIBTRARY_FIELD_WIDTH,2};
Parameter_properties_literal PP_oxidation_effect_sand = {"sand_oxidation"           ,NoAltFieldName,NotYetSubsection,"sand"   ,"tillage oxidation effect","%PROG_HOME%:path/document.HTM#anchor",UC_multiplier};                                      Parameter_range PPR_oxidation      = {0.0,10.0,0.0,100.0}; Parameter_format PPF_oxidation             = {ARIBTRARY_FIELD_WIDTH,4}; //width =8 is arbitrary
Parameter_properties_literal PP_oxidation_effect_clay = {"clay_oxidation"           ,NoAltFieldName,NotYetSubsection,"clay"   ,"tillage oxidation effect","%PROG_HOME%:path/document.HTM#anchor",UC_multiplier};


Parameter_properties_literal PP_soil_N_sampling_depth = {LABEL_sampling_depth,LABEL_sampling_depth,NotYetSubsection,TL_Soil_N_sampling_depth,"","HTTP:\\descriptionURL",UC_meter};
Parameter_range PPR_soil_N_sampling_depth={0.0,    3.0,0.0,    4.0 };    //PPF_arbitrary_2decimals

//______________________________________________________________________________
Tillage_operation::Tillage_operation()
:Tillage_operation_class()
,p_dust_mulch_depth_cm        (dust_mulch_depth_cm       ,PP_dust_mulch_depth       ,PPR_dust_mulch_depth         ,PPF_dust_mulch_depth)
,p_dust_mulch_effective_days  (dust_mulch_effective_days ,PP_dust_mulch_effective   ,PPR_dust_mulch_effective     ,PPF_dust_mulch_effective)
,p_dust_mulch_intensity       (dust_mulch_intensity      ,PP_dust_mulch_intensity   ,PPR_dust_mulch_intensity     ,PPF_dust_mulch_intensity)
,p_oxidation_effect_sand      (oxidation_effect.sand     ,PP_oxidation_effect_sand  ,PPR_oxidation                ,PPF_oxidation)
,p_oxidation_effect_clay      (oxidation_effect.clay     ,PP_oxidation_effect_clay  ,PPR_oxidation                ,PPF_oxidation)
{}
//_2011-01-13___________________________________________________________________
void Tillage_operation::setup_parameters(CORN::Data_record &record,bool for_write)
{
   Tillage_operation_class::setup_parameters(record,for_write);
   record.expect_parameter(p_dust_mulch_depth_cm);
   record.expect_parameter(p_dust_mulch_effective_days);
   record.expect_parameter(p_dust_mulch_intensity);
   record.expect_parameter(p_oxidation_effect_sand);
   record.expect_parameter(p_oxidation_effect_clay);
}
//_2011-01-13___________________________________________________________________
//______________________________________________________________________________
Parameter_properties_literal PP_org_N = {LABEL_org_N,LABEL_org_N,NotYetSubsection,"Nitrogen mass in organic form","Hint","HTTP:\\descriptionURL",UC_kg_ha};
Parameter_range PPR_org_N={0.0, 400.0, 0.0,2000.0 };

Parameter_properties_literal PP_NH3_N = {LABEL_NH3_amount,LABEL_NH3_amount,NotYetSubsection,TL_Amount_N_form_of_ammonia,"Hint","HTTP:\\descriptionURL",UC_kg_ha};
Parameter_range PPR_NH3_N={0.0,1000.0, 0.0,1000.0 };

Parameter_properties_literal PP_dry_matter = {"dry_matter","DM",NotYetSubsection,"Dry matter of fresh manure","percent not water","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_dry_matter={3.0,  20.0, 0.0, 100.0 };  Parameter_format PPF_XXXX = {ARIBTRARY_FIELD_WIDTH,1};

Parameter_properties_literal PP_long_term_org_N_volatilization_loss = {LABEL_long_term_org_N_volatilization,"LTorgNvol",NotYetSubsection,"Long term NH3 volatilization","including mineralized organic N","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_long_term_org_N_volatilization_loss ={0.0, 100.0, 0.0, 100.0 };

/*130406  NYI
Parameter_properties_literal PP_total_solids = {LABEL_xxxxNH3_amount,LABELxxxx_NH3_amount,8,TL_xxxxAmount_N_form_of_ammonia,"Hint","HTTP:\\descriptionURL",UC_kg_ha};
Parameter_range PPR_total_solids={0.0,1000.0, 0.0,1000.0 };   PPF_arbitrary_3decimals
*/

Organic_nitrogen_operation_abstract::Organic_nitrogen_operation_abstract(CropSyst_Op cs_op)
: Organic_nitrogen_operation_abstract_class(cs_op)
,p_org_N       (org_N_kg_ha     ,PP_org_N ,PPR_org_N,PPF_arbitrary_3decimals)
,p_NH3_N       (NH3_N_kg_ha     ,PP_NH3_N ,PPR_NH3_N,PPF_arbitrary_3decimals)
,p_dry_matter  (dry_matter_percent,PP_dry_matter  ,PPR_dry_matter,PPF_arbitrary_1decimals)
,p_long_term_org_N_volatilization_loss(long_term_org_N_volatilization_loss_percent,PP_long_term_org_N_volatilization_loss,PPR_long_term_org_N_volatilization_loss,PPF_arbitrary_3decimals)
/*130406
,p_total_solids(total_solids_kg_ha,PP_total_solids,PPN_total_solids)
*/
{}
//_2011-01-XX___________________________________________________________________
void Organic_nitrogen_operation_abstract::setup_parameters(CORN::Data_record &record,bool for_write)
{  Organic_nitrogen_operation_abstract_class::setup_parameters(record, for_write);
   record.expect_parameter(p_org_N);
   record.expect_parameter(p_NH3_N);
   record.expect_parameter(p_dry_matter);
   record.expect_parameter(p_long_term_org_N_volatilization_loss);       //020525x

   //130406 eventually need to implement parameter properties for these
   record.expect_float32("total_solids",total_solids_kg_ha);
   record.expect_float32("water_depth",water_depth_mm);                        //110816
   record.expect_float32("water_volume",water_volume_m3);                      //110816
}
//_1998-12-28___________________________________________________________________
void Organic_nitrogen_operation_abstract::log(std::ostream &log_file) const
{  Organic_nitrogen_operation_abstract_class::log(log_file);
   std::string buffer;                                                           //030123
   log_file << p_org_N.log(buffer) << std::endl;
   log_file << p_NH3_N.log(buffer) << std::endl;                                 //030123
   log_file << p_dry_matter.log(buffer) << std::endl;                            //021105
   log_file << p_long_term_org_N_volatilization_loss.log(buffer) << std::endl;   //030123
};
//_2011-01-XX___________________________________________________________________
Parameter_properties_literal PP_NO3_N= {"NO3_N","NO3_N",NotYetSubsection,TL_Amount_N_form_of_nitrate,"","HTTP:\\descriptionURL",0 /*120710 UC_kg_ha*/};
Parameter_range PPR_NO3_N={0.0,1000.0, 0.0,1000.0 };
Parameter_properties_literal PP_NH4_N= {"NH4_N","NH4_N",NotYetSubsection,TL_Amount_N_form_of_ammonium,"","HTTP:\\descriptionURL",0 /*120710 UC_kg_ha*/};
Parameter_range PPR_NH4_N={0.0,1000.0, 0.0,1000.0 };

// The units have been disabled because they can be either kg/ha for fixed inorganic N application or % for split auto N  120710

Parameter_properties_literal PP_NH4_volatilization = {LABEL_NH4_volatilization,LABEL_NH4_volatilization,NotYetSubsection,TL_Volatilization_loss,TL_CropSyst_will_calculate,"HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_NH4_volatilization={0.0, 100.0, 0.0, 100.0 };

Parameter_properties_literal PP_N_soil_critical= {"N_soil_critical","N_crit",NotYetSubsection,"Soil critical N","","",UC_kg_ha};
Parameter_range PPR_N_soil_critical={0.0,100.0, 0.0,1000.0 };
//______________________________________________________________________________
Inorganic_nitrogen_operation::Inorganic_nitrogen_operation()
:Inorganic_nitrogen_operation_class()
,p_NO3_N                 (NO3_N          ,PP_NO3_N,PPR_NO3_N,PPF_arbitrary_3decimals)
,p_NH4_N                 (NH4_N          ,PP_NH4_N,PPR_NH4_N,PPF_arbitrary_3decimals)
,p_NH4_volatilization    (NH4_volatilization,PP_NH4_volatilization,PPR_NH4_volatilization ,PPF_arbitrary_3decimals)
,p_N_soil_critical       (condition.N_soil_critical,PP_N_soil_critical,PPR_N_soil_critical          ,PPF_arbitrary_2decimals) //170705
,p_sampling_depth        (condition.sampling_depth ,PP_soil_N_sampling_depth ,PPR_soil_N_sampling_depth    ,PPF_arbitrary_2decimals) //170705
{}
//______________________________________________________________________________
void Inorganic_nitrogen_operation::setup_parameters(Data_record &data_rec,bool for_write)
{  Inorganic_nitrogen_operation_class::setup_parameters(data_rec, for_write);
   data_rec.expect_parameter(p_NO3_N);
   data_rec.expect_parameter(p_NH4_N);
   data_rec.expect_parameter(p_NH4_volatilization);                              //990216X

   data_rec.expect_parameter(p_N_soil_critical);                                 //170705
   data_rec.expect_parameter(p_sampling_depth);                                  //170705
};
//_1998-10-07___________________________________________________________________
void Inorganic_nitrogen_operation::log(std::ostream &log_file) const
{  Inorganic_nitrogen_operation_class::log(log_file);
   std::string buffer;
   log_file << p_NO3_N.log(buffer);
   log_file << p_NH4_N.log(buffer);
   log_file << p_NH4_volatilization.log(buffer);
};
//______________________________________________________________________________
Parameter_properties_literal PP_min_LAI_required = {LABEL_min_LAI,LABEL_min_LAI,NotYetSubsection,TL_Minimum_LAI_required_for_clipping,"","HTTP:\\descriptionURL",U_units_not_specified,TU_m2_m2};
Parameter_range PPR_min_LAI_required={0.0,6.0,0.0,30.0 }; //PPF_arbitrary_2decimals
Parameter_properties_literal PP_min_biomass_required = {LABEL_min_biomass,LABEL_min_biomass,NotYetSubsection,"Minimum biomass required for clipping","","HTTP:\\descriptionURL",UC_kg_ha/*,TU_kg_ha*/};
Parameter_range PPR_min_biomass_required={0.0,30000.0,0.0,100000.0 }; //PPF_arbitrary_2decimals
Parameter_properties_literal PP_reserve_biomass = {"reserve_biomass","reserve_biomass",NotYetSubsection,"Reserve biomass" ,"unavailable for clipping","HTTP:\\descriptionURL",UC_kg_ha/*,TU_kg_ha*/};
Parameter_range PPR_reserve_biomass={0.0,10000.0,0.0,100000.0 };//PPF_arbitrary_2decimals
Parameter_properties_literal PP_grazing_percent_N_as_OM = {LABEL_percent_N_as_OM,LABEL_percent_N_as_OM,NotYetSubsection,"Percent of manure nitrogen as organic matter","Hint","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_grazing_percent_N_as_OM={0,100,0,100 };    //PPF_arbitrary_3decimals
Parameter_properties_literal PP_grazing_percent_N_as_NH3 = {LABEL_percent_N_as_NH3,LABEL_percent_N_as_NH3,NotYetSubsection,"Percent of manure nitrogen as ammonia (NH3)","Hint","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_grazing_percent_N_as_NH3={0,100,0,100 };  //PPF_arbitrary_3decimals
Parameter_properties_literal PP_remove_amount = {"remove_amount","remove_amount",NotYetSubsection,"Fixed amount of biomass to remove","Hint","HTTP:\\descriptionURL",UC_kg_ha};
Parameter_range PPR_remove_amount={0.0,10000.0,0.0,1000000.0 }; //PPF_arbitrary_2decimals
Parameter_properties_literal PP_min_retain_GAI = {"min_retain_GAI" ,"min_retain_GAI" ,NotYetSubsection,"Minimum GAI to be retained","Hint","HTTP:\\descriptionURL",U_units_not_specified,TU_m2_m2};
Parameter_range PPR_min_retain_GAI={0.01,  30.0,0.0, 40.0 };  //PPF_arbitrary_2decimals
Parameter_properties_literal PP_remove_for_use = {"use","use",NotYetSubsection,"Removed and designated for beneficial use (clipped fodder, silage, etc.)","portion of above ground biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remove_for_use={0,100,0,100 };            //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remove_for_grazing = {"graze","graze",NotYetSubsection,"Removed for grazing or other animal consumption","portion of above ground biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remove_for_grazing={0,100,0,100 };     //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remove_for_disposal = {"dispose","dispose",NotYetSubsection,"Removed from the field and disposed (unused)","portion of above ground biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remove_for_disposal={0,100,0,100 }; //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remain_as_residue = {"residue","residue",NotYetSubsection,"Remains in the field laying as surface residue","portion of above ground biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remain_as_residue={0,100,0,100};        //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remain_standing_live = {"live" ,"live" ,NotYetSubsection,"Remains as live standing plant tissue ","portion of above ground biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remain_standing_live={0,100,0,100 };  //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remain_standing_dead = {"dead","dead",NotYetSubsection,"Remains in the field as dead standing stubble/residue","portion of above ground biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remain_standing_dead={0,100,0,100 };  //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remain_roots_as_dead_residue = {"root_dead" ,"root_dead" ,NotYetSubsection,"Remains as dead root residue","portion of subsurface biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remain_roots_as_dead_residue={0,100,0,100};   //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remove_roots_as_loss = {"root_loss" ,"root_loss" ,NotYetSubsection,"Removed as loss","portion of subsurface biomass","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remove_roots_as_loss={0,100,0,100};   //PPF_arbitrary_0decimals
Parameter_properties_literal PP_remain_roots_live = {"root_live","root_live",NotYetSubsection,"Remains as live roots","portion of subsurface biomass (usually 0.0)","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_remain_roots_live={0,100,0,100 };    //PPF_arbitrary_0decimals
Parameter_properties_literal PP_biomass_returned_as_manure = {"return_as_manure","return_as_manure",NotYetSubsection,"Percent of grazed biomass returned to field as manure","portion of grazing manure production","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_biomass_returned_as_manure={0,100,0,100 }; //PPF_arbitrary_0decimals
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
Harvest_or_clipping_operation::Harvest_or_clipping_operation() // section setup constructor
: Harvest_or_clipping_operation_class() //: CropSyst_field_operation_VX    (CS_OP_MGMT_HARVEST_OR_CLIPPING)
, p_min_LAI_required                      (min_LAI_required                                  ,PP_min_LAI_required             ,PPR_min_LAI_required         ,PPF_arbitrary_2decimals)  //020314_
, p_min_biomass_required_kg_ha            (min_biomass_required_kg_ha                        ,PP_min_biomass_required         ,PPR_min_biomass_required     ,PPF_arbitrary_2decimals)  //980826p
, p_reserve_biomass_kg_ha                 (reserve_biomass_kg_ha                             ,PP_reserve_biomass              ,PPR_reserve_biomass          ,PPF_arbitrary_2decimals)  //040807_
, p_grazing_percent_N_as_OM               (grazing_percent_N_as_OM                           ,PP_grazing_percent_N_as_OM      ,PPR_grazing_percent_N_as_OM  ,PPF_arbitrary_3decimals)  //040126x
, p_grazing_percent_N_as_NH3              (grazing_percent_N_as_NH3                          ,PP_grazing_percent_N_as_NH3     ,PPR_grazing_percent_N_as_NH3 ,PPF_arbitrary_3decimals)  //040126x
, p_remove_amount_kg_ha                   (remove_amount_kg_ha                               ,PP_remove_amount                ,PPR_remove_amount            ,PPF_arbitrary_2decimals)  //050822_
, p_min_retain_GAI                        (min_retain_GAI                                    ,PP_min_retain_GAI               ,PPR_min_retain_GAI           ,PPF_arbitrary_2decimals)  //051103_
, p_remove_for_use_percent                (biomass_fate_percents.remove_for_use              ,PP_remove_for_use               ,PPR_remove_for_use           ,PPF_arbitrary_0decimals)                  //050822_
, p_remove_for_grazing_percent            (biomass_fate_percents.remove_for_grazing          ,PP_remove_for_grazing           ,PPR_remove_for_grazing       ,PPF_arbitrary_0decimals)                      //050822_
, p_remove_for_disposal_percent           (biomass_fate_percents.remove_for_disposal         ,PP_remove_for_disposal          ,PPR_remove_for_disposal      ,PPF_arbitrary_0decimals)                    //050822_
, p_remain_as_residue_percent             (biomass_fate_percents.remain_as_residue           ,PP_remain_as_residue            ,PPR_remain_as_residue        ,PPF_arbitrary_0decimals)                        //050822_
, p_remain_standing_live_percent          (biomass_fate_percents.remain_as_live              ,PP_remain_standing_live         ,PPR_remain_standing_live     ,PPF_arbitrary_0decimals)                  //050822_
, p_remain_standing_dead_percent          (biomass_fate_percents.remain_as_dead              ,PP_remain_standing_dead         ,PPR_remain_standing_dead     ,PPF_arbitrary_0decimals)                  //050822_
, p_remain_roots_as_dead_residue_percent  (biomass_fate_percents.remove_roots_to_dead_residue,PP_remain_roots_as_dead_residue ,PPR_remain_roots_as_dead_residue,PPF_arbitrary_0decimals)  //050822_
, p_remove_roots_as_loss_percent          (biomass_fate_percents.remove_roots_as_loss        ,PP_remove_roots_as_loss         ,PPR_remove_roots_as_loss     ,PPF_arbitrary_0decimals)                  //050822_
, p_remain_roots_live_percent             (biomass_fate_percents.remain_roots_live           ,PP_remain_roots_live            ,PPR_remain_roots_live        ,PPF_arbitrary_0decimals)                        //050822_
, p_biomass_returned_as_manure            (biomass_fate_percents.return_as_manure            ,PP_biomass_returned_as_manure   ,PPR_biomass_returned_as_manure,PPF_arbitrary_0decimals)      //050822_
{}
//_2011-01-15___________________________________________________________________
#ifdef CHECK_OBSOLETE
Harvest_or_clipping_operation::Harvest_or_clipping_operation(const Harvest_or_clipping_operation_class &to_be_copied); // <- This may be obsolete
: CropSyst_field_operation_VX    (CS_OP_MGMT_HARVEST_OR_CLIPPING)
{}
#endif
//_2011-01-15___________________________________________________________________
void Harvest_or_clipping_operation::setup_parameters(CORN::Data_record &data_rec,bool for_write)
{  Harvest_or_clipping_operation_class::setup_parameters(data_rec,for_write);
   data_rec.expect_parameter(p_min_LAI_required);
   data_rec.expect_parameter(p_min_biomass_required_kg_ha);
   data_rec.expect_parameter(p_reserve_biomass_kg_ha);
   data_rec.expect_parameter(p_grazing_percent_N_as_OM);
   data_rec.expect_parameter(p_grazing_percent_N_as_NH3);
   data_rec.expect_parameter(p_remove_amount_kg_ha);
   data_rec.expect_parameter(p_min_retain_GAI);
   data_rec.expect_parameter(p_remove_for_use_percent);
   data_rec.expect_parameter(p_remove_for_grazing_percent);
   data_rec.expect_parameter(p_biomass_returned_as_manure);
   data_rec.expect_parameter(p_remove_for_disposal_percent);
   data_rec.expect_parameter(p_remain_as_residue_percent);
   data_rec.expect_parameter(p_remain_standing_live_percent);
   data_rec.expect_parameter(p_remain_standing_dead_percent);
   data_rec.expect_parameter(p_remain_roots_as_dead_residue_percent);
   data_rec.expect_parameter(p_remove_roots_as_loss_percent);
   data_rec.expect_parameter(p_remain_roots_live_percent);
}
//_2011-01-XX___________________________________________________________________
Parameter_properties_literal PP_LAI_forces_clipping                     = {LABEL_max_LAI           ,LABEL_max_LAI          ,NotYetSubsection,"Maximum LAI that forces clipping","","HTTP:\\descriptionURL",UC_m2_m2};
Parameter_properties_literal PP_biomass_forces_clipping                 = {LABEL_max_biomass       ,LABEL_max_biomass      ,NotYetSubsection,TL_Maximum_biomass_that_forces_clipping,"","HTTP:\\descriptionURL",UC_kg_ha};
Parameter_properties_literal PP_flowering_forces_clipping               = {LABEL_after_flowering   ,LABEL_after_flowering  ,NotYetSubsection,"Number of days after flowering forces clipping","","HTTP:\\descriptionURL",UT_day,"Days"};
Parameter_properties_literal PP_adjust_relative_growth_rate_for_clipping= {LABEL_adj_rel_growth    ,LABEL_adj_rel_growth   ,NotYetSubsection,TL_Clipping_relative_growth_rate_adjustment,"","HTTP:\\descriptionURL",U_units_not_specified,TU_0_2};

Parameter_range PPR_LAI_forces_clipping       ={ 2.0,10.0, 0.0,15.0 };           //PPF_arbitrary_2decimals
Parameter_range PPR_biomass_forces_clipping   ={2000.0,6000.0,0.0,100000.0 };    //PPF_arbitrary_2decimals
Parameter_range PPR_flowering_forces_clipping ={0,365,0,366  };                     //PPF_arbitrary_0decimals
Parameter_range PPR_adjust_relative_growth_rate_for_clipping={0.5,1.5,0.0,2.0 }; //PPF_arbitrary_2decimals

Auto_clip_biomass_mode::Auto_clip_biomass_mode()
: Auto_clip_biomass_mode_class()
, p_LAI_forces_clipping                      (LAI_forces_clipping       ,PP_LAI_forces_clipping                      ,PPR_LAI_forces_clipping,PPF_arbitrary_2decimals)//5.0
, p_biomass_forces_clipping                  (biomass_forces_clipping   ,PP_biomass_forces_clipping                  ,PPR_biomass_forces_clipping,PPF_arbitrary_2decimals)//4000.0
, p_flowering_forces_clipping                (flowering_forces_clipping ,PP_flowering_forces_clipping                ,PPR_flowering_forces_clipping,PPF_arbitrary_0decimals)//0
, p_adjust_relative_growth_rate_for_clipping (adj_relative_growth_rate  ,PP_adjust_relative_growth_rate_for_clipping ,PPR_adjust_relative_growth_rate_for_clipping,PPF_arbitrary_2decimals)//1.0
{}
//_2001-10-27___________________________________________________________________
Auto_clip_biomass_mode::Auto_clip_biomass_mode
(const Auto_clip_biomass_mode& to_be_copied)
: Auto_clip_biomass_mode_class(to_be_copied)
, p_LAI_forces_clipping                      (LAI_forces_clipping       ,PP_LAI_forces_clipping                      ,PPR_LAI_forces_clipping,PPF_arbitrary_2decimals)//5.0
, p_biomass_forces_clipping                  (biomass_forces_clipping   ,PP_biomass_forces_clipping                  ,PPR_biomass_forces_clipping,PPF_arbitrary_2decimals)//4000.0
, p_flowering_forces_clipping                (flowering_forces_clipping ,PP_flowering_forces_clipping                ,PPR_flowering_forces_clipping,PPF_arbitrary_0decimals)//0
, p_adjust_relative_growth_rate_for_clipping (adj_relative_growth_rate  ,PP_adjust_relative_growth_rate_for_clipping ,PPR_adjust_relative_growth_rate_for_clipping,PPF_arbitrary_2decimals)//1.0
//*040914p*/ , p_adjust_relative_growth_rate_for_clipping (adj_relative_growth_rate  ,U_units_not_specified     ,LABEL_adj_rel_growth /*LABEL_adjust_relative_growth_rate_for_clipping*/,2,NO_adj_relative_growth_rate,0.5,1.5,0.0,2.0,TU_0_2,TL_Clipping_relative_growth_rate_adjustment)
//*040830_*/ , p_LAI_forces_clipping                      (LAI_forces_clipping       ,UC_kg_ha                  ,LABEL_max_LAI             ,2,5.0, 2.0,10.0, 0.0,15.0,TU_m2_m2,"Maximum LAI that forces clipping")
//*970522p*/ , p_biomass_forces_clipping                  (biomass_forces_clipping   ,UC_kg_ha                  ,LABEL_max_biomass /*LABEL_biomass_forces_clipping_old  */  ,2,4000.0,2000.0,6000.0,0.0,100000.0,TU_kg_ha,TL_Maximum_biomass_that_forces_clipping)
//*040830_*/ , p_flowering_forces_clipping                (flowering_forces_clipping ,                           LABEL_after_flowering              ,NO_flowering_forces_clipping,0,365,0,366,"Days","Number of days after flowering forces clipping")
{}
//_2002-03-14___________________________________________________________________
void Auto_clip_biomass_mode::setup_parameters(Data_record &data_rec,bool for_write)
{  Auto_clip_biomass_mode_class::setup_parameters(data_rec, for_write);
   data_rec.expect_parameter(p_adjust_relative_growth_rate_for_clipping);
   data_rec.expect_parameter(p_LAI_forces_clipping);
   data_rec.expect_parameter(p_biomass_forces_clipping);
   data_rec.expect_parameter(p_flowering_forces_clipping);
}
//_2002-03-14___________________________________________________________________
void Auto_clip_biomass_mode::log(std::ostream &log_file) const
{  Auto_clip_biomass_mode_class::log(log_file);
   std::string buffer;                                                           //030123
   log_file << p_adjust_relative_growth_rate_for_clipping.log(buffer);           //031023
   log_file << p_biomass_forces_clipping.log(buffer);                            //031023
   log_file << p_flowering_forces_clipping.log(buffer);                          //040830
}
//_2002-08-10___________________________________________________________________
Parameter_properties_literal PP_amount = {LABEL_amount,LABEL_amount,NotYetSubsection,TL_Total_irrigation,"","HTTP:\\descriptionURL",UC_mm};
Parameter_range PPR_amount={0.0,1000.0, 0.0,1000.0 };                //PPF_arbitrary_3decimals
Parameter_properties_literal PP_net_irrigation_mult = {LABEL_net_irrigation_mult,"net_irr_mult",NotYetSubsection,TL_Net_irrigation_multiplier,"","HTTP:\\descriptionURL",U_units_not_specified};
Parameter_range PPR_net_irrigation_mult={0.0,2.0, 0.0,10.0 };        //PPF_arbitrary_2decimals
Parameter_properties_literal PP_refill_point = {LABEL_refill_point,LABEL_refill_point,NotYetSubsection,"Refill point","","HTTP:\\descriptionURL",UC_decimal_percent};
//130313 now use PPN_fraction_3decimals Parameter_range PPR_refill_point={0.0,1.0,0.0,2.0 }; //PPF_arbitrary_2decimals
Parameter_properties_literal PP_NO3_N_concentration = {"NO3_N_concentration","NO3_N_conc",NotYetSubsection,"Nitrate NO3 N concentration",TL_Irrigation,"HTTP:\\descriptionURL",UC_kg_m3};
Parameter_range PPR_NO3_N_concentration={0.0,99999.9,0.0,99999.9 };     //PPF_arbitrary_3decimals
Parameter_properties_literal PP_NH4_N_concentration = {"NH4_N_concentration","NH4_N_conc",NotYetSubsection,"Ammonium NH4 N concentration",TL_Irrigation,"HTTP:\\descriptionURL",UC_kg_m3};
Parameter_range PPR_NH4_N_concentration={0.0,99999.9,0.0,99999.9 }; //PPF_arbitrary_3decimals
Parameter_properties_literal PP_salinity = {LABEL_salinity,LABEL_salinity,NotYetSubsection,TL_Salinity,TL_Irrigation,"HTTP:\\descriptionURL",UC_dS_m};
Parameter_range PPR_salinity={0.0,20.0,0.0,50.0};         //PPF_arbitrary_3decimals
Parameter_properties_literal PP_ECw_to_TDS                           = {"ECw_to_TDS"                  ,"ECw_to_TDS"  ,NotYetSubsection,"ECw (dS/m) -> TDS (kg/m�) conversion factor","Eletrical conductivity in water (dS/m) to total dissolved solids (l/g or kg/m�). Usually about 0.64.","HTTP:\\descriptionURL",UC_factor};
//130313 now use PPN_fraction_3decimals Parameter_range PPR_ECw_to_TDS                   ={0.0,1.0,0.0, 2.0 };//PPF_arbitrary_3decimals
Parameter_properties_literal PP_max_allowable_depletion              = {LABEL_max_allowable_depletion ,"max_depl"    ,NotYetSubsection,TL_Maximum_allowable_depletion,"","HTTP:\\descriptionURL",U_units_not_specified};
//130313 now use PPN_fraction_3decimals Parameter_range PPR_max_allowable_depletion      ={ 0.0,1.0, 0.0,1.0 };//PPF_arbitrary_3decimals
Parameter_properties_literal PP_depletion_observe_depth              = {LABEL_depletion_observe_depth ,"depl_obs_depth",NotYetSubsection,TL_Depletion_observation_depth,"","HTTP:\\descriptionURL",UC_meter};
Parameter_range PPR_depletion_observe_depth={0.0,2.0, 0.0,4.0 };    //PPF_arbitrary_2decimals
Parameter_properties_literal PP_depletion_observe_root_zone_fract    = {"depletion_observe_root_zone_fract","delp_obs_rz_fract",NotYetSubsection,"Fraction of current root depth","","HTTP:\\descriptionURL",UC_fraction,"TU_0_2"};
Parameter_range PPR_depletion_observe_root_zone_fract={0.0,2.0,0.0,4.0};//PPF_arbitrary_2decimals
Parameter_properties_literal PP_min_application                      = {"min_application"             ,"min_appl"    ,NotYetSubsection,"Irrigation system minimum application capacity","","HTTP:\\descriptionURL",UC_mm};
Parameter_range PPR_min_application              = {0.0,200.0,0.0,1000.0};  //PPF_arbitrary_2decimals
Parameter_properties_literal PP_max_application                      = {LABEL_max_application         ,"max_appl"    ,NotYetSubsection,"Irrigation system maximum application capacity","","HTTP:\\descriptionURL",UC_mm};
Parameter_range PPR_max_application              = {0.0,200.0,0.0,1000.0};  //PPF_arbitrary_2decimals
Parameter_properties_literal PP_leaf_water_potential                 = {"leaf_water_potential"        ,"LWP"         ,NotYetSubsection,"Leaf water potential","Irrigation will occur when the leaf water potential becomes more negative than this value.","HTTP:\\descriptionURL",UC_J_kg/*",-J/kg"*/};
Parameter_range PPR_leaf_water_potential         = {-1000.0,-5000.0,0.0,-10000.0 };  //PPF_arbitrary_1decimals
Parameter_properties_literal         PP_surface_evaporation_area     = {"surface_evaporation_area","surf_evap"   ,NotYetSubsection,"Soil surface subject to soil evaporation","fraction of soil surface wetted and evaporatable","HTTP:\\descriptionURL",UC_fraction}; //130321
Parameter_properties_literal         PP_profile_volume               = {"profile_volume"          ,"prof_vol"    ,NotYetSubsection,"Soil profile volume/area"                ,"fraction of the subsurface that is wetted (effective root zone)","HTTP:\\descriptionURL",UC_fraction}; //130321

//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
/*170710
#define IRRIGATION_CONSTRUCTOR_INITIALIZATION                                  \
,p_amount                  (amount_mm                                      ,PP_amount                             ,PPR_amount                            ,PPF_arbitrary_3decimals)                           \
,p_net_irrigation_mult     (net_irrigation_mult                            ,PP_net_irrigation_mult                ,PPR_net_irrigation_mult               ,PPF_arbitrary_2decimals)              \
,p_refill_point            (refill_point                                   ,PP_refill_point                       ,PPR_fraction                          ,PPF_arbitrary_3decimals)               \
,p_NO3_N_concentration     (NO3_N_concentration                            ,PP_NO3_N_concentration                ,PPR_NO3_N_concentration               ,PPF_arbitrary_3decimals)              \
,p_NH4_N_concentration     (NH4_N_concentration                            ,PP_NH4_N_concentration                ,PPR_NH4_N_concentration               ,PPF_arbitrary_3decimals)              \
,p_salinity                (salinity                                       ,PP_salinity                           ,PPR_salinity                          ,PPF_arbitrary_3decimals)                         \
,p_ECw_to_TDS              (ECw_to_TDS                                     ,PP_ECw_to_TDS                         ,PPR_fraction                          ,PPF_arbitrary_3decimals)               \
,p_max_allowable_depletion (max_allowable_depletion                        ,PP_max_allowable_depletion            ,PPR_fraction                          ,PPF_arbitrary_3decimals)               \
,p_depletion_observe_depth (depletion_observe_depth_m                      ,PP_depletion_observe_depth            ,PPR_depletion_observe_depth           ,PPF_arbitrary_2decimals)          \
,p_depletion_observe_root_zone_fract(depletion_observe_root_zone_fract     ,PP_depletion_observe_root_zone_fract  ,PPR_depletion_observe_root_zone_fract ,PPF_arbitrary_2decimals)\
,p_min_application         (min_application_mm                             ,PP_min_application                    ,PPR_min_application                   ,PPF_arbitrary_2decimals)                  \
,p_max_application         (max_application_mm                             ,PP_max_application                    ,PPR_max_application                   ,PPF_arbitrary_2decimals)                  \
,p_leaf_water_potential    (leaf_water_potential                           ,PP_leaf_water_potential               ,PPR_leaf_water_potential              ,PPF_arbitrary_1decimals)             \
,p_surface_evaporation_area(soil_wetting.surface_evaporation_area_fraction ,PP_surface_evaporation_area           ,PPR_fraction                          ,PPF_arbitrary_3decimals)               \
,p_profile_volume          (soil_wetting.profile_volume_fraction           ,PP_profile_volume                     ,PPR_fraction                          ,PPF_arbitrary_3decimals)

//,p_irrigation_type         (irrigation_type                                ,PP_irrigation_type                    ,PPR_fraction                          ,PPF_arbitrary_3decimals)
*/

Irrigation_operation_parameters_numeric::Irrigation_operation_parameters_numeric
(Irrigation_operation_struct &op)
:p_amount                  (op.amount_mm                                      ,PP_amount                             ,PPR_amount                            ,PPF_arbitrary_3decimals)                           \
,p_net_irrigation_mult     (op.net_irrigation_mult                            ,PP_net_irrigation_mult                ,PPR_net_irrigation_mult               ,PPF_arbitrary_2decimals)
,p_refill_point            (op.refill_point                                   ,PP_refill_point                       ,PPR_fraction                          ,PPF_arbitrary_3decimals)
,p_NO3_N_concentration     (op.NO3_N_concentration                            ,PP_NO3_N_concentration                ,PPR_NO3_N_concentration               ,PPF_arbitrary_3decimals)
,p_NH4_N_concentration     (op.NH4_N_concentration                            ,PP_NH4_N_concentration                ,PPR_NH4_N_concentration               ,PPF_arbitrary_3decimals)
,p_salinity                (op.salinity                                       ,PP_salinity                           ,PPR_salinity                          ,PPF_arbitrary_3decimals)
,p_ECw_to_TDS              (op.ECw_to_TDS                                     ,PP_ECw_to_TDS                         ,PPR_fraction                          ,PPF_arbitrary_3decimals)
,p_max_allowable_depletion (op.max_allowable_depletion                        ,PP_max_allowable_depletion            ,PPR_fraction                          ,PPF_arbitrary_3decimals)
,p_depletion_observe_depth (op.depletion_observe_depth_m                      ,PP_depletion_observe_depth            ,PPR_depletion_observe_depth           ,PPF_arbitrary_2decimals)
,p_depletion_observe_root_zone_fract(op.depletion_observe_root_zone_fract     ,PP_depletion_observe_root_zone_fract  ,PPR_depletion_observe_root_zone_fract ,PPF_arbitrary_2decimals)
,p_min_application         (op.min_application_mm                             ,PP_min_application                    ,PPR_min_application                   ,PPF_arbitrary_2decimals)
,p_max_application         (op.max_application_mm                             ,PP_max_application                    ,PPR_max_application                   ,PPF_arbitrary_2decimals)
,p_leaf_water_potential    (op.leaf_water_potential                           ,PP_leaf_water_potential               ,PPR_leaf_water_potential              ,PPF_arbitrary_1decimals)
,p_surface_evaporation_area(op.soil_wetting.surface_evaporation_area_fraction ,PP_surface_evaporation_area           ,PPR_fraction                          ,PPF_arbitrary_3decimals)
,p_profile_volume          (op.soil_wetting.profile_volume_fraction           ,PP_profile_volume                     ,PPR_fraction                          ,PPF_arbitrary_3decimals)
//,p_irrigation_type         (irrigation_type                                ,PP_irrigation_type                    ,PPR_fraction                          ,PPF_arbitrary_3decimals)
{}
//_2017-07-10___________________________________________________________________
Irrigation_operation::Irrigation_operation(CropSyst_Op irrig_or_auto_irrig_code)
: Irrigation_operation_class(irrig_or_auto_irrig_code)
, parameters(*this)                                                              //170710
//170710 IRRIGATION_CONSTRUCTOR_INITIALIZATION
{  disable_when_precipitation = false;
}
//_2004-05-11___________________________________________________________________
Automatic_irrigation_mode::Automatic_irrigation_mode()
:Automatic_irrigation_mode_class()
, parameters(*this)                                                                   //170710
//170710 IRRIGATION_CONSTRUCTOR_INITIALIZATION
{};
//_2013-04-08___________________________________________________________________
void Automatic_irrigation_mode::setup_parameters(Data_record &data_rec, bool for_write)
{
#ifdef VIC_CROPSYST_VERSION
    Automatic_irrigation_mode_class::setup_parameters(data_rec, for_write);
    data_rec.expect_parameter(p_amount);
    data_rec.expect_parameter(p_net_irrigation_mult);
    data_rec.expect_parameter(p_refill_point);
    data_rec.expect_parameter(p_salinity);
    data_rec.expect_parameter(p_NO3_N_concentration);
    data_rec.expect_parameter(p_NH4_N_concentration);
    data_rec.expect_parameter(p_leaf_water_potential);
    data_rec.expect_parameter(p_max_allowable_depletion);
    data_rec.expect_parameter(p_depletion_observe_depth);
    data_rec.expect_parameter(p_depletion_observe_root_zone_fract);
    data_rec.expect_parameter(p_min_application);
    data_rec.expect_parameter(p_max_application);
    data_rec.expect_bool("disable_when_precipitation",disable_when_precipitation);//110516
    data_rec.expect_parameter(p_surface_evaporation_area);                        //130321
    data_rec.expect_parameter(p_profile_volume);                                  //130321
#endif
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
void Automatic_irrigation_mode::log(std::ostream &log_file) const
{
    //LML 140916
    //assert(false);
}
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
void Irrigation_operation::setup_parameters(Data_record &data_rec,bool for_write)
{
   Irrigation_operation_class::setup_parameters(data_rec, for_write);
   data_rec.expect_parameter(parameters.p_amount);
   data_rec.expect_parameter(parameters.p_net_irrigation_mult);
   data_rec.expect_parameter(parameters.p_refill_point);
   data_rec.expect_parameter(parameters.p_salinity);
   data_rec.expect_parameter(parameters.p_NO3_N_concentration);
   data_rec.expect_parameter(parameters.p_NH4_N_concentration);
   data_rec.expect_parameter(parameters.p_leaf_water_potential);
   data_rec.expect_parameter(parameters.p_max_allowable_depletion);
   data_rec.expect_parameter(parameters.p_depletion_observe_depth);
   data_rec.expect_parameter(parameters.p_depletion_observe_root_zone_fract);
   data_rec.expect_parameter(parameters.p_min_application);
   data_rec.expect_parameter(parameters.p_max_application);
   data_rec.expect_bool("disable_when_precipitation",disable_when_precipitation);//110516
   data_rec.expect_parameter(parameters.p_surface_evaporation_area);                        //130321
   data_rec.expect_parameter(parameters.p_profile_volume);                                  //130321
}
//_1998-10-07___________________________________________________________________
void Irrigation_operation::log(std:: ostream &log_file)                   const
{  Irrigation_operation_class::log(log_file);
   std::string buffer;
   if (amount_mm > 0.000001)
      log_file << parameters.p_amount.log(buffer);                                          //030123
   log_file << parameters.p_salinity.log(buffer);                                           //030123
   log_file << parameters.p_NO3_N_concentration.log(buffer);                                //080213
   log_file << parameters.p_NH4_N_concentration.log(buffer);                                //080213
   log_file << parameters.p_net_irrigation_mult.log(buffer);                                //030123
   log_file << parameters.p_refill_point.log(buffer);                                       //051228
}
//______________________________________________________________________________
#ifdef NYI
110326
void Automatic_irrigation_mode::log(std::ostream &log_file)                const
{  Automatic_irrigation_mode_class::log(log_file);
   char buffer[255];                                                             //030123
   { log_file << v_max_allowable_depletion.log(buffer);
     log_file << v_depletion_observe_depth.log(buffer);
   };                                                                            //041118
   log_file << v_min_application.log(buffer);
   log_file << v_max_application.log(buffer);
}
#endif
//_2002-08-10__________________________________Automatic_irrigation_mode::log__/
Parameter_properties_literal PP_target_yield_N_uptake = {LABEL_target_yield_N_uptake,LABEL_target_yield_N_uptake,NotYetSubsection,TL_Crop_N_uptake_for_target_yield,"","HTTP:\\descriptionURL",UC_kg_ha};
Parameter_range PPR_target_yield_N_uptake={0.0,99999.9,0.0,99999.9 };    //PPF_arbitrary_2decimals
Parameter_properties_literal PP_estimatied_mineralization = {"est_mineralization","est_mineral",NotYetSubsection,"Estimated mineralization","","HTTP:\\descriptionURL",UC_kg_ha};   //120710
Parameter_range PPR_estimatied_mineralization={0.0,99999.9,0.0,99999.9 };  //PPF_arbitrary_2decimals
Parameter_properties_literal PP_critical_soil_NO3_for_no_response = {LABEL_critical_soil_N_for_no_response,LABEL_critical_soil_N_for_no_response,NotYetSubsection,LABEL_critical_soil_N_for_no_response/*130406 TL_Critical_soil_NO3*/,"","HTTP:\\descriptionURL",UC_kg_ha};
Parameter_range PPR_critical_soil_NO3_for_no_response={0.0,99999.9,0.0,99999.9 }; //PPF_arbitrary_2decimals
Parameter_properties_literal PP_fertilizer_use_efficiency = {LABEL_fertilizer_use_efficiency,LABEL_fertilizer_use_efficiency,NotYetSubsection,TL_Fertilizer_use_efficiency,"","HTTP:\\descriptionURL",UC_percent};
Parameter_range PPR_fertilizer_use_efficiency={0.0,  100.0,0.0,  100.0 };  //PPF_arbitrary_1decimals

N_application_soil_observation_mode::N_application_soil_observation_mode()
: N_application_soil_observation_mode_class()
,p_target_yield_N_uptake                  (target_yield_N_uptake_kg_ha            ,PP_target_yield_N_uptake            ,PPR_target_yield_N_uptake     ,PPF_arbitrary_2decimals)
,p_estimatied_mineralization              (estimated_mineralization_kg_ha         ,PP_estimatied_mineralization        ,PPR_estimatied_mineralization ,PPF_arbitrary_2decimals) //120710
//120710 only in V4,p_critical_soil_NO3_for_no_response_kg_ha (critical_soil_NO3_for_no_response_kg_ha,PP_critical_soil_NO3_for_no_response,PPN_critical_soil_NO3_for_no_response)
,p_fertilizer_use_efficiency              (fertilizer_use_efficiency              ,PP_fertilizer_use_efficiency        ,PPR_fertilizer_use_efficiency ,PPF_arbitrary_1decimals)
,p_soil_N_sampling_depth                  (soil_N_sampling_depth                  ,PP_soil_N_sampling_depth            ,PPR_soil_N_sampling_depth     ,PPF_arbitrary_2decimals)
{}
//______________________________________________________________________________
void N_application_soil_observation_mode::setup_parameters(CORN::Data_record &data_rec,bool for_write)
{  N_application_soil_observation_mode_class::setup_parameters(data_rec,for_write);
   data_rec.expect_float32(LABEL_target_yield_N_uptake,target_yield_N_uptake_kg_ha);
//120710 only in V4   data_rec.expect_float32(LABEL_critical_soil_NO3_for_no_response,critical_soil_NO3_for_no_response_kg_ha);
   data_rec.expect_float32(LABEL_fertilizer_use_efficiency,fertilizer_use_efficiency);
//021001      NOTE THIS IS NOT YET IMPLEMENTED, currently we only allow one set of split applications (for easy V3 compatibility)
////*020617_*/    EXPECT_ENUMERATED_SECTION(LABEL_auto_NO3_application  ,auto_NO3_appl_section_VV                 ,auto_NO3_applications);
}
//_1997-07-09___________________________________________________________________
void N_application_soil_observation_mode::log(std::ostream &log_file) const
{
   N_application_soil_observation_mode_class::log(log_file);
   std::string buffer;
   log_file << p_target_yield_N_uptake.log(buffer);
   log_file << p_estimatied_mineralization.log(buffer);
//120710 only in V4   log_file << p_critical_soil_NO3_for_no_response_kg_ha.log(buffer);
   log_file << p_soil_N_sampling_depth.log(buffer);
   log_file << p_fertilizer_use_efficiency.log(buffer);
}
//_2002-03-11___________________________________________________________________
Parameter_properties_literal PP_chemical_concentration = {LABEL_concentration,LABEL_concentration,NotYetSubsection,TL_Concentration,"","HTTP:\\descriptionURL",UC_kg_m3};
Parameter_range PPR_chemical_concentration={0.0,  10.0, 0.0, 100.0 };    //PPF_arbitrary_3decimals
Chemical_operation::Chemical_operation()
:Chemical_operation_class()
,p_chemical_concentration  (chemical_concentration,PP_chemical_concentration,PPR_chemical_concentration,PPF_arbitrary_3decimals)
{}
//______________________________________________________________________________
void Chemical_operation::setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_
{  Chemical_operation_class::setup_parameters(data_rec,for_write);
   data_rec.expect_parameter(p_chemical_concentration);
}
//_2013-11-05___________________________________________________________________
DEFINE_Biomatter_application_operation
//______________________________________________________________________________
Parameter_properties_literal PP_soil_conservation_factor = {LABEL_soil_conservation_factor,"soil_cons_fact",NotYetSubsection,TL_RUSLE_soil_conservation_practice_factor,"","HTTP:\\descriptionURL",UC_factor};
Parameter_range PPR_soil_conservation_factor={ 0.0,1.0, 0.0,1.0 };   //PPF_arbitrary_3decimals
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
Management_parameters::Management_parameters()
: Management_parameters_class()
, p_soil_conservation_factor(soil_conservation_factor,PP_soil_conservation_factor,PPR_soil_conservation_factor,PPF_arbitrary_3decimals)
{}
//             Eventually automatic NO3 application mode will be fully an event period.
//_2011-01-XX___________________________________________________________________
bool Management_parameters::expect_structure(bool for_write)
{  Management_parameters_class::expect_structure(for_write);                     //120314
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_management);
   expect_parameter(p_soil_conservation_factor);                                 //180418
#ifdef NYI
if reimplement multiple auto NO3 events
   {  // Automatic NO3 applicaiton mode:
      auto_NO3_appl_mode_section_VV *auto_NO3_appl_mode_section = new
      auto_NO3_appl_mode_section_VV(LABEL_automatic_irrigation,auto_NO3_application_mode_operations);
      expect_enumerated_section(auto_NO3_appl_mode_section);
      // relinquish auto_irrigation_section  to VV file DONT DELETE IT
   }
#endif
   set_current_section("automatic_nitrogen");                                    //040712
//WARNING, need to use expect_parameter I haven't updated this yet

   /*110326 moving  don't delete need to check if I have moved this
   expect_float32(LABEL_target_yield_N_uptake,N_application_soil_observation_event->target_yield_N_uptake_kg_ha,"","");
   expect_float32(LABEL_critical_soil_NO3_for_no_response,N_application_soil_observation_event->critical_soil_NO3_for_no_response_kg_ha);
   expect_float32(LABEL_fertilizer_use_efficiency,N_application_soil_observation_event->fertilizer_use_efficiency);
   set_current_section("soil_N_sampling");                                       //040712

   //WARNING, need to use expect_parameter I haven't updated this yet

   expect_float32(LABEL_sampling_depth,N_application_soil_observation_event->soil_N_sampling_depth);
   */
   structure_defined = true;                                                     //120314
   return true;                                                                  //170706
}
//_2011-01-16___________________________________________________________________

//_2011-01-16___________________________________________________________________
nat32 Management_parameters::fertilization_nitrogen_multiply_by(float multiplier) modification_
{  nat32 count = Management_parameters_class::fertilization_nitrogen_multiply_by(multiplier);
   FOR_EACH_IN(biomatter_appl,Biomatter_application_operation,biomatter_application_operations,each_biomatter_appl)
       count += biomatter_appl->multiply_amount_by(multiplier);
   FOR_EACH_END(each_biomatter_appl);
//080829 NYI   May need to do this also for new manure application
   return count;
}
//_2011-01-16___________________________________________________________________
#ifdef NYI
040712 currently only one set of split applications
float32 N_application_soil_observation_mode::total_automatic_NO3_applications() const  //020403
{  float32 total = 0;
   FOR_EACH_IN(auto_NO3_appl,N_application_soil_observation_mode::Split_application,auto_NO3_applications,each_appl) //030709
      total += auto_NO3_appl->get_percent_of_application();
   FOR_EACH_END(each_appl);                                                      //030709
   return total;
}
#endif
//______________________________________________________________________________
}; // namespace CropSyst
#endif

