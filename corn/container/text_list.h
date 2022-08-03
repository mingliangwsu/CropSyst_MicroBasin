#ifndef text_listH
#define text_listH

#include <string.h>

#ifndef bi_listH
#  include "corn/container/bilist.h"
#endif
#include "corn/string/strconv.hpp"

namespace CORN {
class Data_record;
// This is a simple list of text
//______________________________________________________________________________
class Item_string
: public implements_ CORN::Item , public extends_ std::string
{
 public:
   inline Item_string(const char *text)
      : CORN::Item()
      , std::string(text)
      {}
   inline Item_string(const char *text,size_t start, size_t n = std::string::npos)
      : CORN::Item()
      , std::string (text,start,n)
      {}
   inline Item_string(const wchar_t *text)
      : CORN::Item()
      , std::string ()
      {
         CORN::UnicodeZ_to_string(text,*this);
      }
   inline Item_string(const wchar_t *text,size_t start,size_t n = std::string::npos)
      : CORN::Item()
      , std::string()
      {
         std::wstring text_substr(text,start,n);
         CORN::wstring_to_string(text_substr,*this);
      }
   inline Item_string(const std::string &text)
      : CORN::Item()
      , std::string(text)
      {
      }
   inline Item_string(const std::wstring &text)
      : CORN::Item()
      , std::string ()
      {
         CORN::wstring_to_string(text,*this);
      }
   inline virtual const char *label_string(std::string &buffer)           const  //170424
         { buffer.append(c_str()); return buffer.c_str();}
   inline virtual const wchar_t *label_wstring(std::wstring &buffer)      const
         {  CORN::append_string_to_wstring((*this),buffer);                      //170831
            return buffer.c_str();}                                              //170101
   virtual bool write(std::ostream &strm)                            stream_IO_; //150728
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return (*this) == key; }

/*180820  was probably only used for find_cstr now using is_key
   
   inline virtual const char *get_key()                                   const  //160704
         { return std::string::c_str(); }
*/         
   inline virtual Item_string *clone()                                    const
         { return new Item_string(this->c_str()); }
         // WARNING should have copy constructor!!  171117
   inline virtual const std::string &append_to_string(std::string &buffer)    const
      {  buffer.append(*this); return buffer; }
   inline virtual const std::wstring &append_to_wstring(std::wstring &buffer) const
      {  CORN::append_string_to_wstring(*this,buffer); return buffer; }
};
//_2017-12-25______________________________________________________Item_string_/
class Item_wstring
: public implements_ CORN::Item , public extends_ std::wstring
{
 public:
   inline Item_wstring(const char *text)
      : CORN::Item()
      , std::wstring ()
      {
         CORN::ASCIIZ_to_wstring(text,*this);
      }
   inline Item_wstring(const char *text,size_t start, size_t n = std::string::npos)
      : CORN::Item()
      , std::wstring ()
      {
         std::string text_string(text,start,n);
         CORN::string_to_wstring(text_string,*this);
      }
   inline Item_wstring(const wchar_t *text)
      : CORN::Item()
      , std::wstring (text)
      {}
   inline Item_wstring(const wchar_t *text,size_t start,size_t n = std::string::npos)
      : CORN::Item()
      , std::wstring (text,start,n)
      {}
   inline Item_wstring(const std::string &text)
      : CORN::Item()
      , std::wstring()
      {
         CORN::string_to_wstring(text,*this);
      }
   inline Item_wstring(const std::wstring &text)
      : CORN::Item()
      , std::wstring (text)
      {}

   // NYN Item_wstring(const std::string &text,size_t start, size_t n = std::string::npos)
   // NYN Item_wstring(const std::wstring &text,size_t start, size_t n = std::string::npos)

   inline virtual Item_wstring *clone()                                    const //180115
      { return new Item_wstring(this->c_str()); }
         // WARNING should have copy constructor!!  171117

   inline virtual const std::string &append_to_string(std::string &buffer) const
      {  CORN::append_wstring_to_string(*this,buffer); return buffer; };
   inline virtual const std::wstring &append_to_wstring(std::wstring &buffer) const
      {  buffer.append(*this); return buffer; }
};
//_2017-12-25_____________________________________________________Item_wstring_/
// Text list is deprecated because Container, now provides a string_items
// It is only missing constructor taking initial text
// This functionallity can be provided with a global function
// string_to_container


class Text_list
: public extends_ Bidirectional_list  // so we can sort
{public:

   // Item has been replaced with Item_string but it is provided for compatibility

 public:
   Text_list
      (const char *initial_text = 0
      ,char separator_character = '\n');                                         //090918
   /* Conceptual
   Text_list
      (const wchar_t *initial_text = 0
      ,wchar_t separator_character = '\n');                                      //090918
   */
      // This constructor takes all_text which contains \n separated
      // text strings and composes an initial list of text.
   Text_list(const Text_list &copy_from);                                        //170101
   inline  virtual ~Text_list()                                               {} //081125
   nat32 copy(const Text_list &copy_from)                         modification_; //170101
   virtual Item *find(const char *search_key,bool case_sensitive = true)  const;
   virtual Item *find_string (const std::string &search_key, bool case_sensitive = true) const; //130310
   virtual Item *find_wstring(const std::wstring &search_key,bool case_sensitive = true) const;
        // find should be renamed find_cstr

   // Note that uniqueness is now a property of container
   // the unique parameter is now redundent  151002

   Item_string  *add_cstr(const char *text_to_add);                              //110228_060910
   Item_wstring *add_wstr(const wchar_t *text_to_add);                           //120209
   Item_string  *add_string (const std::string  &text_to_add);                   //130123
   Item_wstring *add_wstring(const std::wstring &text_to_add);                   //130123
      //121012 add_cstr and add_wstr were previously both named 'add'
      //but some compilers complain and/or cannot handle this contravariant overloading.

/*171225  conceptual I haven't implemented these because Text_list can not be deprecated
by using
   // The append text methods are replacing the deprecated add_XXX methods.
   bool append_text(const char         *text_to_append);                         //171226
   bool append_text(const wchar_t      *text_to_append);                         //171226
   bool append_text(const std::string  &text_to_append);                         //171226
   bool append_text(const std::wstring &text_to_append);                         //171226
*/


   /*171225 moved to Container
   virtual nat32 string_items
      (std::string &string_buffer,   char   separator =  '\n')            const; //171225
   virtual nat32 string_items
      (std::wstring &string_buffer, wchar_t separator = L'\n')            const; //171225

//   virtual nat32 wstring_items(std::wstring &string_buffer,  wchar_t separator = L'\n') const;   //161231
   */

      ///< Composes a string representation of the items which is appended to buffer.
      /// The string_buffer is not cleared, it may have previously composed text which is left intact.
      /// (so if there are no items the string buffer would not be changed).
      /// The separator is appended between items (not prepended or appended).
      /// \returns the number of items appended
};
//______________________________________________________________________________
}; // namespace CORN

#endif

