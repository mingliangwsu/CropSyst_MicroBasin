#include "crop_param_NET.h"
#include "crop/crop_param_V5.h"
#include "corn/data_source/VV_File.h"
using namespace System::Runtime::InteropServices; 
#define const_
//______________________________________________________________________________
//______________________________________________________________________________
namespace CropSyst_parameters_NET
{
//______________________________________________________________________________
Crop::Crop(System::String ^crop_file_name)
: crop(0)
{  crop = new CropSyst::Crop_parameters;
   std::string filename_std_string;
   const char *crop_filename_cstr = 0;
   #if (_MSC_VER > 1600)
   // The following is for VC2010
   filename_std_string = marshal_as<std::string>(crop_file_name);
   crop_filename_cstr->filename_std_string;
   #else
   crop_filename_cstr = (const char*) (Marshal::StringToHGlobalAnsi(crop_file_name)).ToPointer();
   #endif
   CORN::VV_File crop_file(crop_filename_cstr);
   crop_file.get(*crop);
};
//_2011-04-29_______________________________________________________constructor_/
Crop::~Crop()
{	if (crop) delete crop; crop = 0;
};
//_2001-05-04________________________________________________________destructor_/
const CropSyst::Crop_parameters_struct::Thermal_time               &Crop::ref_thermal_time()             const_ { return crop->ref_thermal_time(); };
const CropSyst::Crop_parameters_struct::Inactive_period            &Crop::ref_inactive_period()          const_ { return crop->ref_inactive_period(); };
const CropSyst::Crop_parameters_struct::Phenology                  &Crop::ref_phenology()                const_ { return crop->ref_phenology(); };
const CropSyst::Crop_parameters_struct::Transpiration              &Crop::ref_transpiration()            const_ { return crop->ref_transpiration(); };
const CropSyst::Crop_parameters_struct::Biomass_production         &Crop::ref_biomass_production()       const_ { return crop->ref_biomass_production(); };
const CropSyst::Crop_parameters_struct::Morphology                 &Crop::ref_morphology()               const_ { return crop->ref_morphology(); };
const CropSyst::Crop_parameters_struct::Canopy_growth_LAI_based    &Crop::ref_canopy_growth_LAI_based()  const_ { return crop->ref_canopy_growth_LAI_based(); };
const CropSyst::Crop_parameters_struct::Canopy_growth_cover_based  &Crop::ref_canopy_growth_cover_based()const_ { return crop->ref_canopy_growth_cover_based(); };
const CropSyst::Crop_parameters_struct::Root                       &Crop::ref_root()                     const_ { return crop->ref_root(); };
const CropSyst::Crop_parameters_struct::Fruit                      &Crop::ref_fruit()                    const_ { return crop->ref_fruit(); };
#ifdef CROPSYST
//NYI   const CropSyst::Crop_parameters_struct::Photoperiod        &Crop::ref_photoperiod()              const_ { return crop->ref_photoperiod(); };
const CropSyst::Crop_parameters_struct::Hardiness                  *Crop::ref_hardiness()                const_ { return crop->ref_hardiness(); };
const CropSyst::Crop_parameters_struct::Vernalization              *Crop::ref_vernalization()            const_ { return crop->ref_vernalization(); };
const CropSyst::Crop_parameters_struct::Nitrogen                   &Crop::ref_nitrogen()                 const_ { return crop->ref_nitrogen(); };
const CropSyst::Crop_parameters_struct::Emergence_hydro_thermal    &Crop::ref_emergence()                const_ { return crop->ref_emergence(); };
const CropSyst::Crop_parameters_struct::Emergence_hydro_thermal    &Crop::ref_emergence_class()          const_ { return crop->ref_emergence_class(); };
#endif

//_2011-04-29__________________________________________________ref_thermal_time_/
}; //namespace