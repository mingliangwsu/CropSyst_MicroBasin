#ifndef projectH
#define projectH
#if (CS_VERSION >= 5)
// This class would be obsolete because it only defined the active_file_name
   // active_scenario_filename will be obsolete because now runs will be initiated
   // within the scenario directory which will define the active scenario
#else

#ifndef parameters_datarecH
#  include "corn/parameters/parameters_datarec.h"
#endif
#include "corn/OS/directory_entry_name_concrete.h"

#define  LABEL_project              "project"
#define  LABEL_recent               "recent"

class Common_project_directory; // forward declaration
//______________________________________________________________________________
class Common_project_parameters
: public Common_parameters_data_record                                           //050322
{public:  // "recent" section

   CORN::OS::File_name_concrete active_filename;                                 //120322
 public:
   Common_project_parameters(/*180626 nat8 major,nat8 release,nat8 minor*/);
   virtual bool expect_structure(bool for_write = false);                        //981208
   virtual const char *get_primary_section_name()                         const; //020917
   //  Derived classes must s3pecify the fully qualified name of the project icon
   //050324 note eventually rename to get_active_filename
   inline virtual const CORN::OS::File_name &get_active_filename()         const //050324
      { return active_filename;}
};
//______________________________________________________________________________
#endif

#endif

