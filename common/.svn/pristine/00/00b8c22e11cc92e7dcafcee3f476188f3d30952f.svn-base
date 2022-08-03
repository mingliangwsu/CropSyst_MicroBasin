#ifndef balancerH
#define balancerH

/*
	This class is a generic Balancer
*/
#include "corn/primitive.h"
//140118 #include "corn/std/std_fstream.h"
#include "corn/dynamic_array/dynamic_array_T.h"
#include "UED/library/UED_types.h"
#include "corn/measure/units.h"
#if (CS_VERSION == 5)
#include "CS_suite/simulation/CS_simulation_element.h"
#else
#include "corn/container/unilist.h"
#endif

class UED_file;
using namespace CORN;

namespace Simulation
{
//______________________________________________________________________________
class Balancer
//#if (CS_VERSION == 5)

// I don't think I want balancers to be simulation elements

//: public extends_ CS::Simulation_element
//#else
: public implements_ CORN::Item
//#endif
{
private:
   CORN::Units_code  units;           // All variables in the balance have the same units
private:
   class Accumulator
   {  std::string             description;
   public:
      float32                 initial; // plus
      Dynamic_array<float64>  pluses;
      Dynamic_array<float64>  minuses;
      float32                 final;   // minus
      float32                 balance;
   private:
      float32                 start_initial; // This is used to transition from the time step and to specify the very initial value
   public:
      Accumulator(const char *balance_description, const char *accumulator_description);
      void clear()                                                 modification_;
      float32 add(const Accumulator &augend)                       modification_;
      float32 update_balance()                                     modification_;
      ///< \return the balance
      bool start_timestep()                                        modification_;
      void reinitialize(float32 _initial)                          modification_;
   public:
      void write(std::ostream &balance_report_file)                performs_IO_;
   };
protected:
   Accumulator  daily;
   Accumulator  annual;
   Accumulator  *seasonal; // Seasonal is options
   cognate_ std::ostream *balance_file_annual;
   cognate_ std::ostream *balance_file_daily;
protected:
public: // constructor and initialization
   Balancer(CORN::Units_code _units, const char *balance_description
      /*150907
      #if (CS_VERSION >= 5)
      ,modifiable_ CS::Simulation_control &_simulation_control
      #endif
      */
      );

   virtual ~Balancer();

   inline void know_balance_file_annual(std::ostream *_balance_file_annual) cognition_
      { balance_file_annual = _balance_file_annual;}
   inline void know_balance_file_daily(std::ostream *_balance_file_daily) cognition_
      { balance_file_daily = _balance_file_daily;}

public:
   virtual float32 get_final() = 0;
   virtual bool start_day()                                        modification_;//130618
   virtual bool start_year()                                       modification_;//130618
   virtual bool end_day()                                          modification_;//130618
   virtual bool end_year()                                         modification_;//130618
   virtual float32 start_season()                                  modification_;
   virtual float32 end_season()                                    modification_;
      ///< \return the balance which should be 0.0 (approximately)
   virtual bool deactivate_seasonal();
protected: // The following are used to write the balance to a stream
   virtual bool get_caption_plus (uint32 plus_index ,std::string &plus_caption) const=0;
   virtual bool get_caption_minus(uint32 minus_index,std::string &minus_caption)const=0;
      ///< The captions are written to column headers.
      /// All derived classes must override and the derived method will typically call the parent class's method
      /// \return true if the caption was set, false if there is no such index.
public:
   virtual void write_column_headers(std::ostream &balance_report_file) performs_IO_;
   virtual void write_daily(std::ostream &balance_report_file)       performs_IO_;
   virtual void write_annual(std::ostream &balance_report_file)      performs_IO_;
   virtual void write_seasonal(std::ostream &balance_report_file)    performs_IO_;

//NYI   virtual void write_current(ostream &balance_report_file);
//NYI   virtual void write_accumulation(ostream &balance_report_file);
};
//______________________________________________________________________________
} //  namespace Simulation
#endif


