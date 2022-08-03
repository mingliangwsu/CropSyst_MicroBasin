#include "mapunit.h"
#include "corn/metrology/units_code_CU.h"
using namespace CORN;
#define DFW 8
namespace USDA_NRCS
{
//______________________________________________________________________________
//1 musym Mapunit Symbol String Yes 6
//2 muname Mapunit Name String No 175
//3 mukind Kind Choice No 254 mapunit_kind
//4 mustatus Status Choice No 254 mapunit_status
Parameter_properties_literal PP_muacres      = {"muacres"     ,"muacres"     ,"muacres"     ,"Total Acres","Hint","HTTP:\\descriptionURL",UE_acre}; Parameter_range PPR_muacres={0,9999999,0,9999999}; //, 0,10 };
Parameter_properties_literal PP_mapunitlfw_l = {"mapunitlfw_l","mapunitlfw_l","mapunitlfw_l","Linear Feature Width"  ,"Low","HTTP:\\descriptionURL",UC_meter}; Parameter_range PPR_mapunitlfw={0,9999999,0,9999999}; //, 0,10 };
Parameter_properties_literal PP_mapunitlfw_r = {"mapunitlfw_r","mapunitlfw_r","mapunitlfw_r","Linear Feature Width"  ,"Representative","HTTP:\\descriptionURL",UC_meter};
Parameter_properties_literal PP_mapunitlfw_h = {"mapunitlfw_h","mapunitlfw_h","mapunitlfw_h","Linear Feature Width"  ,"High","HTTP:\\descriptionURL",UC_meter};
Parameter_properties_literal PP_mapunitpfa_l = {"mapunitpfa_l","mapunitpfa_l","mapunitpfa_l","Point Feature Area"    ,"Low","HTTP:\\descriptionURL",UE_acre}; Parameter_range PPR_mapunitpfa={0.1,10,0.1,10}; //, 1,10 };
Parameter_properties_literal PP_mapunitpfa_r = {"mapunitpfa_r","mapunitpfa_r","mapunitpfa_r","Point Feature Area"    ,"Representative","HTTP:\\descriptionURL",UE_acre};
Parameter_properties_literal PP_mapunitpfa_h = {"mapunitpfa_h","mapunitpfa_h","mapunitpfa_h","Point Feature Area"    ,"High","HTTP:\\descriptionURL",UE_acre};
//12 farmlndcl Farm Class Choice No 254 farmland_classification
//13 muhelcl HEL Choice No 254 mapunit_hel_class
//14 muwathelcl HEL Water Choice No 254 mapunit_hel_class
//15 muwndhelcl HEL Wind Choice No 254 mapunit_hel_class
//16 interpfocus Interpretive Focus String No 30
//17 invesintens Order of Mapping Choice No 254 investigation_intensity
Parameter_properties_literal PP_iacornsr = {"iacornsr","iacornsr","iacornsr","IA CSR","Hint","HTTP:\\descriptionURL",UC_unitless}; Parameter_range PPR_iacornsr={5,100,5,100}; //, 0,10 };
//19 nhiforsoigrp NH Forest Soil Grp Choice No 254 nh_important_forest_soil_group
Parameter_properties_literal PP_nhspiagr = {"nhspiagr","nhspiagr","nhspiagr","NH SPI Agr","Hint","HTTP:\\descriptionURL",UC_unitless}; Parameter_range PPR_nhspiagr={0,100,0,100}; //, 1,10 };

//21 vtsepticsyscl VT Septic System Choice No 254 vt_septic_system_class
//22 mucertstat Map Unit Certification Status Choice No 254 mapunit_certification_status
//23 lkey Legend Key String Yes 30
//24 mukey Mapunit Key String Yes 30

//______________________________________________________________________________
Mapunit::Mapunit()
: Mapunit_struct()
, CORN::Data_record("mapunit")
//1 musym Mapunit Symbol String Yes 6
//2 muname Mapunit Name String No 175
//3 mukind Kind Choice No 254 mapunit_kind
//4 mustatus Status Choice No 254 mapunit_status
,p_muacres(muacres,PP_muacres,PPR_muacres,PPF_8_0_10)
,p_mapunitlfw_l(mapunitlfw.low   ,PP_mapunitlfw_l,PPR_mapunitlfw,PPF_8_0_10)
,p_mapunitlfw_r(mapunitlfw.repr  ,PP_mapunitlfw_r,PPR_mapunitlfw,PPF_8_0_10)
,p_mapunitlfw_h(mapunitlfw.high  ,PP_mapunitlfw_h,PPR_mapunitlfw,PPF_8_0_10)
,p_mapunitpfa_l(mapunitpfa.low   ,PP_mapunitpfa_l,PPR_mapunitpfa,PPF_8_1_10)
,p_mapunitpfa_r(mapunitpfa.repr  ,PP_mapunitpfa_r,PPR_mapunitpfa,PPF_8_1_10)
,p_mapunitpfa_h(mapunitpfa.high  ,PP_mapunitpfa_h,PPR_mapunitpfa,PPF_8_1_10)
//12 farmlndcl Farm Class Choice No 254 farmland_classification
//13 muhelcl HEL Choice No 254 mapunit_hel_class
//14 muwathelcl HEL Water Choice No 254 mapunit_hel_class
//15 muwndhelcl HEL Wind Choice No 254 mapunit_hel_class
//16 interpfocus Interpretive Focus String No 30
//17 invesintens Order of Mapping Choice No 254 investigation_intensity
,p_iacornsr(iacornsr,PP_iacornsr,PPR_iacornsr,PPF_8_0_10)
//19 nhiforsoigrp NH Forest Soil Grp Choice No 254 nh_important_forest_soil_group
,p_nhspiagr(nhspiagr,PP_nhspiagr,PPR_nhspiagr,PPF_8_1_10)
//21 vtsepticsyscl VT Septic System Choice No 254 vt_septic_system_class
//22 mucertstat Map Unit Certification Status Choice No 254 mapunit_certification_status
//23 lkey Legend Key String Yes 30
//24 mukey Mapunit Key String Yes 30
{}
//______________________________________________________________________________
bool Mapunit::expect_structure(bool for_write)
{
   bool expected = CORN::Data_record::expect_structure(for_write);
   expect_string("musym"   ,musym   ,6);   //Mapunit Symbol String Yes
   expect_string("muname"  ,muname  ,175); // Mapunit Name String No
   expect_string("mukind"  ,mukind  ,254);// Kind Choice No
   expect_string("mustatus",mustatus,254); //Status Choice No  mapunit_status

   expect_parameter(p_muacres); //Total Acres Integer No 0 acres
   expect_parameter(p_mapunitlfw_l); // Linear Feature Width - Low Value Integer No meters
   expect_parameter(p_mapunitlfw_r); // Linear Feature Width - Representative Value Integer No meters
   expect_parameter(p_mapunitlfw_h);//8  Linear Feature Width - High Value Integer No meters
   expect_parameter(p_mapunitpfa_l);//9  Point Feature Area - Low Value Float No 1 0.1 10 acres
   expect_parameter(p_mapunitpfa_r);//10  Point Feature Area - Representative Value Float No 1 0.1 10 acres
   expect_parameter(p_mapunitpfa_h);//11  Point Feature Area - High Value Float No 1 0.1 10 acres
   expect_string("farmlndcl"     ,farmlndcl,254); //Farm Class Choice No  farmland_classification
   expect_string("muhelcl"       ,muhelcl,254);// HEL Choice No  mapunit_hel_class
   expect_string("muwathelcl"    ,muwathelcl,254); //HEL Water Choice No  mapunit_hel_class
   expect_string("muwndhelcl"    ,muwndhelcl,254);// HEL Wind Choice No  mapunit_hel_class
   expect_string("interpfocus"   ,interpfocus,30); //Interpretive Focus String No
   expect_string("invesintens"   ,invesintens,254);// Order of Mapping Choice No  investigation_intensity
   expect_parameter(p_iacornsr);//18  IA CSR Integer No 5 100
   expect_string("nhiforsoigrp"  ,nhiforsoigrp,254); //NH Forest Soil Grp Choice No  nh_important_forest_soil_group
   expect_parameter(p_nhspiagr);// NH SPI Agr Float No 1 0 100
   expect_string("vtsepticsyscl" ,vtsepticsyscl,254); //VT Septic System   vt_septic_system_class
   expect_string("mucertstat"    ,mucertstat,254);  //Map Unit Certification Status  mapunit_certification_status
   expect_string("lkey"          ,lkey,30); //Legend Key
   expect_string("mukey"         ,mukey,30);// Mapunit Key
   structure_defined = true;                                                     //120314   
   return expected;
}
//______________________________________________________________________________
} // namespace USDA_NRCS
/*
mapunit.txt
"s66"|"Leesburg-Gorgas-Allen (s66)"|"Association"||8285||||||||||||"Order 5"||||||"15970"|"657944"
"s67"|"Sullivan-State-Ketona-Decatur-Bodine (s67)"|"Association"||7619||||||||||||"Order 5"||||||"15970"|"657945"
"s68"|"Wynnville-Townley-Sipsey (s68)"|"Association"||14201||||||||||||"Order 5"||||||"15970"|"657946"
"s69"|"Townley-Stemley-Minvale-Bodine (s69)"|"Association"||6126||||||||||||"Order 5"||||||"15970"|"657947"
*/

