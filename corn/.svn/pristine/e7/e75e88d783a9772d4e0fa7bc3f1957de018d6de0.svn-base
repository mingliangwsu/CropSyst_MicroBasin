#include "corn/format/VV/VV_document.h"
namespace CORN
{
namespace VV
{
//______________________________________________________________________________
//structural::Mapping
Document::Section
&Document::expect_section(const char *section_name)      expectation_
{
   current_section = dynamic_cast<Document::Section *>(&provide_KV_pair_mapping_str(section_name));
   return *current_section;
}
//______________________________________________________________________________
Document::Section &Document::expect_section(const wchar_t       *section_name)    expectation_
{
   current_section = dynamic_cast<Document::Section *>(&provide_KV_pair_mapping_wstr(section_name));
   return *current_section;
}
//______________________________________________________________________________
Document::Section &Document::expect_section(const std::string   &section_name) expectation_
{
   current_section = dynamic_cast<Document::Section *>(&provide_KV_pair_mapping_string(section_name));
   return *current_section;
}
//______________________________________________________________________________
Document::Section &Document::expect_section(const std::wstring  &section_name)  expectation_
{
   current_section = dynamic_cast<Document::Section *>(&provide_KV_pair_mapping_wstring(section_name));
   return *current_section;
}
//______________________________________________________________________________
/*
VV_Document::Section::Section(const char *section_name)
{
}
//______________________________________________________________________________
vV_Document::Section::Section(const wchar_t *section_name)
{
}
//______________________________________________________________________________
VV_Document::Section::Section(const std::string &section_name)
{
}
//______________________________________________________________________________
VV_Document::Section::Section(const std::wstring &section_name)
{
}
//______________________________________________________________________________
*/
} // namespace VV
} // namespace CORN

