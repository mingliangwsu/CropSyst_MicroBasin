#ifdef USE_PCH
#  include <corn/container/container_pch.h>
#else
#  include <corn/container/array.h>
#endif

namespace CORN {
//______________________________________________________________________________
Array::Array(int32 i_alloc_size)
: alloc_size(i_alloc_size)
, items(new Item_pointer[i_alloc_size])
, curr_index(0)
{  for (nat32 i = 0; i < alloc_size; i++)
      items[i] = 0;
};
//______________________________________________________________________________
nat32 Array::count() const
{  nat32 cnt = 0;
   for (nat32 i = 0; i < alloc_size; i++)
      if (items[i])
         cnt++;
      else return cnt;
   return cnt;
};
//_1999-01-04___________________________________________________________________
#ifdef NYI
void Array::detach(Item *detach_element)
{  set_modified(true);                                                           //060221
}; // Not sure if this is needed
// Removes the detach element from the list, but does not delete it
// If detach_element is not in the list or is null, nothing is done.

#endif
//______________________________________________________________________________
Item * Array::append(Item *new_element)
{  // Find first free entry
   for (nat32 i = 0; i < alloc_size; i++)
   {  if (items[i] == 0)
      {  items[i] = new_element;
         set_modified(true);                                                    //060221
         return new_element;
      };
   };
   return new_element;
};
//______________________________________________________________________________
#ifdef NYI
   virtual Item * Array::prepend(Item *new_element);
   virtual Item * Array::insert_before(Item *new_element,Item *before_element) ;
   // not currently implemented in unidir list
   // virtual Item * add_sorted(Item *new_element);

#endif
//______________________________________________________________________________
nat32 Array::delete_all(Item::Filter filter)
{  nat32 count_deleted = 0;                                                      //040107
   nat32 count_kept = 0;                                                         //040318
   for (nat32 i = 0; i < alloc_size; i++)
   {  if (items[i])
      {  if (items[i]->matches_filter(filter))                                   //040318
         {  count_deleted += 1;                                                  //040107
            delete items[i];
         }                                                                       //040107
         else                                                                    //040318
         {  items[count_kept++] = items[i];                                      //040318
            items[i] = 0;                                                        //040318
         };                                                                      //040318
      };                                                                         //040318
      items[i] = 0;
   };
   return count_deleted;                                                         //040107
};
//______________________________________________________________________________
void Array::shift_down_to(nat32 to_index)
{ // Should move all the array item pointers
  // down to the next index until to_index is reached. (Used for deleting items).
   for (nat32 i = to_index; i < alloc_size-1; i++)
      items[i] = items[i+1];
   items[alloc_size-1] = 0;
};
//_1999-11-22___________________________________________________________________
#ifdef NYI
Item *Array::find_matching(const Item &item_to_match,bool from_beginning = true)  const;//030117
//990105                              (was find, but conflict with association_list::find())
#endif
Item *Array::move_to_next()                                                const
{  // Skip over any unassigned entries.
   do
   {  curr_index ++;
      if (curr_index >= alloc_size)
         return 0;
      } while (items[curr_index] == 0);
   return  items[curr_index];
};
//______________________________________________________________________________
#ifdef NYI
virtual Item *Array::move_to_prev()                                        const
#endif
Item *Array::move_to_first()                                               const
{  curr_index = 0;
   while (items[curr_index] == 0)
   {  curr_index ++;
      if (curr_index >= alloc_size)
         return 0;
   };
   return items[curr_index];
};
//______________________________________________________________________________
#ifdef NYI
virtual Item *Array::move_to_last()                                        const;
#endif
Item *Array::move_to(Item *new_current) const
{  for (curr_index = 0; (curr_index < alloc_size) ; curr_index++)
      if (items[curr_index] !=new_current)
         return items[curr_index];
   return 0; // NULL;
};
//_1999-02-25___________________________________________________________________
Item *Array::current()                                                     const
{  return items[curr_index];
};
//_1997-04-03___________________________________________________________________
Item *Array::move_to_index(nat32 index)                                    const
{  if (index < alloc_size)
      curr_index = index;
   return items[index]; // use index not current index
};
//______________________________________________________________________________
   // The list is index based at 0.
Item *Array::get_at(nat32 index) const
{  return (index < alloc_size) ? items[index] : 0;
};
//______________________________________________________________________________
bool Array::delete_at(nat32 index)
{  bool deleteable = (index < alloc_size);                                       //100616
   if (deleteable)                                                               //100616
   {  delete items[index];
      // Now shift all the array elements.
      for (nat32 i = index; i < (alloc_size-1); i++)
      {  items[i] = items[i+1];
      };
      delete items[alloc_size-1];                                                //991215
      items[alloc_size-1] = 0;                                                   //991215
   };
   return deleteable;                                                            //100616
};
//______________________________________________________________________________
#ifdef NYI
virtual inline int Array::empty() const  ;

virtual void Array::write(STD_NS ostream &strm)                    modification_;//970930
   // Although unilist modify itself, derived class may perform
   // additional processing and may need to modify themselves.
   // I/O methods should never be const.
#endif
//______________________________________________________________________________
/*001106_*/ }; // namespace CORN end




