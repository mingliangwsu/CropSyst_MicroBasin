#ifndef CSS_fileH
#define CSS_fileH

#include "corn/format/binary/oldbinrec/oldbinrec_s.h"
/*
   This set of classes allow reading and writing spreadsheet files.

   This is the base class for
   Lotus 1-2-3 WKS
   Excel XLS spreadsheet

   file classes.
*/

// CSS_Record_type is not a record header code (which are defined by derived classes)
// These specify the kind of record.

#define MAX_COLUMNS 100
using namespace CORN;
//______________________________________________________________________________
class Common_spreadsheet_file
: public Old_binary_record_file
{
 public:
    uint8    column_widths[MAX_COLUMNS];//The column width set by WKS_CODE_COLW1
    int16    max_col;
    int16    max_row;
 public: // Enumerations
   enum Record_type
   { unknown_record
   , BOF_record
   , formatting_record
   , data_cell_record      // Anything that displays data in a cell
   , multiple_data_cell_record      // Anything that displays data in a cell
   , formula_cell_record   // computes and displays data in a cell
   , comment_record
   , control_record
   , printing_record
   , EOF_record
   , any_record
   };
   //________________________________________________________________
   enum data_types {not_data,type_str,type_date,type_integer,type_float};
   //________________________________________________________________
   enum CSS_justifications
   {CSS_justify_general    // 000b
   ,CSS_justify_left       // 001b
   ,CSS_justify_center     // 010b
   ,CSS_justify_right      // 011b
   ,CSS_justify_fill       // 100b
   };
   //________________________________________________________________
 protected: // write
    virtual void update_extent(int16 i_column,int16 i_row);
    // When writing cells we need to keep track of the extent of the sheet
 public:
   Common_spreadsheet_file                                                       //001206
      (const char *i_filename
      ,std::ios_base::openmode _openmode);                                       //111108
      ///< for input
   Common_spreadsheet_file
      (const char *i_filename                                                    //001206
      ,sint32 first_row  ,sint32 rows                                            //090618
      ,int16 first_col   ,int16 cols  );
   inline virtual ~Common_spreadsheet_file() {}                                  //151204
 public: // The following are abstract methods that must be defined in derived classes
   virtual void write_dimensions
      (sint32 first_row  ,sint32 rows                                            //090618
      ,int16 first_col ,int16 cols) = 0;
   virtual void initialize();                                                    //981006
               // this method gets called at the end of open_output
               //   where any additional configuration records may need to be written following the BOF record.
   virtual void write_integer_cell
      (int16 _column
      ,int16 _row
      ,int16 _value);
   virtual void write_number_cell
      (int16 _column
      ,int16 _row
      ,float64 _value
      ,int8  _precision);
   virtual void write_label_cell
      (int16 _column
      ,int16 _row
      ,CSS_justifications _alignment
   ,const char *_value);                                                        //030120
   virtual void write_col_width                                                  //981006
      (int16 from_col
      ,int16 to_col
      ,int16 col_width_in_chars) = 0;
      /**< This is optional method that may be overridden by spreadsheet classes.
         It can be used to specify the width of a range of columns (in characters).
         Most spreadsheets do not require a column width records,
         and if not present will simply use a default width.
      **/
   inline virtual void freeze_pane                                               //981006_
      (int16 left_most_column,int16 top_most_row)
      {};
      /**<Later we may add multiple panes (excel can handle it)
         In that case we will return the current pane number.
         Now we just have one pane.
      **/
   // The following are used to generated ordered spreadsheet files }
   void write_integer(int16 value ,int16 width);
   void write_real(float64 value, int8 width, int8 precision);
   inline void write_float(float64 value, int8 width, int8 _precision) { write_real(value, width, _precision); }; //021216
   void write_string_aligned(CSS_justifications alignment            //020212
      , const char *value );                                         //030120
   void endl();
 public: // reading methods
   virtual void read_number_cell(bool expect_header = false);
   virtual void read_integer_cell(bool expect_header = false);
   virtual void read_label_cell(bool expect_header = false);         //981018
   virtual Record_type read_next(Record_type filter_type = any_record) = 0;
      /**< Reads the next record from the file and returns type type of record read.
           Input settings for the cell will be set up if it is a data cell record.
      **/
   bool reset() performs_IO_; // Go back to the beginning of the files            //111111
   char *cell_text_string(char *buffer);
public: // state accessors
   inline int16 get_max_row() { return max_row; };
   inline int16 get_max_col() { return max_col; };
public: // properties of the last cell read
   uint32      row;       // 0 based
   int16       col;       // 0 based
   data_types  data_type; // The type of data
   char        cstr_value[257];      // the value if type_str
   int16       int_value;           // the value if type_integer
   float64     float_value;        // the value if type_float
   int16       precision;       // number of decimal points if a float
   int8        alignment;
#ifdef USE_CORN_DATES
#error reached
   CORN_date   date_value;         // the value if TYPE_DATE
#endif
};
//_1998-10-06___________________________________________________________________
#endif

