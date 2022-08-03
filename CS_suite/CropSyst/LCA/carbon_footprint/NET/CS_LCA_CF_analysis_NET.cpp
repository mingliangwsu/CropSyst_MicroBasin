
#include "CS_LCA_CF_analysis_NET.h"
#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;

//#include "corn/dynamic_array/dynamic_array_T.h"
#include "UED/library/database_file.h"
#include "UED/library/datasetrec.h"
#include "corn/datetime/date.h"
#include "csvc.h"
#include "corn/measure/measures.h"
#include "chemistry/stoichiometry_composition.h"
#include <stdlib.h>

namespace CropSyst
{
namespace LCA_Carbon_footprint
{
//_____________________________________________________________________________
Analysis::Analysis(System::String ^scenario_directory_name_SysString)
: scenario_directory(0)
{
   std::wstring scenario_directory_name_wstring = marshal_as<std::wstring>(scenario_directory_name_SysString);
   CORN_Directory_name_instance scenario_directory_name(scenario_directory_name_wstring);
   scenario_directory = new CropSyst::Scenario_directory(scenario_directory_name);
      /** The name of CropSyst scenario directory.
      The directory must contain the CropSyst run Output directory
      containing the CropSyst output schedule and annual UED files.
      **/
};
//_____________________________________________________________________________
Analysis::~Analysis()
{
   delete scenario_directory;
};
//_____________________________________________________________________________
unsigned int Analysis::scan(IReceiver^ receiver)
{
   unsigned int emit_count = 0;
/*
   int32 earliest_SOM_profile_date32(9999365); float earliest_SOM_profile_value_Mg_ha;
   int32 latest_SOM_profile_date32(0000001);   float latest_SOM_profile_value_Mg_ha;
*/

   float32 annual_N2O_N_denitr_kg_m2[200]; nat16 N2O_denitr_count = 0;
   float32 annual_N2O_N_nitr_kg_m2  [200]; nat16 N2O_nitr_count = 0;
   Year N2O_first_year = 0;

   UED::Database_file_indexed output_UED_file(scenario_directory->CS_output().annual_UED().c_str(),true);

   for (UED::Binary_data_record *data_rec = output_UED_file.goto_next_data_record()
             ;data_rec
             ;data_rec = output_UED_file.goto_next_data_record())
   {  UED_variable_code variable_code(data_rec->get_variable_code());
      CORN::Quality quality;
      nat32 years =  data_rec->data_values_get_count();
      CORN::Date initial_date;
      initial_date.set_datetime64(data_rec->get_date_time_for_index(0));
      if (variable_code == CSVC_soil_C_SOM_profile)
      {  // The initial and final values are used for carbon foot print calculation
         CORN::Date final_date(data_rec->get_date_time_for_index(data_rec->data_values_get_count()));
         CORN::Quality initial_quality;
         float32 initial_soil_C_SOM_profile_kg_m2 = data_rec->get_at(0,initial_quality); // get_value(quality,initial_date_DT64);
         float initial_soil_C_SOM_profile_Mg_ha =  kg_to_mg(per_m2_to_per_ha(initial_soil_C_SOM_profile_kg_m2));
         CORN::Quality final_quality;
         nat32 final_year_index = years - 1;                                        
         float32 final_soil_C_SOM_profile_kg_m2 =  data_rec->get_at(final_year_index,final_quality);  //data_rec->get_value(quality,final_date_DT64);
         float final_soil_C_SOM_profile_Mg_ha = kg_to_mg(per_m2_to_per_ha(final_soil_C_SOM_profile_kg_m2));
         receiver->know_SOM_initial_final_CO2_Mg_ha
            (initial_date.get_year(), initial_soil_C_SOM_profile_Mg_ha
            ,final_date.get_year(),final_soil_C_SOM_profile_Mg_ha);
         emit_count++;
      }; // if variable code
   
      //nat8 rot_index = 0;
      for (nat16 year_index = 0; year_index < years; year_index++)
      {  Year year = initial_date.get_year() + year_index;
         CORN::Quality initial_quality;
         float32 value = data_rec->get_at(year_index,initial_quality); 
         //nat8 rot_index = year_index % years_in_rotation; // number of years in rotation (warning we need to get the number of years in rotation)
         //take_variable_value(year_index,rot_index,variable_code,value,data_rec->units_code,cell_sheet_row);
         switch (variable_code)
         {  case CSVC_soil_N_N2O_loss_denitrification_time_step_sum:
            {  N2O_first_year = initial_date.get_year();
               annual_N2O_N_denitr_kg_m2[N2O_denitr_count++] = value;
               //N2O_N_denitr_kg_m2.append(value);
            } break;
            case CSVC_soil_N_N2O_loss_nitrification_time_step_sum :
            {  N2O_first_year = initial_date.get_year();
               annual_N2O_N_nitr_kg_m2[N2O_nitr_count++] = value;
               //N2O_N_nitr_kg_m2.append(value);
            } break;;
         } // switch
      }; // for year_index
   }; //each data record
   int32 N2O_years = std::max<int32>
         (N2O_denitr_count,N2O_nitr_count);
         //(N2O_N_denitr_kg_m2.get_count(),N2O_N_nitr_kg_m2.get_count());
   for (nat16 year_index = 0; year_index < N2O_years; year_index++)
   {
      Year N2O_year = N2O_first_year;
      float N2O_N_kg_m2 
            = annual_N2O_N_denitr_kg_m2[year_index] // N2O_N_denitr_kg_m2.get(year_index);
            + annual_N2O_N_nitr_kg_m2  [year_index]; //N2O_N_nitr_kg_m2.get(year_index);
      float N2O_N_Mg_ha = kg_to_mg(per_m2_to_per_ha(N2O_N_kg_m2 ));
      float N2O_Mg_ha = calc_N20_given_N_mass(N2O_N_Mg_ha);
      float N2O_CO2e_Mg_ha = 298.0 * N2O_Mg_ha;
      receiver->know_N2O_CO2e_Mg_ha(N2O_year, N2O_CO2e_Mg_ha);      
      emit_count++;
      N2O_year ++;
   };
   emit_count += scan_schedule(receiver);

   return emit_count;
};
//_____________________________________________________________________________
struct Event_particulars
{
   int         date;
   std::string ID;
   std::string type;
   std::string NRCS_field_op;
   std::string operation_filename;
   float       amount;
   std::string amount_units;
public: 
   inline void clear()
   {
      date = 0;
      ID.clear();
      type.clear();
      NRCS_field_op.clear();
      operation_filename.clear();
      amount = 0;
      amount_units.clear();
   };

};
//_____________________________________________________________________________
bool Analysis::emit_event(IReceiver^ receiver,const Event_particulars &event_particulars)
{
   System::String ^ID = gcnew System::String(event_particulars.ID.c_str());
   System::String ^type = gcnew System::String(event_particulars.type.c_str());
   System::String ^NRCS_field_op = gcnew System::String(event_particulars.NRCS_field_op.c_str());
   System::String ^operation_filename = gcnew System::String(event_particulars.operation_filename.c_str());
   System::String ^amount_units = gcnew System::String(event_particulars.amount_units.c_str());
   receiver->know_event(event_particulars.date,ID,type,NRCS_field_op,operation_filename,event_particulars.amount,amount_units);
   return true;
};
//_____________________________________________________________________________
unsigned int Analysis::scan_schedule(IReceiver^ receiver)
{
   nat32 emit_count = 0;

   std::string buffer;
   Event_particulars event_particulars;
   CORN_File_name_instance schedule_txt(scenario_directory->CS_output(),"schedule.txt");
   std::ifstream schedule_strm(schedule_txt.c_str());
   std::string status;
   while (!schedule_strm.eof())
   {
      getline(schedule_strm,buffer);
      if (buffer.length())
      {
         size_t right_bracket_pos = buffer.find("]");
         if ((buffer.c_str()[0] == '[') && (right_bracket_pos != std::string::npos))          
         {
            if (status=="complete")
               emit_count += emit_event(receiver,event_particulars);
            event_particulars.clear();
            status.clear();
         } else
         {  size_t equal_pos = buffer.find("=");
            if (equal_pos != std::string::npos)
            {  std::string key(buffer,0,equal_pos);
               std::string value(buffer,equal_pos+1,buffer.length());
               if       (key == "ID")                 event_particulars.ID = value;
               else if  (key == "date")            
               {  CORN::Date date_value(value.c_str(),D_YD,D_YYYY|D_lead_zero, 0 ,false);
                  event_particulars.date = date_value.get_date32();
               }
               else if (key == "type")                event_particulars.type = value;
               else if (key == "NRCS_field_op")       event_particulars.NRCS_field_op = value;
               else if (key == "operation_filename")  event_particulars.operation_filename = value;
               else if (key == "amount_units")        event_particulars.amount_units = value;
               else if (key == "amount")              event_particulars.amount = (float)atof(value.c_str());
               else if (key == "status")              status = value;
            }; // if variable value line
         }; // if section line
      }; // if buffer not empty
   }; // while not eof

   return emit_count;
};
//_2012-10-25__________________________________________________________________


}; // namespace LCA_Carbon_footprint
}; // namespace CropSyst