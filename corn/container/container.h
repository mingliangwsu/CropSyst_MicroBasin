#ifndef containerH
#define containerH

#ifndef itemH
// Must be included first or some compilers with define ostream as as a member of CORN
#  include "corn/container/item.h"
#endif
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#ifndef constH
#  include "corn/const.h"
#endif

// These are abstract classes for CORN templateless data structures
#define is_greater_than(index) (index > 0)
#define is_less_than(index)    (index < 0)
#define is_equal_to(index)     (index == 0)

namespace CORN {
class Data_record;
class Binary_file_interface;                                                     //111015
//______________________________________________________________________________
class Container                                                                  //991105
{
 public: // Container node class   public  only for BC5 which incorrectly cannot see the protected node!
   class Node                                                                    //040107
   {
   protected:
      Item *elmt_data;                                                           //980206
   public: // structors:
      Node(Item *elmt_data_);
      virtual ~Node();
   public:
      virtual int compare(const Item &other)                              const; //980206
      virtual const char *label_string(std::string &buffer)               const; //170423
         // For some applications, label should be overridden
      inline Item *get()                                           modification_ { return elmt_data;}
      inline void set(Item *elmt_data_)                            modification_ { elmt_data = elmt_data_;} //980315
      virtual bool setup_structure(Data_record &data_rec,bool for_write) modification_; //020617
   };
 public:  // Iterator class
   class Iterator  //141111 actually an interface                                //030603
   {
   public:
      inline virtual ~Iterator() {}                                              //081125
   public:
      // Each of the following advances the iterator to the respective node
      // and returns the item at that position.
      // If the container is empty
      // or there is no item at the position it returns 0;
      virtual Item *  first() = 0;
      virtual Item *  last() = 0;
      virtual Item *  next() = 0;
      virtual Item *  prev() = 0;
      virtual Item *  current() = 0;
      virtual Item *  find(Item *item_to_find,bool from_beginning=false);        //030709
         // Returns item_to_find if item_to_find is in the container otherwise returns 0 indicating not found.
         // If from_beginning is true the search is done from the beginning of the list.
         // otherwise it searchs from the current position.
         // if the item is found, that node becomes the current node.            //030717
         // Find is overridden by derived iterators to make sure the pointers are right when removing and detaching does. //051101
      virtual bool has(Item *item_to_find,bool from_beginning=false);            //030709
         // Returns true if the item_to_find is stored in the container otherwise returns false.
         // If from_beginning is true the search is done from the beginning of the list.
         // otherwise it searchs from the current position.
         // if the item is found, that note becomes the current node.            //030717
/*180515 replaced with has_successor
      virtual bool has_more()                                        affirmation_=0;//150505
*/
      virtual bool has_predecessor()                             affirmation_=0; //180515
      virtual bool has_successor()                               affirmation_=0; //180515
         // Return true if there is more items (a next item) to iterate
      virtual Item *  find_comparable(const Item &comparable_to_find,bool from_beginning=false);   //051101
         // Returns item_to_find if item_to_find is in the container otherwise returns 0 indicating not found.
         // If from_beginning is true the search is done from the beginning of the list.
         // otherwise it searchs from the current position.
         // if the item is found, that note becomes the current node.
         // The basic container Iterator class provides a simple
         // exhaustive search from the beginning of the structure
         // derived classes (I.e. search trees) may override this
         // using a faster search algorithm afforded by the nature of the data structure.
      virtual Item *  Ith(nat32 i) = 0;                                          //030707
         // Advances the iterator to the Ith node (0 based).
      virtual Item *  Nth(nat32 n);
         // Advances the iterator to the Nth node (1 based).
   public: // The following are editing.
      virtual bool delete_current();
         //  Deletes the current node and the data.
         //  The node data is deleted.
         //  Returns true if successful.
      virtual Item *detach_current() = 0;
         //  Removes the current node from the list
         //  The node data is not deleted.
         //  Returns the item or 0 if not successful
      virtual void end() = 0;
         // Ends the iteration
   };
public:
   struct Format
   {  // These should be wchar_t but std::cout is not writing them
      char *initializer;
      char *finalizer;
      char  indentor;
      Item::Format  items;
   };
   //_2013-02-17_______________________________________________________________/
 public:
   enum Ordering {ASCENDING,DESCENDING};                                         //971214
   contribute_ bool modified;                                                    //060321
         // This is set to true whenever nodes are added or removed, or detached.
         // This can be used by derived classes to update status, recount etc.
         // mutable because this is just a status marker.
 protected:
    contribute_ bool unique_keys; // contribute True if keys must be unique;     //140716_080224
    contribute_ std::string write_delimiter;                                     //171221_141013
 public:
   inline Container(bool _unique_keys=false)                                     //150819_140716
      : modified(false)
      , unique_keys(_unique_keys)
      , write_delimiter("\n")                                                 {} //151013
   //NYIContainer(const Container &from_copy);                                        //170817
      //copy constructor
   inline virtual ~Container()                                                {} //081125
   virtual nat32 clone_from                                                      //170817
      (const Container &from_copy
      ,nat32 include_from_item_index = 0                                         //171117
      ,nat32 count = 0xFFFFFFFF);                                                //171117
   virtual nat32 count()                                                const=0; //991215
   virtual Item* detach(Item *detach_item)                        modification_; //030709
      // Removes the detach element from the list, but does not delete it
      // If detach_element is not in the list or is null, nothing is done.
   virtual bool remove(Item *remove_element);
      // Deletes the node containing remove_element.
      // remove_element will be deleted even if it does not exist in the list.
      // If remove_element is 0 it does nothing.

   virtual Item *take(Item *new_item)                          appropriation_=0;

   // The following should actually be implemented as submissions  171204

   virtual Item *append(Item *new_item)                           appropriation_ { return take(new_item); } //150818
   inline virtual Item * prepend(Item *new_item)                     submission_ { return take(new_item); } //150818_060619
      // Temporarily this is common I need to override this in all classes
      // This should actually return bool (true) if item is taken;
   virtual nat32 prepend_items(Container &take_items)               submission_; //171204
   virtual Item *add_sorted                                                      //970928
      (Item *new_element, Ordering ordering = ASCENDING)         appropriation_; //971211
      // If the derived class doesn't implement sort then the default behaviour is to simply append.
   virtual nat32 transfer_all_from
      (Container &from_container
      ,Item::Filter filter = Item::filter_all)                    modification_; //991122
      // This appends all the items from another Container, the items are removed from the other Container.
      // If filter is specified, only those items matching the filter will be transfered  //040318
      // Returns the number of items transfered

      // transfer_all_from() is deprecated because the from_container has
      // little control in the process.
      // Where as in give_to, this container is modifying itself.
      // The to_container would have the option to take the item it is given.
   /* This is not linking don't know why
   virtual nat32 give_to
      (Container &receiving_container
      ,Item::Filter filter = Item::filter_all)                    modification_;
   */

#ifdef NYI
   virtual Item * insert_before
      (Item *new_element,Item *before_element)                 appropriation_=0;
      // not currently implemented in unidir list
      // virtual Item * add_sorted(Item *new_element);
#endif
   virtual nat32 delete_all(Item::Filter filter = Item::filter_all)          =0;
   virtual Item *pop_first()                                                 =0;
   inline virtual Item *pop_at_head()                    { return pop_first(); } //171204
      // pop_at_head is deprecated rename all used to pop_first()
   virtual Item *pop_last()                                                 = 0; //171204

   virtual Item * find_matching
      (const Item &item_to_match,bool from_beginning = true)              const; //990105
      // This was find_matching  it is now deprecated, and will eventually be removed
      // use instead find_comparable()
   virtual Item * find_comparable                                                //990105
      (const Item &comparable_item_to_match,bool from_beginning = true)   const;

   virtual Item *find_string (const std::string  &search_key,bool case_sensitive=true) const; //140716
   virtual Item *find_wstring(const std::wstring &search_key,bool case_sensitive=true) const; //140716
   virtual Item *find_cstr   (const_ASCIIZ        search_key,bool case_sensitive=true) const; //140716
   virtual Item *find_wstr   (const_UnicodeZ      search_key,bool case_sensitive=true) const; //140716
   virtual Item *find_nat32  (nat32 search_key)                                        const; //150608
      /**<\fn \return the association with the matching key (Case sensitive or case insensitive).
         Returns 0 if not matching association.
      **/
      // These find methods were in Assocation_list
   virtual nat32 remove_all_matching_key_cstr
      (const char *search_key,bool case_sensitive = true)         modification_; //140716
      /**<\fn Remove removes all matching entries from the list
            and deletes the associated data!
         \return the number of matchings and deletions.
      **/

   virtual Item * get_at(nat32 index)                                   const=0; //991216
   virtual bool   delete_at(nat32 index);                                        //991216
      ///< NYI \return bool true if there is an entry at index index is 0 based.
   // The following methods can be used to presume the list is indexed from 1
   virtual Item * get_Nth(nat32 element_num)                              const;
      // Similar to get_at, but element_num is a 1 based index
   virtual bool delete_Nth(nat32 element_num)                     modification_; //100616
   virtual void set_checked(bool i_checked)                       contribution_; //101129 modification_;
      // This is used for Container checked list boxes. It sets the checked state of all items.
   virtual void set_selected(bool i_selected)                     contribution_; //020125 101129 modification_;
      // This is used for Container list boxes. It sets the selected state of all items.
   virtual Iterator *iterator()                                         const=0; //030603
      // Derived classes will create an iterator capable of
      // moving in the various directions.
   virtual bool   is_empty()                                            const=0; //040107
      // returns true if there are no items in the list
   //NYI virtual nat32 write_return_bytecount(std::ostream &strm)  performs_IO_;//111015
   virtual nat32   write(std::ostream &strm)                       performs_IO_;//151002_150728_040108 was void
      // Although unilist modify itself, derived class may perform
      // additional processing and may need to modify themselves.
      // I/O methods should never be const.
      // returns the number of items written
   inline virtual bool set_write_delimiter(char delimiter_)                      //151013
      { write_delimiter = delimiter_; return true; }
      // eventually we should have only write_return_bytecount, returning the number of bytes written
   inline virtual bool set_write_delimiter_cstr(char *delimiter_)                //151013
      { write_delimiter = delimiter_; return true; }
      // eventually we should have only write_return_bytecount, returning the number of bytes written

   virtual nat32 write_with_format
      (std::ostream &strm,const Format &,nat16 indentation_level)  performs_IO_; //150728_130217
      // returns the number of items written

#ifndef _MSC_VER
   // I don't know why VS is not linking write_binary()
   virtual nat32 write_binary(Binary_file_interface &bin_file)     performs_IO_;
      // returns the number of bytes written
#endif

   virtual nat32 string_items
      (std::string  &string_buffer,  char   separator =  '\n')            const; //171225
   virtual nat32 string_items
      (std::wstring &string_buffer, wchar_t separator = L'\n')            const; //171225
      ///< Composes a string representation of the items which is appended to buffer.
      /// The string_buffer is not cleared, it may have previously composed text which is left intact.
      /// (so if there are no items the string buffer would not be changed).
      /// The separator is appended between items (not prepended or appended).
      /// \returns the number of items appended as strings to buffer
      /// which does not necessary include the count of any items previously
      /// appended to the buffer.

 public: // modified accessors
   virtual bool get_modified(bool clear_modified=false)                   const; //060321
      // clear_modified can be use to clear the modified flag so it will start checking for new modifications
   virtual bool set_modified(bool modified)                       contribution_; //060321_070417 was modification_;
 public:
   inline void set_unique_keys(bool unique_keys_)                 contribution_  //140716_081001
      {unique_keys = unique_keys_;}
 protected:
   virtual Item *delete_unappropriatabled(Item *new_item)        appropriation_;
};
//______________________________________________________________________________
#define FOR_EACH_IN(item,type,container,iterator_name)                         \
{  CORN::Container::Iterator *iterator_name = (container).iterator();          \
   for (type *item =  dynamic_cast<type *>(iterator_name->first())             \
       ;item                                                                   \
       ;item =   dynamic_cast<type *>(iterator_name->next()))                  \
   {                                                                           \
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#ifdef __BCPLUSPLUS__
// BC++ currently doesn't have OMP
#define FOR_EACH_IN_PARALLEL(item,type,container,iterator_name)                \
{  CORN::Container::Iterator *iterator_name = (container).iterator();          \
   for (type *item =  dynamic_cast<type *>(iterator_name->first())             \
       ;item                                                                   \
       ;item =   dynamic_cast<type *>(iterator_name->next()))                  \
   {
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#define FOR_EACH_IN_REVERSE_PARALLEL(item,type,container,iterator_name)        \
{  CORN::Container::Iterator *iterator_name = (container).iterator();          \
   for (type *item =  dynamic_cast<type *>(iterator_name->last())              \
       ;item                                                                   \
       ;item =   dynamic_cast<type *>(iterator_name->prev()))                  \
   {
//_2017-05-28__ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#else

#define FOR_EACH_IN_PARALLEL(item,type,container,iterator_name)                \
{  type *parallel_item;                                                        \
   type *item;                                                                 \
   CORN::Container::Iterator *iterator_name = (container).iterator();          \
   _Pragma("omp parallel private(parallel_item)")                              \
   for (parallel_item =  dynamic_cast<type *>(iterator_name->first())          \
       ;parallel_item                                                          \
       ;parallel_item =   dynamic_cast<type *>(iterator_name->next()))         \
   { item = parallel_item;

//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#define FOR_EACH_IN_REVERSE_PARALLEL(item,type,container,iterator_name)        \
{  type *parallel_item;                                                        \
   type *item;                                                                 \
   CORN::Container::Iterator *iterator_name = (container).iterator();          \
   _Pragma("omp parallel private(parallel_item)")                              \
   for (parallel_item =  dynamic_cast<type *>(iterator_name->last())           \
       ;parallel_item                                                          \
       ;parallel_item =   dynamic_cast<type *>(iterator_name->prev()))         \
   { item = parallel_item;
#endif
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#define FOR_EACH(item,type,iterator_name)                                      \
{  CORN::Container::Iterator *iterator_name = iterator();                      \
   for (type *item = dynamic_cast<type *>(iterator_name->first())              \
       ;item ;item = dynamic_cast<type *>(iterator_name->next ()))             \
   {                                                                           \
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#define FIND_FOR_EACH(found_item,item,type,from_beginning,iterator_name)       \
type *found_item = 0;                                                          \
{  CORN::Container::Iterator *iterator_name = iterator();                      \
   for (type *item = dynamic_cast<type *>                                      \
        (from_beginning ? iterator_name->first() : iterator_name->current())   \
       ;!found_item && item;item = dynamic_cast<type *>(iterator_name->next()))\
   {
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#define FIND_FOR_EACH_IN(found_item,item,type,container,from_beginning,iterator_name)   \
type *found_item = 0;                                                          \
{  CORN::Container::Iterator *iterator_name = (container).iterator();          \
   for (type *item = dynamic_cast<type *>                                      \
        (from_beginning?iterator_name->first():iterator_name->current())       \
       ;!found_item && item;item = dynamic_cast<type *>(iterator_name->next()))\
   {
//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
#define FOR_EACH_END(iterator_name)                                            \
   } if (iterator_name) delete iterator_name; iterator_name = 0;               \
}                                                                              \

//______________________________________________________________________________
} // namespace CORN

#endif
// container.h

