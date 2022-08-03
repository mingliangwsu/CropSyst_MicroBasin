#ifdef USE_PCH
#  include <corn/corn_pch.h>
#else
#  pragma hdrstop
#  include <stdio.h>
#  include "corn/math/compare.h"
#endif
#include "corn/format/spreadsheet/css_file.h"
using namespace CORN;

//______________________________________________________________________________
Common_spreadsheet_file::Common_spreadsheet_file
(const char *i_filename
,std::ios_base::openmode _openmode)                                              //111108
: Old_binary_record_file(i_filename,false,false,_openmode)                       //990412
, col(0)
, row(0)
, max_col(0)
, max_row(0)
, int_value(0)
, data_type(not_data)
, float_value(0.0)
, precision(2)
#ifdef USE_CORN_DATES
, date_value(0L)
#endif
{};
//_1998?________________________________________________________________________
Common_spreadsheet_file::Common_spreadsheet_file
(const char *i_filename                                                           //000211
,sint32 first_row  ,sint32 rows                                                   //090618
,int16 first_col   ,int16 cols  )
: Old_binary_record_file(i_filename,false,false,std::ios_base::out)   //111108
, col(first_col)                                                                  //090618
, row(first_row)                                                                  //090618
, max_col(0)
, max_row(0)
, int_value(0)
, data_type(not_data)
, float_value(0.0)
, precision(2)
#ifdef USE_CORN_DATES
, date_value(0L)
#endif
{  initialize();                                                                     //990331
};
//_1998?________________________________________________________________________
void Common_spreadsheet_file::initialize()
{  for (int _col = 0; _col < MAX_COLUMNS; _col++)                                   //021216
      column_widths[_col] = 8;
};
//_1999-03-21___________________________________________________________________
void Common_spreadsheet_file::update_extent(int16 i_column,int16 i_row)
{  // record the maximum extent of the sheet
   max_col = CORN_max(max_col,i_column);
   max_row = CORN_max(max_row,i_row);
};
//_1998?________________________________________________________________________
void Common_spreadsheet_file::write_integer_cell
(int16 _column
,int16 _row
,int16 _value)
{  update_extent(_column,_row); };
//_1998?________________________________________________________________________
void Common_spreadsheet_file::write_number_cell
(int16 _column
,int16 _row
,float64 _value
,int8  _precision)
{  update_extent(_column,_row); };
//_1998?________________________________________________________________________
void Common_spreadsheet_file::write_label_cell
(int16 _column
,int16 _row
,CSS_justifications _alignment
,const char *_value)                                                             //030120
{  update_extent(_column,_row); };
//_1998?________________________________________________________________________
void Common_spreadsheet_file::read_number_cell(bool expect_header)
{  update_extent(col,row); };
//_1998?________________________________________________________________________
void Common_spreadsheet_file::read_integer_cell(bool expect_header)
{  update_extent(col,row); };
//_1998?________________________________________________________________________
void Common_spreadsheet_file::read_label_cell(bool expect_header)
{  update_extent(col,row); };
//_1998-10=81___________________________________________________________________
// The following function output a spreadsheet cell of the respective data type.}
void Common_spreadsheet_file::write_integer(int16 value , int16 width)
{  write_integer_cell(col,row,value);
   col++;
};
//_1998-09-15___________________________________________________________________
void Common_spreadsheet_file::write_real(float64 value , int8 width , int8 _precision)
{  write_number_cell(col,row,value,_precision);
   col++;
};
//_1998-09-15___________________________________________________________________
void Common_spreadsheet_file::write_string_aligned
(CSS_justifications align ,const char *value)                                    //030120
{  write_label_cell(col,row,align,value);
   col++;
};
//_2002-12-16___________________________________________________________________
void Common_spreadsheet_file::endl()
{  col = 0; row++; };
//_1998?________________________________________________________________________
char *Common_spreadsheet_file::cell_text_string(char *buffer)
{  switch (data_type)
   { // this should be expanded for the various cell formats
      case   type_integer : sprintf(buffer,"%*d",column_widths[col],int_value); break;
      case   type_float   : sprintf(buffer,"%*.*f",column_widths[col],precision,(float)float_value); break;
      case   type_str     : sprintf(buffer,"%*s",column_widths[col],cstr_value); break;
      case   type_date    : // not currently handling dates (don't know date format);
      break;
      default : sprintf(buffer,"%*s",column_widths[col]," "); break;
   };
   return buffer;
};
//_1998?________________________________________________________________________
bool Common_spreadsheet_file::reset()                               performs_IO_
{  is_at_eof = 0;
   //clear(); /*Clear rdstate flags */                                             //111111
   seek(0);
   return true;                                                                  //120805
};
//______________________________________________________________________________
