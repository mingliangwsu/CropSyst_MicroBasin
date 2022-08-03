#include <corn/tabular/tabular_text_parser.h>
#include <corn/tabular/tabular_format.h>
#include <corn/std/std_fstream.h>
namespace CORN
{
//______________________________________________________________________________
Tabular_text_parser::Tabular_text_parser(const Common_tabular_file_format &format)
: Tabular_parser(format)
,curr_file_line_number  (1)
,curr_data_line_number  (0)
,curr_block_line_number (0)
,curr_page_line_number  (0)
,curr_page_number       (0)
//,curr_column_header_line_number(0)
//,curr_detail_line_number (0)
,curr_character_pos     (0)
{};
//______________________________________________________________________________
void Tabular_text_parser::process_form_feed() modification_
{  if (format.paginated)
   {  curr_page_line_number = 1;
      curr_page_number += 1;
   };
};
//______________________________________________________________________________
bool Tabular_text_parser::read(const char *filename,CORN::Text_list &parsing_notes) modification_
{  bool result_parsable = true;
   // Returns true if the file was parsable with this format
   // returns false if any datum read was not consistent with the
   // format.
   known_colcount = format.columns_1based.count() + 1;
   if (known_colcount < 2)   // If we haven't delinieated columns yet, then
       known_colcount = 2;    // initially only the Row number and the rest of the line.
/*
Note that much of this is relevent to tabular text files.
may wish to merge this with tabular text file and display the parsed data,
however The tabular text file may want to simply assume that
the file is the valid format.
*/
   curr_data_line_number =      // 1 based counted from the starting line of the  data begin marker (if specified) this is never reset.
      (format.begin_marker.length())
      ? 0                           // 0 indicates we haven't reached the data begin marker
      : 1;                          // 1 indicates there will be no marker so the beginning of the file is the begin marker
   int curr_grid_row = 1;           // 1 based (I think)
   bool found_begin_marker = !format.begin_marker.length(); // will be true if the begin marker is not relevent
   STD_NS ifstream text_file_stream(filename);
   bool at_end_of_data = !(text_file_stream.good());
   while (!text_file_stream.eof())
   {
      char the_char =  text_file_stream.get();
      switch (the_char)
      {  case '\n' :
         {  curr_character_pos++; // Increment curr_character_pos because a context might need it to determine if reached field width
            update_contexts('\n'); // Allow contexts to process the new line since they may use it as a delimiter
            curr_file_line_number += 1;
            if (curr_data_line_number) curr_data_line_number += 1;
            if (curr_page_line_number) curr_page_line_number += 1;
            curr_character_pos = 0;
         } break;
         case 12 : // Form feed
         {  process_form_feed();
         };
      };
      if (curr_character_pos == 0)
      {  // We are at the beginning of the line
         if (format.FORTRAN_carriage_control)
         {  // eat and process the carriage_control character
            char carriage_ctrl_char =  text_file_stream.get();
            switch (carriage_ctrl_char)
            {  case ' ' : /* Normal line do nothing */ break;
               case '0' : /* double space*/     if (curr_page_line_number) curr_page_line_number++; break;
               case '+' : /* overwrite mode*/
                  if (curr_page_line_number) curr_page_line_number--;
                  clear_contexts(); // we are going back a line, we need to
               break; // This case should never happen for data file and most reports
               case '1' : /* next page */       process_form_feed(); break;
               default : the_char = carriage_ctrl_char; break;
                  // default Should not happen but could be a file without carriage_ctrl_char;
            };  // switch  carriage_ctrl_char
         };  // if carriage_control_FORTRAN
         curr_character_pos = 1;
      } else curr_character_pos++;
      if ((curr_data_line_number == 1) && format.paginated)
      {  curr_page_line_number = 1;
         curr_page_number = 1;
      };
      // At this point line positions should have been resolved
      update_contexts(the_char);
      if (the_char)
      {  // the_char may have been 'eaten' by the context update (I.e. as delimitor, white space, quotation etc.).
         // if it isn't then it should be interpreted as data.
         // since we have changed position in the file we may be in a new context
         // and/or out of an old one.

         // At this point we should be in the file line with the next character of potential data read
         // and ready to process
         bool character_processed_as_data = false;
         if (curr_data_line_number)
             character_processed_as_data = process_character(the_char);
         if (!character_processed_as_data)
         {
            // all cases are probably handled now
         };
      };
   };
   return  curr_file_line_number;
};
//______________________________________________________________________________
bool Tabular_text_parser::process_character(char character)        modification_
{  // This does not appear to be data maybe it is control or marker or commentary
//continue here
   return false;
};
//______________________________________________________________________________
void  Tabular_text_parser::update_contexts(char &character)
{
//continue here

};
//______________________________________________________________________________
}
