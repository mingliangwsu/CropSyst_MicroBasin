#ifndef enumlistH
#define enumlistH
#ifndef bi_listH
#  include "corn/container/bilist.h"
#endif
//    An enumeration list is similar to an Association list,
//          but the key is an unsigned integer;
namespace CORN {
//______________________________________________________________________________
class Enumeration : public Item
{
 public:
   Enumeration();
   virtual ~Enumeration();                                                       //081125
   virtual int compare(const Item &other)                                 const;
   //170424 replaced with label_wstring virtual const char *label_cstr(char *buffer)                const; //030120
                     //For some applications, label_cstr should be overridden
   virtual const char *label_string(std::string &buffer)                  const; //170424
/*180820 already declared in Item
   virtual bool is_key_string(const std::string &key)            affirmation_=0; //180820
*/


/*180820  was probably only used for find_cstr now using is_key

   virtual nat32 get_key_nat32()                                      const = 0; //110305_020319
*/
};
//______________________________________________________________________________
//   Now based on bidirectional list so association lists can be used in RUI controls
// Items appended to the enumeration list are kept in the order added.
class Enumeration_list
: public Bidirectional_list
{
 public:
   Enumeration_list();                                    //160616_051010
   Enumeration_list(bool unique_keys);                                    //160616_051010
      //121112 NYI should have the option to have unique keys.
      // This would probably be common to all container classes.
   virtual ~Enumeration_list();                                                  //081125
   virtual Enumeration *find(nat32 search_key)                            const; //020319
      /**<\fn \return the association with the matching key
         \return 0 if no matching association. */
   virtual nat32 find_index(nat32 search_key)                              const;//130125
      /**<\fn \return the index (0 based position) of the item matching the search key.
         \return npos if no matching association.
      */

      // Note, currently this class has no restriction on mutiple items having
      // the same key value.  The find methods return the first occurance.


   virtual nat32 remove_all_matching(nat32 search_key)             modification_;//020319
      /**<\fn Remove removes all matching entries from the list
         and deletes the associated data!
         \Return number of matching deletionions
            //140716 true if there was a matching deletion.
      **/
};
//_2001-10-31___________________________________________________________________
} // namespace CORN
#endif
// enumlist.h

