#include "file_system_engine_Qt.h"
#include "corn/OS/directory_entry_name_concrete.h"
#include "corn/seclusion.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>

namespace CORN { namespace OS {
//_______________________________________________________
File_system_engine_Qt::File_system_engine_Qt()
{}
//_2015-03-20___________________________________________________________________
nat32 File_system_engine_Qt::list_names_in
(const Directory_name & directory_name
,CORN::Text_list *file_name_list_unqual
,CORN::Text_list *directory_name_list_unqual)                              const
{  QString dirName;
   dirName = QString::fromWCharArray(directory_name.w_str());
   QDir dir(dirName);
   if (dir.exists(dirName))
   {  Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
      {  std::wstring unqualified_name(info.fileName().toStdWString());
         if (info.isDir() && directory_name_list_unqual)
            directory_name_list_unqual->add_wstring(unqualified_name);
         else  // its a normal file name
            if (file_name_list_unqual)
               file_name_list_unqual->add_wstring(unqualified_name);
      } // Q_FOREACH
   }
   return file_name_list_unqual      ? file_name_list_unqual->count()      :0
        + directory_name_list_unqual ? directory_name_list_unqual->count() : 0;
}
//_2016-08-29___________________________________________________________________
/*161029
nat32 File_system_engine_Qt::list_names_in //161017 list_entry_names_in
(const Directory_name & directory_name
,CORN::Text_list *file_name_list_unqual
,CORN::Text_list *directory_name_list_unqual
,const Seclusion &seclusion)                                               const
{  QString dirName;
   dirName = QString::fromWCharArray(directory_name.w_str());
   QDir dir(dirName);
   if (dir.exists(dirName))
   {  Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
      {  std::wstring unqualified_name(info.fileName().toStdWString());
         if (info.isDir() && directory_name_list_unqual)
         {  if (seclusion.is_included_wstring(unqualified_name,false,false))
               directory_name_list_unqual->add_wstring(unqualified_name);
         } else  // its a normal file name
         {  if (file_name_list_unqual)
            {  if (seclusion.is_included_wstring(unqualified_name,false,false))
                  file_name_list_unqual->add_wstring(unqualified_name);
            }
         }
      } // Q_FOREACH
   }
   return file_name_list_unqual      ? file_name_list_unqual->count()      :0
        + directory_name_list_unqual ? directory_name_list_unqual->count() : 0;
}
//_2016-08-29___________________________________________________________________
*/

nat32 File_system_engine_Qt::list_entry_names_in_deprecated
(const Directory_name & directory_name
,CORN::Text_list *file_name_list_unqual
,CORN::Text_list *directory_name_list_unqual
,const wchar_t *name_wild_card
,const wchar_t *extension_filter
,const CORN::Text_list *exclude_directories)                               const
{  nat32 file_list_count = 0;
   nat32 dir_list_count = 0;
   QString dirName;
   dirName = QString::fromWCharArray(directory_name.w_str());
   QDir dir(dirName);
   if (dir.exists(dirName))
   {
      Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
      {
         bool extension_filter_matches = (extension_filter == 0);
         if (!extension_filter_matches)
         {
            std::string extension_filter_string; CORN::UnicodeZ_to_string(extension_filter,extension_filter_string);
            /*
            QString extension_filter_Qstring(extension_filter_string.c_str()); //(L"test2");
            // Not sure why this doesnt do anything: extension_filter_Qstring.fromWCharArray(extension_filter);
            extension_filter_matches =
                  info.suffix() == extension_filter_Qstring;
           */
            std::string info_suffix(info.suffix().toStdString());
            extension_filter_matches = info_suffix == extension_filter_string;
         }
         if (extension_filter_matches)
         {  // list only directories that have the specified extension
            bool wild_card_matches = (name_wild_card == 0);
            if (!wild_card_matches)
            {
               QString name_wild_card_Qstring;
               name_wild_card_Qstring.fromWCharArray(name_wild_card);
               QRegExp regexp
                  (name_wild_card_Qstring
                  #ifdef __linux__
                  ,Qt::CaseSensitive
                  #else
                  ,Qt::CaseInsensitive
                  #endif
                  ,QRegExp::WildcardUnix);
               wild_card_matches = regexp.exactMatch(info.completeBaseName());
            }
            if (wild_card_matches)
            {
               if (info.isDir())
               {
                  if (directory_name_list_unqual)
                  {
                      directory_name_list_unqual->add_wstring(info.fileName().toStdWString());
                      dir_list_count++;
                  }
               } else  // its a normal file name
               {
                  if (file_name_list_unqual)
                  {
                     file_name_list_unqual->add_wstring(info.fileName().toStdWString());
                     file_list_count++;
                  }
               }
            } //matches
         } // extension filtered
      } // Q_FOREACH
   }
   return file_list_count + dir_list_count;
}
//_2015-12-12___________________________________________________________________
bool File_system_engine_Qt::matches_any_in                                                   //151212
(const std::wstring &name_with_ext
,const CORN::Text_list &wild_card_patterns_to_compare
,bool case_insensitive)                                             affirmation_
{   bool matches = false;
   FIND_FOR_EACH_IN(matching_pattern,pattern,CORN::Item_string /*180119 Text_list::Item*/,wild_card_patterns_to_compare,true,each_WCP)
   {
      QString name_wild_card_Qstring;
      name_wild_card_Qstring.fromStdString(*pattern);
      QRegExp regexp
               (name_wild_card_Qstring
               ,case_insensitive ? Qt::CaseInsensitive :Qt::CaseSensitive
               ,QRegExp::WildcardUnix);
      matches = regexp.exactMatch(name_wild_card_Qstring);
      if (matches) matching_pattern = pattern;
   } FOR_EACH_END(each_WCP)
   return matches;
}
//_2015-12-12___________________________________________________________________
} } // namespace CORN OS
//______________________________________________________________________________

