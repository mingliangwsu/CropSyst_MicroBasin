#include "croppotentialtranspirationclass.h"
#include <math.h>

CropPotentialTranspirationClass::CropPotentialTranspirationClass(CropStateClass &_CropStateRef)
    :CropStateRef(_CropStateRef)
{
}

void CropPotentialTranspirationClass::DeterminePotentialTranspiration(bool Potential, 
  WeatherStateDailyClass &Weather, CropInputClass &CropParametersRef)
{
    double Potential_Transpiration(0.0);
    double Current_Crop_Height(0.0);
    double Unadjusted_Current_Crop_ET_Coeff_Full_Shading(0.0);
    double Current_Crop_ET_Coeff_Full_Shading(0.0);
    CropStateRef.Reference_ET = Weather.getReferenceCropET();
    CropStateRef.Cumulative_Reference_Crop_ET += CropStateRef.Reference_ET;
    double CO2_Adjustment_To_Transpiration = CropStateRef.CO2_Adjustment_To_Transpiration;
    CropStateRef.CO2_Elevated_Reference_Crop_ET = 
        Weather.getReferenceCropET() * CO2_Adjustment_To_Transpiration;
    CropStateRef.Cumulative_CO2_Elevated_Reference_Crop_ET += 
        CropStateRef.CO2_Elevated_Reference_Crop_ET;
    //Roger: new lines
    double Maximum_Crop_Height = CropParametersRef.Maximum_Crop_Height;
    double Maximum_Crop_ET_Coeff_Full_Shading = 
        CropParametersRef.Crop_ET_Coeff_100_Percent_Cover;
    double Crop_ET_Coeff_Ratio(0.0);
    if (Maximum_Crop_ET_Coeff_Full_Shading == 0) {
        Maximum_Crop_ET_Coeff_Full_Shading = CalculateFullShadingCropETCoeff(Maximum_Crop_Height);
        Crop_ET_Coeff_Ratio = 1;
    }
    else Crop_ET_Coeff_Ratio = Maximum_Crop_ET_Coeff_Full_Shading 
                               / CalculateFullShadingCropETCoeff(Maximum_Crop_Height);
    //Roger: End of new lines
    if (Potential) {
        //Crop ET coefficient: it grows from Kc=1 until reaching the maximum Kc at full canopy, assuming that any canopy,
        //no matter how sparse, will have Kc>1 if actually covering (shading) the ground completely (a reflection of roughness due to heigth)
        //Roger: The next several lines are new
        if ((CropStateRef.Potential_Fraction_Solar_Rad_Intercepted < CropParametersRef.Maximum_Canopy_Cover) &&
            (CropStateRef.Cumulative_Thermal_Time <= CropParametersRef.Thermal_Time_At_The_End_Of_Canopy_Growth)) {
            Current_Crop_Height = Maximum_Crop_Height 
                                  * CropStateRef.Potential_Fraction_Solar_Rad_Intercepted 
                                  / CropParametersRef.Maximum_Canopy_Cover;
            Max_Reached_Height_Potential_Crop = Current_Crop_Height;            
            // 'store value for use after maximum canopy growth is reached
            Unadjusted_Current_Crop_ET_Coeff_Full_Shading = 
                CalculateFullShadingCropETCoeff(Current_Crop_Height) * Crop_ET_Coeff_Ratio;     
            // 'scale to Kc user input
            //Current crop coefficient is now adjusted for current weather conditions
            Current_Crop_ET_Coeff_Full_Shading = 
                CalculateWeatherAdjustedCropETCoeff(Current_Crop_Height, 
                                                    Unadjusted_Current_Crop_ET_Coeff_Full_Shading, 
                                                    Weather);
            Max_Unadj_Crop_ET_Coeff_Potential_Crop = Unadjusted_Current_Crop_ET_Coeff_Full_Shading;         
            // 'store value for use after maximum canopy growth is reached
            // OBSOLETE: Potential_Current_ET_CropCoefficient = 1 + (CropParametersRef.CropETCoeff100PercentCover - 1) _
            //'          * (CropStateRef.PotentialFractionSolarRadiationIntercepted(DACE) / CropParametersRef.MaximumCanopyCover)
        } else {
            Current_Crop_ET_Coeff_Full_Shading = 
                CalculateWeatherAdjustedCropETCoeff(Max_Reached_Height_Potential_Crop, 
                                                    Max_Unadj_Crop_ET_Coeff_Potential_Crop, 
                                                    Weather);
        }
        //Roger: End of new lines
        CropStateRef.Potential_Current_ET_Crop_Coeff = Current_Crop_ET_Coeff_Full_Shading;
        //Calculate potential transpiration for potential crop
        Potential_Transpiration = CO2_Adjustment_To_Transpiration 
                                  * Weather.getReferenceCropET()
                                  * Current_Crop_ET_Coeff_Full_Shading
                                  * CropStateRef.Potential_Fraction_Solar_Rad_Intercepted;
        Weather.setPotentialCropPotentialTranspiration(Potential_Transpiration);
        CropStateRef.Potential_Crop_Potential_Transpiration = Potential_Transpiration;  //LML 150127
        //'    CropStateRef.CumulativePotentialCropTranspiration(DACE) = _
        //'        CropStateRef.CumulativePotentialCropTranspiration(DACE - 1) + Potential_Transpiration
    } else {       //'Actual crop
        //Crop ET coefficient: it grows from Kc=1 until reaching the maximum Kc at full canopy, assuming that any canopy,
        //no matter how sparse, will have Kc>1 if actually covering all the ground (a reflection of roughness due to heigth
        if ((CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy < CropParametersRef.Maximum_Canopy_Cover) &&
            (CropStateRef.Cumulative_Thermal_Time <= CropParametersRef.Thermal_Time_At_The_End_Of_Canopy_Growth)) {
            Current_Crop_Height = Maximum_Crop_Height 
                                  * CropStateRef.Potential_Fraction_Solar_Rad_Intercepted 
                                  / CropParametersRef.Maximum_Canopy_Cover;
            Max_Reached_Height_Actual_Crop = Current_Crop_Height;           // 'store value for use after maximum canopy growth is reached
            Unadjusted_Current_Crop_ET_Coeff_Full_Shading = 
                CalculateFullShadingCropETCoeff(Current_Crop_Height) * Crop_ET_Coeff_Ratio;     // 'scale to Kc user input
            //'Current crop coefficient is now adjusted for current weather conditions
            Current_Crop_ET_Coeff_Full_Shading = 
                CalculateWeatherAdjustedCropETCoeff(Current_Crop_Height, 
                                                    Unadjusted_Current_Crop_ET_Coeff_Full_Shading, 
                                                    Weather);
            Max_Unadj_Crop_ET_Coeff_Actual_Crop = Unadjusted_Current_Crop_ET_Coeff_Full_Shading;                // 'store value for use after maximum canopy growth is reached

        } else {
            Current_Crop_ET_Coeff_Full_Shading = 
                CalculateWeatherAdjustedCropETCoeff(Max_Reached_Height_Actual_Crop, 
                                                    Max_Unadj_Crop_ET_Coeff_Actual_Crop, 
                                                    Weather);
        }
        CropStateRef.Current_ET_Crop_Coeff = Current_Crop_ET_Coeff_Full_Shading;
        //'Calculate potential transpiration for actual crop
        double Reference_Crop_ET = CO2_Adjustment_To_Transpiration * Weather.getReferenceCropET();
        Potential_Transpiration = Reference_Crop_ET 
                                  * Current_Crop_ET_Coeff_Full_Shading 
                                  * CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy;
        /*
        std::cout<<" DOY:"<<DOY<<" Potential_Transpiration:"<<Potential_Transpiration
                <<" Reference_Crop_ET:"<<Reference_Crop_ET
                <<" Current_Crop_ET_Coeff_Full_Shading:"<<Current_Crop_ET_Coeff_Full_Shading
                <<" Fraction_Solar_Rad_Intercepted_Green_Canopy:"<<CropStateRef.Fraction_Solar_Rad_Intercepted_Green_Canopy
                <<std::endl;
                */
        Weather.setActualCropPotentialTranspiration(Potential_Transpiration);
        CropStateRef.Crop_Potential_Transpiration = Potential_Transpiration;
        CropStateRef.Cumulative_Crop_Potential_Transpiration += Potential_Transpiration;
    }
}

double CropPotentialTranspirationClass::CalculateFullShadingCropETCoeff(double Crop_Height)
{
    return 0.118 * log(Crop_Height) + 1.2428;
}

double CropPotentialTranspirationClass::CalculateWeatherAdjustedCropETCoeff(double Crop_Height,
  double Unajusted_Crop_ET_Full_Shading, WeatherStateDailyClass &Weather)
{
    double RHmin = Weather.getDailyMinimumRelativeHumidity();
    double Wind = Weather.getDailyWindSpeed();
    if (RHmin < 20) RHmin = 20;
    else if (RHmin > 80) RHmin = 80;
    if (Wind < 1) Wind = 1;
    else if (Wind > 6) Wind = 6;
    double Kc = Unajusted_Crop_ET_Full_Shading + 
                (0.04 * (Wind - 2.0) - 0.004 * (RHmin - 45.0)) * 
                pow((Crop_Height / 3.0),0.3);
    if (Kc < 1) Kc = 1;
    return Kc;
}
