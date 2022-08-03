
#  ifdef __BCPLUSPLUS__
               // There is a bug in Win32, one of MicroSoft's DLL's is incorrectly changing floating point formats!
#     include <float.h>
#  endif
#  include "watertab.h"
#  ifndef CORN_STRING_USTRING_H
#  endif
//170525 #  include "corn/datetime/date.hpp"

#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include <string>

extern bool quick_and_dirty_disable_chem_balance_when_watertable;                //150424
// for io operators
//______________________________________________________________________________
Water_table_curve::Water_table_curve
(const char *water_tab_filename
,const char *selector
,const CORN::date32 &today_                                                      //170524
,const CORN::Date_const &start_date
,const CORN::Date_const &end_date
,float64 initial_value_elemental                                                 //000502
   // For example salinity dS/m           For NO3 and NH4 this is elemental N concentration
,float32 convert_to_molecular_concentration)                                     //000502
   // In the case of salinity this factor (ECw->TDS converts dS/m -> kg/m3 (converts to salt concentration).
   // Need to check: In the case of nitrogen chemicals this converts elemental mass to chemical mass????
: CS::Simulation_element_abstract(today_)                                        //150925
, interpolator(0)                                                                //080213
, constant_value(0.0)                                                            //080213
, value_today(0.0)
{
   Year   read_year;
   DOY    DOY;
   std::string code;
   float32 value;                                                                //000504
   std::string junk;
   float64 initial_concentration_molecular = initial_value_elemental*convert_to_molecular_concentration; //080219
#ifdef __BCPLUSPLUS__
   _fpreset(); // There is a bug in Win32, one of MicroSoft's DLL's is incorrectly changing floating point formats!
#endif
   if (water_tab_filename)                                                       //020620
   {  std::ifstream recal_file(water_tab_filename);                              //981118
      /*180426 renamed
      interpolation = new CORN::Interpolation_curve_dated
         (CORN::linear_curve,initial_concentration_molecular,&start_date);       //150313_150112_080213
      */
      interpolator = new CORN::Interpolator_temporal
         (CORN::linear_curve,initial_concentration_molecular,&start_date);       //150313_150112_080213
      bool any_apropos_records_in_the_file = false;                              //080213
      while (! recal_file.eof() && recal_file.good())                            //990330
      {  recal_file >> read_year >> DOY >> code >> value;
         Year  start_every_year = (read_year == 0) ? start_date.get_year() : read_year; //000504
         Year  end_every_year   = (read_year == 0) ? end_date.get_year()   : read_year; //000504
         for (Year  year = start_every_year ; year <= end_every_year ; year++)   //000504
         {  CORN::Date_clad_32 observation_date(year,DOY);                       //000504
            if (code == selector)                                                //000504
            {  any_apropos_records_in_the_file = true;                           //080213
               interpolator->set_by_date(observation_date,value * convert_to_molecular_concentration); //000504
      }  }  }
      if (!any_apropos_records_in_the_file)                                      //080212
      {  // The interpolation record is empty, so just delete it                 //080212
            // maybe we will then default to a single constant value             //080212
         delete interpolator;                                                    //080212
         interpolator = 0;                                                       //080212
      }
     recal_file.close();
   }
   if (!interpolator) // When there is no water table file or no apropos records in the file there may be a single constant value        //080213
        value_today = constant_value = initial_concentration_molecular;          //150925_080213
   quick_and_dirty_disable_chem_balance_when_watertable = true;                  //150424
}
//_Water_table_curve:constructor________________________________________________
bool Water_table_curve::start_day()                                modification_
{  value_today =  get(today);
   return true;
}
//_start_day________________________________________________________2015-09-25_/
float64 Water_table_curve::get_for_today()                         modification_
{  return value_today;                                                           //150925
}
//_get_for_today____________________________________________________2007-10-23_/
float64 Water_table_curve::get(const CORN::Date_const &for_date)   modification_
{  return interpolator //180426 interpolation
      ? (float64)interpolator //180426 interpolation
         ->get_ordinate_by_date(for_date)
      : constant_value;                                                          //080213
}
//_get______________________________________________________________2002-03-06_/
bool Water_table_curve::is_valid()                                         const
{  return (interpolator != NULL)
      || !CORN::is_approximately<float64>(constant_value,0.0,0.000001);
}
//_Water_table_curve::is_valid______________________________________2008-02-13_/

