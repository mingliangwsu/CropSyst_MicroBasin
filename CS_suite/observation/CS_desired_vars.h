#ifndef CS_desired_varsH
#define CS_desired_varsH
#include "corn/dynamic_array/dynamic_array_T.h"
#include "corn/container/container.h"
#include "UED/library/varcodes.h"
namespace CS { // Actually this could be moved to CS namespace
//______________________________________________________________________________
class Desired_variables
: public CORN::Dynamic_array<nat32>
{
 public:
   CORN::Units_code  timestep;                                                   //170319
   bool              desire_everything;                                          //111221
 public:
   inline Desired_variables
      (CORN::Units_code timestep_
      ,bool              desire_everything_=false)
      : CORN::Dynamic_array<nat32>(0,50,0)
      , timestep           (timestep_)
      , desire_everything  (desire_everything_)
      {}
   bool is_desired(UED_variable_code var_code)                     affirmation_;
   bool is_anything_desired()                                      affirmation_;
      // returns true if the specified variable is listed as a desired variable.
   bool desire    (UED_variable_code var_code)                  initialization_; //170224
   nat32 include_from_files(const CORN::Container &file_list)   initialization_; //170224
      // Loads variables from each of the listed files.
      // \returns the number of variables ultimately listed
      // (including prexisting and all newly included variables)
      // The file is a simple format with one variable on each line.
      // The variable codes are 32bit hexadecimal (8 digit) numbers
      // The variable code may be followed by an inline name/description comment
      // indicated by # character (padded with at least one space).
      // I.e.
      // 0xFFFFFFFF # description
      // Note that this format is valid YAML.

};
//______________________________________________________________________________
}
#endif

