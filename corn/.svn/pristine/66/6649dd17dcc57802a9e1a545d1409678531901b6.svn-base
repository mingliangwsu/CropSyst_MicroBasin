#ifndef rec_setH
#define rec_setH

//18-01-07 #include "corn/container/association.h"
#include "corn/format/excel/BIFF_record.h"

namespace CORN {
//______________________________________________________________________________
class BIFF_record_set
: public Item 
, public Unidirectional_list  // List of records (in Binary_record_index_node_dynamic)
{
  // This is a set of related records that begin with an BOF and end with EOF
  // I.e. Workbook global section, Worksheet sections and Chart sections.
  // The records are stored in a lists Binary_record_index_node but BIFF_record_set is not a Binary_record_index.
   std::string       name;       // The name of the sheet/macro/chart/VB module
 public:
   inline BIFF_record_set(const std::string &i_name)
      :  Item() //180101 Association()
      ,  Unidirectional_list()
      ,  name(i_name)
      {}
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return name == key; }

/*180820  was probably only used for find_cstr now using is_key
      
   inline virtual const char *get_key() const { return name.c_str(); }       //030109
*/   
};
//______________________________________________________________________________
} //namespace CORN
#endif

