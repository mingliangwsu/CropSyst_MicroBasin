#include <corn/tabular/tabular_format_identifier.h>
#include <corn/math/compare.hpp>

namespace CORN
{
//______________________________________________________________________________
Text_format_auto_identifier::Text_format_auto_identifier
      (modifiable_ Common_tabular_file_format  &_tabular_file_format
      ,const char *sample_filename)
: tabular_file_format(_tabular_file_format)
,text_file(sample_filename,ios::binary)
{};
//______________________________________________________________________________
bool Text_format_auto_identifier::identify()
{  bool identified = false;
   static const nat16 consider_lines_max = 100;   // Stop after 100 (arbitray) lines.
   static const nat16 consider_lines_alloc = 101;   // Stop after 100 (arbitray) lines.
   static const nat16 consider_char_cols = 1024;   // Stop after 1024 (arbitray) characters (on a line).

   nat16 curr_line=1;       // 1 based
   nat16 curr_char_col=0;  // current character_column   0 based
   nat32 line_count=0;
   nat32 character_count_all[256];
//   nat32 tab_count_all=0;
//   nat32 CR_count_all=0;
//   nat32 LF_count_all=0;

   char   line_type[consider_lines_alloc];                  // Index 0 is not used (1 based)
   // This is the guessed line type
   // 'b'  blank line (absolutely no text on the line)
   // 's'  white space only tabs and white space encountered
   // 'd'  detail data line
   // 'u'  units line
   // 'c'  column header
   // 'h'  abritrary header
   // '-'  separater line
   // 'f'  footer (NYI)

   nat16 character_count[consider_lines_alloc][256];  // This is the count of each character encountered on the line  // Index 0 is not used (1 based)

//   nat16 tab_count[consider_lines];  // The number of tabs encountered on each line.
   // The number of tabs encountered in each line can be useful for counting columns
   // and/or identifying column headers and detail lines in tab delimited files.
//   nat16 period_count[consider_lines];  // The number of decimal points encountered on each line.
   // An matching number of decimal points on continguous lines
   // could indicated data rows.
//   nat16 comma_count[consider_lines];  // The number of decimal points encountered on each line.
   // An matching number of decimal points on continguous lines
   // could indicated data rows.
   nat16 line_length[consider_lines_alloc]; // The length of each line.     // Index 0 is not used (1 based)
   // If lines are all the same length then this is a fixed column format.
   // we presume the later lines are detail lines,
   // so scanning line counts backward, we may be able to identify any
   // header breaks (start of details, and/or column headers)

   char char_type_for_fixed[consider_lines_alloc][consider_char_cols];      // Index 0 is not used (1 based)
   // This matrix encodes the type of characters encountered.
   // This can be used to identified columns and data types.
   // ' ' space
   // '\t' tab
   // 'A' alpha numeric
   // '9' numeric (including commas and periods)

   char periods_for_fixed[consider_lines_alloc][consider_char_cols];         // Index 0 is not used (1 based)
   // This matrix tries to identify decimal points (US style numbers).
   // if all lines have decimal points in the same column this can be used
   // to identified fields, and the start of data.

   char commas_for_fixed[consider_lines_alloc][consider_char_cols];       // Index 0 is not used (1 based)
   // This matrix tries to identify decimal points (European style numbers).
   // if all lines have decimal points in the same column this can be used
   // to identified fields, and the start of data.

   for (int i = 0; i < 256; i++)
         character_count_all[i] = 0;

   for (int l = 0; l <= consider_lines_max; l++)
   {  line_length[l] = 0;
      line_type[l] =0;

//      tab_count[l] = 0;
//      period_count[l] = 0;
//      comma_count[l] = 0;
      for (int i = 0; i < 256; i++)
         character_count[l][i] = 0;
      for (int c = 0; c < consider_char_cols; c++)
      {
          char_type_for_fixed[l][c] = '?';
          periods_for_fixed[l][c] = ' ';
          commas_for_fixed[l][c] = ' ';
      };
   };

   while (!text_file.eof() && (curr_line <= consider_lines_max))   // Stop after 100 (arbitray) lines.
   {
      uint8 char_read;
      text_file.read((char *)(&char_read),sizeof(uint8));
      character_count[curr_line][char_read] ++;
      character_count_all[char_read] ++;

//      tab_count[curr_line] += (char_read == '\t');
//      tab_count_all += (char_read == '\t');
      if (char_read == '.')
      {
         periods_for_fixed[curr_line][curr_char_col]='.';
//         period_count[curr_line] += 1;
      };
      if (char_read == ',')
      {
         commas_for_fixed[curr_line][curr_char_col]=',';
//         comma_count[curr_line] += 1;
      };
      if (char_read == '\n')
      {  line_count ++;
         curr_line ++;
         curr_char_col = 0;
//         LF_count ++;
      } else
      {
         if  (char_read == '\r')
         {
            line_length[curr_line] = curr_char_col;
//            CR_count ++ ;
            // we otherwise ignore carriage return
         }
         else
         {
            line_length[curr_line] = curr_char_col;
            if (char_read == ' ')
               char_type_for_fixed[curr_line][curr_char_col] = ' ';
            else if (char_read == '\t')
               char_type_for_fixed[curr_line][curr_char_col] = '\t';
            else if (isalpha(char_read))
               char_type_for_fixed[curr_line][curr_char_col] = 'A';
            else if (isdigit(char_read))
               char_type_for_fixed[curr_line][curr_char_col] = '9';
            else if ((char_read=='.')||(char_read==','))
               char_type_for_fixed[curr_line][curr_char_col] = '9'; // may be decimal point
            else
               char_type_for_fixed[curr_line][curr_char_col] = '?'; // may be decimal point
            curr_char_col ++;   
         };
      };
   };

   bool may_be_character_delimited = false;
   bool character_delimited = false;
   int last_few_lines = std::max<nat32>(line_count,20);

   {  // Determine if character_delimited
      int last_line_length = line_length[line_count - 1];
      for (int l = line_count - last_few_lines; l < (int)line_count; l++)
      {
         if (line_length[l] != last_line_length) may_be_character_delimited = true; // uneven line lengths usually indicate delimited fields
         if (character_count[l]['\t'] > 0) character_delimited = true;  // must be tab delimited
      };
   };
   tabular_file_format.big_endian = false;
   tabular_file_format.carriage_return_line_feed = (character_count['\r'] > 0);
   tabular_file_format.FORTRAN_carriage_control = false;   // Cannot be determined at this time.
   int16 column_header_start_row = line_count;   // stating with the last line read, search for the first similar apparent data row.
   int16 detail_line_start_row = line_count;   // stating with the last line read, search for the first similar apparent data row.
   int16 units_rows_count = 0;
   int16 units_row_offset = -1;
   int16 column_header_rows = 0;
   {  // Now try to identify row types
      // Presume the last line in the file is a data line
      line_type[line_count-1] = 'd';
      char last_line_examined = 'd';
      for (int l = line_count-2; l > 0; l--)
      {

//if (l == 1)
//cout << "reached" << endl;

         uint8 data_row_semblance_points   = 0;
         uint8 col_header_semblance_points = 0;
         uint8 unit_header_semblance_points = 0;
         if (strlen(char_type_for_fixed[l]) == 0)
         {
               line_type[l] = 'b'; // blank line;
         } else
         {
            int alpha_count = 0;
            int numeric_count = 0;
            int comma_count = 0;
            int period_count = 0;
            bool all_spaces = true;
            for (int c = 0; c <= line_length[l];c++)
            {
               alpha_count   += char_type_for_fixed[l][c] == 'A';
               numeric_count += char_type_for_fixed[l][c] == '9';
               period_count   += periods_for_fixed[l][c] == '.';
               comma_count   += commas_for_fixed[l][c] == ',';
               if (char_type_for_fixed[l][c] != ' ')
                  all_spaces = false;
            };
            if (all_spaces)
               line_type[l] = ' ';
            else
            {
               if (numeric_count > alpha_count) data_row_semblance_points += 1;   // If there are more numbers than letters, then it is probably data line
               else                             col_header_semblance_points += 1;
               if (period_count > 1)  data_row_semblance_points += 1;
               if (comma_count > 1)   { data_row_semblance_points += 1; col_header_semblance_points+= 1; } // comma separated lines are likely either data rows or column header rows
               if (character_count[l]['\t'] > 0) { data_row_semblance_points += 1;   col_header_semblance_points+= 1; }  // tab delimited lines are likely data lines (but could be column headers)
               if (last_line_examined == 'd')
               {  // if the last line adjacent we look at has the same pattern of commas and periods and alphanumerics then probably a data line
                  // Fixed field width
                  if (strcmp(periods_for_fixed[l],periods_for_fixed[l+1]) == 0)
                  {   line_type[l] = 'd'; data_row_semblance_points += 1; };
                     if (strcmp(commas_for_fixed[l],commas_for_fixed[l+1]) == 0)
                  {   line_type[l] = 'd'; data_row_semblance_points += 1; };
                  if (strcmp(char_type_for_fixed[l],char_type_for_fixed[l+1]) == 0)
                  {   line_type[l] = 'd'; data_row_semblance_points += 1; };
               }
               if (data_row_semblance_points >= 3)
                  {
                     detail_line_start_row = std::min<int16>(detail_line_start_row,l);
                     line_type[l] = 'd';
                  }
               else
               {
                  if (line_type[l+1] == 'b') // Sometimes blank lines are used to separate data  from any headers
                     { unit_header_semblance_points += 1; col_header_semblance_points += 1; };
                  if (line_type[l+1] == ' ') // Sometimes white spaces lines are used to separate data  from any headers
                     { unit_header_semblance_points += 1; col_header_semblance_points += 1; };

//NYI                  split the line into words if more than 1 word is a unit maker
//NYI                  if there are any units makers then presume this is a units line
//NYI                     unit_header_semblance_points += 1;

                  if (last_line_examined == 'd')  // units line are usually immediately before data lines
                  {
                     unit_header_semblance_points += 1;
                     col_header_semblance_points += 1;
                  }
                  if (unit_header_semblance_points > col_header_semblance_points)
                  {
                     line_type[l] = 'u';
                     units_rows_count += 1;
                     tabular_file_format.column_headers_delineation.units_parenthesis =
                        (character_count[l]['('] > 0 ) && (character_count[l][')'] > 0 ); 
                  }
                  else
                  {
                     line_type[l] = 'c';
                     column_header_start_row = std::min<int16>(column_header_start_row,l);
                     column_header_rows += 1;
                     units_row_offset += 1;

                  };
               };
            };
         };

   // 's'  white space only tabs and white space encountered
   // 'd'  detail data line
   // 'u'  units line
   // 'c'  column header
   // 'h'  abritrary header
   // 'f'  footer (NYI)
      };
   };

//   tabular_file_format.detail_lines_delineation.relative_to_row_labeled.set(BEGIN_FILE_RELATIVE);  
   tabular_file_format.detail_lines_delineation.start_row_1_based = detail_line_start_row;
//   tabular_file_format.detail_lines_delineation.begin_marker; // Unable to determine presume none
//   tabular_file_format.detail_lines_delineation.end_marker; // Unable to determine presume none
   if (!character_delimited)
   {
      if (may_be_character_delimited)
      {
         if (character_count[detail_line_start_row][';'] > 0)  // check for semicolons, if any, most likely
         {  character_delimited = true;
            tabular_file_format.detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_character);
         }
         else
         {
            if (character_count[detail_line_start_row]['|'] > 0)  // check for |, if any, most likely
               tabular_file_format.detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_character);
         }
      } else
      {
         tabular_file_format.detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_fixed_width);
      };
   };

   if (character_delimited)
   {  tabular_file_format.detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_character);
      tabular_file_format.detail_lines_delineation.delimiter_comma = true; // presume comma delimited unless we find another delimitor
      if (character_count[detail_line_start_row][';'] > 0)  // check for semicolons, if any, most likely
      {
         tabular_file_format.detail_lines_delineation.delimiter_semicolon = true;
         tabular_file_format.detail_lines_delineation.delimiter_comma = false; // presume not both semicolon and tab delimited
      };
      if (character_count[detail_line_start_row]['\t'] > 0)
      {
         tabular_file_format.detail_lines_delineation.delimiter_tab = true;
         tabular_file_format.detail_lines_delineation.delimiter_comma = false; // presume not both comma and tab delimited
      };
//      tabular_file_format.detail_lines_delineation.continuous_delimiter = false; // Treat continuous delimiters as one.  (Currently unable to determine).
//      tabular_file_format.detail_lines_delineation.delimiter_space = false;  // Unable to determine here
//      tabular_file_format.detail_lines_delineation.delimiter_other = false;   // Currently unable to determine here
      //NYI   tabular_file_format.detail_lines_delineation.other_delimiter_16;   // Currently unable to determine here
//      tabular_file_format.detail_lines_delineation.delimiter_string;   // Currently unable to determine here
      //NYI   tabular_file_format.detail_lines_delineation.other_delimiter_string;   // Currently unable to determine here
   }

   // Currently unable to determine alternating quote
   // Probably would need to look at all lines in the file and see if the are occurances of both in the file exclusively in certain lines
   if (character_count[detail_line_start_row]['\"'] > 2)
      tabular_file_format.detail_lines_delineation.text_quote_mode_labeled.set(Delineation_layout::DOUBLE_QUOTE);
   if (character_count[detail_line_start_row]['\''] > 2)
      tabular_file_format.detail_lines_delineation.text_quote_mode_labeled.set(Delineation_layout::SINGLE_QUOTE);

   tabular_file_format.detail_lines_delineation.decimal_mark.assign(".");
   if ((character_count[detail_line_start_row][';'] > 0) && ( character_count[detail_line_start_row][','] > 0))
   { // there are both commas and semicolons in the data lines then decimal must be ,
      tabular_file_format.detail_lines_delineation.decimal_mark.assign(",");
   };
   tabular_file_format.detail_lines_delineation.notes.assign("Deliniation specification is not confirmed");

   // Currently presuming the column headers have the same delineation as the data (probably 99% of the time it is the same)
   // But probably should also do the same checks
   tabular_file_format.column_headers_delineation.relative_to_labeled  .set(tabular_file_format.detail_lines_delineation.relative_to_labeled.get());
   tabular_file_format.column_headers_delineation.start_row_1_based        = column_header_start_row;
   tabular_file_format.column_headers_delineation.begin_marker             = tabular_file_format.detail_lines_delineation.begin_marker;
   tabular_file_format.column_headers_delineation.end_marker               = tabular_file_format.detail_lines_delineation.end_marker;
   tabular_file_format.column_headers_delineation.delimit_mode_labeled     .set(tabular_file_format.detail_lines_delineation.delimit_mode_labeled.get()); // Currently presume the same  delimit mode for column headers (if any)

   tabular_file_format.column_headers_delineation.continuous_delimiter     = tabular_file_format.detail_lines_delineation.continuous_delimiter;
   tabular_file_format.column_headers_delineation.delimiter_space          = tabular_file_format.detail_lines_delineation.delimiter_space;
   tabular_file_format.column_headers_delineation.delimiter_comma          = tabular_file_format.detail_lines_delineation.delimiter_comma;
   tabular_file_format.column_headers_delineation.delimiter_tab            = tabular_file_format.detail_lines_delineation.delimiter_tab;
   tabular_file_format.column_headers_delineation.delimiter_semicolon      = tabular_file_format.detail_lines_delineation.delimiter_semicolon;
   tabular_file_format.column_headers_delineation.delimiter_other          = tabular_file_format.detail_lines_delineation.delimiter_other;
   tabular_file_format.column_headers_delineation.other_delimiter_16       = tabular_file_format.detail_lines_delineation.other_delimiter_16;
   tabular_file_format.column_headers_delineation.delimiter_string         = tabular_file_format.detail_lines_delineation.delimiter_string;
   tabular_file_format.column_headers_delineation.other_delimiter_string   = tabular_file_format.detail_lines_delineation.other_delimiter_string;
   tabular_file_format.column_headers_delineation.text_quote_mode_labeled  .set(tabular_file_format.detail_lines_delineation.text_quote_mode_labeled.get());
   tabular_file_format.column_headers_delineation.decimal_mark             .assign(tabular_file_format.detail_lines_delineation.decimal_mark);
   tabular_file_format.column_headers_delineation.notes                    .assign(tabular_file_format.detail_lines_delineation.notes);

   tabular_file_format.column_headers_delineation.rows = column_header_rows;
   tabular_file_format.column_headers_delineation.units_row_offset = units_row_offset; // Number of rows below the column header start row where units start (relative to column header start row_
   tabular_file_format.column_headers_delineation.units_rows = units_rows_count;

  /*NYI
With the column headers delimited might be able to setup the captions
//             column_headers can have a delineation layout different from the detail lines, but the same options are available
      columns_1based;          // list of Column

   */

/* NYI  May be able to determine this by scanning the
   file colums and searching for some common missing markers
   tabular_file_format.missing_data_marker;  // any codes I.e. -9999 or MISSING used to denote missing data
*/
   return identified;
};
//______________________________________________________________________________
#ifdef NYI
bool dBase_format_auto_identifier::identify()
{  bool identified = false;
   return identified;
};
#endif
//______________________________________________________________________________
#ifdef NYI
Excel_format_auto_identifier::Excel_format_auto_identifier
      (modifiable_ Common_tabular_file_format  &_tabular_file_format
      ,const char *sample_filename)
: tabular_file_format(_tabular_file_format)
{};
//______________________________________________________________________________
#endif

bool Excel_format_auto_identifier::identify(TAdvGridWorkbook *sample_workbook)
{  bool identified = false;

   static const nat16 consider_lines_max = 100;   // Stop after 100 (arbitray) lines.
   static const nat16 consider_lines_alloc = 101;   // Stop after 100 (arbitray) lines.
   static const nat16 consider_cols_max = 100;   // Stop after 1024 (arbitray) characters (on a line).
   static const nat16 consider_cols_alloc = 101;   // Stop after 1024 (arbitray) characters (on a line).

   nat16 curr_line=1;       // 1 based
   nat32 line_count=std::min<int16>(consider_lines_max,sample_workbook->Grid->RowCount);

   char   line_type[consider_lines_alloc];                  // Index 0 is not used (1 based)
   // This is the guessed line type
   // 'b'  blank line (absolutely no text on the line)
   // 's'  white space only tabs and white space encountered
   // 'd'  detail data line
   // 'u'  units line
   // 'c'  column header
   // 'h'  abritrary header
   // '-'  separater line
   // 'f'  footer (NYI)

   for (int l = 0; l <= consider_lines_max; l++)
   {  line_type[l] =0;
   };
   int last_few_lines = std::max<nat32>(line_count,20);

   tabular_file_format.big_endian = false;
   tabular_file_format.carriage_return_line_feed = false;
   tabular_file_format.FORTRAN_carriage_control = false;   // Cannot be determined at this time.

   int16 column_header_start_row = line_count;   // stating with the last line read, search for the first similar apparent data row.
   int16 detail_line_start_row = line_count;   // stating with the last line read, search for the first similar apparent data row.
   int16 units_rows_count = 0;
   int16 units_row_offset = -1;
   int16 column_header_rows = 0;

   char last_line_data_pattern[consider_cols_alloc]; last_line_data_pattern[0] = 0;
   char curr_line_data_pattern[consider_cols_alloc]; curr_line_data_pattern[0] = 0;

   {  // Now try to identify row types
      // Presume the last line in the file is a data line
      line_type[line_count-1] = 'd';
      char last_line_examined = 'd';
      for (int l = line_count-2; l > 0; l--)
      {
         uint8 data_row_semblance_points   = 0;
         uint8 col_header_semblance_points = 0;
         uint8 unit_header_semblance_points = 0;

         int alpha_count = 0;
         int numeric_count = 0;
         bool all_blank = true;
         for (int c = 0; c < sample_workbook->Grid->ColCount; c++)
         {
            AnsiString cell_value_string = sample_workbook->Grid->Cells[c][l];
            if (cell_value_string.Length() > 0)
            {  all_blank = false;
               float cell_float_value = atof(cell_value_string.c_str()); // sample_workbook->Grid->Floats[c][l];
               if (!CORN::is_approximately<float>(cell_float_value,0.0,0.000001))
               {  numeric_count += 1;
                  curr_line_data_pattern[c] = 'n';
               } else
               {  alpha_count += 1;
                  curr_line_data_pattern[c] = 'a';
               };
            } else
                  curr_line_data_pattern[c] = ' ';
            curr_line_data_pattern[c+1] = 0;
         };
         if (all_blank)
               line_type[l] = ' ';
         else
         {  if (numeric_count > alpha_count) data_row_semblance_points += 1;   // If there are more numbers than letters, then it is probably data line
            else                             col_header_semblance_points += 1;
            if (last_line_examined == 'd' )
            {  // if the last line adjacent we look at has the same pattern of numerics
                  // then this is probably a detail line
                  if ((strcmp(curr_line_data_pattern,last_line_data_pattern) == 0)
                      || (last_line_data_pattern[0] == 0)) // This is the first pattern check, assume it is a data row
                        data_row_semblance_points += 1;
                  else
                        col_header_semblance_points += 1;
            }
            if (data_row_semblance_points >= 2)
            {
                     detail_line_start_row = std::min<int16>(detail_line_start_row,l);
                     line_type[l] = 'd';
            } else
            {
               if (line_type[l+1] == 'b') // Sometimes blank lines are used to separate data  from any headers
                     { unit_header_semblance_points += 1; col_header_semblance_points += 1; };
               if (line_type[l+1] == ' ') // Sometimes white spaces lines are used to separate data  from any headers
                     { unit_header_semblance_points += 1; col_header_semblance_points += 1; };

//NYI                  split the line into words if more than 1 word is a unit maker
//NYI                  if there are any units makers then presume this is a units line
//NYI                     unit_header_semblance_points += 1;
               if (last_line_examined == 'd')  // units line are usually immediately before data lines
               {
                     unit_header_semblance_points += 1;
                     col_header_semblance_points += 1;
               }
               if (unit_header_semblance_points > col_header_semblance_points)
               {
                     line_type[l] = 'u';
                     units_rows_count += 1;
//                     tabular_file_format.column_headers_delineation.units_parenthesis =
//                        (character_count[l]['('] > 0 ) && (character_count[l][')'] > 0 );
               }
                  else
               {
                     line_type[l] = 'c';
                     column_header_start_row = std::min<int16>(column_header_start_row,l);
                     column_header_rows += 1;
                     units_row_offset += 1;

               };
            };
         };
         strcpy(last_line_data_pattern,curr_line_data_pattern);
      };

   // 's'  white space only tabs and white space encountered
   // 'd'  detail data line
   // 'u'  units line
   // 'c'  column header
   // 'h'  abritrary header
   // 'f'  footer (NYI)
   };
   tabular_file_format.detail_lines_delineation.start_row_1_based = detail_line_start_row;
   tabular_file_format.detail_lines_delineation.delimit_mode_labeled.set(Delineation_layout::DELIMIT_intrinsic);

   // Currently unable to determine alternating quote
   // Probably would need to look at all lines in the file and see if the are occurances of both in the file exclusively in certain lines

   // Currently presuming the column headers have the same delineation as the data (probably 99% of the time it is the same)
   // But probably should also do the same checks
   tabular_file_format.column_headers_delineation.relative_to_labeled  .set(tabular_file_format.detail_lines_delineation.relative_to_labeled.get());
   tabular_file_format.column_headers_delineation.start_row_1_based        = column_header_start_row;
   tabular_file_format.column_headers_delineation.begin_marker             = tabular_file_format.detail_lines_delineation.begin_marker;
   tabular_file_format.column_headers_delineation.end_marker               = tabular_file_format.detail_lines_delineation.end_marker;
   tabular_file_format.column_headers_delineation.delimit_mode_labeled     .set(tabular_file_format.detail_lines_delineation.delimit_mode_labeled.get()); // Currently presume the same  delimit mode for column headers (if any)

   tabular_file_format.column_headers_delineation.continuous_delimiter     = tabular_file_format.detail_lines_delineation.continuous_delimiter;
   tabular_file_format.column_headers_delineation.delimiter_space          = tabular_file_format.detail_lines_delineation.delimiter_space;
   tabular_file_format.column_headers_delineation.delimiter_comma          = tabular_file_format.detail_lines_delineation.delimiter_comma;
   tabular_file_format.column_headers_delineation.delimiter_tab            = tabular_file_format.detail_lines_delineation.delimiter_tab;
   tabular_file_format.column_headers_delineation.delimiter_semicolon      = tabular_file_format.detail_lines_delineation.delimiter_semicolon;
   tabular_file_format.column_headers_delineation.delimiter_other          = tabular_file_format.detail_lines_delineation.delimiter_other;
   tabular_file_format.column_headers_delineation.other_delimiter_16       = tabular_file_format.detail_lines_delineation.other_delimiter_16;
   tabular_file_format.column_headers_delineation.delimiter_string         = tabular_file_format.detail_lines_delineation.delimiter_string;
   tabular_file_format.column_headers_delineation.other_delimiter_string   = tabular_file_format.detail_lines_delineation.other_delimiter_string;
   tabular_file_format.column_headers_delineation.text_quote_mode_labeled  .set(tabular_file_format.detail_lines_delineation.text_quote_mode_labeled.get());
   tabular_file_format.column_headers_delineation.decimal_mark             .assign(tabular_file_format.detail_lines_delineation.decimal_mark);
   tabular_file_format.column_headers_delineation.notes                    .assign(tabular_file_format.detail_lines_delineation.notes);
   tabular_file_format.column_headers_delineation.rows = column_header_rows;
   tabular_file_format.column_headers_delineation.units_row_offset = units_row_offset; // Number of rows below the column header start row where units start (relative to column header start row_
   tabular_file_format.column_headers_delineation.units_rows = units_rows_count;
   /*NYI
With the column headers delimited might be able to setup the captions
//             column_headers can have a delineation layout different from the detail lines, but the same options are available
      columns_1based;          // list of Column
   */
/* NYI  May be able to determine this by scanning the
   file colums and searching for some common missing markers
   tabular_file_format.missing_data_marker;  // any codes I.e. -9999 or MISSING used to denote missing data
*/
   return identified;
};
//______________________________________________________________________________
Format_file_type Tabular_format_identifier::identify_file_type_by_extension(const char *_sample_filename) const
{  Format_file_type identified_file_type = FILE_TYPE_unknown;
   CORN::File_name  local_sample_filename(_sample_filename);
   if      (local_sample_filename.ext_is("xls")) identified_file_type = FILE_TYPE_Excel;
   else if (local_sample_filename.ext_is("dbf")) identified_file_type = FILE_TYPE_dBase;
   return identified_file_type;
};
//______________________________________________________________________________
Format_file_type Tabular_format_identifier::identify_file_type(ifstream &datafile) const
{  Format_file_type identified = FILE_TYPE_text;
/* NYI
   check extension
   look for cr/lf combinations
   look for Excel start record
   look for dBase
*/
   return identified;
};
//______________________________________________________________________________
#ifdef NYI
bool Tabular_format_identifier::identify
(modifiable_ Common_tabular_file_format  &tabular_file_format
,const char *sample_filename
,Tsample_form *local_sample_form
) const
{  bool format_identified = false;
   Format_file_type format_file_type = identify_file_type_by_extension(sample_filename);
   if (format_file_type == FILE_TYPE_unknown)
   {  // Need to scan the file for clues to the format
      ifstream datafile(sample_filename);
      format_file_type = identify_file_type(datafile);
   };
   tabular_file_format.format_file_type_labeled.set(format_file_type);
   tabular_file_format.defined_by.assign("Tabular format editor auto-identification (rnelson@mail.wsu.edu)");
   tabular_file_format.variable_order_labeled.set(Common_tabular_file_format::fixed_order);  // presume fixed order since this is the only sample file to go on
   switch (tabular_file_format.format_file_type_labeled.get())
   {  case FILE_TYPE_text :
      {  Text_format_auto_identifier format_identifier(tabular_file_format,sample_filename);
         format_identified = format_identifier.identify();
      } break;
      case FILE_TYPE_Excel:
      {  if (local_sample_form)
         {
#ifdef NYI
            local_sample_form->AdvGridExcelIO_sample->XLSImport(sample_filename);
            Excel_format_auto_identifier format_identifier(tabular_file_format,sample_filename);
            if (sample_form)
               format_identified = format_identifier.identify(local_sample_form->AdvGridWorkbook_sample);
#endif
         };
      } break;
#ifdef NYI
      case FILE_TYPE_dBase:
      {  dBase_format_auto_identifier format_identifier(tabular_file_format,sample_filename);
         format_identified = format_identifier.identify();
      } break;
#endif
      case FILE_TYPE_lotus123:   format_identified = false; break; // Not yet implemented
      case FILE_TYPE_binary :    format_identified = false; break; // Not possible to part binary data
   };
   return format_identified;
};
#endif
//______________________________________________________________________________
};
