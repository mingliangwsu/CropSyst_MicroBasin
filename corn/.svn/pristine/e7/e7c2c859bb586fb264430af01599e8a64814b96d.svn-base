#ifndef fieldH
#define fieldH
#include "corn/measure/units.h"
#include "corn/container/item.h"
#include "corn/const.h"
namespace CORN
{
//______________________________________________________________________________
interface_ Field
//: public implements_ CORN::Item
{
   //virtual ~Field() {};

   virtual const char* get_name_long()                         const {return 0;}
      // The name is required this is a fully descriptive name for the
   virtual const char* get_name_short()                        const {return 0;}
      // The field name is an optional shorter representation of the parameter key name.
      // It is used for parameters read from database tables where the field name has limit of character.
      // Oracle has a limit of 30 characters.
      // dBase has a limit of 11 characters
      // (In CropSyst this is used for LADSS)
      // If field name is not specified, key is used.
      // So if the key is less that the limit of the field name length in target database tables, the field_name may be omitted for the key.
   virtual const char* get_name_subsection()                   const {return 0;} //130915
   virtual const char* get_caption_SDF()                       const {return 0;}
      // Description of the value as it may appear in a label or caption associated with a field
      // In system data format
   virtual const char* get_hint()                              const {return 0;}
      // Optional information parameter displayed in the user interface (0 when not provided)
      // In system data format
   virtual const char* get_description_URL()                   const {return 0;}
      // Optional URL to a full description of the parameter (0 when not provided)
   virtual Units_code  get_units_code()                        const {return 0;}
      // 0 is used when there is no common units code defined.
   virtual const char* get_units_caption()                     const {return 0;}
      // Even though units usually only applied to numbers;
      // for dates and times, these may be stored/represented as string.
      // In system data format
   inline virtual const char* get_format()                   const { return 0; }
      // The units caption may be used to encode the date format.
      // units_caption specified, will override output of unit_code.
      // Use NULL if no units.
      // For RNAutoControls if units_code is 0 and units_caption is NULL
      // then the form designed units caption
      // will be displayed (with no options for alternate units)
      // even if alt_units_codes are set for the parameter.
};
//_2016-10-13___________________________________________________________________
} // namespace CORN
#endif
