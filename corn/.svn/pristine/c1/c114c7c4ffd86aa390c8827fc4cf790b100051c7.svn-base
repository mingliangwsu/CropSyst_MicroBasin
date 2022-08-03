#ifndef arrayH
#define arrayH

#include <corn/container/container.h>

namespace CORN {
//______________________________________________________________________________
class Array
: public Container
{private:
   nat32 alloc_size;
   contribute_ nat32 curr_index ;                                                //011031
   Item_pointer *items;
 private:
   virtual void shift_down_to(nat32 to_index);                                   //991122
   // (Used for deleting items).
 public:
   Array(int32 i_alloc_size);
   inline virtual ~Array() {};                                                   //081125
   virtual nat32 count()                                                   const;//990104
#ifdef NYI
   inline virtual void detach(Container_item *detach_element) {}; // Not sure if this is needed
   // Removes the detach element from the list, but does not delete it
   // If detach_element is not in the list or is null, nothing is done.
#endif
   virtual Item * append(Item *new_element) ;
#ifdef NYI
   virtual Item *add_sorted                                                      //970928
      (Item *new_element
      , Ordering ordering = ASCENDING);
#endif
#ifdef NYI
   virtual Item * prepend(Item *new_element);
   virtual Item * insert_before(Item *new_element,Item *before_element) ;
   // not currently implemented in unidir list
   // virtual Item * add_sorted(Item *new_element);
#endif
   virtual nat32 delete_all(Item::Filter filter = Item::filter_all) ;
   virtual Item *pop_first()
      { Item *first = items[0];
        shift_down_to(0);
        return first;
      };
#ifdef NYI
   virtual Item *find_matching(const Item &item_to_match,bool from_beginning = true)  const;//030117
//990105   (was find, but conflict with association_list::find())
#endif
   virtual Item *move_to_next()                                            const;
#ifdef NYI
   virtual Item *move_to_prev()                                            const;
#endif
   virtual Item *move_to_first()                                           const;
#ifdef NYI
   virtual Item *move_to_last()                                            const;
#endif
   virtual Item *move_to(Item *new_current)                                const;//990225
   virtual Item *current()                                                 const;//970403
   virtual Item *move_to_index(nat32 index)                                const;//991216
   virtual Item *get_at(nat32 index)                                       const;//991216
   virtual bool  delete_at(nat32 index);                                         //991216
#ifdef NYI
   virtual inline bool is_empty()                                          const;//040107
   virtual nat32 write(std::ostream &strm)                         modification_;//150728_970930
//             Although unilist modify itself, derived class may perform
//             additional processing and may need to modify themselves.
//             I/O methods should never be const.
#endif
};
//______________________________________________________________________________
}; // namespace CORN
#endif

