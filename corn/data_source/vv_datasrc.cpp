#include "corn/data_source/vv_datasrc.h"
#include "corn/data_source/datarec.h"

// NYI rename buffer to text
namespace CORN
{
//______________________________________________________________________________
VV_Data_source::VV_Data_source()
: current_section(0)
, inheritance(false)                                                             //160128
{}
//______________________________________________________________________________
VV_Data_source::Submission_status VV_Data_source::submit
(Data_record &data_rec
,const std::string &buffer
,bool unexpected_only)                                               submission_
{  VV_Data_source::Submission_status status = VV_Data_source::unrecognized;
   bool expected_item = false;
   size_t right_bracket_pos = buffer.find("]");

   if (!current_section) current_section = data_rec.get_current_section();       //161016
   if ((buffer.c_str()[0] == '[') && (right_bracket_pos != std::string::npos))    //010108
   {  status = VV_Data_source::section_unknown;
      std::string new_section_name;                                              //040909
      size_t left_bracket_pos = buffer.find("[");                                //090605
      size_t label_len = (right_bracket_pos - left_bracket_pos) - 1;             //090605
      new_section_name.assign(buffer,1,label_len);
      inheritance = false;                                                       //160210
         // Since we are at a new section (in the current file),
         // we are done with any inheritance
      if (new_section_name == "inherit")
         inheritance = true;
      else
      {
/*debug
if (new_section_name=="harvest:1")
std::clog << "reached harvest:1" << std::endl;
*/
        current_section = data_rec.set_current_section(new_section_name.c_str());//030109
         if (current_section)                                                    //120311
         {  current_section->set_encountered(true);                              //020419
            status = VV_Data_source::section_known;
         }
      }
   } else
   {  size_t equal_pos = buffer.find("=");
      if (equal_pos != std::string::npos)
      {  status = VV_Data_source::entry_unknown;                                 //130401
         std::string key(buffer,0,equal_pos);                                    //040909
         std::string value(buffer,equal_pos+1,buffer.length());                  //040909
         if (inheritance)
         {
            data_rec.inherits.add_string(value);                                 //170721
            if (recurse_inheritance)                                             //170724
            {
               // It is necessary to turn off the inheritance flag
               // while loading inherited files, otherwise we keep assuming
               // the next entry is inherit file enumeration.
               inheritance = false;                                              //160210
               inherit(data_rec,key,value);                                      //160128
               inheritance = true;                                               //160210
            }
         }
         else                                                                    //160128
         {
         size_t count_pos = key.find(":count");
         if (count_pos != std::string::npos)                                     //131020
         {  std::string enumerated_section_name(key,0,count_pos);                //040909
            VV_enumerated_section *enum_sect = (VV_enumerated_section *)data_rec //030117
            .enumerated_sections_definitions.find_string(enumerated_section_name);
            if (enum_sect)
            {  status = VV_Data_source::entry_known;
               nat16 count = (nat16)atoi(value.c_str());
               enum_sect->set_count(count,unexpected_only);
               if (count)                                                        //120314
                  enum_sect->setup_structure(data_rec,false);
            }
         }
         if (current_section)                                                    //120311
         {  VV_base_entry *entry =                                               //130401
               current_section->set_entry(key.c_str(),value.c_str(),unexpected_only);
            const VV_unexpected_entry *unexpected_entry = dynamic_cast<const VV_unexpected_entry *>(entry); //130401
            status = unexpected_entry ? VV_Data_source::entry_unknown : VV_Data_source::entry_known;             //130401
         }
         }
      } else
         if (current_section)                                                    //120311
         {  current_section->set_entry("",buffer.c_str(),unexpected_only);       //030117
            status = VV_Data_source::entry_unknown ;                             //130401
         }
   }
   return status;
}
//_2013-04-01______________________________________________________parse_item__/
} // namespace CORN
