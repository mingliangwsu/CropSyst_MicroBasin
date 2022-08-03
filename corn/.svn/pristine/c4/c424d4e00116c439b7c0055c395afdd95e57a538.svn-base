#ifndef CORN_HTML_H
#define CORN_HTML_H

// These html macros are being replaced by HTML_xxx classes

extern char HTML_TITLE[];     extern char HTML_XTITLE[];
extern char HTML_CENTER[];    extern char HTML_XCENTER[];

extern char HTML_BODY[];      extern char HTML_XBODY[];

extern char HTML_HEAD[];      extern char HTML_XHEAD[];

extern char HTML_H1[];        extern char HTML_XH1[];
extern char HTML_H2[];        extern char HTML_XH2[];
extern char HTML_H3[];        extern char HTML_XH3[];
extern char HTML_HR[];
extern char HTML_HTML[];      extern char HTML_XHTML[];

extern char HTML_XLAYER[];

extern char HTML_P[];
extern char HTML_BR[];

extern char HTML_TD[];        extern char HTML_XTD[];
extern char HTML_TD_CENTER[];

extern char HTML_TR[];        extern char HTML_XTR[];
extern char HTML_TH[];
extern char HTML_TH_CENTER[];

extern char HTML_B[];         extern char HTML_XB[];
extern char HTML_BLINK[];     extern char HTML_XBLINK[];

                              extern char HTML_XSELECT[];
extern char HTML_TABLE[];     extern char HTML_XTABLE[];

extern char HTML_UL[];        extern char HTML_XUL[];
extern char HTML_OL[];        extern char HTML_XOL[];
extern char HTML_DL[];        extern char HTML_XDL[];
extern char HTML_DT[];
extern char HTML_DD[];
extern char HTML_LI[];

extern char HTML_SCRIPT_JAVASCRIPT[];
extern char HTML_XSCRIPT[];

#define HTML_BODY_BGCOLOR(bgcolor) "<BODY BGCOLOR=\"" << bgcolor << "\">"
#define HTML_BODY_BGCOLOR_ONLOAD(bgcolor,onload) "<BODY BGCOLOR=\"" << bgcolor << "\" onLoad=\"" << onload << "\"> 
#define HTML_FORM(post,action)  "<FORM method=\"" << (post ? "POST" : "GET") << "\" ACTION=\"" << action << "\">"
extern char HTML_XFORM[];

#define HTML_INPUT_HIDDEN(name,value) "<INPUT TYPE=\"HIDDEN\" NAME=\"" << name << "\" VALUE=\"" << value << "\">"
#define HTML_INPUT_TEXT(name,value,size,maxlength) "<INPUT TYPE=\"TEXT\" NAME=\"" << name << "\" VALUE=\"" << value << "\" SIZE=" << size << " MAX_LENGTH=" << maxlength << ">"
#define HTML_INPUT_RADIO(name,value,checked,text) "<INPUT TYPE=\"RADIO\" NAME=\"" << name << "\" VALUE=\"" << value << "\" " << ( checked ? "CHECKED>" : ">") << text
#define HTML_INPUT_CHECKBOX(name,checked,text)    "<INPUT TYPE=\"CHECKBOX\" NAME=\"" << name << "\"" << (checked ? "CHECKED" : "") << ">" << text
#define HTML_INPUT_CHECKBOX_VALUE(name,checked,value,text)    "<INPUT TYPE=\"CHECKBOX\" NAME=\"" << name << "\" VALUE=\"" << value << "\" " << (checked ? "CHECKED" : "") << ">" << text
#define HTML_SELECT(name) "<SELECT NAME=\"" << name << "\">"
extern char HTML_XSELECT[];
#define HTML_SELECT_OPTION(value,selected,text) "<OPTION VALUE=\"" << value << "\" " << ((selected) ? "SELECTED" : " ") << ">" << text << endl

#define HTML_A_HREF(url) "<A HREF=\"" << url << "\">"
#define HTML_A_HREF_TARGET(url,target) "<A TARGET=\"" << target << "\" HREF=\"" << url << "\">"
#define HTML_A_HREF_MOUSEOVER(url,onmouseover) "<A HREF=\"" << url << "\" onMouseOver=\"" << onmouseover << "\">"
extern char HTML_XA[];
#define HTML_SUBMIT(text) "<INPUT TYPE=\"SUBMIT\" VALUE=\"" << text << "\">"
#define HTML_IMG(src,alt) "<IMG SRC=\"" << src << "\" ALT=\"" << alt << "\">"
#define HTML_IMG_SIZE(src,alt,width) "<IMG SRC=\"" << src << "\" ALT=\"" << alt << "\" WIDTH=" << width << ">"

#endif

