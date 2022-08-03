#error This is obsolete the original STATSGO database nolonger exists , now use STATSGO2_to_CS_soil

#ifndef soil_param_with_STATSGOH
#define soil_param_with_STATSGOH
#include "soil/soil_param.h"
#include <STATSGO_deprecated/library/STATSGO_database.h>
//______________________________________________________________________________
class Smart_soil_parameters_with_STATSGO
: public Smart_soil_parameters
{public:
   inline Smart_soil_parameters_with_STATSGO()
      : Smart_soil_parameters()
      {};
   bool read_available_STATSGO_data                                              //000113
      (STATSGO::Database  &STATSGO_database
      ,const char *_MUID                                                         //050921
      ,uint8       _seqnum // sequence number
      ,uint8       _COMPPCT                                                      //080303
      ,float32     _max_evap_layer_thickness_m);                                 //051201
      /**<
         Read any relevent data from the STATSGO database.
         Also derive any relevent data I.e. compute hydraulic properties from texture.
         This can only be done by smart soil file because hydraulic prop computation is provided by soil_texture_hydraulics.
      **/
   virtual void expect_structure(bool for_write = false);                        //981103
 public: // So STATSGO objects can access
   virtual bool interpret_STATSGO_layer(nat8 layer,STATSGO::LAYER_data_record &layer_record);   //060127
   bool read_available_STATSGO_data                                              //060127
      (STATSGO::Database::State_tables &state_tables
      ,const char *_MUID  // I.e. WA0001
      ,uint8       _SEQNUM // sequence number
      ,uint8       _COMPPCT                                                      //080303
      ,float32     _max_evap_layer_thickness_m);                                 //051201
};
//_2006-02-13___________________________________________________________________
#endif

