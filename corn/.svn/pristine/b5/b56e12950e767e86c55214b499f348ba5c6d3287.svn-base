#ifndef COMMON_EMAIL_CLIENT_H
#define COMMON_EMAIL_CLIENT_H

class CORN_string;
namespace CORN
{
   class File_name;
   class Email_message;
};

/*_______*/ class Common_email_client
/*_______*/ {
/*_______*/ public:
/*_______*/    Common_email_client()
/*_______*/    {};

/*030417_*/    virtual bool send_message
/*_______*/    (const CORN::Email_message &message
/*_______*/    ,const char *prescript_filename = 0
/*_______*/    ,const char *postscript_filename = 0
/*_______*/    ) = 0;
//_______//    This will send a message (where the email header fields
//_______//    and text body are specified in message object.
//_______//    If prescript_filename and/or postscript_filename is specified,
//_______//    the specified file will be loaded and output before and after
//_______//    the message.body respectively.
//_______//
/*_______*/ };

#endif