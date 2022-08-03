check where used, probably obsolete
#ifndef SCENARIO_NAME_SEL_H
#define SCENARIO_NAME_SEL_H

#include "corn/container/item.h"
class Name_selection
: public Item
{
   CORN_string name;
public:
   inline Name_selection(const char *i_name)
      : Item()
      , name(i_name)
      {}

   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return name == key; }

/*180820  was probably only used for find_cstr now using is_key
   
   inline virtual const char *get_key() const
   { return name.c_str(); };
*/   
};

#endif
