#include <corn/format/html/types.h>

using namespace CORN;

using namespace std; // 091123
namespace HTML
{

char *units_label_table[]=
{""
,"%"
,0
};

void Arbitrary::text_out(const Ustring &out_text)
{
   flush();
   document << ' ' << out_text << ' ';
};

void Arbitrary::simple(const char *element_marker)
{  flush();
      document << '<' << element_marker << '>';
};


void Arbitrary::float32_out(float32 value)
{  flush();
   document << CORN::float32_to_str(value,4);
};

void Arbitrary::color(char *color_appl,uint32 color_code)
{
   char code_str[10];
   CORN_uint32_to_str(color_code,code_str,16);
   Ustring leading_zeros('0',6-strlen(code_str));
   document << ' ' << color_appl << "=\"#";
   document << leading_zeros << code_str << "\"";
};

void Arbitrary::A_HREF(const Ustring &url,const Ustring &target_frame)
{
   document << "<A HREF=\"" << url << "\"";
   if (target_frame.length())
      document << " TARGET=\"" << target_frame << "\"";
   document << ">" << endl;
};

void Arbitrary::XA()
{
   document << "</A>" << endl;
};



void Arbitrary::FONT_COLOR(uint32 color_code)
{
   document << "<FONT";
   color("COLOR",color_code);
   document << ">";
};

void Arbitrary::XFONT()
{
   document << "</FONT>" << endl;
};
}; // namespace HTML
