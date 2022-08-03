#ifndef CSVC_SPECIALH
#define CSVC_SPECIALH

// CropSyst variable codes


//160521 special output
// These CSVC variable codes are temporary until I added them to CSVC creation
#define CSVC_crop_degree_hours_above_30_flowering_fortnight 0xFFFFF01
#define CSVC_crop_degree_hours_above_34_flowering_fortnight 0xFFFFF02
#define CSVC_Srad_seasonal 0xFFFFF03
#define CSVC_Tmax_seasonal 0xFFFFF04
#define CSVC_Tmin_seasonal 0xFFFFF05
#define CSVC_Tavg_seasonal 0xFFFFF06
#define CSVC_crop_WUE_seasonal  0xFFFFF07
#define CSVC_crop_days_to_flowering 0xFFFFF08
#define CSVC_crop_duration       0xFFFFF09

#define CSVC_PAW_15_init_seasonal   0xFFFFF0A
#define CSVC_PAW_15_final_seasonal  0xFFFFF0B
#define CSVC_canopy_cover_max          0xFFFFF0C
#define CSVC_canopy_cover_green        0xFFFFF0D
#define CSVC_canopy_cover_green_final  0xFFFFF0E

//daily
#define CSVC_crop_WUE                     0xFFFFF10
#define CSVC_crop_degree_hours_above_30   0xFFFFF11
#define CSVC_crop_degree_hours_above_34   0xFFFFF12

#endif
