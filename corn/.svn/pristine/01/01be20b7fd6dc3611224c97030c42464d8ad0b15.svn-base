#include "translation.h"
//______________________________________________________________________________
void Translation_phrases::load_phrases
(const char *language_code
,const CORN::Program_directory &program_directory
,const CORN::OS_FS::Application_directory *application_directory                 //141119
,const CORN::OS_FS::Suite_directory       *suite_directory                       //141119

)
{  Association_list translation_files_ANSI;
   Association_list translation_files_Unicode;
   program_directory.list_file_names(translation_files_ANSI,false,"*","ANSI");
   // NYI program_directory.list_file_names(translation_files_Unicode,false,"*","Unicode");
   //141119   provided_ CORN::Application_directory  *application_directory = program_directory.provide_application_directory();
   if (application_directory)
   {  application_directory->list_file_names(translation_files_ANSI,false,"*","ANSI");
      //NYI application_directory->list_file_names(translation_files_Unicode,false,"*","Unicode");
   }
   // There may be additional translations common to all application programs in the suite.
   //141119 provided_ CORN::Suite_directory *suite_directory = program_directory.provide_suite_directory();
   if (suite_directory)
   {  suite_directory->list_file_names(translation_files_ANSI,false,"*","ANSI");
      //NYI suite_directory->list_file_names(translation_files_Unicode,false,"*","Unicode");
   }
   FOR_EACH_IN(translation_file, OS::File_name,translation_files_ANSI,each_trans_file)
      load_translation_ANSI(language_code,suites_translations.c_str());
   FOR_EACH_END(each_trans_file)
   /* NYI
   FOR_EACH_IN(translation_file, OS::File_name,translation_files_Unicode,each_trans_file)
      load_translation_Unicode(language_code,suites_translations.c_str());
   FOR_EACH_END(each_trans_file);
   */
}
//______________________________________________________________________________
void Translation_phrases
::load_translation_ANSI
(const char *language_code,const char *filename)
{  std::ifstream translation_file(filename);
   std::string line;
   Translation *translation = 0;
   while (!translation_file.eof())
   {  std::getline(translation_file,line);
      if (line.c_str()[0] == '/')
      {  translation = new Translation;
         append(translation);
      }
      if (translation)
      {  if ((line.c_str()[0] == 'e') &&
             (line.c_str()[1] == 'n'))
         {  translation->english = line.substr(3);
         } else if
            ((line.c_str()[0] == language_code[0]) &&
             (line.c_str()[1] == language_code[1]))
         {  translation->translation = line.substr(3);
         }
      }
   }
}
//______________________________________________________________________________
