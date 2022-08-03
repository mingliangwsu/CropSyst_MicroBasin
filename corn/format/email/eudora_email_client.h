#ifndef EUDORA_CLIENT_H
#define EUDORA_CLIENT_H

#ifndef _Windows
#error This class is Windows specific since it uses the Eudora for Windows.
/* Do not include this class in the UNIX version of your project.
   For UNIX try the ELM_email_client (Requires ELM installed on the target machine).
*/
#endif

//#include <corn/cstrngem.h>
#include <corn/format/email/common_email_client.h>
#include <corn/file_sys/filename.h>

//class Email_message;

/*_______*/ class Eudora_email_client
/*_______*/ : public Common_email_client
/*_______*/ {
/*_______*/    CORN_string body;
/*_______*/    CORN::File_name body_filename;
/*_______*/    CORN_string email_command_line;
/*_______*/ public:
               Eudora_email_client()
/*_______*/    : Common_email_client()
/*_______*/    {};

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
/*_______*/ private:
/*_______*/    void add_file_to_body(const char *filename);

/*_______*/    void  compose_message
/*_______*/    (const CORN::Email_message &message
/*_______*/    ,const char *prescript_filename
/*_______*/    ,const char *postscript_filename
/*_______*/    );


#ifdef OBSOLETE
/*_______*/    virtual void send_from_file(const char *to_address, const char *subject1, const char *subject2, const char *body_filename);
/*_______*/
/*_______*/    virtual void compose_email_command_line
/*_______*/       (CORN_string         &email_command_line
/*_______*/       ,const CORN_string   &to_email_address
/*_______*/       ,const CORN_string   &subject_part_1
/*_______*/       ,const CORN_string   &subject_part_2
/*_______*/       ,const CORN::File_name &body_filename
/*_______*/       ) = 0 ;
/*_______*/
/*_______*/    virtual void compose_email_body
/*_______*/       (const CORN::File_name  &body_filename
/*_______*/       ,const CORN_string   &to_email_address
/*_______*/       ,const CORN_string &subject_part_1
/*_______*/       ,const CORN_string &subject_part_2
/*_______*/       ) = 0;
#endif
/*_______*/ };

#endif
