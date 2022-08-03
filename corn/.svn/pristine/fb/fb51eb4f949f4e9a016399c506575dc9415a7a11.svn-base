#ifndef tabular_parserH
#define tabular_parserH

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/tabular/tabular.h"
#include "corn/container/text_list.h"
class ED_tabular_file_format;

namespace CORN
{

class Common_tabular_file_format;

//______________________________________________________________________________
class Grid_information
{
   class Cell
   {public:
      enum Status
      {  unidentified    // not parsed
      ,  unparsable
      ,  extraneous
      ,  unexpected_text  // I.e. label mismatch
      ,  data_type_mismatch // I.e. non numeric found in numeric field/column
      ,  scalar_field_label
      ,  scalar_field_data
      ,  column_header_caption
      ,  column_header_units
      ,  detail_line_date_field
      ,  detail_line_data
      ,  station_ID
      ,  station_name
      };
   protected:
      uint32 row;
      uint32 col;
      std::string sheet;
      std::string data;
      CORN::Data_type data_type;
      Status status;
   };
};
//______________________________________________________________________________
class Tabular_parser
{
public:
   enum Context_update_status
      { no_change_of_context
      , advance_to_next_column  // also in same context
      , in_same_context
      , out_of_context
      };
public:
   //___________________________________________________________________________
   class Context_abstract
   {
   protected:
      Context_update_status status;
   public:
      virtual Context_update_status update(char &character)         modification_= 0;
      virtual bool process_character(char character)                modification_= 0;
   };
   //___________________________________________________________________________
protected:
   const Common_tabular_file_format &format;
protected:
   CORN::Text_list         parsing_errors;
public:
   Tabular_parser(const Common_tabular_file_format &format);
   virtual bool read
      (const char *filename,CORN::Text_list &parsing_notes)         modification_= 0;
   // Actually probably want to return parsability information
   //
   virtual void clear_contexts()                                    modification_= 0;
   // returns the number of lines read.
};
//______________________________________________________________________________
};
#endif

