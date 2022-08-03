#include "seeding_param.h"
#include "corn/data_source/datarec.h"
#define NoAltFieldName 0
#define NotYetSubsection "NotYetSubsection"

CORN::Parameter_properties_literal PP_rate_seeds    = {"seeding_rate"   ,NoAltFieldName,NotYetSubsection,"Seed application rate" ,"","",UC_count_per_m2,"seeds/m²"};
CORN::Parameter_properties_literal PP_emergence_rate= {"emergence_rate" ,NoAltFieldName,NotYetSubsection,"Emergence rate"        ,"","",UC_percent};
CORN::Parameter_properties_literal PP_sowing_depth  = {"sowing_depth"   ,NoAltFieldName,NotYetSubsection,"Sowing depth"          ,"","",UC_cm};

CORN::Parameter_range PPR_rate_seeds      = {    1,1000.0,  0.0,1000000.0};
CORN::Parameter_range PPR_emergence_rate  = {  5.0, 100.0,  0.0, 100.0  };
CORN::Parameter_range PPR_sowing_depth    = {  0.0,  50.0,  0.0, 100.0  };

CORN::Parameter_format PPF_rate_seeds     = {8,0};
CORN::Parameter_format PPF_emergence_rate = {8,1};
CORN::Parameter_format PPF_sowing_depth   = {8,2};

//______________________________________________________________________________
Seeding_parameters::Seeding_parameters()
: rate_seeds_m2         (300.0)               // This is for wheat (guess RLN)
, emergence_rate_percent(100.0)
, sowing_depth_cm       (5.0)
, p_rate_seeds    (rate_seeds_m2          ,PP_rate_seeds    ,PPR_rate_seeds      ,PPF_rate_seeds)
, p_emergence_rate(emergence_rate_percent ,PP_emergence_rate,PPR_emergence_rate  ,PPF_emergence_rate)
, p_sowing_depth  (sowing_depth_cm        ,PP_sowing_depth  ,PPR_sowing_depth    ,PPF_sowing_depth)
/*180326
, v_rate_seeds    (rate_seeds_m2          ,UC_count_per_m2  ,"seeding_rate"   ,0,300.0,    1,1000.0,  0.0,1000000.0  ,"seeds/m²","Seed application rate")
, v_emergence_rate(emergence_rate_percent ,UC_percent       ,"emergence_rate" ,1, 50.0,  5.0,100.0,  0.0, 100.0  ,"%","Emergence rate")
, v_sowing_depth  (sowing_depth_cm        ,UC_cm            ,"sowing_depth"   ,2,  5.0,  0.0,50.0,  0.0, 100.0  ,"cm","Sowing depth")
*/
{}
//______________________________________________________________________________
Seeding_parameters::Seeding_parameters(const Seeding_parameters &original)
: rate_seeds_m2            (original.rate_seeds_m2)               // This is for wheat (guess RLN)
, emergence_rate_percent   (original.emergence_rate_percent)
, sowing_depth_cm          (original.sowing_depth_cm)
, p_rate_seeds    (rate_seeds_m2          ,PP_rate_seeds    ,PPR_rate_seeds      ,PPF_rate_seeds)
, p_emergence_rate(emergence_rate_percent ,PP_emergence_rate,PPR_emergence_rate  ,PPF_emergence_rate)
, p_sowing_depth  (sowing_depth_cm        ,PP_sowing_depth  ,PPR_sowing_depth    ,PPF_sowing_depth)
/*180326
, v_rate_seeds    (rate_seeds_m2          ,UC_count_per_m2  ,"seeding_rate"   ,0,300.0,    1,1000.0,  0.0,1000000.0  ,"seeds/m²","Seed application rate")
, v_emergence_rate(emergence_rate_percent ,UC_percent       ,"emergence_rate" ,1, 50.0,  5.0,100.0,  0.0,    100.0  ,"%","Emergence rate")
, v_sowing_depth  (sowing_depth_cm        ,UC_cm            ,"sowing_depth"   ,2,  5.0,  0.0, 50.0,  0.0,    100.0  ,"cm","Sowing depth")
*/
{  rate_seeds_m2          =  (original.rate_seeds_m2);
   emergence_rate_percent=   (original.emergence_rate_percent);
   sowing_depth_cm       =   (original.sowing_depth_cm);
}
//______________________________________________________________________________
void Seeding_parameters::setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_
{
   data_rec.expect_parameter(p_rate_seeds);
   data_rec.expect_parameter(p_emergence_rate);
   data_rec.expect_parameter(p_sowing_depth);
/*180326
   data_rec.expect_valid_float32(v_rate_seeds);
   data_rec.expect_valid_float32(v_emergence_rate);
   data_rec.expect_valid_float32(v_sowing_depth);
*/
}
//______________________________________________________________________________
