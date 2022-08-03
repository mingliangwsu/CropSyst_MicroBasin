#include "corn/datetime/date_time_index.h"
#include "corn/math/compare.h"
#include "corn/measure/units.h"
#include "corn/container/item.h"
namespace CORN
{
//______________________________________________________________________________
Date_time_index::Date_time_index(Units_code i_time_step, Year i_earliest_year,uint32 i_resize_overage_years)
: earliest_year(i_earliest_year)
, doy_index(0)
, year_item(0)
, year_item_mode(time_step == UT_year)
, time_step(i_time_step)
{  terminal_index = i_resize_overage_years-1;
   allocate_and_clear();
}
//______________________________________________________________________________
Date_time_index::~Date_time_index()
{  if (doy_index) delete[] doy_index; doy_index = 0;
   if (year_item) delete[] year_item; year_item = 0;
   terminal_index = 0;
}
//______________________________________________________________________________
void Date_time_index::allocate_and_clear()
{  if (year_item_mode)
   {  year_item = new Item_pointer[terminal_index+1];
      for (int i = 0; i <= terminal_index; i++)
         year_item[i] = 0;
   }
   else
   {  doy_index = new DOY_index_pointer[resize_overage_years];
      for (int i = 0; i <= terminal_index; i++)
         doy_index[i] = 0;
   }
}
//______________________________________________________________________________
Item_pointer Date_time_index::get(const Date_time_64 &date_time) const
{  Item_pointer got_item = 0;
   Year year = date_time.get_year();
   uint32 year_index = year - earliest_year;
   if ((year >= earliest_year) && (year <= earliest_year + terminal_index))
   {  if (year_item)  // simply year array mode
      {  got_item = year_item[year_index];
      }
      else if (doy_index)
      {  if (doy_index[year_index])
            got_item = doy_index[year_index]->get(date_time);
         // else leave got_index as 0 because no index has been set for that year.
      }
   }
   // else leave got_index as 0, the date is out of range
   return got_item;
}
//______________________________________________________________________________
bool Date_time_index::resize(Year for_year)
{  Year        old_earliest_year = earliest_year;
   int32       old_terminal_index = terminal_index;
   DOY_index_pointer  *old_doy_index = doy_index;           // will be 0 if time step is DT_year;
   Item_pointer  *old_year_item = year_item;          // will be used if time step is DT_year;
   earliest_year = std::min<Year>(old_earliest_year,for_year);
   terminal_index = std::max<Year>(for_year - earliest_year + resize_overage_years,old_terminal_index);
   allocate_and_clear();
   //move the year_items or doy_indexes to the new array.
   for (int old_year_index = 0; old_year_index < old_terminal_index; old_year_index++)
   {  int year = old_earliest_year + old_year_index;
      int new_year_index = year - earliest_year;
      if (year_item_mode)
      {  year_item[new_year_index] = old_year_item[old_year_index];
         old_year_item[old_year_index] = 0;;
      }
      else
      {  doy_index[new_year_index] = old_doy_index[old_year_index];
         old_doy_index[old_year_index] = 0;
      }
   }
   if (old_year_item) delete old_year_item;
   if (old_doy_index) delete old_doy_index;
}
//______________________________________________________________________________
Date_time_index::DOY_index::DOY_index(Units_code i_time_step)
: time_step(i_time_step)
, DOY_item_mode(i_time_step == UT_day)
, time_step_index(0)
, doy_item(0)
{  if (DOY_item_mode)
         doy_item = new Item_pointer[366];
   else  time_step_index = new Time_step_index_pointer[366];
}
//______________________________________________________________________________
Date_time_index::DOY_index::~DOY_index()
{  if (time_step_index) delete time_step_index; time_step_index = 0;
   if (doy_item)        delete doy_item;       doy_item = 0;
}
//______________________________________________________________________________
Date_time_index::DOY_index::Time_step_index::Time_step_index(Units_code i_time_step)
: time_step(i_time_step)
, count(0)
, ts_item(0)
{  switch (time_step)
   {  case UT_hour         :  case UT_60_minutes   :  count = 24;    break;
      case UT_minute       :  case UT_60_seconds   :  count = 1440;  break;
      case UT_second       :                          count = 86400; break;
//NYI      case UT_millisecond  :                          count = 86400000; break;
      default :
      {  CORN::Units_clad smart_i_timestep(i_time_step);
         Smart_units_component smart_time_step(smart_i_timestep.get_primary());
         if ((time_step > UT_0_seconds) && (time_step < UT_60_seconds))
         {  int seconds = smart_time_step.get_submeasure_index();
            count = 86400 / seconds;
         }
         else if ((time_step > UT_0_minutes) && (time_step < UT_60_minutes))
         {  int minutes = smart_time_step.get_submeasure_index();
            count = 1440 / minutes;
         }
         else if ((time_step > UT_0_hours) && (time_step < UT_24_hours))
         {  int hours = smart_time_step.get_submeasure_index();
            count = 24 / hours;
         }
      }
   }
   if (count)
      ts_item = new Item_pointer[count];
}
//______________________________________________________________________________
Date_time_index::DOY_index::Time_step_index::~Time_step_index()
{  if (ts_item)   delete ts_item; ts_item = 0;
}
//______________________________________________________________________________
Item_pointer Date_time_index::DOY_index::get(const Date_time_64 &date_time) const
{  Item_pointer got_item = 0;
   DOY doy = date_time.get_DOY();
   int doy_index = doy - 1;
   if (DOY_item_mode)
      got_item = doy_item[doy_index];
   else if (time_step_index)
   {  if (time_step_index[doy_index])
         got_item = time_step_index[doy_index]->get(date_time);
   }
   return got_item;
}
//______________________________________________________________________________
Item_pointer Date_time_index::DOY_index::Time_step_index::get(const Date_time_64 &date_time) const
{  Item_pointer got_item = 0;
   if (ts_item)
   {  datetime64 time = date_time.get_time64();
      uint32 time_index = time * count;
      got_item = (time_index < count)
         ? ts_item[time_index];
         : got_item = 0; // Something is wrong this shouldn't happen
   }
   return got_item;
}
//______________________________________________________________________________
Item_pointer Date_time_index::DOY_index::Time_step_index::set(const Date_time_64 &date_time,Item_pointer index_item)
{  Item_pointer successful = 0;
   datetime64 time = date_time.get_time64();
   uint32 time_index = time * count;
   if (ts_item)
   {  //  year array mode
      if (ts_item[time_index]) successful = 0; // item has already been set.
      else                     successful = ts_item[time_index] = index_item;
   }
   return successful;
}
//______________________________________________________________________________
Item_pointer Date_time_index::set(const Date_time_64 &date_time,Item_pointer index_item)
{  Item_pointer successful = 0;
   Year year = date_time.get_year();
   if (!((year >= earliest_year) && (year <= earliest_year + terminal_index)))
      resize(year);
   uint32 year_index = year - earliest_year;
   if (year_item)
   {  //  year array mode
      if (year_item[year_index]) successful = 0; // item has already been set.
      else                       successful = year_item[year_index] = index_item;
   }
   else if (doy_index)
   {  if (!doy_index[year_index])   doy_index[year_index] = new DOY_index(time_step);
      if (doy_index[year_index])    successful = doy_index[year_index]->set(date_time,index_item);
         // else could not allocate memory (generally should never happen)
   }
   return successful;
}
//______________________________________________________________________________
Item_pointer Date_time_index::DOY_index::set(const Date_time_64 &date_time,Item_pointer index_item)
{  Item_pointer successful = 0;
   DOY doy = date_time.get_DOY();
   int doy_index = doy - 1;
   if (doy_item)
   {  // doy array mode
      if (doy_item[doy_index])   successful = 0; // item has already been set.
      else                       successful = doy_item[doy_index] = index_item;
   }
   else if (time_step_index)
   {  if (!time_step_index[doy_index]) time_step_index[doy_index] = new Time_step_index(time_step);
      if (time_step_index[doy_index])  successful =  time_step_index[doy_index] ->set(date_time,index_item);
      // else could not allocate memory (generally should never happen)
   }
   return successful;
}
//______________________________________________________________________________
} // namespace CORN

