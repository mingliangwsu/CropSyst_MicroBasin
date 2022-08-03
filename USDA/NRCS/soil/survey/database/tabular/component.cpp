
#pragma hdrstop
#include "component.h"
//______________________________________________________________________________
using namespace CORN;
//140201 #define DFW 8
namespace USDA_NRCS
{
//______________________________________________________________________________
Parameter_properties_literal PP_comppct_l          = {"comppct_l"    ,"comppct_l"   ,"xxxx","Comp %","Low","HTTP:\\descriptionURL",UC_percent};Parameter_range PPR_comppct={0,100,0,100}; // , 0,10 };
Parameter_properties_literal PP_comppct_r          = {"comppct_r"    ,"comppct_r"   ,"xxxx","Comp %","Representative","HTTP:\\descriptionURL",UC_percent};
Parameter_properties_literal PP_comppct_h          = {"comppct_h"    ,"comppct_h"   ,"xxxx","Comp %","High","HTTP:\\descriptionURL",UC_percent};
Parameter_properties_literal PP_compname           = {"compname"     ,"compname"    ,"xxxx", "Component Name","Hint","HTTP:\\descriptionURL",UC_unitless};  // width 60
Parameter_properties_literal PP_compkind           = {"compkind"     ,"compkind"    ,"xxxx", "Kind","Hint","HTTP:\\descriptionURL",UC_unitless}; //width 254
Parameter_properties_literal PP_majcompflag        = {"majcompflag"  ,"majcompflag" ,"xxxx", "Major Component","Hint","HTTP:\\descriptionURL",UC_unitless}; //width 3
Parameter_properties_literal PP_otherph            = {"otherph","otherph","xxxx", "SIR phase","Hint","HTTP:\\descriptionURL",UC_unitless}; //width 40
Parameter_properties_literal PP_localphase         = {"localphase","localphase","xxxx", "Local Phase","Hint","HTTP:\\descriptionURL",UC_unitless};
Parameter_properties_literal PP_slope_l            = {"slope_l","slope_l","xxxx"," Slope Gradient","Low","HTTP:\\descriptionURL",UC_gradian_angle}; Parameter_range PPR_slope={0,100,0,400}; // , 1,10 };
Parameter_properties_literal PP_slope_r            = {"slope_r","slope_r","xxxx"," Slope Gradient","Representative","HTTP:\\descriptionURL",UC_gradian_angle};
Parameter_properties_literal PP_slope_h            = {"slope_h","slope_h","xxxx"," Slope Gradient","High","HTTP:\\descriptionURL",UC_gradian_angle};
Parameter_properties_literal PP_slopelenusle_l = {"slopelenusle_l","slopelenusle_l","xxxx","Slope Length USLE","Low","HTTP:\\descriptionURL",UC_meter}; Parameter_range PPR_slopelenusle={0,4000,0,4000}; // , 0,10 };
Parameter_properties_literal PP_slopelenusle_r = {"slopelenusle_r","slopelenusle_r","xxxx","Slope Length USLE","Representative","HTTP:\\descriptionURL",UC_meter};
Parameter_properties_literal PP_slopelenusle_h = {"slopelenusle_h","slopelenusle_h","xxxx","Slope Length USLE","High","HTTP:\\descriptionURL",UC_meter};
Parameter_properties_literal PP_runoff = {"runoff","runoff","xxxx", "Runoff Class","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_tfact = {"tfact","tfact","xxxx","T","tons per acre per year","HTTP:\\descriptionURL",UE_ton_per_acre/*per year*/};          Parameter_range PPR_tfact={1,5,1,5}; // , 1,10 };
Parameter_properties_literal PP_wei = {"wei","wei","xxxx", "Wind Erodibility Index","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_weg = {"weg","weg","xxxx", "Wind Erodibility Group","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_erocl = {"erocl","erocl","xxxx", "Erosion Class","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_earthcovkind1 = {"earthcovkind1","earthcovkind1","xxxx" ,"Cover Kind 1","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_earthcovkind2 = {"earthcovkind2","earthcovkind2","xxxx", "Cover Kind 2","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_hydricon = {"hydricon","hydricon","xxxx", "Hydric Condition","Hint","HTTP:\\descriptionURL",UC_unitless};            // width 254
Parameter_properties_literal PP_hydricrating = {"hydricrating","hydricrating","xxxx", "Hydric Rating","Hint","HTTP:\\descriptionURL",UC_unitless};   // width 254
Parameter_properties_literal PP_drainagecl = {"drainagecl","drainagecl","xxxx", "Drainage Class","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_elev_l = {"elev_l","elev_l","xxxx","Elevation","Low","HTTP:\\descriptionURL",UC_meter}; Parameter_range PPR_elev={-300,8550,-300,8550}; // , 1,10 };             //    (prcsn 1)   meters
Parameter_properties_literal PP_elev_r = {"elev_r","elev_r","xxxx","Elevation","Representitive","HTTP:\\descriptionURL",UC_meter};
Parameter_properties_literal PP_elev_h = {"elev_h","elev_h","xxxx","Elevation","High","HTTP:\\descriptionURL",UC_meter};
Parameter_properties_literal PP_aspectccwise = {"aspectccwise","aspectccwise","xxxx","Aspect Counter Clockwise","Hint","HTTP:\\descriptionURL",UC_degree_angle}; Parameter_range PPR_aspect={0,360,0,360}; // , 0,10 };
Parameter_properties_literal PP_aspectrep = {"aspectrep","aspectrep","xxxx","Aspect Representative","Hint","HTTP:\\descriptionURL",UC_degree_angle};
Parameter_properties_literal PP_aspectcwise = {"aspectcwise","aspectcwise","xxxx","Aspect Clockwise","Hint","HTTP:\\descriptionURL",UC_degree_angle};
Parameter_properties_literal PP_geomdesc = {"geomdesc","geomdesc","xxxx","Geomorphic Description","Hint","HTTP:\\descriptionURL",UC_unitless};
Parameter_properties_literal PP_albedodry_l = {"albedodry_l","albedodry_l","xxxx","Albedo Dry","Low","HTTP:\\descriptionURL",UC_decimal_percent}; Parameter_range PPR_albedo={0,1,0,1}; // , 2,10 };
Parameter_properties_literal PP_albedodry_r = {"albedodry_r","albedodry_r","xxxx","Albedo Dry","Representative","HTTP:\\descriptionURL",UC_decimal_percent};
Parameter_properties_literal PP_albedodry_h = {"albedodry_h","albedodry_h","xxxx","Albedo Dry","High","HTTP:\\descriptionURL",UC_decimal_percent};
Parameter_properties_literal PP_airtempa_l = {"airtempa_l","airtempa_l","xxxx","MAAT","Low","HTTP:\\descriptionURL",UC_Celcius}; Parameter_range PPR_airtempa={-50,50,-50,50}; // , 1,10 };
Parameter_properties_literal PP_airtempa_r = {"airtempa_r","airtempa_r","xxxx","MAAT","Representative","HTTP:\\descriptionURL",UC_Celcius};
Parameter_properties_literal PP_airtempa_h = {"airtempa_h","airtempa_h","xxxx","MAAT","High","HTTP:\\descriptionURL",UC_Celcius};
Parameter_properties_literal PP_map_l = {"map_l","map_l","xxxx","MAP","Low","HTTP:\\descriptionURL",UC_mm}; Parameter_range PPR_map={0,11500,0,11500}; // , 0,10 };
Parameter_properties_literal PP_map_r = {"map_r","map_r","xxxx","MAP","Representative","HTTP:\\descriptionURL",UC_mm};
Parameter_properties_literal PP_map_h = {"map_h","map_h","xxxx","MAP","High","HTTP:\\descriptionURL",UC_mm};
Parameter_properties_literal PP_reannualprecip_l = {"reannualprecip_l","reannualprecip_l","xxxx","REAP","Low","HTTP:\\descriptionURL",UC_mm}; Parameter_range PPR_reannualprecip={0,11500,0,11500}; // , 0,10 };
Parameter_properties_literal PP_reannualprecip_r = {"reannualprecip_r","reannualprecip_r","xxxx","REAP","Representative","HTTP:\\descriptionURL",UC_mm};
Parameter_properties_literal PP_reannualprecip_h = {"reannualprecip_h","reannualprecip_h","xxxx","REAP","High","HTTP:\\descriptionURL",UC_mm};
Parameter_properties_literal PP_ffd_l = {"ffd_l","ffd_l","xxxx","Frost Free Days","Low","HTTP:\\descriptionURL",UT_day}; Parameter_range PPR_ffd={0,365,0,365}; // , 0,10 };
Parameter_properties_literal PP_ffd_r = {"ffd_r","ffd_r","xxxx","Frost Free Days","Representative","HTTP:\\descriptionURL",UT_day};
Parameter_properties_literal PP_ffd_h = {"ffd_h","ffd_h","xxxx","Frost Free Days","Hint","HTTP:\\descriptionURL",UT_day};
Parameter_properties_literal PP_nirrcapcl = {"nirrcapcl","nirrcapcl","xxxx", "Nirr LCC","Capability class","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_nirrcapscl = {"nirrcapscl","nirrcapscl","xxxx", "Nirr Subcl","Capability subclass","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_nirrcapunit = {"nirrcapunit","nirrcapunit","xxxx","Nirr LCU","","HTTP:\\descriptionURL",UC_unitless}; Parameter_range PPR_capunit={1,99,1,99}; // , 0,10 };
Parameter_properties_literal PP_irrcapcl = {"irrcapcl","irrcapcl","xxxx",  "Irr LCC ","Capability class","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_irrcapscl = {"irrcapscl","irrcapscl","xxxx", "Irr Subcl Choice","Capability subclass","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_irrcapunit = {"irrcapunit","irrcapunit","xxxx","Irr LCU","Hint","HTTP:\\descriptionURL",UC_unitless};
Parameter_properties_literal PP_cropprodindex = {"cropprodindex","cropprodindex","xxxx","Prod Index ","Hint","HTTP:\\descriptionURL",UC_index}; Parameter_range PPR_cropprodindex={0,100,0,100}; // , 0,10 };
Parameter_properties_literal PP_constreeshrubgrp = {"constreeshrubgrp","constreeshrubgrp","xxxx", "Cons Tree Shrub Group","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_wndbrksuitgrp = {"wndbrksuitgrp","wndbrksuitgrp","xxxx", "Windbreak Suitability","Obsolete","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_rsprod_l = {"rsprod_l","rsprod_l","xxxx","Range Prod","Low","HTTP:\\descriptionURL",UE_pound_per_acre/*per year*/}; Parameter_range PPR_rsprod={0,20000,0,20000}; // , 0,10 }; //   0 20000 pounds per acre per year
Parameter_properties_literal PP_rsprod_r = {"rsprod_r","rsprod_r","xxxx","Range Prod","Representative","HTTP:\\descriptionURL",UE_pound_per_acre/*per year*/};
Parameter_properties_literal PP_rsprod_h = {"rsprod_h","rsprod_h","xxxx","Range Prod","High","HTTP:\\descriptionURL",UE_pound_per_acre/*per year*/};
Parameter_properties_literal PP_foragesuitgrpid = {"foragesuitgrpid","foragesuitgrpid","xxxx","Forage Suitability Group ID","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 11
Parameter_properties_literal PP_wlgrain = {"wlgrain","wlgrain","xxxx", "Grain Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlgrass = {"wlgrass","wlgrass","xxxx", "Grass Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlherbaceous = {"wlherbaceous","wlherbaceous","xxxx", "Herbaceous Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlshrub = {"wlshrub","wlshrub","xxxx",  "Shrub Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlconiferous = {"wlconiferous","wlconiferous","xxxx", "Conifer Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlhardwood = {"wlhardwood","wlhardwood","xxxx", "Hardwood Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlwetplant = {"wlwetplant","wlwetplant","xxxx", "Wetland Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlshallowwat = {"wlshallowwat","wlshallowwat","xxxx",  "Water Habitat","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlrangeland = {"wlrangeland","wlrangeland","xxxx",  "Rangeland Wildlife","Hint","HTTP:\\descriptionURL",UC_unitless};;// width 254
Parameter_properties_literal PP_wlopenland = {"wlopenland","wlopenland","xxxx", "Openland Wildlife","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlwoodland = {"wlwoodland","wlwoodland","xxxx", "Woodland Wildlife","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_wlwetland = {"wlwetland","wlwetland","xxxx", "Wetland Wildlife","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_soilslippot = {"soilslippot","soilslippot","xxxx", "Soil Slip Pot Choice","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 254
Parameter_properties_literal PP_frostact = {"frostact","frostact","xxxx", "Frost Action Choice ","Hint","HTTP:\\descriptionURL",UC_unitless};          // width 254
Parameter_properties_literal PP_initsub_l = {"initsub_l","initsub_l","xxxx","Init Subsid","Low","HTTP:\\descriptionURL",UC_cm}; Parameter_range PPR_subsidence={0,999,0,999}; // , 0,10 };                      //   0 999 centimeters
Parameter_properties_literal PP_initsub_r = {"initsub_r","initsub_r","xxxx","Init Subsid","Representative","HTTP:\\descriptionURL",UC_cm};
Parameter_properties_literal PP_initsub_h = {"initsub_h","initsub_h","xxxx","Init Subsid","High","HTTP:\\descriptionURL",UC_cm};
Parameter_properties_literal PP_totalsub_l = {"totalsub_l","totalsub_l","xxxx","Total Subsid","Low","HTTP:\\descriptionURL",UC_cm};
Parameter_properties_literal PP_totalsub_r = {"totalsub_r","totalsub_r","xxxx","Total Subsid","Representative","HTTP:\\descriptionURL",UC_cm};
Parameter_properties_literal PP_totalsub_h = {"totalsub_h","totalsub_h","xxxx","Total Subsid","High","HTTP:\\descriptionURL",UC_cm};
Parameter_properties_literal PP_hydgrp = {"hydgrp","hydgrp","xxxx", "Hydrologic Group","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_corcon = {"corcon","corcon","xxxx", "Corrosion Concrete","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_corsteel = {"corsteel","corsteel","xxxx", "Corrosion Steel","uncoated","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxclname = {"taxclname","taxclname","xxxx", "Class","Taxonomic class","HTTP:\\descriptionURL",UC_unitless}; // width 120
Parameter_properties_literal PP_taxorder = {"taxorder","taxorder","xxxx", "Order ","Taxonomic order","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxsuborder = {"taxsuborder","taxsuborder","xxxx", "Suborder","Taxonomic suborder","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxgrtgroup = {"taxgrtgroup","taxgrtgroup","xxxx", "Great Group","Taxonomic great group","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxsubgrp = {"taxsubgrp","taxsubgrp","xxxx", "Subgroup","Taxonomic subgroup","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxpartsize = {"taxpartsize","taxpartsize","xxxx", "Particle Size","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxpartsizemod = {"taxpartsizemod","taxpartsizemod","xxxx", "Particle Size Mod","Taxonomic_family_part_size_mod","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxceactcl = {"taxceactcl","taxceactcl","xxxx", "CEC Activity Cl","Taxonomic_family_c_e_act_class","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxreaction = {"taxreaction","taxreaction","xxxx", "Reaction","Taxonomic_family_reaction","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxtempcl = {"taxtempcl","taxtempcl","xxxx", "Temp Class","Taxonomic_family_temp_class","HTTP:\\descriptionURL",UC_unitless};  // width 254
Parameter_properties_literal PP_taxmoistscl = {"taxmoistscl","taxmoistscl","xxxx", "Moist Subclass","Taxonomic_moisture_subclass","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_taxtempregime = {"taxtempregime","taxtempregime","xxxx", "Temp Regime","Taxonomic_temp_regime","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_soiltaxedition = {"soiltaxedition","soiltaxedition","xxxx", " Keys to Taxonomy Edition Used","Soil_taxonomy_edition","HTTP:\\descriptionURL",UC_unitless};// width 2
Parameter_properties_literal PP_castorieindex = {"castorieindex","castorieindex","xxxx","CA Storie Index","Hint","HTTP:\\descriptionURL",UC_index};         Parameter_range PPR_castorieindex={0,100,0,100}; // , 0,10 };
Parameter_properties_literal PP_flecolcomnum = {"flecolcomnum","flecolcomnum","xxxx", "FL Ecol Comm #","Hint","HTTP:\\descriptionURL",UC_unitless};// width 5
Parameter_properties_literal PP_flhe = {"flhe","flhe","xxxx", "FL HE","Hint","HTTP:\\descriptionURL",UC_unitless};// width 3
Parameter_properties_literal PP_flphe = {"flphe","flphe","xxxx", "FL PHE","Hint","HTTP:\\descriptionURL",UC_unitless}; // width 3
Parameter_properties_literal PP_flsoilleachpot = {"flsoilleachpot","flsoilleachpot","xxxx", "FL Leach Pot","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_flsoirunoffpot = {"flsoirunoffpot","flsoirunoffpot","xxxx", "FL Runoff Pot","Hint","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_fltemik2use = {"fltemik2use","fltemik2use","xxxx", "FL Temik","","HTTP:\\descriptionURL",UC_unitless};// width 3
Parameter_properties_literal PP_fltriumph2use = {"fltriumph2use","","xxxx", "FL Triumph","","HTTP:\\descriptionURL",UC_unitless};;// width 3
Parameter_properties_literal PP_indraingrp = {"indraingrp","indraingrp","xxxx", "IN Drainage Grp","Hint","HTTP:\\descriptionURL",UC_unitless};// width 3
Parameter_properties_literal PP_innitrateleachi = {"innitrateleachi","innitrateleachi","xxxx","IN NO3 Leach Index","Hint","HTTP:\\descriptionURL",UC_index}; Parameter_range PPR_innitrateleachi={0,9,0,99}; // , 0,10 };
Parameter_properties_literal PP_misoimgmtgrp = {"misoimgmtgrp","misoimgmtgrp","xxxx", "MI Soil Mgmt Grp","MI_Soil_management_group","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_vasoimgtgrp = {"vasoimgtgrp","vasoimgtgrp","xxxx", "VA Soil Mgmt Grp","VA_Soil_management_group","HTTP:\\descriptionURL",UC_unitless};// width 254
Parameter_properties_literal PP_mukey = {"mukey","mukey","xxxx", "Mapunit Key","Hint","HTTP:\\descriptionURL",UC_unitless};// width 30
Parameter_properties_literal PP_cokey = {"cokey","cokey","xxxx", "Component Key","Hint","HTTP:\\descriptionURL",UC_unitless};// width 30
//______________________________________________________________________________
Component::Component()
: Component_struct()
, CORN::Data_record("component")
,p_comppct_l(comppct.low,PP_comppct_l,PPR_comppct,PPF_8_0_10)
,p_comppct_r(comppct.repr,PP_comppct_r,PPR_comppct,PPF_8_0_10)
,p_comppct_h(comppct.high,PP_comppct_h,PPR_comppct,PPF_8_0_10)
//,p_compname(compname,PP_compname)
//,p_compkind(compkind,PP_compkind)
//,p_majcompflag(majcompflag,PP_majcompflag)
//,p_otherph(otherph,PP_otherph)
//,p_localphase(localphase,PP_localphase)
,p_slope_l           (slope.low,PP_slope_l,PPR_slope,PPF_8_1_10)
,p_slope_r           (slope.repr,PP_slope_r,PPR_slope,PPF_8_1_10)
,p_slope_h           (slope.high,PP_slope_h,PPR_slope,PPF_8_1_10)
,p_slopelenusle_l    (slopelenusle.low,PP_slopelenusle_l,PPR_slopelenusle,PPF_8_0_10)
,p_slopelenusle_r    (slopelenusle.repr,PP_slopelenusle_r,PPR_slopelenusle,PPF_8_0_10)
,p_slopelenusle_h    (slopelenusle.high,PP_slopelenusle_h,PPR_slopelenusle,PPF_8_0_10)
//,p_runoff(runoff,PP_runoff)
,p_tfact(tfact,PP_tfact,PPR_tfact,PPF_8_1_10)
//,p_wei(wei,PP_wei)
//,p_weg(weg,PP_weg)
//,p_erocl(erocl,PP_erocl)
//,p_earthcovkind1(earthcovkind1,PP_earthcovkind1)
//,p_earthcovkind2(earthcovkind2,PP_earthcovkind2)
//,p_hydricon(hydricon,PP_hydricon)
//,p_hydricrating(hydricrating,PP_hydricrating)
//,p_drainagecl(drainagecl,PP_drainagecl)
,p_elev_l(elev.low,PP_elev_l,PPR_elev,PPF_8_1_10)
,p_elev_r(elev.repr,PP_elev_r,PPR_elev,PPF_8_1_10)
,p_elev_h(elev.high,PP_elev_h,PPR_elev,PPF_8_1_10)
,p_aspectccwise(aspectccwise,PP_aspectccwise,PPR_aspect,PPF_8_0_10)
,p_aspectrep(aspectrep,PP_aspectrep,PPR_aspect,PPF_8_0_10)
,p_aspectcwise(aspectcwise,PP_aspectcwise,PPR_aspect,PPF_8_0_10)
//,p_geomdesc(geomdesc,PP_geomdesc)
,p_albedodry_l(albedodry.low,PP_albedodry_l,PPR_albedo,PPF_8_2_10)
,p_albedodry_r(albedodry.repr,PP_albedodry_r,PPR_albedo,PPF_8_2_10)
,p_albedodry_h(albedodry.high,PP_albedodry_h,PPR_albedo,PPF_8_2_10)
,p_airtempa_l(airtempa.low,PP_airtempa_l,PPR_airtempa,PPF_8_1_10)
,p_airtempa_r(airtempa.repr,PP_airtempa_r,PPR_airtempa,PPF_8_1_10)
,p_airtempa_h(airtempa.high,PP_airtempa_h,PPR_airtempa,PPF_8_1_10)
,p_map_l(map.low,PP_map_l,PPR_map,PPF_8_0_10)
,p_map_r(map.repr,PP_map_r,PPR_map,PPF_8_0_10)
,p_map_h(map.high,PP_map_h,PPR_map,PPF_8_0_10)
,p_reannualprecip_l(reannualprecip.low,PP_reannualprecip_l,PPR_reannualprecip,PPF_8_0_10)
,p_reannualprecip_r(reannualprecip.repr,PP_reannualprecip_r,PPR_reannualprecip,PPF_8_0_10)
,p_reannualprecip_h(reannualprecip.high,PP_reannualprecip_h,PPR_reannualprecip,PPF_8_0_10)
,p_ffd_l(ffd.low,PP_ffd_l,PPR_ffd,PPF_8_0_10)
,p_ffd_r(ffd.repr,PP_ffd_r,PPR_ffd,PPF_8_0_10)
,p_ffd_h(ffd.high,PP_ffd_h,PPR_ffd,PPF_8_0_10)
//,p_nirrcapcl(nirrcapcl,PP_nirrcapcl)
///,p_nirrcapscl(nirrcapscl,PP_nirrcapscl)
,p_nirrcapunit(nirrcapunit,PP_nirrcapunit,PPR_capunit,PPF_8_0_10)
//,p_irrcapcl(irrcapcl,PP_irrcapcl,PPR_irrcapcl)
//,p_irrcapscl(irrcapscl,PP_irrcapscl,PPR_x)
,p_irrcapunit(irrcapunit,PP_irrcapunit,PPR_capunit,PPF_8_0_10)
,p_cropprodindex(cropprodindex,PP_cropprodindex,PPR_cropprodindex,PPF_8_0_10)
//,p_constreeshrubgrp(constreeshrubgrp,PP_constreeshrubgrp)
//,p_wndbrksuitgrp(wndbrksuitgrp,PP_wndbrksuitgrp)
,p_rsprod_l(rsprod.low,PP_rsprod_l,PPR_rsprod,PPF_8_0_10)
,p_rsprod_r(rsprod.repr,PP_rsprod_r,PPR_rsprod,PPF_8_0_10)
,p_rsprod_h(rsprod.high,PP_rsprod_h,PPR_rsprod,PPF_8_0_10)
//,p_foragesuitgrpie(foragesuitgrpid,PP_foragesuitgrpid)
//,p_wlgrain(wlgrain,PP_wlgrain)
//,p_wlgrass(wlgrass,PP_wlgrass)
//,p_wlherbaceous(wlherbaceous,PP_wlherbaceous)
//,p_wlshrub(wlshrub,PP_wlshrub)
//,p_wlconiferous(wlconiferous,PP_wlconiferous)
//,p_wlhardwooe(wlhardwood,PP_wlhardwood)
//,p_wlwetplant(wlwetplant,PP_wlwetplant)
//,p_wlshallowwat(wlshallowwat,PP_wlshallowwat)
//,p_wlrangelane(wlrangeland,PP_wlrangeland)
//,p_wlopenlane(wlopenland,PP_wlopenland)
//,p_wlwoodlane(wlwoodland,PP_wlwoodland)
//,p_wlwetlane(wlwetland,PP_wlwetland)
//,p_soilslippot(soilslippot,PP_soilslippot)
//,p_frostact(frostact,PP_frostact)
,p_initsub_l(initsub.low,PP_initsub_l,PPR_subsidence,PPF_8_0_10)
,p_initsub_r(initsub.repr,PP_initsub_r,PPR_subsidence,PPF_8_0_10)
,p_initsub_h(initsub.high,PP_initsub_h,PPR_subsidence,PPF_8_0_10)
,p_totalsub_l(totalsub.low,PP_totalsub_l,PPR_subsidence,PPF_8_0_10)
,p_totalsub_r(totalsub.repr,PP_totalsub_r,PPR_subsidence,PPF_8_0_10)
,p_totalsub_h(totalsub.high,PP_totalsub_h,PPR_subsidence,PPF_8_0_10)
//,p_hydgrp(hydgrp,PP_hydgrp)
//,p_corcon(corcon,PP_corcon)
//,p_corsteel(corsteel,PP_corsteel)
//,p_taxclname(taxclname,PP_taxclname)
//,p_taxorder(taxorder,PP_taxorder)
//,p_taxsuborder(taxsuborder,PP_taxsuborder)
//,p_taxgrtgroup(taxgrtgroup,PP_taxgrtgroup)
//,p_taxsubgrp(taxsubgrp,PP_taxsubgrp)
//,p_taxpartsize(taxpartsize,PP_taxpartsize)
//,p_taxpartsizemod(taxpartsizemod,PP_taxpartsizemod)
//,p_taxceactcl(taxceactcl,PP_taxceactcl)
//,p_taxreaction(taxreaction,PP_taxreaction)
//,p_taxtempcl(taxtempcl,PP_taxtempcl)
//,p_taxmoistscl(taxmoistscl,PP_taxmoistscl)
//,p_taxtempregime(taxtempregime,PP_taxtempregime)
//,p_soiltaxedition(soiltaxedition,PP_soiltaxedition)
,p_castorieindex(castorieindex,PP_castorieindex,PPR_castorieindex,PPF_8_0_10)
//,p_flecolcomnum(flecolcomnum,PP_flecolcomnum)
//,p_flhe(flhe,PP_flhe)
//,p_flphe(flphe,PP_flphe)
//,p_flsoilleachpot(flsoilleachpot,PP_flsoilleachpot)
//,p_flsoirunoffpot(flsoirunoffpot,PP_flsoirunoffpot)
//,p_fltemik2use(fltemik2use,PP_fltemik2use)
//,p_fltriumph2use(fltriumph2use,PP_fltriumph2use)
//,p_indraingrp(indraingrp,PP_indraingrp)
,p_innitrateleachi(innitrateleachi,PP_innitrateleachi,PPR_innitrateleachi,PPF_8_0_10)
//,p_misoimgmtgrp(misoimgmtgrp,PP_misoimgmtgrp)
//,p_vasoimgtgrp(vasoimgtgrp,PP_vasoimgtgrp)
//,p_mukey(mukey,PP_mukey)
//,p_cokey(cokey,PP_cokey)
{ clear();                                                                       //111212
};
//______________________________________________________________________________
bool Component::expect_structure(bool for_write)
{
   bool expected = CORN::Data_record::expect_structure(for_write);
   expect_parameter(p_comppct_l);          // Comp %   0 100 percent
   expect_parameter(p_comppct_r);
   expect_parameter(p_comppct_h);
   expect_string("compname",compname,60); //expect_parameter(p_compname);         // Component Name String No 60
   expect_enum("compkind",compkind/*,254*/); //   expect_parameter(p_compkind);      // Kind 254 Component_kind
   expect_bool("majcompflag",majcompflag);             // Major Component 3 bool
   expect_string("otherph",otherph,40); //   expect_parameter(p_otherph);          // SIR phase No 40
   expect_string("localphase",localphase,40); //   expect_parameter(p_localphase);       // Local Phase   40
   expect_parameter(p_slope_l);            // Slope Gradient (prcsn 1) 0 999, percent
   expect_parameter(p_slope_r);
   expect_parameter(p_slope_h);
   expect_parameter(p_slopelenusle_l);     // Slope Length USLE    0 4000, meters
   expect_parameter(p_slopelenusle_r);
   expect_parameter(p_slopelenusle_h);
   expect_string("runoff",runoff,245); //   expect_parameter(p_runoff);          //  Runoff Class   254 runoff Runoff_class
   expect_parameter(p_tfact);            // T  (prcsn 1) 5 tons per acre per year
   expect_string("wei",wei,254); //   expect_parameter(p_wei);   // Wind Erodibility Index 254, tons per acre per year wind_erodibility_index Wind_erodibility_index
   expect_string("weg",weg,254); //   expect_parameter(p_weg);   // Wind Erodibility Group 254 Wind_erodibility_group
   expect_string("erocl",erocl,254); //   expect_parameter(p_erocl);          // Erosion Class   254 Erosion_class
   expect_string("earthcovkind1",earthcovkind1,254); //   expect_parameter(p_earthcovkind1; // Cover Kind 1  254 Earth_cover_kind_level_one
   expect_string("earthcovkind2",earthcovkind2,254); //   expect_parameter(p_earthcovkind2; // Cover Kind 2  254 Earth_cover_kind_level_two
   expect_string("hydricon",hydricon,254); //   expect_parameter(p_hydricon);      // Hydric Condition 254 Hydric_condition
   expect_string("hydricrating",hydricrating,254); //   expect_parameter(p_hydricrating);  // Hydric Rating 254 Hydric_rating
   expect_string("drainagecl",drainagecl,254); //   expect_parameter(p_drainagecl);    // Drainage Class 254 Drainage_class
   expect_parameter(p_elev_l);             // Elevation   (prcsn 1) -300 8550 meters
   expect_parameter(p_elev_r);
   expect_parameter(p_elev_h);
   expect_parameter(p_aspectccwise);           // Aspect Counter Clockwise   0 360 degrees
   expect_parameter(p_aspectrep);              // Aspect Representative   0 360 degrees
   expect_parameter(p_aspectcwise);            // Aspect Clockwise   0 360 degrees
   expect_string("geomdesc",geomdesc,254); //   expect_parameter(p_geomdesc);               //Geomorphic Description Vtext No Vtext
   expect_parameter(p_albedodry_l);        // Albedo Dry  (prcsn 2) 0 1
   expect_parameter(p_albedodry_r);
   expect_parameter(p_albedodry_h);
   expect_parameter(p_airtempa_l);         // MAAT  (prcsn 1) -50 50 degrees centigrade
   expect_parameter(p_airtempa_r);
   expect_parameter(p_airtempa_h);
   expect_parameter(p_map_l);              // MAP  No 0 11500 millimeters
   expect_parameter(p_map_r);
   expect_parameter(p_map_h);
   expect_parameter(p_reannualprecip_l);   // REAP No 0 11500 millimeters
   expect_parameter(p_reannualprecip_r);
   expect_parameter(p_reannualprecip_h);
   expect_parameter(p_ffd_l);              // Frost Free Days  0 365 days
   expect_parameter(p_ffd_r);
   expect_parameter(p_ffd_h);
   expect_enum("nirrcapcl",nirrcapcl); //   expect_parameter(p_);  // Nirr LCC 254 Capability_class
   expect_enum("nirrcapscl",nirrcapscl); //   expect_parameter(p_); //  Nirr Subcl Choice No 254 Capability_subclass
   expect_parameter(p_nirrcapunit);            // Nirr LCU  1 99
   expect_enum("irrcapcl",irrcapcl);    // Irr LCC 254 Capability_class
   expect_enum("irrcapscl",irrcapscl); //   expect_parameter(p_irrcapscl);// Irr Subcl Choice No 254 Capability_subclass
   expect_parameter(p_irrcapunit);       // Irr LCU  No 1 99
   expect_parameter(p_cropprodindex);    // Prod Index   0 100
   expect_string("constreeshrubgrp",constreeshrubgrp,254); //   expect_parameter(p_constreeshrubgrp); //  Cons Tree Shrub Group   254 Conservation_tree_shrub_group
   expect_string("wndbrksuitgrp",wndbrksuitgrp,254); //   expect_parameter(p_wndbrksuitgrp); // Windbreak Suitability (Obsolete)   254 Windbreak_suitability_group
   expect_parameter(p_rsprod_l); // Range Prod  0 20000 pounds per acre per year
   expect_parameter(p_rsprod_r);
   expect_parameter(p_rsprod_h);
   expect_string("foragesuitgrpid",foragesuitgrpid,11); //   expect_parameter(p_); // Forage Suitability Group ID 11
   expect_string("wlgrain",wlgrain,254); //   expect_parameter(p_wlgrain);       // Grain Habitat   254    Wildlife_rating
   expect_string("wlgrass",wlgrass,254); //   expect_parameter(p_wlgrass);       // Grass Habitat   254   Wildlife_rating
   expect_string("wlherbaceous",wlherbaceous,254); //   expect_parameter(p_wlherbaceous);  // Herbaceous Habitat   254  Wildlife_rating
   expect_string("wlshrub",wlshrub,254); //   expect_parameter(p_wlshrub);       // Shrub Habitat   254  Wildlife_rating
   expect_string("wlconiferous",wlconiferous,254); //   expect_parameter(p_wlconiferous);  // Conifer Habitat   254  Wildlife_rating
   expect_string("wlhardwood",wlhardwood,254); //   expect_parameter(p_wlhardwood);    // Hardwood Habitat   254 Wildlife_rating
   expect_string("wlwetplant",wlwetplant,254); //   expect_parameter(p_wlwetplant);    // Wetland Habitat   254  Wildlife_rating
   expect_string("wlshallowwat",wlshallowwat,254); //   expect_parameter(p_wlshallowwat);  // Water Habitat   254    Wildlife_rating
   expect_string("wlrangeland",wlrangeland,254); //   expect_parameter(p_wlrangeland);   // Rangeland Wildlife   254   Wildlife_rating
   expect_string("wlopenlande",wlopenland,254); //   expect_parameter(p_wlopenland);    // Openland Wildlife   254  Wildlife_rating
   expect_string("wlwoodland",wlwoodland,254); //   expect_parameter(p_wlwoodland);    // Woodland Wildlife   254  Wildlife_rating
   expect_string("wlwetland",wlwetland,254); //   expect_parameter(p_wlwetland);     // Wetland Wildlife   254   Wildlife_rating
   expect_string("soilslippot",soilslippot,254); //   expect_parameter(p_soilslippot);   // Soil Slip Pot Choice  254 Soil_slippage_potential
   expect_string("frostact",frostact,254); //   expect_parameter(p_frostact);      // Frost Action Choice  254 Potential_frost_action
   expect_parameter(p_initsub_l);                      // Init Subsid  0 999 centimeters
   expect_parameter(p_initsub_r);
   expect_parameter(p_initsub_h);
   expect_parameter(p_totalsub_l);                     // Total Subsid  0 999 centimeters
   expect_parameter(p_totalsub_r);                      // Total Subsid  0 999 centimeters
   expect_parameter(p_totalsub_h);                     // Total Subsid  0 999 centimeters
   expect_enum("hydgrp",hydgrp/*,254*/); //   expect_parameter(p_hydgrp);        // Hydrologic Group   254 Hydrologic_group
   expect_string("corcon",corcon,254); //   expect_parameter(p_corcon);        // Corrosion Concrete  254 Corrosion_concrete
   expect_string("corsteel",corsteel,254); //   expect_parameter(p_corsteel);      // Corrosion Steel   254 Corrosion_uncoated_steel
   expect_string("taxclname",taxclname,254); //   expect_parameter(p_taxclname);     // Taxonomic Class 120
   expect_string("taxorder",taxorder,254); //   expect_parameter(p_taxorder);      // Order   254 Taxonomic_order
   expect_string("taxsuborder",taxsuborder,254); //   expect_parameter(p_taxsuborder);   // Suborder 254 Taxonomic_suborder
   expect_string("taxgrtgroup",taxgrtgroup,254); //   expect_parameter(p_taxgrtgroup);   // Great Group 254 Taxonomic_great_group
   expect_string("taxsubgrp",taxsubgrp,254); //   expect_parameter(p_taxsubgrp);     // Subgroup 254 Taxonomic_subgroup
   expect_string("taxpartsize",taxpartsize,254); //   expect_parameter(p_taxpartsize);   // Particle Size 254  Taxonomic_family_particle_size
   expect_string("taxpartsizemod",taxpartsizemod,254); //   expect_parameter(p_taxpartsizemod);// Particle Size Mod 254 Taxonomic_family_part_size_mod
   expect_string("taxceactcl",taxceactcl,254); //   expect_parameter(p_taxceactcl);    // CEC Activity Cl 254   Taxonomic_family_c_e_act_class
   expect_string("taxreaction",taxreaction,254); //   expect_parameter(p_taxreaction);   // Reaction 254  Taxonomic_family_reaction
   expect_string("taxtempcl",taxtempcl,254); //   expect_parameter(p_taxtempcl);     // Temp Class 254 Taxonomic_family_temp_class
   expect_string("taxmoistscl",taxmoistscl,254); //   expect_parameter(p_taxmoistscl);   // Moist Subclass   254  //Taxonomic_moisture_subclass
   expect_string("taxtempregime",taxtempregime,254); //   expect_parameter(p_taxtempregime); // Temp Regime 254 Taxonomic_temp_regime
   expect_string("soiltaxedition",soiltaxedition,254); //   expect_parameter(p_soiltaxedition);// Keys to Taxonomy Edition Used 254 Soil_taxonomy_edition
   expect_parameter(p_castorieindex);    // CA Storie Index   0 100
   expect_string("flecolcomnum",flecolcomnum,5);     // FL Ecol Comm #   5
   expect_bool("flhe",flhe);             // FL HE  3       the boolean is current read into a string
   expect_bool("flphe",flphe);            // FL PHE 3        the boolean is current read into a string
   expect_string("flsoilleachpot",flsoilleachpot,254); //   expect_parameter(p_flsoilleachpot);
   expect_string("flsoirunoffpot",flsoirunoffpot,254); //   expect_parameter(p_flsoirunoffpot);
   expect_bool("fltemik2use",fltemik2use);
   expect_bool("fltriumph2use",fltriumph2use);                   // FL Triumph   3          the boolean is current read into a string
   expect_string("indraingrp",indraingrp,3);                      // IN Drainage Grp 3
   expect_parameter(p_innitrateleachi);                 // IN NO3 Leach Index   0 99
   expect_string("misoimgmtgrp",misoimgmtgrp,254); //   expect_parameter(p_misoimgmtgrp);     // MI Soil Mgmt Grp  254 MI_Soil_management_group
   expect_string("vasoimgtgrp",vasoimgtgrp,254); //   expect_parameter(p_vasoimgtgrp);      // VA Soil Mgmt Grp 254 VA_Soil_management_group
   expect_string("mukey",mukey,30); //   expect_parameter(p_mukey);   // Mapunit Key   30
   expect_string("cokey",cokey,30); //   expect_parameter(p_cokey);  // Component Key   30
   structure_defined = true;                                                     //120314
   return expected;
};
//______________________________________________________________________________
} // namespace USDA_NRCS

/*
|20||"Dorchester"|"Series"|"Yes"|"MAAT<50"||0|1|2|||||5||"4L"|||||"No"|"Well drained"|213|335|457||||||||7|9|11|762|813|864||||145|160|175|"2"|"w"||||||||||||"Fair"|"Fair"|"Fair"||"Poor"|"Fair"|"Poor"|"Poor"||"Fair"|"Poor"|"Poor"||"High"|||||||"B"|"Low"|"High"|"TYPIC UDIFLUVENTS, FINE-SILTY, MIXED (CALCAREOUS), MESIC"|"Entisols"|"Fluvents"|"Udifluvents"|"Typic Udifluvents"|"fine-silty"|"not used"|"superactive"|"calcareous"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:991195"
|20||"Chaseburg"|"Series"|"Yes"|"HIGH PPT"||0|1|2|||||5||"5"|||||"No"|"Moderately well drained"|||||||||||||||||||||||"1"|||||||||||||"Good"|"Good"|"Good"||"Good"|"Good"|"Poor"|"Poor"||"Good"|"Good"|"Poor"||"High"|||||||"B"|"Moderate"|"Moderate"|"TYPIC UDIFLUVENTS, COARSE-SILTY, MIXED, NONACID, MESIC"|"Entisols"|"Fluvents"|"Udifluvents"|"Typic Udifluvents"|"coarse-silty"|"not used"|"superactive"|"nonacid"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:991196"
|9||"Caneek"|"Series"||"MAAT<50"||0|1|2|||||5||"4L"|||||"Yes"|"Somewhat poorly drained"|198|297|396||||||||7|9|10|762|813|864||||145|160|175|"2"|"w"||||||||||||"Fair"|"Fair"|"Fair"||"Poor"|"Fair"|"Good"|"Good"||"Fair"|"Poor"|"Good"||"High"|||||||"B"|"Low"|"High"|"AERIC FLUVAQUENTS, FINE-SILTY, MIXED (CALCAREOUS), MESIC"|"Entisols"|"Aquents"|"Fluvaquents"|"Aeric Fluvaquents"|"fine-silty"|"not used"|"superactive"|"calcareous"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:991200"
|8||"Water"|"Miscellaneous area"||||||||||||||||||"No"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"1017218"|"1017218:991202"
|4||"Fayette"|"Series"||"MAAT<50, ERODED"|"moderately eroded"|5|7|9||84||"Medium"|5|"48"|"6"|||||"No"|"Well drained"|213|335|457||||||0.23||7|10|12|736|851|965||||145|163|180|"3"|"e"|||||||"3"|||||"Fair"|"Good"|"Good"||"Good"|"Good"|"Very poor"|"Very poor"||"Good"|"Good"|"Very poor"||"High"|0|0|0||||"B"|"Moderate"|"Moderate"|"TYPIC HAPLUDALFS, FINE-SILTY, MIXED, MESIC"|"Alfisols"|"Udalfs"|"Hapludalfs"|"Typic Hapludalfs"|"fine-silty"|"not used"|"superactive"|"not used"|"mesic"||"mesic"|"ninth edition"|||||||||||||"1017218"|"1017218:1199496"
|7||"Rock outcrop"|"Miscellaneous area"||||25|43|60||61||"Very high"||"0"|"8"|||||"Unranked"|"Well drained"|152|381|610||||||||6|9|12|660|813|965||||140|165|190|"8"|"s"||||||||||||"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"|"Very poor"||"None"|0|0|0||||"D"||||||||||||||||||||||||||||"1017218"|"1017218:1199497"
*/



