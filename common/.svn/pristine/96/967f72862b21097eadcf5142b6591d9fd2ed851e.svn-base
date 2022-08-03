#include "common/geodesy/geolocation_item.h"
//______________________________________________________________________________
Geolocation_item::Geolocation_item()
: CORN::Item()
{}
//_2013-05-29___________________________________________________________________
const char *Geolocation_item::label_string(std::string &buffer) const
{  return Geolocation::label_string(buffer);
}
//_2017-04-23___________________________________________________________________
Geocoordinate_item::Geocoordinate_item()
: CORN::Item()
, Geocoordinate()
{}
//______________________________________________________________________________
bool Geocoordinate_item::is_key_string(const std::string &key)              affirmation_  //180820
{  std::string label; Geocoordinate::label_string(label);       
   return label == key; 
}
//_is_key___________________________________________________________2018-08-20_/
/*180820  was probably only used for find_cstr now using is_key

const char *Geocoordinate_item::get_key()                                  const
{  return Geocoordinate::label_string(key);                                      //170423
}
*/
//_2014-01-28___________________________________________________________________
const char *Geocoordinate_item::label_string(std::string &buffer)          const
{  return Geocoordinate::label_string(buffer);
}
//_2017-04-23___________________________________________________________________
int Geocoordinate_item::compare(const CORN::Item &other_item)              const
{
   int compare = 0;
   const Geocoordinate_item *other_geocoord
      = dynamic_cast<const Geocoordinate_item *> (&other_item);
   if (other_geocoord)
   {  compare = Geocoordinate::compare(*other_geocoord);
   } else
      compare = -1;
   return compare;
}
//_2016-09-02__________________________________________________________compare_/
Geocoordinate_item *Geocoordinate_item::clone()                            const
{  return new Geocoordinate_item(*this);
}
//_2017-08-23____________________________________________________________clone_/
