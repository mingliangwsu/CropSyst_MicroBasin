#include "corn/parameters/parameters_datarec.h"
#define LABEL_version      "version"
#define  LABEL_major          "major"
#define  LABEL_release        "release"
#define  LABEL_minor          "minor"
#define LABEL_GUI          "GUI"
#define  LABEL_top            "top"
#define  LABEL_left           "left"
#define  LABEL_width          "width"
#define  LABEL_height         "height"
using namespace CORN;
//______________________________________________________________________________
Common_parameters_data_record::Common_parameters_data_record
(Associated_directory_mode associated_directory_mode_                            //060620
,const char *              primary_section_name_
,nat32                     version_code_                                         //180626
//180626 now using date ,nat8 _major ,nat8 _release,nat8 _minor
) /* = "-" */
: CORN::Data_record(primary_section_name_)
, Common_parameters
(associated_directory_mode_                                                      //060620
,version_code_                                                                   //180626
//180626 now using date ,_major , _release, _minor
)
{}
//______________________________________________________________________________
const char *Common_parameters_data_record::get_primary_section_name()      const
{  return Data_record::get_primary_section_name();
}
//_2007-05-08___________________________________________________________________
bool Common_parameters_data_record::expect_structure(bool for_write)
{
   bool expected = Data_record::expect_structure(for_write);                     //161023
   set_current_section("version");                                               //180626
      expect_nat32("code"     ,version_code,10);                                 //180626
      expect_date("program"  ,version_program_date);                             //180626

      #if ((CS_VERSION > 0) && (CS_VERSION < 6))
      // We used to have major,minor,release idiom
      if (!for_write)                                                            //180626
         expect_nat32("major"  ,version_code,10);                                //180626
      #endif

/*180626
   #if (CS_VERSION == 4)
   expected &= data_source_version.setup_structure(*this,for_write);                         //140114
   #else
   expect_nat32("version",data_source_version_number,10);                        //150921
   #endif
*/
   set_current_section(get_primary_section_name());
      expect_string("details_URL",description.details_URL,255);                  //080502
      setup_parameters(*this,for_write);
   structure_defined = true;                                                     //120314
   return expected;
}
//______________________________________________________________________________
void Common_parameters_data_record::setup_parameters
(CORN::Data_record &data_rec,bool for_write)                       modification_
{
// 041106  For cropSyst operations we need to use data_rec.expect_string, I am not sure if this
//          is the case for parameter files
   data_rec.expect_string("description",description.brief,MAX_DESCRIPTION_LENGTH);//150111
}
//______________________________________________________________________________
bool Common_parameters_data_record::set_start()
{
/*180626
   // We currently always write to the current version
   // set the IO version numbers to the current version.
   #if (CS_VERSION == 4)
   data_source_version.major_    = current_program_version.major_;
   data_source_version.release_  = current_program_version.release_;
   data_source_version.minor_    = current_program_version.minor_;
   #else
   data_source_version_number = current_program_version_number;                  //150921
   #endif
*/
   version_program_date.set(version_program_date_curr);                          //180626
   return Data_record::set_start();                                              //161023
}
//______________________________________________________________________________
/*180626 This is obsolete.
Now file version upgrading is handle using upgrade/conversion utilities

bool Common_parameters_data_record::get_end()
{  bool ended = Data_record::get_end();                                          //161023


   // After reading, we will check if the read file version does not match the current version.
   // If not we update section and entries that may have been moved or renamed.
   nat16 count = 0;
   nat32 IO_version_code =
       #if (CS_VERSION == 4)
         (data_source_version.major_ << 16) | (data_source_version.release_ << 8) | data_source_version.minor_ ;
       #else
         data_source_version_number;                                             //150921
       #endif
   Section_entry_change *changes =get_section_entry_changes(count);
   for (int i = 0; i < count; i++)
   {  // Check to see if this file's version is less than the program version the change occured
      nat32 changes_version_code = (changes[i].major_ << 16) | (changes[i].release_<< 8) | changes[i].minor_ ;
      if (IO_version_code < changes_version_code)
      {  VV_Section *old_section = set_current_section(changes[i].old_section);
         if (old_section)
         {  VV_abstract_entry *old_entry   = (VV_abstract_entry *)old_section->entries.find_cstr(changes[i].old_entry);
            if (old_entry)
            {  VV_Section *new_section = set_current_section(changes[i].new_section);
               if (new_section)
               {  VV_abstract_entry *new_entry   = (VV_abstract_entry *)new_section->entries.find_cstr(changes[i].new_entry);
                  if (new_entry)
                  {  std::string buffer;                                         //140615
                     old_entry->append_to_string(buffer);                        //140615
                     new_entry->set_string(buffer);                              //140615
   }  }  }  }  }  }
   return ended;                                                                 //161023
}
*/
//______________________________________________________________________________
