#ifndef LADSS_CropSystH
#define LADSS_CropSystH
#include "cs_mod.h"
#include "LADSS.h"
//______________________________________________________________________________
class LADSS_CropSyst_Model
: public CropSyst_V4::CropSyst_Model                                             //151003
{  LADSS_LBF   LBF;
   LADSS_LBF_location LBF_location;
   LADSS_topography topography;
   const Directory_name *weather_directory;
 public:
   LADSS_CropSyst_Model
      (
      //160312 CORN::Date       &driving_date,                                            //150920
      const CropSyst::Arguments_V4 &arguments_                                  //151128
      //160312       ,modifiable_ Geocoordinate &geocoordinate_                                 //151128
      //160312 ,const CORN::OS::Directory_name     &_weather_directory                    //130827
      //151128       ,CropSyst::Land_unit_with_output_V4 &_land_unit_with_output                //141206
      //160312  ,CropSyst::Scenario &scenario_control_and_model_ops_                       //151128
      //151128 ,CropSyst_Model_options          &_active_model_options
      ,CropSyst::Desired_variables     &_desired_variables
      //151128 ,Report_formats_parameters       *_reports
      //160312 ,bool                             _batch_mode
      );
   virtual Location_parameters * load_location_parameters()                const;
   virtual void get_parameters_from_GIS_table
      (const char *GIS_override_table,nat32 LBF_ID,CropSyst_project &_project);
   virtual bool initalize()                                      initialization_;
};
//______________________________________________________________________________
extern LADSS_CropSyst_Model *LADSS_CropSyst_model;
//______________________________________________________________________________

#endif
