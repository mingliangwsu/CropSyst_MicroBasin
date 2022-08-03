#ifndef CORN_HTML_TEXT_LAYOUT_H
#define CORN_HTML_TEXT_LAYOUT_H

#include <corn/format/html/element.h>

#define M_BR "BR"
namespace HTML
{
class Br
: public Element
, public Core_attribute_options
, public IL8N_options
{
   enum Clear {NONE,LEFT,RIGHT,ALL};
   Clear clear;
public:
   inline Br(Element *i_parent_element)
   : Element(M_BR,i_parent_element)
   ,clear(NONE)
   {};
   inline virtual ~Br() { flush();};

public: // overrides
   virtual void options();
    inline void set_clear(Clear i_clear) { clear = i_clear; };
};

}; // namespace HTML

#endif

