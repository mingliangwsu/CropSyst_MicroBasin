#ifndef markerH
#define markerH

/* UED markers are UED records the delinate sections of the UED database file
   The BOF marker is always the first record of the file.
   There will always be a BOF record.

   The EOF marker can be omitted but if present denotes the end of a database
   Usually the end of the file denotes the end of a database so the EOF marker
   isn't needed.  But the EOF marker can be used to truncate a database.
*/
#include <UED/library/record.h>
//______________________________________________________________________________
namespace UED {
class Marker_record : public Record_base                                         //971207
{public:
   inline Marker_record
      (CORN::Record_code type_code)                                              //990107
      : Record_base(type_code)
      {}
   /* This shouldn't be needed because not really extending the type
   inline Marker_record
      (const &Marker_record copy_from)                                              //990107
      : Record_base(type_code)
      {}
   inline Marker_record *clone()                                           const { return new Marker_record(*this); };
   */
   inline virtual nat32 compute_record_body_size()                         const { return 0;} //001008
};
//_2007-07-18___________________________________________________Marker_record__/
class Marker_BOF_record : public Marker_record
{nat16 database_version;
 public:
   inline Marker_BOF_record(nat16 _version = UED_VERSION_CODE)
      : Marker_record((CORN::Record_code)(UED_marker_BOF))
      , database_version(_version)
      {}
   inline virtual nat32 compute_record_body_size()                         const //001008
      {return sizeof(nat16);}
   // Returns the size of the record body (not including the header).
   virtual bool read_body (CORN::Binary_file_interface   &parent_database);      //971103
   virtual void write_body(CORN::Binary_file_interface   &parent_database);      //971103
};
//_1997-12-07___________________________________________________________________
} // namespace UED
#endif
//marker

