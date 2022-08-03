#ifndef CROPCANOPYGROWTHCLASS_H
#define CROPCANOPYGROWTHCLASS_H
#include "cropinputclass.h"
#include "cropstateclass.h"
#include "control/clssimulation.h"


class clsSimulation;
class CropInputClass;
class CropStateClass;
class CropCanopyGrowthClass
{
    bool First;
    double Maximum_Canopy_Cover_Reached;
    double Total_Canopy_Cover_To_Lose;
    double Yesterday_Potential_Canopy_Expansion;
    double Canopy_Senescence_Rate;
    double CalculateCover(double Cumulative_Thermal_Time, clsSimulation &Simulation/*150601 ,CropInputClass &CropParametersRef*/);
public:
    //adding references
    CropInputClass *pCropParameters;                                             //150601
    CropStateClass &CropStateRef;
public:
    CropCanopyGrowthClass(CropStateClass& _CropStateRef);
    void DetermineUnstressedCover(clsSimulation &Simulation);
    void DetermineActualCover(/*150601 CropInputClass &CropParametersRef*/);
    double calc_leaf_green_area_index(std::string GAI_or_LAI);
    void setFirst(bool b) {First = b;};
    bool getFirst() {return First;};
};

#endif // CROPCANOPYGROWTHCLASS_H
