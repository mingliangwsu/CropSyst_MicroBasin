#ifndef CORN_Body_H
#define CORN_Body_H

#include <corn/format/html/structure.h>
namespace HTML
{
class Body
: public Element
{
protected:

   URI_option   background;
   Color_option bgcolor;
   Color_option text;
   Color_option link;
   Color_option alink;
   Color_option vlink;

public: // constructors
   inline Body(Document *doc)
   : Element("BODY",doc)
   , background("BACKGROUND")
   , bgcolor("BGCOLOR")
   , text("TEXT")
   , link("LINK")
   , alink("ALINK")
   , vlink("VLINK")
   {};
   // Default mode

   inline virtual void options()
   {
      background.write(document);
      bgcolor.write(document);
      text.write(document);
      link.write(document);
      alink.write(document);
      vlink.write(document);
   };

   inline virtual void set_text(const Color &i_color)    { text.set(i_color); };
   inline virtual void set_bgcolor(const Color &i_color) { bgcolor.set(i_color); };
   inline virtual void set_link(const Color &i_color)    { link.set(i_color); };
   inline virtual void set_alink(const Color &i_color)   { alink.set(i_color); };
   inline virtual void set_vlink(const Color &i_color)   { vlink.set(i_color); };


/*NYI
   Body
   (HTML_URL   i_url
   ,HTML_color i_bgcolor  = default_color
   ,HTML_color i_text     = default_color
   ,HTML_color i_link     = default_color
   ,HTML_color i_alink    = default_color
   ,HTML_color i_vlink    = default_color
   );
   // background image

   Body
   (HTML_color i_bgcolor  = default_color
   ,HTML_color i_bgcolor  = default_color
   ,HTML_color i_text     = default_color
   ,HTML_color i_link     = default_color
   ,HTML_color i_alink    = default_color
   ,HTML_color i_vlink    = default_color
   );
*/

};

}; // namespace HTML
#endif

