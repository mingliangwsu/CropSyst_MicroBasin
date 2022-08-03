#ifndef seeding_paramH
#define seeding_paramH
#include "corn/primitive.h"
#include "corn/const.h"
//180326 #include "corn/validate/validtyp.h"
#include "corn/parameters/parameter.h"
namespace CORN
{
class Data_record; // forward declaration
}
//______________________________________________________________________________
class Seeding_parameters
{
public:
   float32  rate_seeds_m2;                   // seeding rate seeds/m2
   float32  emergence_rate_percent;          // anticipated emergence percent  (100% indicates all seeds emerge)
   float32  sowing_depth_cm;                 //
public: // validators
   CORN::Parameter_number p_rate_seeds;                                          //180326
   CORN::Parameter_number p_emergence_rate;                                      //180326
   CORN::Parameter_number p_sowing_depth;                                        //180326
   /*180326
   CORN::Valid_float32 v_rate_seeds;
   CORN::Valid_float32 v_emergence_rate;
   CORN::Valid_float32 v_sowing_depth;
   */
public: // constructors
   Seeding_parameters();
   Seeding_parameters(const Seeding_parameters &original);
   inline virtual ~Seeding_parameters() {}                                       //170217
public: // I/O
   virtual void setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_;
};
//______________________________________________________________________________
#endif

