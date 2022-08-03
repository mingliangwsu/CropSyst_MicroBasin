#include "corn/format/spreadsheet/biff.h"
nat16 Biff_file::get_BOF_code() const {return BIFF578_CODE_BOF; }
nat16 Biff_file::get_EOF_code() const {return BIFF234578_CODE_EOF; }             //981016
/*
Information on this format based on text provided by
       Mark O'Brien
          Microsoft Corporation
        18-Feb-1988
See also OpenOffice documentation: http://sc.openoffice.org/excelfileformat.pdf
//______________________________________________________________________________

http://support.microsoft.com/kb/147732
The records listed below must be included in order for Microsoft Excel to
recognize the file as a valid BIFF5 file. Because BIFF5 files are OLE compound document files,
these records must be written using OLE library functions.
For information on how to output an OLE docfile, see the OLE 2 Programmer's Reference Volume One.
BOF - Set the 6 byte offset to 0x0005 (workbook globals)
Window1
FONT - At least five of these records must be included
XF - At least 15 Style XF records and 1 Cell XF record must be included
STYLE
BOUNDSHEET - Include one BOUNDSHEET record per worksheet
EOF
BOF - Set the 6 byte offset to 0x0010 (worksheet)
INDEX
DIMENSIONS
WINDOW2
EOF
*/

//______________________________________________________________________________
Biff_file::Biff_file(const char *i_filename,std::ios_base::openmode _openmode)   //111108
:Common_spreadsheet_file(i_filename,_openmode)                                   //111108
,BIFF_format(BIFF2) // This will be provided by BOF record  // 090618 was 4      //090618
,has_frozen_panes(false)                                                         //000307
,pane_left_most_column(0)                                                        //000307
,pane_top_most_row(0)                                                            //000307
,pane_active(0)                                                                  //000307
{  read_BOF_record();
}
//_2000-02-11___________________________________________________________________
Biff_file::Biff_file
(const char *     _filename
,sint32 first_row  ,sint32 rows                                                  //090618
,int16 first_col   ,int16 cols
,BIFF_Format      _BIFF_format )                                                 //090618
:Common_spreadsheet_file(_filename ,first_row,rows,first_col , cols )
   ,BIFF_format(_BIFF_format)                                                   //090618
   ,has_frozen_panes(false)                                                      //000307
   ,pane_left_most_column(0)                                                     //000307
   ,pane_top_most_row(0)                                                         //000307
   ,pane_active(0)                                                               //000307
{  write_BOF_record();
   write_dimensions(first_row,rows,first_col,cols);
   //NYI/*100116_*/    write_1904_record();
   initialize();                                                                 //990428
}
//______________________________________________________________________________
void Biff_file::initialize()
{  /* derived classes may override this */
}
//_1998-10-06___________________________________________________________________
void Biff_file::write_end_of_document_records()
{
//NYI       PROTECT
//NYI       WINDOW PROTECT
//NYI       PASSWORD
//NYI       NOTE
//          WINDOW1
   write_window1(0,0,20000,10000,false); // WARNING, Should record max row and column when enountered and put these values here
//          WINDOW2
    write_window2
     (false //{display_formulas}
     ,true  //{display_grid}
     ,true  //{display_headers}
     ,true  //{freeze_window_panes}
     ,true  //{display_zero_values}
     ,0     //{top_visible_row}
     ,0     //{left_visible_row}
     ,true  //{use_default_gridline_color}
     ,0,0,0);//{ Color RGB }
      //NYI       PANE
            write_pane();
      //NYI       SELECTION
      //          EOF
   write_EOF_record();
}
//_1998-10-06___________________________________________________________________
Biff_file::~Biff_file()
{  if (get_open_mode() && std::ios::out)                                         //990412
      write_end_of_document_records();                                           //000307
}
//______________________________________________________________________________
void Biff_file::write_cell_attributes(uint8 attribute_0, uint8 attribute_1 , uint8 attribute_2)
{  write_nat8(attribute_0);  // Was originally unsigned, but I think it needs to be signed
   write_nat8(attribute_1);
   write_nat8(attribute_2);
}
//______________________________________________________________________________
void Biff_file::read_cell_attributes()
{
   /*NYN int8 attribute_0 = */read_nat8();
   int8 attribute_1 = read_nat8();
   /*NYN int8 attribute_2 = */read_nat8();

//NYI          Need to partition out attribute info into cell properties
    alignment = (CSS_justifications)(attribute_1 & 0x07);
}
//______________________________________________________________________________
/* Not yet implemented
Worksheet Record Types in Opcode Order
The following section lists all record types in opcode order.  It gives a specification
and byte-by-byte breakdown of each type.  Note that Excel terminology refers to
spreadsheets or worksheets as "documents."
*/
void Biff_file::write_dimensions
(sint32 first_row, sint32 rows                                                    //090618
,int16 first_col , int16 cols)
{
   switch (BIFF_format)                                                          //090618
   {  case BIFF2 : write_rec_header(BIFF2_CODE_DIMENSIONS,BIFF2_LEN_DIMENSIONS); break;
      case BIFF3 : write_rec_header(BIFF34578_CODE_DIMENSIONS,BIFF345_LEN_DIMENSIONS); break;
      case BIFF4 : case BIFF5 :
                   write_rec_header(BIFF34578_CODE_DIMENSIONS,BIFF345_LEN_DIMENSIONS); break;
      case BIFF8 : write_rec_header(BIFF8_LEN_DIMENSIONS,BIFF345_LEN_DIMENSIONS); break;
   }
   if (BIFF_format >= BIFF8)
   {  write_nat32(first_row); // first row           // These may need to be unsigned!!!!
      write_nat32(rows);      // last row + 1
   }
   else
   {  // Older versions of BIFF only reserve 16 bits for row indices
      write_nat16((nat16)first_row); // first row           // These may need to be unsigned!!!!
      write_nat16((nat16)rows);      // last row + 1
   }
   write_nat16(first_col); // first col
   write_nat16(cols);      // first col + 1
   if (BIFF_format >= BIFF3)                                                     //090618
      write_nat16(0);         // This may be the number of sheet pages???
}
/*
BLANK                       01h                         1d

Record Type: BLANK
Description: Cell with no formula or value
Record Body Length: 7 bytes
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-1        Row
           2-3        Column
           4-6        Cell attributes (rgbAttr) (Table 2-3)
*/
//______________________________________________________________________________
void Biff_file::write_integer_cell
(int16 at_col
,int16 at_row
,int16 value)
{  Common_spreadsheet_file::write_integer_cell(col,row,value);
   write_rec_header(BIFF2_CODE_INTEGER,BIFF_LEN_INTEGER);
   write_nat16((nat16)at_row);
   write_nat16((nat16)at_col);
   write_cell_attributes(BIFF_ATTR0_DEFAULT,BIFF_ATTR1_DEFAULT,BIFF_ATTR2_ALIGN_RIGHT);
   write_nat16(value); // signed!
}
//______________________________________________________________________________
void Biff_file::read_integer_cell(bool expect_header)
{  if (expect_header) read_rec_header();
   row = read_nat16(); // perhaps unsigned?
   col = read_nat16();
   read_cell_attributes();
   int_value = read_nat16(); // signed
   data_type = type_integer;                                                     //981018
   Common_spreadsheet_file::read_integer_cell(expect_header);
}
//______________________________________________________________________________
void Biff_file::write_number_cell
(int16   at_col
,int16   at_row
,float64 value
,int8    precision_decimals)                                                     //980917
{  Common_spreadsheet_file::write_number_cell( col,  row,  value,precision_decimals);
   write_rec_header(BIFF2_CODE_NUMBER,BIFF2_LEN_NUMBER);
   write_nat16(at_row); // perhaps unsigned?
   write_nat16(at_col);
   write_cell_attributes(BIFF_ATTR0_DEFAULT,BIFF_ATTR1_DEFAULT,BIFF_ATTR2_ALIGN_RIGHT);
   write_float64(value);
}
//______________________________________________________________________________
void Biff_file::read_number_cell(bool expect_header)
{  if (expect_header) read_rec_header();
   row = read_nat16(); // perhaps unsigned
   col = read_nat16();
   read_cell_attributes();
   float_value = read_float64();
   data_type = type_float;                                                       //981018
   Common_spreadsheet_file::read_number_cell(expect_header);
}
//______________________________________________________________________________
#ifdef NYI

I don't know how dates were stored in BIFF2, they couldn't have
been stored in an Integer cell because they were 16bit integers
and couldn't be number cells because probably not sufficent precision
and RK records' didn't exist yet.
virtual void write_date_cell
      (int16 at_col
      ,int16 at_row
      ,CSS_justifications alignment
      ,CORN::Date date);
{  CORN::Date epoch((Year)1904,(DOY)1);
   uint32 days_since_epoch
   continue here virtual void write_date_cell
   Date cells are simply the count of the number of days since either
   Jan 0 1900 or Jan 1 1904
   I will preferably use the Jan 1 1904 system because there is a design flaw
   in that Excel did not correctly recognize 1900 as a leap year
   also While logically January 0, 1900 is equivalent to December 31, 1899,
   these systems do not allow users to specify the latter date.
#endif
//_2010-01-16___________________________________________________________________
void Biff_file::write_label_cell
(int16 at_col
,int16 at_row
,CSS_justifications justification_alignment
,const char *value)                                                              //030120
{  Common_spreadsheet_file::write_label_cell(at_col,at_row,justification_alignment,value);
   int32 len = strlen(value);                                                    //030120
   if (len > 0)
   {  write_rec_header(BIFF2_CODE_LABEL,7+len+2);
      write_nat16(at_row); // perhaps unsigned?
      write_nat16(at_col);
      write_cell_attributes(BIFF_ATTR0_DEFAULT,BIFF_ATTR1_DEFAULT,BIFF_ATTR2_ALIGN_LEFT);
      write_c_str(value,ASCII_C8_string,len+2);                                  //100114
   }
}
//______________________________________________________________________________
void Biff_file::read_label_cell(bool expect_header)
{   if (expect_header) read_rec_header();
    row = read_nat16(); // perhaps unsigned?
    col = read_nat16();
    read_cell_attributes();
    int string_length = read_int8();    // perhaps unsigned?
    read_c_str((char *)(&cstr_value),ASCII_string,string_length+1);               //100114
    data_type = type_str;                                                         //981018
    Common_spreadsheet_file::read_label_cell(expect_header);
}
//______________________________________________________________________________
/*
BOOLERR                     05h                         5d

Record Type: BOOLERR
Description: Boolean constant or error value
Record Body Length: 9 bytes
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-1        Row
           2-3        Column
           4-6        Cell attributes (rgbAttr) (Table 2-3)
           7          Boolean or error value
                                Boolean
                                      true                 1
                                      false                0
                                Error
                                      #NULL!               0
                                      #DIV/0!              7
                                      #VALUE!              0Fh
                                      #REF!                17h
                                      #NAME?               1Dh
                                      #NUM!                24h
                                      #N/A                 2Ah
           8          Specifies Boolean or error
                                Boolean                    0
                                Error                      1

FORMULA                     06h                         6d

Record Type: FORMULA
Description: Name, size, and contents of a formula cell
Record Body Length: 17-272 bytes
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-1        Row
           2-3        Column
           4-6        Cell attributes (rgbAttr) (see Table 2-3)
           7          Current value of formula (IEEE format, see Appendix A)
           15         Recalc flag
           16         Length of parsed expression
           17         Parsed expression
If a formula must be recalculated whenever it is loaded, the recalc flag (byte 15) must
be set.  Any nonzero value is a set recalc flag.  However, a flag value of 3 indicates
that the cell is a part of a matrix, and the entire matrix must be recalculated. Bytes 7
through 14 may contain a number, a Boolean value, an error code, or a string.  The
following tables apply.
Case 1: Bytes 7 - 14 contain a Boolean value.
     Byte Number     Byte Description          Contents (hex)
           7         otBool                          1
           8         Reserved                        0
           9         Boolean value
           10-12     Reserved                        0
           13-14     fExprO                          FFFFh
Case 2: Bytes 7 - 14 contain an error code.
     Byte Number     Byte Description          Contents (hex)
           7         otErr                           2
           8         Reserved                        0
           9         error code
           10-12     Reserved                        0
           13-14     fExprO                          FFFFh
Case 3: Bytes 7 - 14 contain a string.
     Byte Number     Byte Description          Contents (hex)
           7         otString                        0
           8-12      Reserved                        0
           13-14     fExprO                          FFFFh
The string value itself is not stored in the field, but rather in a separate record of
the STRING type.
STRING                      07h                         7d

Record Type: STRING
Description: Value of a string in a formula
Record Body Length: variable
Record Body Byte Structure:
      Byte Number     Byte Description           Contents (hex)
           0          Length of the string
           1-256 (max) The string itself
The STRING record appears immediately after the FORMULA record that evaluates to the
string, unless the formula is in an array.  In that case, the string record immediately
follows the ARRAY record.
ROW                         08h                         8d

Record Type: ROW
Description: Specifies a spreadsheet row
Record Body Length: 16 bytes
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-1        Row number
           2-3        First defined column in the row
           4-5        Last defined column in the row plus 1
           6-7        Row height
           8-9        RESERVED                                0
           10         Default cell attributes byte
                      Default attributes                      1
                      Not default attributes                  0
           11-12      Offset to cell records for this row
           13-15      Cell attributes (rgbAttr) (see Table 2-3)
*/
//______________________________________________________________________________
void Biff_file::write_BOF_record()
{
#define        BIFF_VERSION_EXCEL         0x0002
#define        BIFF_VERSION_MULTIPLAN     0x0003
#define        BIFF_DOCTYPE_WORKSHEET     0x0010
#define        BIFF_DOCTYPE_CHART         0x0020
#define        BIFF_DOCTYPE_MACROSHEET    0x0040
#define        BIFF_DOCTYPE_WORKSPACE     0x0100
   // Workspace is only in BIFF3W BIFF4W and BIFF5W
   switch (BIFF_format)                                                          //090618
   {  case BIFF2 :         write_rec_header(BIFF2_CODE_BOF,BIFF2_LEN_BOF);  write_nat16(0x0000); break;  // BIFF version not used in earlier vesion (assuming 0)
      case BIFF3 :         write_rec_header(BIFF3_CODE_BOF,BIFF34_LEN_BOF); write_nat16(0x0000); break;  // BIFF version not used in earlier vesion (assuming 0)
      case BIFF4 :         write_rec_header(BIFF4_CODE_BOF,BIFF34_LEN_BOF); write_nat16(0x0000); break;  // BIFF version not used in earlier vesion (assuming 0)
      case BIFF5 : BIFF7 : write_rec_header(BIFF578_CODE_BOF,BIFF57_LEN_BOF); write_nat16(0x0500); break;  // BIFF version (always 0500H for BIFF5). Should only be used, if this record is the leading workbook globals BOF.
      case BIFF8 :         write_rec_header(BIFF578_CODE_BOF,BIFF8_LEN_BOF);  write_nat16(0x0600); break;  // BIFF version (always 0600H for BIFF8)
    //default :            write_rec_header(BIFF5_CODE_BOF,BIFF8_LEN_BOF);  write_nat16(0x0000); break;  // BIFF version not used in earlier vesion (assuming 0)
   }
   write_nat16(BIFF_DOCTYPE_WORKSHEET);
   if (BIFF_format > BIFF2)                                                      //090618
   {  write_nat16(BIFF_format > BIFF5 ? 1 : 0);  // Build identifier type not used until BIFF 5 when it must not be 0 (I presume it was 0 for BIFF3 and BIFF4).
      if (BIFF_format >= BIFF5)
         write_nat16(2009); // Build year (must not be 0)
      if (BIFF_format == BIFF8)
      {  write_nat32(0);  // File history flags (I don't know what values to use here
         write_nat32(5);  // Lowest Excel version that can read all records in this file.  (currently I have only implement Excel 5? format so I presume 5 for this code).
      }
   }
}
//______________________________________________________________________________
bool Biff_file::read_BOF_record()
{
   read_rec_header();
   nat16 reccode = get_code();                                                    //990111
   switch (reccode & 0x00FF)
   {
    case  0x00 : BIFF_format = BIFF2; break;
    case  0x02 : BIFF_format = BIFF3; break;
    case  0x04 : BIFF_format = BIFF4; break;
    case  0x08 : BIFF_format = BIFF5; break; // BIFF5 BIFF7 BIFF8
   }
   if (reccode == BIFF578_CODE_BOF)
   {
      nat16 vers = read_nat16();
      if (vers == 0x0600)
            BIFF_format = BIFF8;
      if (vers == 0x0500)
            BIFF_format = BIFF5; // BIFF5 or BIFF7
   }
   if (BIFF_format > BIFF2)
   {
      // Currently not doing anything with the following
      /* nat16 substreamtype = */ read_nat16();   // substream/document type is not currently used
      if (BIFF_format >= BIFF5)
      {
         /* build_id       = */ read_nat16();   // build_ID not currently used
         /* build_year     = */ read_nat16();   // build_year not currently used
      }
      if (BIFF_format == BIFF8)
      {
         /* history_flags        = */ read_nat32(); // history_flags         not currently used
         /* lowest_BIFF_version = */ read_nat32();   //lowest_BIFF_version    not currently used
      }
   }
   return BIFF_format; // ((reccode & 0xFF) == 0x09);  // 081212 probably should be:  return good();
}
//_2009-06-18_2000-03-07________________________________________________________
void Biff_file::write_EOF_record()
{  write_rec_header(BIFF234578_CODE_EOF,BIFF_LEN_EOF);
}
//______________________________________________________________________________
/*
Record Type: INDEX
Description: Contains pointers to other records in the BIFF file, and defines the range
of rows used by the document.  It is used to simplify searching a file for a particular
cell or name.
Record Body Length: variable
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-3        Absolute file position of first NAME record
           4-5        First row that exists
           6-7        Last row that exists plus 1
           8-on       Array of absolute file positions of the
                      blocks of ROW records.
The INDEX record is optional.  If present, it must immediately follow the FILEPASS
record.  IF there is no FILEPASS record, it must follow the BOF record.
CALCCOUNT                   0Ch                         12d

Record Type: CALCCOUNT
Description: Specifies the iteration count
Record Body Length: 2
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-1        Iteration Count
CALCMODE                    0Dh                         13d

Record Type: CALCMODE
Description: Specifies the calculation mode
Record Body Length: 2
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-1        Calculation mode
                        Manual                           0
                        Automatic                        1
                        Automatic except tables          2 ?
                        Automatic, no tables            -1
PRECISION                   0Eh                         14d

Record Type: PRECISION
Description: Specifies precision of calculations for document
Record Body Length: 2
Record Body Byte Structure:
      Byte Number     Byte Description               Contents (hex)
           0-1        Document precision
                        precision as displayed           0
                        full precision                   1
REFMODE                     0Fh                         15d

Record Type: REFMODE
Description: Specifies location reference mode
Record Body Length: 2
Record Body Byte Structure:
      Byte Number     Byte Description            Contents (hex)
          0-1         Reference mode
                        R1C1 mode                      0
                        A1 mode                        1
DELTA                       10h                         16d

Record Type: DELTA
Description: Maximum change for an iterative model
Record Body Length: 8
Record Body Byte Structure:
      Byte Number           Byte Description      Contents (hex)
          0-7               Maximum change (IEEE format, see Appendix A)
ITERATION                   11h                         17d

Record Type: ITERATION
Description: Specifies whether iteration is on
Record Body Length: 2
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Iteration flag
                              Iteration off               0
                              Iteration on                1
PROTECT                     12h                         18d

Record Type: PROTECT
Description: Specifies whether the document is protected with a document password
Record Body Length: 2
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Document protection
                              Not protected               0
                              Protected                   1
PASSWORD                    13h                         19d

Record Type: PASSWORD
Description: Contains encrypted document password
Record Body Length: 2
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Encrypted password
HEADER                      14h                         20d

Record Type: HEADER
Description: Specifies header string that appears at the top of every page when the
document is printed
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
           0                Length of string (bytes)
         1-on               Header string (ASCII)
FOOTER                      15h                         21d

Record Type: FOOTER
Description: Specifies footer string that appears at the bottom of every page when the
document is printed
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0                 Length of string (bytes)
        1-on                Footer string (ASCII)
EXTERNCOUNT                 16h                         22d

Record Type: EXTERNCOUNT
Description: Specifies the number of documents referenced externally by an Excel
document
Record Body Length: 2
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Number of externally referenced documents
EXTERNSHEET                 17h                         23d

Record Type: EXTERNSHEET
Description: Specifies a document that is referenced externally by the Excel file.
There must be an EXTERNSHEET record for every external file counted by the EXTERNCOUNT
record.
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
           0                Length of document name
          1-on              Document name
The document name may be encoded.  If so, its first character will be 0, 1 or 2.
0 indicates the document name is an external reference to an empty sheet.
1 indicates the document name has been translated to a less sys-tem-dependent name.
This feature is valuable for documents intended for a non-DOS environment.
2 indicates that the externally referenced document is, in fact, the current document.
NAME                        18h                         24d

Record Type: NAME
Description: User-defined name on the document
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description              Contents (hex)
           0                Name attribute
                              Only bits 1 and 2 are ever nonzero.

                              Bit 1 is 1 if the name is a function or
                              command name on a macro sheet.

                              Bit 2 is 1 if the name definition
                              includes:
                              * A function that returns an array, such
                                 as TREND or MINVERSE
                              * A ROW or COLUMN function
                              * A user-defined function

                            Name attribute
                              Meaningful only if bit 1 of
                              byte 0 is 1 (the name is a function or
                              command name).  Only bits 0 and 1 are
                              ever nonzero.

                              Bit 0 is 1 if the name is a function.

                              Bit 1 is 1 if the name is a command.

           2                Keyboard shortcut.  Meaningful only if the
                            name is a command.
                              If no keyboard shortcut     0
                              If shortcut exists          ASCII value

           3                Length of the name text
           4                Length of the name's definition
           5-?              Text of the name
           ?-?              Name's definition (parsed) in internal
                            compressed format
           ?                Length of the name's definition (duplicate)
All NAME records should appear together in a BIFF file.
WINDOW PROTECT              19h                         25d

Record Type: WINDOW PROTECT
Description: Specifies whether a document's windows are protected
Record Body Length: 2 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Window protect flag
                            Not protected                 0
                            Protected                     1
VERTICAL PAGE BREAKS        1Ah                          26d

Record Type: VERTICAL PAGE BREAKS
Description: Lists all column page breaks
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Number of page breaks
          2-on              Array containing a 2-byte integer for each
                            column that immediately follows a column page
                            break.  Columns must be sorted in ascending
                            order.
HORIZONTAL PAGE BREAKS      1Bh                         27d

Record Type: HORIZONTAL PAGE BREAKS
Description: Lists all row page breaks
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Number of page breaks
          2-on              Array containing a 2-byte integer for each
                            row that immediately follows a row page
                            break.  Rows must be sorted in ascending
                            order.
NOTE                        1Ch                         28d

Record Type: NOTE
Description: Note associated with a cell
Record Body Length: Variable, maximum of 254
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Row of the note
          2-3               Column of the note
          4-5               Length of the note part of the record
          6-on               Text of the note
Notes longer than 2048 characters must be split among multiple records.  All except the
last one will contain 2048 text characters.  The last one will contain the overflow.
SELECTION                   1Dh                         29d

Record Type: SELECTION
Description: Specifies which cells are selected in a pane of a split window.  It can
also specify selected cells in a window that is not split.
Record Body Length: Variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
           0                Number of pane
                              bottom right                0
                              top right                   1
                              bottom left                 2
                              top left                    3
                              no splits                   3
          1-2               Row number of the active cell
          3-4               Column number of the active cell
          5-6               Reference number of the active cell
          7-8               Number of references in the selection
          9-on              Array of references
Each reference in the array consists of 6 bytes arranged as follows:
      Byte Number           Byte Description
          0-1               First row in the reference
          2-3               Last row in the reference
           4                First column in the reference
           5                Last column in the reference

FORMAT                      1Eh                         30d

Record Type: FORMAT
Description: Describes a picture format in a document.  All FORMAT records must appear
together in a BIFF file.
Record Body Length: Variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
           0                Length of format string
          1-on              Picture format string
FORMATCOUNT                 1Fh                         31d

Record Type: FORMATCOUNT
Description: The number of standard FORMAT records in the file.  There are 21 different
format records.
Record Body Length: 2 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Number of built in format records.
COLUMN DEFAULT              20h                         32d

Record Type: COLUMN DEFAULT
Description: Specifies default cell attributes for cells in a particular column.  The
default value is overriden for individual cells by a subsequent explicit definition.
Record Body Length: Variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Column number of first column for which a
                              default cell is being defined
          2-3               Column number of last column for which a
                              default cell is being defined, plus 1.
          4-on              Array of cell attributes
ARRAY                       21h                         33d

Record Type: ARRAY
Description: Describes a formula entered into a range of cells as an array.  Occurs
immediately after the FORMULA record for the upper left corner of the array.
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description              Contents (hex)
          0-1               First row of the array
          2-3               Last row of the array
           4                First column of the array
           5                Last column of the array
           6                Recalculation flag
                              Array is calculated             0
                              Needs to be calculated         nonzero
           7                Length of parsed expression
          8-on              Parsed expression (array formula)
*/
//______________________________________________________________________________
#ifdef NYI
void Biff_file::write_1904_record(bool date_mode_1904)
{
   write_rec_header(BIFF234578_CODE_1904,2);
   write_nat16(date_mode_1904 ? 1 : 0);  // perhaps unsigned?
}
//_2010-01-16___________________________________________________________________
#endif
/*
EXTERNNAME                  23h                         35d

Record Type: EXTERNNAME
Description: An externally referenced name, referring to a work-sheet or macro sheet or
to a DDE topic.  All EXTERNNAME records associated with a supporting document must
directly follow its EXTERNSHEET record.
Record Body Length: Variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
           0                Length of the name
          1-on              The name
When EXTERNNAME references a DDE topic, Excel may append its most recent values to the
EXTERNNAME record.  If the record becomes too long to be contained in a single record,
it is split into multiple records, with CONTINUE records holding the excess.
COLWIDTH                    24h                         36d
*/
//______________________________________________________________________________
void Biff_file::write_col_width(int16 from_col, int16 to_col , int16 col_width_in_chars )
{
// write_rec_header(BIFF_CODE_COLWIDTH,BIFF_LEN_COLWIDTH);
// write_byte(from_col);  { Not sure why BIFF uses bytes and not chars
// write_byte(to_col);
// write_int16(col_width_in_chars * 256);
}
//_1998-10-06___________________________________________________________________
/*
DEFAULT ROW HEIGHT          25h                         37d

Record Type: DEFAULT ROW HEIGHT
Description: Specifies the height of all rows that are not defined explicitly
Record Body Length: 2 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents  (hex)
          0-1               Default row height in units of 1/20th of a
                            point
LEFT MARGIN                 26h                          38d

Record Type: LEFT MARGIN
Description: Specifies the left margin in inches when the document is printed
Record Body Length: 8 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-7               Left margin (IEEE format, see Appendix A)
RIGHT MARGIN                27h                         39d

Record Type: RIGHT MARGIN
Description: Specifies the right margin in inches when the document is printed
Record Body Length: 8 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-7               Right margin (IEEE format, see Appendix A)
TOP MARGIN                  28h                         40d

Record Type: TOP MARGIN
Description: Specifies the top margin in inches when the document is printed
Record Body Length: 8 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-7               Top margin (IEEE format, see Appendix A)
BOTTOM MARGIN               29h                         41d

Record Type: BOTTOM MARGIN
Description: Specifies the bottom margin in inches when the document is printed
Record Body Length: 8 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-7               Bottom margin (IEEE format, see Appendix A)
PRINT ROW HEADERS           2Ah                          42d

Record Type: PRINT ROW HEADERS
Description: Flag determines whether to include row and column headers on printout of
document
Record Body Length:
Record Body Byte Structure:
      Byte Number           Byte Description              Contents (hex)
          0-1               Row and Column Header Print Flag
                              Do not print headers             0
                              Print headers                    1
PRINT GRIDLINES             2Bh                         43d

Record Type: PRINT GRIDLINES
Description: Flag determines whether to print gridlines on print-out of document
Record Body Length: 2
Record Body Byte Structure:
      Byte Number           Byte Description              Contents (hex)
          0-1               Gridline Print Flag
                              Do not print gridlines           0
                              Print gridlines                  1
FILEPASS                    2Fh                         47d

Record Type: FILEPASS
Description: Specifies a file password.  If this record is present, the rest of the file
is encrypted.  The file password specified here is distinct from the document password
specified by the PASSWORD record.  If present, the FILEPASS record must immediately
follow the BOF record.
Record Body Length: ?
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-on              ?
FONT                        31h                         49d

Record Type: FONT
Description: Describes an entry in the document's font table.  A document may have up to
4 different fonts, numbered 0 to 3.  Font records are written in the font table in the
order in which they are encountered in the file.
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description              Contents (binary)
          0-1               Height of the font (in 1/20ths of a point)
          2-3               Font Attributes
                              First byte (reserved)             00000000b
                              Second byte
                                Bit 0 - bold                    00000001b
                                Bit 1 - italic                  00000010b
                                Bit 2 - underline               00000100b
                                Bit 3 - strikeout               00001000b
                                Bit 4 - outline                 00010000b BIFF3 on?
                                Bit 5 - shadow                  00100000b BIFF3 on?
                                Bits 6-7 (reserved)
           4                Length of font name
          5-?               Font name
FONT2                    32h                         50d

Record Type: FONT2
Description:  System specific information about the font defined in the previous FONT
record.  The FONT2 record is option-al.
Record Body Length: Variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-on              ?
TABLE                    36h                         54d

Record Type: TABLE
Description: Describes a one-input row or column table created through the Data Table
command
Record Body Length: 12 bytes
Record Body Byte Structure:
      Byte Number           Byte Description              Contents (hex)
          0-1               First row of the table
          2-3               Last row of the table
           4                First column of the table
           5                Last column of the table
           6                Recalculation flag
                              Table is recalculated           0
                              Not recalculated              nonzero
           7                Row or column input table flag
                              Column input table              0
                              Row input table                 1
          8-9               Row of the input cell
          10-11             Column of the input cell
The area given by the first and last rows and columns does not include the outer row or
column, which contains table formulas or input values.  If the input cell is a deleted
reference, the row of the input cell, given by the bytes at offset 8 and 9, is -1.
TABLE2                    37h                         55d

Record Type: TABLE2
Description: Describes a two-input table created by the Data Table command.  It is the
same as the TABLE record, except there is no distinction between a row input table and a
column input table, there are two input cells rather than one, and either may have a
value of -1, indicating a deleted reference.
Record Body Length: 16 bytes
Record Body Byte Structure:
      Byte Number           Byte Description              Contents (hex)
          0-1               First row of the table
          2-3               Last row of the table
           4                First column of the table
           5                Last column of the table
           6                Recalculation flag
                              Table is calculated              0
                              Needs recalculation           nonzero
           7                RESERVED - must be zero            0
          8-9               Row of the row input cell
          10-11             Column of the row input cell
          12-13             Row of the column input cell
          14-15             Column of the column input cell
CONTINUE                    3Ch                         60d

Record Type: CONTINUE
Description: Continuation of FORMULA, ARRAY, or EXTERNNAME records that are too long to
fit in a single record.
Record Body Length: variable
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-on              Parsed expression
*/
//______________________________________________________________________________
void Biff_file::write_window1
(int16 horizontal_pos
,int16 vertical_pos
,int16 width
,int16 height
,bool  hidden)
{  write_rec_header(BIFF234578_CODE_WINDOW1,BIFF_LEN_WINDOW1);
   write_nat16(horizontal_pos);  // perhaps unsigned?
   write_nat16(vertical_pos);    // perhaps unsigned?
   write_nat16(width);           // perhaps unsigned?
   write_nat16(height);          // perhaps unsigned?
   write_nat8(hidden);           // perhaps unsigned?
}
//_1998-10-06___________________________________________________________________
void Biff_file::write_window2
(bool     display_formulas
,bool     display_grid
,bool     display_headers
,bool     //freeze_window_panes
,bool     display_zero_values
,int16    top_visible_row
,int16    left_visible_row
,bool     use_default_gridline_color
,int8     grid_R
,int8     grid_G
,int8     grid_B
)
{  write_rec_header
      (BIFF_format == 2 ? BIFF2_CODE_WINDOW2 : BIFF34578_CODE_WINDOW2
      ,BIFF_format == 2 ? BIFF2_LEN_WINDOW2 :
       BIFF_format == 8 ? BIFF8_LEN_WINDOW2 :
                          BIFF345_LEN_WINDOW2);

   nat16 option_flags =
      //070829 This is not working with MicroSoft Excel Updates:  KB936507 and/or KB936509
      // Hopefully MicroSoft can fix this one day
               // Offset 0
      display_formulas
    | (display_grid << 1)
    | (display_headers << 2)
    | (has_frozen_panes << 3)
    | (display_zero_values << 4)
    | (0 << 5) // NYI default header
    | (0 << 6) // NYI arabic
    | (0 << 7) // NYI outline symbols
    // Offset 1
    | (has_frozen_panes << 8)  // Bit 0 Currently only frozen and no split
    | (1 << 9)                 // Bit 1 NYI sheet tab selected
    | (1 << 10);                // Bit 2 NYI current workbook
#ifdef NOT_APPLICABLE
    // Bits 3-7 are not assigned (As of BiFF 7)
    | (1 << 11) // In BIFF8 WINDOW2 (23Eh), this is fSLV sheet saved while in page break mode
    | (1 << 12)
    | (1 << 13)
    | (1 << 14)
    | (1 << 15)
#endif
   write_nat16(option_flags);
   write_nat16(top_visible_row);
   write_nat16(left_visible_row);
   write_nat32(1); //NYI row_col_grid_color);
/*
//             BIFF8 has additional fields:
               write_nat16 (0); Zoom magnification in page break preview
               write_nat16 (0); Zoom magnification in normal mode
               write_nat32 (0); Reserved
*/


//     write_byte(ORD(display_formulas));
//     write_byte(ORD(display_grid));
//     write_byte(ORD(display_headers));
//     write_byte(ORD(freeze_window_panes));
//     write_byte(ORD(display_zero_values));
//     write_int16(top_visible_row);
//     write_int16(left_visible_row);
//     write_byte(ORD(use_default_gridline_color));
//     write_byte(0);
//     write_byte(0);
//     write_byte(0);
//     write_byte(0);
}
//_1998-10-06___________________________________________________________________
/*
BACKUP                    40h                         64d

Record Type: BACKUP
Description: Specifies whether a BIFF file should be backed up
Record Body Length: 2 bytes
Record Body Byte Structure:
      Byte Number           Byte Description         Contents (hex)
          0-1               Backup flag
                              Do not back up              0
                              Back up                     1
*/
//______________________________________________________________________________
void Biff_file::freeze_pane(int16 i_left_most_column , int16 i_top_most_row  )
{
//             Later we may add multiple panes (excel can handle it)
//             In that case we will return the current pane number.
//             Now we just have one pane.
               has_frozen_panes = true;
               pane_left_most_column = i_left_most_column;
               pane_top_most_row =i_top_most_row;
               pane_active = 0; // lower right
//NYI             write_pane(1,1,top_most_row,left_most_column,0);  {Excel gives some data may be lost}
}
//_1998-10-06___________________________________________________________________
void Biff_file::write_pane()
{
   write_rec_header(BIFF234578_CODE_PANE,BIFF_LEN_PANE);
   write_nat16(pane_left_most_column); // perhaps should be unsigned
   write_nat16(pane_top_most_row);     // perhaps should be unsigned
   write_nat16(pane_top_most_row);     // perhaps should be unsigned
   write_nat16(pane_left_most_column); // perhaps should be unsigned
   write_nat16(pane_active);           // perhaps should be unsigned
}
//_1998-10-06___________________________________________________________________

/* BIFF4_CODE_BOOLERR

   Error values
     0x00:#NULL!
     0x07:#DIV/0!
     0x0F:#VALUE!
     0x17:#REF!
     0x1D:#NAME?
     0x24:#NUM!
     0x2A:#N/A
   BOOL values
      0?    : #TRUE
      1?    : #FALSE
*/
///////////////////////////////////////////////////////////////////////////////
//______________________________________________________________________________
int16 Biff_file::read_record()
{  rec_code = read_rec_header();
   switch (rec_code)                                                             //981016
   {  case BIFF2_CODE_INTEGER :  read_integer_cell();    break;
      case BIFF2_CODE_NUMBER :   read_number_cell();     break;
      case BIFF2_CODE_LABEL :    read_label_cell();      break;                  //981018
//    case BIFF_CODE_COLW1 :    data_type = not_data; read_column_width();    break;
//    case BIFF_CODE_MARGINS :  data_type = not_data; read_margins();         break;
//    case BIFF_CODE_HEADER:    data_type = not_data; read_header(242);          break;
//    case BIFF_CODE_PRANGE:    data_type = not_data; read_print_range();     break;
      default :  // Don't know what this record is ignore it
      { // We also don't do anything with:
       // WKS_CODE_BOF
       // WKS_CODE_EOF
         if (rec_code == BIFF234578_CODE_EOF)
            is_at_eof = 1;
         data_type = not_data;
         read_unknown_record_data();                                             //981016
      }
      break;
   }
  return rec_code;                                                               //981016
}
//______________________________________________________________________________
Common_spreadsheet_file::Record_type Biff_file::read_next(Common_spreadsheet_file::Record_type filter_type)
{  Common_spreadsheet_file::Record_type rec_type = unknown_record;
   nat16 last_position = 0;                                                     //990412
   nat16 curr_position = tell();                                               //070622_990412
   do
   {  last_position = curr_position;
      int16 rec_code_read =  read_record();
      curr_position = tell();                                                     //070622_990412
      switch (rec_code_read)
      {
        case BIFF2_CODE_BOF :  case BIFF3_CODE_BOF :
        case BIFF4_CODE_BOF :  case BIFF578_CODE_BOF :
           rec_type = BOF_record;
        break;
        case BIFF2_CODE_DIMENSIONS :      case BIFF34578_CODE_DIMENSIONS :       //090618
        case BIFF2_CODE_FORMATCOUNT :     case BIFF23_CODE_FORMAT : case BIFF4578_CODE_FORMAT :
        case BIFF2_CODE_COLUMN_DEFAULT :
        case BIFF234578_CODE_1904 :
        case BIFF2_CODE_TABLE :           case BIFF34578_CODE_TABLE : case BIFF2_CODE_TABLE2 :
        case BIFF234578_CODE_WINDOW1 :    case BIFF2_CODE_WINDOW2 : case  BIFF34578_CODE_WINDOW2 :
        case BIFF234578_CODE_PANE :

        case BIFF2_CODE_COLWIDTH :  case BIFF2_CODE_DEFAULT_ROW_HEIGHT :
        case BIFF234578_CODE_LEFT_MARGIN :case BIFF234578_CODE_RIGHT_MARGIN :
        case BIFF234578_CODE_TOP_MARGIN : case BIFF234578_CODE_BOTTOM_MARGIN :
           rec_type = formatting_record;
        break;
        case BIFF2_CODE_ARRAY :     case BIFF34578_CODE_ARRAY :
        case BIFF2_CODE_BLANK :     case BIFF34578_CODE_BLANK :
        case BIFF2_CODE_BOOLERR :   case BIFF34578_CODE_BOOLERR :
        case BIFF2_CODE_LABEL    :  case BIFF34578_CODE_LABEL :
        case BIFF8_CODE_LABELSST : // String constant that uses BIFF8 shared string table (new to BIFF8)
        case BIFF2_CODE_NUMBER :    case BIFF34578_CODE_NUMBER :
        case BIFF2_CODE_INTEGER  :
        case BIFF2_CODE_RK :        case BIFF34578_CODE_RK :
        case BIFF2_CODE_STRING :    case BIFF34578_CODE_STRING :  // Cell with character formatting
        case BIFF578_CODE_RSTRING :  // Cell with character formatting

           rec_type = data_cell_record;
        break;
        case BIFF578_CODE_MULBLANK :  //  MULBLANK Multiple empty cells (new to BIFF5)
        case BIFF578_CODE_MULRK :     // Multiple RK numbers (new to BIFF5)
           rec_type = multiple_data_cell_record;
        break;
        case BIFF34_CODE_FORMULA : case BIFF2578_CODE_FORMULA :
        case BIFF578_CODE_SHAREDFMLA :
           rec_type = formula_cell_record;
        break;
        case BIFF234578_CODE_NOTE :
           rec_type = comment_record;
        break;
        case BIFF2_CODE_INDEX :  case BIFF34578_CODE_INDEX :
        case BIFF234578_CODE_CALCCOUNT :  case BIFF234578_CODE_CALCMODE :
        case BIFF234578_CODE_PRECISION :
        case BIFF234578_CODE_REFMODE :
        case BIFF234578_CODE_DELTA :
        case BIFF234578_CODE_ITERATION :
        case BIFF234578_CODE_PROTECT :    case BIFF234578_CODE_PASSWORD :
        case BIFF2345_CODE_EXTERNCOUNT :case BIFF234578_CODE_EXTERNSHEET :
        case BIFF2578_CODE_NAME :
        case BIFF234578_CODE_WINDOW_PROTECT :
        case BIFF234578_CODE_SELECTION :
        case BIFF2578_CODE_EXTERNNAME :
        case BIFF234578_CODE_CONTINUE :
        case BIFF234578_CODE_BACKUP :
           rec_type = control_record;
        break;
        case BIFF234578_CODE_HEADER :  case BIFF234578_CODE_FOOTER :
        case BIFF234578_CODE_VERTICAL_PAGE_BREAKS :
        case BIFF234578_CODE_HORIZONTAL_PAGE_BREAKS :
        case BIFF234578_CODE_PRINT_ROW_HEADERS :
        case BIFF234578_CODE_PRINT_GRIDLINES :
        case BIFF234578_CODE_FILEPASS :
        case BIFF2578_CODE_FONT :    case BIFF2_CODE_FONT2 :
           rec_type = printing_record;
        break;
        case BIFF234578_CODE_EOF :
           rec_type = EOF_record;
        break;
        default :
           rec_type = unknown_record;
        break;
      }
   } while ((rec_type != EOF_record) &&
            ((filter_type != any_record) &&
             (rec_type != filter_type) &&
            (curr_position != last_position)));                                  //990412*
   return rec_type;
}
//_1998-10-16___________________________________________________________________

