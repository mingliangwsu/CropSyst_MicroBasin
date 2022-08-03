#ifndef CS_recordingH
#define CS_recordingH
#include "CS_suite/simulation/CS_simulation_element.h"
#include "CS_suite/observation/CS_UED_recorder.h"
namespace CS
{
//______________________________________________________________________________
class Recording_system
: public Simulation_element_abstract
{
 private:
   Examination &examination;
 public:
   Recording_system(const CORN::date32 &today_raw);
 public:
   virtual bool start_year()                                      modification_;
   virtual bool end_day()                                         modification_;
   virtual bool end_year()                                        modification_;
   virtual bool stop()                                            modification_;
};
//_2017-05-28_________________________________________________Recording_system_/
} // namespace CS
#endif
