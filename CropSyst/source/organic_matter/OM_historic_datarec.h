#ifndef OM_historic_datarecH
#define OM_historic_datarecH
#include "organic_matter/OM_params.h"
#include "corn/data_source/datarec.h"
//______________________________________________________________________________
/*  This is currently used only by REACCH but it will likely be
    needed for other projects where we need to run CropSyst under
    historical conditions to get the equilibrated OM conditions.
*/
class Historical_organic_matter_data_record
: public extends_ CORN::Data_record
{public:
   soil_horizon_array32(horizon_percent_organic_matter); //{ 0-10 (0-100) }      //CHEM
      //may eventually move horizon_percent_organic_matter
      //into Organic_matter_initialization_parameters
      //because right now there may be unnecessary multiple occurances 120909
   Organic_matter_initialization_parameters  organic_matter_initialization_parameters;
 public:
   inline Historical_organic_matter_data_record()
      : CORN::Data_record("historical_organic_matter")
      {}
   virtual void expect_structure(bool for_write);
};
//_2012-09-10___________________________________________________________________

#endif
