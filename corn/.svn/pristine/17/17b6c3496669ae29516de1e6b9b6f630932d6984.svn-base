#include <corn/dataset/timeseries.h>

namespace CORN
{
//___________________________________________________________________________
Time_series::Time_series(Units_code     _time_step_units)
: Dynamic_float_array()
, start_date_time(0)
, time_step_units(_time_step_units)
{};
//___________________________________________________________________________
Time_series::Time_series(const Dynamic_float_array &dataset,Units_code     _time_step_units)
: Dynamic_float_array(dataset)
, start_date_time(0)
, time_step_units(_time_step_units)
{};
//___________________________________________________________________________
Time_series::Time_series(const Time_series &copy_from)
: Dynamic_float_array(copy_from)
, start_date_time(copy_from.start_date_time)
, time_step_units(copy_from.time_step_units)
{};
//___________________________________________________________________________
Time_series *Time_series::normalize_amounts_to_timesteps
(uint32 target_timesteps)                             const
{
   Time_series *target = new Time_series(*this);
   target->resize(target_timesteps);
   uint32 this_timesteps = this->get_count();
   if (target_timesteps > this_timesteps)
   {  // split this time series' values into the target.
      uint32 this_bin = 0;
      float64 relative_target_bin_size = (float64)this_timesteps / (float64)target_timesteps;
      float64 fraction_this_bin_taken = 0.0;
      float64 target_bin_span = 0.0;
      float64 this_bin_amount_remaining = get_no_resize(0);
      float64 this_amount_to_fill_one_target = this_bin_amount_remaining * relative_target_bin_size;

      for (uint32 target_bin = 0; target_bin < target_timesteps; target_bin++)
      {
         float64 target_bin_amount = 0;
         float64 new_target_bin_span = (target_bin_span + relative_target_bin_size);
         if (new_target_bin_span > 1)
         {
            target_bin_amount = this_bin_amount_remaining;
            float32 this_next_bin_amount = get_no_resize(this_bin+1);
            this_amount_to_fill_one_target = this_next_bin_amount * relative_target_bin_size;
            float64 fraction_from_this_next_bin = new_target_bin_span - 1;
            float32 this_next_amount_to_target_bin = this_next_bin_amount * fraction_from_this_next_bin;
            target_bin_amount += this_next_amount_to_target_bin;
            this_next_bin_amount -= this_next_amount_to_target_bin;
            this_bin += 1;
            // set up for next target
            target_bin_span = 0;
            this_bin_amount_remaining = this_next_bin_amount;
         }
         else
         {
            target_bin_amount += this_amount_to_fill_one_target;
            this_bin_amount_remaining -= this_amount_to_fill_one_target;
            target_bin_span += 1;
         }
         target->set(target_bin,target_bin_amount);
         target_bin_amount = 0;
      };
      if ((this_bin_amount_remaining > 0.0)  )
      {
         float32 target_bin_amount = target->get_no_resize(target_timesteps);
         target_bin_amount += this_bin_amount_remaining;
         target->set(target_timesteps,target_bin_amount);
      };
   } else if  (target_timesteps < this_timesteps)
   {  // combine values into the target.
      uint32  target_bin = 0;
      float64 this_bin_span = 0;
      float64 relative_target_bin_size = (float64)this_timesteps / (float64)target_timesteps;
      float64 target_bin_fraction_filled = 0;
//      float64 carry_remainder_amount_from_this_bin = 0.0;
//      float64 carry_remainder_fraction_from_this_bin = 0.0;
      float64 curr_target_bin_amount = 0.0;
      float64 next_target_bin_amount = 0.0;
      for (uint32 this_bin = 0; this_bin < get_count(); this_bin++)
      {
         curr_target_bin_amount += next_target_bin_amount;
         bool advance_to_next_target_bin = false;
         if ((this_bin_span + 1) >= relative_target_bin_size)
         {
            float64 fraction_from_this_bin_to_curr_target_bin = 1.0;
            float64 fraction_from_this_bin_to_next_target_bin = 0.0;
            fraction_from_this_bin_to_curr_target_bin = relative_target_bin_size - this_bin_span;
            fraction_from_this_bin_to_next_target_bin = 1.0 - fraction_from_this_bin_to_curr_target_bin;
            float64 this_bin_amount = get_no_resize(this_bin);
            curr_target_bin_amount += this_bin_amount * fraction_from_this_bin_to_curr_target_bin;
            next_target_bin_amount += this_bin_amount * fraction_from_this_bin_to_next_target_bin;
            advance_to_next_target_bin = true;
            this_bin_span = fraction_from_this_bin_to_next_target_bin;
         } else
         {  next_target_bin_amount = 0;
            this_bin_span += 1;
         };
         target->set(target_bin,curr_target_bin_amount);
         target_bin += (uint32)advance_to_next_target_bin;
         if (advance_to_next_target_bin) curr_target_bin_amount = 0.0;
      };
      // It is possible that the amounts were not discretely divided
      // so make sure to pick up any residual amount
      if ((next_target_bin_amount > 0.000001) && (target_bin < target->get_count()))// any residual
      {  curr_target_bin_amount += next_target_bin_amount;
         target->set(target_bin,curr_target_bin_amount);
      };
   } else // (timesteps == this_timesteps) the timesteps matches the number of items in this
      target->copy(*this);
   return target;
};
//___________________________________________________________________________
}; // namespace CORN
