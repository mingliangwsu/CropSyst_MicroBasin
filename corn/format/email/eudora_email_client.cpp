#include <corn/std/std_fstream.h>
#include <corn/format/email/eudora_email_client.h>
#include <corn/format/email/message.h>
#include <stdio.h>
#include <windows.h>

//extern unsigned int /*UINT */ WinExec(void */*LPCSTR */lpszCmdLine, unsigned int  fuCmdShow);

/*030417_*/ bool Eudora_email_client::send_message
/*_______*/ (const CORN::Email_message &message
/*_______*/ ,const char *prescript_filename
/*_______*/ ,const char *postscript_filename
/*_______*/ )
/*_______*/ {
//_______//    This will send a message (where the email header fields
//_______//    and text body are specified in message object.
//_______//    If prescript_filename and/or postscript_filename is specified,
//_______//    the specified file will be loaded and output before and after
//_______//    the message.body respectively.

///*_______*/    body_filename.set("temp.msg");

/*_______*/    body_filename.set_file(tempnam("","nttmp"));
/*_______*/    email_command_line.assign("eudora ");
/*_______*/    email_command_line.append(body_filename);
/*_______*/    compose_message(message,prescript_filename,postscript_filename);
/*_______*/    WinExec(email_command_line.c_str(),SW_HIDE);
/*_______*/    return true;
/*_______*/ };

/*_______*/ void  Eudora_email_client::compose_message
/*_______*/ (const CORN::Email_message &message
/*_______*/ ,const char *prescript_filename
/*_______*/ ,const char *postscript_filename
/*_______*/ )
//             Eudora requires .msg extension, we will simply use that extension for unix as well
/*_______*/ {
/*_______*/       ofstream body_file(body_filename.c_str());

//                Eudora needs to and subject in the body of the msg
/*_______*/       body_file << "to: "        << message.header_to_address_SDF << endl;
/*_______*/       body_file << "from: "      <<  message.header_from_address << endl;
/*_______*/       body_file << "X-mailer: "  <<  message.header_X_mailer << endl;
/*_______*/       body_file << "Reply-To: "  << message.header_reply_to << endl;

/*_______*/       body_file << "Subject: "   << message.header_subject << endl;
/*_______*/       body_file << "bcc: "       << message.header_bcc_SDF << endl;
/*_______*/       body_file << "cc: "        << message.header_cc_SDF << endl;
/*_______*/    // Don't know how to set up attachements
/*_______*/
/*_______*/       if (prescript_filename)
/*_______*/          add_file_to_body(prescript_filename);
/*_______*/       // Note, may need to separate each line
/*_______*/       body.append(message.body.c_str());
/*_______*/       if (postscript_filename)
/*_______*/          add_file_to_body(postscript_filename);
/*_______*/ };

/*_______*/ void Eudora_email_client::add_file_to_body(const char *filename)
/*_______*/ {
/*_______*/    CORN_string body_line;
/*_______*/    ifstream body_file(filename);
/*_______*/    while (!body_file.eof())
/*_______*/    {
/*_______*/       body_line.read_line(body_file);
/*_______*/       body.append(body_line);
/*_______*/    };
/*_______*/ };
/*_______*/

#ifdef OBSOLETE
/*_______*/ void Eudora_email_client::compose_email_command_line
/*_______*/ (CORN_string         &email_command_line
/*_______*/ ,const CORN_string   &to_email_address
/*_______*/ ,const CORN_string   &subject_part_1
/*_______*/ ,const CORN_string   &subject_part_2
/*_______*/ ,const CORN_filename &body_filename
/*_______*/ )
/*_______*/ {
/*_______*/       email_command_line.assign("eudora ");
/*_______*/       email_command_line.append(body_filename);
/*_______*/ };

/*_______*/ void Eudora_email_client::compose_email_body
/*_______*/ (const CORN_filename &body_filename
/*_______*/ ,const CORN_string   &to_email_address
/*_______*/ ,const CORN_string &subject_part_1
/*_______*/ ,const CORN_string &subject_part_2
/*_______*/ )
/*_______*/ {  ofstream notify_body_file(body_filename.get());
// Eudora needs to and subject in the body of the msg
/*_______*/    notify_body_file << "to: " << to_email_address << endl;
/*_______*/    notify_body_file << "subject: " << subject_part_1 << ' '<< subject_part_2 << endl;
/*_______*/    write(notify_body_file);
/*_______*/ };


/*_______*/ void Eudora_email_client::send_from_file
/*_______*/ (const CORN_string &email_address
/*_______*/ ,const CORN_string   &subject_part_1
/*_______*/ ,const CORN_string   &subject_part_2
/*_______*/ ,const CORN_filename &body_filename)
/*_______*/ {
/*_______*/    CORN_string email_command;
/*_______*/    compose_email_command_line
/*_______*/       (email_command
/*_______*/       ,email_address
/*_______*/       ,subject_part_1
/*_______*/       ,subject_part_2
/*_______*/       ,body_filename
/*_______*/       );
/*_______*/    WinExec(email_command,SW_HIDE);
//             Once the mail is sent we can delete the body file
//TEMP DISABLED /*_______*/    unlink(body_filename.get());
/*_______*/ };
#endif
