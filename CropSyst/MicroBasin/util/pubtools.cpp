#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
//#include "math.h"
#include <cmath>
#include "constants.h"
#include <cfloat>
#include <time.h>
#include "pubtools.h"
#ifdef __BCPLUSPLUS__
#  include <limits>
#endif
#include <cmath>            //fabs problem
//______________________________________________________________________________
void nrerror(const char* error_text)
/* Numerical Recipes standard error handler */
{
    std::cerr<<"Model run-time error...\n";
    std::cerr<<error_text<<std::endl;
    std::cerr<<"...now exiting to system...\n";
    exit(0);
};
//______________________________________________________________________________
double psi_f_vwc(double psi_air,double vwc_sat,double vwc,double b) {
    //(J/kg or kPa) soil-water potential from volumn water content
    //(J/kg or kPa) psi_air: Soil-water potential at air entry
    //(m3/m3) vwc: volumn water content
    //(m3/m3) vwc_sat: saturated volumn water content (m3/m3)
    //b: coefficient for soil-water potential
    double out = psi_air * pow(vwc/vwc_sat,-b);
    return out;
}
//______________________________________________________________________________
double vwc_f_psi(double psi_air,double vwc_sat,double psi,double b) {
    //Calculating volumn water content from soil-water potential
    //(J/kg or kPa) psi: water potential
    //(J/kg or kPa) psi_air: Soil-water potential at air entry
    //(m3/m3): volumn water content
    //(m3/m3)vwc_sat: saturated volumn water content
    //b: coefficient for soil-water potential
    double out = vwc_sat * pow(psi/psi_air,-1/b);
    return out;
}
//______________________________________________________________________________
double calcRunoff(double manning_coef, double hydro_slope, double pond_depth) {
    //ManningCoef: Manning coefficient [unitless];
    //hydroslope [m/m];
    //pond_depth [m];
    //Element length [m]
    //Runoff [m2/s]   //Runoff*cell_length = m3/s  or Runoff/cell_length = vertical_remove m/s
    double runoff = (1.0 / manning_coef) * sqrt(fabs(hydro_slope)) * pow(pond_depth,5.0/3.0);
    return runoff;
}
//______________________________________________________________________________
double calc_K_Theta(double Theta, double Theta_s, double K_Sat, double Campbell_b,
                      double Theta_b/*, double MacPoFac*/) {
    //with the optional arguments the equation could still be used for calculating the original Campbell
    //Theta, Theta_s, Theta_b [cm/cm]
    //K_sat [Length/Time]
    //Campbell b [unitless]
    //MacPoFac = macropore factor, which is used as a multiplyer to increase Ks to account for macro-pore abundance [unitless]
    double K_Theta(0);
    double MacPoFac(1);  //LML 14/04/14
    //if (Theta >= Theta_s) K_Theta = K_Sat;
    //else {
        double K_Theta_b = K_Sat * pow(Theta_b / Theta_s,(2.0 * Campbell_b + 3.0));
        //if (is_approximately<double>(MacPoFac,0.0)) MacPoFac = 1.0;  //takes care of the Optional argument //LML 14/04/14
        if (CORN::is_approximately<double>(Theta_b,0.0)) Theta_b = Theta_s;
        if (Theta < Theta_b) {
            K_Theta = K_Sat * pow(Theta / Theta_s, (2.0 * Campbell_b + 3.0));
        } else {
            if (CORN::is_approximately<double>(Theta_b,Theta_s)) K_Theta = MacPoFac * K_Sat;
            else 
                //analogous to the approach described in Mehta et al. 2004 Environmental Modeling and Assessment 9: 77–89, 2004.
                K_Theta = (Theta - Theta_b) / (Theta_s - Theta_b) * (MacPoFac * K_Sat - K_Theta_b) + K_Theta_b;
        }
    //}
    //if (K_Theta > K_Sat) K_Theta = K_Sat;
    //else if (K_Theta < 0.0) K_Theta = 0.0;
    return K_Theta;
}
//______________________________________________________________________________
double MeanOfArray(double *data_array,double invalid_data,int members)
{
    //Calculate the average from array
    //invalid_data shows the invalid data if not valid
    double temp(0);
    for (int i = 0; i < members; i++) {
        if (!CORN::is_approximately<double>(data_array[i],invalid_data)) {
            temp += data_array[i]/members;
        } else {
            temp = invalid_data;
            i = members;
        }
    }
    return temp;
}
//______________________________________________________________________________
double SumOfArray(double *data_array,double invalid_data,int members)
{
    //Calculate the sum from array
    //invalid_data shows the invalid data if not valid
    double temp(0);
    for (int i = 0; i < members; i++) {
        if (!CORN::is_approximately<double>(data_array[i],invalid_data)) {
            temp += data_array[i];
        } else {
            temp = invalid_data;
            i = members;
        }
    }
    return temp;
}
//______________________________________________________________________________
double MaxOfArray(double *data_array,double invalid_data,int members)
{
    //Calculate the maximum from array
    //invalid_data shows the invalid data if not valid
    double temp = std::numeric_limits<int>::min();
    for (int i = 0; i < members; i++) {
        if (!CORN::is_approximately<double>(data_array[i],invalid_data)) {
            if (temp<data_array[i]) temp = data_array[i];
        } else {
            temp = invalid_data;
            i = members;
        }
    }
    return temp;
}
//______________________________________________________________________________
double MinOfArray(double *data_array,double invalid_data,int members)
{
    //Calculate the minimum from array
    //invalid_data shows the invalid data if not valid
    double temp(std::numeric_limits<int>::max());
    for (int i = 0; i < members; i++) {
        if (!CORN::is_approximately<double>(data_array[i],invalid_data)) {
            if (temp>data_array[i]) temp = data_array[i];
        } else {
            temp = invalid_data;
            i = members;
        }
    }
    return temp;
}
//______________________________________________________________________________
/*150919 This leapyear function is erroneous using CORN
bool bLeapYear(const int year)
{   //Leap year: 1
    return !((year)%400) || (!((year)%4) && ((year)%100));
}
*/
//______________________________________________________________________________
std::string getKeyWord(const std::string& str)
{
    std::string key("");
    std::size_t s_comments = str.find_first_of('#');
    std::size_t s_keyfirst = str.find_first_of('[');
    std::size_t s_keysend = str.find_first_of(']');
    if (s_keyfirst == std::string::npos || s_keysend == std::string::npos) {
        return key;
    } else {
        if ((s_comments != std::string::npos) && ((s_keyfirst > s_comments) || (s_keysend > s_comments))) {
            return key;
        } else {
            std::size_t length = s_keysend - s_keyfirst - 1;
            if (length < 1) {
                return key;
            } else {
                key = str.substr(s_keyfirst+1,length);
                return key;
            }
        }
    }
}
//______________________________________________________________________________
void removeWhitespace(std::string& str)
{
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r') {
            str.erase(i, 1);
            i--;
        }
    }
}
//______________________________________________________________________________
bool IsMassBalance(double inflow,double outflow,double oldpool,double newpool,double tolerance)
{
    bool balance(true);
    double netflux = inflow - outflow;
    double change = newpool - oldpool;
    if (fabs(netflux-change) > tolerance
       || fabs(oldpool)>1e20                //LML 140911
       || fabs(newpool)>1e20                //LML 140911
    )
    {
        balance = false;
    }
    return balance;
}
//______________________________________________________________________________
// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
/*150915RLN obsolete use CORN::Time (The default constructor is now)
std::string currentDateTime() {
    time_t     now(time(0));
    char       buf[80];
    struct tm tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}
*/
//______________________________________________________________________________
void Tridiagonal(int n, double *a, double *b, double *c, double *d, double *v, double *b1, double *d1)
{
    //[a b c]*[v]=[d]
    //n is the no of eqns (integer, inputs)
    //a, b, c, d are 1-D arrays of size n (real, inputs)
    //v is solution array of size n+1 (real, outputs)
    //b1,d1: array of size n+1
    //array: 0-n [0] is useless
    //double *b1, *d1;
    for (int i = 1; i <= n; i++) {
        b1[i] = b[i];
        d1[i] = d[i];
    }
    for (int i = 2; i <= n; i++) {
        double ff = a[i] / b1[i - 1];
        b1[i] = b1[i] - c[i - 1] * ff;
        d1[i] = d1[i] - d1[i - 1] * ff;
    }
    v[n] = d1[n] / b1[n];
    for (int i = 1; i <= n - 1; i++) {
        int j = n - i;
        v[j] = (d1[j] - c[j] * v[j + 1]) / b1[j];
    }
}
//______________________________________________________________________________
// LML 141212
bool FindAndMatchYearForRotationEvents(int &target_year,int target_doy,int cur_year,int cur_doy,int rot_years)
{
    if (target_doy != cur_doy) {
        return false;
    } else {
        #ifdef REPEAT_MANAGEMENT
        //LML 150205 if repeat management, all years in management input are reset every rotation cycle
        div_t period = div(cur_year-target_year, rot_years);
        if (period.rem != 0) {
            return false;
        } else {
            if (target_year < 6000) {                                            //150522 added this option
                target_year += period.quot * rot_years;
                return true;
            } else {
                if (period.quot == 1) return true;
                else return false;
            }
        }
        #else
        if(target_year == cur_year) return true;
        else return false;
        #endif        
    }
}
//_160122 FMS___________________________________________________________________
double calc_SoilHeatCapacity(const double BD, const double SOM_fraction, const double volumetric_WC,const double volumetric_IceC)   //FMS Jan 22, 2016 was private function
{
    //soil heat capacity (J/(m3 °C))
    //BD = bulk density (g/cm3)
    //SOM fraction (g/g)
    //volumetric water and ice content (m/m)

    const double PD             = 2.65;                                          //particle density (g/cm3)  - multiply by 1000 gets (kg/m3)
    const double SOM_D          = 1.3;                                           //SOM particle density (g/cm3)  - multiply by 1000 gets (kg/m3)
    const double Cm_minerals    = 750;                                           //heat capacity of clay, silt and sand (J/(kg °C))
    const double Cm_SOM         = 1880;                                          //heat capacity of soil organic matter (J/(kg °C))
    const double Cv_water       = 4180000;                                       //volumetric heat capacity of water (J/(m3 °C))
    const double Cv_ice         = 1938000;                                       //volumetric heat capacity of ice (J/(m3 °C))
    double SoilHeatCapacity = (PD * 1000. * Cm_minerals * (1 - SOM_fraction) + SOM_D * 1000. * Cm_SOM * SOM_fraction)
                              * BD / (PD * (1 - SOM_fraction) + SOM_D * SOM_fraction)
                              + Cv_water * volumetric_WC
                              + Cv_ice * volumetric_IceC;
    return SoilHeatCapacity;
}
//_160122 FMS___________________________________________________________________
double calc_Heat_Conductivity(const double Bulk_Density, const double volumetric_WC, const double fraction_clay)
{
    //thermal conductivity (page 32+ of Campbell 1985)
    double C1 = 0.65 - 0.78 * Bulk_Density + 0.6 * Bulk_Density * Bulk_Density;  //equation 4.27; coeff of 4.20 ;(A)
    double C2 = 1.06 * Bulk_Density;                                             //equation 4.25; coeff of 4.20; (B)
    double C3 = 1 + 2.6 / sqrt(fraction_clay);                                   //equation 4.28; coeff of 4.20 ;(C)
    double C4 = 0.03 + 0.1 * Bulk_Density * Bulk_Density;                        //equation 4.22; coeff of 4.20 ;(D)
    double Heat_Conductivity = C1 + C2 * volumetric_WC - (C1 - C4) * exp(-pow(C3 * volumetric_WC,4));
    return Heat_Conductivity;
}
//______________________________________________________________________________
double calc_LatentHeat(const double Latent_Heat, const double Conductivity, const double SaturationVaporPressureSurface, const double SaturationVaporPressureAir, const double AirPressure) //FMS Jan 27, 2016
{
    //Latent_Heat J/mol
    //Presure kPa
    //Conductivity mol/m2/s
    //CalcLatentHeat J/m2/s
    return Latent_Heat * Conductivity * (SaturationVaporPressureSurface - SaturationVaporPressureAir) / AirPressure;
}
//FMS Jan 27, 2016______________________________________________________________
double calc_LatentHeatSoil(const double Latent_Heat, const double Molar_Mass_Air, const double Relative_Humidity_Soil, const double Soil_Temperature, const double Air_Temperature) //FMS Jan 27, 2016
{
    //Latent_Heat J/mol
    //Delta_Temperature degree K
    //Molar mass  mol/g
    //CalcLatentHeat kJ/m2/s
    //Relative_Humidity_Soil %
    //Diffusivity m2/s
    const double Diffusivity = 2.22 * 1.e-5;                                       //By campbell 1998 at zero C is 2.12*10^-5 at, 45C is 2.77 *10^-5
    double Delta_Temperature = Soil_Temperature - Air_Temperature;
    return Latent_Heat * Molar_Mass_Air * Diffusivity * Relative_Humidity_Soil * Delta_Temperature;
}
/*160226LML not used
//FMS Jan 27, 2016______________________________________________________________
double calc_RelativeHumiditySoil(const double Soil_Potential, const double Hourly_Soil_Temp, const double Molecular_Mass_Water, const double R) //FMS Jan 27, 2016
{
    //Soil_Potential J/kg
    //Hourly_Soil_Temp K
    //Molecular_Mass_Water g/mol
    //R Constant of Gas
    double T = Hourly_Soil_Temp + 273.3;
    return exp(Soil_Potential * Molecular_Mass_Water / (R * T));
}
//FMS Jan 27, 2016______________________________________________________________
*/
