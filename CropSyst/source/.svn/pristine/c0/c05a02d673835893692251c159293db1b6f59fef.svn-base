#ifndef cs_UED_harvestH
#define cs_UED_harvestH
#include "corn/data_source/datarec.h"
#include "UED/library/UED_tuple_datasrc.h"
namespace CropSyst {
class Crop_interfaced;
}
//______________________________________________________________________________
class Harvest_data_record : public CORN::Data_record
{
   CORN::Date_clad_32 planting_date;
   CORN::Date_clad_32 emergence_date;
   CORN::Date_clad_32 maturity_date;
   float32 yield;
   float32  used_biomass;
   float32  grazed_biomass;
   float32  residue_biomass;
   float32  stubble_biomass;
   float32  disposed_biomass;
   float32  uncut_biomass;  // after clipping                                    //070207
   float32  above_ground_biomass; // before clipping
# define harvest_section  "harvest"
 public: // constructor
   inline Harvest_data_record()
      : CORN::Data_record(harvest_section)
      {}
   void update(const CropSyst::Crop_interfaced &crop);                           //131008
   virtual bool expect_structure(bool for_write);                                //161025
};
//______________________________________________________________________________
class Harvest_data_source : public UED::Tuple_data_source
, public Harvest_data_record
{
 public: // Constructor
   Harvest_data_source(UED::Database_file_indexed *i_database );
   void record(datetime64 date_time);
 private:
   inline bool check_abstract() { return new Harvest_data_source(0); }
};
//_2007?________________________________________________________________________
#endif

