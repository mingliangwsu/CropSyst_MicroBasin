#include "common/recorder/recorder_datarec.h"
#include "common/recorder/recorder.h"
namespace CORN {
//______________________________________________________________________________
void Desired_variables_list::desire(UED_variable_code new_var)
{  for (uint16 i = 0; i < count; i++)
      if (desired_vars[i] == new_var)
         return; // The variable is already listed
   desired_vars[count] = new_var;
   count++;
}
//______________________________________________________________________________
void Desired_variables_list::desire(UED_variable_code new_vars[])
{  for (uint16 i = 0; new_vars[i]; i++)
      desire(new_vars[i]);
}
//______________________________________________________________________________
bool Desired_variables_list::is_desired(UED_variable_code variable_code)
{  for (uint16 i = 0; i < count ; i++)
      if (desired_vars[i]) return true;
   return desire_all_variables();                                                //010419
}
//______________________________________________________________________________
Recorder_data_record::Recorder_data_record()
: Data_record("-")
, date_time(0)                                                                   //030713
{}
//______________________________________________________________________________
void Recorder_data_record::expect_recorder(Recorder_float32 *recorder)
{  // Appends the recorder to the current section;
   VV_Section *curr_section = get_current_section();
   if (curr_section) curr_section->entries.append(recorder);
}
//______________________________________________________________________________
void Recorder_data_record::expect_recorder(Recorder_float64 *recorder)
{  // Appends the recorder to the current section;
   VV_Section *curr_section = get_current_section();
   if (curr_section) curr_section->entries.append(recorder);
}
//______________________________________________________________________________
void Recorder_data_record::remember
(Recording_object *object_to_remember)
{  set_current_section(object_to_remember->get_record_section_label()); //010215
         object_to_remember->add_desired_variables(*this);
}
   // scan the list of known recording objects for the requesting object,
   // if it hasn't already added a recorder before, add the object to the list.
//______________________________________________________________________________
void Recorder_data_record::forget(Recording_object *object_to_forget)
{  delete_section(object_to_forget->get_record_section_label());              //010215
}
//______________________________________________________________________________
} // namespace CORN

