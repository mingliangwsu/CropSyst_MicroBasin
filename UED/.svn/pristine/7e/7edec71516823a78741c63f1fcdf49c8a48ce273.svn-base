#include "UED/library/UED_fname.h"
//______________________________________________________________________________
UED_File_name::UED_File_name(const char *_filename)
: CORN::Filtered_file_name(_filename ? _filename : "noname",UED_EXT,"Database",UED_wildcard)
{}
//______________________________________________________________________________
UED_File_name::UED_File_name
(const CORN::OS::File_name &_filename)
: CORN::Filtered_file_name(_filename.c_str() ,UED_EXT,"Database",UED_wildcard)   //050207
{}
//______________________________________________________________________________
// UED_fname.h

