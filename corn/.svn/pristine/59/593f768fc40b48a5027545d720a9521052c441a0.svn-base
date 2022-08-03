#ifndef tableH
#define tableH

#include "corn/format/html/element.h"
#define M_TABLE "TABLE"

namespace HTML {
#if (!(__BCPLUSPLUS__ >= 0x0550))
// Builder doesn't seem to like forward enum declarations
enum HTML_units;
#endif
extern const char *scope_label_table[];

class Body;
//______________________________________________________________________________
class Table
: public Element
, public Dimension_options
, public Align_option
{
public:
   // attributes
   enum Frame { VOID_,ABOVE,BELOW,HSIDES,VSIDES,LHS,RHS,BOX,BORDER };
   enum Rules { NONE,GROUP,ROWS,COLS,ALL};

   Uint_option  border;        // in pixels
   Uint_option  cellspacing;   // pixels
   Uint_option  cellpadding;   // pixels
   /*NYI
   Frame          frame;
   Rules          rules
   std::string    summary;
   HTML_color     bgcolor;
   HTML_color     bordercolor;
   HTML_color     bordercolordark;
   HTML_color     bordercolorlight;
   nat16         cols;
   nat16         datapagesize;     // ???
   */

public:
   Table(Body *i_parent_element);
   inline virtual ~Table()                                           { flush();}
public: // overrides
   virtual void options();
public: // attribute accessors
   inline void set_border     (nat16 border_)          {  border.set(border_); }
   inline void set_cellpadding(nat16 padding)     {  cellpadding.set(padding); }
   inline void set_cellspacing(nat16 spacing)     {  cellspacing.set(spacing); }
protected: // base classes for table elements
   class Table_element
   : public Element
   , public Attribute_options
   , public Align_option
   , public Valign_option
   {
    public:
      inline Table_element(const std::string &i_marker,Element *parent_table)
         : Element(i_marker,parent_table)                                     {}
      inline virtual ~Table_element()                                { flush();}
    public: // overrides
      virtual void options();
   };
   //_Table_element____________________________________________________________/
   class Ext_table_element
   : public Table_element
   {
    public:
      Color_option    bgcolor;
      char              char_;   // ?
      Uint_option     charoff; // ?
    public:
      inline Ext_table_element(const std::string &marker_,Element *parent_table)
         : Table_element                                  (marker_,parent_table)
         , bgcolor                                                   ("BGCOLOR")
         , char_                                                             (0)
         , charoff                                                   ("CHAROFF")
         {}
      inline virtual ~Ext_table_element()                            { flush();}
   public: // overrides
      virtual void options();
      inline void set_bgcolor(const Color &color_)      { bgcolor.set(color_); }
   };
   //_Ext_table_element_________________________________________________________
   class Table_element_block
   : public Ext_table_element
   , public Height_option
   {
   public:
      Bool_option  nowrap;
      Color_option  bordercolor;
      Color_option  bordercolordark;
      Color_option  bordercolorlight;
      URI_option              background;
   public:
      inline Table_element_block(const std::string &i_marker,Element *parent_element)
      : Ext_table_element(i_marker,parent_element)
      , nowrap("NOWRAP")
      , bordercolor("BORDERCOLOR")
      , bordercolordark("BORDERCOLORDARK")
      , bordercolorlight("BORDERCOLORLIGHT")
      , background("BACKGROUND")
      {};
      inline virtual ~Table_element_block() { flush();};
   public: // overrides
      virtual void options();
      inline virtual void set_background(const std::string &i_URI)
      { background.set(i_URI); };
   };

   public: //table elements
   //___________________________________________________________________________
   #define M_CAPTION "CAPTION"
   class Caption
   : public Table_element
   {
    public:
      inline Caption(Table *parent_table)
         : Table_element(M_CAPTION,parent_table)                              {}
         // This constructor is used with captions with extensive text
      inline Caption(Table *parent_table,const std::string &text)
        : Table_element(M_CAPTION,parent_table)              { text_out(text); }
         // This constructor can be used when there is only a short text string.
         // This is the most common case.
      inline virtual ~Caption()                                      { flush();}
   };
   //___________________________________________________________________________
   #define M_THEAD "THEAD"
   class Thead
   : public Ext_table_element
   {
   public:
      inline Thead(Table *parent_table)
         : Ext_table_element(M_THEAD,parent_table)
         {}
      inline virtual ~Thead() { flush();}
   };
   #define M_TBODY "TBODY"
   class Tbody
   : public Ext_table_element
   {
    public:
      inline Tbody(Table *parent_table)
      : Ext_table_element(M_TBODY,parent_table)
      {}
      inline virtual ~Tbody() { flush();};
   };
   //___________________________________________________________________________
   #define M_Tfoot "Tfoot"
   class Tfoot
   : public Ext_table_element
   {
   public:
      inline Tfoot(Table *parent_table)
      : Ext_table_element(M_Tfoot,parent_table)                               {}
      inline virtual ~Tfoot()                                        { flush();}
   };
   //___________________________________________________________________________

   #define M_COLGROUP "Colgroup"
   class Colgroup
   : public Ext_table_element
   , public Width_option
   {
   public:
      Uint_option  span;
   public:
      inline Colgroup(Table *parent_table)
      : Ext_table_element(M_COLGROUP,parent_table)
      , Width_option()
      , span("SPAN")
      {}
      inline virtual ~Colgroup() { flush();}

   public: // overrides
      virtual void options()
   };
   //___________________________________________________________________________

#define M_COL "COL"
   class Col
   : public Ext_table_element
   , public Width_option
   {
   public:
      Uint_option  span;
   public:
      inline  Col(Table *parent_table)
      : Ext_table_element(M_COL,parent_table)
      , Width_option()
      , span("SPAN")
      {}
      inline virtual ~Col() { flush();}
   public: // overrides
      virtual void options();
   };
   //___________________________________________________________________________
   #define M_TR "TR"
   class Tr
   : public Table_element_block
   {
    public:
      inline Tr(Table *parent_table)
      : Table_element_block(M_TR,parent_table)
      {}
      inline virtual ~Tr() { flush();}
    protected: // tr elements
      class Table_cell
      : public Table_element_block
      , public Width_option
      {
      public:
         enum  Scope{DEFAULT,ROW,COL,ROWGROUP,COLGROUP};
//         DECLARE_LABELED_ENUM(Scope_labeled,Scope,scope_label_table)

         Uint_option     colspan; // columns
         Uint_option     rowspan; // rows
         String_option   abbr;
         String_option   axis;
         Enum_option    scope; // was Enum_option
         /* NYI
         headers
         scope
         */

       public:
            inline Table_cell(const std::string &marker_,Tr *parent_tr)
            : Table_element_block                 (marker_,(Element *)parent_tr)
            , Width_option                                                    ()
            , colspan                                                ("COLSPAN")
            , rowspan                                                ("ROWSPAN")
            , abbr                                                      ("ABBR")
            , axis                                                      ("AXIS")
            , scope                                  ("SCOPE",scope_label_table)
            {}
         inline virtual ~Table_cell()                                { flush();}
         inline void set_colspan(nat16 colspan_)      { colspan.set(colspan_); }
         inline void set_rowspan(nat16 rowspan_)      { rowspan.set(rowspan_); }
       public: // overrides
         virtual void options();
      };
      //___________________________________________________________________________
   public:
#define M_TD "TD"
      class Td
      : public Table_cell
      {
      public:
         inline Td(Tr *parent_tr)
         :Table_cell(M_TD,parent_tr)
         {}
         inline virtual ~Td() { flush();}
      };
      //________________________________________________________________________
#define M_TH "TH"
      class Th
      : public Table_cell
      {
      public:
         inline Th(Tr *parent_tr)
         :Table_cell(M_TH,parent_tr)
         {}
         inline virtual ~Th() { flush();}
      };
      //________________________________________________________________________
   };
};
//______________________________________________________________________________
} // namespace HTML
#endif

