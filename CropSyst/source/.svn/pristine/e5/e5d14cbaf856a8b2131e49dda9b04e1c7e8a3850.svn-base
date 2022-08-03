#include "soilbase.h"
#include <math.h>


/*_______*/ // This function returns the aoccomodated flow (in) (this can be negative)
/*990214P*/ float32 soil_base::determine_flow_to_move
/*_______*/ (uint8   sublayer
/*_______*/ ,float32 entering_flow
/*_______*/ ,float32 reservoir
/*_______*/ ,float32 storage_content_limit
/*_______*/ )
/*_______*/ {
/*_______*/   float32 non_accom_flow = 0.0 ; // m
/*_______*/   float32 unstored_flow = 0.0; // m
/*_______*/	  float32 flow_and_reservoir = entering_flow + reservoir; // m
/*_______*/   float32 accomodatable_content = storage_content_limit - water_content[sublayer];
/*_______*/   float32 accomodatable_flow = accomodatable_content * thickness[sublayer]; // m
/*_______*/   if (accomodatable_flow > 0.0)
/*_______*/   {   non_accom_flow =
/*_______*/       (flow_and_reservoir > accomodatable_flow)
/*_______*/       ? flow_and_reservoir - accomodatable_flow
/*_______*/       :  0.0;
/*_______*/   }
/*_______*/   else // The water content is above the max storage at water pot -10 J/kg
/*_______*/   {
/*_______*/       unstored_flow = -accomodatable_flow;
/*_______*/       non_accom_flow = flow_and_reservoir ; // thus down flow will increase for next layer
/*_______*/   };
/*_______*/   return non_accom_flow + unstored_flow;
/*_______*/ };
/*_______*/
/*990214P*/ float32 soil_base::determine_flow_out
/*_______*/ (uint8 sublayer
/*_______*/ ,float32  total_flow_to_move
/*_______*/ ,float32 &reservoir
/*_______*/ )
/*_______*/ {
/*_______*/    float32 out_flow = 0.0;   // m
/*_______*/
/*_______*/    float32 out_flow_max_sublayer = // m
/*_______*/    86.4 * gravitation_const * get_sat_hydraul_cond_kg_s_m3(sublayer);
/*_______*/
/*_______*/    if (total_flow_to_move < out_flow_max_sublayer)// We can move the remaining flow out
/*_______*/    {
/*_______*/       out_flow    = total_flow_to_move;
/*_______*/       reservoir   = 0.0;    //back flow or flow up
/*_______*/    }
/*_______*/    else
/*_______*/    {
/*_______*/       out_flow    = out_flow_max_sublayer;
/*_______*/       reservoir   = total_flow_to_move - out_flow_max_sublayer;
/*_______*/    };
/*_______*/    return out_flow;
/*_______*/ };
/*_______*/
/*990214P*/ float32 soil_base::determine_flux  // kg/(m2 sec)
/*_______*/ (uint8      sublayer
/*_______*/ ,float32    water_pot_adj_sublayer
/*_______*/ )
/*_______*/ {
/*_______*/    return (((water_pot_adj_sublayer - water_pot[sublayer])
/*_______*/                      / thickness[sublayer]) -  gravitation_const)
/*_______*/                      * get_hydraulic_conductivity(sublayer);
/*_______*/ };
/*_______*/
/*990214P*/ void soil_base::no_water_entering_soil_case()
/*_______*/ {
/*_______*/    // only move water already in the soil
/*_______*/    soil_sublayer_array32(local_water_flux);
/*_______*/    local_water_flux[0]  = 0;
/*_______*/

/*_______*/    for (uint8 sublayer = 1; sublayer <= get_num_sublayers_eff(); sublayer++)
/*_______*/    {
/*_______*/       //  This should be OK water potentials for num_sublayers_eff+1
/*_______*/       //  is set up in previous mass balance iteration.
/*_______*/       //  by convetion flow down is negative (different from above)
/*_______*/

/*990106P*/       local_water_flux[sublayer] = determine_flux(sublayer,water_pot[sublayer+1]);

/*_______*/       if (sublayer < get_num_sublayers_eff()) // last layer has no limit.
/*_______*/          if (local_water_flux[sublayer] < 0.0)
/*_______*/          {
/*_______*/             float32 movable_content = CORN_must_be_greater_or_equal_to
/*_______*/                ((water_content[sublayer] - get_field_capacity_volumetric(sublayer))
/*_______*/                ,0.0);
/*_______*/
/*_______*/             float32 max_flux_out = CORN_min
/*_______*/                 (- (movable_content / 86.4 *  get_thickness(sublayer))
/*_______*/                  + local_water_flux[sublayer-1]
/*_______*/                 ,+ ((get_saturation_water_content(sublayer+1) - get_water_content(sublayer+1) )
/*_______*/                     / 86.4 *  get_thickness(sublayer+1)));
/*_______*/             if (is_approximately(max_flux_out,0.0,0.00000000001))
/*_______*/                  max_flux_out = 0.0;
/*_______*/
/*_______*/             // Take the value closest to zero ( both should be neg or 0.0).
/*_______*/             local_water_flux[sublayer] = CORN_max(local_water_flux[sublayer],max_flux_out);

/*_______*/          }
/*_______*/          else
/*_______*/          {
/*_______*/             float32 movable_content = CORN_must_be_greater_or_equal_to(
/*_______*/                (water_content[sublayer+1] - get_field_capacity_volumetric(sublayer+1))
/*_______*/                ,0.0);
/*_______*/             float32 max_flux_in = CORN_min
/*_______*/                 ( + ((get_saturation_water_content(sublayer) - water_content[sublayer] )
/*_______*/                      / 86.4 *  get_thickness(sublayer))
/*_______*/                   + local_water_flux[sublayer-1]
/*_______*/                 , + (movable_content / 86.4 *  get_thickness(sublayer+1)));
/*_______*/
/*_______*/             if (is_approximately(max_flux_in ,0.0,0.00000000001))
/*_______*/                   max_flux_in = 0.0;
/*_______*/             // Take the value closest to zero ( both should be pos. or 0.0).
/*_______*/               local_water_flux[sublayer] = min(local_water_flux[sublayer],max_flux_in);

/*_______*/          };

/*_______*/   };
/*_______*/
/*_______*/   for (uint8 sublayer = 1; sublayer <= get_num_sublayers_eff() ; sublayer++)
/*_______*/   { // Do it for real now:
/*_______*/       float32 change_in_water_content = (-local_water_flux[sublayer-1] +
/*_______*/             local_water_flux[sublayer]) * 86.4 / thickness[sublayer];
/*990106p*/       water_content[sublayer] += change_in_water_content ;
/*_______*/       water_flux[sublayer] = local_water_flux[sublayer];
/*_______*/    };
/*_______*/ };

/*981214C*/ float32 soil_base::infiltration_darcian_cascade
/*990216C*/ ( float32 management_irrigation
/*_______*/ , float32 &additional_runoff // m any additional computed runoff
/*_______*/ )
/*_______*/ {
//*_______*/    down_flow    : REAL;  {m3 water/m2 soil (m) }
//*_______*/    sublayer     : INTEGER;
//*_______*/    flow_out : REAL;
/*_______*/    soil_sublayer_array32(reservoir); // m
//*990106p*/    previous_layer_down_flow : REAL;
//*990106p*/    flow_to_move : REAL;
//*_______*/    hydraulic_conductance : EXTENDED;
//*_______*/    unused_phiu : EXTENDED;
//*_______*/    unused_dwdp : EXTENDED;
///*_______*/    storage_content_at10J_kg   : REAL;
//*_______*/    water_pot_adjacent_sublayer : REAL;
//*_______*/
//*_______*/    excess_flux : REAL;
//*_______*/    excess_content  : REAL;
//*_______*/

///*_______*/    balance_drainage = 0.0;  // already initialized in infiltrate()
///*_______*/    reported_drainage = 0.0; // already initialized in infiltrate()
///*_______*/    runoff = 0.0;            // already initialized in infiltrate()
/*_______*/
/*990212X*/    soil_sublayer_array32(old_water_content);
/*990214_*/    copy_sublayer_array(old_water_content,water_content);
/*_______*/    if (water_entering_soil > 0.0)
/*_______*/    {
/*_______*/       float32 previous_layer_down_flow = water_entering_soil;
/*_______*/       float32 down_flow = water_entering_soil;  // m3 water/m2 soil (m)
/*_______*/       for (uint8 sublayer = 1 ; sublayer <= get_num_sublayers_eff(); sublayer++)
/*_______*/       {  // some optimized variables
/*990214_*/          float32 saturation_water_content_sl = get_saturation_water_content(sublayer);
/*990214_*/          float32 thickness_sl = get_thickness(sublayer);
                     float32 air_entry_pot_sl = get_air_entry_pot(sublayer);
                     float32 b_sl   =  get_soil_b(sublayer);
/*_______*/          // Determine the flow what will fill to water pot -10 J/kg.
/*_______*/          float32 storage_content_at10J_kg = //  at water pot -10 J/kg
/*_______*/             saturation_water_content_sl
/*_______*/               * pow((-10.0 /air_entry_pot_sl ) ,-1.0/ b_sl);
/*_______*/
/*_______*/          float32 flow_to_move = // m
/*_______*/             determine_flow_to_move(sublayer,down_flow,0.0,storage_content_at10J_kg);
/*_______*/
/*_______*/          float32 flow_out = // m
/*_______*/             determine_flow_out(sublayer,flow_to_move,reservoir[sublayer]);
/*990106p*/          water_flux[sublayer] =  -flow_out / 86.4;  // {kg /(m2 sec) (neg. for downflow)}
/*_______*/
/*_______*/          if (reservoir[sublayer] > 0.0)
/*_______*/          {
/*_______*/             float32 req_water_content_to_saturate = (saturation_water_content_sl - storage_content_at10J_kg);
/*_______*/             float32 reservoir_content = reservoir[sublayer] / thickness_sl; // m3/m3
/*_______*/             if (req_water_content_to_saturate > reservoir_content)
/*_______*/                water_content[sublayer] =  (storage_content_at10J_kg + reservoir_content);
/*_______*/             else
/*_______*/             {
/*_______*/                water_content[sublayer] = saturation_water_content_sl;
/*_______*/                reservoir[sublayer] -= (req_water_content_to_saturate * thickness_sl);
/*_______*/             };
/*_______*/          }
/*_______*/          else
/*_______*/             water_content[sublayer] +=
/*990106p*/                ((previous_layer_down_flow - flow_out) / thickness_sl);
/*_______*/          // This may exceed saturation
/*_______*/          // setup for next layer:
/*990106p*/          down_flow = flow_out;
/*990106p*/          previous_layer_down_flow = flow_out;
/*_______*/       };
/*_______*/
/*_______*/       if (get_water_table_encountered())
/*_______*/       { // If water table then drainage is added to back flow of num_sublayers_eff
/*990106p*/          reservoir[get_num_sublayers_eff()] += down_flow;
/*_______*/          balance_drainage = 0.0;
/*_______*/       };
/*_______*/
/*_______*/       float32 up_flux = determine_flux(get_num_sublayers_eff(),water_pot[get_num_sublayers_eff()+1]);
/*_______*/       float32 up_flow = (up_flux > 0)   // {m3 water/m2 soil (m) }
/*_______*/       ? up_flux * 86.4
/*_______*/       : 0.0;
/*_______*/
/*990106p*/       float32 previous_layer_up_flow = up_flow;
/*_______*/       for (uint8 sublayer = get_num_sublayers_eff(); sublayer >= 1; sublayer--)
/*_______*/       {
/*_______*/          float32 flow_out = determine_flow_to_move
/*_______*/          (sublayer,up_flow,reservoir[sublayer], get_saturation_water_content(sublayer));
/*990106p*/
/*990106p*/          water_flux[sublayer] += previous_layer_up_flow / 86.4;  // kg/(m2 sec)
/*_______*/
/*990106p*/          water_content[sublayer] +=
/*_______*/          ((up_flow + reservoir[sublayer] - flow_out) / thickness[sublayer]);
/*990106p*/          up_flow = flow_out;
/*990106p*/          previous_layer_up_flow = up_flow;
/*_______*/       };
/*_______*/       additional_runoff = up_flow; // m

/*_______*/    }
#ifdef TEMP_DISABLED
// Causing problems with next day
/*_______*/    else
/*_______*/       no_water_entering_soil_case();
#endif
/*_______*/
/*_______*/    for (uint8 sublayer = 1 ; sublayer <= get_num_sublayers_eff(); sublayer++)
/*_______*/    {
/*990214X*/       water_pot[sublayer] = waterpotential(sublayer);
/*980604S*/       water_pot[sublayer+1] = water_pot[sublayer];
/*_______*/    };

               // WARNING this needs to be for time step, because
               // this is being called within finite diff time step control!!!!
               // Ie. increment drainage and change secs per day to time_step
/*_______*/       balance_drainage = - seconds_per_day*(mm_to_m(water_flux[get_num_sublayers_eff()])); //{time_step};
/*990214_*/       uint8 leaching_sublayer = sublayer_at(get_leaching_depth(),false);
/*_______*/       reported_drainage =  override_leaching_depth
/*990214_*/       ? - seconds_per_day*(mm_to_m(water_flux[leaching_sublayer])) //{time_step}
/*_______*/       : balance_drainage;
/*_______*/
/*980724_*/       chemical_transport_and_exchange
/*_______*/       (//070117 true,
/*_______*/        get_num_sublayers_eff()
/*_______*/       ,old_water_content
/*_______*/       ,water_content // new_water_content
/*_______*/       ,water_entering_soil + management_irrigation  // Warning check should be: total water entering (irrig + precip)
/*_______*/       ,water_entering_soil
/*990213x*/       ,override_leaching_depth
/*990213x*/       ,leaching_sublayer
/*_______*/       );

/*990214_*/    return water_entering_soil - additional_runoff; // <- Check this with Claudio
/*_______*/ };

//060306 264 lines

