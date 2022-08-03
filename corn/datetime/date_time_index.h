#ifndef DATE_INDEX_H
#define DATE_INDEX_H
#error check obsolete
#include <corn/measure/units.h>
#include <corn/datetime/date_types.hpp>

/* This class is used to create dynamic indexes of dates
   It was intended for UED in memory data record indexes
*/

namespace CORN {
class Date_time_64; // Forward declaration
class Item_pointer;
//______________________________________________________________________________
class Date_time_index
// This could be a container:
// I haven't done that yet because I need to write an iterator, and it
// could be a little complex and I don't need it now.
{
   class DOY_index
   {
      Units_code time_step;
      class Time_step_index
      {
         Units_code     time_step;
         uint32         count;      // Number of time steps (array size)
         Item_pointer  *ts_item;  // timestep item
   public:
         Time_step_index(Units_code i_time_step = UT_hour);
         virtual ~Time_step_index();
         Item_pointer get(const Date_time_64 &date_time) const; // No resizing
         Item_pointer set(const Date_time_64 &date_time,Item_pointer index_item);
      }; typedef Time_step_index *Time_step_index_pointer;

      bool DOY_item_mode;
      Time_step_index_pointer *time_step_index; // Will only have one index if the timestep is UT_day
      Item_pointer            *doy_item;       // array will be used if time step is DT_year;
   public:
      DOY_index(Units_code i_time_step = UT_day);
      virtual ~DOY_index();
      Item_pointer get(const Date_time_64 &date_time) const; // No resizing
      Item_pointer set(const Date_time_64 &date_time,Item_pointer index_item);
   }; typedef DOY_index * DOY_index_pointer;

   Year        earliest_year;
   uint32      resize_overage_years;// When the index needs to be resized, this is the number of years to buffer
   bool        year_item_mode;
   Units_code  time_step;

   int32             Umax_index;          // -1 denotes empty list
   DOY_index_pointer *doy_index;           // array will be 0 if time step is DT_year;
   Item_pointer      *year_item;           // array will be used if time step is DT_year;
public:
   Date_time_index(Units_code i_time_step = UT_day, Year i_earliest_year= 2000,uint32 i_resize_overage=10);
   virtual ~Date_time_index();

   Item_pointer get(const Date_time_64 &date_time) const; // No resizing
   // Returns the index pointer
   // Returns 0 if there was no index for the specified time

   Item_pointer set(const Date_time_64 &date_time, Item_pointer index_item);
   // returns index_item if set,
   // returns 0 if failed.
   // Will fail if there is already an entry for the time stamp
   // so you will want to call get first to check if there is already something there.
private:
   void allocate_and_clear();
   bool resize(Year for_year);
   // returns true if resize was successful otherwise false.
};
//______________________________________________________________________________
}; // namespace CORN;
#endif
// date_time_index.h

