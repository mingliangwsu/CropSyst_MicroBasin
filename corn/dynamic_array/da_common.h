#ifndef da_commonH
#define da_commonH
/*heck needed
#ifdef __BCPLUSPLUS__
#include <values.h>
#endif
*/
#ifndef no_nsH
#  include <corn/no_ns.h>
#endif
#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#ifndef constH
#   include <corn/const.h>
#endif
/*980203  This class is a dynamic array base class
          It allows the array to be automatically resized to accomodate
          larger indicies.
*/

/*001206_*/ namespace CORN {
/*_______*/
/*_______*/ class Dynamic_array_common
/*_______*/ {
/*091217_*/ public:    
/*091217_*/    enum Ordering {UNORDERED,ASCENDING,DESCENDING};
/*_______*/ protected: // adjuncts
/*010531_*/    uint32   current_size_plus_overage;
/*_______*/       // This is the size (number of elements) of the current array.
/*_______*/       // It may be larger than the actual number of elements in the array.
/*010531_*/    uint32   resize_overage;
/*_______*/       // When the array is dynamically resized, the new array may be
/*_______*/       // allocated by this much more with the expectation that more elements
/*_______*/       // will be added. This is used to help reduce that number of
/*_______*/       // memory allocation and copying operations needed when a new
/*_______*/       // array needs to be allocated to accomodate more numbers.
/*000707_*/    bool     empty_list;
/*_010531*/    mutable int32    terminal_index;      // This is the current highest index to the array. (-1 denotes empty list)
/*_980310*/    mutable bool     resized;        // set to true if the array is actually resized
/*_981123*/ protected:  // contributes
/*_______*/    mutable bool     changed;  // set to true if the data set changes
/*_______*/       // this can be used by derive classes to determine when to refresh tallies etc.
/*091217_*/    mutable Ordering order;
/*_______*/ public:
/*_010531*/    inline uint32 get_terminal_index()    const { return terminal_index;};
/* 980318*/           virtual bool   good()             const = 0; // { return array != 0; };
/*_010531*/    inline uint32 get_current_size() const { return current_size_plus_overage; };
/*_990427*/    inline bool   was_resized()      const { return resized; };
/*000707_*/    inline bool   is_empty()         const { return empty_list; };
/*_______*/ public:
/*_______*/    Dynamic_array_common
/*990415_*/       (uint32 initial_size          // This is the initial allocation space
/*_______*/       ,uint32 i_resize_overage = 10);   // This is the overage to give on reallocation
/*000225_*/    Dynamic_array_common(const Dynamic_array_common &to_copy);
/*_______*/ public:
/*_______*/    virtual void reallocate_array(uint32 new_bloated_size) const = 0;
/*_______*/    void if_necessary_resize_for(uint32 index);
/*_______*/    void resize(nat32 new_size);
/*m980305*/    uint32 get_count() const;
/*m980310*/    virtual void clear();
/*040123_*/       // virtual because Statistical dataset needs to reset also
/*_______*/ public:  // The following are pure
/*980721_*/    virtual void remove(uint32 at_index) = 0;
/*_______*/       // This removes the entry at the specified index.
/*_______*/       // all following array elements are moved down one cell and the ?max_index? is decremented
/*000831*/     inline void set_resize_overage(uint32 new_resize_overage) { resize_overage = new_resize_overage;  };
/*_______*/ public:  // The following methods are usually provided in derived classes
/*100119_*/    inline virtual void require_order(Ordering required_order)    contribution_ { order = required_order; };
/*_______*/    inline virtual void sort(Ordering ordering = ASCENDING /*091217 bool ascending = true*/)   {};
/*_______*/       // Append adds the specified value to the end of the data set.
/*_______*/ };

/*001106*/  }; // namespace CORN
#endif

