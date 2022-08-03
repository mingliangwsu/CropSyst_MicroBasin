#ifndef file_system_typesH
#define file_system_typesH
//---------------------------------------------------------------------------
namespace CORN {
namespace OS {
//______________________________________________________________________________
enum Directory_entry_type
{
   // Note: This enumeration is not arbitrary, it matches the
   // high order nyble of the st_mode word16 of the
   // directory entry 'stat' (POSIX complient)
    unknown_entry             = 0x0  // a comment in the sys/stat.h file seems to indicate that the st_mode 0 could represent a file, but the S_ISREG macro only test for value 8
   ,FIFO_special_entry        = 0x1
   ,character_special_entry   = 0x2
   ,block_special_entry       = 0x3
   ,directory_entry           = 0x4
   // 4,5,6,7 are undefined (perhaps the correspond to junctions, symbolic links, and/or hard links)
   ,file_entry                = 0x8
};
//______________________________________________________________________________
} } // namespace CORN OS
#endif
