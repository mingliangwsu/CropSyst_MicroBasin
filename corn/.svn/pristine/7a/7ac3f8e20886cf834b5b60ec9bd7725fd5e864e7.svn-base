#ifndef time_secondH
#define time_secondH
#include "corn/chronometry/time_A.h"
namespace CORN
{
//______________________________________________________________________________
class Time_second_cowl
: public extends_ Time_abstract
{
 protected:
   nat32 &ref_seconds;  // seconds after midnight
 public: // structors
   inline Time_second_cowl(nat32 &ref_seconds_)
      : Time_abstract()
      , ref_seconds(ref_seconds_)
      {}
 public: // accessors
    virtual datetime64   get_datetime64()                                 const;
    virtual float64      get_time64()                                     const;
   inline virtual Seconds get_seconds_after_midnight()                    const
      { return ref_seconds; }
  public: // assignations
   virtual datetime64 set_time(const Time &time)                   assignation_;
   virtual datetime64 set_datetime64(datetime64 time64)            assignation_;
   virtual datetime64 set_HMSc
      (Hour hour, Minute minute, Second second
      ,Centisecond centisecond)                                    assignation_;
   virtual datetime64 set_HMSm
      (Hour hour, Minute minute, Second second
      ,Millisecond millisecond)                                    assignation_;
   virtual datetime64 set_S(Seconds _seconds)                      assignation_;
 public: // math
   virtual datetime64 inc_hours(Hours hours)                       assignation_;
   virtual datetime64 inc_minutes(Minutes minutes)                 assignation_;
   virtual datetime64 inc_seconds(Seconds seconds)                 assignation_;
 public: // methods for arbitrary time
   virtual int8 compare(const Temporal /*180626 Time*/ &other_time)       const;
};
//______________________________________________________________________________
class Time_second_clad
: public extends_ Time_second_cowl
{
 protected:
   nat32 seconds;       // seconds after midnight
 public: // structors
   inline Time_second_clad()
      : Time_second_cowl(seconds)
      {}
   inline Time_second_clad(const Time &from_copy)
      : Time_second_cowl(seconds)
      {  seconds=from_copy.get_seconds();
      }
   inline Time_second_clad(Hour hour)
      : Time_second_cowl(seconds)
      , seconds(0)
      { set_HMS(hour,0,0);}
   inline Time_second_clad(Hour hour, Minute minute)
      : Time_second_cowl(seconds)
      , seconds(0)
      { set_HMS(hour,minute,0);}
   inline Time_second_clad(Hour hour, Minute minute, Second second)
      : Time_second_cowl(seconds)
      , seconds(0)
      { set_HMS(hour,minute,second);}
 private:
   Time_second_clad *abstract_check() { return new Time_second_clad; };
};
//______________________________________________________________________________
} //namespace CORN
#endif

