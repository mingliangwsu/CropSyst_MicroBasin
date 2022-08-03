#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#include "corn/measure/measures.h"
#include "corn/measure/unitconv.h"
namespace CORN {
//______________________________________________________________________________
float32 Units_convertor::get_english_length_to_yards_multiplier(Units_component english_linear_units) const
{  // The yard is the base linear units of measure in the English system
   float64 english_length_to_yards = 0.0; // retun 0.0 if failed
   uint8 submeasure = english_linear_units.get_submeasure_index();
   switch (submeasure)
   {
      case SUE_inch : english_length_to_yards = 0.027777778; break;
      case SUE_nail : english_length_to_yards = 0.0625; break;
      case SUE_hand : english_length_to_yards = 0.111111111; break;
      case SUE_link : english_length_to_yards = 0.22; break;
      case SUE_foot : english_length_to_yards = 0.333333333; break;
      case SUE_yard : english_length_to_yards = 1.0; break;
      case SUE_rod  : english_length_to_yards = 5.5; break;
//The following are the same as rod:
//                     case pole : english_length_to_yards = 5.5; break;
//                     case perch : english_length_to_yards = 5.5; break;
//                     case lugg   : english_length_to_yards = 5.5; break;
      case SUE_fathom : english_length_to_yards = 2.0; break;
      case SUE_chain  : english_length_to_yards = 22; break;
      case SUE_furlong: english_length_to_yards = 220; break;
      case SUE_statute_mile  : english_length_to_yards = 1760; break;
      case SUE_nautical_mile : english_length_to_yards = 2025.37182852143; break; // 1852meters (exact)
//NYI      case SUE_nautical_mile_historic : english_length_to_yards = 2026.666667; break;
   }
                  // Warning this has not been tested.
   if (english_linear_units.is_denominator() && !CORN::is_approximately<float64>(english_length_to_yards,0.0,0.000000000001))
   {
      english_length_to_yards = CORN::is_approximately<float64>(1.0 / english_length_to_yards,0.0,0.000001);
   }
   return (float32)english_length_to_yards;
}
//______________________________________________________________________________
void Units_convertor::normalize_customary_units_to_metric(float32 &from_value, Units_component &from_units) const
{  nat8 from_measure = from_units.get_measure_index();
   switch (from_units.subcode)
   {  case UE_Farenheit :
            from_value = (float32)F_to_C(from_value);
            from_units = UC_Celcius;
      break;
      case U_denominator_marker|UE_Farenheit :
            from_value = (float32)(1.0/F_to_C(from_value));  // I THINK NEED TO VERIFY
            from_units = U_denominator_marker |UC_Celcius;
      break;
      default :
         switch(from_measure)
            {
               case UM_land_area :
               {
                  float64 english_land_area_to_acres = 1.0;
                  uint8 submeasure = from_units.get_submeasure_index();
                  switch (submeasure)
                  {
                     case  UE_acre        :  english_land_area_to_acres = 1.0;      break;
                     case  UE_rood        :  english_land_area_to_acres = 0.25;     break;
                     case  UE_arpent_area :  english_land_area_to_acres = 0.8445;   break;
                     case  UE_virgate     :  english_land_area_to_acres = 30.0;     break;
                     case  UE_hide        :  english_land_area_to_acres = 120.0;    break;

                     case  UE_morgen_scandinavian  :  english_land_area_to_acres = 0.63;break;
                     case  UE_morgen_prussian      :  english_land_area_to_acres = 0.630914402069596 ; break;
                     case  UE_morgen_dutch         :  english_land_area_to_acres = 2.1; break;
                     case  UE_morgen_south_african :  english_land_area_to_acres = 2.1169; break;

// here we have rood and acres
//rood  old unit of land area equal to 1/4 acre
//arpent  unit of land area slightly smaller than an acre
//morgen  unit of land area slightly more than two acres
//virgate  old unit of land area usually equal to 30 acres or 1/4 hide
//hide  old unit of land area equal to 120 acres

                  }
                  // Warning this has not been tested.
                  if (from_units.is_denominator())
                     english_land_area_to_acres = 1.0/english_land_area_to_acres;
                  float64 from_value_acres = from_value * english_land_area_to_acres;
                  from_value = (float32)acre_to_are(from_value_acres);
                  from_units = UC_are;
               }
               break;
               case UM_linear :
               {  // length is based on the unit yard
//050613          // english_length_to_yards was moved to get_english_length_to_yards_multiplier

                  float64 english_length_to_yards = get_english_length_to_yards_multiplier(from_units);
                  float64 from_value_yards = from_value * english_length_to_yards;
                  from_value = (float32)yard_to_m(from_value_yards);
                  from_units = UC_meter;
               } break;
               case UM_dry : case UM_liquid :
               {  // liquid and dry measure is based on the unit gallon
                  float64 amount_to_gallons  = 1.0;
                  uint8 submeasure = from_units.get_submeasure_index();
                  switch (submeasure)
                  {  case SUE_minim        :  amount_to_gallons =  1.30208E-05;   break;
                     case SUE_drachm       :  amount_to_gallons =  0.00078125;    break;
                     case SUE_ounce        :  amount_to_gallons =  0.00625;       break;
                     case SUE_mutchkin      :  amount_to_gallons =  0.09375;       break;
                     case SUE_pint         :  amount_to_gallons =  0.125;         break;
                     case SUE_gill         :  amount_to_gallons =  0.03125;       break;
                     case SUE_fifth        :  amount_to_gallons =  0.2;           break;
                     case SUE_quart        :  amount_to_gallons =  0.25;          break;
//                   case SUE_gallon       :  amount_to_gallons = 1.0;            break;
                     case SUE_peck         :  amount_to_gallons = 2.0;            break;
                     case SUE_bushel       :  amount_to_gallons = 8.0;            break;
                     case SUE_quarter      :  amount_to_gallons = 32.0;           break;
                     case SUE_tun          :  amount_to_gallons = 252.0;          break;
                     case SUE_chaldron     :  amount_to_gallons = 288.0;          break;
                  }

                  // Warning this has not been tested.
                  if (from_units.is_denominator())
                     amount_to_gallons = (1.0 / amount_to_gallons);

                  float64 from_value_gallons = from_value * amount_to_gallons;
                  /*
                  float32 from_value_cubic_inches =  from_value_gallons *
                  (from_units.is_imperial) ? 277.4194 // 1 imperial gallon to cubic inches
                                           : 231.0;    // 1 US gallon to cubic inches
                  */
                   from_value = (float32)
                   (from_units.is_imperial()
                    ? gallon_imperial_to_liter(from_value_gallons)
                    : gallon_to_liter(from_value_gallons));
                   from_units = UC_liter;
                  // NYI firkin  barrel  hogshead bottle
               } break;
               /// Warning I need to implement other units
               // As with normalization length to yards, we normalize weights to grains
            }
         break;
   }
}
//______________________________________________________________________________
bool Units_convertor::convert_subunit
(float32 from_value ,Units_component from_SUC
,float32 &to_value,Units_component to_SUC) const
{
   // Note that from and to units are updated locally as the conversion factor is scaled.
   // Note that the length, depth, width, distance and altitude although have different quantity byte
   // they are all essentially length so will have the same conversion factor

   // At this point, we presume that from and to are the same measure.
   // Now we need to convert nonstandard units to metric:

   bool from_units_not_standard =  !from_SUC.is_standard();
   if (from_units_not_standard)
      normalize_customary_units_to_metric(from_value,from_SUC);
   if (to_SUC.is_standard())
   {  // converting to metric
      float32 scale_factor =  from_SUC.standard_conversion_to_factor(to_SUC);
      to_value = from_value * scale_factor;
   } else
   {
//050613       return false; // This isn't implemented yet, so can't convert
      // at this point from value and from units are metric
      // I.e. kilo meter we need to normalize (i.e. meter)
//      float32 normalized_from_value_metric(from_value,from_units)
      // at this point from value and from units are metric normal units
      // I.e. meter not kilometer
      convert_metric_to_customary(from_value,from_SUC,to_value,to_SUC);
   }
   return true;
}
//______________________________________________________________________________
bool Units_convertor::convert_metric_to_customary(float32 from_value,Units_component &from_SUC,float32 &to_value,Units_component &to_SUC) const
{  bool result = true;
   // Convert the metric value/units to the base units  (I.e.  km->m  cm->m)
   normalize_to_metric_base_units(from_value, from_SUC);
   switch (from_SUC.subcode)
   {
      case UC_meter     : result = convert_meter_to_customary(from_value/*in meters*/,to_value,to_SUC);
      // NYI need the various other measures
      break;
      case UC_Celcius :
                  to_value = (float32)C_to_F(from_value);
                  to_SUC = UE_Farenheit;
      break;
      default : result = false;
//cerr << "Warning: metric to customary units conversion not yet implement for units." << endl;
      break;
   }
   return result;
}
//_050613______________________________________________________________________________
void Units_convertor::normalize_to_metric_base_units(float32 &from_value,Units_component &from_SUC) const
{
   // warning presuming from units is indeed using metric composition
   // warning don't forget to handle if it is denominator
   Units_component from_SUC_normal(from_SUC);
   from_SUC_normal.clear_metric_exponent();
   float32 conversion_factor = from_SUC.standard_conversion_to_factor(from_SUC_normal);
   float32 from_normalized = from_value*conversion_factor;
   // modify the return value and units with the normalized value and units
   from_value = from_normalized;
   from_SUC.clear_metric_exponent();
}
//_050613______________________________________________________________________________
bool Units_convertor::convert_meter_to_customary(float32 from_value/*in meters*/,float32 &to_value,Units_component &to_units) const
{  bool result = true;
   float32 to_in_yard = (float32)m_to_yard(from_value);
   float32 length_to_yards_multiplier = get_english_length_to_yards_multiplier(to_units);
   if (CORN::is_approximately<float32>(length_to_yards_multiplier,0.0,0.000000001))
         result = false;
   else  to_value = to_in_yard / length_to_yards_multiplier;
   return result;
}
//_050613______________________________________________________________________________/
bool Units_convertor::convert
(float64 from_value
,Units_code from_units  // may be modified but only locally
,float64 &to_value
,Units_code to_units    // may be modified but only locally
) const
{  float32 to_value_32 = (float32)to_value;
   bool converted = convert((float32)from_value,from_units,to_value_32,to_units);
   to_value = to_value_32;
   return converted;
}
//_100303______________________________________________________________________________
bool Units_convertor::convert
(float32 from_value
,Units_code from_units  // may be modified but only locally
,float64 &to_value
,Units_code to_units    // may be modified but only locally
) const
{  float32 to_value_32 = (float32)to_value;
   bool converted = convert(from_value,from_units,to_value_32,to_units);
   to_value = to_value_32;
   return converted;
}
//_100303______________________________________________________________________________
bool Units_convertor::convert
(float64 from_value
,Units_code from_units  // may be modified but only locally
,float32 &to_value
,Units_code to_units    // may be modified but only locally
) const
{
   return convert((float32)from_value,from_units,to_value,to_units);
}
//_100303______________________________________________________________________________
bool Units_convertor::convert
(float32 from_value
,Units_code from_units  // may be modified but only locally
,float32 &to_value
,Units_code to_units    // may be modified but only locally
) const
{
   bool converted = false;
//            Equivelent units
   if (from_units == to_units)                                                   //970923
   {  to_value = from_value;
      return true;
   }
//            See if the specific property standard units can be generalized
//            if so use the generalized forms.
//            The units modification are local only and should not be returned
   CORN::Units_clad smart_from_units(from_units);
   CORN::Units_clad smart_to_units(to_units);
   // Special standard units that have irregular conversions.
   switch (to_units)                                                             //000410
   {
      case UC_kelvin :                                                           //120109
      {  if (from_units == UC_Celcius)
         {  to_value = (float32)C_to_kelvin(from_value);
            converted = true;
         }
      } break;
      case UC_Celcius:                                                           //120109
      {  if (from_units == UC_kelvin)
         {  to_value = (float32)kelvin_to_C(from_value);
            converted = true;
         }
      } break;
      case UC_square_meter_area : // UC_square_meter_surface_area                //030903
         if (from_units == UC_hectare)                                           //030903
         {  to_value = (float32)ha_to_m2(from_value);                            //030903
            converted = true;                                                    //030903
         }
      break;
      case UC_hectare :                                                          //030903
         if (from_units ==UC_square_meter_area) //  UC_square_meter_surface_area //030903
         {  to_value = (float32)m2_to_ha(from_value);                            //030903
            converted = true;                                                    //030903
         }
      break;
      case UC_cubic_meter_volume :                                               //040418
//040715 now we just have volume       case UC_cubic_meter_liquid_volume :
      if (from_units == UC_liter)                                                //040418
      {  to_value = (float32)liter_to_m3(from_value);                            //040418
         converted = true;                                                       //040418
      }
      break;
      case UC_percent :                                                          //041031
      {  if ((from_units == UC_decimal_percent) || (from_units == UC_fraction))  //041031
         {  to_value = (float32)(from_value * 100.0);                            //041031
            converted = true;                                                    //041031
      }
      } break;
      case UC_decimal_percent :  case UC_fraction :                              //041031
      {  if (from_units ==UC_percent )                                           //041031
         {  to_value = (float32)(from_value / 100.0);                            //041031
            converted = true;                                                    //041031
         }
      } break;
      case UC_index :                                                            //180408
      {  if (from_units ==UC_decimal_percent )                                   //180408
         {  to_value = 1.0-(float32)(from_value );                               //180408
            converted = true;                                                    //180408
         }
      } break;
      break;
      case UC_kg_ha :                                                            //000410
         if (from_units == UC_kg_m2) // Denominator is not the same measure      //000410
         {  to_value =  (float32)per_m2_to_per_ha(from_value);                   //000410
            converted = true;                                                    //000410
         }
      break;
      case UC_kg_m2 :                                                            //000410
         if (from_units == UC_kg_ha) // Denominator is not the same measure      //000410
         {  to_value =  (float32)per_ha_to_per_m2(from_value);                   //000410
            converted = true;                                                    //000410
         }
      break;
      case UE_Langley :                                                          //020505
         if (from_units == UC_MJ_per_m2_solar_radiation)                         //020505
         {  to_value = (float32)MJ_m2_to_Langley(from_value);                    //020505
            converted = true;                                                    //020505
         }
      break;
      case  UC_MJ_per_m2_solar_radiation:   /* I.e. per day */                   //020505
      {  converted = true;                                                       //080327
         switch (from_units)                                                     //080327
         {  case UE_Langley :                                                    //020505
            {  to_value = (float32)Langley_to_MJ_m2(from_value);                 //020505

            } break;
            case UC_watt_m2_flux_density :                                       //050425
            {  //Note watts are per unit time.                                   //050425
               // this may only be part of the conversion                        //050425
               // there may be a time element (time step)                        //050425
               // make sure to use convert_with_time in most cases               //050425
               //                                                                //050425
               to_value = (float32)from_value/1000000.0;                         //020505
               //080326 I think this conversion may be watt-day/m^2              //020505
            } break;
            case UC_watt_day_per_m2 :                                            //150328
            {  // 080326 Warning this has not been confirmed.                    //080327
               to_value = (float32)from_value * 0.0864;                          //150328
            } break;
            case UC_watt_hour_per_m2 :                                           //090915
            {  // 080326 Warning this has not been confirmed.                    //090915
               to_value = (float32)from_value/1000000.0 * 3600.0;                //090915
/*
One Watt equals one Joule per second.

If the average Watts per meter squared over the course of an hour is 800 (Watt hour) then

800 W/m2 = 800 J/m2/Sec
800 J/m2/Sec * 3600 Sec/Hour = 2,880,000 Joules/m2/Hour
2,880,000 Joules/m2/Hour / 1,000,000 = 2.88 MJ/m2/Hour

Note that for this specific case (hourly average to an hourly total)

2.88 MJ/m2/Hour / 800 W/m2 = 0.0036

therefore

800 W/m2 * 0.0036 = 2.88 MJ/m2/Hour

You could just use 0.0036 as a direct multiplier to get from W/m2 to MJ/m2/Hour.
*/
            } break;                                                             //090915
            case UC_watt_second_per_m2 :                                         //080327
            {  // 080326 Warning this has not been confirmed.                    //080327
               to_value = (float32)from_value/1000000.0 * 86400.0;               //080327
            } break;
            default : converted = false; break;                                  //080327
         }
      } break;
      case UC_watt_hour :                                                        //021214
         if (from_units == UC_joule_energy)                                      //020505
         {  to_value = (float32)(from_value * 2.77777778e-4);  // (1/3600)       //020505
            converted = true;                                                    //020505
         }
      break;
      case UC_watt_day :                                                         //021218
         if (from_units == UC_joule_energy)                                      //020505
         {  to_value = (float32)(from_value * 1.15740740740740e-5);  // (1/86400)//020505
            converted = true;                                                    //020505
         }
      break;
    }
    if (converted) return true;                                                  //000410
              // regular conversions where the numerators and denominators are the same measure
               // The following are simple scale factors.
//            Generalized standard units
   float32 to_primary = 0;
   float32 from_primary = from_value;
   // If both the from and to targets are the same kind of units
   // we can do an easy conversion.
   // First convert the numerator
   Units_component from_primary_units  (smart_from_units.get_primary());
   Units_component from_secondary_units(smart_from_units.get_secondary());
   Units_component to_primary_units   (smart_to_units.get_primary());
   Units_component to_secondary_units (smart_to_units.get_secondary());
   bool primary_converted = convert_subunit(from_primary,from_primary_units,to_primary,to_primary_units);
   bool secondary_converted = true;
   if (from_secondary_units.subcode || to_secondary_units.subcode)
   {  // We only need to convert the secondary if there is a units code.
      float32 to_secondary = 0;
      float32 from_secondary = to_primary;
      secondary_converted = convert_subunit(from_secondary,from_secondary_units,to_secondary,to_secondary_units);
      to_value = to_secondary;
   }
   else to_value = to_primary;
   converted = primary_converted && secondary_converted;
//               float32 float32 primary_conversion_factor = get_standard_or_nonstandard_conversion_factor(from_primary,to_primary);
//               float32 float32 secondary_conversion_factor = get_standard_or_nonstandard_conversion_factor(from_secondary,to_secondary);
//               to_value *= primary_conversion_factor * secondary_conversion_factor;
//               return true;
  // Take from value from_units to unit value for the from_units
  // Convert unit value to unit value in to_units
  // take unit value in to_units to to_units
  // I.e.  if from_units is in kilometers and to units is in miles,
  // convert from units to meters.  convert meters to yards, convert yards to
  // miles.
  return converted;
}
//______________________________________________________________________________
bool Units_convertor::convert_time
   (float32  from_value, Units_code from_time_step
   ,float32 &to_value,  Units_code to_time_step  ) const
{  bool converted = true;
   uint32 from_time_seconds = get_seconds_in(from_time_step); //returns 0 if could not get values in seconds (overflow)
   uint32 to_time_seconds   = get_seconds_in(to_time_step);
   to_value = from_value * (float32)from_time_seconds ;
   bool is_to_unit_time = (to_time_step == UT_unit_time);
   if (!is_to_unit_time)  to_value /=  (float32)to_time_seconds;
   if ((from_time_seconds == 0) || (!is_to_unit_time && (to_time_seconds == 0)))  converted = false;
   return converted;
}
//_2005-04-21___________________________________________________________________
bool Units_convertor::convert_with_time_step
   (Units_code   from_time_step
   ,float32 from_value, Units_code from_units
   ,Units_code    to_time_step
   ,float32 &to_value,  Units_code to_units  ) const
{  bool converted = true;
   float32 to_WO_time = 0;
   converted &= Units_convertor::convert(from_value,from_units,to_WO_time,to_units);
   converted &= Units_convertor::convert_time(to_WO_time,from_time_step,to_value,to_time_step);
  return converted;
/*_______*/}
//_2005-04-21___________________________________________________________________
uint32 Units_convertor::get_seconds_in(Units_code time_units) const
{
   uint32 seconds = 0;
   uint32 minutes = 0;
   uint32 hours   = 0;
   uint32 days    = 0;
   uint32 years   = 0;
   switch (time_units)
   {
      case UT_week : days = 7; break;
      // NYI for UT_week_1 to UT_week_52 set the te respective number of days
       // continue here  not critical needed only for completeness
/*_______*/
      case UT_fortnight : days = 14; break;
      // NYI for UT_fortnight_1 to UT_fortnight_26 set the te respective number of days
       // continue here   not critical needed only for completeness
      // The following units of measure are actually metric, the metric power cases are handled by default
      case UT_second : seconds = 1; break;
      case UT_minute : minutes = 1; break;
      case UT_hour   : hours   = 1; break;
      case UT_day    : days    = 1; break;
      case UT_year   : years   = 1; break;
      default :
      {
         // NYI    UT_day_of_month_1 to UT_day_of_month_31
         if ((time_units >= UT_1_second) && (time_units <= UT_60_seconds)) seconds = time_units - UT_0_seconds;
         if ((time_units >= UT_1_minute) && (time_units <= UT_60_minutes)) minutes = time_units - UT_0_minutes;
         if ((time_units >= UT_1_hour)   && (time_units <= UT_24_hours))   hours   = time_units - UT_0_hours;
#ifdef NYI
// not critical, needed only for completeness
#define UT_second          (uint16)0x1600      // 00010110 00000000b
// The lower word is the metric exponent so
// reserverd                     0x1601
// to                            0x16FF

#define UT_minute          (uint16)0x1700      // 00010111 00000000b
// The lower word is the metric exponent so
// reservered                    0x1701
// to                            0x17FF

#define UT_hour            (uint16)0x1800      // 00011000 00000000b
// The lower word is the metric exponent so
// reservered                    0x1801
// to                            0x18FF

#define UT_day             (uint16)0x1900      // 00011001 00010000b // was1080x
// The lower word is the metric exponent so
// reservered                    0x1901
// to                            0x19FF

#define UT_year            (uint16)0x1A00      // 00011010 00000000b
// The lower word is the metric exponent so  //
// reservered                    0x1A01
// to                            0x1AFF

//can only go up to about 1 century time step to seconds conversion

#endif
      }  break; // end default
   }  // end switch
   days += years * 365 + ((years/4) - (years / 100) + (years/400));
   // This give a rough estimate of the number of days accounting for leap year
   // but it can be off give or take a year. (I don't expect this condition to ever actually be used
   // for units conversion.
   hours += days * 24;
   minutes += hours * 60;
   seconds += minutes * 60;
   return seconds;
}
//_2005-04-21___________________________________________________________________
Units_convertor units_convertor;
} // namespace CORN

