#ifndef CORN_HTML_FONT_H
#define CORN_HTML_FONT_H


//#include <corn/format/html/html.h>
#include <corn/format/html/element.h>
#define M_FONT "FONT"

namespace HTML
{

class Font
: public Element
, public Attribute_options
{
   Int_option      size; // + or -
   Uint_option     point_size; // ???
   Color_option    color;
   String_option   face;
   //NYI weight ???
public: // structors
   inline Font
   (Color i_color,Element *i_parent_element)
   :Element(M_FONT,parent_element)
   ,size("SIZE")          // default
   ,point_size("POINT-SIZE")    // default
   ,color()
   ,face("FACE")         // default
   // ,weight(???)
   {
      color.set(i_color);
   };
   inline Font
   (const CORN::Ustring &i_face,Element  *i_parent_element)
   :Element(M_FONT,i_parent_element)
   ,size("SIZE")
   ,point_size("POINT-SIZE")
   ,color()
   ,face("FACE")
   // ,weight(???)
   {
      face.set(i_face);
   };
   inline virtual ~Font() { flush();};
public: // overrides
   virtual void options();
};
}; // namespace HTML
#endif

