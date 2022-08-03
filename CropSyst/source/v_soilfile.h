#ifndef v_soilfileH
#define v_soilfileH

#include "soil_param.h"
#include "filenames.h"
//______________________________________________________________________________
class Valid_soil_parameters
: public Smart_soil_parameters
{public:
   Validation_status status;
   Valid_soil_parameters();
   Validation_status validate(const SIL_filename &file_name);
     // Returns true if the file is usable
      // Also validates all selected parameter files.
};
//______________________________________________________________________________
#endif
//v_soilfile.h

