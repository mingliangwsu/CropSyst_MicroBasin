#ifndef HTML_FORM_REQUEST_H
#define HTML_FORM_REQUEST_H

/* This class parses submitted HTLM form data which can be get() to a data record.

*/

#include "corn/format/datasrc.h"
#include "corn/string/cstrngem.h"

namespace HTML
{
 class Common_form_IO; // for friendship
//______________________________________________________________________________
 class HTML_form_request
 : public CORN::Data_source
 { friend class Common_form_IO;
   std::string ontent;
 public:
   HTML_form_request();
   virtual bool get(CORN::Data_record &data_rec);
   virtual bool set(CORN::Data_record &data_rec);
   //170423 virtual const char *label_cstr(char *buffer) const;
   virtual bool validate (std::string &errors) const = 0;
 protected:
   virtual bool set_data(Data_record &data_rec) { return true; /*NYI*/} ;        //170423
};
//______________________________________________________________________________
}; // namespace HTML

#endif

