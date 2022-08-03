#include "corn/tabular/tabular.h"
#include "corn/data_source/datarec.h"
#define LABEL_label     "label"
#define LABEL_data_type "data_type"
#define LABEL_start     "start"
#define LABEL_width     "width"
#define LABEL_precision "precision"
#define LABEL_spread    "spread"
#define LABEL_columns   "columns"
#define LABEL_delimiter "delimiter"
namespace CORN {
//_____________________________________________________________________________/
Tabular_column::Tabular_column()
: Parameter_properties_string()                                                  //100116
, Parameter_number_properties()                                                  //100116
//not needed ?,Data_record("")                                                                    //160607
   // actually could pass column key/label
,data_type_labeled(DT_char)
,sheet("")                                                                       //061019
,start_1based(0)
,spread_over_columns(false)
,spread_columns(0)
,missing_value("missing")                                                        //070524
{}
//_____________________________________________________________________________/
bool CORN::Tabular_column::setup_structure(Data_record &data_rec,bool for_write )
{   //probably need to set section here
   Parameter_properties_string::setup_structure(data_rec,for_write);             //100116
   Parameter_number_properties::setup_structure(data_rec,for_write);             //100116
   if (!for_write) // I am now using Parameter_properites which uses 'name'
      data_rec.expect_string(LABEL_label            ,name_long,255); // rename this to name
   data_rec.expect_int16 (LABEL_start               ,start_1based);
   data_rec.expect_enum  (LABEL_data_type           ,data_type_labeled);         //020505
   data_rec.expect_bool  (LABEL_spread              ,spread_over_columns,VV_bool_entry::form_true);
   data_rec.expect_int16 (LABEL_columns             ,spread_columns);
   data_rec.expect_string("missing"                 ,missing_value,255);         //070524
   data_rec.expect_string("sheet"                   ,sheet,255);                 //061019
   data_rec.expect_uint16("width"                   ,field_width,10);            //141014
   return true;
}
//____________________________________________________________setup_structure__/
Tabular_data_column::Tabular_data_column(CORN::Tabular_column  &_layout)
: TC_layout(_layout)
,value_bool(false)
,value_string("")
,value_float32(0.0)
,value_float64(0.0)
,value_datetime()
,date_format(0)                                                                  //170531
,time_format(0)                                                                  //170531
,value_int16(0)
,value_int32(0)
,validation_status(unavailable_status)                                           //050518
{}
//____________________________________________constructor Tabular_data_column__/
Tabular_data_column::~Tabular_data_column()
{  delete date_format;
   delete time_format;
}
//_____________________________________________destructor Tabular_data_column__/
float32 Tabular_data_column::get_value_as_float32() const
{  float32 result = 0.0;
   switch (TC_layout.data_type_labeled.get())
   {
      //NYI        case CORN::DT_int8                             : result = (float32)value_int16; break; //090416
      case CORN::DT_int16   : result = (float32)value_int16; break;
      case CORN::DT_int32   : result = (float32)value_int32; break;
      //NYI /*090416_*/       case CORN::DT_nat8
      case CORN::DT_nat16   : result = (float32)value_int16; break;              //090416
      case CORN::DT_nat32   : result = (float32)value_int32; break;              //090416
      case CORN::DT_float32 : result =          value_float32 ; break;
      case CORN::DT_float64 : result = (float32)value_float64 ; break;
      /*
      case CORN::DT_date    : result = (float32)value_int32; break;              //170525
      case CORN::DT_time    : result = (float32)value_int32; break;              //170525
      case CORN::DT_datetime: result = (float32)value_float64; break;            //170525
      */
      case CORN::DT_date    : result = (float32)value_datetime.get_datetime64(); break;
      case CORN::DT_time    : result = (float32)value_datetime.get_datetime64(); break;
      case CORN::DT_datetime: result = (float32)value_datetime.get_datetime64(); break;
      //probably could do string but not currently needed in this context
      default : /* other non numeric types are not handled here */  break;       //090416
   }
   return result;
}
//_______________________________________________________get_value_as_float32__/
int16 Tabular_data_column::get_value_as_int16() const
{  int16 result = 0.0;
   switch (TC_layout.data_type_labeled.get())
   {
      //NYI        case CORN::DT_int8   : result = (int16)value_int8; break;
      case CORN::DT_int16   : result = (int16)value_int16; break;
      case CORN::DT_int32   : result = (int16)value_int32; break;
      //NYI        case CORN::DT_nat8   : result = (int16)value_nat8; break;
      case CORN::DT_nat16   : result = (int16)value_int16; break;  // Current don't have nat16 and nat32 buffers
      case CORN::DT_nat32   : result = (int16)value_int32; break;
      default : /* other non numeric types are not handled here */  break; //090416
   }
   return result;
}
//_2005-04-12____________________________________________get_value_as_float32__/
int16 Tabular_data_column::set_int_value(int16 from_int16) modification_
{  // This simply sets each of the integer union elements (In case user ever changes the integer type of the field (I.e. as defined TDF file)
   value_int16 = from_int16;
   value_int32 = from_int16;
   return from_int16;
}
//_2007-02-03___________________________________________________set_int_value__/
float32 Tabular_data_column::set_float_value(float32 from_float32) modification_
{   // This simply sets each of the integer union elements (In case user ever changes the integer type of the field (I.e. as defined TDF file)
    value_float32 = from_float32;
    value_float64 = from_float32;
    value_int16 = (int16)from_float32;
    value_int32 = (int32)from_float32;
    return from_float32;
}
//_2007-02-03_________________________________________________set_float_value__/
float64 Tabular_data_column::set_float64_value(float64 from_float64) modification_
{   // This simply sets each of the integer union elements (In case user ever changes the integer type of the field (I.e. as defined TDF file)
    value_float32 = from_float64;
    value_float64 = from_float64;
    value_int16 = (int16)from_float64;
    value_int32 = (int32)from_float64;
    return from_float64;
}
//_2014-10-21_______________________________________________set_float64_value__/
void Tabular_data_column::clear_values()
{  value_float32 = 0.0;
   value_float64 = 0.0;
   value_int16 = 0;
   value_int32 = 0;
   value_bool = false;
   value_string.assign("");
   value_datetime.set_date32(0);  // Use for date, time and datetime values.
   validation_status = unavailable_status;
}
//_2010-01-26____________________________________________________clear_values__/
} // namespace CORN

