#error Abandoned, I never finished working on this, I am now using xlslib (from SourceForge) to read xls files

#ifndef compound_document_Excel_XLSH
#define compound_document_Excel_XLSH
#include "corn/format/binary/CDBF.h"
namespace CORN
{
//______________________________________________________________________________
class Compound_document_Excel_XLS
: public Compound_file_binary_format
{
public:
   inline Compound_document_Excel_XLS(const char *_file_name)
      : Compound_file_binary_format(_file_name)
      {};
};
//______________________________________________________________________________
};
#endif
