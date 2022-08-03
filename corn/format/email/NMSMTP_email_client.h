

#ifndef NMSMTP_CLIENT_H
#define NMSMTP_CLIENT_H

#include <NMsmtp.hpp>

#if (__BCPLUSPLUS__ < 0x0550)
#error This class requires Borland C++ Builder
// this may also work in builder version 3 (0x0530) and version 4 (0x0540), but haven't tried
For Unix or other Windows compilers, try one of the other email client classes.
#endif

#include <corn/format/email/common_email_client.h>
//class TNMSMTP;

/*_______*/ class NMSMTP_email_client
/*_______*/ : public Common_email_client
/*_______*/ {
/*_______*/    TNMSMTP *nmsmtp_component;
/*_______*/ public:
/*_______*/    NMSMTP_email_client(TNMSMTP *i_nmsmtp_component/*,char *userid, char*password*/)
/*_______*/    : Common_email_client()
/*_______*/    , nmsmtp_component(i_nmsmtp_component)
/*_______*/    {
///*_______*/       nmsmtp_component->UserID =userid;
//*_______*/       nmsmtp_component->Password =password;
/*_______*/    };

/*030417_*/    virtual bool send_message
/*_______*/    (const CORN::Email_message &message
/*_______*/    ,const char *prescript_filename = 0
/*_______*/    ,const char *postscript_filename = 0
/*_______*/    );
//_______//    This will send a message (where the email header fields
//_______//    and text body are specified in message object.
//_______//    If prescript_filename and/or postscript_filename is specified,
//_______//    the specified file will be loaded and output before and after
//_______//    the message.body respectively.
//_______//
/*_______*/    void add_file_to_body(const char *filename);
#ifdef OBSOLETE
/*_______*/    virtual void send_from_file(const char *to_address, const char *subject1, const char *subject2, const char *body_filename);
/*_______*/
/*_______*/    virtual void compose_email_body
/*_______*/       (const char */*const CORN::File_name &*/body_filename
/*_______*/       ,const char */*const CORN_string   &*/to_email_address
/*_______*/       ,const char */*const CORN_string   &*/subject_part_1
/*_______*/       ,const char */*const CORN_string   &*/subject_part_2
/*_______*/       );
#endif
/*_______*/ };

#endif

