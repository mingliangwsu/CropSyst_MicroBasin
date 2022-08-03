
#include <corn/format/html/form_IO/content.h>
//130919 #include <corn/string/ustring.h>
//______________________________________________________________________________
const char *request_method_label_table[] =
{"DEBUG"    // May also be default
,"GET","POST",0};
//______________________________________________________________________________
char x2c(const char *what)
{   register char digit;
    digit = (char)(what[0] >= 'A' ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
    digit *= (char)16;
    digit += (char)(what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));
    return(digit);
}
//______________________________________________________________________________
void unescape_url(std::string &url)
{
   register int x;
   std::string new_url("");
   for (x = 0; x < (int)url.length(); x++)
   {  char new_char[2]; new_char[1] = 0;                                          //010308
      switch(url[x])
      {
        case '+' : new_char[0] = ' '; break;
        case '%' : new_char[0] = x2c(&url.c_str()[x+1]); x+=2; break;
        default  : new_char[0] = url[x];
        break;
      }
#ifdef __BORLANDC__
      new_url.append(new_char);
#else
      new_url += new_char;
#endif

   }
   url.assign(new_url);
}
//______________________________________________________________________________
void replace_with(std::string &str,char oldc, char newc)
{
   std::string news(str);
   for (int i = 0; i < (int)str.length();i++)
      if (str[i] == oldc) news[i] = newc;
   str.assign(news);
}
//______________________________________________________________________________
