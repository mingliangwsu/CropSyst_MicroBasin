#include "corn/application/translations.h"
#ifdef TRANSLATIONS_AUTOLOAD_PHRASES
#include "corn/string/strconv.hpp"
#include <fstream>

#include "corn/application/program_directory_OS_FS.h"
#include "corn/application/application_directory_OS_FS.h"
#include "corn/application/suite_directory_OS_FS.h"
#include "corn/OS/directory_entry_name.h"
#endif
#include "corn/seclusion.h"
#include "corn/OS/file_system_engine.h"
namespace CORN {
using namespace OS_FS;
using namespace OS;

#ifdef TRANSLATIONS_AUTOLOAD_PHRASES
//______________________________________________________________________________
unsigned long Translations_phrases::load_phrases
(const char *_primary_language_code
,const Program_directory            &program_directory
,const Application_directory  *application_directory  // Optional          //141119
,const Suite_directory         *suite_directory        // Optional          //141119
)
{  unsigned long phrase_count = 0;
   primary_language_code = _primary_language_code;
   Bidirectional_list /*180101 Association_list*/ translation_files_ANSI;
   Bidirectional_list /*180101 Association_list*/ translation_files_Unicode;
   CORN::Seclusion ANSI_pattern("*.ANSI");
   CORN::Seclusion Unicode_pattern("*.Unicode");

   CORN::OS::file_system_engine.list_DENs                                        //161106
      (program_directory,&translation_files_ANSI,0,ANSI_pattern
      ,File_system::subdirectory_recursion_inclusive);                           //150908
/*161106
   program_directory.list_file_names_deprecated
      (translation_files_ANSI
      ,File_system::subdirectory_recursion_inclusive                             //150908
      ,Directory_entry_name::none_qualification //(may want fully qualified)     //150908
      ,L"*",L"ANSI");
*/

   // NYI program_directory.list_file_names(translation_files_Unicode,false,"*","Unicode");
   if (application_directory)
   {
      CORN::OS::file_system_engine.list_DENs                                     //161106
         (*application_directory
         ,&translation_files_ANSI,0
         ,ANSI_pattern
         ,File_system::subdirectory_recursion_inclusive);                          //150908
      //NYI application_directory->list_file_names(translation_files_Unicode,false,"*","Unicode");
   }
   // There may be additional translations common to all application programs in the suite.
   if (suite_directory)
   {
      CORN::OS::file_system_engine.list_DENs                                     //161106
         (*suite_directory,&translation_files_ANSI,0,ANSI_pattern
         ,File_system::subdirectory_recursion_inclusive);
      //NYI suite_directory->list_file_names(translation_files_Unicode,false,"*","Unicode");
   }
   FOR_EACH_IN(translation_file,File_name,translation_files_ANSI,each_trans_file)
      phrase_count += load_translations_ANSI(primary_language_code.c_str(),translation_file->c_str());
   FOR_EACH_END(each_trans_file);
   /* NYI
   FOR_EACH_IN(translation_file, OS::File_name,translation_files_Unicode,each_trans_file)
      load_translation_Unicode(language_code,suites_translations.c_str());
   FOR_EACH_END(each_trans_file);
   */
      CORN::OS::file_system_engine.list_DENs                                     //161106
      (program_directory,&translation_files_Unicode,0,Unicode_pattern
      ,File_system::subdirectory_recursion_inclusive);
   // NYI program_directory.list_file_names(translation_files_Unicode,CORN::OS::Directory_entry_name::none/*121102 false*/,"*","Unicode");
   if (application_directory)
   {
      CORN::OS::file_system_engine.list_DENs                                     //161106
         (*application_directory,&translation_files_Unicode,0,Unicode_pattern
         ,File_system::subdirectory_recursion_inclusive);
      //NYI application_directory->list_file_names(translation_files_Unicode,CORN::OS::Directory_entry_name::Qualification::none/*121102 false*/,"*","Unicode");
   }
   // There may be additional translations common to all application programs in the suite.
   if (suite_directory)
   {
      CORN::OS::file_system_engine.list_DENs                                     //161106
         (*suite_directory,&translation_files_Unicode,0,Unicode_pattern
         ,File_system::subdirectory_recursion_inclusive);
   }
   if (suite_directory)
   {
      CORN::OS::File_system_logical::Directory common_directory
         (suite_directory->common(),false); /*This would be an optional preexisting directory if there were translations */
      CORN::OS::file_system_engine.list_DENs                                     //161106
         (common_directory,&translation_files_Unicode,0,Unicode_pattern
         ,File_system::subdirectory_recursion_inclusive);
   }
   FOR_EACH_IN(translation_file,CORN::File_name,translation_files_Unicode,each_trans_file)
      phrase_count += load_translations_Unicode(primary_language_code.c_str(),translation_file->c_str());
   FOR_EACH_END(each_trans_file);
   /* NYI
   FOR_EACH_IN(translation_file, OS::File_name,translation_files_Unicode,each_trans_file)
      load_translation_Unicode(language_code,suites_translations.c_str());
   FOR_EACH_END(each_trans_file);
   */
   return phrase_count;
}
#endif
//______________________________________________________________________________
unsigned long Translations_phrases
::load_translations_ANSI
(const char *primary_language_code
,const char *filename)
{  unsigned long phrase_count = 0;
   std::ifstream translation_file(filename);
   std::string line;
   Translation *translation = 0;
   while (!translation_file.eof())
   {  std::getline(translation_file,line);
      if ((line.c_str()[0] == 'L') && (line.c_str()[1] == '_'))
      {  size_t comma_pos = line.find(",");
         std::string ID = line.substr(0,comma_pos );
         translation = new Translation(ID);
      } else
      if ((line.c_str()[0] == '/') && (line.c_str()[1] == '*'))
      {  // this line lists the programs the phrase occurs in and the persons initials' who made the translation
         line.clear(); // not currently using this line
      } else
      if (((line.c_str()[0] == '*') && (line.c_str()[1] == '/')) || (line.length() == 0))
      {  append(translation);
         phrase_count++;
         translation = 0;
      } else
      if (translation)
      {  size_t delimitor_pos = line.find(" ");
         if (delimitor_pos != std::string::npos)
         {  std::string language_code(line.substr(0,delimitor_pos));
            std::string translated_text(line.substr(delimitor_pos+1));
//if (translated_text == "Adjustment factor for phenologic response to stress")
//std::cout << "reached" << std::endl;

            Translation::Translated *translated = new Translation::Translated(language_code,translated_text);
            translation->translations.append(translated);
            if (   (language_code == "*") // Text is the same in all languages
                 ||(language_code == primary_language_code))
               #ifdef _UNICODE
                 translation->primary_text.assign(translated_text);
               #else
                  translation->primary_text =translated->get_text();
               #endif
         } //else  this is not a traslated text line
      }
   }
   return phrase_count;
}
//______________________________________________________________________________
nat32 read_Unicode_line(std::ifstream &strm,std::wstring &str)
{  nat32 linelen = 0;
   nat16 char_unicode = 0;
   nat8  lowbyte = 0;
   nat8 highbyte = 0;
   bool at_eol = false;
   str.clear();
   while (!at_eol && !strm.eof() && strm.good())
   {
/*
      strm.read((char *)(&char_unicode),sizeof(nat16));
      switch (char_unicode)
      {
         case '\n' :
         case 0x0A00 :
            at_eol = true;
         break;
         default :
            str.push_back((wchar_t)char_unicode);
            linelen++;
         break;

      };
*/

      strm.read((char *)(&lowbyte),sizeof(nat8));
/*
      if ((lowbyte >=1 ) && (lowbyte < 32))
      {  // This is a control character
         strm.read((char *)(&highbyte),sizeof(nat8));
         if (lowbyte == '\n')
            return linelen;
      } else
*/
      if (lowbyte == 0)
         { /* the notepad UNICODE file appears to have a single 0 at the end of the line*/}
      else
      {
         strm.read((char *)(&highbyte),sizeof(nat8));
         char_unicode = lowbyte | (highbyte << 8);
         if (char_unicode == '\n')
            return linelen;
         if (char_unicode == '\r')
            { /* Eat the carridge return */}
         else
            str.push_back((wchar_t)char_unicode);
         linelen++;
      }
      if (str.length() == 0)
         return linelen;
   }
   return  linelen;
}
//______________________________________________________________________________
#ifndef _UNICODE

int Unicode_codepage1251[128][2] =
{{0x0402,128},{0x0403,129},{0x201A,130},{0x0453,131},{0x201E,132},{0x2026,133}
,{0x2020,134},{0x2021,135},{0x20AC,136},{0x2030,137},{0x0409,138},{0x2039,139}
,{0x040A,140},{0x040C,141},{0x040B,142},{0x040F,143}
,{0x0452,144},{0x2018,145},{0x2019,146},{0x201C,147},{0x201D,148},{0x2022,149}
,{0x2013,150},{0x2014,151},{0xFFFF,152},{0x2122,153},{0x0459,154},{0x203A,155}
,{0x045A,156},{0x045C,157},{0x045B,158},{0x045F,159}
,{0x00A0,160},{0x040E,161},{0x045E,162},{0x0408,163},{0x00A4,164},{0x0490,165}
,{0x00A6,166},{0x00A7,167},{0x0401,168},{0x00A9,169},{0x0404,170},{0x00AB,171}
,{0x00AC,172},{0x00AD,173},{0x00AE,174},{0x0407,175}
,{0x00B0,176},{0x00B1,177},{0x0406,178},{0x0456,179},{0x0491,180},{0x00B5,181}
,{0x00B6,182},{0x00B7,183},{0x0451,184},{0x2116,185},{0x0454,186},{0x00BB,187}
,{0x0458,188},{0x0405,189},{0x0455,190},{0x0457,191}
,{0x0410,192},{0x0411,193},{0x0412,194},{0x0413,195},{0x0414,196},{0x0415,197}
,{0x0416,198},{0x0417,199},{0x0418,200},{0x0419,201},{0x041A,202},{0x041B,203}
,{0x041C,204},{0x041D,205},{0x041E,206},{0x041F,207}
,{0x0420,208},{0x0421,209},{0x0422,210},{0x0423,211},{0x0424,212},{0x0425,213}
,{0x0426,214},{0x0427,215},{0x0428,216},{0x0429,217},{0x042A,218},{0x042B,219}
,{0x042C,220},{0x042D,221},{0x042E,222},{0x042F,223}
,{0x0430,224},{0x0431,225},{0x0432,226},{0x0433,227},{0x0434,228},{0x0435,229}
,{0x0436,230},{0x0437,231},{0x0438,232},{0x0439,233},{0x043A,234},{0x043B,235}
,{0x043C,236},{0x043D,237},{0x043E,238},{0x043F,239}
,{0x0440,240},{0x0441,241},{0x0442,242},{0x0443,243},{0x0444,244},{0x0445,245}
,{0x0446,246},{0x0447,247},{0x0448,248},{0x0449,249},{0x044A,250},{0x044B,251}
,{0x044C,252},{0x044D,253},{0x044E,254},{0x044F,255}
};
//------------------------------------------------------------------------------
int Unicode_codepage1256[260][2] =
{//Isolated forms
 {0x0402,128},{0x067E,129},{0x201A,130},{0x0192,131},{0x201E,132},{0x2026,133}
,{0x2020,134},{0x2021,135},{0x02C6,136},{0x2030,137},{0x0679,138},{0x2039,139}
,{0x0152,140},{0x0686,141},{0x0698,142},{0x0688,143}
,{0x06AF,144},{0x2018,145},{0x2019,146},{0x201C,147},{0x201D,148},{0x2022,149}
,{0x2013,150},{0x2014,151},{0x06A9,152},{0x2122,153},{0x0691,154},{0x203A,155}
,{0x0153,156},{0x200C,157},{0x0200D,158},{0x06BA,159}
,{0x00A0,160},{0x060C,161},{0x00A2,162},{0x00A3,163},{0x00A4,164},{0x00A5,165}
,{0x00A6,166},{0x00A7,167},{0x00A8,168},{0x00A9,169},{0x06BE,170},{0x00AB,171}
,{0x00AC,172},{0x00AD,173},{0x00AE,174},{0x00AF,175}
,{0x00B0,176},{0x00B1,177},{0x00B2,178},{0x00B3,179},{0x00B4,180},{0x00B5,181}
,{0x00B6,182},{0x00B7,183},{0x00B8,184},{0x00B9,185},{0x061B,186},{0x00BB,187}
,{0x00BC,188},{0x00BD,189},{0x00BE,190},{0x061F,191}
,{0x06C1,192},{0x0621,193},{0x0622,194},{0x0623,195},{0x0624,196},{0x0625,197}
,{0x0626,198},{0x0627,199},{0x0628,200},{0x0629,201},{0x062A,202},{0x062B,203}
,{0x062C,204},{0x062D,205},{0x062E,206},{0x062F,207}
,{0x0630,208},{0x0631,209},{0x0632,210},{0x0633,211},{0x0634,212},{0x0635,213}
,{0x0636,214},{0x00D7,215},{0x0637,216},{0x0638,217},{0x0639,218},{0x063A,219}
,{0x0640,220},{0x0641,221},{0x0642,222},{0x0643,223}
,{0x00E0,224},{0x0644,225},{0x00E2,226},{0x0645,227},{0x0646,228},{0x0647,229}
,{0x0648,230},{0x00E8,231},{0x00E8,232},{0x00E9,233},{0x00EA,234},{0x00EB,235}
,{0x0649,236},{0x064A,237},{0x00EE,238},{0x00EF,239}
,{0x064B,240},{0x064C,241},{0x064D,242},{0x064E,243},{0x00F4,244},{0x064F,245}
,{0x0650,246},{0x00F7,247},{0x0651,248},{0x00F9,249},{0x0652,250},{0x00FB,251}
,{0x00FC,252},{0x200E,253},{0x200F,254},{0x06D2,255}

// The following are initial, medial and final forms of the characters
// These will be simply converted to the basic isolated form of the code page.
// spacing forms
,{0xFE70,/*0x064B*/240}
,{0xFE71,/*0x064B*/240}
,{0xFE72,/*0x064D*/242}

//depr ,{0xFE73,/*0x064B*/,240}

,{0xFE74,/*0x064D*/242}
//refv,{0xFE75,/*0x0HHHH*/,DDD}
,{0xFE76,/*0x064E*/243}
,{0xFE77,/*0x0640 0x064E*/243}
,{0xFE78,/*0x064F*/245}
,{0xFE79,/*0x0640 0x064F*/245}
,{0xFE7A,/*0x0650*/246}
,{0xFE7B,/*0x0640 0x0650*/246}
,{0xFE7C,/*0x0651*/248}
,{0xFE7D,/*0x0640 0x0651*/248}
,{0xFE7E,/*0x0652*/250}
,{0xFE7F,/*0x0640 0x0652*/250}


// contextual forms

,{0xFE80,/*0x0621*/193}
,{0xFE81,/*0x0622*/194}
,{0xFE82,/*0x0622*/194}
,{0xFE83,/*0x0623*/195}
,{0xFE84,/*0x0623*/195}
,{0xFE85,/*0x0624*/196}
,{0xFE86,/*0x0624*/196}
,{0xFE87,/*0x0625*/197}
,{0xFE88,/*0x0625*/197}
,{0xFE89,/*0x0626*/198}
,{0xFE8A,/*0x0626*/198}
,{0xFE8B,/*0x0626*/198}
,{0xFE8C,/*0x0626*/198}
,{0xFE8D,/*0x0627*/199}
,{0xFE8E,/*0x0627*/199}
,{0xFE8F,/*0x0628*/200}
,{0xFE90,/*0x0628*/200}
,{0xFE91,/*0x0628*/200}
,{0xFE92,/*0x0628*/200}
,{0xFE93,/*0x0629*/201}
,{0xFE94,/*0x0629*/201}
,{0xFE95,/*0x062A*/202}
,{0xFE96,/*0x062A*/202}
,{0xFE97,/*0x062A*/202}
,{0xFE98,/*0x062A*/202}
,{0xFE99,/*0x062B*/203}
,{0xFE9A,/*0x062B*/203}
,{0xFE9B,/*0x062B*/203}
,{0xFE9C,/*0x062B*/203}
,{0xFE9D,/*0x062C*/204}
,{0xFE9E,/*0x062C*/204}
,{0xFE9F,/*0x062C*/204}
,{0xFEA0,/*0x062C*/204}
,{0xFEA1,/*0x062C*/204}
,{0xFEA2,/*0x062C*/204}
,{0xFEA3,/*0x062D*/205}
,{0xFEA4,/*0x062D*/205}
,{0xFEA5,/*0x062E*/206}
,{0xFEA6,/*0x062E*/206}
,{0xFEA7,/*0x062E*/206}
,{0xFEA8,/*0x062E*/206}
,{0xFEA9,/*0x062F*/207}
,{0xFEAA,/*0x062F*/207}
,{0xFEAB,/*0x0630*/208}
,{0xFEAC,/*0x0630*/208}
,{0xFEAD,/*0x0631*/209}
,{0xFEAE,/*0x0631*/209}
,{0xFEAF,/*0x0632*/210}
,{0xFEB0,/*0x0632*/210}
,{0xFEB1,/*0x0633*/211}
,{0xFEB2,/*0x0633*/211}
,{0xFEB3,/*0x0633*/211}
,{0xFEB4,/*0x0633*/211}
,{0xFEB5,/*0x0634*/212}
,{0xFEB6,/*0x0634*/212}
,{0xFEB7,/*0x0634*/212}
,{0xFEB8,/*0x0634*/212}
,{0xFEB9,/*0x0635*/213}
,{0xFEBA,/*0x0635*/213}
,{0xFEBB,/*0x0635*/213}
,{0xFEBC,/*0x0635*/213}
,{0xFEBD,/*0x0636*/214}
,{0xFEBE,/*0x0636*/214}
,{0xFEBF,/*0x0636*/214}
,{0xFEC0,/*0x0636*/214}
,{0xFEC1,/*0x0637*/216}
,{0xFEC2,/*0x0637*/216}
,{0xFEC3,/*0x0637*/216}
,{0xFEC4,/*0x0637*/216}
,{0xFEC5,/*0x0638*/217}
,{0xFEC6,/*0x0638*/217}
,{0xFEC7,/*0x0638*/217}
,{0xFEC8,/*0x0638*/217}
,{0xFEC9,/*0x0639*/218}
,{0xFECA,/*0x0639*/218}
,{0xFECB,/*0x0639*/218}
,{0xFECC,/*0x0639*/218}
,{0xFECD,/*0x063A*/219}
,{0xFECE,/*0x063A*/219}
,{0xFECF,/*0x063A*/219}
,{0xFED0,/*0x063A*/219}
,{0xFED1,/*0x0641*/221}
,{0xFED2,/*0x0641*/221}
,{0xFED3,/*0x0641*/221}
,{0xFED4,/*0x0642*/222}
,{0xFED5,/*0x0642*/222}
,{0xFED6,/*0x0642*/222}
,{0xFED7,/*0x0642*/222}
,{0xFED8,/*0x0642*/222}
,{0xFED9,/*0x0643*/223}
,{0xFEDA,/*0x0643*/223}
,{0xFEDB,/*0x0643*/223}
,{0xFEDC,/*0x0643*/223}
,{0xFEDD,/*0x0644*/225}
,{0xFEDE,/*0x0644*/225}
,{0xFEDF,/*0x0644*/225}
,{0xFEE0,/*0x0644*/225}
,{0xFEE1,/*0x0645*/227}
,{0xFEE2,/*0x0645*/227}
,{0xFEE3,/*0x0645*/227}
,{0xFEE4,/*0x0645*/227}
,{0xFEE5,/*0x0646*/228}
,{0xFEE6,/*0x0646*/228}
,{0xFEE7,/*0x0646*/228}
,{0xFEE8,/*0x0646*/228}
,{0xFEE9,/*0x0647*/229}
,{0xFEEA,/*0x0647*/229}
,{0xFEEB,/*0x0647*/229}
,{0xFEEC,/*0x0647*/229}
,{0xFEED,/*0x0648*/230}
,{0xFEEE,/*0x0648*/230}
,{0xFEEF,/*0x0649*/236}
,{0xFEF0,/*0x0649*/236}
,{0xFEF1,/*0x064A*/237}
,{0xFEF2,/*0x064A*/237}
,{0xFEF3,/*0x064A*/237}
,{0xFEF4,/*0x064A*/237}

,{0xFEFF,32} // non-break space
};

int Unicode_codepage1256_ligatures[8][3] =
{
// The following are ligatures
 {0xFEF5,/*0x0644,0x0622*/225,194}
,{0xFEF6,/*0x0644,0x0622*/225,194}
,{0xFEF7,/*0x0644,0x0623*/225,195}
,{0xFEF8,/*0x0644,0x0623*/225,195}
,{0xFEF9,/*0x0644,0x0625*/225,197}
,{0xFEFA,/*0x0644,0x0625*/225,197}
,{0xFEFB,/*0x0644,0x0627*/225,199}
,{0xFEFC,/*0x0644,0x0627*/225,199}
};

// Note I may need to add conversions of initial medial and final forms
// to this isolated form code page.
//------------------------------------------------------------------------------
std::string &Translations_phrases::Unicode_to_codepageXXXX
(const std::wstring &str_Unicode,std::string &str_codepage
,int unicode_codepage[][2]                                                   //101116
,int codes
)
{
   str_codepage.clear();
   for (size_t i = 0; i < str_Unicode.length(); i++)
   {
      wchar_t char_Unicode = str_Unicode.data()[i];
      char char_codepage = (char)char_Unicode;
      bool found = false;

      if ((char_Unicode >= 0xFEF5) &&(char_Unicode <= 0xFEFC))
      {  // Arabic ligatures
         for (int code_i = 0; (code_i < 8) && !found; code_i++)
            {  if (Unicode_codepage1256_ligatures[code_i][0] == char_Unicode)
               {
                  char_codepage = unicode_codepage[code_i][1];
                  str_codepage.append(1,char_codepage);
                  char_codepage = unicode_codepage[code_i][2];
                  str_codepage.append(1,char_codepage);
                  found = true;
               }
            }
      }else
      {  // single character
         for (int code_i = 0; (code_i < codes) && !found; code_i++)
            {  if (unicode_codepage[code_i][0] == char_Unicode)
               {
                  char_codepage = unicode_codepage[code_i][1];
                  found = true;
               }
            }
         str_codepage.append(1,char_codepage);
      }
   }
   return str_codepage;
}
#endif
//______________________________________________________________________________
unsigned long Translations_phrases
::load_translations_Unicode
(const char *primary_language_code
,const char *filename)
{
//   std::string primary_language_code_ANSI(_primary_language_code);
//   std::wstring primary_language_code_Unicode;
//   string_to_wstring(primary_language_code_ANSI,primary_language_code_Unicode);
   unsigned long phrase_count = 0;
   std::ifstream translation_file(filename, std::ifstream::in|std::ifstream::binary);

//   std::ifstream translation_file("C:\\CS_Suite_4\\CropSyst\\Crop_editor\\translation.Unicode");

   std::wstring line;
   Translation *translation = 0;
   nat16 BOM;
   translation_file.read((char *)(&BOM),sizeof(nat16));
   while (!translation_file.eof() && translation_file.good())
   {  nat32 line_len = read_Unicode_line(translation_file,line);
/*
std::string check_line;
wstring_to_string(line,check_line);
std::clog << check_line << std::endl;
*/
      if ((line.c_str()[0] == L'L') && (line.c_str()[1] == L'_'))
      {  size_t comma_pos = line.find(L",");
         std::wstring ID_Unicode = line.substr(0,comma_pos );
         std::string ID_ANSI;
         wstring_to_string(ID_Unicode,ID_ANSI);
         translation = new Translation(ID_ANSI);
      } else
      if ((line.c_str()[0] == L'/') && (line.c_str()[1] == L'*'))
      {  // this line lists the programs the phrase occurs in and the persons initials' who made the translation
         if ((line.length() > 2) && translation)
         {
            std::wstring notes(line,2);
            wstring_to_string(notes,translation->notes);
         }
         line.clear(); // not currently using this line
      } else
      if (((line.c_str()[0] == L'*') && (line.c_str()[1] == L'/')) || (line.length() == 0))
      {
         append(translation);
         phrase_count++;
         translation = 0;
      } else
      if (translation)
      {
         size_t delimitor_pos = line.find(L" ");
         if (delimitor_pos != std::string::npos)
         {  std::wstring w_language_code(line.substr(0,delimitor_pos));
            std::string language_code;
            wstring_to_string(w_language_code,language_code);
            #ifdef _UNICODE
            std::wstring translated_text(line.substr(delimitor_pos+1));
            #else
            std::wstring translated_text_Unicode(line.substr(delimitor_pos+1));
            std::string translated_text;
            if (language_code == "ru")
               Unicode_to_codepageXXXX(translated_text_Unicode,translated_text,Unicode_codepage1251,128);
               /*101116 Unicode_to_codepage1251(translated_text_Unicode,translated_text);*/
            if (language_code == "ar")                                           //101116
               Unicode_to_codepageXXXX(translated_text_Unicode,translated_text,Unicode_codepage1256,260); //101116
            else
               wstring_to_string(translated_text_Unicode,translated_text);
            #endif
//if (translated_text == "Adjustment factor for phenologic response to stress")
//std::cout << "reached" << std::endl
            Translation::Translated *translated = new Translation::Translated(language_code,translated_text);
            translation->translations.append(translated);
            if (   (language_code == "*") // Text is the same in all languages
                 ||(language_code == primary_language_code))
               #ifdef _UNICODE
               wstring_to_string(translated_text,translation->primary_text);
               #else
               translation->primary_text = translated->get_text();
               #endif
         } //else  this is not a traslated text line
      }
   }
   return phrase_count;
}
//______________________________________________________________________________
#ifdef _UNICODE
const wchar_t
#else
const char
#endif
*Translation
::get_translation(const char *language_code) const
{  Translated *translated_in_language = dynamic_cast<Translated *>(translations.find_cstr(language_code));
   return translated_in_language ? translated_in_language->text.c_str() : 0;
}
//______________________________________________________________________________
Translation::Translated::Translated
(const std::string &_language
,const std::string &_text)
: CORN::Item() //180101 Association()
, language(_language)
, text()
//, is_Unicode(_is_Unicode)
{
   #ifdef _UNICODE
   string_to_wstring(_text,text);
   #else
   text.assign(_text);
   #endif
}
//______________________________________________________________________________
#ifdef _UNICODE
Translation::Translated::Translated
(const std::string &_language
,const std::wstring &_text)
: CORN::Association()
, language(_language)
, text(_text)
//, is_Unicode(_is_Unicode)
{}
#endif
//______________________________________________________________________________
} // namespace CORN
