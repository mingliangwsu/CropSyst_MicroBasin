#ifndef recorderH
#define recorderH
#ifndef UED_H
#  include <UED/library/UED.h>
#endif
#ifndef UED_DATASETREC_CREATION_H
#  include <UED/library/datasetrec_creation.h>
#endif
#ifndef VV_entryH
#  include <corn/data_source/vv_entry.h>
#endif
#ifndef UED_UNITCONV_H
#  include <corn/measure/unitconv.h>
#endif

// These classes are used by simulation models to record daily results to
// Data sources

// The Recorder is not UED database specific,
// but we will use UED data structures, variable and units codes to
// store recorded data in memory.

namespace CORN {
class Recorder_data_record; // forward dec
//______________________________________________________________________________
class Recorder_base
: public UED::Data_record_creation_layout                                        //010213
, public Units_convertor
{
   CORN::Units_clad value_units;
   // The units the value has may be different than the
   // units desired to store in the database.
 public:
   Recorder_base
      (UED_variable_code   _variable_code                                          //010213
      ,UED_units_code      _database_units_code
      ,UED_units_code      _value_units
      ,Record_code         _record_type_code);
   inline UED_units_code get_value_units_code()                            const { return value_units.get();};
};
//_2001-04-21______________________________________________________________________________
class Recorder_float64
: public Recorder_base                                                           //010213
, public VV_float64_entry
{public:
   Recorder_float64
      (float64                  &_value_to_record                               //010213
      ,const char               *_descriptive_var
      ,UED_variable_code         _variable_code
      ,UED_units_code            _database_units_code
      ,UED_units_code            _value_units
      ,Record_code               _record_type_code);
};
//______________________________________________________________________________
class Recorder_float32
: public Recorder_base                                                           //010213
, public VV_float32_entry
{public:
   Recorder_float32
      (const float32          &_value_to_record                                  //010213
      ,const char             *descriptive_var
      ,UED_variable_code       _variable_code
      ,UED_units_code          _database_units_code
      ,UED_units_code          _value_units
      ,Record_code             _record_type_code);
};
//______________________________________________________________________________
class  Recording_object
{public:
   Recording_object();
   virtual const char *get_record_section_label()                       const = 0;//010215
     // Derived classes must override and return a label for the section the data is stored in.
   virtual void add_desired_variables(Recorder_data_record &to_data_record) = 0;
     // The recording object will scan the list of desired variables
     // If a variable is maintained by the object, it will create a recorder for it
     // and add it to the database.

     // A database may request this action at any time
     // (Usually at the beginning of the year)
  virtual uint32 compose_variable_code                                          //010215
     (CORN::Quality_code  quality
     ,uint8               class_group // 4 bits
     ,uint32              class_code  // 0 to 20 bits
     ,uint32              variable_num); // 0 to 20 bits
};
//______________________________________________________________________________
} // namespace CORN

#endif
// recorder.h

