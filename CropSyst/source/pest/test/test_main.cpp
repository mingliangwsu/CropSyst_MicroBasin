#include "CS_suite/simulation/CS_simulation_control.h"
#include "CS_suite/simulation/CS_simulation_engine.h"
#include "CS_suite/application/CS_arguments.h"
#include "pest/population_insect.h"
#include "common/weather/any_timestep/temperature_est.h"

struct Temperature
{ float32 max;
  float32 min; };

extern Temperature temperature[];
using namespace CropSyst;
//______________________________________________________________________________
class Test_simulation
: public extends_ CS::Simulation_engine
{
   //---------------------------------------------------------------------------
   class Simulation_control
   : public extends_ CS::Simulation_control
   {
    public:
      inline Simulation_control(nat8  major,nat8  release,nat8  minor)
         : CS::Simulation_control(major,release,minor)
         {}
   inline virtual Common_operation *get_operation                                //030808
      (const char *operation_type_str
      ,const std::string &operation_ID
      ,modifiable_
         CORN::OS::File_name                                                     //150523_120913
         &operation_filename // the fully qualified operation filename may be returned (to be output to the schedule)
      ,int32 resource_set_ID,bool &relinquish_op_to_event) { return 0; }
   };
   //---------------------------------------------------------------------------
 public:
   CropSyst::Population_insect    *population; // dont delete given to CS::Simulation_engine
   provided_ Simulation_control         sim_control;
   Air_temperature_average    air_temperature_avg;
   Air_temperature_minimum    air_temperature_min;
   CORN::OS::Directory_name_concrete scenario_directory;
   std::string model_name;
   std::wstring control_file_name_unused;
 private:
   Temperature_estimator         temperature_estimator_hourly;
   CORN::Dynamic_array<float32>  temperature_by_hour;
 public:
   inline Test_simulation(const CropSyst::Parameters_insect  &_parameters)
      : CS::Simulation_engine()
      , population(new CropSyst::Population_insect
         (_parameters
         ,true
         , today
         ,air_temperature_avg
         ,air_temperature_min
         ,temperature_by_hour
         ,temperature_by_hour // for this test we dont have soil temperature
         ))
      , sim_control(0,0,0)
      , air_temperature_avg()
      , air_temperature_min()
      , scenario_directory() // CWD
      , temperature_by_hour(24,0,0)
      , model_name("insect")
      , temperature_estimator_hourly(60)
      {
         append(population);  // add insect population submodel
      }
 public: // CS::Simulation engine overrides
   inline virtual const CORN::OS::Directory_name &get_output_directory_name() const { return scenario_directory; }
   inline virtual const std::string &get_model_name()                      const { return model_name; }
   virtual CORN::Data_record &provide_scenario_data_rec()             provision_ //160119
      { return sim_control; }
      // Simply returning sim_control.  It is actually not used in this model.
   virtual nat16 find_and_compose_scenario()                           provision_ //160119
      { return 0;} // the scenario parameter are hard coded for this test
 protected:
   inline virtual const CORN::OS::Directory_name &provide_scenario_directory_name() provision_ { return scenario_directory; }
   inline virtual const std::wstring &get_control_file_name_unqual()       const { return control_file_name_unused; }
   inline virtual Common_operation *get_operation                                //030808
      (const char *operation_type_str
      ,const std::string &operation_ID
      ,modifiable_
         CORN::OS::File_name                                                     //150523_120913
         &operation_filename // the fully qualified operation filename may be returned (to be output to the schedule)
      ,int32 resource_set_ID,bool &relinquish_op_to_event)
      { return 0; }
 public: // Simulation element implementations
   virtual bool start()                                            modification_
      {  temperature_estimator_hourly.reset
            (temperature[1].max
            ,temperature[1].max
            ,temperature[1].min
            ,temperature[2].min);
         return true;
      }
   virtual bool start_day()                                        modification_
      {  nat16 doy = today.get_DOY();
         air_temperature_avg.set_Celcius((temperature[doy].max+temperature[doy].min)/2.0,CORN::measured_quality);
         air_temperature_min.set_Celcius(temperature[doy].min,CORN::measured_quality);
         temperature_estimator_hourly.get_temperature_by_interval(temperature_by_hour);
         return CS::Simulation_engine::start_day();
      }
   virtual bool end_day()                                         modification_
      {
         CORN::Date tomorrow(today); tomorrow.inc();
         CORN::Date day_after_tomorrow(tomorrow); day_after_tomorrow.inc();
         nat16 doy_tomorrow            = tomorrow.get_DOY();
         nat16 doy_day_after_tomorrow  = day_after_tomorrow.get_DOY();
         temperature_estimator_hourly.set_max_today_min_tomorrow
            (temperature[doy_tomorrow].max,temperature[doy_day_after_tomorrow].min);
         return CS::Simulation_engine::end_day();
      }
public:
   inline virtual bool find_and_load_simulation_control()           modification_{ return true;}
   virtual const       Simulation_control &ref_simulation_control_const()  const { return sim_control; }//160225
   virtual const std::wstring &get_scenario_file_name_extension()          const { return L"none"; };//160114
};
//______________________________________________________________________________
class Test_simulation_with_output
: public extends_ Test_simulation
{
   std::ofstream population_file;
   std::ofstream feeding_file;
   #ifdef MATCH_EXCEL_VERSION

   float64 live_adults_pre_season_yesterday;
   #endif
 public:
   Test_simulation_with_output(const CropSyst::Parameters_insect  &_parameters)
      : Test_simulation(_parameters)
      , population_file("population.dat")
      , feeding_file   ("feeding.dat")
      #ifdef MATCH_EXCEL_VERSION
      , live_adults_pre_season_yesterday(0)
      #endif
      {}
   virtual bool start()                                            modification_
      {
         population_file << "Year	DOY	Taverage	Degree-days	Pre Adults	Laid Eggs	Live Eggs	Live L1	Live L2	Live L3	Live L4	Live Pupa	Post Adults	Diapause	Daily Feed	Total Larvae" << std::endl;
         feeding_file << "			Abundance				feeding rate (mm2/larvae)				Total	LAI Consumed" << std::endl;
         feeding_file << "Year	DOY	Tavg	Live L1	Live L2	Live L3	Live L4	fr.Larva1	fr.Larva2	fr.Larva3	fr.Larva4	Feeding" << std::endl;
         return Test_simulation::start();
      }
   #ifdef MATCH_EXCEL_VERSION
   virtual bool start_day()                                        modification_
      {
         bool started = Test_simulation::start_day();
         const Population_insect::Adult_pre_season *adult_pre_season = dynamic_cast<const Population_insect::Adult_pre_season *>(population->get_stage(adult_preseason_stage));
         live_adults_pre_season_yesterday = (adult_pre_season) ? adult_pre_season->total_live() : 0.0;
         return started;
      }
   #endif
   virtual bool end_day()                                          modification_
      {
         bool ended = Test_simulation::end_day();
         ended &= population->dump(population_file,feeding_file);                        //151229
         return ended;
      }
};
//______________________________________________________________________________
namespace CropSyst
{
extern struct Parameters_insect parameters_Oulema_melanopus;
}
int main (int argc, char *argv[])
{
   Test_simulation_with_output insect_simulation(CropSyst::parameters_Oulema_melanopus);
   // Test run for 2 year (the actual years are irrelevent for this test).
   insect_simulation.sim_control.start_date.set_YD(0,1);
   insect_simulation.sim_control.stop_date .set_YD(30,365);
   insect_simulation.run();
}
//______________________________________________________________________________
//	Tmax		Tmin
Temperature temperature[] =
{
{7.8,	4.39}       // previous day
,{5.83,	-0.23}
,{6.8,	0.27}
,{6.05,	-1.92}
,{3.97,	-2.8}
,{3.91,	-3.51}
,{1.01,	-5.7}
,{-3.56,	-10.8}
,{-4.12,	-11.96}
,{-5.36,	-11.71}
,{-3.12,	-10.91}
,{-3.8,	-11.55}
,{-0.81,	-10.78}
,{3.44,	-2.92}
,{2.11,	-1.77}
,{3.55,	-0.86}
,{2.92,	-4.32}
,{3.43,	-2.38}
,{2.17,	-6.34}
,{-0.83,	-9.09}
,{-2.02,	-11.15}
,{-1.15,	-9.66}
,{-1.2,	-9.41}
,{-1.99,	-9.65}
,{0.46,	-6.51}
,{1.08,	-7.22}
,{-3.01,	-11.05}
,{-5.92,	-13.91}
,{-11.31,	-19.44}
,{-10.06,	-20.51}
,{-11.5,	-20.81}
,{-6.71,	-19.21}
,{-0.9,	-11.93}
,{0.32,	-5.37}
,{2.04,	-1.82}
,{3.69,	0.89}
,{4.26,	-1.05}
,{6.68,	-0.73}
,{4.85,	0.47}
,{5.24,	-0.92}
,{4.88,	-2.1}
,{5.67,	-2.83}
,{3.54,	-3.74}
,{3.17,	-3.96}
,{1.39,	-3.59}
,{-1.17,	-4.56}
,{-4.04,	-7.58}
,{-1.16,	-8.07}
,{1.28,	-6.02}
,{2.67,	-1.34}
,{9.52,	1.69}
,{10.4,	3.31}
,{7.37,	2.17}
,{7.2,	-0.85}
,{8.07,	-0.91}
,{7.3,	-1.5}
,{10.07,	-0.14}
,{12.76,	1.51}
,{10.8,	4.38}
,{10.88,	7.17}
,{10.88,	7.17}
,{12.09,	-0.97}
,{11.73,	1.71}
,{10.21,	2.04}
,{6.62,	-0.18}
,{4.39,	-2.78}
,{1.82,	-4.99}
,{3.13,	-4.17}
,{4.41,	-1.69}
,{4,	-2.6}
,{9.16,	-0.62}
,{6.55,	-0.21}
,{4.49,	-2.74}
,{5.32,	0.16}
,{7.77,	0.12}
,{3.8,	-2.19}
,{3.89,	-4.94}
,{7.61,	-1.76}
,{8.06,	1.51}
,{7.51,	-0.52}
,{9.64,	-0.38}
,{10.16,	0.36}
,{10.41,	1.22}
,{6.67,	-0.98}
,{6.43,	-1.01}
,{6.39,	-1.39}
,{7.19,	-0.22}
,{6.1,	-0.41}
,{8.43,	-0.82}
,{8.06,	0.1}
,{6.82,	-2.44}
,{7.28,	-1.22}
,{6.47,	-0.96}
,{9.99,	-1.19}
,{11.95,	-0.59}
,{13.7,	1.87}
,{15.06,	3.93}
,{9.02,	1.58}
,{8.48,	-2.11}
,{11.74,	-0.55}
,{12.02,	1.77}
,{9.38,	0.41}
,{13.99,	0.66}
,{16.6,	1.54}
,{20.58,	4.42}
,{19.48,	7.88}
,{12.89,	3.26}
,{20.35,	1.19}
,{21.79,	6.66}
,{21.24,	7.35}
,{17.23,	7.44}
,{15.2,	4.74}
,{15.66,	6.96}
,{18.81,	4.19}
,{19.32,	6.66}
,{15,	7.33}
,{17.26,	4.41}
,{23.14,	5.68}
,{25.04,	11.34}
,{24.76,	11.81}
,{17.72,	4.9}
,{11.93,	2.53}
,{20.94,	2.84}
,{19.96,	9.86}
,{21.31,	8.19}
,{24.5,	7.49}
,{26.28,	9.92}
,{20.37,	5.88}
,{16.45,	4.27}
,{16.67,	7.68}
,{11.79,	2.95}
,{15.87,	3.19}
,{18.07,	2.94}
,{18.79,	5.49}
,{17.63,	7.05}
,{17.03,	6.57}
,{13.5,	3.22}
,{11.32,	3.15}
,{18.52,	1.9}
,{21.41,	7.68}
,{20.95,	10.01}
,{22.3,	9.58}
,{21.53,	11.27}
,{15.44,	6.18}
,{12.61,	2.87}
,{11.27,	3.32}
,{8.94,	2.27}
,{10.26,	2.49}
,{11.27,	3.22}
,{14.06,	4.45}
,{15.55,	5.59}
,{16.23,	7.81}
,{17.22,	6.29}
,{14.3,	5.82}
,{11.44,	0.93}
,{12.72,	2.48}
,{15.56,	3.07}
,{16.18,	6.37}
,{15.37,	4.15}
,{20.34,	4.31}
,{24.73,	7.25}
,{21.39,	9.74}
,{20.76,	9.02}
,{20.52,	7.21}
,{17.27,	8.13}
,{15.22,	5.06}
,{18.7,	3.31}
,{16.74,	5.92}
,{23.17,	6.74}
,{19.15,	8.65}
,{20.93,	7.86}
,{23.02,	9.85}
,{24.39,	10.13}
,{24.42,	12.12}
,{18.45,	10.01}
,{18.04,	7.44}
,{21.45,	5.96}
,{18.95,	9.84}
,{16.38,	6.18}
,{17.34,	4.08}
,{21.91,	8.21}
,{20.92,	8.45}
,{21.51,	4.94}
,{25.29,	4.96}
,{25.41,	9.39}
,{21.35,	6.56}
,{20.29,	4.49}
,{21.36,	4.93}
,{22.75,	6.42}
,{27.61,	6.7}
,{30.1,	13.3}
,{28.58,	15.07}
,{23.43,	9.12}
,{23.99,	7.39}
,{21.4,	6.34}
,{23.16,	8.83}
,{21.92,	10.05}
,{23.94,	7.45}
,{25.12,	8.16}
,{23.71,	6.96}
,{25.25,	8.94}
,{23.67,	7.3}
,{27.38,	12.82}
,{30.69,	10.83}
,{35.73,	13.56}
,{28.37,	12.23}
,{28.72,	10.42}
,{29.04,	13.21}
,{30.15,	13.42}
,{30.72,	12.77}
,{32.78,	14.87}
,{28.13,	11.57}
,{29.44,	12.28}
,{32.39,	10.99}
,{26.65,	9.1}
,{26.31,	6.85}
,{21.8,	3.71}
,{24.49,	5.5}
,{21.87,	4.62}
,{23.02,	7.26}
,{25.61,	6.29}
,{27.91,	5.6}
,{27.3,	9.6}
,{29.35,	7.27}
,{30.53,	9.99}
,{29.03,	12.17}
,{27.97,	11.14}
,{27.59,	10.75}
,{24.77,	6.78}
,{21.36,	6.13}
,{21.1,	4.78}
,{16.87,	3.76}
,{21.94,	1.46}
,{23.08,	7.03}
,{24.13,	7.51}
,{24.76,	7.25}
,{24.91,	8.88}
,{23.58,	6.61}
,{22.91,	2.52}
,{26.15,	4.55}
,{20.2,	6.9}
,{19.35,	0.82}
,{20.37,	3.28}
,{20.32,	3.31}
,{17.93,	3.79}
,{19.78,	4.04}
,{18.16,	3.93}
,{20.1,	2.78}
,{25.9,	8.4}
,{28.38,	9.21}
,{28.75,	14.05}
,{23.39,	10.63}
,{24.26,	7.1}
,{27.02,	7.11}
,{26.08,	9.58}
,{25.53,	10.39}
,{22.58,	8.94}
,{17.4,	4.87}
,{21.87,	3.59}
,{21.86,	6.2}
,{24.11,	7.66}
,{24,	7.44}
,{18.83,	6.71}
,{17.85,	5.8}
,{15.53,	3.81}
,{14.79,	2.14}
,{15.54,	4.57}
,{18.96,	7.23}
,{19.53,	5.36}
,{20.88,	3.02}
,{25.56,	4.54}
,{26.29,	10.4}
,{19.91,	9.25}
,{26.02,	6.68}
,{20.03,	8.9}
,{18.86,	4.93}
,{22.13,	3.34}
,{25.8,	5.68}
,{23.14,	8.56}
,{26.7,	7}
,{28.65,	9.56}
,{27.49,	10.71}
,{22.22,	8.99}
,{15.45,	0.71}
,{21.91,	0.97}
,{20.86,	4.85}
,{15.59,	3.91}
,{14.92,	2.46}
,{10.42,	0.95}
,{11.22,	0.02}
,{11.93,	-1.41}
,{13.21,	0.56}
,{13.75,	1.41}
,{15.4,	-0.6}
,{12.91,	1.35}
,{11.04,	1.89}
,{10.81,	-3}
,{12.59,	-4.89}
,{16.88,	-2.47}
,{10.08,	0.03}
,{10.33,	-2.72}
,{10.48,	-2.02}
,{10.68,	-4.95}
,{13.06,	-3.56}
,{15.8,	-0.86}
,{12.93,	6.24}
,{14.44,	7.44}
,{12.33,	5.99}
,{11.91,	5.59}
,{18.23,	8.08}
,{15.02,	4.46}
,{12.55,	3.77}
,{13.05,	4.21}
,{10.09,	5.15}
,{9,	3.42}
,{7.16,	-1.09}
,{4.42,	-2.28}
,{3.64,	-3.57}
,{3.55,	-5.06}
,{5.7,	-5.39}
,{0.72,	-6.12}
,{2.4,	-7.11}
,{4.14,	-3.91}
,{6.18,	-0.96}
,{8.75,	1.72}
,{7.77,	-1.38}
,{7.9,	1.75}
,{7.22,	-2.72}
,{3.58,	-3.65}
,{-1.07,	-7.61}
,{0.36,	-5.72}
,{1.02,	-5.48}
,{4.65,	-1.07}
,{6.27,	-1.14}
,{8.46,	2.62}
,{4.65,	-1.74}
,{3.86,	-2.7}
,{4.9,	-3.79}
,{9.68,	2.35}
,{7.01,	-0.24}
,{3.04,	-2.14}
,{0.31,	-7.72}
,{-4.21,	-12.05}
,{-3.12,	-10.81}
,{-2.58,	-13.33}
,{2.52,	-10.04}
,{3.96,	-0.54}
,{4.7,	-0.74}
,{4.99,	-2.91}
,{4.09,	-2.06}
,{10.19,	1.34}
,{10.08,	0.55}
,{8.41,	-0.09}
,{5.57,	-2.28}
,{3.61,	-3.39}
,{1.95,	-3.24}
,{6.04,	-1.43}
,{8.52,	3.77}
,{7.72,	1.79}
,{6.22,	1.14}
,{11.03,	4.26}
,{10.41,	5.81}
,{11.42,	3.59}
,{8.98,	0.39}
,{9.5,	0.23}
,{8.15,	2.37}
,{7.8,	4.39}
,{0,0}};

