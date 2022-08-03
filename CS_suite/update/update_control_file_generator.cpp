#include "update_control_file_generator.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#include "corn/datetime/date.h"
#include "corn/datetime/time.h"
#include <fstream>

uint32 Update_control_file_generator::create
(const char *control_file_name_cstr          // This is the fully qualified name of the update_control.inf file to create.
,const char *app_distribution_directory_cstr // This is the directory containing the files to be included in the installation.
,const char *app_installation_directory_cstr // This is the directory on the users computer where the application is to be installed.
,const char *app_URL_directory_cstr          // This is the URL of the web site where the files will be found by the updater program.
)
{
   CORN::File_name control_filename(control_file_name_cstr);
   CORN::Smart_directory_name app_distribution_directory(app_distribution_directory_cstr);
//   control_filename.set_path(app_distribution_directory);
   ofstream control_inf(control_filename.c_str());
//   CORN::Date_time_64 now;

Continue here dates need to be normalized to GMT Greenwich Mean Time

   CORN::Date now_date;
   CORN::Time now_time;

   control_inf
      << "[update]" << endl
      << "date="     << now_date.c_str() << endl
      << "time="     << now_time.c_str() << endl
      << "[WhatsNew]"  << endl
      << "file="     << app_URL_directory_cstr << "/documentation/history.htm" << endl
      ;
/*
[EULA]
file=location of file

      [action]
      updateURL=http://yourserver/update.inf
      msg=Automatic web update
      query=This is the update version 1.5.0.0 Continue ?
      showURL=http://www.yourserver.com/updates/doc.htm
      htmldlg=http://www.yourserver.com/updates/dialog.htm
      runbefore=
      runafter=
*/
   CORN::Association_list installation_files;
   CORN::File_name app_installation_directory(app_installation_directory_cstr);

   app_distribution_directory.list_contents_by_type
      ( installation_files
      , true // recursive
      , true // qualify
      , true // with_extension
      , true // show_path
      , true // show_extension
      , CORN::Directory_entry_name::file_entry
      , 0  // no extension_filter
      );
   uint32 file_count = 0;
   FOR_EACH_IN(distribution_filename,CORN::Smart_file_name,installation_files,each_file)
   {
      if (distribution_filename->find("update_control") == CORN_npos)
      {
         file_count ++;
         CORN::Smart_file_name inst_filename(*distribution_filename);
         // uint32 file_size = inst_filename.get_size_bytes();

         CORN::Datetime64 file_date_time = inst_filename.get_date_time();
         CORN::Date file_date(file_date_time);

         CORN::Smart_file_name distribution_filename_partially_qualified(*distribution_filename);
         distribution_filename_partially_qualified.remove_common_path(app_distribution_directory);
         CORN::Ustring URL_filename(app_URL_directory_cstr);
         URL_filename.append("/");
         URL_filename.append(distribution_filename_partially_qualified);
         URL_filename.replace_character('\\','/');

         CORN::Directory_name distribution_filename_directory;
         distribution_filename_partially_qualified.get_path(distribution_filename_directory);
         CORN::Ustring installation_target_directory_name(app_installation_directory_cstr);
         if (distribution_filename_directory.length())
         {  installation_target_directory_name.append("\\");
            installation_target_directory_name.append(distribution_filename_directory);
         }

         if (distribution_filename->ext_is("bpl") || distribution_filename->ext_is("dll"))
         { // Special case for shared BPL and DLL files
           installation_target_directory_name.assign("{WIN}");
         }

         control_inf
            << "[" <<
               "file:" << file_count << "]" << endl
            << "url="            << URL_filename << endl
            // newversion=1,0,0,0
//            << "newsize="        << file_size << endl
            // newchecksum=
            << "localversion="   << distribution_filename->get_name(true) << endl
            << "targetdir="      << installation_target_directory_name << endl
            << "date="           << file_date.c_str() << endl
            // descr=your description of the file
            // compressed=1
//            << "filesize="       << file_size << endl;
            // mandatory=0 or 1
            // hidden=0 or 1
            ;
      } // skip the control file
   } FOR_EACH_END(each_file);
   control_inf
      << "[files]" << endl
//      << "count=" << file_count << endl       // This is used by Web update
      << "file:count=" << file_count << endl    // This
      ;
   return file_count;
}
