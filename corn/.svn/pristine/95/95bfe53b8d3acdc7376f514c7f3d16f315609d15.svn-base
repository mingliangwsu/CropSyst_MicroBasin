#ifndef SDF_listH
#define SDF_listH
#include "corn/container/text_list.h"
/*171125
#ifndef associationH
#  include "corn/container/association.h"
#endif
*/
/*
This container is used for working with
System Data Format (SDF) lists.

(this could potentially be derived from Text list  (but not sure why this is an association list
I think it was simply because that was the closest thing I had to a text lists.

This class will probably become deprecated when I add SDF rendering to Text_list
Use instead use Text_list

*/
namespace CORN {
class SDF_List; // forward declaration for friendship
//______________________________________________________________________________
class SDF_List : public Text_list //171125 Association_list
{
private:
   bool updated;
   mutable std::string SDF_list_string;                                          //040909
      // This is only a buffer, data is stored as SDF_items
   bool space_is_a_delimiter;                                                    //090901
public:
   SDF_List(const char *SDF_list_string = 0,bool space_is_a_delimiter = true);
   inline virtual ~SDF_List() {}
   const char *get_cstr() const;
   void update();
   // Update refills the list based on the value buffer
   // This is used after the SDF_list_string has been read by data_record expect.
   //
   //
   std::string &get_SDF_for_data_record_expect();                                //040909
};
//______________________________________________________________________________
} // namespace CORN
#endif
// SDF_List

