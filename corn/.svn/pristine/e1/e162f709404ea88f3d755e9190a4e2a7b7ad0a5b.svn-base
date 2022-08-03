#ifndef VV_documentH
#define VV_documentH
#include "corn/format/structural.h"
namespace CORN
{
//______________________________________________________________________________
class KV_Document
: public extends_ structural::Mapping_clad
{
   // NYI
};
namespace VV
{
//_2017-01-28___________________________________________________________________
class Document
: public extends_ structural::Mapping_clad // list of Sections
{
 public:
   typedef structural::Mapping_clad Section;
   /* Not needed because sections are simply mappings
   class Section
   : public extends_ structural::Mapping_abstract // list of variable=value
   {
    public:
      Section(const char *section_name);
      Section(const wchar_t *section_name);
      Section(const std::string &section_name);
      Section(const std::wstring &section_name);
   };
   */

   //___________________________________________________________________________
 protected:
   //Section *current_section;
   Section *current_section;
 public:
   inline Document()
      : structural::Mapping_clad(0)
      // Currently documents don't have specifier but essentially
      {}
//   structural::Mapping /*Section*/
   Section &expect_section(const char          *section_name) expectation_;
   Section &expect_section(const wchar_t       *section_name) expectation_;
   Section &expect_section(const std::string   &section_name) expectation_;
   Section &expect_section(const std::wstring  &section_name) expectation_;
};
//_2017-01-28___________________________________________________________________
} // namespace VV
} // namespace CORN

#endif
