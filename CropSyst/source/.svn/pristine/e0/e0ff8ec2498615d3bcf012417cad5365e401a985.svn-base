#ifndef SOIL_INFILTRATION_DARCIAN_H
#define SOIL_INFILTRATION_DARCIAN_H

#include "soil_infiltration.h"

/*_______*/ class Soil_infiltration_cascade_darcian
/*_______*/ : public  Soil_infiltration_cascade
/*_______*/ {
/*_______*/ public:
/*_______*/    Soil_infiltration_cascade_darcian(Soil_base &i_soil);

/*_______*/    virtual float64 infiltrate
/*_______*/    (float64                       management_irrigation
/*_______*/    ,float64                       management_auto_irrigation_concentration
/*991102P*/    ,Pond                         &pond
/*_______*/    ,const CORN::Date             &today
/*990204_*/    ,Dynamic_water_entering_soil  &water_entering_in_intervals_mm
/*990409X*/    ,const Dynamic_float_array    &runon_in_intervals
/*990409X*/    ,Dynamic_float_array          &runoff_in_intervals
/*_______*/    );
//030711_//    Returns the amount of infiltration (m of water depth?)


/*990214X*/ protected: // Darcian working methods
/*981214P*/    float64 infiltration_darcian_cascade
/*990216P*/       (float64    management_irrigation
/*_______*/       ,float64   &additional_runoff); // m any additional computed runoff

/*990214P*/    float64 determine_flow_to_move
/*_______*/       (uint8      sublayer
/*_______*/       ,float64    entering_flow
/*_______*/       ,float64    reservoir
/*_______*/       ,float64    storage_content_limit);
/*990214P*/    float64 determine_flow_out
/*_______*/       (uint8      sublayer
/*_______*/       ,float64    total_flow_to_move
/*_______*/       ,float64   &reservoir);
/*990214P*/    float64 determine_flux  // kg/(m2 sec)
/*_______*/       (uint8      sublayer
/*_______*/       ,float64    water_pot_adj_sublayer);
/*990214P*/    void no_water_entering_soil_case();


/*_______*/ };
#endif

