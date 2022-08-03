void Soil_infiltration_XXXXXX::infiltrate
(Infiltration_model     infiltration_mode
,float64                management_irrigation
,float64                management_auto_irrigation_concentration
,Pond                  &pond                                                     //991201
,const CORN_date       &today
,Dynamic_water_entering_soil &water_entering_in_intervals_mm                     //990204
,const Dynamic_float_array &runon_in_intervals                                   //990409
,Dynamic_float_array &runoff_in_intervals                                        //990409
)
{
      float64 additional_runoff = 0.0;                                           //990214
      infiltration = infiltration_darcian_cascade(management_irrigation,additional_runoff);
      add_runoff_from_infiltration(additional_runoff);                           //990214
};
//_1999-02-14______________________________________________________infiltrate__/
