#include <corn/format/html/element.h>

using namespace std; //091123
namespace HTML
{
const char *align_label_table[] =
{"LEFT"
,"CENTER"
,"RIGHT"
,"JUSTIFY"     // <- Text only
,"BOTTOM"      // <- CAPTION LEGEND IFRAME
,"ABSBOTTOM"   // <- INPUT
,"MIDDLE"      // <- IMG APPLET IFRAME
,"TOP"
,"BASELINE"
,"ABSMIDDLE"
,"TEXTTOP" // <- IMG APPLET
,0
};

const char *valign_label_table[]=
{"TOP"
,"MIDDLE"
,"BOTTOM"
,"BASELINE"
,0
};

const char *dir_label_table[]=
{"LTR"
,"RTL"
,0
};

const char *dataformatas_label_table[] =
{"PLAINTEXT"
,"HTML"
,0
};

const char *special_target_label_table[] =
{"_blank"
,"_self"
,"_parent"
,"_top"
,0
};

Element::Element
(const CORN::Ustring &i_marker
,STD_NS ostream &i_doc
)
:Arbitrary(i_doc)
,marker(i_marker)
,parent_element(0)
,started(false)
{
   start_parent_if_necessary();
};

Element::Element
(const CORN::Ustring &i_marker
,Element *i_parent_element)
:Arbitrary(i_parent_element->get_document_stream())
,marker(i_marker)
,parent_element(i_parent_element)
,started(false)
{
   start_parent_if_necessary();
};

void Element::start()
{  if (!started)
   {
      document << endl << "<" << marker;
      options();
      document << ">" << endl;
      started = true;
   };
};

void Element::end(const char *element_marker)
{  flush();
   document << endl <<"</" << element_marker << '>' << endl;
};

}; // namespace HTML

