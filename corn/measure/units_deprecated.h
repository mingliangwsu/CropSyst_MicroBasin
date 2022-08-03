
// I decided to go with  UC_xxx_per_xxx
#define UC_m2_kg                          U_a_per_b(UC_square_meter_area,UC_kg_mass)
#define UC_km_kg                          U_a_per_b(UC_km,UC_kg_mass)
#define UC_MJ_m2                         U_a_per_b(UC_mega_joule_energy,UC_square_meter_area)
#define UC_J_m2                          U_a_per_b(UC_joule_energy,UC_square_meter_area)
#define UC_kg_MJ                         U_a_per_b(UC_kg_mass,UC_mega_joule_energy)
#define UC_g_MJ                          U_a_per_b(UC_gram_mass,UC_mega_joule_energy)
#define UC_kJ_mole                       U_a_per_b(UC_kilo_joule_energy,UC_mole)
#define UC_watt_day_m2                   U_a_per_b(UC_watt_day,UC_square_meter_area)

#define UC_kg_kg                         U_a_per_b(UC_kg_mass,UC_kg_mass)
#define UC_kg_ha                         U_a_per_b(UC_kg_mass,UC_hectare)
#define UC_kg_m2                         U_a_per_b(UC_kg_mass,UC_square_meter_area)
#define UC_kg_m3                         U_a_per_b(UC_kg_mass,UC_cubic_meter_volume)
#define UC_tn_ha                         U_a_per_b(UC_tonne_mass,UC_hectare)
#define UC_ml_g                          U_a_per_b(UC_ml,UC_g)
#define UC_m3_m3                         U_a_per_b(UC_cubic_meter_volume,UC_cubic_meter_volume)
#define UC_cm3_cm3                       U_a_per_b(UC_cubic_cm_volume,UC_cubic_cm_volume)
#define UC_g_cm3                       U_a_per_b(UC_gram_mass,UC_cubic_cm_volume)
#define UC_cmole_kg                       U_a_per_b(UC_cmole,UC_kg_mass)
#define UC_mmole_kg                       U_a_per_b(UC_mmole,UC_kg_mass)

#define UC_m2_m2                         U_a_per_b(UC_square_meter_area,UC_square_meter_area)
#define UC_kg_solid_kg_liquid            U_a_per_b(UC_kg_mass,UC_kg_mass)
#define UC_kg_kg                         U_a_per_b(UC_kg_mass,UC_kg_mass)

#define UC_g_kg                         U_a_per_b(UC_g_mass,UC_kg_mass)
#define UC_mg_kg                         U_a_per_b(UC_mg_mass,UC_kg_mass)
#define UC_J_kg                          U_a_per_b(UC_joule_energy, UC_kg_mass)

#define UC_mEq_100g                       U_a_per_b(UC_mEq, UC_hg_mass)

#define UC_dS_m                         U_a_per_b(UC_decisiemens,UC_meter)
#define UC_luminance_c_m2                (uint16)U_a_per_b(UC_candela,UC_square_cm_area)

#define UC_watt_m2_flux_density           U_a_per_b(UC_watt_radiant_flux,UC_square_m_area)
#define UC_W_steradian_radiant_intensity U_a_per_b(UC_watt_power,UC_steradian)


/* 060926
Don't delete until CropSyst V3 is retired
// These units are obsolete/deprecated
// Units with _D suffix are depricated use the new units

//040715 depricated
// Area measure in square (This could probably be a composite of meter length / breadth /depth etc.).
#define UM_surface_area_D             (uint8) 0x29   // 00101001 00000000
#define UC_square_meter_surface_area_D   (uint16)0x2900
// Curved or convoluted surfaces (I.e. spheres, rough terrain)
#define UC_square_cm_surface_area_D      (uint16)0x2942

//040715 depricated
// I.e. meters 3
#define UM_cubic_solid_volume_D         (uint8) 0x31   // 00101111 00000000
#define UC_cubic_meter_solid_volume_D      (uint16)0x3100

#define UM_cubic_liquid_volume_D        (uint8) 0x32   // 00101110 00000000
#define UC_cubic_meter_liquid_volume_D     (uint16)0x3200

#define UM_cubic_gas_volume_D           (uint8) 0x33   // 00101101 00000000
#define UC_cubic_meter_gas_volume_D        (uint16)0x3300

#define UM_quality_of_heat_D                     (uint8) 0x4A
#define UC_joule_quality_of_heat_D                  (uint16)0x4A00
#define UC_kilo_joule_quality_of_heat_D           (uint16)0x4A03
#define UC_mega_joule_quality_of_heat_D           (uint16)0x4A06

#define UM_work_D                     (uint8) 0x4B
#define UC_joule_work_D                  (uint16)0x4B00
#define UC_kilo_joule_work_D             (uint16)0x4B03
#define UC_mega_joule_work_D             (uint16)0x4B06

#define UC_cm_per_second_D                 U_a_per_b(UC_cm_length_D,UT_second)

// 040715 the following are depricated, use the ones above
#define UC_meters_per_second_D           U_a_per_b(UC_meter_distance_D,UT_second)
#define UC_meters_per_day_D              U_a_per_b(UC_meter_distance_D,UT_day)
#define UC_mm_depth_per_day_D            U_a_per_b(UC_mm_depth_D,UT_day)
#define UC_kilometers_per_day_D          U_a_per_b(UC_km_distance_D,UT_day)
#define UC_kilometers_per_hour_D         U_a_per_b(UC_km_distance_D,UT_hour)

#define UC_m2_kg_surface_area_D          U_a_per_b(UC_square_meter_surface_area,UC_kg_mass)

#define UC_MJ_m2_D                       U_a_per_b(UC_mega_joule_energy,UC_square_meter_surface_area_D)
#define UC_MJ_m2_solar_radiation_D       UC_MJ_m2_D
#define UC_watt_day_m2_D                 U_a_per_b(UC_watt_day,UC_square_meter_surface_area_D)
#define UE_Langley_D                     U_a_per_b(UE_calorie_energy,UC_square_cm_surface_area)

#define UC_kg_m3_D                       U_a_per_b(UC_kg_mass,UC_cubic_meter_solid_volume_D)
#define UC_J_kg_liquid_D                 U_a_per_b(UC_joule_energy, UC_kg_liquid)
#define UC_m3_liquid_m3_solid_D          U_a_per_b(UC_cubic_meter_liquid_volume_D,UC_cubic_meter_solid_volume_D)


//040715 depricated we now just have linear
// Distance from point to point or center to center
#define UM_distance_D                 (uint8) 0x21   // 00100001 00000000
#define UC_distance_D                    (uint16)0x2100
#define UC_meter_distance_D              (uint16)0x2100
#define UC_km_distance_D                 (uint16)0x2103
#define UC_cm_distance_D                 (uint16)0x2142


// 040715 depricated we now just have linear
// Breadth through the center (widest) point or width at a given interval along the length
#define UM_breadth_D                  (uint8) 0x23   // 00100011 00000000
#define UC_meter_breadth_D               (uint16)0x2300
#define UC_m_breadth_D                   (uint16)0x2300
#define UC_dm_breadth_D                  (uint16)0x2341
#define UC_cm_breadth_D                  (uint16)0x2342
#define UC_mm_breadth_D                  (uint16)0x2343

//040715 depricated we now just have linear
#define UC_meter_diameter_D              (uint16)0x2300 // alias
#define UC_m_diameter_D                  (uint16)0x2300 // alias
#define UC_dm_diameter_D                 (uint16)0x2341 // alias
#define UC_cm_diameter_D                 (uint16)0x2342 // alias
#define UC_mm_diameter_D                 (uint16)0x2343 // alias

//040715 depricated we now just have linear
// Positive upward perpendicular to the horintal place of reference or surface
#define UM_height_D                   (uint8) 0x24   // 00100100 00000000
#define UC_meter_height_D                (uint16)0x2400
#define UC_m_height_D                    (uint16)0x2400
#define UC_dm_height_D                   (uint16)0x2441
#define UC_cm_height_D                   (uint16)0x2442
#define UC_mm_height_D                   (uint16)0x2443


//040715 depricated we now just have linear
// Positive downward perpendicular to the horizontal plane of reference or surface
#define UM_depth_D                     (uint8) 0x25   // 00100101 00000000
#define UC_meter_depth_D                 (uint16)0x2500
#define UC_m_depth_D                     (uint16)0x2500 // synonym
#define UC_dm_depth_D                    (uint16)0x2541 // 00100101 01000001
#define UC_cm_depth_D                    (uint16)0x2542 // 00100101 01000010
#define UC_mm_depth_D                    (uint16)0x2543 // 00100101 01000011

#define UC_depth_D                       (uint16)0x2500
#define UE_inch_depth_D                  CU(UC_depth) | SUE_inch
#define UE_nail_depth_D                  CU(UC_depth) | SUE_nail
#define UE_hand_depth_D                  CU(UC_depth) | SUE_hand
#define UE_link_depth_D                  CU(UC_depth) | SUE_link
#define UE_foot_depth_D                  CU(UC_depth) | SUE_foot
#define UE_yard_depth_D                  CU(UC_depth) | SUE_yard
#define UE_rod_depth_D                   CU(UC_depth) | SUE_rod
#define UE_pole_depth_D                  CU(UC_depth) | SUE_pole
#define UE_perch_depth_D                 CU(UC_depth) | SUE_perch
#define UE_lugg_depth_D                  CU(UC_depth) | SUE_lugg
#define UE_fathom_depth_D                CU(UC_depth) | SUE_fathom
#define UE_chain_depth_D                 CU(UC_depth) | SUE_chain
#define UE_furlong_depth_D               CU(UC_depth) | SUE_furlong
#define UE_statute_mile_depth_D          CU(UC_depth) | SUE_statute_mile
#define UE_nautical_mile_modern_depth_D  CU(UC_depth) | SUE_nautical_mile_modern
#define UE_nautical_mile_depth_D         CU(UC_depth) | SUE_nautical_mile

//050613  instead of UE_xxxx_length use the new UE_xxxx_linear
#define UE_inch_length                   CU(UC_length) | SUE_inch
#define UE_nail_length                   CU(UC_length) | SUE_nail
#define UE_hand_length                   CU(UC_length) | SUE_hand
#define UE_link_length                   CU(UC_length) | SUE_link
#define UE_foot_length                   CU(UC_length) | SUE_foot
#define UE_yard_length                   CU(UC_length) | SUE_yard
#define UE_rod_length                    CU(UC_length) | SUE_rod
#define UE_pole_length                   CU(UC_length) | SUE_pole
#define UE_perch_length                  CU(UC_length) | SUE_perch
#define UE_lugg_length                   CU(UC_length) | SUE_lugg
#define UE_fathom_length                 CU(UC_length) | SUE_fathom
#define UE_chain_length                  CU(UC_length) | SUE_chain
#define UE_furlong_length                CU(UC_length) | SUE_furlong
#define UE_statute_mile_length           CU(UC_length) | SUE_statute_mile
#define UE_nautical_mile_modern_length   CU(UC_length) | SUE_nautical_mile_modern
#define UE_nautical_mile_length          CU(UC_length) | SUE_nautical_mile


// Areal measure from reference surface up
#define UM_altitude_D                 (uint8) 0x26   // 00100110 00000000
#define UC_meter_altitude_D              (uint16)0x2600
// NYI                                          (uint8) 0x27   // 00100111 00000000


#define UC_newton_force_D                  (uint16)0x5000
#define UM_stress_D                   (uint8) 0x5C
#define UC_pascal_stress_D               (uint16)0x5C00

*/


