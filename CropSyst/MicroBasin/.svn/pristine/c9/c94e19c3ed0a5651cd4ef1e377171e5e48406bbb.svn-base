#ifndef MANAGESCHEDULECLASS_H
#define MANAGESCHEDULECLASS_H

#ifndef CROPSYST_PROPER_MANAGEMENT
#include "control/clssimulation.h"
#include "control/allcontrolclass.h"

#define MAX_NUM_EVENTS 20

class AllControlClass;
class clsSimulation;
//_150526_______________________________________________________________________
class Management_Item
{
protected:
    int inner_management_id;                                                     //150526 Inner index for global Control management file
public:
    Management_Item() {inner_management_id = -1;};
    ~Management_Item(){};
    void set_inner_id(int id) {inner_management_id = id;};
    int get_inner_id() {return inner_management_id;};
    virtual bool Is_Valid_Event()                                           = 0; //150611
};
//______________________________________________________________________________
class BiomassToResidueAtHarvestClass
:public Management_Item
{
public:
    int year;
    int doy;
    double Standing_Fraction;
    double Surface_Fraction;

public:
    BiomassToResidueAtHarvestClass();
    virtual bool Is_Valid_Event() {return CORN::is_approximately(Standing_Fraction+Surface_Fraction,1.0);};
};
//______________________________________________________________________________
class IrrigationEventClass
:public Management_Item
{
public:
    bool b_matched_year;
    int year;
    int doy;
    double Irrigation_Amount;
    double Irrigation_NO3;  //(kg/ha)
    double Irrigation_NH4;  //(kg/ha)
public:
    IrrigationEventClass();
    virtual bool Is_Valid_Event() {return Irrigation_Amount >= 0.0 && Irrigation_NO3 >= 0.0 && Irrigation_NH4 >= 0.0;};
};
//______________________________________________________________________________
class FertilizationEventClass
:public Management_Item
{
public:
    bool b_matched_year;
    int year;
    int doy;
    double Fertilization_Total_Amount;
    double Fertilization_NO3_N;                 //(kgN/ha)
    double Fertilization_NH4_N;                 //(kgN/ha)
    int Fertilization_Source;
    int Fertilization_Form;
    int Fertilization_Method;
    Fertilization_TYPE Fertilization_Type;       //150519
public:
    FertilizationEventClass();
    virtual bool Is_Valid_Event();
};
//______________________________________________________________________________
class ManureEventClass
:public Management_Item
{
public:
    bool b_matched_year;
    int year;
    int doy;
    std::string Manure_Event_Label;
    double Manure_Amount;
    double Manure_Carbon_Fraction;
    double Manure_Ammonium_N;
    double Manure_Water;
    int Manure_Application_Method;
    double Manure_Fast_Cycling_Fraction;
    double Manure_Slow_Cycling_Fraction;
    double Manure_Lignified_Fraction;
    double Manure_Fast_Cycling_Decomposition_Rate;
    double Manure_Slow_Cycling_Decomposition_Rate;
    double Manure_Lignified_Decomposition_Rate;
    double Manure_Fast_Cycling_CN;
    double Manure_Slow_Cycling_CN;
    double Manure_Lignified_CN;
    double Manure_Area_To_Mass_Ratio;
public:
    ManureEventClass();
    virtual bool Is_Valid_Event();                                               //150611LML
};
//______________________________________________________________________________
class TillageEventClass
:public Management_Item
{
public:
    bool b_matched_year;
    int year;
    int doy;
    std::string Tillage_Label;
    double Surface_Residue_Fraction_Remaining_On_Soil_Surface;
    double Fraction_Standing_Residue_Flatenned_To_Soil_Surface;
    double Depth_Soil_Disturbance_m;
    int Type_Of_Disturbance;
    double Soil_Mixing_Fraction;
    double Tillage_Soil_Disturbance_Rating;
public:
    TillageEventClass();
    virtual bool Is_Valid_Event();                                               //150611LML
};
//______________________________________________________________________________
class ManageScheduleClass
{
private:
    std::string getManagementFileName(AllControlClass &ControlRef);
public:
    std::string Management_Name;        //LML 140827
    //int Irrig_Number;
    //int Fert_Number;
    //int Manure_Event_Number;
    //int Tillage_Event_Number;
    int Harvest_Event_Number;
public:
    std::vector<IrrigationEventClass> parrIrrigation_Event;                         //(2000, 5) As Variant ' JAVIER MARCOS: Increased array size to 20000 (was 60) to allow more events
    std::vector<FertilizationEventClass> parrFertilization_Event;                   //(2000, 8) As Variant ' JAVIER MARCOS: Increased array size to 20000 (was 60) to allow more events
    std::vector<ManureEventClass> parrManure_Event;                                 //(60, 25) As Variant
    //std::string *parrManure_Event_Label;                              //[60];     // As String
    std::vector<TillageEventClass> parrTillage_Event;                               //(60, 8);           // As Variant
    std::vector<BiomassToResidueAtHarvestClass> parrBiomass_To_Residue_At_Harvest;

    //LML 140827 AllControlClass &ControlRef;
public:
    ManageScheduleClass(/*LML 140827 AllControlClass &_ControlRef*/);
    ~ManageScheduleClass();
    void ReadManagementEvents(AllControlClass &ControlRef, int inner_id);
    void Clear_All_Events();                                                     //150522
    void AppendFromOtherSchedule(ManageScheduleClass *from);                     //150522
};
//______________________________________________________________________________
#endif // CROPSYST_PROPER_MANAGEMENT
#endif // MANAGESCHEDULECLASS_H

