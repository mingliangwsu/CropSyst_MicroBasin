#ifndef CORN_TIMEWTHR_H
#define CORN_TIMEWTHR_H


050718  I think this is obsolete,
we now have the weather hour and any_timestep classes

/*

   This is a weather class the operates on a partial day time step
   (I.e. hour half hour minute or second)
*/

#include <corn/bsysemod/wthrbase.h>

/*_______*/ class date_time_weather
/*_______*/ : public base_weather
/*_______*/ {
/*_______*/ public:
/*_______*/
/*_______*/    inline date_time_weather
/*_______*/    (const LOC_filename &i_loc_filename
/*_______*/    ,snow_pack_models    snow_pack_model
/*991004_*/    ,float32             i_soil_slope_deg
/*991004_*/    ,float32             i_site_aspect_deg_from_north
/*991004_*/    ,bool                i_forest_vegetation
/*_______*/    ,bool                 generating_data
/*______*/     , CORN_seconds        time_step_seconds
               )
/*_______*/    :base_weather
/*_______*/    (i_loc_filename
/*_______*/    ,snow_pack_model
/*991004_*/    ,i_soil_slope_deg
/*991004_*/    ,i_site_aspect_deg_from_north
/*991004_*/    ,i_forest_vegetation
/*_______*/    ,generating_data
/*______*/     ,time_step_seconds
               )
/*_______*/    {};
/*_______*/ };

#endif
//wthrtime.h
