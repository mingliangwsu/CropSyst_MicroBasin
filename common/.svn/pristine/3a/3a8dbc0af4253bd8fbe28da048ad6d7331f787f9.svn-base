#include <common/recorder/recorder.h>
#include <corn/string/strconv.h>
#include <UED/library/varcodes.h>

namespace CORN {
char RECORDER_var_code_hex_buffer[20];
//______________________________________________________________________________
Recorder_base::Recorder_base
(UED_variable_code   _variable_code
,UED_units_code      _units_code
,UED_units_code      _value_units
,Record_code         _record_type_code)
: UED::Data_record_creation_layout
    (_record_type_code
    ,_variable_code//.get()
    ,_units_code//.get()
    ,UT_day
    ,UT_year   // time_stamp_step
    ,simulated_quality)
   ,value_units(_value_units)
{};
//_2001-02-13___________________________________________________________________
Recorder_float64::Recorder_float64
(float64            &_value_to_record
,const char         *_descriptive_var
,UED_variable_code   _variable_code
,UED_units_code      _units_code   // this is the units as stored in the database
,UED_units_code      _value_units  // this is the current units for the recorded value
,Record_code         _record_type_code
)
: Recorder_base(_variable_code,_units_code,_value_units,_record_type_code)
, VV_float64_entry
      (_descriptive_var
      ,_value_to_record
      ,0//CORN::Units_clad(i_units_code).label(label_buffer).c_str()
      ,0)//UED_smart_variable_code(i_variable_code).label(label_buffer).c_str())
{  char units_buffer[100];
   CORN::Units_clad(_units_code).label_cstr(units_buffer);
   annotation1.assign(units_buffer);
   UED::Smart_variable_code(_variable_code).label_cstr(units_buffer);
   annotation2.assign(units_buffer);
};
//_2003-01-23__2001-02-13_______________________________________________________
Recorder_float32::Recorder_float32
(const float32       &_value_to_record
,const char          *descriptive_var
,UED_variable_code    _variable_code
,UED_units_code       _units_code
,UED_units_code       _value_units
,Record_code          _record_type_code)
: Recorder_base(_variable_code,_units_code,_value_units,_record_type_code)
, VV_float32_entry
      (descriptive_var
      ,const_cast<float &>( i_value_to_record )
      ,(const char *)0
      ,(const char *)0)
{  char units_buffer[100];
   CORN::Units_clad(_units_code).label_cstr(units_buffer);
   annotation1.assign(units_buffer);
   UED::Smart_variable_code(_variable_code).label_cstr(units_buffer);
   annotation2.assign(units_buffer);
};
//_2003-01-23__2001-02-13_______________________________________________________
Recording_object::Recording_object()
{ };
//______________________________________________________________________________
nat32  Recording_object::compose_variable_code
(CORN::Quality_code quality
,nat8    class_group    // 4 bits
,nat32   class_code     // 0 to 20 bits
,nat32   variable_num)  // 0 to 20 bits
{  nat32  vc= (quality << 24) | (class_group << 20) | class_code | variable_num;
   return vc;
};
//_2001-04-18______________________________________________________________________________
}; // namespace CORN
