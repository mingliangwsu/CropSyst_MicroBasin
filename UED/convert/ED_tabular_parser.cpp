#include <UED/convert/ED_tabular_parser.h>
#include <UED/convert/ED_tabular_format.h>
using namespace CORN;
//______________________________________________________________________________
ED_tabular_parser_text::ED_tabular_parser_text(const ED_tabular_file_format &_format)
: CORN::Tabular_text_parser((const Common_tabular_file_format &)_format)
, format(_format)
{  // constructor
};
//______________________________________________________________________________
bool ED_tabular_parser_text::process_character(char character)     modification_
{  bool processed = false;
   if (character)
   {  if (detail_line_context)         processed = detail_line_context           ->process_character(character);
      if (scalar_field_caption_context)processed = scalar_field_caption_context  ->process_character(character);
      if (scalar_field_value_context)  processed = scalar_field_value_context    ->process_character(character);
      if (column_header_context)       processed = column_header_context         ->process_character(character);
      if (!processed)                  processed = Tabular_text_parser::process_character(character);
   };
   return processed;
};
//______________________________________________________________________________
void ED_tabular_parser_text::update_contexts(char &character)      modification_
{
   Context_update_status scalar_field_caption_context_status= update_scalar_field_caption_context(character);
   Context_update_status scalar_field_value_context_status  = update_scalar_field_value_context(character);
   Context_update_status column_header_context_status       = update_column_header_context(character);
   Context_update_status detail_line_context_status         = update_detail_line_context(character);
};
//______________________________________________________________________________
void ED_tabular_parser_text::clear_contexts()                      modification_
{  if (detail_line_context)         delete detail_line_context;         detail_line_context = 0;
   if (scalar_field_caption_context)delete scalar_field_caption_context;scalar_field_caption_context = 0;
   if (scalar_field_value_context)  delete scalar_field_value_context;  scalar_field_value_context = 0;
   if (column_header_context)       delete column_header_context;       column_header_context = 0;
};
//______________________________________________________________________________
bool ED_tabular_parser_text::Columnar_context::process_character(char character) modification_
{
   curr_column_value[curr_column_pos++] = character;
   return true;
};
//______________________________________________________________________________
bool ED_tabular_parser_text::Scalar_field_caption_context::process_character(char character) modification_
{  bool caption_matches = true;
   if (field_description.caption.length() // If there is a caption for the field
       &&(character != field_description.caption.c_str()[curr_caption_pos]))
   {  caption_matches = false;
      // Should output parse error message to parsing_errors
   };
   return caption_matches;
};
//______________________________________________________________________________
bool ED_tabular_parser_text::Scalar_field_value_context
::process_character(char character)                                modification_
{
   char character_str[2]; character_str[1] = 0; character_str[0] = character;
   field_description.read_buffer.append(character_str);
   return true;
};
//______________________________________________________________________________
bool ED_tabular_parser_text::Column_header_context
::process_character(char character)                                modification_
{
   Ustring  *raw_column_header[1000];  int curr_column_header_col; // 1 based (index 0 not used)
   Ustring  *raw_detail_line  [1000];  int curr_detail_line_col;   // 1 based (index 0 not used)
   return true;
};
//______________________________________________________________________________
#ifdef CHECK_OBSOLETE
081224 but I may have been partly through so don't delete until I finish the
tabular import
Tabular_parser::Context_update_status ED_tabular_parser_text::update_scalar_caption_context(char &character)     modification_
{

   if (scalar_field_caption_context)
   {
      Context_update_status status =  scalar_field_caption_context->update(character);
      switch (status)
      {  case no_change_of_context     :        /* do nothing. Continue with current context */
         case advance_to_next_column   :        /* do nothing. This is not applicable to scalar fields */
         case in_same_context          : break; /* do nothing. Continue with current contex*/
         case out_of_context           : {  delete scalar_field_caption_context; scalar_field_caption_context = 0; }; break;
      };
   };
   if (scalar_field_caption_context) // see if we are in another scalar field.
   FIND_FOR_EACH_IN(found_scalar_field,scalar_field,ED_tabular_file_format::Scalar_field,format.header_fields_1based,true,each_scalar_field)
   {
      int expected_caption_length = scalar_field->caption.length();
      bool on_the_field_row = false;
      switch (scalar_field->relative_to_labeled.get())
      {
         case FILE_RELATIVE  : { if ( scalar_field->caption_row == curr_file_line_number) on_the_field_row = true;  } break;
         case DATA_RELATIVE  : { if ( scalar_field->caption_row == curr_data_line_number) on_the_field_row = true;  } break;
         case BLOCK_RELATIVE : { if ( scalar_field->caption_row == curr_block_line_number)on_the_field_row = true;  } break;
         case PAGE_RELATIVE  : { if ((scalar_field->caption_row == curr_page_line_number)
                                      &&((curr_page_number==1)||scalar_field->every_page))on_the_field_row = true;  } break;
      }; // Switch (scalar_field->relative_to_labeled.get())
      bool in_context = false;
      if (on_the_field_row)
      {
         if ( (curr_character_pos >= scalar_field->caption_col)
           && (curr_character_pos <= scalar_field->caption_col + expected_caption_length))
           // Note that the second condition for the field caption length
           // isn't really necessary, but it is possible that the field width was
           // not specified (variable) or overlapped another field
         {  in_context = true; };
      };
      if (found_scalar_field)
         scalar_field_caption_context = new scalar_field_caption_context(found_scalar_field);
   };
};
#endif
//______________________________________________________________________________
#ifdef CHECK_OBSOLETE
081224 but I may have been partly through so don't delete until I finish the
tabular import
Tabular_parser::Context_update_status ED_tabular_parser_text::update_scalar_value_context(char &character)     modification_
{
   if (scalar_field_value_context)
   {  Context_update_status status =  scalar_field_value_context->update(character);
      switch (status)
      {  case no_change_of_context     :        /* do nothing. Continue with current context */
         case advance_to_next_column   :        /* do nothing. This is not applicable to scalar fields */
         case in_same_context          : break; /* do nothing. Continue with current contex*/
         case out_of_context           : {  delete scalar_field_value_context; scalar_field_value_context = 0; }; break;
      };
   };
   if (scalar_field_value_context)
   FIND_FOR_EACH_IN(found_scalar_field,scalar_field,ED_tabular_file_format::Scalar_field,format.header_fields_1based,true,each_scalar_field)
   {  // see if we are in another scalar field.
      int expected_value_length = scalar_field->width;
      bool on_the_field_row = false;
      switch (scalar_field->relative_to_labeled.get())
      {  case FILE_RELATIVE  : { if ( scalar_field->row == curr_file_line_number) on_the_field_row = true;  } break;
         case DATA_RELATIVE  : { if ( scalar_field->row == curr_data_line_number) on_the_field_row = true;  } break;
         case BLOCK_RELATIVE : { if ( scalar_field->row == curr_block_line_number)on_the_field_row = true;  } break;
         case PAGE_RELATIVE  : { if ((scalar_field->row == curr_page_line_number)
                                      &&((curr_page_number==1)||scalar_field->every_page))on_the_field_row = true;  } break;
      }; // Switch (scalar_field->relative_to_labeled.get())
      bool in_context = false;
      if (on_the_field_row)
      {
         if ( (curr_character_pos >= scalar_field->col)
           && (curr_character_pos <= scalar_field->col + scalar_field->width))
           // Note that the second condition for the field caption length
           // isn't really necessary, but it is possible that the field width was
           // not specified (variable) or overlapped another field
         {  found_scalar_field = scalar_field; };
      };
      if (found_scalar_field)
         scalar_field_value_context = new scalar_field_value_context(found_scalar_field);
   };
};
#endif
//______________________________________________________________________________
Tabular_parser::Context_update_status ED_tabular_parser_text::Columnar_context::update(char &character)
{  // Returns true if we updated to next column
//   Context_update_status result = false;
   status = no_change_of_context;
   bool at_delimitor = false;
   bool at_column_break = false; // Either at a delimitor, at end of line, or at column width
   if (character == '\n')
   {
      context_line_number += 1;
      at_column_break = true;
      character = 0; // we have eaten the character
   };
   ED_tabular_file_format::Column *curr_column = (ED_tabular_file_format::Column *)each_column->current();
   if (!in_quote)
   { // If we are inside a quote string then we are not looking for delimitor
      switch (delineation.delimit_mode_labeled.get())
      {  case Delineation_layout::DELIMIT_fixed_width   : if ((curr_column_pos+1) == curr_column->field_width) at_column_break = true; break;
         case Delineation_layout::DELIMIT_character :
         {
            switch (character)
            {  case '\t'   : if (delineation.delimiter_tab)       at_delimitor = true; break;
               case ' '    : if (delineation.delimiter_space)     at_delimitor = true; break;
               case ','    : if (delineation.delimiter_comma)     at_delimitor = true; break;
               case ';'    : if (delineation.delimiter_semicolon) at_delimitor = true; break;
               default:
               {  if (delineation.delimiter_other && (character == delineation.other_delimiter_16))
                     at_delimitor = true;
                  if (delineation.delimiter_string)
                  {  if (character == delineation.other_delimiter_string[curr_delimitor_string_pos])
                     {
                        curr_delimitor_string[curr_delimitor_string_pos] = character;
                        curr_delimitor_string[curr_delimitor_string_pos++] = 0;
                        if (delineation.other_delimiter_string[curr_delimitor_string_pos] == 0)
                        {  // we've read the entire expected delimitor string
                           // so we must be at the delimitor
                           at_delimitor = true;
                           // Reset for the next delimitor
                           curr_delimitor_string_pos = 0;
                           curr_delimitor_string[0] = 0;
                        };
                     } else
                     {  // what we have read so far that looked like the delimitor string is not
                              // so we will append it to the curr_column_value
                        for (int i = 0; i <= curr_delimitor_string_pos; i++)
                        {
                           curr_column_value[curr_column_pos++] = curr_delimitor_string[i];
                        };
                     }; // if (character == other_delimiter_string[curr_delimitor_string_pos])
                  }; // if (delineation.delimiter_string)
               } break;
            }; // switch (character)
            last_character_processed_was_delimitor = at_delimitor;
            if (delineation.continuous_delimiter && at_delimitor && last_character_processed_was_delimitor)
            {  at_delimitor = false; // we have already processed a continuous delimitor
            };
            at_column_break = at_delimitor;
         } break;  // DELIMIT_character
         case Delineation_layout::DELIMIT_intrinsic : default : /* Not applicable to text files */ break;
      }; // switch delimit_mode
      if (at_delimitor) character = 0;
   }; // if (!in_quote)
   switch (delineation.text_quote_mode_labeled.get())
   {
      case Delineation_layout::SINGLE_QUOTE       :
      {  if (character == '\'')
         {  if (in_quote == '\'') // end quote
                  in_quote = 0;
            else  in_quote = '\'';
            character = 0;
         }; // else it is so other character  we continue to process
      } break;
      case Delineation_layout::DOUBLE_QUOTE :
      {  if (character == '\"')
         {  if (in_quote == '\"') // end quote
                  in_quote = 0;
            else  in_quote = '\"';
            character = 0;
         }; // else it is so other character  we continue to process
      } break;
      case Delineation_layout::ALTERNATING_QUOTE :
      {
         switch (character)
         { case '\"' :
            {  if (in_quote == '\"')  // end quote
                     in_quote = 0;
               else  in_quote = '\"';
               character = 0;
            } break; // else it is so other character  we continue to process
            case '\'' :
            {  if (in_quote == '\'')  // end quote
                     in_quote = 0;
               else  in_quote = '\'';
               character = 0;
            } break; // else it is so other character  we continue to process
         }; // switch (character)
      } break;
      case Delineation_layout::NO_QUOTE : default: /* Do nothing, just continue with processing of character*/ break;
   };
   return status;
};
//______________________________________________________________________________
Tabular_parser::Context_update_status  ED_tabular_parser_text::update_column_header_context(char &character)
{
   if (column_header_context)
   {
      Context_update_status status = column_header_context->update(character);
      if (status == advance_to_next_column)
      {  delete column_header_context; column_header_context = 0;
      };
      curr_column_header_col += 1;

   };

   if (!column_header_context)
   {  // See if we are in a column header
      bool on_column_header_row = false;
      switch (format.column_headers_delineation.relative_to_labeled.get())
      {  case FILE_RELATIVE   :
         {
           on_column_header_row = curr_file_line_number >= format.column_headers_delineation.start_row_1_based;
         } break;
         case  DATA_RELATIVE  :
         {
           on_column_header_row = curr_data_line_number >= format.column_headers_delineation.start_row_1_based;
         } break;
         case  PAGE_RELATIVE  :
         {
           on_column_header_row = curr_page_line_number >= format.column_headers_delineation.start_row_1_based;
         } break;
         case  BLOCK_RELATIVE :
         {
           on_column_header_row = curr_block_line_number >= format.column_headers_delineation.start_row_1_based;
         } break;
      }
      if (on_column_header_row)
      {  // now see if we are in one of the defined columns based on position
         // Note that columns do not have to be

         int find_column_index = 0;
         FIND_FOR_EACH_IN(found_column,column,ED_tabular_file_format::Column,format.columns_1based,true,each_column)
         {  find_column_index += 1;
            if (column->start_1based)
            {
               if (curr_character_pos >= column->start_1based)
               {
                  if (column->field_width == 0) // then the column definition extends to the end of the line
                     found_column = column;
                  else
                  {  if (curr_character_pos <= column->start_1based + column->field_width)
                     {
                        found_column = column; // we are within the column field extent.
                        column_header_context = new Column_header_context(format.column_headers_delineation,format.columns_1based);
                     };
                  }
               }; // we haven't reached this column yet
            }; // else this column is not delineated by position and width,
               // so it must be delineated by delimitor (handled below).
            // NYI  not currently handling the case where data (vectors) are spread over multiple columns
            // (this is a CropSyst output mode not intented for import)
            // spread_over_columns;
            // columns;    // This is the number of columns including this column to reserve for spreading data set and layered variables (not character columns)
            if (found_column)
               curr_column_header_col = find_column_index;
         } FOR_EACH_END(each_column);
      }; // else we are not in a context (column_header_context remains 0)





   };
   if (column_header_context)
      column_header_context->update(character);




#ifdef NYI
   character might be separator and  end the column header (caption line or units line)
      column_header_context
   if (character is separator or new line)
   {


/*060626_*/        Ustring caption_SDF;       // This is the text that would appear in the column header, in SDF format.
/*_______*/        Ustring units_description; // A text string indicating the label of the units.
/*_______*/        // units definition is not yet implemented, currently only supporting Units_codes
/*040925_*/       Labeled_units_enum      smart_units_code_enum;

/*_______*/    Ustring           label;      // The label is used in dBase like tables (it is available for use (reference) in other formats.
/*_______*/    Data_type_labeled data_type_labeled;
/*_______*/    Ustring           worksheet;  // For workbook programs (I.e. Excel, this is the worksheed the column occurs on
/*_______*/    int16             start_1based;   // For text files this is the character position. For Excel, this is the cell column.
/*_______*/                      // This is 1 based for text file (in the case of FORTRAN like carridge control)
                                 // This is 1 based for excel columns
/*_______*/                      // The carridge control character is at position 0 (there should be no column defined for the carridge control characters position.
/*_______*/    int16             precision_16;  // Actually only need 8 bit but using 16 for UI (autouint16 edit)
/*_______*/    bool              spread_over_columns;
/*_______*/    int16             columns;    // This is the number of columns including this column to reserve for spreading data set and layered variables (not character columns)
/*070524_*/    Ustring           missing_value; // For text this might be the word "missing" or "N/A", for numbers this might be "99999.99"




      add new line to caption (if more rows in C.H.)

      delete the column_header context
      if not last column create new column header context

      (Note, may need rest of line context)

      add cell information

   }
   else
   {
      append character to caption

   };
#endif
};
//______________________________________________________________________________
Tabular_parser::Context_update_status  ED_tabular_parser_text::update_detail_line_context(char &character)
{

   Detail_line_context     *detail_line_context;

#ifdef NYI
   character might be separator and the field
   if (character is separator or new line)
   {
      delete the detailine line
      if not last column create new detail line context
      (Note, may need rest of line context)
      add cell information
   }
   {
      append character to field data

/*050402_*/    CORN::Ustring decimal_mark;  // . for US  , for other countries


   };

#endif
   return 0;
};
//______________________________________________________________________________

#ifdef NYI
         switch (format->relative_to_labeled.get())

            if (curr_data_line_number >= column_headers_delineation->start_row_1_based)
            {
               if (columns_1based.count() > 0)
               {
                  for each column description
                  {
                     write the current part of the column header caption
                     or units
                     set the cell color
                     string_grid_for_text->Colors[curr_grid_col][curr_grid_row] = clLime;
                  };
               } else
               {
                  set the cell text color to undelineated text color
               };

            };
            if (curr_data_line_number >= detail_line_delineation->start_row_1_based)
            {  in detail line extent
               if (format->date_column_number_1based > 1)      // 1 based
               {
                  set the set background color to current grid row
                  and format->date_column_number_1based column to
                  the date background color.
               };
               if (format->ID_column_number_1based > 1)      // 1 based
               {
                  set the set background color to current grid row
                  and format->ID_column_number_1based column to
                  the staton ID background color.
               };
               if (format->name_column_number_1based > 1)      // 1 based
               {
                  set the set background color to current grid row
                  and format->name_column_number_1based column to
                  the station ID background color.
               };



               if (columns_1based.count() > 0)
               {
                  for (each column)
                  {
                     set the cell value

                     If the value is the format->detail_lines_delineation.missing_data_marker;  // any codes I.e. -9999 or MISSING used to denote missing data
                        then set the cell text color to the missing data text color
                  }

               } else
               {
                 set the cell text color to undelineated text color
               };

            };



         }
         else
         {  // were are still in extraneous data
            if (format->end_marker.length())
            {
               end_marker_pos =line_read.find(format->end_marker);
               if (end_marker_pos)
                  we can now break the read loop.
            };

         };
      };
      string_grid_for_text->RowCount= curr_data_line_number;
   };
   string_grid_for_text->Fixed_rows = xxxx;  detail line start row
   string_grid_for_text->Fixed_cols = 1; // The first column is the header


/*
ED_tabular_file_format:
    column_headers_delineation
    detail_lines_delineation
    columns_1based
*/


#endif
//______________________________________________________________________________
