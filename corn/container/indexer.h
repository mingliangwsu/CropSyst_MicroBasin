#ifndef indexerH
#define indexerH
/*
   This abstract class
   This class is used by table data sources
*/
#include "corn/primitive.h"

namespace CORN {
#define     CORN_MAX_KEYS 10
//______________________________________________________________________________
//150731 class Indexer_abstract
interface_ Indexer                                                               //150731
{
   contribute_ bool  keys_unique;      // Status indicator set to false if the keys were found to not be unique
   contribute_ bool  built;            // set to true when the datasource has built the index
public:
   inline Indexer() //150731 Indexer_abstract()
      : keys_unique(true)
      , built(false)
      {}
   virtual const char *get_key_name(nat8 key_number)                       const = 0;
   /**<
   This returns the name of the index key (1 is the primary index)
   key_index must not exceed the value returned by get_key_count() otherwise 0 should be returned.
   **/
   virtual nat8       get_key_count()                                      const = 0;
   /**<
   \return he number of keys used by the index.
   I.e. 1 if there is only a primary key, 2 if also a secondary key etc..
   **/
//    virtual bool        set(nat32 position,const char **attribute_values) = 0;
   /**<
   This is used when building the index.
   This identifies the position of the data
   Position may be any index value.
   I.e. for database tables this may be the record number
   for binary files it may be the file position
   for memory data, this may be the address.
   Attribute values is an array of null terminated character arrays
   storing the record's data values for the respective key (in canonical order)
   The attribute values are currently passed as text representations
   I.e. if the primary key is an integer value 123 and the secondary key is a bool value true
   The values will be passed as  {"123","true"}
   Strings are passes because databases (i.e.) dBase and Oracle often store
   values as string representations and the quick index read
   should not need to do conversions.
   Derived classes will want to store the key values in the desired data types.
   Returns true if the attribute value(s) were unique
   Returns false if the keys were duplicate (or some other problem was encountered).

   This is used when and existing data source is opened and indexed.
   **/
// In the following mode the position and key values are set as the data record is processed
// This allows the datasource to simply process record as it is encountered.
// This is used when records are added to the data source with the set() or append() value
   virtual bool know_position(nat32 position)                         cognition_ = 0;
   virtual bool know_value
      (const std::string &value                                                  //150730
      //150730 const char *value
      ,  const char *field , const char *section )                    cognition_ = 0;
   /**<
   This is called for all fields, if the field (or section) is not used
   Note that the section is optional, not all data source have sections
   and not all indices may use them.
   Returns true if the field is a key
   otherwise false (false does not me failure).
   **/
   virtual bool commit()= 0;
   virtual nat8 get_key_sequence(const char *field, const char *section)   const = 0;
   /**<
   \return a 1 based key number sequence of the named field.
   return 0 if field is not a key_field
   Note that the section is optional, not all data source have sections
   and not all indices may use them.
   **/
   inline virtual bool set_built() { return built = true;}
   /**<
   Derived classes should provide a find() method to return the position matching a set of attribute values.
   **/
};
//______________________________________________________________________________
} // namespace CORN
#endif

