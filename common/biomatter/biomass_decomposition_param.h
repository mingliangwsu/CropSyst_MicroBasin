#ifndef biomass_decomposition_paramH
#define biomass_decomposition_paramH
#include "organic_matter/OM_types.h"
#include "corn/parameters/parameters_datarec.h"
#include "common/residue/residue_const.h"
#include "corn/validate/validtyp.h"
//______________________________________________________________________________
class Biomass_decomposition_parameters
: public Common_parameters_data_record
{
public: // composition DryWt basis!
   Organic_matter_composition_decomposition composition_decomposition;           //080908
public: // virtual overrides
   inline virtual const char *get_type_label()                                   const { return "CropSyst manure";} //051011
public: // decomposition
   //NYN   float32                    area_to_mass_ratio_after_application;
   //NYN/  Valid_float32 v_area_to_mass_ratio_after_application;
   //NYN   Valid_float32 v_NH3_N_content;
   CORN::Valid_float32 v_carbon_percent;
   CORN::Valid_float32 v_nitrogen_percent;
public: // constructor
   Biomass_decomposition_parameters(Organic_matter_source source);
public: // overrides
   virtual bool expect_structure(bool for_write = false);                        //161025
public: // accessors
   inline float32 get_fraction_of_biomass(Organic_matter_cycling cycling)  const
      { return composition_decomposition.fraction_of_biomass[cycling]; };
public: // computed parameters
   inline float32 get_carbon_nitrogen_ratio(Organic_matter_cycling cycling)const
      // Currently the carbon nitrogen ration is the same for al cyclings (CropSyst V.B. allows different cycling values).
       { return composition_decomposition.carbon_percent_DryWt / composition_decomposition.nitrogen_percent_DryWt; }
   float64 get_decomposition_constant(Organic_matter_cycling OM_cylcing)   const;      //060219
   void setup_default(Organic_matter_source source);
};
//_2008-08-29___________________________________________________________________
#endif
