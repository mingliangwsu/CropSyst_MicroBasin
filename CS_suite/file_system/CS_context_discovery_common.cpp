#include "CS_suite/file_system/CS_context_discovery_common.h"
#include "corn/data_source/vv_file.h"
#include "corn/OS/file_system_engine.h"
#include "corn/container/bilist.h"
#include "corn/container/text_list.h"
#include "common/geodesy/geolocation.h"
#include "corn/seclusion.h"
#include "CS_suite/file_system/CS_file_ext.hpp"
namespace CS
{
//______________________________________________________________________________
CORN::OS::File_name *Context_discovery_common::extract_accessible_file_with_pattern
(const std::wstring &pattern)                            contribution_
{
   CORN::Inclusion inclusion(pattern,true);
   CORN::OS::File_name *closest_file = 0;
   CORN::OS::File_name *closest_file_resolved = 0;
   FOR_EACH_IN(accessible,CORN::OS::File_name,accessible_files,each_accessible)
   {

      if (inclusion.is_included_DEN(*accessible))
      {
         closest_file = accessible;
      }
      #if (defined(_WIN32)  || defined(_WIN64))
      else
      {
         // For Windows also find LNK (shortcut) files and resolve
         if (accessible->has_extension_ASCII("LNK"))
         {  CORN::OS::File_name_concrete accessible_without_LNK
               (*accessible
               ,CORN::OS::Directory_entry_name::include_all_except_extension);
            if (inclusion.is_included_DEN(accessible_without_LNK));
            {
               CORN::OS::Directory_entry_name *accessible_resolved
                  = CORN::OS::file_system_engine
                    .render_resolved_shortcut_or_assume_actual(*accessible);
               if (accessible_resolved )
               {
                  delete closest_file_resolved;
                  closest_file_resolved = accessible_resolved;
               }
            }
         }
      }
      #endif
   } FOR_EACH_END(each_accessible)
   accessible_files.detach(closest_file);
   return closest_file;
}
//_2017-07-07_____________________________extract_accessible_file_with_pattern_/

nat16 Context_discovery_common::extract_accessible_files_with_pattern
(const std::wstring &pattern
,modifiable_ CORN::Container &DEN_list)                            contribution_
{  nat32 extracted = 0;
   CORN::Inclusion inclusion(pattern,true);

//std::clog << "extract accessible:" << std::endl;

   FOR_EACH_IN(accessible,CORN::OS::File_name,accessible_files,each_accessible)
   {

//std::clog << accessible->c_str() << std::endl;

      if (inclusion.is_included_DEN(*accessible))
      {
         if (DEN_list.take(each_accessible->detach_current()))
            extracted ++;
      }
      #if (defined(_WIN32)  || defined(_WIN64))
      else
      {
         // For Windows also find LNK (shortcut) files and resolve
         if (accessible->has_extension_ASCII("LNK"))
         {  CORN::OS::File_name_concrete accessible_without_LNK
               (*accessible
               ,CORN::OS::Directory_entry_name::include_all_except_extension);
            if (inclusion.is_included_DEN(accessible_without_LNK));
            {
               CORN::OS::Directory_entry_name *accessible_resolved
                  = CORN::OS::file_system_engine
                    .render_resolved_shortcut_or_assume_actual(*accessible);
               if (accessible_resolved )
                  DEN_list.take(accessible_resolved);
            }
         }
      }
      #endif
   } FOR_EACH_END(each_accessible)
   return extracted;
}
//_2017-06-27___________________________________________________________________
nat16 Context_discovery_common::extract_accessible_files_with_extension
(const std::wstring &extension
,modifiable_ CORN::Container &file_list)                           contribution_
{
   std::wstring nameless_pattern(L"."); nameless_pattern.append(extension);      //170626
   extract_accessible_files_with_pattern(nameless_pattern,file_list);            //170626
   std::wstring pattern(L"*."); pattern.append(extension);
   return extract_accessible_files_with_pattern(pattern,file_list);
}
//_2017-06-27___________________________________________________________________
nat16 Context_discovery_common::compose_accessible_parameter_files
(modifiable_ CORN::Data_record &data_rec
,const std::wstring &extension
,CORN::Container *caller_keeps_filenames)                          contribution_
{  nat16 from_files_count = 0;
   CORN::Unidirectional_list other_files;
   if (verbose > 2)
   {
      std::string extension_str;
      CORN::wstring_to_string(extension,extension_str);
      std::clog << "composing any accessible parameter files with extension:"
      << extension_str
      << std::endl;
   }
   // accessible_files is presumed to be sorted!
   for (CORN::OS::File_name *accessible_file =
           dynamic_cast<CORN::OS::File_name *>(accessible_files.pop_first())
       ; accessible_file
       ; accessible_file =
           dynamic_cast<CORN::OS::File_name *>(accessible_files.pop_first()))
   {  bool apropos = accessible_file->has_extension(extension);
      if (!apropos)
      {  std::wstring accessible_file_name_with_ext;
         accessible_file->get_name_with_extension(accessible_file_name_with_ext);
         apropos = (accessible_file_name_with_ext == extension);
      }

//std::clog << accessible_file->c_str() << std::endl;


      if (apropos)
      {
         if (verbose>3) // discovery
            std::clog << accessible_file->c_str() << std::endl;
         CORN::VV_File param_file(accessible_file->c_str(),true);
         from_files_count += param_file.get(data_rec);
         const CORN::OS::Directory_name &param_file_dir
             = accessible_file->get_parent_directory_name_qualified();
         data_rec.resolve_directory_entry_names(param_file_dir);
         if (caller_keeps_filenames)
             caller_keeps_filenames->take(accessible_file);
         else delete accessible_file;
      } else other_files.take(accessible_file);
    }
   if ((verbose > 2) && (from_files_count == 0))                                 //180119
   {  std::clog << " none found" << std::endl; }                                 //180119
   accessible_files.transfer_all_from(other_files);
   return from_files_count;
}
//_2017-06-29___________________________________________________________________
Context_discovery_common::Context_discovery_common()
: leaf(0),leaf_owned(true)
, root(0),root_owned(true)
, accessible_files   ()                                                          //170627
, verbose(0)                                                                     //170214
{
   leaf = new CORN::OS::Directory_entry_name_concrete;
   initialize();                                                                 //170627
   // root_level currently always going to be the root of the drive.
}
//_2015-12-06___________________________________________________________________
Context_discovery_common::Context_discovery_common
(const CORN::OS::Directory_name &leaf_
,const CORN::OS::Directory_name *root_)
: leaf(const_cast<CORN::OS::Directory_name *>(&leaf_)),leaf_owned(false)
, root(const_cast<CORN::OS::Directory_name *>(root_)),root_owned(false)
, accessible_files   ()                                                          //170627
{
   // root_level currently always going to be the root of the drive.
   initialize();                                                                 //170627
}
//_2016-11-02___________________________________________________________________
Context_discovery_common::~Context_discovery_common()
{
   if (leaf_owned) delete leaf;
   if (root_owned) delete root;
}
//_2015-12-08___________________________________________________________________
bool Context_discovery_common::initialize()                      initialization_
{
//   CORN::Inclusion recognized_inclusions("*.*",false);
   CORN::Exclusion recognized_inclusions("*.sh",true);
   recognized_inclusions.exclude_pattern_cstr("*.bat");
   recognized_inclusions.exclude_pattern_cstr("*.bash");
   recognized_inclusions.exclude_pattern_cstr("*.zip");

      // Currently this is including all files, but may need to include only
      // files recognized by CS programs
   CORN::OS::file_system_engine.list_DENs
      (*leaf,&accessible_files,0,recognized_inclusions
      ,CORN::OS::File_system::superdirectory_recursion_inclusive,root);
/*Sorting is locking up
   accessible_files.sort();
*/
// accessible_files.write(std::clog); // debug

   return true;
}
// 2017-06-27___________________________________________________________________
bool Context_discovery_common::get_geolocation
(const CORN::OS::Directory_entry_name  &file_or_directory
,const char *geolocation_section
,modifiable_ Geolocation      &geolocation
,modifiable_ std::string      &ISO_6709_annex_D_or_H)                      const
{  bool got_geolocation = false;
   // 1st priority see if there is a geolocation in this scenario or any parent directories
   // Search for files with .CS_geolocation

   CORN::Data_record geolocation_datarec(geolocation_section/*"location"*/);     //170629
   geolocation.setup_structure(geolocation_datarec,false);                       //170629
   CORN::Unidirectional_list geolocations;                                       //170628
   nat32 geoloc_count = geoloc_count
   = compose_accessible_parameter_files                                          //170628
      (geolocation_datarec,L"CS_geocoordinate",&geolocations);
   + compose_accessible_parameter_files                                          //170628
      (geolocation_datarec,L"CS_geolocation"  ,&geolocations);

   // also look for geocoordinate files if (geoloc_count==0)  // maybe there will be simple geocoordinate files
   if (geoloc_count)
   {  // The geolocation in the deepest directory has highest priorty
      // If the geolocation is in the name of the file as ISO_6709, remember the ISO coding for return.
      got_geolocation = true;
      FOR_EACH_IN(geofile,CORN::OS::File_name,geolocations,each_geofile)
      {
         Geocoordinate geocoord_unused;
         std::string pot_geoloc_filename_as_ISO_6709_annex_D_or_H;
         CORN::wstring_to_string(geofile->get_name(),pot_geoloc_filename_as_ISO_6709_annex_D_or_H);
         bool name_is_geocoor = geocoord_unused.set_latitude_and_longitude(pot_geoloc_filename_as_ISO_6709_annex_D_or_H);
         if (name_is_geocoor)
            ISO_6709_annex_D_or_H = pot_geoloc_filename_as_ISO_6709_annex_D_or_H;
      } FOR_EACH_END(each_geofile)
   }
   if (!got_geolocation)
   {  // 2nd priority see if there is geocoordinate in the name of the
      // file/directory or any parent directories

      CORN::Text_list potential_geocoordinates;
      Geocoordinate geocoord;
      file_or_directory.append_path_list_to
         (potential_geocoordinates);
      std::wstring name_with_extension;
      // The last name decimal point gets interpreted as an extension,
      // so this is handled separately.
      // I haven't check where geolocation is further up the path
      // I am not sure if in that case the final decimal point
      // is also interpreted as an extension (I dont think so).
      potential_geocoordinates.add_wstring
         (file_or_directory.get_name_with_extension(name_with_extension));

      // This should also be able to recognize
      // something like 46.7797N_117.0851W.Pullman


      // NYI need to add: either the file or directory name or extension

      bool superceed_geoloc = false;
      for (CORN::Item_string *pot_geocoord = dynamic_cast<CORN::Item_string *>
            (potential_geocoordinates.pop_at_tail())
          ;pot_geocoord && ! superceed_geoloc
          ;pot_geocoord = dynamic_cast<CORN::Item_string *>
            (potential_geocoordinates.pop_at_tail()))
      {
/*
if (*pot_geocoord == "46.7700N117.1048W")
std::clog <<"reached" << std::endl;
*/
         bool name_is_geocoor = geocoord.set_latitude_and_longitude(*pot_geocoord);
         if (name_is_geocoor)
         {  superceed_geoloc = true;
                geocoord.set_elevation_meter(geolocation.get_elevation());
                geolocation.copy_from_geocoordinate(geocoord);
            got_geolocation = true;
            ISO_6709_annex_D_or_H.assign(*pot_geocoord);                         //160110
         }
      }
   }
   return got_geolocation;
}
//_2015-12-06_________________________________________________get_geolocation__/
bool Context_discovery_common::know_leaf(const CORN::OS::Directory_name &leaf_) cognition_
{  {  if (leaf_owned) delete leaf;
      leaf = const_cast<CORN::OS::Directory_name *>(&leaf_); leaf_owned = false;
   }
   return leaf != 0;
}
//_2015-12-08___________________________________________________________________
bool Context_discovery_common::take_leaf(CORN::OS::Directory_name *leaf_)
{  if (leaf_)
   {  if (leaf_owned) delete leaf;
      leaf = leaf_; leaf_owned = true;
   }
   return leaf != 0;
}
//_2015-12-08___________________________________________________________________
bool Context_discovery_common::know_root(const CORN::OS::Directory_name *root_) cognition_
{  {  if (root_owned) delete root;
      if (root_)
      {  root = const_cast<CORN::OS::Directory_name *>(root_);
         root_owned = false;
      } else
      {
         std::cerr << "NYI find reset to primary project, or user home or file system root" << std::endl;
         /* NYI
         search for primary project
         if not found search for users home in the path (don't just get home)
         because the CWD (leaf or whatever) is not necessarily under the home directory
         if home not found find file system root
         */
      }
   }
   return root != 0;
}
//_2015-12-08___________________________________________________________________
bool Context_discovery_common::take_root(CORN::OS::Directory_name *root_)
{  if (root_)
   {  if (root_owned) delete root;
      root = root_; root_owned = true;
   }
   return root != 0;
}
//_2015-12-08___________________________________________________________________
/*Check reimplement
CORN::OS::Directory_name * Context_discovery_common::find_level
(Directory_level level
,const CORN::OS::Directory_name *from_directory)                      rendition_
{
   CORN::OS::Directory_name *found_level_rendered = 0;
   if (from_directory->is_root())
   {  found_level_rendered =
       (level == file_system_root_level)
         ? new CORN::OS::Directory_name_concrete(*from_directory)
         : 0; // we are at the root so the level was not found;
   } else
   {  found_level_rendered = find_level                                          //160307
         (level,from_directory->get_path_directory_name());
      if (!found_level_rendered)
      {
         if (is_level(*from_directory,level))
            found_level_rendered = new CORN::OS::Directory_name_concrete(*from_directory);
         else // recurse
         {  const CORN::OS::Directory_name *parent = from_directory->get_path_directory_name();
            found_level_rendered = (parent)
               ? find_level(level,parent)
               : 0;
         }
      }
   }
   return found_level_rendered;
}
//_2015-12-08___________________________________________________________________
*/
/*161116 check reimplement
CORN::OS::Directory_name *Context_discovery_common::set_level_as_root(Directory_level level) rendition_
{
   CORN::OS::Directory_name *found_level_rendered = find_level(level,leaf);
   if (found_level_rendered)
      know_root(found_level_rendered);
   return found_level_rendered;
}
*/
//_2015-12-08___________________________________________________________________
/*160301 RLN
bool File_discovery::set_level_as_root(Directory_level level)         rendition_
{  bool was_set = false;
   CORN::OS::Directory_name *found_level_rendered = find_level(level,leaf);
   if (found_level_rendered)
      was_set = take_root(found_level_rendered);
   if (!was_set)
      delete found_level_rendered;
   return was_set;
}
//_2015-12-08___________________________________________________________________
*/
const CORN::OS::Directory_name &Context_discovery_common::provide_leaf()        provision_
{
   if (!leaf)
   {  leaf = new CORN::OS::Directory_name_concrete();
      leaf_owned = true;
   }
   return *leaf;
}
//_2016-11-16___________________________________________________________________
/* check if need to reimplement
bool Context_discovery_common::is_level
(const CORN::OS::Directory_name &directory
,Directory_level level)                                             affirmation_
{

   bool it_is
   =  ((directory.is_root()) && (level == file_system_root_level))
   || ((directory.get_name() == L"Scenarios") && (level == scenarios_level));
   if (!it_is && (level == project_level))
   {  // Check if this is project
      CORN::OS::File_name_concrete project_file(directory,".CS_project");
      it_is = CORN::OS::file_system_engine.exists(project_file) ;
      if (!it_is)                                                                //160307
      {  CORN::OS::Directory_name_concrete database_dir(directory,"Database");   //160307
         it_is = CORN::OS::file_system_engine.exists(database_dir);              //160307
      }
   }
   if (!it_is && (level == scenario_level))
   {
      CORN::OS::File_name_concrete scenario_file(directory,".CropSyst_scenario");
      it_is = CORN::OS::file_system_engine.exists(scenario_file);
   }
   return it_is;
}
*/
//_2015-12-08___________________________________________________________________
/*170629 obsolete, replaced with reset_missing_with_accessible
bool Context_discovery_common::find_and_reset_missing_parameter_file_name
(modifiable_ CORN::OS::File_name &parameter_file_name
,const wchar_t *extension_expected
,const wchar_t *extension_alternate
,CORN::OS::File_system::Recursion recursion)                               const
{
   bool filename_reset = false;
   if (!CORN::OS::file_system_engine.exists(parameter_file_name))
   {  CORN::Unidirectional_list discovered_param_files;
      nat8 param_file_count =
         //170628 find_files_with_extension_wstring
         extract_accessible_files_with_extension
         (extension_expected,discovered_param_files
         //170628 ,CORN::OS::File_system::superdirectory_recursion_inclusive
         );
      if (!param_file_count && extension_alternate)
         param_file_count =
            //170628 find_files_with_extension_wstring
            extract_accessible_files_with_extension
            (extension_alternate,discovered_param_files
            //170628,CORN::OS::File_system::superdirectory_recursion_inclusive
            );
      CORN::OS::File_name *discovered_filename = dynamic_cast<CORN::OS::File_name *>
         (discovered_param_files.pop_at_tail());
      // Use the file found with the greatest specificity
      // (currently this would be listed last, but probably should sort the list)//160128
      if (discovered_filename)
      {
         parameter_file_name.set_DEN(*discovered_filename);
         filename_reset = true;
         delete discovered_filename;
      }
   }
   return filename_reset;
}
*/
//_2016-01-26___________________________________________________________________
bool Context_discovery_common::reset_missing_with_accessible
(modifiable_ CORN::OS::File_name &parameter_file_name
,const wchar_t *extension_expected
,const wchar_t *extension_alternate)                               contribution_
{  bool resat = false;
   CORN::Unidirectional_list other_files;
   for (CORN::OS::File_name *accessible = dynamic_cast<CORN::OS::File_name *>(accessible_files.pop_first())
       ;accessible
       ;accessible = dynamic_cast<CORN::OS::File_name *>(accessible_files.pop_first()))
   {


//std::clog << accessible->c_str() << std::endl;


      if (accessible->has_extension_Unicode(extension_expected))
      {  parameter_file_name.set_DEN(*accessible);
         /* Conceptual
         if (call_keeps_replaced)
            call_keeps_replaced.take(accessible);
         else
         */
         delete accessible; accessible = 0;
         resat = true;
      } else if (extension_alternate && accessible->has_extension_Unicode(extension_alternate))
      {  parameter_file_name.set_DEN(*accessible);
         delete accessible;  accessible = 0;
        resat = true;
      } else other_files.take(accessible);
   }
   accessible_files.transfer_all_from(other_files);
   return resat;
}
//_2017-06-29___________________________________________________________________
nat16 Context_discovery_common::reset_data_record_missing_with_accessible
(CORN::Data_record &data_record)                                   contribution_
{  nat16 resat = 0;
   CORN::Unidirectional_list other_files;
   FOR_EACH_IN(section,CORN::VV_Section,data_record.sections,each_section)
   {  FOR_EACH_IN(entry,CORN::VV_abstract_entry,section->entries,each_entry)
      {  const CORN::VV_directory_entry_entry *entry_as_DEN =
            dynamic_cast<const CORN::VV_directory_entry_entry *>(entry);
         if (entry_as_DEN
             && !entry_as_DEN->ref_value().has_name(true))                       //170202
         {  CORN::OS::Directory_entry_name &param_filename = entry_as_DEN->ref_value();
            bool found_and_reset = false;
            #if ((CS_VERSION > 0) && (CS_VERSION <= 5))
               // Recognize both new and old file extensions
                // Version 6 and beyond will drop support for the old extensions
               Alternate_extensions *alt_exts = lookup_alternate_extensions_by_variable
                  (entry->get_variable().c_str()/*180821 get_key()*/);                   //170202
               if (alt_exts)
                  found_and_reset = reset_missing_with_accessible
                        (param_filename,alt_exts->extension[0],alt_exts->extension[1]);
               else
            #endif
               {  std::wstring param_file_extension(param_filename.get_extension());
                  found_and_reset = reset_missing_with_accessible
                        (param_filename,param_file_extension.c_str(),0);
               }
               resat += found_and_reset;
               if (found_and_reset && (verbose==2)) //resolution  //170420
               {  std::clog << "info: found and set parameter file"
                     <<  "[" << section->get_label()/*180820 get_key()*/ << "]";
                  entry->write_key(std::clog);  //180820                     
                   //180820   << entry->get_key() 
                   std::clog
                     << "=" << param_filename.c_str() <<  std::endl;
               }
         } // if as DEN
      } FOR_EACH_END(each_entry)
   } FOR_EACH_END(each_section)
   return resat;
}
//_2017-06-29___________________________________________________________________

} // namespace CS

