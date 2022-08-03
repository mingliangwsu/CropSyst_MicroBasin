#ifndef rprtclssH
#define rprtclssH

#if ((CROPSYST_VERSION > 0) && (CROPSYST_VERSION < 5))
//#  error The report writer class is obsolete in version 5


//RPRTCLSS;

/*
  The report class file is formatted as follows:

  LOTUS_BOF record
  4 label_cells containing the header lines
     each in column 1 starting at row 0
  A set of label cells
    for each column header:
      in column major order
    rows will be limited to 4-9 inclusive
  Line 10 is blank.
  The remaining records to the EOF record
    contain the output data in row major order.
  row 11 is the first record

  LOTUS_EOF record
*/

#include "corn/format/spreadsheet/biff.h"
#include "rptoptns.h"
#include "fmt_param.h"
#include "cs_glob.h"

#define FIRST_HEADER_LINE_ROW 0
#define FIRST_COLUMN_HEADER_LINE_ROW 5
#define FIRST_DATA_LINE_ROW 11

// NOTE: I have a more updated set of classes for creating BIFF format (Excel) files.
// If I ever decide to redo the report write I may want to use these.
// (see CORN\format\Excel)
//______________________________________________________________________________
class Report_writer
#ifdef SOILR
: public std::ofstream
#else
: public Biff_file
#endif
{public:
   Report_options report_options;                                                //001114
public:
   Report_writer
      (const char *filename                                                      //030110
      ,const Report_options &options_to_copy                                     //981203
      ,nat16 maximum_rows);                                                      //981203
   ~Report_writer();
   void write_header(const std::string &line1, const std::string &line2, const std::string &line3, const std::string &line4);  //981211
   void write_column_header
      (report_var_layout_with_graph *var_layout
      ,int top_line_row,std::string top_line);
   void write_grouped_column_header
      (group_report_var_layout &var_layout,int top_line_row);
   void write_integer(int16 value , int8 width );
   void write_real(float64 value , int8 width, int8 precision);
   virtual void write_string_aligned(CSS_justifications alignment,const std::string &value);  //001116
   void endl();
};
#ifdef REPORT_READER_CLASS_USED
This class is not currently used it will be replaced with format convertor.
class report_reader_class : public WKS_input_file
{public:
   report_reader_class(File_name filename)
   :WKS_input_file(filename) {};

   void rewind();

   // read header should only be called only immediatly after open
   std::string &read_header(std::string &line1, std::string &line2, std::string &line3,std::string &line4 ,std::string &buffer);
   void skip_header();

   /// read_column_header should only be called after read_header
   std::string &read_column_header(int column_number ,std::string &line1, std::string &line2, std::string &line3, std::string &line4, std::string &units , std::string &buffer);
   void skip_column_headers();

     // read_cell should only be called after reading the column headers.
     //  returns falls if next cell is not on the specified row.
    bool read_cell(int on_row );
   bool read_cell_at(int on_row , int  at_col);
    report_reader_class();
};
//______________________________________________________________________________
#endif
#endif
#endif
//rprtclss.h

