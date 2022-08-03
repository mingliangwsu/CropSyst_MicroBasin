#ifndef GIS_tableH
#define GIS_tableH

#include "corn/data_source/datarec.h"
#include "project/GIS/pat.h"
#include "common/soil/layering.h"

// for the  Polygon_simulation_parameters

#define        equiv_polygon_ran          -1
#define        equiv_polygon_not_present  -2
#define        polygon_not_runable        -3

#  define LABEL_init_PAW "init_PAW"
#  define LABEL_init_NO3 "init_NO3"
#  define LABEL_aspect  "aspect"

namespace CropSyst {                                                             //130621
class Scenario;
//______________________________________________________________________________
class Simulation_override_record
: public CORN::Data_record
, public Item
{
 public: // ArcCS tracking and control
   // ID's are numbers assigned by GIS
   // They correspond to Cell or Polygon ID's
   // Negative values represent offset areas.
   int32       scenario_ID;                               //050919
   int32       same_as_ID;  // In ArcCS this is the polygon ID this polygon is similar to
   int32       same_as_record_num;
   bool        run_it;                                                           //050729
   std::string notes;                                                            //130621_050922
 public: // Simulation control overrides
   Polygon_simulation_parameters parameter_overrides;                            //050630
   float32     cell_width;   // Used by watershed
 protected: // Soil overrides
   soil_horizon_array32(horizon_thickness); // m  soil horizon thickness (Corresponds to layer_thickness_32)
 public:
   Simulation_override_record
      (int32 _scenario_ID                                                        //050919
      ,const Polygon_simulation_parameters &_parameter_overrides_from_pat
      ,nat8                                 _actual_seqnum);                     //050729
   bool setup_record
      (const Scenario *template_sim_params                                       //020423
         // template_sim_params is now optional
         // if specified, check to see if coded parameter files exists
      ,bool            soils_mapped                                              //010520
      ,bool            uniform_soil_profile_mapped                               //050531
      ,float32         cell_width                                                //990528
      ,bool            subsurface_flow                                           //990604
      ,bool            steepness_mapped                                          //010129
      ,float32        *horizon_thickness_override                                //991004
      ,bool            init_PAW_mapped                                           //010129
      ,bool            init_NO3_mapped                                           //010129
      ,bool            weather_mapped                                            //010129
      ,bool            rotations_mapped                                          //010129
      ,bool            recalibration_mapped                                      //060411
      ,bool            water_table_mapped                                        //060706
      ,std::ostream   &errors);
   virtual bool expect_structure(bool for_write = false);                        //161025
   virtual int compare(const Item &other) const;
   bool check_coded_file_exists                                                  //010129
      (const CORN::OS::File_name&   template_filename
      ,const std::string&           filename_code
      ,std::ostream&                errors);
   const std::string& compose_as_command_line_arguments
      (std::string& command_line_args)                                     const;//140216
};
//_2001-01-29_1999____________________________class:Simulation_override_record_/
} // namespace CropSyst                                                          //130621
#endif
//arccs_table.h

