// This is obsolete, these methods have be moved to  Tframe_scenario_output 171206


// The methods in this file are common to both Tform_CS_context (CS_explorer)
// and  Toutput_manager_advanced_form.
// This file is included by both of these forms which will #define the macro
// FORM_SCENRIO_OUTPUT_CONTEXT  as the respective form.

// Do not add this file to an IDE project or makefile, it must be #included.

//______________________________________________________________________________

void FORM_SCENRIO_OUTPUT_CONTEXT::update_list_of_pending_reports()
{  listbox_pending_reports->Clear();

   if (output_options)
   {
      FOR_EACH_IN(conversion,CropSyst::Scenario_output_options::Conversion,output_options->conversions,each_conversion)
      {  if (report_out_of_sync(conversion))
            listbox_pending_reports->Items->Append(conversion->get_key());
      } FOR_EACH_END(each_conversion)
      listbox_pending_reports->Update();
   }

//   else Application->MessageBox("Output options have not been loaded: This is a programming error","Output options not loaded",MB_OK);
};
//_____________________________________________update_list_of_pending_reports__/

bool FORM_SCENRIO_OUTPUT_CONTEXT::report_out_of_sync
(const CropSyst::Scenario_output_options::Conversion *conversion)
{
   CORN::datetime64 ued_datetime = CORN::OS::file_system_engine.get_modification_date_time(conversion->ued_filename);
   CORN::datetime64 xxx_datetime = CORN::OS::file_system_engine.get_modification_date_time(conversion->xxx_filename);
   CORN::datetime64 tdf_datetime = CORN::OS::file_system_engine.get_modification_date_time(conversion->tdf_filename);
   CORN::OS::File_name_concrete XXX_filename(scenario_output_directory,conversion->xxx_filename.w_str());
   bool out_of_sync = ! CORN::OS::file_system_engine.exists(XXX_filename)
          || (ued_datetime > xxx_datetime)
          || (tdf_datetime > xxx_datetime);

   return out_of_sync;
};
//_________________________________________________________report_out_of_sync__/

