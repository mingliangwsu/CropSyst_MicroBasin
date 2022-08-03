#ifndef CDBFH
#define CDBFH
#include "corn/format/binary/binary_file_fstream.h"
//180107 #include "corn/container/association.h"
#include "corn/container/bilist.h"
#include "corn/dynamic_array/dynamic_array_T.h"
namespace CORN {
//______________________________________________________________________________
typedef unsigned long ULONG;    // 4 Bytes
typedef unsigned short USHORT;  // 2 Bytes
typedef short OFFSET;           // 2 Bytes
typedef ULONG SECT;             // 4 Bytes
typedef ULONG FSINDEX;          // 4 Bytes
typedef USHORT FSOFFSET;        // 2 Bytes
typedef USHORT WCHAR;           // 2 Bytes
typedef ULONG DFSIGNATURE;      // 4 Bytes
typedef unsigned char BYTE;     // 1 Byte
typedef unsigned short WORD;    // 2 Bytes
typedef unsigned long DWORD;    // 4 Bytes
typedef ULONG SID;              // 4 Bytes
//typedef GUID CLSID;             // 16 Bytes

typedef sint32 sector_ID;
//______________________________________________________________________________
class Compound_file_binary_format
: public Binary_file_fstream
{
 public:
   #pragma pack(1)
   struct StructuredStorageHeader
   { // [offset from start (bytes), length (bytes)]
    BYTE    CDF_ID[8];             // [00H,08] {0xd0, 0xcf, 0x11, 0xe0, 0xa1, 0xb1,
                                // 0x1a, 0xe1} for current version
    BYTE    UID[16];               // [08H,16] reserved must be zero (WriteClassStg/
                                // GetClassFile uses root directory class id)
    USHORT  revision;      // [18H,02] minor version of the format: 33 is
                                // written by reference implementation
    USHORT  version;        // [1AH,02] major version of the dll/format: 3 for
                                // 512-byte sectors, 4 for 4 KB sectors
    USHORT  byte_order;         // [1CH,02] 0xFFFE: indicates Intel byte-ordering
    USHORT  sector_size_shift;       // [1EH,02] size of sectors in power-of-two;
                                // typically 9 indicating 512-byte sectors
    USHORT  short_sector_size_shift;   // [20H,02] size of mini-sectors in power-of-two;
                                // typically 6 indicating 64-byte mini-sectors
    BYTE    reserved1[10];
    FSINDEX SAT_sector_count;          // [28H,04] must be zero for 512-byte sectors,
                                // number of SECTs in directory chain for 4 KB
                                // sectors
    sector_ID    directory_stream_first_sector_SecID;         // [30H,04] first SECT in the directory chain
    DFSIGNATURE signature;     // [34H,04] signature used for transactions; must
                                // be zero. The reference implementation
                                // does not support transactions
    ULONG   standard_stream_minimum_size;  // typically 4096 bytes
    sector_ID    SSAT_first_sector_ID;     // [3CH,04] first SECT in the MiniFAT chain
    FSINDEX SSAT_sector_count;      // [40H,04] number of SECTs in the MiniFAT chain
    sector_ID    MSAT_first_sector_ID;         // [44H,04] first SECT in the DIFAT chain
    FSINDEX MSAT_sector_count;          // [48H,04] number of SECTs in the DIFAT chain
    sector_ID    MSAT_part1[109];         // [4CH,436] the SECTs of first 109 FAT sectors
   };
   #pragma pack()
   //___________________________________________________________________________
   #pragma pack(1)
   struct Directory_entry
   {
      //BYTE     name[64];
      std::wstring name;
      nat16    unused_area_size;
      nat8     type;
      nat8     node_color;
      sint32   dir_ID_left_node;
      sint32   dir_ID_right_node;
      sint32   dir_ID_root_node;
      BYTE     unique_ID[16];    // may be all 0
      nat32    user_flags; // may be all 0
      BYTE     creation_timestamp[8]; // mall be all 0
      BYTE     modification_timestamp[8];
      sector_ID first_sector_ID;   // no negative codings
      nat32    stream_size;
      nat32    unused;
   };
   #pragma pack()

   //___________________________________________________________________________
   class Stream
   : public CORN::Binary_file_fstream
   , public CORN::Item
   {public:
      bool modified;
    public:
      inline Stream()
         : CORN::Binary_file_fstream("",false,std::ios_base::in|std::ios_base::out) //111118
         , modified(false)
         {}
      virtual std::STREAM_TYPE &provide_stream()                   performs_IO_;
      virtual sector_ID get_first_sector_ID()                         const = 0;
      inline bool is_loaded()                     const { return strm != NULL; }
   };
   //___________________________________________________________________________
   class Stream_user
   : public Stream
   {  int32 dir_ID;
      Directory_entry *dir_entry;   // owned by this
    public:
      inline Stream_user(int32 _dir_ID,Directory_entry *_dir_entry_given)
         : dir_ID(_dir_ID)
         , dir_entry(_dir_entry_given)
         {}
      bool has_name(const std::wstring &name)                              const;
      virtual sector_ID get_first_sector_ID()                              const;
         // get this from the dir_entry
   };
   //___________________________________________________________________________
   class Stream_directory
   : public Stream
   {  int32 dir_sector_ID;
    public:
      Stream_directory(int32 _dir_sector_ID);
      Stream_user *provide_user_stream
         (const std::wstring &name
         ,int32 in_directory_entry_ID
         ,bool creating_document)                                  performs_IO_;
    protected:
      bool read(Directory_entry &dir_ent)                          performs_IO_;
      inline virtual sector_ID get_first_sector_ID() const {return dir_sector_ID;};
   };
   //___________________________________________________________________________
   class Sector_allocation_table
   : public CORN::Dynamic_array<sector_ID>
   {
    public:
      inline Sector_allocation_table()
      :CORN::Dynamic_array<sector_ID>()
      {};
      nat32 render_stream_sector_chain(sector_ID first_sector_ID,CORN::Dynamic_array<nat32> &sector_chain) const;
      sector_ID allocate_sector()                                 modification_;
   };
   //___________________________________________________________________________
   class Master_sector_allocation_table
   : public CORN::Dynamic_array<sector_ID>
   {};
   //___________________________________________________________________________
 protected:
   provided_ StructuredStorageHeader    *header;    bool header_modified;
   provided_ Stream_directory *master_directory_stream;
   contribute_ Stream_user    *recently_provided_user_stream;
   contribute_ Bidirectional_list /*180101 Association_list*/ user_streams;   // This could be a search tree, but there is not expected to be alot of document user streams
   Sector_allocation_table    *sector_allocation_table;  // Also know as the Double-Indirect Fat
   Master_sector_allocation_table *MAST;
   //Unidirectional_list         streams;
 protected:
   contribute_ bool creating_document;
public:
   Compound_file_binary_format(const char *_file_name);
   ~Compound_file_binary_format();
   Stream_user &provide_user_stream(const std::wstring &name)       performs_IO_;
   Stream_directory &provide_master_directory_stream()              performs_IO_;
   bool write_all();
public: // eventually protected:
   nat32 calc_sector_file_pos(sector_ID sector_ID)                         const;
   StructuredStorageHeader    &provide_header()                     performs_IO_;
   nat32 load_stream_buffer(Stream &stream) performs_IO_;
   nat32 write_stream_buffer(Stream &stream) performs_IO_;
      //<<\return the size of the buffer/stream
   Sector_allocation_table &provide_sector_allocation_table()       performs_IO_;
   Master_sector_allocation_table &provide_master_sector_allocation_table()       performs_IO_;
private:
   bool write_header()                                              performs_IO_;
   bool write_sector_allocation_table()                             performs_IO_;
};
//______________________________________________________________________________
}; // namespace CORN
#endif
