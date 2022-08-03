#include "Project/Optimization/carbon_sequestration/carbon_sequestration_param.h"
#include "corn/data_source/datarec.h"
#include "corn/string/strconv.hpp"
#define LABEL_percent_N_as_OM          "percent_N_as_OM"
#define LABEL_percent_N_as_NH3         "percent_N_as_NH3"
//______________________________________________________________________________
Carbon_sequestration_optimization_parameters::Carbon_sequestration_optimization_parameters()
: pasture_size_ha(500)
, max_plot_count(10)
, step_plot_count(1)
, min_herd_size(100)
, max_herd_size(500)
, step_herd_size(10)
, max_duration(14)
, step_duration(1)
, grazing_season_duration(250)
, max_recovery_days(21)
,begin_grazing_after_emergence_days(30)
, dry_matter_requirements_animal_units(6.25)
, reserve_biomass_kg_ha(200)
, biomass_return_to_field(80)
, grazing_percent_N_as_OM(50)
, grazing_percent_N_as_NH3(50)
, trampling(true)
, contingency_labeled(STOP_CONTINGENCY)//180106 (NOT_VIABLE_CONTINGENCY)
// valid_int16
,v_max_plot_count                         (max_plot_count                     ,"max_plots"                                      , 10,    1 ,MAXSHORT,1,MAXSHORT  ,"plots"    ,"Maximum number of plots/paddocks (pasture divisions)")
,v_step_plot_count                        (step_plot_count                    ,"step_plots"                                     ,  1,    1 ,MAXSHORT,1,MAXSHORT  ,"plots"    ,"Step number of plots by")
,v_min_herd_size                          (min_herd_size                      ,"min_stocking_rate"                              ,100,    1 ,MAXSHORT,1,MAXSHORT  ,"animals"  ,"Minumum number of animals")
,v_max_herd_size                          (max_herd_size                      ,"max_stocking_rate"                              ,500,    1 ,MAXSHORT,1,MAXSHORT  ,"animals"  ,"Maximum number of animals")
,v_step_herd_size                         (step_herd_size                     ,"step_stocking_rate"                             ,100,    1,1000,1,MAXSHORT      ,"animals"  ,"Step number of animals by")
,v_begin_grazing_after_emergence_days     (begin_grazing_after_emergence_days ,"begin_grazing"                                  , 30,    1 ,365,1,MAXSHORT       ,"days"     ,"Begin grazing after emergence","(delay)")
,v_max_duration                           (max_duration                       ,"max_duration"                                   , 14,    1 ,365,1,MAXSHORT       ,"days"     ,"Maximum grazing duration (consecutive days on the field)")
,v_step_duration                          (step_duration                      ,"step_duration"                                  ,  1,    1 ,365,1,MAXSHORT       ,"days"     ,"Step number of consecutive days on the field by")
,v_grazing_season_duration                (grazing_season_duration            ,"grazing_season_duration"                        ,  1,    1 ,365,1,MAXSHORT       ,"days"     ,"The total number of days animals are present on the pasture")
,v_max_recovery_days                      (max_recovery_days                  ,"max_recovery_days"                              , 21,    1 ,365,1,MAXSHORT       ,"days"     ,"The maximum number of days animals are off the field")

,v_biomass_return_to_field                (biomass_return_to_field            ,"biomass_return_to_field"                        , 80,    1 ,100,1,100            ,"%"        ,"Percent of biomass grazed return to the field as manure")
,v_grazing_percent_N_as_OM                (grazing_percent_N_as_OM            ,LABEL_percent_N_as_OM                            , 50,    1 ,100,1,100            ,"%"        ,"Percent of manure nitrogen as organic matter")
,v_grazing_percent_N_as_NH3               (grazing_percent_N_as_NH3           ,LABEL_percent_N_as_NH3                           , 50,    1 ,100,1,100            ,"%"        ,"Percent of manure nitrogen as ammonia (NH3)")
// valid_float32
,v_pasture_size                           (pasture_size_ha                     ,  UC_hectare      ,"pasture_size"            ,1,500.0 ,1.0 ,999999.0,0.0,999999.0  ,"ha"             ,"Pasture size")
,v_dry_matter_requirements_animal_units   (dry_matter_requirements_animal_units,  UC_unit         ,"dry_matter_requirements" ,3,6.25  ,0.0 ,10.0,0.0,1000.0        ,"kg/animal/day"  ,"Grazing dry matter requirements")
,v_reserve_biomass                        (reserve_biomass_kg_ha               ,  UC_kg_ha        ,"reserve_biomass"         ,2,200   ,0.0 ,10000.0,0.0,30000.0    ,"kg/ha"          ,"Ungrazable (reserve) biomass")
{}
//______________________________________________________________________________
bool Carbon_sequestration_optimization_parameters::setup_structure(CORN::Data_record &data_rec,bool for_write) modification_
{
   data_rec.set_current_section("carbon_sequestration_and_grazing_regimens");
   data_rec.expect_valid_float32  (v_pasture_size);
   data_rec.expect_valid_int16    (v_max_plot_count);
   data_rec.expect_valid_int16    (v_step_plot_count);
   data_rec.expect_valid_int16    (v_min_herd_size);
   data_rec.expect_valid_int16    (v_max_herd_size);
   data_rec.expect_valid_int16    (v_step_herd_size);
   data_rec.expect_valid_int16    (v_begin_grazing_after_emergence_days);
   data_rec.expect_valid_int16    (v_max_duration);
   data_rec.expect_valid_int16    (v_step_duration);
   data_rec.expect_valid_int16    (v_grazing_season_duration);
   data_rec.expect_valid_int16    (v_max_recovery_days);
   data_rec.expect_valid_float32  (v_dry_matter_requirements_animal_units);
   data_rec.expect_valid_float32  (v_reserve_biomass);
   data_rec.expect_valid_int16    (v_biomass_return_to_field);
   data_rec.expect_valid_int16    (v_grazing_percent_N_as_OM);
   data_rec.expect_valid_int16    (v_grazing_percent_N_as_NH3);
   data_rec.expect_enum           ("contingency",contingency_labeled);
   return true;
}
//______________________________________________________________________________
int16 Carbon_sequestration_optimization_parameters::calc_scenarios_required() const
{
/*
   int16 herd_size_combinations =  ((max_herd_size - min_herd_size + 1) / step_herd_size);
   int16 plot_combinations = (max_plot_count / step_plot_count);
   int16 duration_combinations = (max_duration / step_duration);
   int16 estimated_scenario_count
   =  herd_size_combinations
   *  plot_combinations
   *  duration_combinations
   * plots
   // For the single plot, we exclude the set of durations for plots=1 because the animals are kept of the field continuously
   - (herd_size_combinations * plot_combinations)
   ;
*/
   int16 act_scenario_count = 0.0;
      for (int16 herd_size = min_herd_size
       ; (herd_size <= max_herd_size)
       ;herd_size += step_herd_size)
      {
         for (int plots=1; plots <= max_plot_count; plots += step_plot_count)
         {
            int local_max_duration = max_duration;
            if (plots == 1) local_max_duration = 1;
            for (int days_on_field = 1; days_on_field <= local_max_duration; days_on_field += step_duration)
            {
               int recovery_time = (plots-1) * days_on_field;
               if (recovery_time <= max_recovery_days)
                  for (int plot = 1; plot <= plots; plot++)
                     act_scenario_count += 1;
               // else we exclude simulations where the number
               // of days the animals are off the field exceeds the maximum
            }
         }
      }
   return act_scenario_count;
}
//______________________________________________________________________________
void Carbon_sequestration_optimization_parameters::compose_scenario_name
(std::string &scenario_name,int16 herd_size,int16 plots,int16 days_on_field,int16 plot) const
{
   scenario_name.assign("herd=");
   char int_buf[10];
   CORN::int16_to_cstr(herd_size,int_buf,10);
   int int_buf_len = strlen(int_buf);
   for (int i = 1; i < (4 - int_buf_len); i++)
       scenario_name.append("0");  // Use 0 fill so the names can be sorted
   scenario_name.append(int_buf);
   scenario_name.append("_");
   scenario_name.append("plots=");
   CORN::int16_to_cstr(plots,int_buf,10);
    int_buf_len = strlen(int_buf);
   for (int i = 1; i < (3 - int_buf_len); i++)
       scenario_name.append("0");
   scenario_name.append(int_buf);
   if (plots >= 1)
   {  // In the case of a single plot we dont have durations
      scenario_name.append("_");
      scenario_name.append("days=");
      CORN::int16_to_cstr(days_on_field,int_buf,10);
       int_buf_len = strlen(int_buf);
      for (int i = 1; i < (3 - int_buf_len); i++)
          scenario_name.append("0");
      scenario_name.append(int_buf);

      scenario_name.append("_");
      scenario_name.append("plot=");
      CORN::int16_to_cstr(plot,int_buf,10);
      int_buf_len = strlen(int_buf);
      for (int i = 1; i < (2 - int_buf_len); i++)
          scenario_name.append("0");
      scenario_name.append(int_buf);
   }
}
//______________________________________________________________________________
