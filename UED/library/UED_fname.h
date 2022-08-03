#ifndef UED_fnameH
#define UED_fnameH
#define UED_LEXT       L"UED"
#define UED_EXT         "UED"
#define UED_wildcard    "*.UED"
//______________________________________________________________________________
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/OS/filtered_filename.h"

//_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
class UED_File_name
: public CORN::Filtered_file_name
{
 public:
   UED_File_name(const char *i_filename);
   UED_File_name(const CORN::OS::File_name &i_filename);
};
//_1999-02-28___________________________________________________________________
#endif

// UED_fname.h

