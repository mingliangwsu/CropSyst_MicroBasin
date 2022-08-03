#ifndef csprofssH
#define csprofssH
/*
  This unit is Marcello's soil profile spreadsheet.

 Header:

 Simulation description (1,0)
 Soil description  (1,0)
 Transformation layers  (2,0)

 For each sublayer:

 layer sublayer Thick PWP FC BD

 Record for each day.

           root                               For transformation layers
  year doy depth Watercontents  Temperatures  NO3 NH4 Nit Denit OM

I.e.

Simulation description
Soil description
Layer Sublayer Thick PWP FC BD
   1      1      .1   .1  .3 1.3
   1      2      .1   .15 .3 1.2
   2      3      .8   .12 .2 1.1

         root  Water cont. Temperature NO3     NH4     Nitrif  Denitr  Org Mat
year doy depth 1   2   3   1   2   3   1   2   1   2   1   2   1  2    1  2
1994 183  9.9  9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9 9.9
*/

#include "corn/format/spreadsheet/biff.h"

#include "cs_glob.h"
#include "soil.h"
#ifdef USE_OS_FS
#  include "corn/OS/directory_entry_name.h"
#endif

class Organic_matter_residues_profile_abstract;
namespace CropSyst {
class Crop_interfaced; // forward decl
}
//______________________________________________________________________________
class Soil_spreadsheet
: public Biff_file
{protected:
   int16 P_ROW;
   int16 P_COL;
   int16 freeze_pane_row;                                                        //010223
 protected:
   const CropSyst::Soil  &soil;                                                  //161008
 public:
   Soil_spreadsheet
      (const CORN::OS::File_name &filename                                       //130506
      ,const CropSyst::Soil      &soil                                           //161008
      ,const char                *sim_description
      ,const char                *spreadsheet_description);
};
//_1998-10-16___________________________________________________________________
class Soil_horizon_spreadsheet
: public Soil_spreadsheet
{public:
   Soil_horizon_spreadsheet
      (const CORN::OS::File_name &filename
      ,const CropSyst::Soil      &soil                                           //161008
      ,const char                *sim_description);
   virtual ~Soil_horizon_spreadsheet();
};
//_1998-10-16___________________________________________________________________
class Soil_profile_spreadsheet
: public Soil_spreadsheet
{public:
   Soil_profile_spreadsheet
      (const CORN::OS::File_name &filename
      ,const CropSyst::Soil      &soil                                           //161008
      ,const char                *sim_description
      ,const char                *profile_description
      ,const char                *profile_units);
   virtual ~Soil_profile_spreadsheet();
   void write_day
      (const CORN::Date_const &date
      , float64 root_depth
      , soil_sublayer_array_64(profile));
};
//_1998-10-16___________________________________________________________________
class Soil_profile_spreadsheet_set
{protected:
   const CropSyst::Soil     &soil;                                               //161008
   Soil_horizon_spreadsheet *soil_horizon_SS;
   Soil_profile_spreadsheet *water_depth_SS;                                     //051128
   Soil_profile_spreadsheet *cum_water_depth_SS;                                 //051128
   Soil_profile_spreadsheet *water_content_SS;                                   //000911
   Soil_profile_spreadsheet *water_potential_SS;                                 //000911
   Soil_profile_spreadsheet *root_fraction_SS;                                   //010316
   Soil_profile_spreadsheet *root_biomass_SS;                                    //071214
   #ifdef NITROGEN
   bool  nitrogen_sim;
   Soil_profile_spreadsheet *nitrate_SS;
   Soil_profile_spreadsheet *ammonium_SS;
   Soil_profile_spreadsheet *NH4_mineralization_SS;
   Soil_profile_spreadsheet *nitrification_SS;
   Soil_profile_spreadsheet *denitrification_SS;
   Soil_profile_spreadsheet *percent_organic_matter_SS;
   #endif
   #ifdef RESIDUES
   Soil_profile_spreadsheet *plant_residue_biomass_SS;
   Soil_profile_spreadsheet *manure_residue_biomass_SS;
   #endif
   #ifdef SOIL_TEMPERATURE
   Soil_profile_spreadsheet *temperature_SS;
   #endif
   #ifdef SALINITY
   bool  salinity_sim;
   Soil_profile_spreadsheet *salinity_SS;
   Soil_profile_spreadsheet *salt_SS;
   #endif
 public:
   Soil_profile_spreadsheet_set
      (const CORN::OS::Directory_name &output_soil_dir                           //030225
      ,const CropSyst::Soil      &soil_                                          //161008
      ,const char                *sim_description
      #ifdef NITROGEN
      ,bool                      nitrogen_sim_
      #endif
      #ifdef SALINITY
      ,bool                      salinity_sim_
      #endif
      ,bool SS_hydraulic_properties
      ,bool SS_water_content
      ,bool SS_water_potential
      ,bool SS_root_fraction
      ,bool SS_root_biomass
      #ifdef NITROGEN
      ,bool SS_ammonium
      ,bool SS_nitrate
      ,bool SS_denitrification
      ,bool SS_nitrification
      ,bool SS_NH4_mineralization
      ,bool SS_organic_matter
      #endif
      #ifdef RESIDUES
      ,bool SS_plant_residue
      ,bool SS_manure_residue
      #endif
      #ifdef SOIL_TEMPERATURE
      ,bool SS_temperature
      #endif
      #ifdef SALINITY
      ,bool SS_salinity
      ,bool SS_salt
      #endif
   );
   void write_day
      (const CORN::Date_const            &today
      ,float64                            root_depth
      ,const CropSyst::Crop_interfaced   *crop                                   //050209 //131008NS
      ,Organic_matter_residues_profile_abstract *organic_matter_residue);        //050726
   ~Soil_profile_spreadsheet_set();
};
//______________________________________________________________________________
#endif
//csprofss.h

