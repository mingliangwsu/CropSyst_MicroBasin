#include "CS_suite/observation/CS_recording.h"
namespace CS
{
//______________________________________________________________________________
Recording_system::Recording_system(const CORN::date32 &today_raw)
: Simulation_element_abstract(today_raw)
, examination(get_examination_global())                                          //171115
{}
//_2017-05-28_________________________________________________Recording_system_/
bool Recording_system::start_year()                               modification_
{  return
   // I don't currently have subelement so I dont know yet to call the
   // superclass first or last (probably first)
   // Simulation_element_composite::start_year()
          //171115 provide_emanators(today_raw).start_year(today.get_datetime64())
          get_emanators().start_year()                                           //171115
   &&     examination.start_year()
   &&     (!UED_recorder_global) || UED_recorder_global->start_year()
   &&     Simulation_element_abstract::start_year();        // ????
}
//_2017-05-28___________________________________________________________________
bool Recording_system::end_day()                                   modification_
{  return  Simulation_element_abstract::end_day()                                //170601 ????
   && examination.end_day()
   &&     (!UED_recorder_global || UED_recorder_global->end_day());
   // I don't currently have subelement so I dont know yet to call the
   // superclass first or last (probably last)
}
//_2017-05-28___________________________________________________________________
bool Recording_system::end_year()                                  modification_
{  return Simulation_element_abstract::end_year()                                //170601 ????
   && get_emanators().end_year()                                                 //171115
   && ((!UED_recorder_global) || UED_recorder_global->end_year())
   && examination.end_year();
   // Examination global cleans up deletable inspections and tallies
   // (identified by UED recorder)

   // I don't currently have subelement so I dont know yet to call the
   // superclass first or last (probably last)
}
//_2017-05-28___________________________________________________________________
bool Recording_system::stop()                                      modification_
{  return Simulation_element_abstract::stop()                                    //170601 ????
   && (!UED_recorder_global) ||  UED_recorder_global->stop()
   // All emanators should forget  themselves and be stopped
   // (simulation elements do this automatically, but there
   //  may be some emanators that are not derived from simulation element.
   && get_emanators().stop();
   // Stop emanators last because recorder needs active inspectors

   // I don't currently have subelement so I dont know yet to call the
   // superclass first or last (probably last)
}
//_2017-05-28___________________________________________________________________
} // namespace CS
