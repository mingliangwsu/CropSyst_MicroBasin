#ifndef CS_varsH
#define CS_varsH

#include "cs_varderiv.h"
#include "UED/library/varcodes.h"
#include "corn/measure/units.h"
#include <string>
#define Phrase_ID char *

/*
   CropSyst UED units codes store


   CropSyst nonstandard variable codes are composed as follows:
   Qualifier code is the same as UED
   physical property code is replaced with enumeration unique to cropsyst

   The last byte will be 0 unless for sublayer

   These codings should be eventually replaced with UED codes as the
   are defined in the UED standard.

   33322222 22222111 1111111
   21098765 43210987 65432109 87654321
   1qqqqqqq c                 llllllll

   Bit 32 will always be 1 (non standard)
   q  are the qualifier byte
   l  are layering bits which will be 0 when not refering to a layer

   bit 24 set to 1 denotes a chemical,
     in this case, 23 denote the following
      0 denotes one of the pesticies (indexed by the pesticide database)
          (See pesticide.txt)
         In this case bits 9-16 denote the chemical enumeration.
         and bits 17-22 are an enumeration defined by DLY_CHEM_IDS
      1 Denotes one of the following variables N NO3 NH4 NO2 Salinity Pot Min. N

   bit 24 set to 0 denotes a CropSyst object class member variable
     in this case
         bits 17 to 23 denote the object class
         1111111
         3210987
*/
//______________________________________________________________________________
#define CS_UED_variable_code UED_variable_code

extern nat32 sel_vars_weather_file      ;    // CSVC_weather_file
extern nat32 sel_vars_weather_VPD       ;     // CSVC_VPD_weather
extern nat32 sel_vars_weather_ET        ;      //

//070726 check obsolete extern nat32 sel_vars_soil_base         ;
extern nat32 sel_vars_soil_chemical     ;
extern nat32 sel_vars_soil_N            ;
extern nat32 sel_vars_soil_freezing     ;
extern nat32 sel_vars_soil_erosion      ;
extern nat32 sel_vars_soil_runoff       ;
extern nat32 sel_vars_soil_complete     ;

extern nat32 sel_vars_crop_base         ;
extern nat32 sel_vars_crop_nitrogen     ;
extern nat32 sel_vars_crop_complete     ;

extern nat32 sel_vars_residue           ;
extern nat32 sel_vars_residue_straw     ;
extern nat32 sel_vars_residue_manure    ;

extern nat32 sel_vars_water_table         ;

extern nat32 sel_vars_management        ;
extern nat32 sel_vars_management_irrigation;
//extern nat32 sel_vars_management_biomass_grazed;
extern nat32 sel_vars_management_N  ;
extern nat32 sel_vars_management_NH4       ;
extern nat32 sel_vars_management_NO3       ;

extern nat32 sel_vars_computed_for_output  ;

#define CS_output_units_count 14
//______________________________________________________________________________
struct CS_output_variable_layout
{
   CS_UED_variable_code  code;
   UED_units_code    preferred_units_code;  // These are the units preferred for viewing  //990516
   float min_warning;   // Defines a valid range of values before an warning is issued in an editor
   float max_warning;   // In graphics displays, this will also define the range of the graph.
   const Phrase_ID description;
   const char *abbreviation;                                                     //020909
   // The Following are for variable selection and graph options.
   nat32 color_ramp_low_RGB;                                                     //990405
   nat32 color_ramp_med_RGB;                                                     //990405
   nat32 color_ramp_high_RGB;                                                    //990405
};
#define NO_ABBRV_NO_COLOR "",0,0,0
//______________________________________________________________________________
class CropSyst_Variable_code_clad
: public UED::Variable_code_clad
{
public:
   CropSyst_Variable_code_clad(UED_variable_code i_code)
   :UED::Variable_code_clad(i_code)
   {}
   inline nat8  get_class() const   /* get the CSC */
   {  nat32 prop = get_physical_property();
      return (nat8 )((prop & 0xFF0000) >> 16);
   }
   inline nat8  get_class_group() const // actually only 4 significant bits
   {  return (nat8 )((get_class() & (nat8 )0xF0) >> 4);
   }
   inline nat8  get_class_distinction() const // actually only 4 significant bits
   { return (get_class() & (nat8 )0x0F); };
   inline uint16 get_class_variable() const    // actually only 8 bit for layered variables, 16bits for others
   {  nat32 prop = get_physical_property();
      return (uint16)(is_layered_V1()
       ? ((prop & (nat32)0x00FF00) >> 8)
       : (prop & (nat32)0x00FFFF)); // in UED V2 the physical property is always in the low word
   } // get_layer is the same as UED layer
   nat32 get_class_color() const;
   // This is the background pastel color used when showing groups of cropsyst variables
   // (I.e. in selection listboxes.)
   std::string &get_class_description(std::string &buffer);
   const char *get_abbreviation() const;
};
//______________________________________________________________________________
extern CS_output_variable_layout CS_output_variables[];
extern void set_CS_output_variable_max_warning_range(CS_UED_variable_code code,float highest_value);

extern float64 CS_UED_max_root_biomass_encountered     ;
extern float64 CS_UED_max_canopy_biomass_encountered   ;

#endif
//cs_vars.h

