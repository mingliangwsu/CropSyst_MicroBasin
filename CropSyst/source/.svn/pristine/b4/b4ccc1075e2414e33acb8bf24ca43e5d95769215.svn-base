#ifndef v_cropfileH
#define v_cropfileH
#include "crop_param.h"
#include "filenames.h"
//______________________________________________________________________________
class Valid_crop_parameters
: public Crop_parameters
{
public:
   Validation_status status;
   Valid_crop_parameters ();
   Validation_status validate(const CRP_filename &file_name);
   // Returns true if the file is usable
   // Also validates all selected parameter files.
};
//______________________________________________________________________________
#endif
//v_cropfile.h

