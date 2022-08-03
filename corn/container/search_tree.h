#ifndef search_treeH
#define search_treeH

// These are search trees that can be used for indexes.
// There is one to store associations and one to store enumerations.
// Currently these are implemented as balanced binary tree
//
#ifndef binary_treeH
#  include "corn/container/binary_tree.h"
#endif

namespace CORN {
 interface_ Item;
 class Enumeration;
//______________________________________________________________________________
class Association_search_tree
: public Binary_tree
{
 public:
  inline Association_search_tree()
  : Binary_tree(true)
   {}
  inline virtual ~Association_search_tree() {}                                   //081125
   virtual Item *find(const char *search_key,bool case_sensitive = true) const;

      // probably could return a container //180101

   /**< \return the association with the matching key (Case sensitive or case insensitive).
      0 if no matching association.
   **/
};
//_2005-11-01___________________________________________________________________
// Items appended to the Enumeration_search_tree are sorted by the key
class Enumeration_search_tree
: public Binary_tree                                                             //051010
 {
 public:
   inline Enumeration_search_tree()
   : Binary_tree(true)                                                           //051010
   {}
   inline virtual ~Enumeration_search_tree() {}                                  //081125
   virtual Enumeration *find(nat32 search_key) const;
   /**<
   \returns the association with the matching key
    0 if no matching association.
   **/
   virtual bool remove_all_matching(nat32 search_key);                           //020319
   /**< Remove removes all matching entries from the list
   and deletes the associated data!
   \return true if there was a matching deletion.
   **/
};
//______________________________________________________________________________
} // namespace CORN

#endif

