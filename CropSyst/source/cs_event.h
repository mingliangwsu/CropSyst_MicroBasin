#ifndef cs_eventH
#define cs_eventH
#include "cs_glob.h"
#include "cs_events.h"
void purge_pending_events();
//______________________________________________________________________________
namespace CORN { class Date; }
//______________________________________________________________________________
class profile_print_event
: public CropSyst::Event                                                         //011207
{public:
   class Print_operation
   : public Common_operation
   {  bool &record_soil_profile_today;
    public:
      inline virtual const char *get_type_label()                          const { return "print_profile"; }
      inline virtual const char *get_simulation()                          const { return "CropSyst"; }
      inline virtual int32       get_type()                                const { return CS_OP_PROFILE_PRINT; }
      inline virtual bool        parameters_to_be_stored_in_event_file()   const { return true;}
      inline virtual const char *get_primary_section_name()                const { return "print_profile"; }
      inline Print_operation(bool &_print_soil_profile_today)
         : Common_operation()
         , record_soil_profile_today(_print_soil_profile_today)
         {}
      virtual bool process();
   };
   //_2005-12-01____________________________________________________
 public:
   profile_print_event(const CORN::Date_const &_date                             //000204
      ,bool &_print_soil_profile_today);                                         //010202
   virtual const char *label_string(std::string &buffer) const;
};
//_1999-11-22___________________________________________________________________
#ifdef MANAGEMENT
void log_automatic_irr_event(const CORN::Date_const &date, float64 amount);      //020913
#endif
#endif
//cs_event.h

