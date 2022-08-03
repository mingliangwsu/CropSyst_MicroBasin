#ifndef v_mgmtfileH
#define v_mgmtfileH
#include "mgmt_param.h"
#include "filenames.h"
//______________________________________________________________________________
class Valid_management_parameters
: public Management_parameters
{
public:
   Validation_status status;
   Valid_management_parameters ();
   Validation_status validate(const MGS_MGT_filename &file_name);
   // Returns true if the file is usable
   // Also validates all selected parameter files.
};
//______________________________________________________________________________
#endif
//v_mgmtfile.h

