#ifndef ELM_CLIENT_H
#define ELM_CLIENT_H

#ifndef _unix
#error This class is UNIX specific since it uses the UNIX based program ELM.
/* Do not include this class in the Windows version of your project.
   For C++ Builder projects, use the Builder STMP_email_client.
   For other Windows compilers, try the Eudora_email_client. (Eudora must be installed on the target machine).   
*/
#endif

/*_______*/ class ELM_email_client
/*_______*/ : public Common_email_client
/*_______*/ {
/*_______*/ public:
/*_______*/    ELM_email_client();
/*_______*/    virtual void send_from_file(const char *to_address, const char *subject1, const char *subject2, const char *body_filename);
/*_______*/
/*_______*/    virtual void compose_email_command_line
/*_______*/       (CORN_string         &email_command_line
/*_______*/       ,const CORN_string   &to_email_address
/*_______*/       ,const CORN_string   &subject_part_1
/*_______*/       ,const CORN_string   &subject_part_2
/*_______*/       ,const CORN_filename &body_filename
/*_______*/       );
/*_______*/
/*_______*/    virtual void compose_email_body
/*_______*/       (const CORN_filename &body_filename
/*_______*/       ,const CORN_string   &to_email_address
/*_______*/       ,const CORN_string &subject_part_1
/*_______*/       ,const CORN_string &subject_part_2
/*_______*/       );
/*_______*/ };

#endif

