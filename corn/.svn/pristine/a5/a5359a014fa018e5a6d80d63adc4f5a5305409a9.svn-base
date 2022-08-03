#ifndef CORN_FORMAT_IDENTIFIER_H
#define CORN_FORMAT_IDENTIFIER_H

#include <corn/std/std_fstream.h>
#include <corn/tabular/tabular_format.h>
#include <AdvGridWorkbook.hpp>

namespace CORN
{
//______________________________________________________________________________
class Text_format_auto_identifier
{  STD_NS ifstream  text_file;
   Common_tabular_file_format  &tabular_file_format; //
public:
   Text_format_auto_identifier
      (modifiable_ /*not_const*/ Common_tabular_file_format  &_tabular_file_format
      ,const char *sample_filename);
   bool identify();
};
//______________________________________________________________________________
#ifdef NYI
class dBase_format_auto_identifier
{  Common_tabular_file_format  &tabular_file_format; //
public:
   dBase_format_auto_identifier
      (not_const Common_tabular_file_format  &_tabular_file_format
      ,const char *sample_filename);
   bool identify();
};
#endif
//______________________________________________________________________________
class Excel_format_auto_identifier
{  Common_tabular_file_format  &tabular_file_format; //
public:
   Excel_format_auto_identifier
      (modifiable_  Common_tabular_file_format  &_tabular_file_format
      ,const char *sample_filename);
   bool identify(TAdvGridWorkbook *sample_workbook);
};

//______________________________________________________________________________
class Tabular_format_identifier
{private:
   Format_file_type identify_file_type_by_extension(const char *_sample_filename) const;
   // call identify_file_type_by_extension first
   // if it can't identify or it is ambiguous extension, then call identify_file_type which will preread
   Format_file_type identify_file_type(STD_NS ifstream &datafile) const;
 public:
#ifdef NYI
   bool identify
      (not_const Common_tabular_file_format  &tabular_file_format
      ,const char *sample_filename
      ,Tsample_form *sample_form
      ) const ;
#endif
};
//______________________________________________________________________________
}
#endif

