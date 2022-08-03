#ifndef delineationH
#define delineationH
#ifndef labeled_enumH
#  include "corn/labeled_enum.h"
#endif
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/const.h"
#include <string>
namespace CORN {
extern const char *text_quote_mode_label_table[];
extern const char *delimit_mode_label_table[];                                   //040925

class Data_record;
//______________________________________________________________________________
enum Relative_to      // Relative to top of
   {FILE_RELATIVE
      ///< Use this option when we know something
      /// is always going to be at a specified offset
      /// from the beginning of the file (or first cell)
      /// This implies file will always have the same
      /// delineation (No extraneous text)
   ,DATA_RELATIVE
      ///< was BEGIN_MARKER_RELATIVE 070923_
      /// Use this option when there may be extraneous text
      /// at the begining of a file and there is some marker
      /// that specifies the actual beginning of the data.
   ,PAGE_RELATIVE
      ///< Use this options for text files that are paginated
      /// And we know that something always occurs
      /// on a particular line of the page
      /// (Used for text file reports)
      /// Pagination is denoted with FormFeed character ASCII 12
   ,BLOCK_RELATIVE
      ///< Use this when the line row is relative to the
      /// current section (I.e. the Units row might be the 4 row of the column header).
      /// [This may not be applicable to detail lines, I don't know a situation where it might be used at this time. ].
      //070925     ,LAST_HEADER_ROW_RELATIVE
      /// This is obsolete
      /// Now use section.
      ///  Also header sections are obsolete, now
      ///  fields are floating and can appear anywhere in the file (on the page)
      //070925    ,LAST_COLUMN_HEADER_ROW_RELATIVE
      /// This is obsolete because I never really used it
      /// it was intended to determine the start of detail lines
      /// But it have never been used
   };
extern const char *relative_to_label_table[];
DECLARE_LABELED_ENUM(Relative_to_labeled,Relative_to,relative_to_label_table);
//_2006-08-23___________________________________________________________________
class Extent_layout
{
public:
   Relative_to_labeled relative_to_labeled;
      ///< In the case of the file extent, only BEGIN_FILE_RELATIVE and BEGIN_MARKER_RELATIVE
      /// are relevent (this is the start of all the data including: header fields (if any) column headers (if any) and detail lines)
      /// The relative modes LAST_HEADER_ROW_RELATIVE,LAST_COLUMN_HEADER_ROW_RELATIVE
      /// are relevent to the respective potential sections: header fields, column headers, and detail line extents.
   int16 start_row_1_based;
      ///< This is the row number relative to the bounding extent
      /// For example the column headers may start 5 rows after the begin_marker for the file
      /// I had this at 32, it probably should be 32bit but I don't realistically
      /// think we will encounter a case were the data or column headers start at a huge
      /// number although I suppose they could be at the end of a file (footers)
      /// Row numbers are 1 based, 0 indicates it doesn't apply.
      /// This is the actual row number where the data starts
      /// (below any header and column header rows/lines).
      /// This count starts after any begin_data_marker
   std::string begin_marker;
      ///< This is a character string (usually on its own line) that marks the beginning of the
      /// header or data detail lines
      /// Empty string indicates no marker
      /// data everything before the marker (including this line) is ignored
      /// There will often be an end_data_marker
      /// The reading of the data (headers and detail lines) begins after this line
      /// Header and/or data record number (1 based) will be relative to
      /// To the point following the begin_data_marker
      /// (This will usually be the line following the line containing the begin_data_marker,
      /// although I do see it possible that the data may start on the same line.
   std::string end_marker;
      ///< This is a character string (usually on its own line) that marks the end of the data
      /// Empty string indicates no marker
      /// Everything after this line (including the marker) is ignored.
      /// With no additional parsing
public:
   inline Extent_layout()
      : relative_to_labeled(FILE_RELATIVE)
      , start_row_1_based(0)
      , begin_marker("")
      , end_marker("")
      {}
   virtual bool setup_structure(CORN::Data_record &data_rec,bool for_write) modification_;
};
//_2005-04-11___________________________________________________________________
class Delineation_layout
: public Extent_layout
{ ///< \class This class does not support header fields or column headers other than specifying the number of rows to skip to locate the first data row
 public:
    enum Delimit_mode
       {DELIMIT_intrinsic
       ,DELIMIT_fixed_width
       ,DELIMIT_character};
    DECLARE_LABELED_ENUM(Delimit_mode_labeled,Delimit_mode,delimit_mode_label_table)
    Delimit_mode_labeled delimit_mode_labeled;

    // 180508 rename Delimit_mode to Delimitation

    enum Text_quote_mode   { NO_QUOTE, SINGLE_QUOTE, DOUBLE_QUOTE, ALTERNATING_QUOTE};
    DECLARE_LABELED_ENUM(Text_quote_mode_labeled,Text_quote_mode,text_quote_mode_label_table)

    // 180508 rename to Quoting

   // In alternating quote mode, single quote will quote double quotes
   // I.e.  'He said "yes"'
   // or    "It's mine not sara's"

   //NYI          eventually add justification option

   // If not fixed width columns, the following delimited options are active
   bool           continuous_delimiter; // Treat continuous delimiters as one
   bool           delimiter_tab;
   bool           delimiter_space;
   bool           delimiter_comma;
   bool           delimiter_semicolon;
   bool           delimiter_other;    // also allow other_delimiter_16 as a delimiter
   int16          other_delimiter_16; // Other character to use as a delimiter
   bool           delimiter_string;                                              //050830
   std::string other_delimiter_string;    // Other extended delimiter (I.e. HTML table <TH><TD>) //050830
   Text_quote_mode_labeled   text_quote_mode_labeled;                            //020505

      //180508 rename to quoting

   std::string decimal_mark;  // . for US  , for other countries   This probably should be moved to Tabular file since it is a property of the file format, not delineation //050402

      //180508 rename to decimal separator

   std::string notes;        // Commentary information stored in the format file
 private:
   mutable std::string return_buffer;                                            //060223
 public:
   inline Delineation_layout()
      : Extent_layout()
      , delimit_mode_labeled(DELIMIT_character)
      , continuous_delimiter(false)
      , delimiter_tab(false)
      , delimiter_space(false)
      , delimiter_comma(false)
      , delimiter_semicolon(false)
      , delimiter_other(false)
      , other_delimiter_16(32)
      , delimiter_string(false)                                                  //090305
      , other_delimiter_string("")                                               //090305
      , text_quote_mode_labeled(NO_QUOTE)                                        //010815
      , decimal_mark(".")                                                        //050402
      , notes("")
      {}
   virtual bool setup_structure
      (CORN::Data_record &data_rec,bool for_write)                 modification_;
   bool is_delimiter(char potential_delimiter)                      affirmation_;
   const char *get_delimitor() const;
      // When reading files, multiple potential delimitors could be optionally specified as delimitors
      // When writing files, only a single delimitor is available.
   virtual bool default_R_text()                                   modification_;
      // Sets up delimit for R import/export text files.
   bool copy_from(const Delineation_layout &from)                  modification_;//141008
};
//_2005-04-11___________________________________________________________________
} // namespace CORN
//______________________________________________________________________________
#endif

