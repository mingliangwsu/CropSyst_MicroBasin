#define NO_HELP_YET 0

#if (CS_VERSION==4)
#  include "form_UED_spatial_interpolator_VCL_BCB5.h"
#  include <GUI/parameter/form_param_file.h>
#  include <common/geolocation/gui/geolocation_frm.h>
#define _NO_HELP_YET  ,NO_HELP_YET

#else
#  include "form_UED_spatial_interpolator_VCL_RS.h"
#  include <GUI/parameter/form_param_file_RS.h>
#  include "common/geodesy/GUI/form_geolocation_VCL_RS.h"
//#  include <common/geolocation/gui/BDS/form_geolocation.h>
#define _NO_HELP_YET

#endif
#include "corn/string/strconv.hpp"
//______________________________________________________________________________
#include <vcl.h>
#pragma hdrstop
#include <UED/spatial/interpolation/UED_database_interpolate_datarec.h>
#include <corn/OS/OS.h>
#include <corn/container/text_list.h>
#include <corn/data_source/dbase_datasrc.h>
#include <UED/library/database_file.h>
#include <UED/library/locrec.h>
#include <corn/math/compare.hpp>
#ifdef USE_OS_FS
#  include "corn/OS/file_system_engine.h"
#  include "corn/application/program_directory_OS_FS.h"
#endif
//______________________________________________________________________________
void TUED_spatial_interpolator_form::setup_geoloc_form()
{  geoloc_form = new Tgeolocation_form(tabsheet_target_coordinate);
   geoloc_form->Parent = tabsheet_target_coordinate;
   geoloc_form->Show();
   geoloc_form->Top = 0;
   geoloc_form->Left = 0;
   geoloc_form->Width = tabsheet_target_coordinate->Width;
   geoloc_form->Height= tabsheet_target_coordinate->Height;
   geoloc_form->BorderStyle = bsNone;
   geoloc_form->Align = alClient;
   geoloc_form->BorderStyle = bsNone;
};
//_2013-03-12________________________________________________setup_geoloc_form_/
void TUED_spatial_interpolator_form::bind_to(UED_database_interpolate_data_record *_interpolate_options,Tparameter_file_form  *_parameter_file_form)
{
   parameter_file_form = _parameter_file_form;
   interpolate_options = _interpolate_options;

   source_UED_files_listbox->bind_to(&(interpolate_options->source_UED_filenames) _NO_HELP_YET);
//100924 now we target a directory   target_UED_complete_files_listbox->bind_to(&(interpolate_options->target_UED_filenames) _NO_HELP_YET);
//in this directory there could be exclusions.
//We do not have an excluded file list in the UI; instead,
//we have a target directory file list box where the excluded files are unselected.
//   target_UED_complete_files_check_listbox->bind_to(&(interpolate_options->target_UED_filenames)_NO_HELP_YET);

   interpolation_mode_radiogroup->bind_to(&(interpolate_options->interpolation_mode_labeled) _NO_HELP_YET);
   edit_within_radius->bind_to(&(interpolate_options->within_radius_km) _NO_HELP_YET);

   checkbox_lapse_rate_adjustement->bind_to(&(interpolate_options->estimate_environmental_lapse_rate_adjustment) _NO_HELP_YET);

   checklistbox_selected_elements->bind_to(&(interpolate_options->selected_elements),0 _NO_HELP_YET);
//090504   radio_group_include_elements->bind_to(&(interpolate_options->source_element_include_labeled) _NO_HELP_YET);

   //NYI allow_interpolated_data_checkbox

   // NYI point_ID_combobox->bind_to list of attributes in the database table
   // see how this is done in CropSyst project GIS

//NYI   points_dbf_filebar->bind_to(&(interpolate_options->points_dbf_filename) _NO_HELP_YET);

//NYI   points_dbf_filebarChange(0);

   edit_target_UED_filename_prefix->bind_to((&(interpolate_options->target_UED_filename_prefix)) _NO_HELP_YET);

   begin_year_edit->bind_to(&(interpolate_options->begin_year) _NO_HELP_YET);
   end_year_edit->bind_to(&(interpolate_options->end_year) _NO_HELP_YET);

//obs   between_first_station_filebar->bind_to(&between_first_UED,0);
   DragAcceptFiles(edit_between_1->Handle,true);
//obs   between_second_station_filebar->bind_to(&between_second_UED,0);
   DragAcceptFiles(edit_between_2->Handle,true);

//100924 obs now using pagecontrol   radiogroup_target_mode->bind_to(&(interpolate_options->target_mode),0 _NO_HELP_YET);
   radiogroup_source_mode->bind_to(&(interpolate_options->source_mode),0 _NO_HELP_YET);
//110503    Update();
}

//______________________________________________________________________________
void TUED_spatial_interpolator_form::handle_Update()
{
   source_UED_files_listbox         ->Update();
//100924 now using page control   target_UED_complete_files_listbox->Update();
//   target_UED_complete_files_check_listbox->Update();
   target_UED_files_check_listbox   ->Directory = interpolate_options->target_directory.c_str();

   interpolation_mode_radiogroup    ->Update();
   edit_within_radius               ->Update();
   checkbox_lapse_rate_adjustement  ->Update();
   begin_year_edit                  ->Update();
   end_year_edit                    ->Update();
   if (geoloc_form && interpolate_options)
      geoloc_form->bind_to(&interpolate_options->geolocation,&description);         //100924
   checklistbox_selected_elements   ->Update();

   pagecontrol_target_UED                        ->ActivePageIndex = interpolate_options->target_mode; // complete files or create points
   pagecontrol_target_copy_or_update             ->ActivePageIndex = interpolate_options->copy_or_update_mode;
   pagecontrol_target_generate_single_or_multiple->ActivePageIndex = interpolate_options->generate_points_mode;
   pagecontrol_target_point_creation_mode        ->ActivePageIndex = interpolate_options->single_point_mode; // either geocoordinate or centroid
   pagecontrol_target_multiple_location          ->ActivePageIndex = interpolate_options->multiple_points_mode; // coordinate either entered or dBase

//   pagecontrol_target_UED->ActivePage = tabsheet_target_complete;
//090504   radio_group_include_elements->Update();

   // NYI  eed to file points grid
   // NYI  point_ID_combobox->Update();
   // NYI  points_dbf_filebar->Update();

//100924   radiogroup_target_mode->Update();
   radiogroup_source_mode->Update();

   edit_target_directory->Text = interpolate_options->target_directory.c_str();
   edit_source_directory->Text = interpolate_options->source_directory.c_str();

//Now always shown   panel_target_directory     ->Visible = interpolate_options->target_mode == 0;
//100924obs   groupbox_target_files      ->Visible = interpolate_options->target_mode == 1;
   edit_source_directory      ->Visible = interpolate_options->source_mode == 0;
   groupbox_source_UED_files  ->Visible = interpolate_options->source_mode == 1;
   edit_target_UED_filename_prefix->Update();
   {   // points DBF    //100926
      combobox_latitude_field ->bind_to(&(interpolate_options->points_table_latitude_field_name)   ,0 _NO_HELP_YET);
      combobox_longitude_field->bind_to(&(interpolate_options->points_table_longitude_field_name)  ,0 _NO_HELP_YET);
      combobox_elevation_field->bind_to(&(interpolate_options->points_table_elevation_field_name)  ,0 _NO_HELP_YET);
      combobox_point_ID_field ->bind_to(&(interpolate_options->points_table_ID_field_name)         ,0 _NO_HELP_YET);
   };

   filenameedit_points_table->Text = interpolate_options->points_dbf_filename.c_str();

   // show included/excluded UED files.
   highlight_selected_targets();
}
//______________________________________________________________________________
void TUED_spatial_interpolator_form::highlight_selected_targets()
{
   for (int i = 0; i < target_UED_files_check_listbox->Items->Count; i++)
   {
      #if (CS_VERSION==4)
      std::string checked_item(target_UED_files_check_listbox->Items->Strings[i].c_str());
      #else
      std::string checked_item;
      wstring_to_string(target_UED_files_check_listbox->Items->Strings[i].c_str(),checked_item);
      #endif

      bool excluded
         = (interpolate_options->exclude_target_UED_filenames.find_string(checked_item/*130308.c_str()*/));
      target_UED_files_check_listbox->Selected[i] = !excluded;
   };
};
//______________________________________________________________________________
/*
#ifdef MAYBE_OBSOLETE
void __fastcall TUED_spatial_interpolator_form::radiogroup_target_modeClick(
      TObject *Sender)
{
   panel_target_directory->Visible = interpolate_options->target_mode == 0;
   groupbox_target_files->Visible = interpolate_options->target_mode == 1;


};
#endif
*/
//______________________________________________________________________________
void TUED_spatial_interpolator_form::handle_select_source_UED_button_onclick()
{  if (!interpolate_options) return;
   if(UED_open_dialog->Execute())
   {  for (int i = 0; i < UED_open_dialog->Files->Count; i++)
      {
         CORN_File_name_instance *listed_filename =  new CORN_File_name_instance(UED_open_dialog->Files->Strings[i].c_str()); //130308
         #ifndef USE_OS_FS
         listed_filename->set_show_path();
         listed_filename->set_show_extension();
         #endif
         interpolate_options->source_UED_filenames.append(listed_filename);
      };
      source_UED_files_listbox->Update();
   };
}

//______________________________________________________________________________
void TUED_spatial_interpolator_form::handle_clear_source_UED_button_onclick()
{  if (!interpolate_options) return;
   interpolate_options->source_UED_filenames.delete_all();
   source_UED_files_listbox->Update();
}
//______________________________________________________________________________
void TUED_spatial_interpolator_form::handle_start_interpolation_button_onclick()
{
   if (!interpolate_options) return;
#ifdef NYI_OR_OBSOLETE
for create point or points mode, the
UED file is created(or updated) by the interpolate program,
but only if the point has nearby UEDs within the prescribed proximity radius.

   if (pagecontrol_target_UED->ActivePage == tabsheet_target_create)
   {  // if were are in create target UED files mode we need to copy
      // the selected file names in target_UED_files_check_listbox
      // to the list of target UED files

      for (int index = 0; index <  target_UED_files_check_listbox->Items->Count; index++)
      {
         if (target_UED_files_check_listbox->Checked[index])
         {
            CORN::File_name *checked_filename = new CORN::File_name(target_UED_files_check_listbox->Items->Strings[index].c_str());
            checked_filename->set_checked(true);
            interpolate_options->target_UED_filenames.append(checked_filename);
         };
      };
      target_UED_complete_files_listbox->Update();
//      target_UED_complete_files_check_listbox->Update();
   };

#endif
   bool result
      = (interpolate_options->target_mode == 0)
         ?  // complete UED
            (interpolate_options->copy_or_update_mode == 0)
            ? copy_UEDs_interpolate()
            : update_interpolate()
         :  // generate points
            (interpolate_options->generate_points_mode == 0)
            ? // single point
               (interpolate_options->single_point_mode == 0)
               ?  generate_at_geocoordinate_interpolate(true)
               :  generate_at_centroid_interpolate()
            : // multiple points
               (interpolate_options->multiple_points_mode == 0)
               ? generate_from_entered_coordinates_interpolate()
               : generate_from_dBase_table_interpolate();
};
//______________________________________________________________________________
int TUED_spatial_interpolator_form::run_interpolation()
{
   int exit_status = EXIT_SUCCESS;                                               //130311
#ifdef USE_OS_FS
   CORN::OS::Directory_name_logical this_program(ParamStr(0).c_str());
   CORN::OS::File_name_logical UED_spatial_interpolate_exe(this_program.get_parent_directory_name_qualified(),"UED_spatial_interpolate.exe");
//UED_spatial_interpolate_exe.set_str("C:\\CS_Suite_5\\UED\\spatial\\interpolation\\UED_spatial_interpolate.exe");
   if (!CORN::OS::file_system_engine.exists(UED_spatial_interpolate_exe))
#else
   CORN::Smart_file_name  UED_spatial_interpolate_exe(ParamStr(0).c_str());
   UED_spatial_interpolate_exe.set_name_ext("UED_spatial_interpolate.exe");
//UED_spatial_interpolate_exe.set_str("C:\\CS_Suite_5\\UED\\spatial\\interpolation\\UED_spatial_interpolate.exe");
   if (!UED_spatial_interpolate_exe.exists())
#endif
   {
         String message ("Could not find the interpolator engine:");
         message += UED_spatial_interpolate_exe.c_str();
         Application->MessageBox(message.c_str(),message.c_str(),MB_OK);
         Application->MessageBox(message.c_str(),_TEXT("Interpolator engine not found"),MB_OK);

         // NYI consider adding this message to explainations list
         exit_status = EXIT_FAILURE;
         //130311 return false;
   } else
   {
      exit_status = parameter_file_form->run_file_with_program
         (UED_spatial_interpolate_exe.c_str()   // Warning need to add this to  common paths
         ,parameter_file_form->get_parameter_filename_prompt_in_necessary()   //name of response file 0  // secondary_file
         , 0 // options
         , true   // wait_for_termination
         , (show_interpolation_checkbox->State == cbChecked)? SW_MAXIMIZE : SW_MINIMIZE)
         ? EXIT_SUCCESS
         : EXIT_FAILURE;
      Application->ProcessMessages();
   }
   parameter_file_form->update_explaination(exit_status == EXIT_FAILURE);        //130311
   return exit_status;
};
//______________________________________________________________________________
bool TUED_spatial_interpolator_form::copy_UEDs_interpolate()
{
   if (interpolate_options->source_mode == 0)
   {  CORN::OS::file_system_engine.list_file_names
         (interpolate_options->source_directory,true,interpolate_options->source_UED_filenames,0,L"UED");
   }; // else The user already selected the source UED files
#ifdef USE_OS_FS
   FOR_EACH_IN(source_UED_file,CORN::OS::File_name,interpolate_options->source_UED_filenames,each_source)
   {  CORN::OS::File_name_logical target_UED_file(interpolate_options->target_directory,*source_UED_file);
      if (!CORN::OS::file_system_engine.exists(target_UED_file))
         CORN::OS::file_system_engine.copy_file(*source_UED_file, target_UED_file,false);
      Application->ProcessMessages();
   } FOR_EACH_END(each_source);;
#else
   FOR_EACH_IN(source_UED_file,CORN::OS::File_name,interpolate_options->source_UED_filenames,each_source)
   {  CORN::Smart_file_name target_UED_file(*source_UED_file);
      target_UED_file.set_path(interpolate_options->target_directory);
      if (!target_UED_file.exists())
         OS_copy_file(source_UED_file->c_str(), target_UED_file.c_str());
      Application->ProcessMessages();
   } FOR_EACH_END(each_source);;
#endif
   update_interpolate();
   return true;
};

//______________________________________________________________________________
bool TUED_spatial_interpolator_form::update_interpolate()
{
   nat32 interps_performed = 0;
   // Record excluded files
   UED_spatial_interpolator_pagecontrol->ActivePage = target_databases_tabsheet;
   #ifdef USE_OS_FS
   CORN::Unidirectional_list target_UED_filenames;
   CORN::OS::file_system_engine.list_file_names
      (interpolate_options->target_directory
      ,false   // not recursive
      ,target_UED_filenames
      , 0 //name_wild_card
      ,L"UED"); //extension_filter
   target_UED_files_check_listbox->Update();
   FOR_EACH_IN(target_UED_filename,CORN::OS::File_name ,target_UED_filenames,each_file)
   {  //CORN::OS::File_name_logical target_UED_filename(*target_UED_filename_raw);
      //std::wstring name_with_extension_w;
      //target_UED_filename.get_name_with_extension(name_with_extension_w);
      //std::string name_with_extension; CORN::wstring_to_string(name_with_extension_w,name_with_extension);
      if (!interpolate_options->exclude_target_UED_filenames.find_wstring((target_UED_filename->get_name())))
      {  interpolate_options->current_target_UED_filename.set_DEN(*target_UED_filename); //130309
         if (run_interpolation() == EXIT_SUCCESS)
         {  for (int i = 0; i < target_UED_files_check_listbox->Items->Count; i++)
            {  if (target_UED_files_check_listbox->Items->Strings[i] == target_UED_filename->get_name().c_str()) //1303010target_UED_filename.get_name_with_extension(name_with_extension).c_str())
                  target_UED_files_check_listbox->Checked[i] = true;
            };
            interps_performed += 1;
         };
      };
   } FOR_EACH_END(each_file);

   #else
   CORN::Association_list target_UED_filenames;
   interpolate_options->target_directory.list_contents_by_type
      (target_UED_filenames
      ,false   // not recursive
      ,true    // qualify
      ,true    // with_extension
      ,false   // dont show_path
      ,false   // dont i_show_extension
      ,Directory_entry_name::file_entry
      ,"UED");
   FOR_EACH_IN(target_UED_filename,CORN::File_name,target_UED_filenames,each_file)
   {  if (!interpolate_options->exclude_target_UED_filenames.find(target_UED_filename->get_name(true).c_str()))
      {  if (run_interpolation() == EXIT_SUCCESS)
         {  for (int i = 0; i < target_UED_files_check_listbox->Items->Count; i++)
            {  if (target_UED_files_check_listbox->Items->Strings[i] == target_UED_filename->get_name(true).c_str())
                  target_UED_files_check_listbox->Checked[i] = true;
            };
            interps_performed += 1;
         };
      };
   } FOR_EACH_END(each_file);
   #endif
   return interps_performed > 0;
};
//______________________________________________________________________________
void TUED_spatial_interpolator_form::setup_target_UED_filename_for_point()
{  // The geolocation has been bound and will be set of save for the run_iterpolate
   std::string station_ID_code(interpolate_options->geolocation.get_station_ID_code());
   // Composing UED filename with either entered station ID or prefix lat long.
   if (!station_ID_code.length())
   {  station_ID_code.assign(interpolate_options->target_UED_filename_prefix);
      //station_ID_code.append("_");
      //Currently assuming 5 digits precision
      station_ID_code.append(CORN_float64_to_str(interpolate_options->geolocation.get_latitude_dec_deg(),5));
      station_ID_code.append("_");
      station_ID_code.append(CORN_float64_to_str(interpolate_options->geolocation.get_longitude_dec_deg(),5));
      station_ID_code.append(".UED");
//      interpolate_options->current_target_UED_filename.set_ext("UED");
   }
   #ifdef USE_OS_FS
   CORN::OS::File_name_logical new_name(interpolate_options->target_directory,station_ID_code.c_str(),"UED");
//   interpolate_options->current_target_UED_filename.set_name(station_ID_code.c_str());
//   interpolate_options->current_target_UED_filename.set_ext("UED");
//   interpolate_options->current_target_UED_filename.set_path();
   interpolate_options->current_target_UED_filename.set_DEN(new_name);
   #else
   interpolate_options->current_target_UED_filename.set_name(station_ID_code.c_str());
   interpolate_options->current_target_UED_filename.set_ext("UED");
   interpolate_options->current_target_UED_filename.set_path(interpolate_options->target_directory);
   #endif
};
//______________________________________________________________________________

bool TUED_spatial_interpolator_form::generate_at_geocoordinate_interpolate(bool interactive)
{
   setup_target_UED_filename_for_point();
   if (interactive &&
      #ifdef USE_OS_FS
      CORN::OS::file_system_engine.exists(interpolate_options->current_target_UED_filename)
      #else
      interpolate_options->current_target_UED_filename.exists()
      #endif
      )
   {
         if ((Application->MessageBox(_TEXT("Overwrite/update existing UED file?"),_TEXT("File already exists"),MB_YESNO)) == ID_NO)
         {  return false;
         };
   };
   int run_exit_status = run_interpolation();
   if  (interactive)
      Application->MessageBox
            (run_exit_status == EXIT_SUCCESS
               ? _TEXT("Success") : _TEXT("Failure (perhaps there were no proximate stations with desired elements)")
               ,_TEXT("Interpolation completed"),MB_OK);

   return run_exit_status = EXIT_SUCCESS;
};

//______________________________________________________________________________
bool TUED_spatial_interpolator_form::generate_at_centroid_interpolate()
{
   setup_target_UED_filename_for_point();
   // currently this is the same as generate_at_geocoordinate_interpolate
   // the interpolator will detect and perform centroid mode.
   generate_at_geocoordinate_interpolate(true);
   #ifdef USE_OS_FS
   if (CORN::OS::file_system_engine.exists(interpolate_options->current_target_UED_filename))
   #else
   if (interpolate_options->current_target_UED_filename.exists())
   #endif
   {
         if ((Application->MessageBox(_TEXT("Overwrite/update existing UED file?"),_TEXT("File already exists"),MB_YESNO)) == ID_NO)
         {  return false;
         };
         Application->MessageBox
            ((run_interpolation() == EXIT_SUCCESS)
               ? _TEXT("Success") : _TEXT("Failure (perhaps there were no proximate stations with desired elements)")
               ,_TEXT("Interpolation completed"),MB_OK);
   };
   return true;

#ifdef NYI
   make sure that UED files have been selected.
   Currently two UED files (which may not necessarily be source  UED files)
   are selected to determine the centroid.
   eventually I want determine the centroid from the selected source UED files

   makesure the target UED filename has been entered
   and prompt to continue if the file already exists.

   if (interpolate() == EXIT_SUCCESS)
      message that interpolation completed
   else
      message that probably no stations in range of centroid

   (the interpolator will calculate the centriod and determine
   if there are proximate UED files to generate the file).
   return true;
#endif
};
//______________________________________________________________________________
bool TUED_spatial_interpolator_form::generate_from_entered_coordinates_interpolate()
{
   int points_interpolated = 0;
   //make sure geolocation and station ID (or prefix) have been entered
//   bool any_IDs_empty = false;
   for (int row = 0; row < generate_points_grid->RowCount; row++)
   {  // for each entry in the grid.
      float32 latitude_dec_deg  = generate_points_grid->Floats[1][row+1];
      float32 longitude_dec_deg = generate_points_grid->Floats[2][row+1];
      float32 elevation_m =       generate_points_grid->Floats[3][row+1];
      if (//(generate_points_grid->Cells[row][0].Length() == 0)
          (!CORN::is_approximately<float32>(latitude_dec_deg,0.0,0.00001))
        &&(!CORN::is_approximately<float32>(longitude_dec_deg,0.0,0.00001)))
      {
         interpolate_options->geolocation.set_station_name(generate_points_grid->Cells[4][row+1].c_str());
         interpolate_options->geolocation.set_station_ID_code(generate_points_grid->Cells[0][row+1].c_str());
         interpolate_options->geolocation.set_latitude_dec_deg_32(latitude_dec_deg);
         interpolate_options->geolocation.set_longitude_dec_deg_32(longitude_dec_deg);
         interpolate_options->geolocation.set_elevation_meter(elevation_m);
         setup_target_UED_filename_for_point();
         //100926 We now store geolocation in the options file and use setup_target_UED_filename_for_point().
         //100926Smart_file_name point_UED_filename(generate_points_grid->Cells[row][0].c_str());
         //100926point_UED_filename.set_path(edit_target_directory->Text.c_str());
         //100926UED_database ued_file(point_UED_filename.c_str(),false);
/*
         interpolate_options->geolocation.set_station_name(generate_points_grid->Cells[row][4].c_str());
         interpolate_options->geolocation.set_station_ID_code(generate_points_grid->Cells[row][0].c_str());
         interpolate_options->geolocation.set_latitude_dec_deg_32(latitude_dec_deg);
         interpolate_options->geolocation.set_longitude_dec_deg_32(longitude_dec_deg);
         interpolate_options->geolocation.set_elevation_meter(elevation_m);
*/
         //100926 We now store geolocation in the options file and
         //interpolator composes the geolocation
         //         UED_geolocation_record *new_geolocation = new UED_geolocation_record(interpolation_options->geolocation);
         //         ued_file.take_geolocation_record(new_geolocation);

         points_interpolated += generate_at_geocoordinate_interpolate(false);
      };
   };
//   if (any_IDs_empty)
//      Application->MessageBox("ID's are required, no UED files were created for rows missing the ID","ID(s) blank",MB_OK);
   return points_interpolated > 0;
};
//______________________________________________________________________________
bool TUED_spatial_interpolator_form::generate_from_dBase_table_interpolate()
{
   Data_source_dBase table_DS(interpolate_options->points_dbf_filename.c_str(),std::ios_base::out);
//   table_DS.initialize();
   int points_interpolated = 0;
   progress_bar->Visible = true;
   progress_bar->Min = 0;
   progress_bar->Max = table_DS.get_record_count();
   progress_bar->Smooth = true;

   for (bool at_eof = !table_DS.goto_BOF()
       ;!at_eof
       ;at_eof = !table_DS.goto_next())
   {  // for each entry in the table
      interpolate_options->reading_points_table = true;
      interpolate_options->structure_defined = false;
      table_DS.get(*interpolate_options);
      interpolate_options->reading_points_table = false;
      interpolate_options->structure_defined = false;
      if ((!CORN::is_approximately<float32>(interpolate_options->geolocation.get_latitude_dec_deg(),0.0,0.00001))
        &&(!CORN::is_approximately<float32>(interpolate_options->geolocation.get_longitude_dec_deg(),0.0,0.00001)))
      {
         setup_target_UED_filename_for_point();
         points_interpolated += generate_at_geocoordinate_interpolate(false);
      };
      progress_bar->StepIt();
   };
   progress_bar->Visible = false;
   return points_interpolated > 0;
};
//______________________________________________________________________________
void __fastcall TUED_spatial_interpolator_form::filenameedit_points_tableChange
(TObject *Sender)
{
   if (!interpolate_options) return;  // not yet loaded parameters
   interpolate_options->points_dbf_filename.set_wstr(filenameedit_points_table->Text.c_str());
   if
   #ifdef USE_OS_FS
      (CORN::OS::file_system_engine.exists(interpolate_options->points_dbf_filename))
   #else
      (interpolate_options->points_dbf_filename.exists())
   #endif
   {
      if (points_dbf_actual_fields) delete points_dbf_actual_fields;
      points_dbf_actual_fields = new Text_list(0);
      Data_source_dBase points_dbf (interpolate_options->points_dbf_filename.c_str(),std::ios_base::in);
      points_dbf.initialize();  // need to initialize because we are only getting the fields.
      FOR_EACH_IN(act_field,Association,points_dbf.actual_fields,each_act_field)
      {  points_dbf_actual_fields->append(new Text_list::Item(act_field->get_variable()/*180820 get_key()*/));
      } FOR_EACH_END(each_act_field);
      {   // points DBF    //100926
         combobox_latitude_field ->bind_to(&(interpolate_options->points_table_latitude_field_name)   ,points_dbf_actual_fields _NO_HELP_YET);
         combobox_longitude_field->bind_to(&(interpolate_options->points_table_longitude_field_name)  ,points_dbf_actual_fields _NO_HELP_YET);
         combobox_elevation_field->bind_to(&(interpolate_options->points_table_elevation_field_name)  ,points_dbf_actual_fields _NO_HELP_YET);
         combobox_point_ID_field ->bind_to(&(interpolate_options->points_table_ID_field_name)         ,points_dbf_actual_fields _NO_HELP_YET);

         combobox_latitude_field ->Update();
         combobox_longitude_field->Update();
         combobox_elevation_field->Update();
         combobox_point_ID_field ->Update();
      };

//obs      point_ID_combobox->Update();
   };

}
//______________________________________________________________________________

void TUED_spatial_interpolator_form::update_between_ID()
{
#ifdef USE_OS_FS
   std::wstring first_ID  = between_UED_1.get_name();
   std::wstring second_ID = between_UED_2.get_name();
   std::wstring between(first_ID);
   between.append(L"_");
   between.append(second_ID);
   edit_single_target_name->Text = between.c_str();
#else
   Ustring first_ID  = between_UED_1.get_name(false);
   Ustring second_ID = between_UED_2.get_name(false);
   Ustring between(first_ID);
   between.append("_");
   between.append(second_ID);
   edit_single_target_name->Text = between.c_str();

#endif
};
//______________________________________________________________________________
void __fastcall TUED_spatial_interpolator_form::between_location_update(TObject *Sender)
{
#ifdef USE_OS_FS
   between_UED_1.set_wstr(edit_between_1->Text.c_str());
   between_UED_2.set_wstr(edit_between_2->Text.c_str());
   if (   CORN::OS::file_system_engine.exists(between_UED_1)
       && CORN::OS::file_system_engine.exists(between_UED_2))
#else
   between_UED_1.set(edit_between_1->Text.c_str());
   between_UED_2.set(edit_between_2->Text.c_str());
   if (   between_UED_1.exists()
       && between_UED_2.exists()
      )
#endif
   {
      UED_database between_station1(between_UED_1.c_str(),std::ios_base::in  /*read only true*/);  //130312
      UED_database between_station2(between_UED_2.c_str(),std::ios_base::in  /*read only true*/);  //130312

      UED_geolocation_record  *geoloc1 = between_station1.get_geolocation_record();
      if (!geoloc1) Application->MessageBox(_TEXT("The first station UED database file does not have geolocation information"),_TEXT("Geolocation data required"),MB_OK);
      UED_geolocation_record  *geoloc2 = between_station2.get_geolocation_record();
      if (!geoloc2) Application->MessageBox(_TEXT("The second station UED database file does not have geolocation information"),_TEXT("Geolocation data required"),MB_OK);

      if (geoloc1 && geoloc2)
      {
         if (!edit_single_target_name->Text.Length())
           update_between_ID(); // The user may have deleted the ID value (for whatever reason).
         float64 between_latitude
         =  ( geoloc1->get_latitude_dec_deg_32()
            + geoloc2->get_latitude_dec_deg_32()) / 2.0;
         float64 between_longitude
         =  ( geoloc1->get_longitude_dec_deg_32()
            + geoloc2->get_longitude_dec_deg_32()) / 2.0;

         std::string midpoint_description("Midpoint between:");
         #ifdef USE_OS_FS
         CORN::append_wstring_to_string(between_UED_1.get_name(),midpoint_description);
         midpoint_description.append(" and ");
         CORN::append_wstring_to_string(between_UED_2.get_name(),midpoint_description);
         #else
         midpoint_description.append(between_UED_1.get_name(false));
         midpoint_description.append(" and ");
         midpoint_description.append(between_UED_2.get_name(false));
         #endif
         interpolate_options->geolocation.set_station_name(midpoint_description);
         interpolate_options->geolocation.set_station_ID_code(midpoint_description.c_str());
         interpolate_options->geolocation.set_latitude_dec_deg_32(between_latitude);
         interpolate_options->geolocation.set_longitude_dec_deg_32(between_longitude);
         geoloc_form->Update();
      };
      //100924 groupbox_single_geolocation->Visible = true;
   };
}
//______________________________________________________________________________
void TUED_spatial_interpolator_form::handle_help_buttonClick()
{
   #ifdef USE_OS_FS
   CORN::OS_FS::Program_directory this_program_directory(ParamStr(0).c_str());
   CORN::OS::File_name_logical manual_file(this_program_directory.Documentation().manual(),"UED_spatial_interpolator.htm");
   CORN::OS::file_system_engine.view_file(manual_file);
   /* NYI
   manual_file.prepend(this_program_path);
   */
   #else
   CORN::File_name         this_program(ParamStr(0).c_str());
   CORN::Directory_name    this_program_path;
   this_program.get_path(this_program_path);
   CORN::Smart_file_name   manual_file("\\manual\\UED_spatial_interpolator.htm");
   manual_file.prepend(this_program_path);
   #endif
}
//______________________________________________________________________________
/*
void __fastcall TUED_spatial_interpolator_form::label_check_noneClick(TObject *Sender)
{  interpolate_options->selected_elements = 0x0;
   checklistbox_selected_elements->Update();
}
//______________________________________________________________________________
void __fastcall TUED_spatial_interpolator_form::label_check_allClick(TObject *Sender)
{  interpolate_options->selected_elements = 0xFFFFFFFF;
   checklistbox_selected_elements->Update();
}
//______________________________________________________________________________
void __fastcall TUED_spatial_interpolator_form::edit_target_directoryChange(TObject *Sender)
{
   interpolate_options->target_directory.assign(edit_target_directory->Text.c_str());
   target_UED_files_check_listbox->Directory = edit_target_directory->Text;
}
//______________________________________________________________________________
void __fastcall TUED_spatial_interpolator_form::edit_source_directoryChange(TObject *Sender)
{
   interpolate_options->source_directory.assign(edit_source_directory->Text.c_str());
}
//______________________________________________________________________________
void __fastcall TUED_spatial_interpolator_form::radiogroup_source_modeClick(TObject *Sender)
{
   edit_source_directory ->Visible = interpolate_options->source_mode == 0;
   groupbox_source_UED_files->Visible = interpolate_options->source_mode == 1;
}
//______________________________________________________________________________
*/
