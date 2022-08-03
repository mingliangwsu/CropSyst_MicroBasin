#ifndef ED_tabular_parserH
#define ED_tabular_parserH

#include <corn/tabular/tabular_text_parser.h>
#include <corn/tabular/delineation.h>
#include <corn/tabular/tabular_format.h>
#include <ued/convert/ED_tabular_format.h>
using namespace CORN;

class ED_tabular_parser_text
: public CORN::Tabular_text_parser
{
private:
   //___________________________________________________________________________
   class Scalar_field_caption_context
   : public  CORN::Tabular_parser::Context_abstract
   {
   private: // adjunct references from format
//      Association_list              &header_fields_1based;
      ED_tabular_file_format::Metadata_field                  &field_description;
      int                            curr_caption_pos; // This is the character position in the field caption being read
   public:// 'structors
      Scalar_field_caption_context(ED_tabular_file_format::Metadata_field &_field_description /*Association_list              &_header_fields_1based*/)
         : CORN::Tabular_parser::Context_abstract()
         , field_description(_field_description)
         {};
   public: // override Context_interface
      virtual Tabular_parser::Context_update_status update(char &character) modification_;
      virtual bool process_character(char character) modification_;
   };
   //___________________________________________________________________________
   class Scalar_field_value_context
   : public  CORN::Tabular_parser::Context_abstract
   {
   public: // adjunct references from format
//      Association_list              &header_fields_1based;
      ED_tabular_file_format::Metadata_field                  &field_description;
   public:// 'structors
      Scalar_field_value_context(ED_tabular_file_format::Metadata_field &_field_description /*Association_list              &_header_fields_1based*/)
         : CORN::Tabular_parser::Context_abstract()
         ,field_description(_field_description)
         {};
   public: // override Context_interface
      virtual Tabular_parser::Context_update_status update(char &character) modification_;
      virtual bool process_character(char character) modification_;
   };
   //___________________________________________________________________________
   class Columnar_context
   : public  CORN::Tabular_parser::Context_abstract
   {
   private: // adjunct references from Common_tabular_file_format
      const Delineation_layout           &delineation;
      const Association_list             &columns_1based;
   protected: // adjunct working
      int context_line_number;
   private:
      Container::Iterator          *each_column;
      bool                          last_character_processed_was_delimitor;      // Used in the case of continuous delimiters treated as one
      uint32                        curr_column_pos;                             // This is the character postion for the current column.
      char                          curr_column_value[1000];                     // Buffer storing this current portion of the value
      uint32                        curr_delimitor_string_pos;
      char                          curr_delimitor_string[1000];                 // Buffer storing this current portion of any delimitor substring
         // As we are processing columns text, we may be within a delimitor string
         // I.e. the HTML table delimitor  <TD>  then we need to subparse this text as well.
      char                          in_quote;   // 0 if we have not started quotation
                                                // " if we have started a double quote
                                                // ' if we have started a single quote
   public: // 'structors
      Columnar_context
         (const Delineation_layout  &_delineation
         ,const Association_list    &_columns_1based)
         // : Context_interface   interface constructor not needed
         : delineation           (_delineation)
         , columns_1based        (_columns_1based)
         , each_column           (columns_1based.iterator())
         , last_character_processed_was_delimitor(false)
         , curr_column_pos  (0)
         , curr_delimitor_string_pos(0)
         , in_quote              (false)
         {
            curr_column_value[0] = 0;
            curr_delimitor_string[0] = 0;
         };
   public: // override Context_interface
      virtual Tabular_parser::Context_update_status  update(char &character) modification_;
      virtual bool process_character(char character) modification_;
   };
   //___________________________________________________________________________
   class Column_header_context
   : public Columnar_context
   {
   private: // adjunct references from Common_tabular_file_format
      const Common_tabular_file_format::Column_headers_delineation   &column_headers_delineation;  // reference to column_headers_delineation
   protected:
      int &curr_column_header_line_number;   // alias to context_line_number

   public: // 'structors

      Column_header_context
         (const Common_tabular_file_format::Column_headers_delineation   &_column_headers_delineation
         ,const Association_list             &_columns_1based)
         : Columnar_context(_column_headers_delineation,_columns_1based)
         , column_headers_delineation(_column_headers_delineation)
         , curr_column_header_line_number(context_line_number)
         {


         };
   public: // override Context_interface
      inline virtual Context_update_status update(char &character)  modification_
      {};
      virtual bool process_character(char character)                modification_;
   };
   //___________________________________________________________________________
   class Detail_line_context
   : public Columnar_context
   {
   private:
      int &curr_detail_line_number;  // alias to context_line_number
         // Normally 1 when reading detail line.
                                    // however could be more if the format allows detail to span multiple lines.

   private: // adjunct references from Common_tabular_file_format
      Common_tabular_file_format::Detail_lines_delineation     &detail_lines_delineation;     // reference to detail_lines_delineation
   public: // 'structors
      Detail_line_context
         (Common_tabular_file_format::Detail_lines_delineation   &_detail_lines_delineation
         ,Association_list             &_columns_1based)
         : Columnar_context(_detail_lines_delineation,_columns_1based)
         , detail_lines_delineation(_detail_lines_delineation)
         , curr_detail_line_number(context_line_number)
         {
         };
   };
   //___________________________________________________________________________
protected:  // adjuncts ED_tabular_parser_text
   const ED_tabular_file_format &format;
   Scalar_field_caption_context  *scalar_field_caption_context;
   Scalar_field_value_context    *scalar_field_value_context;
   Column_header_context         *column_header_context;
   Detail_line_context           *detail_line_context;
protected:
   // These contains store raw data as encountered in the file
   // Each item represents the field

   Ustring  *raw_column_header[1000];  int curr_column_header_col; // 1 based (index 0 not used)
   Ustring  *raw_detail_line  [1000];  int curr_detail_line_col;   // 1 based (index 0 not used)
public:
   ED_tabular_parser_text(const ED_tabular_file_format &_format);
   virtual void update_contexts(char &character)                   modification_;
   virtual bool process_character(char character)                  modification_;
   void clear_contexts()                                           modification_;
private:
   Tabular_parser::Context_update_status update_scalar_field_caption_context(char &character) modification_
      {} ;  // 081231 Don't know what these were for, but I can't find the body.
   Tabular_parser::Context_update_status update_scalar_field_value_context(char &character) modification_
      {} ;  // 081231 Don't know what these were for, but I can't find the body.
   Tabular_parser::Context_update_status update_column_header_context(char &character)  modification_;
   Tabular_parser::Context_update_status update_detail_line_context(char &character)    modification_;
};

#endif

