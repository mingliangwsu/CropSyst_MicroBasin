#include "UED/library/datasetrec_creation.h"

namespace UED {
//______________________________________________________________________________
Data_record_creation_layout::Data_record_creation_layout
(CORN::Record_code      record_type_code_
,UED_variable_code      variable_code_
,UED_units_code         stored_units_code_
,UED_units_code         timestep_units_code_
,UED_units_code         time_stamp_step_units_code_
,CORN::Quality_code     default_attribute_code_)
:Record_type_distinguisher_interface()
, smart_record_type(record_type_code_)
{  variable_code                       =variable_code_;
   options.record_type                 =record_type_code_;
   options.stored_units_code           =stored_units_code_;
   options.timestep_units_code         =timestep_units_code_;
   options.time_stamp_step_units_code  =time_stamp_step_units_code_;
   options.default_attribute_code      =(uint8)default_attribute_code_;
}
//_2007-02-14___________________________________________________________________
Data_record_creation_layout::Data_record_creation_layout
(const Data_record_creation_parameters &creation_parameters)
: smart_record_type(creation_parameters.options.record_type)
{  options.record_type               =creation_parameters.options.record_type;
   variable_code                     =creation_parameters.variable_code;
   options.stored_units_code         =creation_parameters.options.stored_units_code;
   options.timestep_units_code       =creation_parameters.options.timestep_units_code;
   options.time_stamp_step_units_code=creation_parameters.options.time_stamp_step_units_code;
   options.default_attribute_code    =creation_parameters.options.default_attribute_code;
}
//_2007-02-14___________________________________________________________________
Data_record_creation_layout::Data_record_creation_layout() // default constructor (Don't use)
:Record_type_distinguisher_interface()
, smart_record_type(0)
{  options.record_type               =0;
   variable_code                     =0;
   options.stored_units_code         =0;
   options.timestep_units_code       =0;
   options.time_stamp_step_units_code=UT_year;
   options.default_attribute_code    =0;
}
//_2007-02-14_1997-09-09________________________________________________________
Smart_record_code &Data_record_creation_layout::get_record_type()          const
{  smart_record_type.set_code(options.record_type);
   return smart_record_type;
}
//_2007-02-14___________________________________________________________________
} // namespace UED

