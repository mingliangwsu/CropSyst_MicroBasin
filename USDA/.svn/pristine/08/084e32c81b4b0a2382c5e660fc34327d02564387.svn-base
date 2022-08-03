#ifndef chtexturegrpH
#define chtexturegrpH
#include "corn/data_source/datarec.h"
#include "chtexturegrp_struct.h"
#include "corn/const.h"
namespace USDA_NRCS
{
//_____________________________________________________________________________
class CHtexturegrp
: public CHtexturegrp_struct
, public CORN::Data_record
, public CORN::Item
{
 private:
   contribute_ bool key_field_is_chkey;
 public:
   inline CHtexturegrp()
      :CHtexturegrp_struct()
      ,CORN::Data_record("chtexturegrp")
      ,CORN::Item()
      , key_field_is_chkey(true)
      {}
   virtual bool expect_structure(bool for_write);
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return key == key_field_is_chkey ? chkey  : chtgkey }

/*180820  was probably only used for find_cstr now using is_key
   inline const char *get_key() const { return key_field_is_chkey ? chkey.c_str() : chtgkey.c_str(); }
*/   
   inline bool use_chkey_as_key_field() contribution_ { return key_field_is_chkey = true; }
};
//_____________________________________________________________________________
} //namespace USDA_NRCS
#endif
