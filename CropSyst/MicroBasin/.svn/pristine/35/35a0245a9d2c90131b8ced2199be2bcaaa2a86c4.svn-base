#include "managescheduleclass.h"
#include "parameters/organicresidueparameterclass.h"
#include "util/pubtools.h"
#include "string"
#include <sstream>
#include <iostream>
#include <fstream>
//______________________________________________________________________________
BiomassToResidueAtHarvestClass::BiomassToResidueAtHarvestClass() {}

IrrigationEventClass::IrrigationEventClass()
:Irrigation_Amount(0.0)
,Irrigation_NO3(0.0)
,Irrigation_NH4(0.0)
,b_matched_year(false)
{
}
//______________________________________________________________________________
FertilizationEventClass::FertilizationEventClass()
:Fertilization_Total_Amount(0.0)
,Fertilization_NO3_N(0.0)
,Fertilization_NH4_N(0.0)
,b_matched_year(false)
,Fertilization_Source(-9999)
,Fertilization_Form(-9999)
,Fertilization_Method(-9999)
{
}
//_150611_______________________________________________________________________
bool FertilizationEventClass::Is_Valid_Event()
{
    if (Fertilization_Total_Amount  >= 0.0  &&
        Fertilization_NO3_N         >= 0.0  &&
        Fertilization_NH4_N         >= 0.0  &&
        Fertilization_Source        >= 1    &&
        Fertilization_Source        <= 3    &&
        Fertilization_Form          >= 1    &&
        Fertilization_Form          <= 2    &&
        Fertilization_Method        >= 1    &&
        Fertilization_Method        <= 2)
        return true;
    else
        return false;
}
//______________________________________________________________________________
ManureEventClass::ManureEventClass()
:Manure_Amount(0.0)
,b_matched_year(false)
,Manure_Application_Method(-9999)
{
}
//_150611 LML___________________________________________________________________
bool ManureEventClass::Is_Valid_Event()
{
    return Manure_Amount >= 0.0             &&
           Manure_Application_Method >= 1   &&
           Manure_Application_Method <= 2;
}
//______________________________________________________________________________
TillageEventClass::TillageEventClass()
:b_matched_year(false)
,year(-9999)
,doy(-9999)
,Tillage_Label("")
,Surface_Residue_Fraction_Remaining_On_Soil_Surface(-9999.0)
,Fraction_Standing_Residue_Flatenned_To_Soil_Surface(-9999.0)
,Depth_Soil_Disturbance_m(-9999.0)
,Type_Of_Disturbance(-9999)
,Soil_Mixing_Fraction(-9999.0)
,Tillage_Soil_Disturbance_Rating(-9999.0)
{}
//_150611_______________________________________________________________________
bool TillageEventClass::Is_Valid_Event()
{
    if (Type_Of_Disturbance             >= 1    &&
        Type_Of_Disturbance             <= 4    &&
        Soil_Mixing_Fraction            >= 0.0  &&
        Soil_Mixing_Fraction            <= 1.0  &&
        Tillage_Soil_Disturbance_Rating >= 0    &&
        Tillage_Soil_Disturbance_Rating <= 30)
        return true;
    else
        return false;
}
//______________________________________________________________________________
ManageScheduleClass::ManageScheduleClass(/*LML 140827 AllControlClass &_ControlRef*/)
    /*LML 140827:ControlRef(_ControlRef)*/
//:Irrig_Number(0) //2000;
//,Fert_Number(0) //2000;
//,Manure_Event_Number(0)//60;
//,Tillage_Event_Number(0)//60;
//,Harvest_Event_Number(5)//5;
{
    //parrIrrigation_Event = new IrrigationEventClass[2000];
    //parrFertilization_Event = new FertilizationEventClass[2000];
    //parrManure_Event = new ManureEventClass[60];
    //parrTillage_Event = new TillageEventClass[60];
    //parrBiomass_To_Residue_At_Harvest = new BiomassToResidueAtHarvestClass[5];
}
//______________________________________________________________________________
ManageScheduleClass::~ManageScheduleClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~ManageScheduleClass:"<<std::endl;
#endif
    //delete[] parrIrrigation_Event;
    //delete[] parrFertilization_Event;
    //delete[] parrManure_Event;
    //delete[] parrTillage_Event;
    //delete[] parrBiomass_To_Residue_At_Harvest;
#ifdef Destruct_Monitor
    std::cout<<"~ManageScheduleClass done."<<std::endl;
#endif
}
//______________________________________________________________________________
std::string ManageScheduleClass::getManagementFileName(AllControlClass &ControlRef)
{
   #ifdef LIU_ENGINE
    std::ostringstream ss("");
    ss<<ControlRef.management_prefix_name<<Management_Name<<ControlRef.management_suffix_name;
    return ss.str();
   #else
   std::string prefix_management_name;
   CORN::wstring_to_string(ControlRef.management_filename.get_name(),prefix_management_name);
   prefix_management_name.append(Management_Name);
   CORN::OS::File_name_concrete management_filename
      (ControlRef.management_filename.get_parent_directory_name_qualified()
      ,prefix_management_name
      ,ControlRef.management_filename.get_extension());
   std::string result(management_filename.c_str());
   return result;
   #endif
}
//______________________________________________________________________________
void ManageScheduleClass::ReadManagementEvents(AllControlClass &ControlRef,int inner_id)
{
    //M.Liu Jan. 21, 2014
    //150526 inner_id is the index in ControlRef management array
    char errormessage[200];
    std::string filename = getManagementFileName(ControlRef);
    int iIrrig_Number(-1);
    int iFert_Number(-1);
    int iManure_Event_Number(-1);
    int iTillage_Event_Number(-1);
    double Standing_Stubble_Mass_Fraction_of_Unharvested_Biomass(0.0);
    double Surface_Residue_Mass_Fraction_of_Unharvested_Biomass(0.0);
    parrFertilization_Event.clear();
    parrIrrigation_Event.clear();
    parrManure_Event.clear();
    parrTillage_Event.clear();
    std::ifstream ifile(filename.c_str());
    if (ifile.is_open()) {
        std::string nameline("");
        while (std::getline(ifile,nameline)) {
            std::string record_key = getKeyWord(nameline);
            std::string dataline("");
            std::stringstream ss("");
            if (!record_key.empty()) {
                //read the data line
                std::getline(ifile,dataline);
                ss.clear();
                ss.str(dataline);
                if (dataline.empty() || !getKeyWord(dataline).empty()) {
                    sprintf(errormessage,"Warning: %s has no data!",record_key.c_str());
                    nrerror(errormessage);
                } else {
                    if (record_key.compare("Fertilization")     == 0 ||
                        record_key.compare("AutoFertilization") == 0 ||
                        record_key.compare("Fertigation")       == 0) {
                        iFert_Number++;
                        FertilizationEventClass temp;
                        temp.set_inner_id(inner_id);                             //150526
                        ss>>temp.year
                            >>temp.doy
                            >>temp.Fertilization_Total_Amount
                            >>temp.Fertilization_NO3_N
                            >>temp.Fertilization_NH4_N
                            >>temp.Fertilization_Source
                            >>temp.Fertilization_Form
                            >>temp.Fertilization_Method;
                        assert(temp.Is_Valid_Event());                           //150611LML
                        if (record_key.compare("Fertilization") == 0) {
                          temp.Fertilization_Type = SCHEDULED_FERTILIZATION;
                        }
                        else if (record_key.compare("AutoFertilization") == 0) {
                          temp.Fertilization_Type = AUTO_FERTILIZATION;
                        }
                        else if (record_key.compare("Fertigation") == 0) {       //150520
                          temp.Fertilization_Type           = SCHEDULED_FERTILIZATION;
                          temp.Fertilization_Total_Amount   = temp.Fertilization_NO3_N + temp.Fertilization_NH4_N;
                          iIrrig_Number++;
                          IrrigationEventClass temp_irrig;
                          temp_irrig.year               = temp.year;
                          temp_irrig.doy                = temp.doy;
                          temp_irrig.Irrigation_Amount  = temp.Fertilization_Total_Amount;
                          temp_irrig.Irrigation_NH4     = temp.Fertilization_NH4_N;
                          temp_irrig.Irrigation_NO3     = temp.Fertilization_NO3_N;
                          parrIrrigation_Event.push_back(temp_irrig);
                          temp.Fertilization_Total_Amount = temp.Fertilization_NO3_N + temp.Fertilization_NH4_N;
                        }
                        parrFertilization_Event.push_back(temp);
                    }
                    else if (record_key.compare("Irrigation") == 0) {
                        iIrrig_Number++;
                        IrrigationEventClass temp;
                        temp.set_inner_id(inner_id);                             //150526
                        ss>>temp.year
                            >>temp.doy
                            >>temp.Irrigation_Amount
                            >>temp.Irrigation_NO3
                            >>temp.Irrigation_NH4;
                        assert(temp.Is_Valid_Event());
                        parrIrrigation_Event.push_back(temp);
                    }
                    else if (record_key.compare("Manure") == 0) {
                        iManure_Event_Number++;
                        ManureEventClass temp;
                        temp.set_inner_id(inner_id);                             //150526
                        ss>>temp.Manure_Event_Label
                            >>temp.year
                            >>temp.doy
                            >>temp.Manure_Amount
                            >>temp.Manure_Application_Method;
                        assert(temp.Is_Valid_Event());
                        int index_manure = ControlRef.pOrganic_Residue_Parameters->FindManureParameterIndex(
                            temp.Manure_Event_Label);
                        
                        ManureParameterClass *pTempManureParameter = &(ControlRef.pOrganic_Residue_Parameters->parrManure_Parameter[index_manure]);
                        if (index_manure != -9999) {
                            temp.Manure_Fast_Cycling_Fraction =
                                    pTempManureParameter->Fraction_Of_Fast_Cycling_Biomass;
                            temp.Manure_Slow_Cycling_Fraction =
                                    pTempManureParameter->Fraction_Of_Slow_Cycling_Biomass;
                            temp.Manure_Lignified_Fraction =
                                    pTempManureParameter->Fraction_Of_Lignified_Biomass;
                            temp.Manure_Fast_Cycling_CN =
                                    pTempManureParameter->Fast_Cycling_Residue_Default_CN_Ratio;
                            temp.Manure_Slow_Cycling_CN =
                                    pTempManureParameter->Slow_Cycling_Residue_Default_CN_Ratio;
                            temp.Manure_Lignified_CN =
                                    pTempManureParameter->Lignified_Residue_Default_CN_Ratio;
                            temp.Manure_Carbon_Fraction =
                                    pTempManureParameter->Residue_Carbon_Fraction;
                            temp.Manure_Ammonium_N =
                                    pTempManureParameter->Ammonium_Content;
                            temp.Manure_Water =
                                    pTempManureParameter->Water_Content;
                            temp.Manure_Area_To_Mass_Ratio =
                                    pTempManureParameter->Area_To_Mass_Ratio_As_After_Application;
                        }
                        parrManure_Event.push_back(temp);
                    }
                    else if (record_key.compare("Tillage") == 0) {
                        iTillage_Event_Number++;
                        TillageEventClass temp;
                        temp.set_inner_id(inner_id);                             //150526
                        ss>>temp.Tillage_Label
                            >>temp.year
                            >>temp.doy
                            >>temp.Surface_Residue_Fraction_Remaining_On_Soil_Surface
                            >>temp.Fraction_Standing_Residue_Flatenned_To_Soil_Surface
                            >>temp.Depth_Soil_Disturbance_m
                            >>temp.Type_Of_Disturbance
                            >>temp.Soil_Mixing_Fraction
                            >>temp.Tillage_Soil_Disturbance_Rating;
                        assert(temp.Is_Valid_Event());
                        parrTillage_Event.push_back(temp);
                    }
                    else if (record_key.compare("Harvest") == 0) {
                        //iTillage_Event_Number++;
                        ss>>Standing_Stubble_Mass_Fraction_of_Unharvested_Biomass
                            >>Surface_Residue_Mass_Fraction_of_Unharvested_Biomass;
                    } else {
                        sprintf(errormessage,"Warning: Cann't find keyword %s",record_key.c_str());
                        nrerror(errormessage);
                    }
                }
            }
        }
        #ifdef LIU_DEBUG
        std::cout<<"Management file:"<<filename<<" is read."<<std::endl;
        #endif
    } else {
        sprintf(errormessage,"Cann't open management file %s",filename.c_str());
        nrerror(errormessage);
    }
    ifile.close();
    //Irrig_Number = iIrrig_Number + 1;
    //Fert_Number = iFert_Number + 1;
    //Manure_Event_Number = iManure_Event_Number + 1;
    //Tillage_Event_Number = iTillage_Event_Number + 1;
    Harvest_Event_Number = 1/*LML 140827 assume only one harvest for each management 5*/;
    parrBiomass_To_Residue_At_Harvest.resize(Harvest_Event_Number);
    for (int i = 0; i < Harvest_Event_Number; i++) {
        //LML 140827 parrBiomass_To_Residue_At_Harvest[i].year = Planting_Year;
        //LML 140827 parrBiomass_To_Residue_At_Harvest[i].doy = Planting_DOY;
        parrBiomass_To_Residue_At_Harvest[i].Standing_Fraction = 
            Standing_Stubble_Mass_Fraction_of_Unharvested_Biomass;
        parrBiomass_To_Residue_At_Harvest[i].Surface_Fraction = 
            Surface_Residue_Mass_Fraction_of_Unharvested_Biomass;

        parrBiomass_To_Residue_At_Harvest[i].set_inner_id(inner_id);             //150526
    }
}
//_150522 ______________________________________________________________________
void ManageScheduleClass::Clear_All_Events()
{
    parrIrrigation_Event.clear();
    parrFertilization_Event.clear();
    parrManure_Event.clear();
    parrTillage_Event.clear();
    parrBiomass_To_Residue_At_Harvest.clear();
}
//_150522 ______________________________________________________________________
void ManageScheduleClass::AppendFromOtherSchedule(ManageScheduleClass *from)
{
    for (int i = 0; i < from->parrIrrigation_Event.size(); i++) {
        parrIrrigation_Event.push_back(from->parrIrrigation_Event[i]);
    }
    for (int i = 0; i < from->parrFertilization_Event.size(); i++) {
        parrFertilization_Event.push_back(from->parrFertilization_Event[i]);
    }
    for (int i = 0; i < from->parrManure_Event.size(); i++) {
        parrManure_Event.push_back(from->parrManure_Event[i]);
    }
    for (int i = 0; i < from->parrTillage_Event.size(); i++) {
        parrTillage_Event.push_back(from->parrTillage_Event[i]);
    }
    for (int i = 0; i < from->parrBiomass_To_Residue_At_Harvest.size(); i++) {
        parrBiomass_To_Residue_At_Harvest.push_back(from->parrBiomass_To_Residue_At_Harvest[i]);
    }
}
//______________________________________________________________________________

