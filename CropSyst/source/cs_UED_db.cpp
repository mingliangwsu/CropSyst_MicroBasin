#  include "cs_UED_db.h"
#  include "csvc.h"
#  include "cs_vars.h"
#  include "cs_glob.h"
#  include "UED/library/varrec.h"
#  include "corn/measure/measures.h"
#include "options.h"
//______________________________________________________________________________
CropSyst_UED_database::CropSyst_UED_database
(const char             *ued_filename_
,std::ios_base::openmode openmode_                                               //140422
,const CORN::Date_const &date_)
:UED::Database_file_indexed(ued_filename_,openmode_,false)
,current_record_time_stamp(CORN::Date_clad_32 (date_.get_year(),(CORN::DOY)1).get_datetime64())
{}
//_2002-06-19_2000______________________________________________________________
CropSyst_UED_database::~CropSyst_UED_database()
{  // We write the variable definitions at the end because
   // some variable ranges are not determined until all crops have been encountered.
   set_CS_output_variable_max_warning_range(CSVC_crop_base_root_biomass_current ,over_m2_to_ha*CS_UED_max_root_biomass_encountered); //070207
   set_CS_output_variable_max_warning_range(CSVC_crop_biomass_canopy  ,over_m2_to_ha*CS_UED_max_canopy_biomass_encountered);   //070207
   write_units_variables_definitions();
}
//_2006-06-08___________________________________________________________________
void CropSyst_UED_database::initialize_with_descriptions
(const std::string &simulation_description
,const std::string &location_description
,const std::string &soil_description
, bool // unused fast_graph
)
{  // Creating variable definitions for all variables used for cropsyst
   // Currently all variables are added, but only ones selected for output really need to be added.
   UED::Database_file_indexed::initialize();
   write_generating_application((CROPSYST_major_version<<8) | CROPSYST_minor_version, "CropSyst"); //971208
   write_database_description(simulation_description.c_str());                   //971208
   write_database_description(location_description.c_str());                     //971208
   write_database_description(soil_description.c_str());                         //971208
}
//_2003-01-07___________________________________________________________________
void CropSyst_UED_database::write_units_variables_definitions()
{  for (int i = 0; CS_output_variables[i].code; i++)
   {  // We now just output all known CropSyst variable definitions
      include_var_code_def                                                       //030716
         (  UED::Variable_format_0                                               //030716
            (CS_output_variables[i].code
            ,CS_output_variables[i].preferred_units_code                         //050631
            ,CS_output_variables[i].min_warning
            ,CS_output_variables[i].max_warning
            ,std::numeric_limits<float32>::min(),std::numeric_limits<float32>::max()
            ,(CS_output_variables[i].description)                                //020330
            ,(CS_output_variables[i].abbreviation)) );                           //020909
   }
   write_end_definitions_marker();                                               //971207
}
//_20000-06-08__________________________________________________________________

