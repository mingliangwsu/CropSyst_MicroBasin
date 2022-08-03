#if (CS_VERSION >= 5)

#error Do not include this file in version 5 projects

This class will be obsolete
because it only defined the active_scenario_filename
now runs will be initiated
within the scenario directory which will define the active scenario
#else

#ifdef USE_PCH
#  include "corn/parameters/parameters_pch.h"
#else
#  include "corn/application/project.h"
#  include "corn/parameters/parameters_directory_OS_FS.h"
#endif
//______________________________________________________________________________
Common_project_parameters::Common_project_parameters
(/*180626 nat8 major_,nat8 release_,nat8 minor_*/)                                          //040210
: Common_parameters_data_record
   (REQUIRED_ASSOCIATED_DIRECTORY,"project",4/*180626 major_,release_,minor_*/)
{ }
//______________________________________________________________________________
bool Common_project_parameters::expect_structure(bool for_write)
{  bool expected = Common_parameters_data_record::expect_structure(for_write);   //020517
   structure_defined = false;                                                    //120314
   set_current_section(LABEL_recent);                                            //020328
      expect_file_name("active",active_filename);                                //121126_050326
   structure_defined = true;                                                     //120314
   return expected;                                                              //161023
}
//_2002-05-17___________________________________________________________________
const char *Common_project_parameters::get_primary_section_name() const
{  return LABEL_project; }
//_2002-09-17___________________________________________________________________
#endif
