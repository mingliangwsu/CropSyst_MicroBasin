#ifndef CROP_CONTAINED_CROPSYST_H
#define CROP_CONTAINED_CROPSYST_H

#error obsolete

/*_______*/ class Crop_CropSyst_contained
/*_______*/ {
/*_______*/    class Weather_contained
/*_______*/    : public Weather_for_crop_abstract
/*_______*/    { };

/*_______*/    Weather_contained          *weather;
/*_______*/    Crop_interfaced_CropSyst   *crop;

/*_______*/ public:
/*_______*/    Crop_CropSyst_contained
/*_______*/    (            const char *crop_parameter_file_name
/*050331_*/    ,Transpiration_model     transpiration_model  = ORIGINAL_TRANSPIRATION_MODEL

//NYI/*050722_*/    ,Crop_nitrogen_model     _nitrogen_model = CROP_NITROGEN_DISABLED
//NYI/*NITRO  */        ,ET_abstract            *_ET =0   // Optional. Although ET is optional, if it is not specified, there will be no correction for transpiration

//050801/*_______*/    ,bool i_fallow          = false
//NYI/*SALT     */      ,bool i_run_salinity    = false
//NYI/*CO2      */      ,bool simulate_CO2      = false
//NYI/*CO2      */      ,float64 current_CO2_conc = 350.0
//NYI/*CROPROWS */      ,Crop_row     *i_crop_row = 0
/*_______*/    );

/*_______*/    virtual ~Crop_CropSyst_contained();

/*_______*/ };

#endif
