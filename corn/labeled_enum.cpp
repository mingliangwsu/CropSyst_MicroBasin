#include "corn/labeled_enum.h"
#include <string.h>
#include <stdlib.h>
#ifndef compareHPP
#  include "corn/math/compare.hpp"
#endif
#ifndef strconvHPP
#   include "corn/string/strconv.hpp"
#endif
// in UNIX, MSC and BC++ strtoul is in stdlib.h
// it might be in other header files for other compiler vendors
//namespace CORN {
//______________________________________________________________________________
Labeled_enum::Labeled_enum()
: simple_label_table(0)
, descriptive_label_table(0)
{}
// This constructor is for enumeration that are simply integer numbers
//_2005-09-29___________________________________________________________________
Labeled_enum::Labeled_enum(const char **_label_table)
: simple_label_table(_label_table)
, descriptive_label_table(0)
{}
//_2005-09-29___________________________________________________________________
Labeled_enum::Labeled_enum(Label_description *_descriptive_label_table )
: simple_label_table(0)
, descriptive_label_table(_descriptive_label_table)
{}
//_2005-09-29___________________________________________________________________
bool Labeled_enum::is_label(const char *label)                      affirmation_
{  if (simple_label_table)
      for (int32 i = 0; simple_label_table[i] && strlen(simple_label_table[i]); i++)
        if (strcmp(label,simple_label_table[i]) == 0)
          return true;
   if (descriptive_label_table)
      for (int32 i = 0; descriptive_label_table[i].label != 0 && strlen(descriptive_label_table[i].label); i++)
        if (strcmp(label,descriptive_label_table[i].label) == 0)
          return true;
   return false;
}
//_2002-04-19_________________________________________________________is_label_/
int32 Labeled_enum::set_label(const char *label)
{  int32 new_value = 0;
   if (simple_label_table)
   {  for (int32 i = 0; simple_label_table[i] && strlen(simple_label_table[i]); i++)
         if (strcmp(label,simple_label_table[i]) == 0)
          new_value = i;
      // If the label wasn't found in the table, try case insensitive search.
      if (!new_value)
         for (int32 i = 0; simple_label_table[i] && strlen(simple_label_table[i]); i++)
            if (stricmp(label,simple_label_table[i]) == 0)
               new_value = i;
   } else if (descriptive_label_table)
   {  for (int32 i = 0; descriptive_label_table[i].label && strlen(descriptive_label_table[i].label); i++)
         if (strcmp(label,descriptive_label_table[i].label) == 0)
          new_value = i;
      // If the label wasn't found in the table, try case insensitive search.
      if (!new_value)
         for (int32 i = 0; descriptive_label_table[i].label && strlen(descriptive_label_table[i].label); i++)
            if (stricmp(label,descriptive_label_table[i].label) == 0)
               new_value = i;
   } else // simple integer enumeration (I.e. soil layers
        new_value = atoi(label);
   set_int32(new_value);
   return new_value;
}
//_2002-03-21 __________________________________________________________________
static const char *num_str[]
={ "0","1","2","3","4","5","6","7","8","9"
, "10","11","12","13","14","15","16","17","18","19"
, "20","21","22","23","24","25","26","27","28","29"
, "30","31","32","33","34","35","36","37","38","39"
, "40","41","42","43","44","45","46","47","48","49"
, "50","51","52","53","54","55","56","57","58","59"
, "60","61","62","63","64","65","66","67","68","69"};
//______________________________________________________________________________
const char *Labeled_enum::get_label()                                      const
{  int32 label_index = get_int32();
   const char *result =
     (simple_label_table)        ? simple_label_table[label_index]
   : (descriptive_label_table)   ? descriptive_label_table[label_index].label
   :                               num_str[label_index];
   return result;
}
//_2005-09-29__2002-04-01____________________________________________get_label_/
const char *Labeled_enum::get_description()                                const
{  const char *result =
   descriptive_label_table
   ? descriptive_label_table[get_int32()].description
   : get_label();  // For simple label tables, simply return the label as the description.
   return result;
}
//_2005-09-29__________________________________________________get_description_/
nat16 Labeled_enum::get_max_label_length()                                 const
{  nat16 max_label_len  = 1; // Must be at least 1 character
   // Returns the longest label length.
   // This is used to determine the field size for Data_records enumeration attributes.
   if (simple_label_table)
       for (nat16 i = 0; simple_label_table[i] && strlen(simple_label_table[i]); i++)
           max_label_len = std::max<nat16>(max_label_len,(nat16)strlen(simple_label_table[i]));
   else if (descriptive_label_table)
       for (nat16 i = 0; descriptive_label_table[i].label && strlen(descriptive_label_table[i].label); i++)
           max_label_len = std::max<nat16>(max_label_len,(int)strlen(descriptive_label_table[i].label));
   else max_label_len  = 6;   // For enumerated label tabels
   return max_label_len;
}
//_2005-09-29_____________________________________________get_max_label_length_/
//} // namespace CORN
