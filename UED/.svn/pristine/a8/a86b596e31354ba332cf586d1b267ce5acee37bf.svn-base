#include "UED/library/locrec.h"
#include "UED/library/UED.h"
#include "corn/format/binary/binary_file_interface.h"
namespace UED {
//______________________________________________________________________________
Geolocation_record::Geolocation_record()
: Record_base(UED_geolocation_information)
, Geolocation()
{}
//______________________________________________________________________________
Geolocation_record::Geolocation_record(const Geolocation& copy_from)
: Record_base(UED_geolocation_information)
, Geolocation(copy_from)
{}
//_2005-05-03___________________________________________________________________
Geolocation_record* Geolocation_record::clone()                            const
{ return new Geolocation_record(*this); }
//_2014-01-16___________________________________________________________________
uint32 Geolocation_record::compute_record_body_size()           const
{ // Returns the size of the record body (not including the header).
   uint32 size = sizeof(available_data);
   if (has_geocoordinates())     size += sizeof(latitude_dec_deg) +sizeof(longitude_dec_deg) +sizeof(elevation);
   if (has_screening_height())   size += sizeof(screening_height_32);            //100519
   if (has_geopolitical_codes()) size += sizeof(country_code_ISO3166) +sizeof(state_code) +sizeof(county_code);
   if (has_geopolitical_names()) size += (country_name.length()+1) +(state_name.length()+1) +(county_name.length()+1);
   if (has_station_number())     size += sizeof(Geolocation::ID /*station_number*/);
   if (has_station_ID_code())    size += station_ID_code.length()+1;             //031217
   if (has_station_name())       size += station_name.length()+1;
   if (has_comment())            size += comment.length()+1;                     //100108
   return size;
}
//_2000-10-08___________________________________________________________________
bool Geolocation_record::read_body(Binary_file_interface &parent_database) // Binary_file_interface_replacing_Binary_fstream
{  available_data = parent_database.read_nat32();
   if (has_geocoordinates())
   {  latitude_dec_deg  = parent_database.read_float32();
      longitude_dec_deg = parent_database.read_float32();
      elevation = parent_database.read_float32();
   }
   if (has_screening_height())                                                   //100519
      screening_height_32 = parent_database.read_float32();                      //100519
   if (has_geopolitical_codes())
   {  country_code_ISO3166 = parent_database.read_nat16();
      state_code = parent_database.read_nat16();
      county_code = parent_database.read_nat16();
         //County code should be 32bit, need to use 32bit in the next version 140505
   }
   if (has_geopolitical_names())
   {
      parent_database.read_string(country_name ,ASCII_Z_string);                 //100014
      parent_database.read_string(state_name   ,ASCII_Z_string);                 //100014
      parent_database.read_string(county_name  ,ASCII_Z_string);                 //100014
   }
   if (has_station_number())                                                     //031217
      ID /*station_number*/ = parent_database.read_nat32();                      //031217
   if (has_station_ID_code())                                                    //031217
   {                                                                             //031217
       parent_database.read_string(station_ID_code,ASCII_Z_string);              //031217
   }                                                                             //031217
   if (has_station_name())
   {
      parent_database.read_string(station_name,ASCII_Z_string);
   }
   if (has_comment())                                                            //100108
   {
      parent_database.read_string(comment,ASCII_Z_string);
   }
   return true;
}
//______________________________________________________________________________
void Geolocation_record::write_body(Binary_file_interface &parent_database) // Binary_file_interface_replacing_Binary_fstream
{  parent_database.write_nat32(available_data);
   if (has_geocoordinates())
   {  parent_database.write_float32(latitude_dec_deg);
      parent_database.write_float32(longitude_dec_deg);
      parent_database.write_float32(elevation);
   }
   if (has_screening_height())                                                   //100519
      parent_database.write_float32(screening_height_32);                        //100519
   if (has_geopolitical_codes())
   {  parent_database.write_nat16(country_code_ISO3166);
      parent_database.write_nat16(state_code);
      parent_database.write_nat16((nat16)county_code);                                  //140505
         //County code should be 32bit, need to use 32bit in the next version 140505
   }
   if (has_geopolitical_names())
   {  parent_database.write_string(country_name,ASCII_Z_string);                 //100014
      parent_database.write_string(state_name,ASCII_Z_string);                   //100014
      parent_database.write_string(county_name,ASCII_Z_string);                  //100014
   }
   if (has_station_number())                                                     //031217
      parent_database.write_nat32(ID /*station_number*/);                        //031217
   if (has_station_ID_code())                                                    //031217
      parent_database.write_string(station_ID_code,ASCII_Z_string);              //100014
   if (has_station_name())
      parent_database.write_string(station_name,ASCII_Z_string);                 //100014
   if (has_comment())                                                            //100105
      parent_database.write_string(comment,ASCII_Z_string);                      //100014
}
//______________________________________________________________________________
bool Geolocation_record::is_more_complete_than(const Geolocation_record &other_geolocation_record) affirmation_
{
   if (has_geocoordinates()    && !other_geolocation_record.has_geocoordinates())      return true;
   if (has_screening_height()  && !other_geolocation_record.has_screening_height())    return true;
   if (has_geopolitical_codes()&& !other_geolocation_record.has_geopolitical_codes())  return true;
   if (has_geopolitical_names()&& !other_geolocation_record.has_geopolitical_names())  return true;
   if (has_station_number()    && !other_geolocation_record.has_station_number())      return true;
   if (has_station_ID_code()   && !other_geolocation_record.has_station_ID_code())     return true;
   if (has_station_name()      && !other_geolocation_record.has_station_name())        return true;
   if (has_comment()           && !other_geolocation_record.has_comment())             return true;

   if (!has_geocoordinates()    && other_geolocation_record.has_geocoordinates())      return false;
   if (!has_screening_height()  && other_geolocation_record.has_screening_height())    return false;
   if (!has_geopolitical_codes()&& other_geolocation_record.has_geopolitical_codes())  return false;
   if (!has_geopolitical_names()&& other_geolocation_record.has_geopolitical_names())  return false;
   if (!has_station_number()    && other_geolocation_record.has_station_number())      return false;
   if (!has_station_ID_code()   && other_geolocation_record.has_station_ID_code())     return false;
   if (!has_station_name()      && other_geolocation_record.has_station_name())        return false;
   if (!has_comment()           && other_geolocation_record.has_comment())             return false;


/*
         has_geocoordinates()    && !other_geolocation_record.has_geocoordinates()
      || has_screening_height()  && !other_geolocation_record.has_screening_height()
      || has_geopolitical_codes()&& !other_geolocation_record.has_geopolitical_codes()
      || has_geopolitical_names()&& !other_geolocation_record.has_geopolitical_names()
      || has_station_number()    && !other_geolocation_record.has_station_number()
      || has_station_ID_code()   && !other_geolocation_record.has_station_ID_code()
      || has_station_name()      && !other_geolocation_record.has_station_name()
      || has_comment()           && !other_geolocation_record.has_comment();
*/
   return true;                                                                  //140612
}
//_104-06-08____________________________________________________________________
using namespace std;
#ifdef UED_DUMP
void Geolocation_record::dumpX(std::ostream &txt_strm)
{
   Record_base::dumpX(txt_strm);
   txt_strm << "| Location information record" << endl;
   txt_strm << hex << available_data << "h | available data" << endl;
   txt_strm << "geocoordinates:";
   if (available_data & avail_geocoordinates)
   {  txt_strm << endl;
      txt_strm << "   latitude:" << latitude_dec_deg <<  " dec deg" <<endl;
      txt_strm << "   longitude:" << longitude_dec_deg << " dec deg" << endl;
      txt_strm << "   elevation:" << elevation << " m" << endl;
   } else
   {  txt_strm << "{none}" << endl; }
   txt_strm << "geopolitical codes:";
   if (available_data & avail_geopolitical_codes)
   {  txt_strm << endl;
      txt_strm << "   country:" << country_code_ISO3166  <<endl;
      txt_strm << "   state:" << state_code  << endl;
      txt_strm << "   county:" << county_code<< endl;
   } else
   {  txt_strm << "{none}" << endl; }
   txt_strm << "geopolitical names:";
   if (available_data & avail_geopolitical_names)
   {  txt_strm << endl;
      txt_strm << "   country:" << country_name <<endl;
      txt_strm << "   state:" << state_name  << endl;
      txt_strm << "   county:" << county_name << endl;
   } else
   {  txt_strm << "{none}" << endl; }
   txt_strm << "station number:";
   if (available_data & avail_station_number)
   {  txt_strm << endl;
      txt_strm << ID /*140612 station_number*/ <<endl;
   } else
   {  txt_strm << "{none}" << endl; }
   txt_strm << "station name:";
   if (available_data & avail_station_number)
   {  txt_strm << endl;
      txt_strm << station_name <<endl;
   } else
   {  txt_strm << "{none}" << endl; }
   txt_strm << "station ID:";
   if (available_data & avail_station_ID_code)
   {  txt_strm << endl;
      txt_strm << station_ID_code <<endl;
   } else
   {  txt_strm << "{none}" << endl; }
   txt_strm << "comment:" ;
   if (available_data & avail_comment)
   {  txt_strm << endl;
      txt_strm << comment <<endl;
   } else
   {  txt_strm << "{none}" << endl; }
}
//______________________________________________________________________________
#endif
void Geolocation_record::write_YAML(std::ostream &YAML_strm,nat16 indent_level)
{
   std::string indent(indent_level,' ');


   Record_base::write_YAML(YAML_strm,indent_level);

   //YAML_strm<< indent  << "hex << available_data << "h | available data" << endl;
   YAML_strm<< indent  << "geocoordinate: ";
   if (available_data & avail_geocoordinates)
   {  YAML_strm<<indent  << endl;
      YAML_strm<<indent << " latitude: " << latitude_dec_deg <<  " # dec deg" <<endl;
      YAML_strm<<indent << " longitude: " << longitude_dec_deg << " # dec deg" << endl;
      YAML_strm<<indent << " elevation: " << elevation << " # m" << endl;
   } else
   {  YAML_strm<<indent << "# none" << endl; }
   if ( (available_data & avail_geopolitical_codes)
      ||(available_data & avail_geopolitical_names))
      YAML_strm << "geopolitical:" << endl;
   {
      if (available_data & avail_geopolitical_codes)
      {
         YAML_strm<<indent << " code:" << std::endl;
         YAML_strm<<indent << "  country:"<< country_code_ISO3166  <<endl;
         YAML_strm<<indent << "  state:"  << state_code  << endl;
         YAML_strm<<indent << "  county:" << county_code<< endl;
      }
      if (available_data & avail_geopolitical_names)
      {
         YAML_strm<<indent << " name:" << std::endl;
         YAML_strm<<indent << "  country:" << country_name <<endl;
         YAML_strm<<indent << "  state:" << state_name  << endl;
         YAML_strm<<indent << "  county:" << county_name << endl;
      }
   }
   if (  (available_data & avail_station_number)
       ||(available_data & avail_station_ID_code)
       ||(available_data & avail_station_number))
   {
      YAML_strm<<indent << "station:";
      if (available_data & avail_station_number)
         YAML_strm<<indent << " number: "  << ID <<endl;
      if (available_data & avail_station_number)
         YAML_strm<<indent << " name: " << station_name <<endl;
      if (available_data & avail_station_ID_code)
         YAML_strm<<indent << " ID:" << station_ID_code <<endl;
   }
   if (available_data & avail_comment)
      YAML_strm<<indent << "comment:" << comment <<endl;
}
//_2018-01-08__________________________________________________________________/
//______________________________________________________________________________
} // namespace UED

