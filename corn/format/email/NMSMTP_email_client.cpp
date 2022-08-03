#include <corn/std/std_fstream.h>
#include <corn/format/email/NMSMTP_email_client.h>
#include <corn/format/email/message.h>
#include <corn/cstrngem.h>

   CORN_string header_Attached;        // Attached: "filename

   // I believe I can use System data format for all to/from fields and attachements

   CORN_string body;
   CORN_string signature;

/*030417_*/ bool NMSMTP_email_client::send_message
/*_______*/ (const Email_message &message
/*_______*/ ,const char *prescript_filename
/*_______*/ ,const char *postscript_filename
/*_______*/ )
/*_______*/ {
//_______//    This will send a message (where the email header fields
//_______//    and text body are specified in message object.
//_______//    If prescript_filename and/or postscript_filename is specified,
//_______//    the specified file will be loaded and output before and after
//_______//    the message.body respectively.
/*_______*/
/*_______*/       nmsmtp_component->PostMessage->FromAddress = message.header_from_address.c_str();
/*_______*/       nmsmtp_component->PostMessage->FromName = message.header_from_name.c_str();
/*_______*/       nmsmtp_component->PostMessage->LocalProgram = message.header_X_mailer.c_str(); //"Web registration";
/*_______*/       nmsmtp_component->PostMessage->ReplyTo = message.header_reply_to.c_str();
/*_______*/       AnsiString full_subject = message.header_subject.c_str(); //subject_part_1 + " " + subject_part_2;
/*_______*/       nmsmtp_component->PostMessage->Subject = full_subject;

/*_______*/       {
#ifdef obsolete
/*_______*/          TStringList *to_addresses =  new TStringList;
/*_______*/          to_addresses->CommaText = message.header_to_address_SDF.c_str();
/*_______*/          nmsmtp_component->PostMessage->ToAddress->AddStrings(to_addresses);
/*_______*/          delete to_addresses;
#endif
/*_______*/          nmsmtp_component->PostMessage->ToAddress->Text = message.header_to_address_SDF.c_str();
/*_______*/       };
/*_______*/       {
/*_______*/          TStringList *bcc_addresses = new TStringList;
/*_______*/          bcc_addresses->CommaText = message.header_bcc_SDF.c_str();
/*_______*/          nmsmtp_component->PostMessage->ToBlindCarbonCopy->AddStrings(bcc_addresses);
/*_______*/          delete bcc_addresses;
/*_______*/       };
/*_______*/       {
/*_______*/          TStringList *cc_addresses = new TStringList;
/*_______*/          cc_addresses->CommaText = message.header_cc_SDF.c_str();
/*_______*/          nmsmtp_component->PostMessage->ToCarbonCopy->AddStrings(cc_addresses);
/*_______*/          delete cc_addresses;
/*_______*/       };
/*_______*/       {
/*_______*/          TStringList *attachements = new TStringList;
/*_______*/          attachements->CommaText = message.header_attached_SDF.c_str();
/*_______*/          nmsmtp_component->PostMessage->Attachments->AddStrings(attachements);
/*_______*/          delete attachements;
/*_______*/       };
/*_______*/
/*_______*/       if (prescript_filename)
/*_______*/          add_file_to_body(prescript_filename);
/*_______*/       // Note, may need to separate each line
/*_______*/       TStringList *message_body_strings = new TStringList;
/*_______*/       message_body_strings->Text = message.body.c_str();
/*_______*/       nmsmtp_component->PostMessage->Body->AddStrings(message_body_strings);
/*_______*/       if (postscript_filename)
/*_______*/          add_file_to_body(postscript_filename);
/*_______*/
/*_______*/       nmsmtp_component->Connect();
/*_______*/       nmsmtp_component->SendMail();
/*_______*/       nmsmtp_component->Disconnect();
/*_______*/    return true;
/*_______*/ };

/*_______*/ void NMSMTP_email_client::add_file_to_body(const char *filename)
/*_______*/ {
/*_______*/    CORN_string body_line;
/*_______*/    ifstream body_file(filename);
/*_______*/    while (!body_file.eof())
/*_______*/    {
/*_______*/       body_line.read_line(body_file);
/*_______*/       nmsmtp_component->PostMessage->Body->Add(body_line.c_str());
/*_______*/    };
/*_______*/ };
/*_______*/
#ifdef obsolete
/*_______*/ void NMSMTP_email_client::compose_email_body
/*_______*/ (const char */*const CORN::File_name &*/body_filename
/*_______*/ ,const char */*const CORN_string   &*/to_email_address
/*_______*/ ,const char */*const CORN_string   &*/subject_part_1
/*_______*/ ,const char */*const CORN_string   &*/subject_part_2
/*_______*/ )
/*_______*/ {  ofstream notify_body_file(body_filename);

/*_______*/    CORN_string body_line;
/*_______*/    ifstream body_file(body_filename);
/*_______*/    while (!body_file.eof())
/*_______*/    {
/*_______*/       body_line.read_line(body_file);
/*_______*/       nmsmtp_component->PostMessage.Body.Add(body_line.c_str());
/*_______*/    };
/*_______*/
/*_______*/    write(notify_body_file);
/*_______*/ };

/*_______*/ void NMSMTP_email_client::send_from_file
/*_______*/ (const char */*const CORN_string   &*/email_address
/*_______*/ ,const char */*const CORN_string   &*/subject_part_1
/*_______*/ ,const char */*const CORN_string   &*/subject_part_2
/*_______*/ ,const char */*const CORN::File_name &*/body_filename)
/*_______*/ {


/*_______*/    CORN_string email_command;
/*_______*/    compose_email_command_line
/*_______*/       (email_command
/*_______*/       ,email_address
/*_______*/       ,subject_part_1
/*_______*/       ,subject_part_2
/*_______*/       ,body_filename
/*_______*/       );
/*_______*/    WinExec(email_command.c_str(),SW_HIDE);
//             Once the mail is sent we can delete the body file
//TEMP DISABLED /*_______*/    unlink(body_filename.get());
/*_______*/ };

#endif
