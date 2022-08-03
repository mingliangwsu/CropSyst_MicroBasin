#ifndef JSONH
#define JSONH
#include <fstream>
#include "corn/const.h"
//180105 #include "corn/container/association.h"
#define JSON_USES_DATAREC
#ifdef JSON_USES_DATAREC
#include "corn/data_source/datarec.h"
#endif
namespace CORN {
namespace JSON {
class Object;
//______________________________________________________________________________
interface_ Structure   // this is actually abstract, not an interface
: public extends_ CORN::Item 
{protected:
   std::string key;
 public:
   inline Structure(const std::string &_key)
      : CORN::Item() //170105 Association()
      , key(_key)
      {}
   inline virtual ~Structure() {}
   virtual std::istream &read_stream (std::istream &data_stream)            = 0;
   virtual std::ostream &write_stream(std::ostream &data_stream)            = 0; //130217
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return key == key; }

/*180820  was probably only used for find_cstr now using is_key
   
   inline virtual const char *get_key()            const { return key.c_str(); }
*/   
   inline virtual bool commit()                                 { return false;}
      // Derived classes should implement commit item if they do anything
      // with the data.
      // This default will cause the data to be ignored as an unexpected section.
};
//______________________________________________________________________________
class Object
: public extends_ Structure
#ifdef JSON_USES_DATAREC
, public extends_ CORN::Data_record
#endif
{public:
//   bool quote_values;                                                            //130217
   //___________________________________________________________________________
   class Array
   : public extends_ Structure
   {public :
      CORN::Bidirectional_list /*180101 Association_list*/ items;
         // Storing the read substructure is optional. Derived class may prefer
         // to consume the data as it is encountered (commited)
    public:
      inline Array(const std::string &_key)
         : Structure(_key)
         , items()
         {}
      virtual std::istream &read_stream(std::istream &data_stream);
      virtual std::ostream &write_stream(std::ostream &data_stream);             //130217
      inline virtual Object *render_item()                            rendition_
         { return 0; /*temp disabled new Object("");*/ }
         // Derived classes should reimplement this method
            // I am not sure if array items are always objects,
            // or they might be scalar values
      virtual Object *commit_item(Object *item);
         // If derived classes immediately consume read JSON text
         // override commit_item and process the read data,
         // and it is not necessary to call this commit_item method.
         // If derived classes want to keep the substructures in memory,
         // they will usually overide commit_item() and use a specialized
         // data structure.
         // If the data is not going to be processed immediately
         // I.e. the the array will first be read it it entirety
         // to be process later this default Object::Array::commit_item()
         // simply load the basic structure into the 'items' list.
      inline virtual bool commit() { return false; } ;
//      virtual const Format *get_format()                                   const;//130217
   };
   //___________________________________________________________________________
   inline Object(const std::string &_key)
      : Structure(_key)
      #ifdef JSON_USES_DATAREC
      , CORN::Data_record(_key.c_str())
      #endif
      {}
      #ifdef JSON_USES_DATAREC
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return key == get_primary_section_name(); }

/*180820  was probably only used for find_cstr now using is_key
      
      inline virtual const char *get_key()                                 const
         { return get_primary_section_name(); }
*/         
      #endif
   //___________________________________________________________________________
 public:
   bool read_string(const std::string &data);
   bool write_string(std::string &data);
   virtual std::istream &read_stream(std::istream &data_stream);
   virtual std::ostream &write_stream(std::ostream &data_stream);
 protected:
   const std::string &read_key(std::istream &data_stream,std::string &key)const;
   bool read_colon(std::istream &data_stream)                             const;
   const std::string &read_quoted_string
      (std::istream &data_stream,std::string &buffer)                     const;
   bool read_and_set_value
      (std::istream &data_stream
      ,const std::string &key)                                     assignation_;
   virtual Structure *provide_substructure(const std::string &key)   provision_
      { return 0; }

      // Currently we are assuming all encountered variables have defined structure in derived classes.
      // but we should provide for arbitrary undefined structures.
      // That we either through away or (optionally) store.
};
//_2012-08-31___________________________________________________________________
} // namespace JSON
} // namespace CORN
#endif

