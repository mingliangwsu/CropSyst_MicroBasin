#ifndef date_TH
#define date_TH
#include "corn/chronometry/date_A.h"
namespace CORN
{
//______________________________________________________________________________
template <typename dateT>  // floating point or integer
class Date_cowl_const
: public extends_ Date_const_abstract
{
 protected:
   const dateT &date_ref;
 public:
   Date_cowl_const(const dateT &date_ref_)
      : Date_const_abstract()
      , date_ref(date_ref_)
      {}
 public: // accessors
   inline virtual datetime64 get_datetime64()                              const
      { return (datetime64)((nat32)date_ref);}
   inline virtual date32 get_date32()                                      const
      { return (date32) date_ref; }
};
//_2017-08-24__________________________________________________Date_cowl_const_/
template <typename dateT>  // floating point or integer
class Date_cowl
: public extends_ Date_abstract
{
 protected:
   dateT &date_ref;
 public:
   inline Date_cowl(dateT &date_ref_)
      : Date_abstract()
      , date_ref(date_ref_)
      {}
 public: // assignations
   inline virtual datetime64 clear()                             initialization_
      { date_ref = 0; return 0; }
   virtual datetime64 set_DT
      (const Date_interface &date_
      ,const Time_interface &)                                      assignation_
      {  date_ref = (dateT)date_.get_date32();
         // Time is currently ignored
         return get_datetime64();
      }
   virtual datetime64 set_datetime64(datetime64 value)              assignation_
      { date_ref = (dateT)value; return get_datetime64(); }
   virtual datetime64 set_date32(int32 date_32)                     assignation_
      { date_ref = (dateT)date_32; return get_datetime64(); }
   virtual datetime64 set_YD(Year year,DOY doy)                     assignation_
      { date_ref = (dateT)(year*1000+doy); return get_datetime64(); }
   virtual datetime64 set(const Temporal &new_date)                 assignation_
      { date_ref = (dateT)(new_date.get_datetime64()); return get_datetime64();}
 public: // accessors
   inline virtual datetime64 get_datetime64()                             const
      { return (datetime64)(nat32)(date_ref);}
   inline virtual date32 get_date32()         const { return (date32)date_ref; }
};
//_2017-08-24________________________________________________________Date_cowl_/
template <typename dateT>  // floating point or integer
class Date_clad
: public extends_ Date_cowl<dateT>
{
 protected:
   friend class Common_tabular_file_format;
   dateT date_num; //Conforms to ISO8601:2004
 public:
   Date_clad()
      : Date_cowl<dateT>(date_num)
      , date_num(0)
      { Date_abstract::set_now(); }
   Date_clad(const date32 date_raw)
      : Date_cowl<dateT>(date_num)
      , date_num((dateT)date_raw)
      { }
   Date_clad(const Date_abstract &other)
      : Date_cowl<dateT>(date_num)
      , date_num(other.get_date32())
      { }
   Date_clad(const Temporal &other)
      : Date_cowl<dateT>(date_num)
      , date_num(other.get_date32())
      { }
   Date_clad(Year year, DOY doy)
      : Date_cowl<dateT>(date_num)
      , date_num(0)
      { Date_cowl<dateT>::set_YD(year,doy); }
   Date_clad(Year year, Month month, DOM dom)
      : Date_cowl<dateT>(date_num)
      , date_num(0)
      { Date_cowl<dateT>::set_YMD(year,month,dom); }
 public:
   // get_datetime64 and get_date32 shouldn't be needed should be handled by cowl
   virtual datetime64 get_datetime64()                                     const
      { return (datetime64)((nat32)date_num);}
   virtual date32 get_date32()                                             const
      { return (date32)date_num; }
};
//_2017-08-24________________________________________________________Date_clad_/
} // namespace CORN

#endif
