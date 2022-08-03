#ifndef cellH
#define cellH
#include <corn/primitive.h>
#include <corn/const.h>
#include <string>
namespace CORN
{
//______________________________________________________________________________
class Cell_common    // interface
{public:
    virtual ~Cell_common() {};
    virtual nat32  get_row()                                               const = 0;
    virtual nat32  get_col()                                               const = 0; // Note: Excel currently only uses uint16  for columns
};
//______________________________________________________________________________
class Cell_numeric    // interface
: public Cell_common
{public: // By default we try to store values in the largest common type
   inline virtual int8   set_int8 (int8 value)                    modification_ { return (int8) set_int16(value);};
   inline virtual int16  set_int16(int16 value)                   modification_ { return (int16)set_int32(value);};
   inline virtual int32  set_int32(int32 value)                   modification_ = 0;  // derived classes must implement

   inline virtual nat8   set_nat8 (nat16 value)                   modification_ { return (nat8) set_nat16(value);};
   inline virtual nat16  set_nat16(nat16 value)                   modification_ { return (nat16)set_nat32(value);};
   inline virtual nat32  set_nat32(nat32 value)                   modification_ { return (nat32)set_int32(value);}; // default falls back to integer

   inline virtual int8   get_int8()                                       const { return (int8) get_int16();};
   inline virtual int16  get_int16()                                      const { return (int16)get_int32();};
   inline virtual int32  get_int32()                                      const = 0;
   inline virtual nat8   get_nat8()                                       const { return (nat8) get_nat16();};
   inline virtual nat16  get_nat16()                                      const { return (nat16)get_nat32();};
   inline virtual nat32  get_nat32()                                      const { return (nat32)get_int32();};

   virtual float32 set_float32(float32 value)                      modification_{ return (float32)set_float64(value); };
   virtual float64 set_float64(float64 value)                      modification_= 0;
   virtual float32 get_float32()                                          const { return (float32)get_float64(); };
   virtual float64 get_float64()                                          const = 0;
};
//______________________________________________________________________________
class Cell_textual   // interface
: public Cell_common
{public:
   virtual const std::string  & set_string  (const std::string &value) modification_ = 0;
   virtual const
   std::wstring & set_wstring (const std::wstring &value)          modification_= 0;
   virtual std::string  & get_string  (std::string &value)                const = 0;
   virtual std::wstring & get_wstring (std::wstring &value)               const = 0;
};
//______________________________________________________________________________
}; // namespace CORN
#endif

