#ifndef associationH
#define associationH
#ifndef bi_listH
#  include "corn/container/bilist.h"
#endif
namespace CORN {
//______________________________________________________________________________
interface_ Association : public Item
{public:
   Association();                                                                //980207
   virtual ~Association();                                                       //081125
   //170424 virtual const char *label_cstr(char *buffer)                const; //970720
   virtual const char *label_string(std::string &buffer)                  const; //170424
      // For some derived classes, label should be overridden
   //150211 moved to Item inline virtual bool is_case_sensitive()                                 const { return false; } //051101
      // Derived classes may override if compare in find() should be are case sensitive.
};
//_1998-02-06___________________________________________________________________
class Association_list : public Bidirectional_list
{
 public:
   Association_list(bool _unique_keys = false);
   inline virtual ~Association_list()                                         {} //081125
/*171015 obsolete  bilist and container now already checks for unique key
 public: // Override attachments to disallow unique keys
   virtual Item * append(Item *new_element)                       modification_; //080224
   virtual Item * prepend(Item *new_element)                      modification_; //080224
*/
};
//_1998-08-06________________________________________________Association_list__/
class Alias : public Item // Association
{
   char *alias;                                                                  //020125
   char *actual;                                                                 //020125
 public:
   Alias(const char *i_actual,const char *i_alias);
   virtual ~Alias();                                                             //030509
   inline virtual const char *get_key()                   const { return alias;} //030117
   inline virtual const char *get_actual()                const { return actual;}//030117
};
//_2001-11-09___________________________________________________________Alias__/
class Alias_association_list : public Association_list
{
   Association_list aliases;
 public:
   inline Alias_association_list(bool _unique_keys = false) // 080224 eventually make this true
      : Association_list(_unique_keys)
      ,aliases()
      {}
   inline virtual ~Alias_association_list() {}                                   //081125
   virtual Association *find_cstr
      (const char *search_key,bool case_sensitive = true)                  const;
      /**<\fn Returns the association with the matching key (Case sensitive or case insensitive).
         \returns 0 if not matching association.
      */

   void alias(const char *actual_variable                                        //011207
             ,const char *alias_variable);
};
//_2001-12-09__________________________________________Alias_association_list__/
} // namespace CORN

#endif

