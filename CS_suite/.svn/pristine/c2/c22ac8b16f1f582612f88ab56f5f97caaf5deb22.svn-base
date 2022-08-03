#include "CS_desired_vars.h"
#include "corn/OS/directory_entry_name.h"
#include "corn/string/strconv.hpp"
namespace CS {
//______________________________________________________________________________
bool Desired_variables::is_desired(UED_variable_code var_code)      affirmation_
{  nat32 found_at_index = 0;
   bool desired
      = desire_everything || is_in_array((nat32) var_code,found_at_index);
   return desired;
}
//______________________________________________________________________________
bool Desired_variables::is_anything_desired()                       affirmation_
{  return desire_everything || get_count();
}
//_2017-02-25___________________________________________________________________
bool Desired_variables::desire(UED_variable_code var_code)       initialization_
{  bool added = false;
   nat32 existing_position = 0;
   added = !is_in_array(var_code,existing_position);
   if (added)
      append(var_code);
   return added;
}
//______________________________________________________________________________
nat32 Desired_variables::include_from_files
(const CORN::Container &file_list)                               initialization_
{  std::string var_line;
   FOR_EACH_IN(var_filename,CORN::OS::File_name,file_list,each_var_file)
   {
      std::ifstream var_file(var_filename->c_str());
      while (var_file.good())
      {  getline(var_file,var_line);
         nat32 var_code = CORN::cstr_to_nat32(var_line.c_str(),0);
         // Can be in any radix hexadecimal and octal would have prefix 0x or 0o
         // (YAML conformant).
         desire(var_code);
      }
   } FOR_EACH_END(each_var_file);
   // Special condition, if there is at least one file specified
   // but no listed variables, this indicates all variable.
   // It is suggested that the
   desire_everything = file_list.count() && get_count() == 0;
   return get_count();
}
//______________________________________________________________________________
} // namespace CropSyst


