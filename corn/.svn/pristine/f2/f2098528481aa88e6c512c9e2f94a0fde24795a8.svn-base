#ifndef date_32H
#define date_32H
#include "corn/chronometry/date_T.h"
namespace CORN
{
class Common_tabular_file_format;
//______________________________________________________________________________
class Date_cowl_const_32
: public extends_ Date_cowl_const<date32>
{public:
   inline Date_cowl_const_32(const date32 &date_ref_)
      : Date_cowl_const<date32>(date_ref_)
      {}
 public: // accessors
   inline const date32 &ref_date32()                  const { return date_ref; } //171115
};
//_Date_cowl_const_32_______________________________________________2017-05-24_/
class Date_cowl_32
: public extends_ Date_cowl<date32>
{public:
   inline Date_cowl_32(date32 &date_ref_)
      : Date_cowl<date32>(date_ref_)
      {}
 public: // assignations
   inline const date32 &ref_date32()                  const { return date_ref; } //171115
   inline modifiable_ date32 &mod_date32()                  { return date_ref; } //171115
};
//_Date_cowl_32_____________________________________________________2017-04-26_/
class Date_clad_32
: public extends_ Date_clad<date32>
{public:
   Date_clad_32();
   Date_clad_32(const date32 date_raw);
   Date_clad_32(const Date_clad_32 &other);
   Date_clad_32(const Temporal &other);
   Date_clad_32(Year year, DOY doy);
   Date_clad_32(Year year, Month month, DOM dom);                                //170712
 public:
   inline const date32 &ref_date32()                  const { return date_num; } //171115_170530
   inline modifiable_ date32 &mod_date32()                  { return date_num; } //171115_
 private:
   Date_clad_32 *check_abstract() { return new Date_clad_32(); }
};
//_Date_clad_32________________________________________________________________/
//The following are temporary aliases to transition from the previous class names
//These will eventually be removed. 170828
#define Date_32_cowl Date_cowl_32
#define Date_32_clad Date_clad_32

/*170824
class Date_cowl_const_32
: public extends_ Date_const_abstract
{
 private:
   const date32 &date_ref;
 public:
   inline Date_cowl_const_32(const date32 &date_ref_)
      : Date_const_abstract()
      , date_ref(date_ref_)
      {}
 public: // accessors
   inline virtual datetime64 get_datetime64()                              const
      { return (datetime64)date_ref;}
   inline virtual date32 get_date32()                                      const
      { return date_ref; }
   inline const date32 &ref_date32()                        { return date_ref; }
 };
//_2017-05-24___________________________________________________________________
class Date_cowl_32
: public extends_ Date_abstract                                                  //170815
//170815 public extends_ Date_abstract
{
 private:
   date32 &date_ref;
 public:
   inline Date_cowl_32(date32 &date_ref_)
      : Date_abstract()
      , date_ref(date_ref_)
      {}
 public: // assignations
   virtual datetime64 set_DT
      (const Date_interface &
      ,const Time_interface &)                                     assignation_;
   virtual datetime64 set_datetime64(datetime64 value)             assignation_;
   virtual datetime64 set_date32(int32 date32)                     assignation_;
   virtual datetime64 set_YD(Year year,DOY doy)                    assignation_;
   virtual datetime64 set(const Temporal &new_date)                assignation_;
 public: // accessors
   inline virtual datetime64 get_datetime64()                             const
      { return (datetime64)date_ref;}
   inline virtual date32 get_date32()                 const { return date_ref; }
   inline date32 &ref_date32()                              { return date_ref; }
};
//_2017-04-26__________________________________________________________________________
class Date_clad_32
: public extends_ Date_cowl_32
{
 protected:
   friend class Common_tabular_file_format;
// public: // temporarily
   date32 date_num; //Conforms to ISO8601:2004
 public:
   Date_clad_32();
   Date_clad_32(const date32 date_raw);
   Date_clad_32(const Date_clad_32 &other);
   Date_clad_32(const Temporal &other);
   Date_clad_32(Year year, DOY doy);
   Date_clad_32(Year year, Month month, DOM dom);                                //170712
 public:
   inline date32 &ref_date32()                              { return date_num; } //170530

   // get_datetime64 and get_date32 shouldn't be needed should be handled by cowl
   inline virtual datetime64 get_datetime64()                              const
      { return (datetime64)date_num;}
   inline virtual date32 get_date32()                                      const
      { return date_num; }
 private:
   Date_clad_32 *check_abstract() { return new Date_clad_32(); }
};
*/
//_2017-04-26__________________________________________________________________________
/* replacements
ref_date_num() -> ref_date32()
*/
//______________________________________________________________________________
} // namespace CORN

#endif
