#ifndef import_columnH
#define import_columnH
#include "imp_exp.h"
#include "UED/library/UED.h"
namespace UED
{
//______________________________________________________________________________
class Import_column
:public UED::Imp_exp_column
{
 public:
   const UED::Data_record_creation_layout  *creation_layout; bool creation_layout_owned;
   // May be 0 if not a data series column
   //   I.e. if does not have UED record code, such as a station_ID column
 public:
   Import_column
      (ED_tabular_file_format::Column   &_layout
      ,Record_code            _record_type_code       // I.e. UED_record_type_distinguisher::UED_data_set_year_var_units
      ,UED_units_code         _time_step_units_code   // this is usually known from the UED_tabular_file_format
      ,UED_units_code         _time_stamp_step_units_code                        //050413
      ,CORN::Quality_code     _default_attribute_code // this is usually known from the UED_tabular_file_format
      ,const UED::Data_record_creation_layout *recognized_creation_layout);      //100125
   virtual ~Import_column();
};
//______________________________________________________________________________
} // namespace UED
#endif

