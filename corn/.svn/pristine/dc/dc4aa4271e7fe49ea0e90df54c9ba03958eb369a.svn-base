#ifndef tabular_text_parserH
#define tabular_text_parserH
#include <corn/tabular/tabular_parser.h>
namespace CORN
{
//______________________________________________________________________________
class Tabular_text_parser
: public Tabular_parser
{protected: //adjuncts   (Note, these may be common also to spreadsheets as well, could move to Tabular_parser
   // line numbers are 0 when not inside a relevent block
   int curr_file_line_number;    // 1 based This is the current line in the file (includes extraneous text)
   int curr_data_line_number;    // 1 based counted from the starting line of the  data begin marker (if specified) this is never reset.
   int curr_block_line_number;   // 1 based counted from the data marker for the section(if specified) this is never reset.
 protected: //adjuncts
   int curr_page_line_number;   // 1 based this is the number of lines from the last form feed character.
                                    //  or the beginning of data.
                                    //  Will always be 0 if this format does not specify pagination
   int curr_page_number;     //  Will always be 0 if this format does not specify pagination
   int curr_character_pos;      // 1 based
                                    // 0 indicates at beginning of the file line
                                    //   in the case of FORTRAN carriage control
                                    //   we read the next character for processing.
   int known_colcount;
 public:  // 'structors
   Tabular_text_parser(const Common_tabular_file_format &format);
 public:  // procedures
   virtual bool read(const char *filename,CORN::Text_list &parsing_notes) modification_;
   // returns the number of lines read.
 protected:
   virtual void process_form_feed()                               modification_;
   virtual bool process_character(char character)                 modification_;
   virtual void update_contexts(char &character)                  modification_;
   virtual void clear_contexts()                                  modification_=0;
};
//______________________________________________________________________________
}; // namespace CORN
#endif

