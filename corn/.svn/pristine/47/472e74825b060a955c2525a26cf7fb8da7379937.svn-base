#include <corn/format/html/structure.h>
//#include <corn/format/html/html.h>

#define M_HTML "HTML"

namespace HTML
{

Document::Document
(STD_NS ostream &i_doc
,bool i_auto_HTML_XHTML
)
:Element(M_HTML,i_doc)
,auto_HTML_XHTML(i_auto_HTML_XHTML)
{
   if (auto_HTML_XHTML)
      start();
};

Document::~Document()
{
   if (auto_HTML_XHTML)
      end();
      //document << HTML_XHTML << endl;
};


}
