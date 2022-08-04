#ifndef cs_mgmtH
#define cs_mgmtH

#include "options.h"
#if (MANAGEMENT == 4)
#include "CropSyst/source/management/management_param_V4.h"
#else
#include "CropSyst/source/management/management_param_V5.h"
#endif
#include "common/recorder/recorder.h"

class Common_event_list;                                                         //120620
namespace CropSyst {
class Desired_variables;                                                         //030801
//______________________________________________________________________________
class Management
: public CropSyst::Management_parameters                                         //010109
{
   int16 days_since_last_clipping;                                               //980826
 public:  // computed values (today's accumulation)
   float64 latest_grazing_percent_N_as_OM;                                       //040625
   float64 latest_grazing_percent_N_as_NH3;                                      //040625
 public: // output control
   bool structure_defined_check_used;                                            //030801
 public:
   inline Management()
      : CropSyst::Management_parameters()
      , days_since_last_clipping(0)                                              //980826
      , latest_grazing_percent_N_as_OM(50.0)                                     //040625
      , latest_grazing_percent_N_as_NH3(50.0)                                    //040625
      {}
   virtual ~Management() {}                                                      //120217
   virtual const char *get_record_section_label() const { return "management";};
   void transfer_all
      (Common_event_list &event_list
      , bool run_nitrogen
      , Synchronization_mode what_to_transfer //= ANY_SYNC_MODE                  //151004
      , const char  *management_filename);                                       //041015
      // May be 0 if not to be associated with a mangement filename in schedule
   bool check_for_periodic_clipping
      (float64 crop_LAI
      ,const CORN::Date_const&today );
};
//______________________________________________________________________________
} // namespace CropSyst
#endif
//cs_mgmt.h

