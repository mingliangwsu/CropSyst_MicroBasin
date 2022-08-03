#ifndef elementH
#define elementH

#include "corn/format/html/types.h"
//150728 #include <corn/std/std_iostream.h>
// Element is the base class for all HTML document parts and elements
namespace HTML
{
class Element
: public Arbitrary
{
protected:
   Element *parent_element;
   CORN::Ustring marker;
   bool started;        // set to true once the attributes for the element have been output
public: // constructor
   Element
      (const CORN::Ustring &i_marker
      ,STD_NS ostream &i_doc );
   Element
      (const CORN::Ustring &i_marker
      ,Element *i_parent_element);
   inline virtual ~Element()
   {
      end();
   }
protected:
   inline virtual void flush()
   {  start_parent_if_necessary();
      start();
   }
   inline void start_parent_if_necessary()
   {  if (parent_element)
         parent_element->start();
   }
public:
   inline virtual void options() {}
   virtual void start();
   //{ if (!started) {simple(marker.c_str()); started = true;};};
   virtual inline void end()  { flush(); end(marker.c_str()); }
   // These functions can be also used to repeat an element block.
   // I.e. to use a font that has already been created.
protected: // used for outputting sub elements and attributes
   void end(const char *element_marker);
   // Used for ending most elements  I.e. </marker>
public: // accessors
   inline STD_NS ostream &get_parent_document_stream()
   {  return parent_element->get_document_stream(); }
   inline bool get_started() {return started;}
};
//______________________________________________________________________________
// The following are common attributes that can occur in various types of elements

class Core_attribute_options
{
   String_option   id;           // wsc4 ie3 ns4 o+ i? l+
   String_option    class_;       // wsc4 ie3 ns4 o+ i? l-
   String_option    style;        // wsc4 ie3 ns4 o+ i? l-
   String_option    title;         // wsc2 ie4 ns- o+-i? l-
public: // overrides
   inline Core_attribute_options()
      :id("ID")
      ,class_("CLASS")
      ,style("STYLE")
      ,title("TITLE")
      {}
   inline virtual void write(std::ostream &doc)
   {
      id.write(doc);
      class_.write(doc);
      style.write(doc);
      title.write(doc);
   }
};
//______________________________________________________________________________
class Event_options
{
   String_option    onclick;       // wsc4 ie3 ns2 o+ i? l-
   String_option    ondblclick;    // wsc4 ie3 ns2 o+ i? l-
   String_option    onkeypress;    // wsc4 ie4 ns4 o- i? l-
   String_option    onkeydown;     // wsc4 ie4 ns4 o- i? l-
   String_option    onkeyup;       // wsc4 ie4 ns4 o- i? l-
   String_option    onmousedown;   // wsc4 ie4 ns4 o- i? l-
   String_option    onmouseup;     // wsc4 ie4 ns4 o- i? l-
   String_option    onmouseover;   // wsc4 ie3 ns2 o+ i? l-
   String_option    onmousemove;   // wsc4 ie4 ns- o- i? l-
   String_option    onmouseout;    // wsc4 ie4 ns3 o+ i? l-
   String_option    language;      // wsc- ie4 ns- o- i? l-
public: // overrides
   inline Event_options()
      :onclick("onclick")
      ,ondblclick("ondblclick")
      ,onkeypress("onkeypress")
      ,onkeydown("onkeydown")
      ,onkeyup("onkeyup")
      ,onmousedown("onmousedown")
      ,onmouseup("onmouseup")
      ,onmouseover("onmouseover")
      ,onmousemove("onmousemove")
      ,onmouseout("onmouseout")
      ,language("language")
      {}

   inline virtual void write(STD_NS ostream &doc)
   {
      onclick.write(doc);
      ondblclick.write(doc);
      onkeypress.write(doc);
      onkeydown.write(doc);
      onkeyup.write(doc);
      onmousedown.write(doc);
      onmouseup.write(doc);
      onmouseover.write(doc);
      onmousemove.write(doc);
      onmouseout.write(doc);
      language.write(doc);
   }
};
//______________________________________________________________________________
class Load_event_options
{
   String_option    onload;       // wsc4 ie3 ns2 o+ i? l-
   String_option    onunload;     // wsc4 ie3 ns2 o+ i? l-
public: // overrides
   inline Load_event_options()
      :onload("ONUNLOAD")
      ,onunload("ONLOAD")
      {}
   inline virtual void write(STD_NS ostream &doc)
   {
      onload.write(doc);
      onunload.write(doc);
   }
};
//______________________________________________________________________________
class Focus_event_options
{
   String_option onfocus;          // wsc4 ie3 ns2 o+ i? l-
   String_option onblur;           // wsc4 ie3 ns2 o+ i? l-
public: // overrides
   inline Focus_event_options()
      : onfocus("ONFOCUS")
      , onblur("ONBLUR")
      {};
   inline virtual void write(STD_NS ostream &doc)
   {
      onfocus.write(doc);
      onblur.write(doc);
   }
};
//______________________________________________________________________________
extern const char *dir_label_table[];

class IL8N_options
{
   enum Dir {LTR,RTL};

//   DECLARE_LABELED_ENUM(Dir_labeled,Dir,dir_label_table)

   String_option   lang;               // wsc4 ie4 ns- o- i? l-
   Enum_option     dir;                // wsc4 ie5 ns- o- i? l-
public: // overrides
   inline IL8N_options()
      : lang("LANG")
      , dir("DIR",dir_label_table)
      {}
   inline virtual void write(STD_NS ostream &doc)
   {
      lang.write(doc);
      dir.write(doc);
   }
};
//______________________________________________________________________________
extern const char *dataformatas_label_table[];
class Data_options
{
   enum Dataformatas {PLAINTEXT,HTML};
//   DECLARE_LABELED_ENUM(Dataformatas_labeled,Dataformatas,dataformatas_label_table)

   String_option   datasrc;          // wsc4
   String_option   datafld;          // wsc4
   Enum_option     dataformatas;     // wsc4   Enum_option
public: // overrides
   inline Data_options()
      :datasrc("DATASRC")
      ,datafld("DATAFLD")
      ,dataformatas("DATAFORMATAS",dataformatas_label_table)
      {}
   inline virtual void write(STD_NS ostream &doc)
   {
      datasrc.write(doc);
      datafld.write(doc);
      dataformatas.write(doc);
   }
};
//______________________________________________________________________________
class Attribute_options
: public Core_attribute_options
, public Event_options
, public IL8N_options
{
public: // overrides
   inline Attribute_options()
      :Core_attribute_options()
      ,Event_options()
      ,IL8N_options()
      {};
   inline virtual void write(STD_NS ostream &doc)
   {
      Core_attribute_options::write(doc);
      Event_options::write(doc);
      IL8N_options::write(doc);
   }
};
//______________________________________________________________________________
class Height_option
{
protected:
   Uint_option  height;         // in height units
   Units        height_units;   // pixels,percent

public:
   inline Height_option()
      :height("HEIGHT")
      ,height_units(pixels)
      {};
   inline void set_height
   (uint16         i_height         // in height units
   ,Units     i_height_units = pixels)   // pixels,percent
   {
      height.set(i_height);
      height_units = i_height_units;
   }
public: // overrides
   inline virtual void write(STD_NS ostream &doc)
   {
      height.write(doc);
      if (height_units == percent)
         doc << '%';
   }
};
//______________________________________________________________________________
class Width_option
{
protected:
   Uint_option         width;         // in width units
   Units     width_units;   // pixels,percent
public:
   inline Width_option()
      :width("WIDTH")
      ,width_units(pixels)
      {}
   inline void set_width
   (uint16         i_width         // in width units
   ,Units     i_width_units = pixels)   // pixels,percent
   {
      width.set(i_width);
      width_units = i_width_units;
   }
public: // overrides
   inline virtual void write(STD_NS ostream &doc)
   {
      width.write(doc);
      if (width_units == percent)
         doc << '%';
   }
};
//______________________________________________________________________________
class Dimension_options
: public Height_option
, public Width_option
{
public:
   inline Dimension_options()
      :Height_option()
      ,Width_option()
      {}
public: // overrides
   inline virtual void write(STD_NS ostream &doc)
   {
      Height_option::write(doc);
      Width_option::write(doc);
   }
};
//______________________________________________________________________________
extern const char *align_label_table[];
class Align_option
: public Enum_option
{
public:
   enum Align {LEFT, CENTER,RIGHT
              ,JUSTIFY     // <- Text only
              ,BOTTOM      // <- CAPTION LEGEND IFRAME
              ,ABSBOTTOM   // <- INPUT
              ,MIDDLE      // <- IMG APPLET IFRAME
              ,TOP,BASELINE,ABSMIDDLE,TEXTTOP // <- IMG APPLET
               }; // Not justify not available form some aligns
public:
   inline Align_option(/*Align i_align = LEFT*/)
      : Enum_option("ALIGN",align_label_table)
      {}
   inline void set_align(Align i_align)
      { set_int32(i_align); }
};
//______________________________________________________________________________
extern const char *valign_label_table[];
class Valign_option
: public Enum_option
{
public:
   enum Valign {TOP,MIDDLE,BOTTOM,BASELINE}; // Not sure if MIDDLE or CENTER
public:
   inline Valign_option(Valign _valign = MIDDLE)
      :Enum_option("VALIGN",valign_label_table)
      {}
   inline void set_valign(Valign _valign)
      { set_int32(_valign); }
};
//______________________________________________________________________________
}; // namespace HTML

#endif

