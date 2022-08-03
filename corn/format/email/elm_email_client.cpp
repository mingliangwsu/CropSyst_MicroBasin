
/*_______*/ void ELM_email_client::compose_email_command_line
/*_______*/ (CORN_string         &email_command_line
/*_______*/ ,const CORN_string   &to_email_address
/*_______*/ ,const CORN_string   &subject_part_1
/*_______*/ ,const CORN_string   &subject_part_2
/*_______*/ ,const CORN_filename &body_filename
/*_______*/ )
/*_______*/ {
/*_______*/       email_command_line.assign("elm ");
/*_______*/       email_command_line.append("-s \"");
/*_______*/       email_command_line.append(subject_part_1);
/*_______*/       email_command_line.append(" ");
/*_______*/       email_command_line.append(subject_part_2);
/*_______*/       email_command_line.append("\" ");
/*_______*/       email_command_line.append(to_email_address);
/*_______*/       email_command_line.append(" < ");
/*_______*/       email_command_line.append(body_filename);
/*_______*/       email_command_line.append(" > /dev/null");
/*_______*/ };

/*_______*/ void ELM_email_client::compose_email_body
/*_______*/ (const CORN_filename &body_filename
/*_______*/ ,const CORN_string   &to_email_address
/*_______*/ ,const CORN_string &subject_part_1
/*_______*/ ,const CORN_string &subject_part_2
/*_______*/ )
/*_______*/ {  ofstream notify_body_file(body_filename.get());
/*_______*/    write(notify_body_file);
/*_______*/ };

/*_______*/ void ELM_email_client::send_from_file
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
/*_______*/    system(email_command.c_str());
//             Once the mail is sent we can delete the body file


//TEMP DISABLED /*_______*/    unlink(body_filename.get());
            };

