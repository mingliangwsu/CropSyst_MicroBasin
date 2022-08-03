
#include <corn/format/WKS_file.h>

#define VAR_LEN = -1;
//___________________________________________________________________________
/*_______*/ Common_spreadsheet_file::Record_type WKS_file::read_next(Common_spreadsheet_file::Record_type filter_type)
/*_______*/ {
/*_______*/       Record_type result = filter_type;
/*_______*/          // NYI  This needs to be implemented as in biff.cpp
/*_______*/       return result;
/*_______*/ };
//___________________________________________________________________________
/*_______*/ int16 WKS_file::read_record()
/*_______*/ {
/*981016_*/    switch (read_rec_header())
/*_______*/    {
/*_______*/      case WKS_CODE_INTEGER :  read_integer_cell();    break;
/*_______*/      case WKS_CODE_NUMBER :   read_number_cell();     break;
/*981018_*/      case WKS_CODE_LABEL :    read_label_cell(/*length-6*/);      break;
/*_______*/      case WKS_CODE_COLW1 :    data_type = not_data; read_column_width();    break;
/*_______*/      case WKS_CODE_MARGINS :  data_type = not_data; read_margins();         break;
/*_______*/      case WKS_CODE_HEADER:    data_type = not_data; read_header(length);    break;
/*_______*/      case WKS_CODE_PRANGE:    data_type = not_data; read_print_range();     break;
/*_______*/
/*_______*/      default :  // Don't know what this record is ignore it
/*_______*/      { // We also don't do anything with:
/*_______*/        // WKS_CODE_BOF
/*_______*/        // WKS_CODE_EOF
/*_______*/        if (rec_code == WKS_CODE_EOF)
/*_______*/           at_eof = 1;
/*_______*/
/*981016_*/        data_type = not_data;
/*981016_*/        read_unknown_record_data();
/*_______*/      }
/*_______*/      break;
/*_______*/    };
/*_______*/
/*981016_*/   return rec_code;
/*_______*/ };
//___________________________________________________________________________
/*981016_*/ void WKS_file::write_BOF_record()
/*_______*/ {
/*_______*/    write_rec_header(WKS_CODE_BOF,WKS_LEN_BOF);
/*_______*/    write_uint16(0x0404); // { Lotus file format}
/*_______*/ };
//___________________________________________________________________________
/*981016_*/ void WKS_file::write_EOF_record()
/*_______*/ {
/*_______*/    write_rec_header(WKS_CODE_EOF,WKS_LEN_EOF);
/*_______*/ };
//___________________________________________________________________________
/*______*/ bool WKS_file::read_BOF_record()
/*______*/ {
/*______*/    read_rec_header();
/*001206*/    WKS_version =read_uint16();
/*______*/    return (rec_code == WKS_CODE_BOF);
/*______*/ };
//___________________________________________________________________________
/* not implemented yet
void WKS_output_file::write_window1
( int16 cursor_col,
  int16 cursor_row,
  byte format,
  int16 col_width,
  int16 cols_screen,
  int16 rows_screen,
  int16 col_left,
  int16 row_top,
  int16 cols_title,
  int16 rows_title,
  int16 col_title,
  int16 row_title,
  int16 col_width_border,
  int16 row_width_border,
  int16 win_width,
)
{
   write_rec_header(outfile,WKS_CODE_WINDOW1,WKS_LEN_WINDOW1);

   put_int16(cursor_col,outfile);
   put_int16(cursor_row,outfile);
   write_byte(format,outfile);
   write_byte(0,outfile);
   put_int16(col_width,outfile);
   put_int16(cols_screen,outfile);
   put_int16(rows_screen,outfile);
   put_int16(col_left,outfile);
   put_int16(row_top,outfile);
   put_int16(cols_title,outfile);
   put_int16(rows_title,outfile);
   put_int16(col_title,outfile);
   put_int16(row_title,outfile);
   put_int16(col_width_border,outfile);
   put_int16(row_width_border,outfile);
   put_int16(win_width,outfile);
   write_byte(0,outfile);
};
/*
void WKS_output_file::write_col_width_win1(int16 column,int16 width)
{
   byte width_byte;

   write_rec_header(WKS_CODE_COLW1,WKS_LEN_COLW1);
   put_int16(column,outfile);
   width_byte := width;
   write_byte(width_byte,outfile);
};
*/
//___________________________________________________________________________
/*_______*/ void  WKS_file::read_header(int16 length)
/*_______*/ {
//obs/*981016_*/    fread(&header,242,1,inoutfile);
/*001205_*/    read((char *)&header,length);
/*_______*/ };
//___________________________________________________________________________
/*_______*/
/*_______*/ void  WKS_file::read_margins()
/*_______*/ {
//obs/*981016_*/    fread(&margins,sizeof(margins_struct),1,this);
/*001205_*/    read((char *)&margins,sizeof(Margins_struct));
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void  WKS_file::read_print_range()
/*_______*/ {
/*_______*/   print_range_enabled = 1;
/*001205_*/   read((char *)&print_range,sizeof(Print_range_struct));
//obs/*981016_*/   fread(&print_range,sizeof(print_range_struct),1,inoutfile);
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void WKS_file::write_column_width(int16 col, int16 width)
/*_______*/ {
/*_______*/    write_rec_header(WKS_CODE_COLW1,WKS_LEN_COLW1);
/*981016_*/    write_sint16(col);
/*981016_*/    write_uint8(width);
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void  WKS_file::read_column_width()
/*_______*/ {
/*981016_*/    int16 col = read_sint16();
/*981016_*/    column_widths[col] = read_uint8();
/*_______*/ };
//___________________________________________________________________________
/*001206_*/ void  WKS_file::read_cell()
/*_______*/ {
/*_______*/    byte format = read_uint8();
/*_______*/    extract_format(format);
/*_______*/    col = read_sint16();
/*_______*/    row = read_sint16();
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void  WKS_file::read_integer_cell(bool expect_header)
/*_______*/ {  //001206obs    Int_cell_struct cell;
//001105obs   fread(&cell,sizeof(int_cell_struct),1,inoutfile);
///*001105*/    read((char *)&cell,sizeof(Int_cell_struct));
//001206obs    extract_format(cell.pos.format);
//001206obs    row = cell.pos.row;
//001206obs    col = cell.pos.col;
//001206obs    int_value = cell.value;
/*001206_*/    read_cell();
/*001206_*/    int_value = read_sint16();
/*_______*/    data_type = type_integer;
/*______*/     Common_spreadsheet_file::read_integer_cell(expect_header);
/*_______*/ };
//___________________________________________________________________________
/*001206_*/ void WKS_file::write_cell(int16 col, int16 row,uint8 format)
/*_______*/ {
/*_______*/    write_uint8(format);
/*_______*/    write_sint16(col);
/*_______*/    write_sint16(row);
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void WKS_file::write_label_cell ( int16 col, int16 row, CSS_justifications i_alignment,const CORN_string &i_value)
/*_______*/ {  Common_spreadsheet_file::write_label_cell(col,row,i_alignment,i_value);
//001206obs   Cell_struct cell;
//001206obs/*_______*/   cell.format = gen_format(0/*not protected*/,WKS_format_special,WKS_special_text);
//001206obs/*_______*/   cell.col = col;
//001206obs/*_______*/   cell.row = row;
/*_______*/   char value[255];
/*_______*/
/*_______*/   strcpy(value,i_value.c_str());
/*_______*/
/*_______*/   int16 len = strlen(value);
/*_______*/   write_rec_header(WKS_CODE_LABEL,5+len+2);
/*001206_*/    write_cell(col,row,gen_format(0/*not protected*/,WKS_format_special,WKS_special_text));
///*_______*/   fwrite(&cell,sizeof(Cell_struct),1,inoutfile);
//001206obs/*001105_*/   write((char *)&cell,sizeof(Cell_struct));
//001205obs/*_______*/   putc(alignment,inoutfile);
//001205obs/*_______*/   fputs(value,inoutfile);
//001205obs/*_______*/   putc(0,inoutfile);
/*_______*/   write_uint8(alignment);
/*_______*/   write(value,strlen(value));
/*_______*/   write_uint8(0);
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void WKS_file::write_integer_cell( int16 col, int16 row, int16 value)
/*_______*/ {  Common_spreadsheet_file::write_integer_cell(col,row,value);
//001206obs    Int_cell_struct cell;
//001206obs    cell.pos.format = WKS_gen_format_integer;
//001206obs    cell.pos.col = col;
//001206obs    cell.pos.row    = row;
//001206obs    cell.value  = value;
/*_______*/
/*_______*/    write_rec_header(WKS_CODE_INTEGER,WKS_LEN_INTEGER);
/*001206_*/    write_cell(col,row,WKS_gen_format_integer);
/*001206_*/    write_sint16(value);
//001205obs    fwrite(&cell,sizeof(int_cell_struct),1,inoutfile);
//001206obs    write((char *)&cell,sizeof(Int_cell_struct));
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void WKS_file::write_number_cell(int16 col, int16 row, double value,int8 precision)
/*_______*/ {  Common_spreadsheet_file::write_number_cell( col,  row,  value,precision);
//001206obs/*_______*/    Double_cell_struct cell;
//001206obs/*_______*/    cell.pos.format = gen_format(0/*not protected*/,WKS_format_fixed,precision);
//001206obs/*_______*/    cell.pos.col = col;
//001206obs/*_______*/    cell.pos.row    = row;
//001206obs/*_______*/    cell.value  = value;
/*_______*/
/*_______*/    write_rec_header(WKS_CODE_NUMBER,WKS_LEN_NUMBER);
/*001206_*/    write_cell(col,row,gen_format(0/*not protected*/,WKS_format_fixed,precision));
/*001206_*/    write_float64(value);
//001205obs/*_______*/    fwrite(&cell,sizeof(double_cell_struct),1,inoutfile);
//001206obs/*_______*/    write((char *)&cell,sizeof(Double_cell_struct));
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void  WKS_file::read_number_cell(bool expect_header)
/*_______*/ {
//001206obs/*_______*/   Double_cell_struct cell;
//001206obs//001205obs/*_______*/   fread(&cell,sizeof(double_cell_struct),1,inoutfile);
//001206obs/*_______*/   read((char *)&cell,sizeof(Double_cell_struct));
//001206obs/*_______*/   extract_format(cell.pos.format);
//001206obs/*_______*/   row = cell.pos.row;
//001206obs/*_______*/   col = cell.pos.col;
//001206obs/*_______*/   float_value = cell.value;
/*001206_*/    read_cell();
/*_______*/    float_value = read_float64();
/*_______*/    data_type = type_float;
/*______*/     Common_spreadsheet_file::read_number_cell(expect_header);
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void  WKS_file::read_label_cell(bool expect_header)
/*_______*/ {  int lngth = length-6; // length includes terminating 0
//001206obs/*_______*/   Cell_struct cell;
//001206obs//001205obs   fread(&cell,sizeof(Cell_struct),1,inoutfile);
//001206obs/*001205*/     read((char *)&cell,sizeof(Cell_struct));
//001206obs/*_______*/   extract_format(cell.format);
//001206obs/*_______*/   row = cell.row;
//001206obs/*_______*/   col = cell.col;

/*001206_*/    read_cell();
//001205obs    alignment = getc(inoutfile);
//001205obs    fread(str_value,1,lngth,inoutfile);
/*_______*/    alignment = read_uint8();
/*_______*/    read((char *)str_value,lngth);
/*_______*/    data_type = type_str;
/*______*/     Common_spreadsheet_file::read_label_cell(expect_header);
/*_______*/ };
//___________________________________________________________________________
/*_______*/ byte WKS_file::gen_format(byte protection, byte format_type, byte decimals_special)
/*_______*/ {
/*_______*/    return  (protection << 7) | (format_type << 4) | decimals_special;
/*_______*/ };
//___________________________________________________________________________
/*_______*/ void WKS_file::extract_format(byte format)
/*_______*/ {                                 // 76543210
/*_______*/   byte protection_mask = 0x80;    // 10000000;
/*_______*/   byte format_mask     = 0x7f;    // 01110000;
/*_______*/   byte precision_mask  = 0x0f;    // 00001111;
/*_______*/
/*_______*/   protection  = ((format & protection_mask) > 0);
/*_______*/   format_type = ((format & format_mask) >> 4);
/*_______*/   if (format == WKS_format_special)
/*_______*/   {
/*_______*/      special_format = precision_mask & format;
/*_______*/      precision = 0;
/*_______*/      switch (special_format)
/*_______*/      {
/*_______*/       case WKS_special_plusminus      : data_type = type_integer; break;
/*_______*/       case WKS_special_general        : data_type = type_integer; break;
/*_______*/       case WKS_special_day_month_year : data_type = type_date; break;
/*_______*/       case WKS_special_day_month      : data_type = type_date; break;
/*_______*/       case WKS_special_month_year     : data_type = type_date; break;
/*_______*/       case WKS_special_text           : data_type = type_str; break;
/*_______*/       default : data_type = type_integer;  break;
/*_______*/      };
/*_______*/   }
/*_______*/   else
/*_______*/   {
/*_______*/      precision = format & precision_mask;
/*_______*/      data_type = type_float;
/*_______*/   }
/*_______*/ };
//___________________________________________________________________________
/*981016_*/ WKS_file::WKS_file(
/*001206*/        const char *i_filename
               )
/*_______*/    : Common_spreadsheet_file(i_filename)
/*_______*/    , protection(false)
/*_______*/    , format_type(WKS_format_fixed)
/*_______*/    , special_format(0)
/*001206*/     , WKS_version(1)
/*_______*/    {
/*_______*/      margins.left = 0;
/*_______*/      margins.right = 0;
/*_______*/      margins.top = 0;
/*_______*/      margins.bottom = 0;
/*_______*/      margins.page_length = 0;
/*_______*/
/*_______*/      print_range.start_col = 0;
/*_______*/      print_range.start_row = 0;
/*_______*/      print_range.end_col   = 0;
/*_______*/      print_range.end_row  = 0;
/*_______*/
/*981016_*/      str_value[0] = 0;
/*981016_*/      header[0] = 0;
//                If the file has length, then it must exists an the first record should be BOF record
/*001206*/        if (get_file_length())
/*_______*/       {
/*981018_*/          at_eof = !read_BOF_record();
/*_______*/       }
/*_______*/    };
//___________________________________________________________________________
//             Constructor for output
/*981016_*/ WKS_file::WKS_file
/*_______*/    (
/*001206*/        const char *i_filename
//001206obs               const CORN_filename &i_filename
/*_______*/       ,int16 i_first_row   ,int16 i_rows
/*_______*/       ,int16 i_first_col   ,int16 i_cols)
/*_______*/    : Common_spreadsheet_file
/*_______*/    (i_filename
/*_______*/    ,i_first_row
/*_______*/    ,i_rows
/*_______*/    ,i_first_col
/*_______*/    ,i_cols)
/*_______*/    , protection(false)
/*_______*/    , format_type(WKS_format_fixed)
/*_______*/    , special_format(0)
/*001206*/     , WKS_version(1)
/*_______*/    {
/*_______*/      margins.left = 0;
/*_______*/      margins.right = 0;
/*_______*/      margins.top = 0;
/*_______*/      margins.bottom = 0;
/*_______*/      margins.page_length = 0;
/*_______*/
/*_______*/      print_range.start_col = 0;
/*_______*/      print_range.start_row = 0;
/*_______*/      print_range.end_col   = 0;
/*_______*/      print_range.end_row  = 0;
/*_______*/
/*981016_*/      str_value[0] = 0;
/*981016_*/      header[0] = 0;
/*981018_*/      write_BOF_record();
/*981018_*/      write_dimensions(i_first_row,i_rows,i_first_col,i_cols);
/*_______*/    };
//___________________________________________________________________________
/*_______*/ int16 WKS_file::get_BOF_code() {return WKS_CODE_BOF;};
/*_______*/ int16 WKS_file::get_EOF_code() {return WKS_CODE_EOF;};
//___________________________________________________________________________
