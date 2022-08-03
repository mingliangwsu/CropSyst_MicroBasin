#ifndef CS_variablesH
#define CS_variablesH

#include "UED/library/variable.h"
#include "UED/library/datasetrec_creation.h"
//______________________________________________________________________________
struct CropSyst_variable_definition_and_creation
{
      UED_variable_code                 variable_code;
      UED::Variable_definition_constant  definition;
      UED::Data_record_creation_options *creation;
      // The following are when stored in data records
      const char *                      section;
      const char *                      entry;
};
//______________________________________________________________________________
#endif

