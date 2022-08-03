#include "soil/dynamic_water_entering.h"

float64 Dynamic_water_entering_soil::deduct(float64 deduction)
{  // deduction is modified locally only
   // The water is currently being deducted from the end of the day 000217
   // to give results more similar to Pascal version,
   for   (int16 interval = get_count()-1
         ; (interval >=0) && (deduction > 0)
         ; interval--)
   {  float64 amount_interval = get(interval);                                   //140226
      if (deduction > amount_interval)
      {  deduction -= amount_interval;
         amount_interval = 0;
      }
      else
      {  amount_interval -= deduction;
         deduction = 0.0;
      }
      set(interval,amount_interval);
   }
   return sum();
}
//_1999-04-02___________________________________________________________________


