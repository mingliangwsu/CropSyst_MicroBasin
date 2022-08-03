#ifndef CORN_HTML_TEXT_STYLE_H
#define CORN_HTML_TEXT_STYLE_H

#include <corn/format/html/element.h>

namespace HTML
{
extern char *M_Hx[];
class Hx
: public Element
, public Attribute_options
, public Align_option
{

public:
   inline Hx(uint8 level,Element *i_parent_element)
   : Element(M_Hx[level],i_parent_element)
   ,Attribute_options()
   ,Align_option()
   {};
   inline virtual ~Hx() { flush();};

   virtual void options();
};

}; // namespace HTML

#endif

