#ifndef dBase_datasrcH
#define dBase_datasrcH
/*
  This is a dBase compatible file maintenance library.

  In provides the following features:

  Creating, reading and writing dBase files.

  It doesn't (yet) provide the following:

  Indexing.
  Reorganizing the database file (order of fields).
  Adding additional fields.
  Relational database operations.

  records are numbered starting from 1

  96 Aug 3  Renamed xxx_boolean to xxx_bool
                    xxx_integer to xxx_int

   Data records:

      When a dBase exists, the file is openned and actual fields list is
      loaded from the database header.

      dBase has a maximum limit to the number of characters used in a field name.
      If any variable name for an expected variable value in a Data_record exceeds
      this maximum (15 I think) or contains characters not valid to
      a dBase field name then a unique field name will be composed base on
      the variable name.
      If any field name is composed, an second database file will
      be created having the same name as the main database with _fields appended
      to the filename.  This database will contained two columns
      one column contained the field names used in the database, and one containing
      the full variable name that was expected.  This database can be used by
      a user to know exactly what variables the field names represent.
*/
#include "corn/const.h"

#include <string.h>
// for memset                                                                      090317

#ifndef binfstrmH
#  include "corn/format/binary/binfstrm.h"
#endif
#include "corn/container/bilist.h"
#ifndef search_treeH
#  include "corn/container/search_tree.h"
#endif
#ifndef data_tableH
#  include "corn/data_source/data_table.h"
#endif
#include "corn/format/field.h"

#ifdef __MSDOS__
#include <dir.h>
#define MAX_path_len MAXPATH
#else
#define MAX_path_len 255
#endif

#define dB_character      'C'
#define dB_number         'N'
#define dB_float          'F'
#define dB_logical        'L'
// 1 byte
#define dB_memo           'M'
// 10 bytes
#define dB_date           'D'
// 8 bytes

// The following are Roger Nelson's data types

#define rB_CORN_date      'j'
// 4 bytes

#define rB_int16      'i'
// 2 bytes

#define rB_float32        'f'
// 4 bytes
#define rB_float64        'd'
// 8 bytes

#define rB_nat8          '1'
#define rB_nat16         '2'
#define rB_nat32         '4'

#include "corn/const.h"

namespace CORN {
// Forward declarations:
//170928class Text_list;
class Data_source_dBase;
class Binary_file_interface;

/*
The data records are layed out as follows:

     1. Data records are preceeded by one byte that is a space (20H) if the
        record is not deleted and an asterisk (2AH) if it is deleted.

     2. Data fields are packed into records with  no  field separators or
	record terminators.

     3. Data types are stored in ASCII format as follows:

     DATA TYPE      DATA RECORD STORAGE
     ---------      --------------------------------------------
     Character      (ASCII characters)
     Numeric        - . 0 1 2 3 4 5 6 7 8 9
     Logical        ? Y y N n T t F f  (? when not initialized)
     Memo           (10 digits representing a .DBT block number)
     Date           (8 digits in YYYYMMDD format, such as
          19840704 for July 4, 1984)
*/
//______________________________________________________________________________
class Data_source_dBase
: public Data_table
{
 public:
   Binary_file_interface *binary_file;   // maybe should be mutable  //070622
 private: // Classes
   //___________________________________________________________________________
   class Header
   {
    public:                   // Byte
      nat8 version;           // 0 (03H without a .DBT file) (83H with a .DBT file)
      nat8 update_year;       // 1 date of last update
      nat8 update_month;      // 2
      nat8 update_dom;        // 3
      int32 num_records;      // 4-7   number of records in data file (not sure if unsigned will work
      nat16 header_length;    // 8-9   length of header structure
                              // This info, the /r and all field info
      nat16  record_length; // length of the record
                              // includes delete marker
      nat16 reserved_bytes_12_13; // Byte12-13Reserved and zero filled in all version of dBase III,IV, 5
      nat8 incomplete_transaction_flag; // Byte14 unused in dBase III
               // 00h Transaction ended (or rolled back)
               // 01h Transaction started
      nat8 encryption_flag;  // Byte15 Introduced in dBase IV unused in dBaseII (0)
      char /* gcc complains about nat8*/ reserved_16_27[12]; // Bytes16-27 Reserved for multi user processing
      nat8 production_MDX_flag; // byte 28 MDX files introduced in dBase IV
               // 00h No MDX file (Currently this class always writes 0 since we don't work with MDX file
               // 01h production MDX file exists for this table
      nat8 lanuage_driver_ID;   // byte 29 introduced in dBase IV (0 for dBaseIII)
      nat16 reserved_30_31;      // bytes30-31 Rserved 0 filled all versions
/*
00h (in dBase III)
01h DOS USA             CP 437
02h DOS Multilingual      CP 850
03h Windows ANSI         CP 1252
04h Standard Macintosh
64h EE MS-DOS            CP 852
65h Noridic MS-DOS      CP 865
66h Russian MS-DOS      CP 866
67h Icelandis MS-DOS
68h Kamenicky (Czeck) MS-DOS
69h Mazovia (Polish) MS-DOS
6Ah Greek MS-DOS (437G)
6Bh Turkish MS-DOS
96h Russian Mackintosh
97h Eastern European Macintosh
98h Greek Macintosh
C8h Windows EE            CP 1250
C9h Russian Windows
CAh Turkish Windows
CBh Greek Windows
*/
    public:
      Header();
      // This constructor is for creating a header from scratch
      // Or for a header whose data will be filled in from a file later.
      Header(const Header &to_copy);                                             //970802
      //This is a copy constructor.

      // field descriptor records follow
      // byte  0Dh terminates header record structure.
      bool read (Binary_file_interface &f);
      void write(Binary_file_interface &f);
      inline virtual nat32 get_record_count()                              const //971019
         { return num_records;}
   };
   //__2008-08-04__1997-07-20_____________________________________class_Header_/
   class Field
   : public implements_ CORN::Item                                               //170928
   , public implements_ CORN::Field                                              //170928
   {  friend class Data_source_dBase;                                            //990615
    protected:                // byte(s)
      char   name[12];          // 0-10   field name in ASCII zero-filled now stored in key. byte 11 must alway be 0, it is now written to the dbase file //980901
      char type;              // 11    (C N L D or M) (F add dBaseIV) (B G add dBase5)
      int32 data_address;     // 12-15   field data address (set in memory) (for dBase III only, all other versions 0)
                              //   12-13 in FOX Pro is the offset of field from beginning of record.
      nat8 length;            // 16      field length in binary (note tha maximum field lenth is 255)
      nat8 decimals;          // 17      field decimal count in binary (always less than 15)
      nat16 reserved_18_19;   // 18-19 Reserved for multi-user dBase III+ on a LAN.                                                                //080804
                              // 18 in FoxPro: 01h System column,  02h Column can store NULL values, 03h Binary column (for CHAR and MEMO)         //080804
      nat8  work_area_ID;     //   20  01h is all dBaseIII files  (0 in all others                                                                   //080804
      nat16 reserved_21_22;   // 21-22 Reserved for multi-user dBase III+ on a LAN. (unused and 0 for all other versions)                          //080804
      nat8  set_fields_flag;  // 23    dBaseIII only. Probably can be 0 for all versions                                                            //080804
      char /* gcc complains about nat8*/   reserved_24_30[7];  // 24-30                                                                            //080804
      nat8  MDX_field_flag;   // 31      dBaseIV and dBase5                                                                                          //080804
               // 01h if field has and index tax in the MDX file, 00h if not                                                                          //080804
    private:
         contribute_ char Field_item_name_return[13];  // not written to file.   //091031
    public:
       Field
          (const char *new_name  // field name in ASCII zero-filled
          ,char new_type         // (C N L D or M)
          ,nat8 new_length=1     // field length in binary
          ,nat8 new_decimals=0); // field decimal count in binary
       Field(Data_source_dBase &f);  //  Construct from file info
       Field(const Field &to_copy);                                              //970802
       // Copy constructor
       void read_from(Data_source_dBase &f);   // read field structure from dBase header
       void write_to(Data_source_dBase &f);  // write field structure from dBase header
    public: // accessors
      inline nat8 get_length()                          const { return length; } //990615
      virtual bool is_key_string(const std::string &key)           affirmation_; //180820;
      virtual const char *get_name()                                      const;

      /*180820  was probably only used for find_cstr now using is_key

       virtual const char *get_key()                                      const; //070525
    */       
    };
    //_1997-07-20__________________________________________________class Field_/
    public: class Field_item : public Data_source_dBase::Field                   //170928
    {       // public so Arccs/Watershed can scan fields
     public:
       nat16 pos;  // byte position in the record                                //010104
       bool modified;      // if the field buffer data has been modified
     public:
       Field_item(Data_source_dBase &f);
       Field_item
          (const char *name_          // field name in ASCII zero-filled
          ,char        type_              // (C N L D or M)
          ,nat8        length_    //= 1   // field length in binary
          ,nat8        decimals_  //= 0
          ,nat16       pos_                                                      //010104
          ); // field decimal count in binary
       Field_item(Field_item &to_copy);                                          //970802
       // Copy constructor
       virtual ~Field_item();
     private:
         inline virtual const std::string &append_to_string(std::string &buffer) const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format
    };
    //_1997-07-20__________________________________________________class Field_/
 private: // Current record status
    long current_record;          // The current record number
    bool current_record_deleted;  // returns true if record is marked as deleted
    Header header;
 private: // Database status
    bool deleted_shown;           // true is deleted records are visible
    bool modified;                // 1 if header format has been modified
    bool initialized;                                                            //000119
    bool deleted_modified;
  // used to get info on the field being get or set
  // offset in the record is returned
 private:  // actually private but need to imp
    nat16 next_field_for_write_pos;   // contribute to remember the next field position when using expect_field_for_write.  //090131
    Bidirectional_list /*180101 Association_list*/ expected_fields;                                            //090131
 public: // Actual fields is public because we allow this list to be used by data aware controls
    Bidirectional_list /*180101 Association_list*/ actual_fields;  // list of  Field_item                      //970722
 public: // Current record status methods
    bool is_record_modified()                                      affirmation_; //170518
    inline bool is_record_deleted() affirmation_{return current_record_deleted;} //170518
    inline nat32 get_record_number()             const { return current_record;}
public:
    Field_item *lookup_field(const char *field_name);
    // Variable name is any valid variable=value variable name

    virtual nat8 get_field_type(const char *field_name);                         //021111
    // returns the filed type corresponding to VV_entry types
    Data_source_dBase(const char *i_filename                                     //001002
       ,std::ios_base::openmode _openmode /* = (std::ios_base::in | std::ios_base::out)*/ //130123 111026
       ,Indexer *optional_indexer=0);                                            //150731
    // This constructor is for openning a file (either an existing file or create a new one).
    Data_source_dBase(const char *i_filename                                     //001002
       ,const Data_source_dBase &from_copy);  // For an existing file
    // This copy constructor is to create a new file having the same structure as the one to copy.
    // Only the fields are copied, not data records.
   virtual ~Data_source_dBase();
   virtual bool initialize()                                         stream_IO_; //080718
   virtual bool finalize()                                           stream_IO_; //979720
 public: // Data_source class private overrides
   virtual bool create(Data_record &from_record);                                //010103
      // When we use get() and we have not yet created the database
      // We need to create the list of actual fields based on the from_record
 public: // Data_source class public overrides
   virtual const char *label_string(std::string &buffer)                  const; //020125
      // This returns a text label that could be used to identify
      // The data source being edited.
      // It is left to the derived data source class how this text is formatted.
      // For VV_file we simply use the fully qualified filename.
      // For dBase we could use the filename and the record number  C:\path\file.dbf#123
      // The following are file record option
   inline void show_deleted(bool show = true)                      modification_
      { deleted_shown = show; }
     // The following moves the record pointer to the beginning of the
     // specified record, reads the record, and repositions the cursor
     // to the beginning of the record for writing.
     // These return true if record exists.
 public: // Record positioning methods
   virtual bool goto_BOF();
      // This method goes to the beginning of the file and reads the first record into the record buffer.
      // The file pointer is positioned back to the beginning of the record (BOF).
      // Returns true if the operation succeeded otherwise false
   virtual bool goto_EOF();
   virtual bool goto_record(int32 record_number);
      // If the specified record number is within the bounds of the database
      // The current_record number is set to record number and returns true.
      // Else
      // Returns true if the record number is within the number of records
      // currently existing in the file
      // Returns false if the record_number > number of records
      // (This is not an error the file will be extended
      // when the next record that is commited for appending will be written here)
      // Returns false if record_number <= 0
   virtual bool goto_next(int32 skip_records = 1);
      // This method advances the file pointer to the next record and reads the record.
      // The file pointer is positioned back to the beginning of the record.
      // Returns true if the operation succeeded otherwise false (I.e. currently at the eof).
   virtual bool goto_prev(int32 skip_records = 1);
   nat32 new_record(int16 num_new_records = 1);
      // Add the specified number of new records at the end of the file
      // The default is to add 1 record
      // returns the record position (record_number) where to write
      // this will be where the end of the file is before the call to new record
      // so if num_new_records > 1 the next record will be
      // written in the space of the first created record.
  virtual nat32 delete_record();     // marks the current record as deleted
  void undelete_record();   // restores the current record
    inline bool *get_deleted_pointer()        { return &current_record_deleted;}
 public: // Data table overrides
   inline virtual bool  goto_first()                      { return goto_BOF(); }  //021111
   inline virtual bool  goto_index(nat32 index) {return goto_record(index + 1);} //021111
      // index is 0 based
   inline virtual bool  goto_last()                       { return goto_EOF(); } //021111
   inline virtual nat32 get_current_index()     {return get_record_number() -1;} //021111
      // rename 0_based is redundendend because index is always 0-based

      // returns the index value for the table's current position.
      // For database tables this is the record number
      // For memory tables, this is the memory location or object pointer);
   virtual bool reset();
 public: // Data_source method overrides
   virtual Generic_data_record *render_generic_data_record()       performs_IO_; //160831_050928
      // deprecated, use render_data_record()
   //virtual Data_record render_data_record()                                const;

      // This should be renamed to render_generic_data_record()


      // Normally users of a datasource will define a class derived from
      // Data_record and override the expect_structure() method
      // for known attributes in the table.
      // However, some times it is necessary to work with Data sources where
      // the structure is not known up front (I.e. Tables that are from other
      // sources or whose structure may be variable).
      // This method can be called to provide a Data_record that generally
      // matches the attributes of the Data source's data records.
      // This method returns 0 if the structure of the data records used in
      // the datasource cannot be determined.
      // (I.e. Variable value files cannot idenfity the structure because
      // attribute type information is not stored in the file).
      // Derived classes can override this method if the structure of
      // the data records is stored in the data source (I.e. database tables).
   virtual bool get(Data_record &data_rec);                                      //010103
      /**< This reads the data record from the current record position in the database
      (I.e. current record in the database) storing the values in provided Data_record structure.
               -  Returns false if the database is not in a state where is can read any data.
               -  Returns false if the database could be read, but there were not maching entries (fields).
               -  Returns true if any record entries could be read from the fields at the current position.
               -  The caller can examine each Data_record entry to determine if it was encountered in the data base.

               Reads the current record data into a buffer
               then copy the data into the Record_data structure provided by
               the caller for field names corresponding to record entries' names.

               The provided Data_record structure may expect fields entries that don't
               actually occur or are not 'encountered' in the database.
               These entries will be marked as not encountered.

               The database format may have fields/columns that are not expected in
               the Data_record.  These fields will not be loaded.
      **/
   virtual bool get_next(Data_record &data_rec);                                 //020914
      // A where clause index more than one record.
      // In this case, use get() to fetch the first record
      // and repeat calling get_next() to fetch remaining records.
      // get_next will return false if there were no
      // additional records returned by the SELECT WHERE statement to fetch.
      // Note that this abstract class ALWAYS returns false because this abstract class does not
      // actually fetch the data, it only sets up the the structure.
      // Derived classes must return true unless the data could not be fetched.
 protected:
   virtual bool set_data(Data_record &data_rec,bool append);                     //150503_050705
      // This writes data from data_rec to this data source.
      // Classes derived from Data_record may provide information such
      // as the position of the record in the data file an the Data_source
      // may then need to position the file pointer before writing the record.
      // In classes such as VV_file, a Data_record constitutes all the data in
      // a file, consequently the data can be written out to the file.
      // Returns true if the record could be written.
      // Returns true if there was a problem.
      // This abstract method must be provided by a derived class.
 public: // Data_table overrides
   virtual nat32 get_record_count()  ; // cannot be const because we may need to initialize 971019
   virtual nat32 append(Data_record &data_rec);                                  //031106
      /**< This creates a new record at the end of the table and sets data_rec.
      \return the record index of the new record that was appended.
      **/
 protected:
   bool expect_field_for_write                                                   //091030
         (const char *new_name                // field name in ASCII zero-filled
         ,char new_type                 // (C N L D or M)
         ,nat8 new_length=1    // field length in binary
         ,nat8 new_decimals=0); // field decimal count in binary
      // Occasionally, in derived classes, when writing to a table,
      // it may be necessary to declare all the fields that may occur up front
      // this is because the first Data_record written might not have
      // all the entries that may ultimately occur in the file.
      // (This happened with the CropSyst Avg_prob_map_tallier
      //  so it was necessary to set up all the selected variable tallies before writing the records)
      // This method should be called before the table is initialized
      // (before writing or reading or positioning the record pointer)
      // otherwise no additional fields can be added.
      // This function has no meaning when reading files (since the database format has already been set).
      // \return false if the file has already been initialized
 private:
   inline bool is_initialized()                    const { return initialized; } //041210
   bool create_header();                                                         //970720
   bool creating();                                                              //010104
   virtual void write_fields();                                                  //970720
   void read_record_buffers_check_obsolete();                                    //970720
   bool position_record_pointer(long record_num);                                //970803
      // record_num must be long
   nat16 get_pos(const std::string &field_name)                           const; //040909
};
//______________________________________________________________________________

// The following are for index

// This class is a dBase file with a simple index

//______________________________________________________________________________
class Dynamic_indexed_dBase_data_source : public Data_source_dBase
{protected: // contributes
   contribute_ bool index_built;                                                 //000119
   contribute_ bool where_mode;                                                  //021111
   contribute_ bool where_found;                                                 //021111
 public:                                                                         //030224
    std::string     index_field_name;                                            //040909
 public:
   Dynamic_indexed_dBase_data_source                                             //020125
      (const char *filename
      ,const char *i_index_field_name
      ,std::ios_base::openmode _openmode);                                       //111026
      // (std::ios_base::in | std::ios_base::out)
   inline virtual ~Dynamic_indexed_dBase_data_source() {}                        //081125
   virtual bool goto_BOF();
   virtual void build_index()                                     stream_IO_= 0;
};
//_2000-01-12___________________________________________________________________
class Dynamic_string_indexed_dBase_data_source
: public Dynamic_indexed_dBase_data_source
{  contribute_ std::string last_where_value;                                     //040909
 public:  // made public so caller can scan the indexed items with out having to read the database himself
   contribute_ Association_search_tree indicies;
public:
   //___________________________________________________________________________
   class Index_item
   : public Item                                                                 //170928
   {public:
      std::string rec_key_value;                                                 //040909
      nat32       rec_num;
    public:
      Index_item(modifiable_ Dynamic_indexed_dBase_data_source &file,const char *field_name);
      virtual bool is_key_string(const std::string &key)           affirmation_; //180820
      

/*180820  was probably only used for find_cstr now using is_key

      virtual const char *get_key() const;                                       //030119
*/      
      inline virtual const std::string &append_to_string(std::string &buffer) const { return buffer; }
          //180813 not currently used  may want to write in a preferred/specified format

   };
   //___________________________________________________________________________
public:
   Dynamic_string_indexed_dBase_data_source
      (const char *i_filename                                                    //000113
      ,const char *i_index_field_name
      ,std::ios_base::openmode _openmode);                                       //111026
      // (std::ios_base::in | std::ios_base::out)
   inline virtual ~Dynamic_string_indexed_dBase_data_source()                 {} //081125
   nat32 find_record
      (const char *search_key,bool from_first_record = true)         stream_IO_;
   // returns 0 if not currently in the database otherwise returns the existing record number
   virtual bool get_next(Data_record &data_rec);                                 //020914
   virtual void where_cstr(const char *attribute, const char *value) modification_;
   virtual void where_long(const char *attribute, const long  value) modification_;
   virtual void build_index()                                        stream_IO_;
};
//_2000-01-12____________________________________________________________________________
class Dynamic_string_int32_indexed_dBase_data_source
: public Dynamic_indexed_dBase_data_source
{   // This is for a two key index where the first index is a string and the second is an integer
 private:
    std::string secondary_field_name;
    contribute_ std::string last_where_value;
 protected:
    contribute_ Binary_tree indicies;
 public:
   //___________________________________________________________________________
   class Index_item : public Item
   {public:
       std::string rec_key1_string_value;
       int32       rec_key2_int_value;
       nat32      rec_num;
    public:
       Index_item
         (modifiable_ Dynamic_indexed_dBase_data_source &file
         ,const char *primary_field_name,const char *secondary_field_name);
       // Constructor for comparable search
       Index_item(const std::string &_rec_key1_string_value,int32 _rec_key2_int_value);
       virtual int  compare(const Item &) const ;
       inline virtual const std::string &append_to_string(std::string &buffer) const
         { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format

   };
   //___________________________________________________________________________
 public:
   Dynamic_string_int32_indexed_dBase_data_source
      (const char *i_filename
      ,const char *i_primary_field_name
      ,const char *i_secondary_field_name
      ,std::ios_base::openmode _openmode);                                       //111026
    inline virtual ~Dynamic_string_int32_indexed_dBase_data_source()          {} //081125
    bool find_record
      (const char *search_key1,int32 search_key2
      ,bool from_first_record = true)                                stream_IO_;
    virtual void build_index()                                       stream_IO_;
};
//_2005-11-01____________________________________________________________________________
class Dynamic_int32_indexed_dBase_data_source : public Dynamic_indexed_dBase_data_source
{  contribute_ Bidirectional_list indicies;
   contribute_ long last_where_value;                                            //020914
 public:
   //___________________________________________________________________________
   class Index_item : public Item
   {
    public:
      int32 rec_key_value;                                                       //980207
      nat32 rec_num;
    public:
      Index_item(modifiable_ Dynamic_indexed_dBase_data_source &file,const char *field_name);
      inline virtual const std::string &append_to_string
         (std::string &buffer)                          const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format

   };
   //___________________________________________________________________________
 public:
    Dynamic_int32_indexed_dBase_data_source
       (const char *_filename                                                    //020125
       ,const char *_index_field_name
       ,std::ios_base::openmode _openmode);                                      //111026
       // (std::ios_base::in | std::ios_base::out)
    inline virtual ~Dynamic_int32_indexed_dBase_data_source()                 {} //081125_
    bool find_record(int32 search_key,bool from_first_record = true) stream_IO_;
    virtual bool get_next(Data_record &data_rec);                                //020914
    virtual void where_long(const char *attribute, const long value)  modification_;
    virtual void where_cstr(const char *attribute, const char *value) modification_;
    virtual void where2_long
       (const char *attribute1, const long value1
       ,const char *attribute2, const long value2)                modification_;
    virtual void build_index()                                       stream_IO_;
};
//_2000-01-12_____________________________________________________________________________

class Dynamic_int32_int32_indexed_dBase_data_source
: public Dynamic_int32_indexed_dBase_data_source
{   // This is for a two key index where both index keys are integers
 private:
    std::string secondary_field_name;
    contribute_ int32 last_where_value;
 protected:
    contribute_ Binary_tree indicies;
 public:
   //___________________________________________________________________________
   class Index_item
   : public Item
   {public:
      int32 rec_key1_int_value;
      int32 rec_key2_int_value;
      nat32 rec_num;
    public:
       Index_item(modifiable_ Dynamic_indexed_dBase_data_source &file
         ,const char *primary_field_name,const char *secondary_field_name);
       // Constructor for comparable search
       Index_item(int32 _rec_key1_int_value,int32 _rec_key2_int_value);
      virtual int compare(const Item &) const ;
    private:
      inline virtual const std::string &append_to_string
         (std::string &buffer)                          const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format
   };
   //___________________________________________________________________________
 public:
   Dynamic_int32_int32_indexed_dBase_data_source
      (const char *i_filename
      ,const char *i_primary_field_name
      ,const char *i_secondary_field_name
      ,std::ios_base::openmode _openmode);
    inline virtual ~Dynamic_int32_int32_indexed_dBase_data_source()          {}
    bool find_record
      (int32 search_key1,int32 search_key2
      ,bool from_first_record = true)                                stream_IO_;
    virtual void build_index()                                       stream_IO_;
};
//_2014-11-11____________________________________________________________________________
} // namespace CORN

#endif
// dbase_datasrc.h

