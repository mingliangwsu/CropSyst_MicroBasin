#ifndef PUBTOOLS_H
#define PUBTOOLS_H
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <math.h>
#if __GNUC__
#include <cxxabi.h>
#endif
#include <sstream>
#include <iostream>
#include "math/compare.hpp"
#include <vector>
#include <limits>
extern void nrerror(const char* error_text);
extern double psi_f_vwc(double psi_air,double vwc_sat,double vwc,double b);
extern double vwc_f_psi(double psi_air,double vwc_sat,double psi,double b);
extern double calcRunoff(double manning_coef, double hydro_slope, double pond_depth);
//140603 #ifndef CROPSYST_HYDROLOGY
#ifdef MBVB_FD
extern double calc_K_Theta(double Theta, double Theta_s, double K_Sat, double Campbell_b
                     ,double Theta_b
                     //140305 Claudio decided to deactivate this , double MacPoFac
                      );
#endif
// RLN replaced with is_approximately extern bool AreDoubleSame(double dFirstVal, double dSecondVal);
extern double SumOfArray(double *data_array,double invalid_data,int members);
extern double MeanOfArray(double *data_array,double invalid_data,int members);
extern double MaxOfArray(double *data_array,double invalid_data,int members);
extern double MinOfArray(double *data_array,double invalid_data,int members);

bool IsMassBalance(double inflow,double outflow,double oldpool,double newpool,double tolerance);
void Tridiagonal(int n, double *a, double *b, double *c, double *d, double *v, double *b1, double *d1);
extern std::string getKeyWord(const std::string& str);
extern void removeWhitespace(std::string& str);
//140305 RLN use CORN
/*150919 This leapyear function is erroneous using CORN
extern bool bLeapYear(const int year);
*/
extern void DebugRunToTime(int current_doy,int current_hour,int target_doy,int target_hour);
extern bool FindAndMatchYearForRotationEvents(int &target_year,int target_doy,int cur_year,int cur_doy,int rot_years);
extern double calc_SoilHeatCapacity(const double BD, const double SOM_fraction, const double volumetric_WC,const double volumetric_IceC);
extern double calc_Heat_Conductivity(const double Bulk_Density, const double volumetric_WC, const double fraction_clay);
extern double calc_LatentHeat(const double Latent_Heat, const double Conductivity, const double SaturationVaporPressureSurface, const double SaturationVaporPressureAir, const double AirPressure); //FMS Jan 27, 2016
extern double calc_LatentHeatSoil(const double Latent_Heat, const double Molar_Mass_Air, const double Relative_Humidity_Soil, const double Soil_Temperature, const double Air_Temperature); //FMS Jan 27, 2016
//160226LML extern double calc_RelativeHumiditySoil(const double Soil_Potential, const double Hourly_Soil_Temp, const double Molecular_Mass_Water, const double R); //FMS Jan 27, 2016


/*150915RLN obsolete use CORN::Time (The default constructor is now)
extern std::string currentDateTime();
*/
//______________________________________________________________________________
template <class array_type> array_type *alloc_1d_array(int rows, const char* varname)
{
    array_type *pdata = new array_type[rows];
    return pdata;
}
//______________________________________________________________________________
template <class array_type>
void delete_1d_array(array_type *p)
{
    delete[] p;
}
//______________________________________________________________________________
template <class array_type>
void delete_2d_array(array_type **p,int rows)
{
    for (int i = 0; i < rows; i++) 
        delete[] p[i];
    delete[] p;
}
//______________________________________________________________________________
template <class array_type>
void delete_3d_array(array_type ***p,int d1,int d2)
{
    for (int i = 0; i<d1; i++) {
        for (int j = 0; j<d2; j++) {
            delete[] p[i][j];
        }
        delete[] p[i];
    }
    delete[] p;
}
//______________________________________________________________________________
template <class array_type>
void delete_4d_array(array_type ***p,int d1,int d2,int d3)
{
    for (int i = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
            for (int k = 0; k < d3; k++) {
                delete[] p[i][j][k];
            }
            delete[] p[i][j];
        }
        delete[] p[i];
    }
    delete[] p;
}
//______________________________________________________________________________
template <class array_type> array_type **alloc_2d_array(int rows, int columns, const char* varname)
{
    array_type **pdata = new array_type*[rows];
    for (int i = 0; i < rows; i++) {
        pdata[i] = new array_type[columns];
    }
    return pdata;
}
//______________________________________________________________________________
template <class array_type> array_type ***alloc_3d_array(int d1, int d2, int d3, const char* varname)
{
    array_type ***pdata = new array_type**[d1];
    for (int i = 0; i < d1; i++) {
        pdata[i] = new array_type*[d2];
        for (int j = 0; j < d2; j++) {
            pdata[i][j] = new array_type[d3];
       }
    }
    return pdata;
}
//______________________________________________________________________________
template <class array_type> array_type ****alloc_4d_array(int d1, int d2, int d3, int d4, const char* varname)
{
    array_type ****pdata = new array_type ***[d1];
    for (int i = 0; i < d1; i++) {
        pdata[i] = new array_type **[d2];
        for (int j = 0; j < d2; j++) {
            pdata[i][j] = new array_type *[d3];
            for (int k = 0; k < d3; k++) {
                pdata[i][j][k] = new array_type[d4];
            }
        }
    }
    return pdata;
}
//______________________________________________________________________________
template <class array_type> void copy_2d_array(array_type **from,array_type **to,int rows,int cols)
{
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)
    for (long ij = 0; ij < rows * cols; ij++) {
        long i = (long)(ij / cols);
        long j = ij % cols;
        to[i][j] = from[i][j];
    }
}
//______________________________________________________________________________
template <class array_type> void copy_1d_array(array_type *from,array_type *to,int rows)
{
    #pragma omp parallel for                                                     //170713 num_threads(NUMCORES_TO_USE)
    for (int i = 0; i < rows; i++) {
            to[i] = from[i]; 
    }
}
//______________________________________________________________________________
template <class array_type>
array_type MaxOfArray(const std::vector<array_type> &data_array,array_type invalid_data,int members)
{
    //Calculate the maximum from array
    //invalid_data shows the invalid data if not valid
    array_type temp = std::numeric_limits<array_type>::min();

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
template <class array_type>
array_type SumOfArray(const std::vector<array_type> &data_array,array_type invalid_data,int members)
{
    //Calculate the sum from array
    //invalid_data shows the invalid data if not valid
    array_type temp(0);
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
template <class array_type>
double MeanOfArray(const std::vector<array_type> &data_array,array_type invalid_data,int members)
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
template <class array_type>
array_type MinOfArray(const std::vector<array_type> &data_array,array_type invalid_data,int members)
{
    //Calculate the minimum from array
    //invalid_data shows the invalid data if not valid
    array_type temp(std::numeric_limits<array_type>::max());  //LML 150205 need check!!!
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

#endif // PUBTOOLS_H
