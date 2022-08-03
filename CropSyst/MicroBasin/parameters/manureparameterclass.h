#ifndef MANUREPARAMETERCLASS_H
#define MANUREPARAMETERCLASS_H
#include <string>

class ManureParameterClass
{
public:
    std::string Label;
    double Fraction_Of_Fast_Cycling_Biomass;
    double Fraction_Of_Slow_Cycling_Biomass;
    double Fraction_Of_Lignified_Biomass;
    double Fast_Cycling_Residue_Default_CN_Ratio;
    double Slow_Cycling_Residue_Default_CN_Ratio;
    double Lignified_Residue_Default_CN_Ratio;
    double Residue_Carbon_Fraction;
    double Ammonium_Content;    //kg Nh3-N/kg Dry Matter
    double Water_Content;       //kg H2O/kg Dry Matter
    double Area_To_Mass_Ratio_As_After_Application;
public:
    ManureParameterClass();
};

#endif // MANUREPARAMETERCLASS_H
