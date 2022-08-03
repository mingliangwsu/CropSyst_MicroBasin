#ifndef texture_hydraulicsH
#define texture_hydraulicsH

extern "C"  __export __stdcall
int set_soil_texture
(float sand
,float clay
,float silt
);
// This function resets all calculations for the specified texture.
// All fixed properties are cleared and estimated values are calculated.
// Texture values are in percent  0 to 100.

// The following functions are optional to set known fixed values for the soil.
// If fixed values are not set they will be estimated from texture
// and/or other fixed values.

// Only call these functions after calling setup_soil_texture_hydraulics()
// because setup_soil_texture_hydraulics recalculates all properties replacing any fixed values.
// Calling any one of these functions recomputes all properties
// that have not been fixed.

extern "C"  __export __stdcall
float fix_vol_WC_at_1500(float fixed_vol_WC_at_1500);
// m3/m3   water content at permanent wilt point (matric potential -1500 kPa)
#define fix_permanent_wilt_point() fix_vol_WC_at_1500()

extern "C"  __export __stdcall
float fix_vol_WC_at_33(float fixed_vol_WC_at_33);
// m3/m3   water content at field capacity  (matric potential -33 kPa)
#define fix_field_capacity() fix_vol_WC_at_33()

extern "C"  __export __stdcall
float fix_bulk_density(float fixed_bulk_density);
// grams/cm3  bulk density

extern "C"  __export __stdcall
float fix_sat_hydraulic_cond_m_d(float fixed_sat_hydraulic_cond);
// m/day  saturated hydraulic conductivity

extern "C"  __export __stdcall
float fix_air_entry_pot(float fixed_air_entry_pot);
// J/kg  air entry potential

// The following functions return the current estimated, calculated or fixed values.
extern "C"  __export __stdcall
float get_saturation();
// m3/m3

extern "C"  __export __stdcall
float get_vol_WC_at_1500();
// m3/m3  water content at permanent wilt point (matric potential -1500 kPa)

#define get_permanent_wilt_point() get_vol_WC_at_1500()

extern "C"  __export __stdcall
float get_WC_at_33();
// m3/m3  water content at field capacity  (matric potential -33 kPa)
#define get_field_capacity_volumetric() get_WC_at_33()

extern "C"  __export __stdcall
float get_bulk_density();
// grams/cm3  bulk density

extern "C"  __export __stdcall
float get_sat_hydraulic_cond_m_d();
// m/day  saturated hydraulic conductivity

extern "C"  __export __stdcall
float get_sat_hydraul_cond_cm_hr();
// cm/hr   same as get_sat_hydraulic_cond_m_d but converted to cm/hr

extern "C"  __export __stdcall
float get_air_entry_pot();
// J/kg   air entry potential

extern "C"  __export __stdcall
float get_b();
// unitless  Campbell b coefficient

extern "C"  __export __stdcall
float get_geometric_mean_particle_size();
// micrometers ?

#endif
