#include "soil_param_V5.h"
#define NO_HINT 0
#define NoAltFieldName 0
#define default_field_width 8
#include "static_phrases.h"
#define NotYetSubsection "NotYetSubsection"

//______________________________________________________________________________

#define TL_steepness_hint  "Grade as the tangent of the angle of inclination multiplied by 100 to express as a percentage"

Parameter_properties_literal PP_override_curve_number    = {LABEL_override_curve_number   ,NoAltFieldName,NotYetSubsection,"all other conditions"                    ,"SCS curve number override"  ,"%PROG_HOME%:path/document.HTM#anchor",UC_unitless,TU_unitless};    Parameter_range  PPR_override_curve_number    = { 1,99,0,100};                   Parameter_format PPF_override_curve_number     ={default_field_width,0,10};
Parameter_properties_literal PP_user_fallow_curve_number = {LABEL_fallow_curve_number     ,NoAltFieldName,NotYetSubsection,"fallow antecedent moisture condition II" ,"SCS curve number override"  ,"%PROG_HOME%:path/document.HTM#anchor",UC_unitless,TU_unitless};    Parameter_range  PPR_user_fallow_curve_number = { 1,99,0,100};                   Parameter_format PPF_user_fallow_curve_number  ={default_field_width,0,10};
Parameter_properties_literal PP_surface_storage_mm       = {LABEL_surface_storage         ,NoAltFieldName,NotYetSubsection,"Surface storage"                         ,"hint"                       ,"%PROG_HOME%:path/document.HTM#anchor",UC_mm,"mm"};                 Parameter_range  PPR_surface_storage          = { 0.0, 10.0,  0.0, 100.0 };      Parameter_format PPF_surface_storage           ={default_field_width,2,10};
Parameter_properties_literal PP_steepness                = {LABEL_steepness               ,NoAltFieldName,NotYetSubsection,TL_Steepness                              ,TL_steepness_hint            ,"%PROG_HOME%:path/document.HTM#anchor",UC_percent,"%"};             Parameter_range  PPR_steepness                = { 0.0,100.0,  0.0, 100.0 };      Parameter_format PPF_steepness                 ={default_field_width,2,10};
Parameter_properties_literal PP_slope_length             = {LABEL_slope_length            ,NoAltFieldName,NotYetSubsection,TL_Slope_length                           ,"hint"                       ,"%PROG_HOME%:path/document.HTM#anchor",UC_meter,TU_m};              Parameter_range  PPR_slope_length             = { 0.0,200.0,  0.0, 300.0 };      Parameter_format PPF_slope_length              ={default_field_width,2,10};
Parameter_properties_literal PP_albedo_dry               = {"albedo_dry"                  ,NoAltFieldName,NotYetSubsection,"dry"                                     ,"Albedo"                     ,"%PROG_HOME%:path/document.HTM#anchor",UC_decimal_percent,"0-1"};   Parameter_range  PPR_albedo_dry               = { 0.05, 0.5,  0.0,   1.0 };      Parameter_format PPF_albedo_dry                ={default_field_width,3,10};
Parameter_properties_literal PP_albedo_wet               = {"albedo_wet"                  ,NoAltFieldName,NotYetSubsection,"wet"                                     ,"Albedo"                     ,"%PROG_HOME%:path/document.HTM#anchor",UC_decimal_percent,"0-1"};   Parameter_range  PPR_albedo_wet               = { 0.05, 0.5,  0.0,   1.0 };      Parameter_format PPF_albedo_wet                ={default_field_width,3,10};
Parameter_properties_literal PP_SLPF_CropGro             = {"SLPF"                        ,NoAltFieldName,NotYetSubsection,"SLPF Soil Limitation? P???? Factor"      ,"hint"                       ,"%PROG_HOME%:path/document.HTM#anchor",UC_factor,"Factor"};         Parameter_range  PPR_SLPF_CropGro             = { 0.0,1.0,0.0,1.0        };      Parameter_format PPF_SLPF_CropGro              ={default_field_width,2,10};
Parameter_properties_literal PP_water_vapor_conductance_atmosphere_adj={"water_vapor_conductance_atmosphere_adj"  ,NoAltFieldName,NotYetSubsection,"Soil water vapor conductance adjustment","hint","%PROG_HOME%:path/document.HTM#anchor",UC_adjustment,"0-1"};        Parameter_range  PPR_water_vapor_conductance_atmosphere_adj  = { 0.00001,1.0,0.0,1.0}; Parameter_format PPF_water_vapor_conductance_atmosphere_adj ={default_field_width,5,10};

Parameter_range  PPR_layer_thickness          = { 0.0,4.0,0.0,10.0   };  Parameter_format PPF_layer_thickness          = {default_field_width,3,10};
Parameter_range  PPR_bypass_coef              = { 0.0,1.0,0.0,1.0    };  Parameter_format PPF_bypass_coef              = {default_field_width,3,10};
Parameter_range  PPR_perm_wilt_point          = { 0.03,0.25,0.0,0.3  };  Parameter_format PPF_perm_wilt_point          = {default_field_width,3,10};
Parameter_range  PPR_field_capacity           = { 0.06,0.42,0.0,0.5  };  Parameter_format PPF_field_capacity           = {default_field_width,3,10};
Parameter_range  PPR_vol_WC_at_1500           = { 0.03,0.25,0.0,0.3  };  Parameter_format PPF_vol_WC_at_1500           = {default_field_width,3,10};
Parameter_range  PPR_vol_WC_at_33             = { 0.06,0.42,0.0,0.5  };  Parameter_format PPF_vol_WC_at_33             = {default_field_width,3,10};
Parameter_range  PPR_bulk_density             = { 0.9, 1.8,0.5, 2.0  };  Parameter_format PPF_bulk_density             = {default_field_width,3,10};
Parameter_range  PPR_sand                     = { 5,95, 0.0,100.0    };  Parameter_format PPF_sand                     = {default_field_width,2,10};
Parameter_range  PPR_clay                     = { 5,95, 0.0,100.0    };  Parameter_format PPF_clay                     = {default_field_width,2,10};
Parameter_range  PPR_silt                     = { 5,95, 0.0,100.0    };  Parameter_format PPF_silt                     = {default_field_width,2,10};
Parameter_range  PPR_sat_hydraul_cond         = { 0.0,6.0,0.0,10.0   };  Parameter_format PPF_sat_hydraul_cond         = {default_field_width,7,10};
Parameter_range  PPR_saturation_WC            = { 0.0,6.0,0.0,10.0   };  Parameter_format PPF_saturation_WC            = {default_field_width,7,10};
Parameter_range  PPR_air_entry_pot            = { -8.0,-0.5,-10.0,0.0};  Parameter_format PPF_air_entry_pot            = {default_field_width,2,10};
Parameter_range  PPR_Campbell_b               = { 1.5,8.0,0.0,10.0   };  Parameter_format PPF_Campbell_b               = {default_field_width,3,10};
Parameter_range  PPR_pH                       = { 4.0,8.5,0.0,14.0   };  Parameter_format PPF_pH                       = {default_field_width,2,10};
Parameter_range  PPR_cation_exchange_capacity = { 0.0,200.0,0.0,200.0};  Parameter_format PPF_cation_exchange_capacity = {default_field_width,2,10};
Parameter_range  PPR_organic_matter           = { 0.0,50.0,0.0,100.0 };  Parameter_format PPF_organic_matter           = {default_field_width,2,10};
Parameter_range  PPR_organic_matter_low       = { 0.0,50.0,0.0,100.0 };  Parameter_format PPF_organic_matter_low       = {default_field_width,2,10};
Parameter_range  PPR_organic_matter_high      = { 0.0,50.0,0.0,100.0 };  Parameter_format PPF_organic_matter_high      = {default_field_width,2,10};

Parameter_properties_literal  PP_layer_thickness          = { LABEL_thickness       ,NoAltFieldName,NotYetSubsection,TL_Thickness                 ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_meter,TU_m};
Parameter_properties_literal  PP_bypass_coef              = { LABEL_bypass_coef     ,NoAltFieldName,NotYetSubsection,TL_Bypass_coef               ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_unitless,TU_unitless};
Parameter_properties_literal  PP_perm_wilt_point          = { LABEL_perm_wilt_point ,NoAltFieldName,NotYetSubsection,TL_Vol_PWP                   ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",U_units_not_specified,TU_m3_m3};
Parameter_properties_literal  PP_field_capacity           = { LABEL_field_capacity  ,NoAltFieldName,NotYetSubsection,TL_Vol_FC                    ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",U_units_not_specified,TU_m3_m3};
Parameter_properties_literal  PP_vol_WC_at_1500           = { LABEL_vol_WC_at_1500  ,NoAltFieldName,NotYetSubsection,TL_Vol_WC_at_1500            ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",U_units_not_specified,TU_m3_m3};
Parameter_properties_literal  PP_vol_WC_at_33             = { LABEL_vol_WC_at_33    ,NoAltFieldName,NotYetSubsection,TL_Vol_WC_at_33              ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",U_units_not_specified,TU_m3_m3};
Parameter_properties_literal  PP_bulk_density             = { LABEL_bulk_density    ,NoAltFieldName,NotYetSubsection,TL_Bulk_density              ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",U_units_not_specified,TU_g_cm3};
Parameter_properties_literal  PP_sand                     = { LABEL_sand            ,NoAltFieldName,NotYetSubsection,TL_P_sand                    ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_percent,TU_percent};
Parameter_properties_literal  PP_clay                     = { LABEL_clay            ,NoAltFieldName,NotYetSubsection,TL_P_clay                    ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_percent,TU_percent};
Parameter_properties_literal  PP_silt                     = { LABEL_silt            ,NoAltFieldName,NotYetSubsection,TL_P_silt                    ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_percent,TU_percent};
Parameter_properties_literal  PP_sat_hydraul_cond         = { LABEL_sat_hydraul_cond,NoAltFieldName,NotYetSubsection,TL_Saturated_hydraulic_conductivity,"hint"        ,"%PROG_HOME%:path/document.HTM#anchor",UC_meters_per_day,TU_m_day};
Parameter_properties_literal  PP_saturation_WC            = { "saturation"          ,NoAltFieldName,NotYetSubsection,"Saturated volumetric water content"  ,"hint"     ,"%PROG_HOME%:path/document.HTM#anchor",U_units_not_specified,TU_m3_m3};
Parameter_properties_literal  PP_air_entry_pot            = { LABEL_air_entry_pot   ,NoAltFieldName,NotYetSubsection,TL_Air_entry_potential       ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_J_kg,TU_J_kg};
Parameter_properties_literal  PP_Campbell_b               = { "Campbell_b"          ,LABEL_b       ,NotYetSubsection,TL_B_parameter_override      ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_unitless,TU_unitless};
Parameter_properties_literal  PP_pH                       = { LABEL_pH              ,NoAltFieldName,NotYetSubsection,"pH"                         ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_pH,TL_pH};
Parameter_properties_literal  PP_cation_exchange_capacity = { LABEL_cation_exchange_capacity,NoAltFieldName,NotYetSubsection,TL_Cation_exchange_capacity  ,"hint"              ,"%PROG_HOME%:path/document.HTM#anchor",UC_mEq_100g,TU_meq_100g};
Parameter_properties_literal  PP_organic_matter           = { "organic_matter"      ,NoAltFieldName,NotYetSubsection,"Organic matter"             ,"recently historical typical" ,"%PROG_HOME%:path/document.HTM#anchor",UC_percent,TU_percent};
Parameter_properties_literal  PP_organic_matter_low       = { "organic_matter_low"  ,NoAltFieldName,NotYetSubsection,"Organic matter range low"   ,"recently historical typical" ,"%PROG_HOME%:path/document.HTM#anchor",UC_percent,TU_percent};
Parameter_properties_literal  PP_organic_matter_high      = { "organic_matter_high" ,NoAltFieldName,NotYetSubsection,"Organic matter range high"  ,"recently historical typical" ,"%PROG_HOME%:path/document.HTM#anchor",UC_percent,TU_percent};

//______________________________________________________________________________
Soil_parameters::Soil_parameters()
: Soil_parameters_class_parent()
, p_override_curve_number                 (override_curve_number_16        ,PP_override_curve_number     ,PPR_override_curve_number    ,PPF_override_curve_number)
, p_user_fallow_curve_number              (user_fallow_curve_number_16     ,PP_user_fallow_curve_number  ,PPR_user_fallow_curve_number ,PPF_user_fallow_curve_number)
, p_surface_storage_mm                    (surface_storage_mm_32           ,PP_surface_storage_mm        ,PPR_surface_storage          ,PPF_surface_storage)
, p_steepness                             (steepness_percent               ,PP_steepness                 ,PPR_steepness                ,PPF_steepness)
, p_slope_length                          (slope_length                    ,PP_slope_length              ,PPR_slope_length             ,PPF_slope_length)
, p_albedo_dry                            (albedo_dry                      ,PP_albedo_dry                ,PPR_albedo_dry               ,PPF_albedo_dry)
, p_albedo_wet                            (albedo_wet                      ,PP_albedo_wet                ,PPR_albedo_wet               ,PPF_albedo_wet)
, p_water_vapor_conductance_atmosphere_adj(water_vapor_conductance_atmosphere_adj,PP_water_vapor_conductance_atmosphere_adj,PPR_water_vapor_conductance_atmosphere_adj,PPF_water_vapor_conductance_atmosphere_adj)
, p_SLPF_CropGro                          (SLPF_CropGro                    ,PP_SLPF_CropGro              ,PPR_SLPF_CropGro             ,PPF_SLPF_CropGro)
{
   for (int8 layer = 1; layer <= MAX_soil_horizons ; layer++)
   {
      p_layer_thickness[layer] = new CORN::Parameter_number(properties.thickness                         .ref(layer),PP_layer_thickness           ,PPR_layer_thickness           ,PPF_layer_thickness);
      p_bypass_coef[layer]     = new CORN::Parameter_number(properties.bypass_coef                       .ref(layer),PP_bypass_coef               ,PPR_bypass_coef               ,PPF_bypass_coef);
      p_perm_wilt_point[layer] = new CORN::Parameter_number(properties.permanent_wilt_point              .ref(layer),PP_perm_wilt_point           ,PPR_perm_wilt_point           ,PPF_perm_wilt_point);
      p_field_capacity[layer]  = new CORN::Parameter_number(properties.field_capacity                    .ref(layer),PP_field_capacity            ,PPR_field_capacity            ,PPF_field_capacity);

      p_bulk_density[layer]    = new CORN::Parameter_number(properties.bulk_density_g_cm3                .ref(layer),PP_bulk_density              ,PPR_bulk_density              ,PPF_bulk_density);
      p_sand[layer]            = new CORN::Parameter_number(properties.sand                              .ref(layer),PP_sand                      ,PPR_sand                      ,PPF_sand);
      p_clay[layer]            = new CORN::Parameter_number(properties.clay                              .ref(layer),PP_clay                      ,PPR_clay                      ,PPF_clay);
      p_silt[layer]            = new CORN::Parameter_number(properties.silt                              .ref(layer),PP_silt                      ,PPR_silt                      ,PPF_silt);
      p_sat_hydraul_cond_m_d[layer] = new CORN::Parameter_number(properties.sat_hydraul_cond_m_d         .ref(layer),PP_sat_hydraul_cond          ,PPR_sat_hydraul_cond          ,PPF_sat_hydraul_cond);
      p_saturation_WC[layer]  = new CORN::Parameter_number(properties.saturation_WC                      .ref(layer),PP_saturation_WC             ,PPR_saturation_WC             ,PPF_saturation_WC);

      p_air_entry_pot[layer]           = new CORN::Parameter_number(properties.air_entry_pot             .ref(layer),PP_air_entry_pot             ,PPR_air_entry_pot             ,PPF_air_entry_pot );
      p_Campbell_b[layer]              = new CORN::Parameter_number(properties.Campbell_b                .ref(layer),PP_Campbell_b                ,PPR_Campbell_b                ,PPF_Campbell_b);
      p_pH[layer]                      = new CORN::Parameter_number(properties.pH                        .ref(layer),PP_pH                        ,PPR_pH                        ,PPF_pH);
      p_cation_exchange_capacity[layer]= new CORN::Parameter_number(properties.cation_exchange_capacity  .ref(layer),PP_cation_exchange_capacity  ,PPR_cation_exchange_capacity  ,PPF_cation_exchange_capacity);
      p_organic_matter[layer]          = new CORN::Parameter_number(properties.organic_matter            .ref(layer),PP_organic_matter            ,PPR_organic_matter            ,PPF_organic_matter);
      p_organic_matter_low[layer]      = new CORN::Parameter_number(properties.organic_matter_low        .ref(layer),PP_organic_matter_low        ,PPR_organic_matter_low        ,PPF_organic_matter_low);
      p_organic_matter_high[layer]     = new CORN::Parameter_number(properties.organic_matter_high       .ref(layer),PP_organic_matter_high       ,PPR_organic_matter_high       ,PPF_organic_matter_high);
   }
}
//______________________________________________________________________________
Soil_parameters::~Soil_parameters()
{
   for (int8 layer = 1; layer <= MAX_soil_horizons ; layer++)
   {
      delete p_layer_thickness[layer];
      delete p_bypass_coef[layer];
      delete p_perm_wilt_point[layer];
      delete p_field_capacity[layer];

      delete p_bulk_density[layer];
      delete p_sand[layer];
      delete p_clay[layer];
      delete p_silt[layer];
      delete p_sat_hydraul_cond_m_d[layer];
      delete p_saturation_WC[layer];

      delete p_air_entry_pot[layer];
      delete p_Campbell_b[layer];
      delete p_pH[layer];
      delete p_cation_exchange_capacity[layer];
      delete p_organic_matter[layer];
      delete p_organic_matter_low[layer];
      delete p_organic_matter_high[layer];
   }
}
//_2014-12-28___________________________________________________________________
bool Soil_parameters::expect_structure(bool for_write)
{
   bool expected = Soil_parameters_class_parent::expect_structure(for_write);    //161025
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_soil);
   expect_parameter(p_override_curve_number);
   expect_parameter(p_user_fallow_curve_number);
   expect_parameter(p_surface_storage_mm);
   expect_parameter(p_steepness);
   expect_parameter(p_slope_length);
   expect_parameter(p_albedo_dry);
   expect_parameter(p_albedo_wet);
   expect_parameter(p_water_vapor_conductance_atmosphere_adj);
   set_current_section   ("CropGro");
      expect_parameter(p_SLPF_CropGro);
   set_current_section(LABEL_soil);
   structure_defined = true;                                                     //120314
   return expected;                                                              //161025
}
//______________________________________________________________________________

