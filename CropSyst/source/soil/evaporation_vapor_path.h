//---------------------------------------------------------------------------
#ifndef evaporation_vapor_pathH
#define evaporation_vapor_pathH
//---------------------------------------------------------------------------
#include "soil/evaporation_abstract.h"
#include "soil/hydrology_finite_diff.h"

//090504  This is obsolete  


/*090106_*/ class Soil_evaporation_with_vapor_path
/*_______*/ : public Soil_evaporation_abstract
/*_______*/ {  // This class works with millimeter
/*_______*/ private:  // references
/*_______*/    mutable const Soil_hydraulic_properties_interface   *soil_hydraulic_props;
                  // Pointer because may change due to tillage etc.. (owned by soil)
                  // Mutable because not an attribute of this evaporation model
                  // which simply responds to the current properties.
/*_______*/        const Soil_layers_interface                 &soil_layers;  // Not const because we adjust the number of effective layers
/*_______*/    not_const Soil_hydrology_finite_difference      &hydrology;    // Owned by the soil class
/*_______*/    float64   &atmospheric_water_potential;                        // kg.s/m^4   Maintained by infiltration model.
/*_______*/ private:  // options/parameters
/*080815_*/    bool      only_one_dryable_layer;   // This is a user model option
/*090417_*/ private:  //
/*090417_*/    bool     first_day;
/*090417_*/    bool     period_evaporation_done;
/*090417_*/    float64  sum_evaporation_mm_ts;             // needs units ?units? I am pretty sure this is for the current wetted period (it is not cummulative evaporation)
/*090417_*/    float64  max_current_period_evaporation;
/*090417_*/    float64  absolute_max_evaporation;
/*090417_*/    float64  old_WC;
/*_______*/ private:
/*_______*/    soil_layer_array64(vapor_conductance);
/*_______*/    soil_layer_array64(vapor_path_length_upper);
/*_______*/    soil_layer_array64(vapor_path_length_lower);
/*_______*/ public :
/*_______*/    Soil_evaporation_with_vapor_path
/*_______*/       (const Soil_layers_interface           &_soil_layers
/*_______*/       ,const Soil_hydraulic_properties_interface   *_soil_hydraulic_props
/*_______*/       ,Soil_hydrology_finite_difference      &_hydrology
/*_______*/       ,float64                               &_atmospheric_water_potential
/*_______*/       ,bool                                   _only_one_dryable_layer
                  );
/*_______*/ public : // processing
               void initialize(uint8 number_real_plus_extended_layer);                                      not_const;
/*_______*/    float64 evaporate
                  (float64 &flux_mm                // modified
/*_______*/       , Seconds time_step
/*_______*/       , Hour    hour_0based
/*_______*/       , float64 pot_evap_mm_day /* mm/day */
/*_______*/       )                                                    not_const;
/*_______*/       // Determine evaporation for the timestep and
/*_______*/       // deducts the water from the soil.
/*_______*/       // Sets up vapor_path
/*_______*/       // Returns actual evaporation in mm
                  // Note that pot_evap_mm_day should be set to 0 if ponding or snow
/*090108_*/    inline void know_soil_hydraulic_properties(const Soil_hydraulic_properties_interface   *_soil_hydraulic_props) mutates_ { soil_hydraulic_props = _soil_hydraulic_props; };
/*090108_*/       // Generally hydraulic properties (initial values provided by the constructor) don't change,
/*090108_*/       // however events may change (perhaps temporarily) the soil properties.
/*_______*/ public : // accessors
/*_______*/    inline float64 get_vapor_conductance(uint8 unsure_layer_or_node)   const { return vapor_conductance[unsure_layer_or_node];}; // I think layer
/*_______*/ private:
/*_______*/    float64  calc_actual
/*_______*/       (
/*_______*/         Seconds time_step   /* May need to be integer */
/*_______*/       , Hour    hour
/*_______*/       , float64 daily_pot_evap_m_ts /* m/hr */
/*_______*/       )                                                        const;
/*_______*/    void
/*_______*/       subtract_water_from_layer
/*_______*/       (
/*_______*/         float64 &evaporation_to_subtract
/*_______*/       , uint8 i   /* appears to be layer but check that it's not node */
/*_______*/       )                                                    not_const;
/*_______*/    float64 calc_vapor_conductance(uint8 i)                     const;
/*_______*/ };

#endif

