#include "CDBF.h"
#include <limits>
#include <sstream>
#include <assert.h>
namespace CORN {
Compound_file_binary_format::Directory_entry default_directory_entry =
{  L"" /*{0,0}*/ // name
,  2     // unused_area_size;
,  0x00  // Empty
,  0x00  // node_color
,  -1    // dir_ID_left_node
,  -1    // dir_ID_right_node
,  -1    // dir_ID_root_node
,  {0,0} // unique_ID[16];    // may be all 0
,  0     // user_flags // may be all 0
,  {0}   // creation_timestamp[8] // may be all 0
,  {0}   // modification_timestamp[8]
,  -2    // first_sector_ID
,  0     // stream_size
,  0     // unused
};
//______________________________________________________________________________
Compound_file_binary_format::Compound_file_binary_format(const char *_file_name)
: Binary_file_fstream(_file_name,false,std::ios_base::in|std::ios_base::out)     //111119
, header(0)
, header_modified(false)
, master_directory_stream(0)
, sector_allocation_table(0)
, MAST(0)
, recently_provided_user_stream(0)
, creating_document(true)                                                        //111010
{}
//_2011-08-22___________________________________________________________________
Compound_file_binary_format::~Compound_file_binary_format()
{}
//_2011-08-22___________________________________________________________________
bool Compound_file_binary_format::write_all()
{  if (master_directory_stream) write_stream_buffer(*master_directory_stream);
   if (sector_allocation_table && sector_allocation_table->is_modified()) write_sector_allocation_table();
   if (header_modified) write_header();
}
//_2011-10-10___________________________________________________________________
nat32 Compound_file_binary_format::calc_sector_file_pos(sector_ID sector_ID)   const
{  nat32 sector_size = 1<<header->sector_size_shift;
   nat32 pos = 512 + sector_ID * sector_size;
   return pos;
}
//_2011-08-22___________________________________________________________________
/*NYN
const Directory_entry &Compound_file_binary_format::provide_directory_entry(const std::wstring &name) provision_
{}
*/
//_2011-08-22___________________________________________________________________
Compound_file_binary_format::Stream_directory &Compound_file_binary_format::provide_master_directory_stream()                performs_IO_
{  if (!master_directory_stream)
   {  provide_header();
      int32 dir_sector_ID = header->directory_stream_first_sector_SecID;
      creating_document = dir_sector_ID < 0;                                     //111010
      if (creating_document)                                                     //111010
      {  Sector_allocation_table &SAT = provide_sector_allocation_table();
         dir_sector_ID = SAT.allocate_sector();
         master_directory_stream = new Stream_directory(dir_sector_ID);
      } else
      {  master_directory_stream = new Stream_directory(dir_sector_ID);
         load_stream_buffer(*master_directory_stream);
      }
   }
   return *master_directory_stream;
}
//_2011-08-27___________________________________________________________________
Compound_file_binary_format::Stream_user &Compound_file_binary_format::provide_user_stream(const std::wstring &name) performs_IO_
{  Stream_user *provided_stream = 0;
   // First do a quick check if the desired stream was the most recent provision
   if (recently_provided_user_stream && recently_provided_user_stream->has_name(name))
       provided_stream = recently_provided_user_stream;
   // Next look in provided streams in memory.
   if (!provided_stream)
      provided_stream = dynamic_cast <Stream_user *>(user_streams.find_wstr(name.c_str()));
   // Next try to load the stream from the document, create if necessary.
   if (!provided_stream)
   {  Stream_directory &directory_stream = provide_master_directory_stream();
      recently_provided_user_stream = provided_stream
         = directory_stream.provide_user_stream(name,0,creating_document);
      if (recently_provided_user_stream->is_loaded())
         load_stream_buffer(*recently_provided_user_stream);
   }
   return *provided_stream;
}
//_2011-08-22___________________________________________________________________
Compound_file_binary_format::StructuredStorageHeader    &Compound_file_binary_format::provide_header() performs_IO_
{  if (!header)
   {  bool need_to_read_header = !header && get_file_length() > 0;
      header = new StructuredStorageHeader;
      if (need_to_read_header) //
      {  // the file already exists, read it.
         std:: STREAM_TYPE &strm = provide_stream();
         strm.seekg(0);                                                           //111206
         strm.read((char *)header,sizeof(header));
         header_modified = false;
            // actually this should be read_int32_array because sect IDS are signed
      } else   // we are creating the file, setup defaults
      {
         header->CDF_ID[0] = 0xd0;
         header->CDF_ID[1] = 0xcf;
         header->CDF_ID[2] = 0x11;
         header->CDF_ID[3] = 0xe0;
         header->CDF_ID[4] = 0xa1;
         header->CDF_ID[5] = 0xb1;
         header->CDF_ID[6] = 0x1a;
         header->CDF_ID[7] = 0xe1;
         for (int i = 0; i < 16; i++) header->UID[i] = 0;
         header->revision = 33;      // [18H,02] minor version of the format: 33 is written by reference implementation
         header->version  = 3;        // [1AH,02] major version of the dll/format: 3 for 512-byte sectors, 4 for 4 KB sectors
         header->byte_order = 0xFFFE; // Intel byte-ordering
         header->sector_size_shift = 9 ; // 9 indicating 512-byte sectors
         header->short_sector_size_shift = 6;   // typically 6 indicating 64-byte mini-sectors
         for (int i = 0; i < 10; i++) header->reserved1[i] = 0;
         header->SAT_sector_count = 0;  // must be zero for 512-byte sectors
         header->directory_stream_first_sector_SecID = -2; // first SECT in the directory chain will be set when the directory is written
         header->signature = 0;     // signature used for transactions; must be zero. The reference implementation does not support transactions
         header->standard_stream_minimum_size = 4096;
         header->SSAT_first_sector_ID = -2;     // [3CH,04] first SECT in the MiniFAT chain
         header->SSAT_sector_count =0;      // [40H,04] number of SECTs in the MiniFAT chain
         header->MSAT_first_sector_ID =-2;         // [44H,04] first SECT in the DIFAT chain
         header->MSAT_sector_count = 0;          // [48H,04] number of SECTs in the DIFAT chain
         for (int i = 0; i < 109; i++) header->MSAT_part1[i] = -1; // all free
         write_header();
      }
   }
   return *header;
}
//_2011-08-27___________________________________________________________________
bool Compound_file_binary_format::write_header()                    performs_IO_
{  seek(0);
   std:: STREAM_TYPE &strm = provide_stream();                                  //111206
   strm.write((char *)header,sizeof(StructuredStorageHeader));                                    //111206
   header_modified = false;
   return true;
}
//_2011-08-27___________________________________________________________________
std:: STREAM_TYPE &Compound_file_binary_format::Stream::provide_stream() performs_IO_
{  if (strm == NULL)
   {  bool include_IOS_in_mode = true;                                           //091222
#if (defined(__BCPLUSPLUS__) || defined(_MSC_VER))
// BC++ seems to have problems creating files in in/out mode
                  include_IOS_in_mode = true;                                    //1110927
/*
#  ifdef _MSC_VER
						_access
#  else
						access
#  endif
						(get_file_name(), 0) == 0;
*/
#  if (__BCPLUSPLUS__ <= 0x0550)
      int
#  else
       std::ios_base::openmode
#  endif
#else
      std::_Ios_Openmode   // This if for GNUC may actually work with all compilers, I just haven't checked 090305
#endif
      open_mode = (std::iostream::out)  OR_IOS_BINARY;
      if (include_IOS_in_mode) open_mode |= (std::iostream::in);
      strm = new std::stringstream(open_mode);
   }
   return *strm;
}
//_2007-08-27__________________________________________________________________/
nat32 Compound_file_binary_format::load_stream_buffer(Stream &doc_stream) performs_IO_
{  iostream doc_stream_buffer = doc_stream.provide_stream();
   CORN::Dynamic_array<nat32> stream_sector_chain;
   nat32 sector_count = provide_sector_allocation_table().render_stream_sector_chain(doc_stream.get_first_sector_ID(),stream_sector_chain);
   nat32 sector_size = 1 << provide_header().sector_size_shift;
   char *buffer = new char [sector_size ];
   nat32 chars_read = 0;
   for (nat32 sector_chain_index = 0; sector_chain_index < sector_count; sector_chain_index++)
   {  nat32 sector_ID = stream_sector_chain.get(sector_chain_index);
      nat32 sector_file_pos = calc_sector_file_pos(sector_ID);
      seek(sector_file_pos); // Seek to the desired offset.
      read(reinterpret_cast<char *>(buffer),sector_size);
      chars_read += provide_stream().gcount();
      doc_stream_buffer.write(buffer, chars_read);
   }
   delete[] buffer;
   return chars_read;
}
//_2007-08-27__________________________________________________________________/
nat32 Compound_file_binary_format::write_stream_buffer(Stream &doc_stream) performs_IO_
{  nat32 chars_written = 0;
   std::stringstream * in_memory_strm = dynamic_cast<std::stringstream * > (&doc_stream.provide_stream());
   CORN::Dynamic_array<nat32> stream_sector_chain;
   sector_ID first_sector_ID = doc_stream.get_first_sector_ID();
   Sector_allocation_table &SAT = provide_sector_allocation_table();
   nat32 sector_count = 0;
   nat32 sector_size = 1 << provide_header().sector_size_shift;
   if (first_sector_ID < 0)
      first_sector_ID = SAT.allocate_sector();
   else
      sector_count = SAT.render_stream_sector_chain(first_sector_ID,stream_sector_chain);
   nat32 sector_index = 0;

//   in_memory_strm->seekg(std::ios_base::beg);
//   std::string  buffer1(in_memory_strm->str());
//   in_memory_strm->seekg(0,std::ios_base::end);
//   nat32 stream_length = in_memory_strm->tellg();
//   stream_length = buffer1.length();
//   stream_length = in_memory_strm->tellg();
//   in_memory_strm->seekg(std::ios_base::beg);
//   nat32 stream_length = doc_stream.get_file_length();


   int32 curr_sector_ID = first_sector_ID;
   char *buffer = new char [sector_size ];
   in_memory_strm->seekg(0,std::ios_base::beg);
   bool _gd = in_memory_strm->good();
   bool _eof = in_memory_strm->eof();
   std::cout << _gd;
   std::cout << _eof;
   while (in_memory_strm->good() && ! in_memory_strm->eof())
   {
      nat32 sector_file_pos = calc_sector_file_pos(curr_sector_ID);
      seek(sector_file_pos);
      in_memory_strm->read(reinterpret_cast<char *>(buffer),sector_size);
      nat32 chars_read = sector_size; // in_memory_strm->/*provide_stream().*/gcount();
      write(buffer, chars_read);
      curr_sector_ID = SAT.allocate_sector();
   }
   // makesure the stream is in the directory (if user stream)
   delete[] buffer;
   return chars_written;
}
//_2007-08-28__________________________________________________________________/
nat32 Compound_file_binary_format::Sector_allocation_table::render_stream_sector_chain
(sector_ID first_sector_ID,CORN::Dynamic_array<nat32> &sector_chain)       const
{  sector_chain.append(first_sector_ID);
   for (sector_ID next_sector = get(first_sector_ID); next_sector > 1; next_sector = get(next_sector))
      sector_chain.append(next_sector);
   return sector_chain.get_count();
}
//_2007-08-27__________________________________________________________________/
Compound_file_binary_format::Master_sector_allocation_table &Compound_file_binary_format::provide_master_sector_allocation_table()         performs_IO_
{  StructuredStorageHeader &hdr = provide_header();
   MAST = new Compound_file_binary_format::Master_sector_allocation_table;

   nat32 sector_size = (1 << hdr.sector_size_shift);
   nat32 MSAT_extension_array_size = sector_size / sizeof(SECT);
   SECT *MSAT_extension = 0; // new SECT [MSAT_extension_array_size];
   nat32 MSAT_extension_index = 0;
   nat32 MSAT_extension_file_pos = 0;
   bool more_sector_allocs = true;
   for (nat32 MSAT_index = 0; more_sector_allocs; MSAT_index ++)
   {  if (MSAT_index < 109)
      {  more_sector_allocs = true;
         MAST->append(hdr.MSAT_part1[MSAT_index]);
        if (MSAT_index == 108)
        {  // load the first MSAT_extension
           more_sector_allocs = hdr.MSAT_first_sector_ID != -2;
           if (more_sector_allocs)
           {  if (MSAT_extension)   // we only need one buffer at a time.
                  MSAT_extension = new SECT [MSAT_extension_array_size];
              MSAT_extension_file_pos = calc_sector_file_pos(hdr.MSAT_first_sector_ID);
           }
        }
      } else
      {  if (MSAT_extension_index == MSAT_extension_array_size);
         {  more_sector_allocs = MSAT_extension[MSAT_extension_array_size-1] != -2 ;
            if (more_sector_allocs)
               MSAT_extension_file_pos = calc_sector_file_pos(MSAT_extension[MSAT_extension_array_size-1]);
         }
         if (MSAT_extension_file_pos)
         {  // we need to load the next MAST extension sector
            seek(MSAT_extension_file_pos);
            read_int32_array(header->MSAT_part1,MSAT_extension_array_size);
               // actually this should be read_int32_array beause sect IDs are signed
            MSAT_extension_file_pos = 0;
         }
         MAST->append(MSAT_extension[MSAT_extension_index++]);
      }
   }
   delete []MSAT_extension;
   return *MAST;
}
//_2007-08-27__________________________________________________________________/
Compound_file_binary_format::Sector_allocation_table &Compound_file_binary_format::provide_sector_allocation_table()       performs_IO_
{  if (!sector_allocation_table)
   {  Compound_file_binary_format::Master_sector_allocation_table &MAST = provide_master_sector_allocation_table();
      sector_allocation_table = new Compound_file_binary_format::Sector_allocation_table(/**SAT_stream*/);
      StructuredStorageHeader &hdr = provide_header();
      nat32 sector_size = (1 << hdr.sector_size_shift);
      nat32 SAT_array_size = sector_size / sizeof(SECT);
      sector_ID SAT_sector_ID = 0;
      nat32 next_MSAT_index = 0;
      do
      {  SAT_sector_ID = next_MSAT_index < MAST.get_count()
            ? MAST.get(next_MSAT_index)
            : 0;
         if (SAT_sector_ID > 0)
         {  nat32 SAT_pos = calc_sector_file_pos(SAT_sector_ID);
            seek(SAT_pos);
            for (nat32 i = 0; i < SAT_array_size; i++)
            {  sector_ID sectID = read_int32();
               sector_allocation_table->append(sectID);
            }
         }
         next_MSAT_index++;
      } while (SAT_sector_ID);
   }
   return    *sector_allocation_table;
}
//_2007-08-27__________________________________________________________________/
bool Compound_file_binary_format::Stream_user::has_name(const std::wstring &name) const
{  return dir_entry->name == name;
}
//_2007-08-28__________________________________________________________________/
sector_ID Compound_file_binary_format::Stream_user::get_first_sector_ID()                                   const
{  return dir_entry->first_sector_ID;
}
//_2007-08-28__________________________________________________________________/
Compound_file_binary_format::Stream_user *Compound_file_binary_format::Stream_directory::provide_user_stream
(const std::wstring &name
,int32 in_directory_entry_ID
,bool creating_document)                                            performs_IO_
{
   Compound_file_binary_format::Stream_user *found_stream = 0;
   Directory_entry *current_directory_entry = 0;
   if (creating_document)
   {
      current_directory_entry =  new Directory_entry;
   }
   else
   {
      bool more_streams = good();
      Directory_entry *current_directory_entry =  new Directory_entry;
      while (!found_stream && more_streams)
      {  nat32 dir_entry_stream_pos = in_directory_entry_ID*128;
         seek(dir_entry_stream_pos);
         more_streams = read(*current_directory_entry);
         if (current_directory_entry->name == name)
         {  found_stream = new Stream_user(in_directory_entry_ID,current_directory_entry);
         } else
         {
            //delete current_directory_entry;
            if (more_streams)
               in_directory_entry_ID ++;
      /*
      if
      (current_directory_entry->name < name)
      {  delete current_directory_entry;
         if (current_directory_entry->dir_ID_left_node = -1)
         {  assert(false);
            // NYI the  stream is not found in directory
            // but it would go in the left node.
            // I haven't implemented this  because I haven't
            // worked out how to rebalance the directory tree.
            // so writing workbooks isn't implemented yet.
         } else
            found_stream = provide_user_stream(name,current_directory_entry->dir_ID_left_node);
      } else if (current_directory_entry->name > name)
      {
         if (current_directory_entry->dir_ID_right_node = -1)
         {  assert(false);
            // NYI the  stream is not found in directory
            // but it would go in the right node.
            // I haven't implemented this  because I haven't
            // worked out how to rebalance the directory tree.
            // so writing workbooks isn't implemented yet.
         } else
            found_stream = provide_user_stream(name,current_directory_entry->dir_ID_right_node);
      }
      */
         }
      } // while
   }
   if (!found_stream)                                                            //111010
   {  // We are adding the stream                                                //111010
         current_directory_entry->name = name;                                      //111010
         found_stream = new Stream_user(in_directory_entry_ID,current_directory_entry);
   }
   return found_stream;
}
//_2011-08-22___________________________________________________________________
Compound_file_binary_format::Stream_directory::Stream_directory(int32 _dir_sector_ID)
: Stream ()
, dir_sector_ID(_dir_sector_ID)
//, current_directory_entry_ID(MAXLONG)
{
/*
   header.directory_stream_first_sector_SecID
      nat32 dir_ID = dir_stream.provide_new_directory_entry();
         provided_stream = new UserStream(dir_ID);
         current_directory_entry.write(dir_stream);
         stream_dir_entry_found = true
*/
}
//_2011-08-22___________________________________________________________________
bool Compound_file_binary_format::Stream_directory::read(Directory_entry &dir_ent) performs_IO_
{  bool ready =  good() && !at_eof();
   if (ready)
   {
   read_wstring(dir_ent.name,UTF8LE_string,64);
   dir_ent.unused_area_size = read_nat16();
   dir_ent.type = read_nat8();
   dir_ent.node_color = read_nat8();
   dir_ent.dir_ID_left_node = read_int32();
   dir_ent.dir_ID_right_node = read_int32();
   dir_ent.dir_ID_root_node= read_int32();
   read_nat8_array(dir_ent.unique_ID,16);
   dir_ent.user_flags= read_nat32(); // may be all 0
   read_nat8_array(dir_ent.creation_timestamp,8); // mall be all 0
   read_nat8_array(dir_ent.modification_timestamp,8);
   dir_ent.first_sector_ID= read_nat32();
   dir_ent.stream_size= read_int32();
   dir_ent.unused= read_nat32();
//   ready = good() && !at_eof() && dir_ent.name.length();
   }
   return ready;
}
//_2011-08-28___________________________________________________________________
bool Compound_file_binary_format::write_sector_allocation_table()   performs_IO_
{  Compound_file_binary_format::Master_sector_allocation_table &MAST = provide_master_sector_allocation_table();
   StructuredStorageHeader &hdr = provide_header();
   nat32 sector_size = (1 << hdr.sector_size_shift);
   nat32 SAT_array_size = sector_size / sizeof(SECT);
   sector_ID SAT_sector_ID = 0;
   nat32 next_MSAT_index = 0;
   nat32 SAT_index = 0;
   do
   {  SAT_sector_ID = next_MSAT_index < MAST.get_count()
         ? MAST.get(next_MSAT_index)
         : 0;
      if (SAT_sector_ID > 0)
      {  nat32 SAT_pos = calc_sector_file_pos(SAT_sector_ID);
         seek(SAT_pos);
         for (nat32 i = 0; i < SAT_array_size; i++)
         {  sector_ID sectID = sector_allocation_table->get(SAT_index++);
            write_int32(sectID);
         }
      }
      next_MSAT_index++;
   } while (SAT_sector_ID);
   return true;
}
//_2011-08-28___________________________________________________________________
sector_ID Compound_file_binary_format::Sector_allocation_table::allocate_sector() modification_
{  nat32 free_sector_index;
   if (!is_in_array(-1,free_sector_index))
   {  append(-1);
      free_sector_index = get_count();
   }
   return free_sector_index;
}
//_2011-08-28___________________________________________________________________
} //namespace CORN

