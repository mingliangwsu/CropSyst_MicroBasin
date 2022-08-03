#include "UED/library/UED_tuple_datasrc.h"
#include "UED/library/database_file.h"
#include "corn/data_source/datarec.h"
#include "corn/data_source/vv_entry.h"
#include "corn/chronometry/date_32.h"
#include "UED/library/datasetrec_creation.h"
#include "UED/library/timeqry.h"
#include "UED/library/variable_format.h"
//______________________________________________________________________________
namespace UED {                                                                  //110911
Tuple_data_source::Tuple_data_source
(Database_file_indexed *_database
,Record_code            _record_type_code                                        //040924
,UED_units_code         _time_step_units_code                                    //040924
,CORN::Quality_code     _default_attribute_code)                                 //040924
: Data_source()
, database(_database)
, field_creations()
, active_date_time(0)
, record_type_code(_record_type_code)                                            //040930
, time_step_units_code(_time_step_units_code)                                    //040930
, default_attribute_code(_default_attribute_code)                                //040930
{}
//______________________________________________________________________________
const char *Tuple_data_source::label_string(std::string &buffer)           const
{  buffer = database->get_file_name(); return buffer.c_str(); }
//_2003-01-23___________________________________________________________________
void Tuple_data_source::set_date(datetime64 date_time)
{ active_date_time.set_datetime64(date_time); }
//______________________________________________________________________________
Tuple_data_source::Field_creation *Tuple_data_source::get_field_creation
(  const char *_section_name
,  const char *_entry_name)
{
   FIND_FOR_EACH_IN(found_field_creation,field_creation,Field_creation,field_creations,true,each_field_creation)
      if ((field_creation->section == _section_name) && (field_creation->entry == _entry_name))
          found_field_creation = field_creation;
   FOR_EACH_END(each_field_creation)
   return  found_field_creation;
}
//_________________________________________________________get_field_creation__/
void Tuple_data_source::add_field
(const char *section_name
,const char *entry_name
,const Data_record_creation_layout *creation_layout
,bool  owns_creation_layout
,Units_code preferred_units)
{  // This establishes a field with the specified name.
   // This field will be used to create UED data records having the specified layout.
   // add_field should be called for each section/entry in Data_records encountered by this database.
   // When creating a database, fields should be set up (calling this function) before calling set()
   // If owns_creation layout is true, the Field_creation will own the creation layout and will
   // delete it when Field_creation is destroyed.
   Field_creation  * existing_field_creation= get_field_creation(section_name,entry_name);
   if (!existing_field_creation)
   {  Field_creation  * new_field_create = new Field_creation(section_name,entry_name,creation_layout,owns_creation_layout,preferred_units);
      field_creations.append(new_field_create);
   } else
   {  // because we we already have this field, if the creation layout was relinquished to this, we can delete the creation layout
      if (owns_creation_layout) delete creation_layout;
   }
}
//__________________________________________________________________add_field__/
void Tuple_data_source::add_field2
(const char           *section_name
,const char           *entry_name
,Variable_code        variable_code_
,Units_code           UED_stored_units_code_ // Units as stored in the database
,Units_code           UED_timestamp_step_units_code_)
{  // This establishes a field with the specified name.
   // This field will be used to create UED data records having the specified layout.
   // add_field should be called for each section/entry in Data_records encountered by this database.
   // When creating a database, fields should be set up (calling this function) before calling set()
   // If owns_creation layout is true, the Field_creation will own the creation layout and will
   // delete it when Field_creation is destroyed.

   Field_creation *existing_field_creation
      = get_field_creation(section_name,entry_name);
   if (!existing_field_creation)
   {  Field_creation  * new_field_create = new Field_creation(section_name,entry_name,
         new Data_record_creation_layout(record_type_code,variable_code_
            ,UED_stored_units_code_,time_step_units_code
            ,UED_timestamp_step_units_code_,default_attribute_code)
         ,true,UED_stored_units_code_);
      field_creations.append(new_field_create);
   }
   std::string description(entry_name);                                          //140904
   UED::Variable_format_0 field_variable_def                                     //140904
      (variable_code_,UED_stored_units_code_,-99999.9,99999.9,999999.9,-999999.9
      ,description.c_str(),entry_name);
   database->Database_file::include_var_code_def(field_variable_def);            //140904
}
//_2004-09-24___________________________________________________________________
bool Tuple_data_source::get(CORN::Data_record &/*unused data_rec*/ )
{  // This reads the data record from the current record position in the database
   // (I.e. current record in the database)
   // If the database is not in a state where is can read any data it returns false.
   // If the database could be read, but there were not maching entries (fields)
   // then it returns false.
   // Returns true if any record entries could be read.
   // Examine each data record entry to determine if it was encountered
   // in the data source.
   // NYI
   return true;                                                                  //030916
}
//________________________________________________________________________get__/
bool Tuple_data_source::set_data(CORN::Data_record &data_rec,bool )              //150503
{  //             This writes data from data_rec to this data source.
   //             Classes derived from Data_record may provide information such
   //             as the position of the record in the data file an the Data_source
   //             may then need to position the file pointer before writing the record.
   //             In classes such as VV_File, a Data_record constitutes all the data in
   //             a file, consequently the data can be written out to the file.
   //             Returns true if the record could be written.
   //             Returns true if there was a problem.
   //             This abstract method must be provided by a derived class.
   bool set=true;                                                                //050705
   CORN::Date_clad_32  active_jan1((Year)active_date_time.get_year(),(DOY)1);    //030911
   CORN::Date_clad_32 active_dec32((Year)active_date_time.get_year()
      ,(DOY)active_date_time.ref_date().days_in_this_year());                    //170825_030911_130225
   datetime64 low_date(active_jan1.get_datetime64());                            //010216
   datetime64 high_date(active_dec32.get_datetime64());                          //010216
   //041111 Note I think I can use UED_time_query single date now and would need the low and high
   //       but I am not sure in the case of daily.
   Time_query time_query
      (active_date_time.get_datetime64(),low_date,high_date,Time_query::at);     //010216
   FOR_EACH_IN(section,VV_Section,data_rec.sections,each_section)
   {  FOR_EACH_IN(entry,VV_abstract_entry,section->entries,each_entry)           //111108
      {  Field_creation *field_creation
            = get_field_creation
               (section->get_label/*180821 get_section_label*/().c_str(),entry->get_variable().c_str());
               //180820 (section->get_key(),entry->get_key());
         if (field_creation)
         {
            CORN::Quality_clad attribute(simulated_quality);                     //081212
            bool created = false;
            float32  store_value = 0;
            switch (entry->get_type())
            {
               case VV_int32 :                                                   //170602
               {   VV_int32_entry *int32_entry = (VV_int32_entry *)entry;        //170602
                  store_value =int32_entry->get_value();                         //170602
               } break;                                                          //170602
               case VV_float32 :
               {   VV_float32_entry *float32_entry = (VV_float32_entry *)entry;
                  store_value =float32_entry->get_value();
               } break;
               case VV_float64 :
               {  VV_float64_entry *float64_entry = (VV_float64_entry *)entry;
                  store_value =float64_entry->get_value();
               } break;
            } // end switch
            UED_units_code preferred_units = field_creation->preferred_units;
            database->set_value(store_value,time_query,preferred_units,attribute
               ,*(field_creation->creation_layout),created ,true  );
         } // end if
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   return set;
}
//___________________________________________________________________set_data__/
} // namespace UED

