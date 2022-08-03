#ifndef YAML_streamH
#define YAML_streamH
//#include <string>
#include "corn/container/unilist.h"
#include "corn/container/text_list.h"
#include "corn/format/YAML/YAML_document.h"
#include "corn/format/structural_stream.h"
//#include <fstream>
namespace YAML
{
//   class Document;
/*
   enum Construct_type                                                           //151025
      {
         construct_unknown
        ,construct_mapping
        ,construct_sequence
        ,construct_scalar
      };
*/
//______________________________________________________________________________
class Stream
: public extends_ CORN::Structural_ifstream_Unicode
{
 protected:
   CORN::Text_list directives;
   Node *unresolved_document;
 protected:
   std::streampos start_line_strm_pos ;
 public:
   Stream(const CORN::OS::File_name &filename);
   virtual ~Stream();
   virtual nat8 get(structural::Construct &document)              modification_;
 protected:
   virtual nat8 parse_document
      (structural::Construct     &document);
      /// \returns error code or 0 if no error
   Parse_error_code parse_document_known
      (
      //170128 std::wistream &strm,
      structural::Construct     &document);
      // This is used for documents that may have preamble text
      // in addition to actual YAML syntax.
 protected:
   structural::Construct *
   parse_construct
      (std::wistream               &strm
      ,structural::Mapping        *in_mapping
      ,structural::Construct       &context_construct
      ,structural::Pair_key_value  *in_key_value_pair// = 0
      ,nat16                        indentation// = 0
      ,nat16                        leading_space_count //= 0
      );
/*
   Parse_error_code :parse_associative_array_inline
      (wchar_t                *text_remainder
      ,structural::Construct  &context_construct
      );
*/
 protected:
   nat16 process_directive(const std::wstring &directive);
   bool parse_to_start_of_document();
      //170128 (std::wistream &strm);

   YAML::Node *promote(given_ YAML::Parsing_element *element_given)        const;

   nat32 read_value
      (std::wistream &strm,std::wstring &value, std::wstring &comment)     const;
   bool read_remainder_of_line_to_comment
      (std::wistream &strm
      ,modifiable_ YAML::Parsing_element &current_parsing_element);
};
//______________________________________________________________________________
} // namespace YAML
#endif
