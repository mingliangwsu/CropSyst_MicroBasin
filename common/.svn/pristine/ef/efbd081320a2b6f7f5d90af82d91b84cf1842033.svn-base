#include <windows.h>
#include "txtrhydr.h"
#include "texture_hydraulics.h"
//______________________________________________________________________________
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//______________________________________________________________________________
#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{  return 1;
}
//______________________________________________________________________________
class Soil_properties
: public Soil_texture_hydraulics
{
public: // texture
   float32 sand;
   float32 clay;
   float32 silt;
public: // hydraulic properties
   float32 saturation;             // m3/m3 ?
   float32 vol_WC_at_1500;         // m3/m3
   float32 vol_WC_at_33;           // m3/m3
   float32 sat_hydraul_cond_m_d;   // m/day
   float32 bulk_density;           // grams/cm3
   float32 air_entry_pot;          // J/kg
   float32 soil_b;
public: //
   Soil_properties(float32 i_sand,float32 i_clay, float32 i_silt)
   : Soil_texture_hydraulics
      (sand,clay,silt
      ,saturation                  ,false
      ,vol_WC_at_1500              ,false
      ,vol_WC_at_33                ,false
      ,sat_hydraul_cond_m_d        ,false
      ,bulk_density                ,false
      ,soil_b                      ,false
      ,air_entry_pot               ,false)
   , sand(i_sand)
   , clay(i_clay)
   , silt(i_silt)
   , saturation(0.0)
   , vol_WC_at_1500(0.0)
   , vol_WC_at_33(0.0)
   , sat_hydraul_cond_m_d(0.0)
   , bulk_density(0.0)
   , air_entry_pot(0.0)
   , soil_b(0.0)
   {  recompute_every_thing();
   };
};
//______________________________________________________________________________
static Soil_properties *global_soil_properties = 0;
//______________________________________________________________________________
extern "C"  __export __stdcall
int set_soil_texture
(float sand
,float clay
,float silt)
{  if (global_soil_properties) delete global_soil_properties;
   global_soil_properties = new Soil_properties(sand,clay,silt);
   return 1;
};
// This function resets all calculations for the specified texture.
// All fixed properties are cleared and estimated values are calculated.
//______________________________________________________________________________
// The following functions are optional to set known fixed values for the soil.
// If fixed values are not set they will be estimated from texture
// and/or other fixed values.

// Only call these functions after calling setup_soil_texture_hydraulics()
// because setup_soil_texture_hydraulics recalculates all properties replacing any fixed values.
// Calling any one of these functions recomputes all properties
// that have not been fixed.
//______________________________________________________________________________
extern "C"  __export __stdcall
float fix_vol_WC_at_1500(float fixed_vol_WC_at_1500)
// m3/m3
{  global_soil_properties->set_vol_WC_at_1500(fixed_vol_WC_at_1500,true); return fixed_vol_WC_at_1500;};

extern "C"  __export __stdcall
float fix_vol_WC_at_33(float fixed_vol_WC_at_33)
// m3/m3
{  global_soil_properties->set_vol_WC_at_33(fixed_vol_WC_at_33,true); return fixed_vol_WC_at_33;};

extern "C"  __export __stdcall
float fix_bulk_density(float fixed_bulk_density)
// grams/cm3
{  global_soil_properties->set_bulk_density(fixed_bulk_density,true); return fixed_bulk_density;};

extern "C"  __export __stdcall
float fix_sat_hydraulic_cond_m_d(float fixed_sat_hydraulic_cond)
// m/day
{  global_soil_properties->set_sat_hydraul_cond_m_d(fixed_sat_hydraulic_cond,true); return fixed_sat_hydraulic_cond;};

extern "C"  __export __stdcall
float fix_air_entry_pot(float fixed_air_entry_pot)
// J/kg
{  global_soil_properties->set_air_entry_pot(fixed_air_entry_pot,true); return fixed_air_entry_pot;};
// The following functions return the current estimated, calculated or fixed values.

extern "C"  __export __stdcall
float get_saturation()
// m3/m3
{  return  global_soil_properties->get_saturation(); };

extern "C"  __export __stdcall
float get_vol_WC_at_1500()
// m3/m3  (permanent wilting point)
{  return  global_soil_properties->get_vol_WC_at_1500(false); };

extern "C"  __export __stdcall
float get_vol_WC_at_33()
// m3/m3  (Field capacity)
{  return  global_soil_properties->get_vol_WC_at_33(false); };

extern "C"  __export __stdcall
float get_bulk_density()
// grams/cm3
{  return  global_soil_properties->get_bulk_density(); };

extern "C"  __export __stdcall
float get_sat_hydraulic_cond_m_d()
// m/day
{  return  global_soil_properties->get_sat_hydraul_cond_m_d(); };

extern "C"  __export __stdcall
float get_sat_hydraul_cond_cm_hr()
// cm/hr   same as get_sat_hydraulic_cond_m_d but converted to cm/hr
{  return  global_soil_properties->get_sat_hydraul_cond_cm_hr(); };

extern "C"  __export __stdcall
float get_air_entry_pot()
// J/kg
{  return  global_soil_properties->get_air_entry_pot(); };

extern "C"  __export __stdcall
float get_b()
// unitless
{  return  global_soil_properties->get_soil_b(); };

extern "C"  __export __stdcall
float get_geometric_mean_particle_size()
{  return  global_soil_properties->get_geometric_mean_particle_size(); };
//______________________________________________________________________________
