

#ifndef CORN_EMAIL_MESSAGE_H
#define CORN_EMAIL_MESSAGE_H

#include <corn/format/datarec.h>

namespace CORN
{

class Email_message
: public Data_record
{
public:
   // Header
   CORN_string header_to_address_SDF;      // To:
   CORN_string header_subject;   
   CORN_string header_from_address;    // From:
   CORN_string header_from_name;       // On output will be added to the From: field  I.e. Name <xxx@yyy.zzz>
   CORN_string header_reply_to;        // Reply-To:
   CORN_string header_X_mailer;        // X-Mailer: (program generating the email message)
//NYI   CORN::Date  header_date_sent;       // Date: Wed, 16 Apr 2003 16:18:05 -0300
   CORN_string header_cc_SDF;              // Cc:  (Carbon copy)
   CORN_string header_bcc_SDF;             // Bcc: (Blind carbon copy)
   CORN_string header_attached_SDF;        // Attached: "filename"

   // SDF indicates the string can be in System data format.
   // I believe I can use System data format for all to/from fields and attachements

   CORN_string body;
   CORN_string signature;
public:
   Email_message()
   : Data_record("email")
   {
   };


   void get_signature_from_file(const char *filename);
   void get_body_from_file(const char *filename);
};


}; // namespace CORN

#endif

