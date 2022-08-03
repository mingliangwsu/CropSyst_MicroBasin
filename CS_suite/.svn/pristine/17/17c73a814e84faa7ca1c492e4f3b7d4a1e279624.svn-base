#include "CS_identification.h"
#include "corn/string/strconv.hpp"
//______________________________________________________________________________
namespace CS
{
//______________________________________________________________________________
Identification::Identification(int32 ID_)
: number(ID_)
, code()
{  CORN::append_nat32_to_string(number,code);
}
//_2015-10-26___________________________________________________________________
Identification::Identification(const std::string &ID_)
: number()
, code(ID_)
{  number = CORN::cstr_to_int32(ID_.c_str(),10);
}
//_2015-10-26___________________________________________________________________
bool Identification::set_code(const std::string &ID_)
{  code = ID_;
   number = CORN::cstr_to_int32(ID_.c_str(),10);
   return true;
}
//_2015-10-26_________________________________________________________set_code_/
bool Identification::set_number(int32 ID_)
{  number =ID_;
   code.clear(); CORN::append_int32_to_string(number,code);
   return true;
}
//_2015-10-26_______________________________________________________set_number_/
} // namespace CS

