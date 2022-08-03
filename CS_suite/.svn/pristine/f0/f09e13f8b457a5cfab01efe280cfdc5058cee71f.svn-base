#include "ClimGen_settings.h"
#include "ClimGen/source/options.h"
#include "corn/data_source/vv_file.h"
#include "corn/data_source/datarec.h"

#define LABEL_last "last"
#define LABEL_options "options"
#define LABEL_language "language"
#define LABEL_location "location"
//______________________________________________________________________________
ClimGen_Settings::ClimGen_Settings()
: CORN::User_settings()
, language_code("en")
, recent_location("noname.loc")
, recent_database("noname.ued")
{}
//_______________________________________________ClimGen_Settings constructor__/
bool ClimGen_Settings::setup_structure
(CORN::Data_record &data_rec,bool for_write)            modification_
{  bool satup = CORN::User_settings::setup_structure(data_rec,for_write);	     //170808
   data_rec.set_current_section  (LABEL_options);
   data_rec.expect_string        (LABEL_language,language_code,0,0);
   data_rec.set_current_section  ("recent");
   data_rec.expect_file_name      (LABEL_location,recent_location);
   data_rec.expect_file_name      ("database",recent_database);
   data_rec.expect_directory_name
      ("import_directory",recent_import_directory
      #ifdef SINGLE_INHERITENCE
                  .name
      #endif
                  ,255);
   return satup;                                                                 //170808				
}
//____________________________________________________________setup_structure__/
ClimGen_Settings *ClimGen_settings;

