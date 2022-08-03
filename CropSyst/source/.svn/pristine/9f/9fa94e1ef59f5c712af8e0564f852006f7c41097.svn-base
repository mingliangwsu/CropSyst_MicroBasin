#ifndef rotationH
#define rotationH
#include "rot_param.h"
#include "UED/library/database_file.h"
#define SOW_EVENTS_ARRAY_ALLOC 255
#ifdef PLANTING_SCHEDULER
#  include "CS_suite/simulation/CS_simulation_element.h"
#  include "common/weather/database/CS_weather_daily_UED.h"
#endif
namespace CS
{
   class Weather_database_daily;
}
class Weather_provider;
namespace CropSyst
{
//______________________________________________________________________________
class Rotation
#ifdef PLANTING_SCHEDULER
: public extends_ CS::Simulation_element_abstract
#else
: public extends_ CORN::Item
#endif
{
   Rotation_parameters parameters;
   bool cyclable;
      // we can only have cycles if all sowing events are relative
   const CORN::OS::File_name_concrete template_rotation_file_name;
      // This must be fully qualified at this point because
      // we use this filename to resolve crop and management filenames.
 private:
   //180529 were locals of render_planting_events_adjusted_for_weather_conditions
   // These are actually only temporary, could be put in a deletable structure

   /*mutable */ CORN::Date_clad_32 clear_window_date;
   /*mutable */ CORN::Statistical_sample_with_dataset<float32,float32,float32>
         sowing_precipitation_window_meter;
   /*mutable */ CORN::Statistical_sample_with_dataset<float32,float32,float32>
         avg_air_temp_for_window;
   /*mutable */ Sowing_operation *sowing_operation;
   /*mutable */CropSyst::Sowing_event *next_sowing_event;
   const Weather_provider *weather_provider;
   CORN::Date_clad_32 start_date;
   CORN::Date_clad_32 stop_date ;
   CORN::Date_clad_32 plant_by_date_actual;
   nat8 cycle;
   int sowing_window_days_midpoint;
   CORN::Unidirectional_list  computed_plantings;
   #ifdef PLANTING_SCHEDULER
   #else
   CORN::Date_clad_32 today;
   #endif
   CORN::Bidirectional_list   plantings_fixed_or_computable;
 public:
   Rotation
      (const CORN::OS::File_name &template_rotation_filename
      #ifdef PLANTING_SCHEDULER
      ,const Weather_provider &weather_provider // CS::Weather_database_daily &weather_
      ,const CORN::date32 &today_raw
      ,const CORN::date32 &start_date_raw
      ,const CORN::date32 &stop_date_raw
#else
//#error reached

      #endif
      );
   nat32 render_planting_events
      (modifiable_ CORN::Container &event_list
      ,CORN::Year start_year
      ,CORN::Year stop_year
      ,nat8 cycle)                                                        const;
      // Generates cycle shifted sowing events
      /// \returns the number of planting_events

   nat32 render_planting_events_adjusted_for_weather_conditions
      (CS::Weather_database_daily/*_UED*/ &weather // eventually delete this line
      ,modifiable_ CORN::Container &event_list
      ,CORN::Year start_year
      ,CORN::Year stop_year
      ,nat8 cycle)                                                        ;//const;
      // adjusts the sowing date
      // based on temperature condition and precipition conditions.
      /// \returns the number of events added to the event_list
   inline nat8 get_cycles()                   const { return parameters.years; }
      /// \returns the number of cycles in the rotation
      /// which will match the number of years in the rotation.
      /// This is only applicable to relative rotations
      /// Otherwise it returns 0 (indicating all sowing events have actual dates).
      /// and cycle shifting (and rotator) will not be applicable.
   inline nat16 count_computed_plantings()                                const
      { return parameters.count_computed_plantings(); }
 protected: // Simulation element implementations
   virtual bool start()                                           modification_;
   virtual bool process_day()                                     modification_;
#ifdef PLANTING_SCHEDULER
#else
 private:
   bool resolve_crop_and_management
      (CropSyst::Sowing_operation &gen_sow_op
      ,const CORN::OS::Directory_name &rotation_dir)                      const;
#endif
};
//_2016-07-08_________________________________________________________Rotation_/
#ifndef PLANTING_SCHEDULER
class Rotations
: public extends_ CORN::Unidirectional_list  // of Rotation unique
{public:
   Rotations();
   /*180529 const*/ Rotation *provide
      (const CORN::OS::File_name &rotation_filename
      ,bool rotation_cycling_enabled);
      // \returns null if the rotation file does not exists or could not
      // be loaded or composed.
};
//_2016-07-08________________________________________________________Rotations_/
extern Rotations rotations_global;  // aspect
#endif
//______________________________________________________________________________
} // namespace CropSyst
#endif

