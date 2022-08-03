#ifndef CORN_HTML_IMG_H
#define CORN_HTML_IMG_H

//#include <corn/format/html/html.h>
//#include <corn/format/html/types.h>
#include <corn/format/html/element.h>

namespace HTML
{
class Img
: public Element
, public Attribute_options
, public Data_options
, public Dimension_options
, public Align_option
{
   String_option   src;
   String_option   alt;
   /*NYI
   CORN_string    longdesc;
   uint8          border;
   uint16         hspace;
   uint16         vspace;
   bool           ismap
   CORN_string    usemap;
   bool           controls ?
   bool           dynsrc   ?
   CORN_string    longdesc ?
   ??             loop;
   CORN_string    lowsrc; ???
   CORN_string    name;
   CORN_string    start;???
   CORN_string    VRML; ???
   bool           suppress;
   */

public:
#define M_IMG "IMG"
   inline Img(Element /*body*/ *parent_body
           ,const CORN::Ustring &i_src
           ,const CORN::Ustring &i_alt
           ,Align_option::Align   i_align = Align_option::LEFT
           )
   :Element(M_IMG,parent_body)
   ,Attribute_options()
   ,Data_options()
   ,Dimension_options()
   ,Align_option()
   ,src("SRC")
   ,alt("ALT")
   {
      src.set(i_src);
      alt.set(i_alt);
      Align_option::set_int32(i_align);
   };
public: // overrides
   virtual void options();
   inline virtual ~Img() { flush();};
};

}; //namespace HTML
#endif

