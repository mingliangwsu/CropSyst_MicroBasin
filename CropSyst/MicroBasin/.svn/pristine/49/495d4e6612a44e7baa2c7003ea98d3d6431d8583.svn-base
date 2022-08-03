#include "weatherreadfilesclass.h"
#include "util/pubtools.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>

WeatherReadFilesClass::WeatherReadFilesClass(int _nyears,WeatherLocationInputClass &_WeatherLocationInputRef)//WeatherLocationInputClass *_weatherloc)
    :WeatherLocationInputRef(_WeatherLocationInputRef)
{
    num_years = _nyears;
    Path = WeatherLocationInputRef.getWeatherFilePath();
    Prefix = WeatherLocationInputRef.getWeatherFilePrefix();
    initMem();
};

WeatherReadFilesClass::~WeatherReadFilesClass()
{
#ifdef Destruct_Monitor
    std::cout<<"~WeatherReadFilesClass:"<<std::endl;
#endif

    clearMem();
#ifdef Destruct_Monitor
    std::cout<<"~WeatherReadFilesClass done."<<std::endl;
#endif
};

void WeatherReadFilesClass::initMem()
{
    Annual_Weather = (WeatherSingleYearClass *) malloc(num_years * sizeof(WeatherSingleYearClass));     //(100) As New
    if(Annual_Weather == NULL)
        nrerror("Can't malloc memory for WeatherReadFilesClass::Annual_Weather!\n");

    Years = (int *)malloc(num_years * sizeof(int));
    if(Years == NULL) nrerror("Can't malloc memory for WeatherReadFilesClass::Years!\n");
};

void WeatherReadFilesClass::clearMem()
{
    free(Annual_Weather);
    free(Years);
};

int WeatherReadFilesClass::FindYearIndex(int year)      //need further works!!! Liu.M 09/20/13
{
    int Year_Index;
    /*
    int i,Year_Index,Unused_Index;
    std::string filename,Year_STR;

    Unused_Index = -1;
    i = 0;
    Year_Index = -1;

    do{
        if(Years[i] == year) Year_Index = i;
        if(Unused_Index == -1 && Years[i] = 0) Unused_Index = i;
        i++;
    }while (Year_Index >= 0 || Unused_Index >= 0 || i > 99);

    if(Unused_Index >= 0){
        //need to load the year
        Year_STR = Str$(Year);
        Year_STR = LTrim(Year_STR);

        filename = Path + "\" + Prefix + Year_STR + ".dat";

        Annual_Weather[Uused_Index].Read_Weather_File(filename);
        Years[Unused_Index] = Year;
        Year_Index = Unused_Index;
    }

    */
    return(Year_Index);

};

#ifdef HOURLY_MET
#else

double WeatherReadFilesClass::getPrecipitation_mm(int year,int doy)
{
    int Year_Index = FindYearIndex(year);
    double out;
    char errormessage[200];
    if(Year_Index >= 0) out = Annual_Weather[Year_Index].getPrecipitation(doy);
    else{
        sprintf(errormessage,"WeatherReadFilesClass::getPrecipitation_mm.Year %d not found",year);
        nrerror(errormessage);
    }
    return(out);
};

double WeatherReadFilesClass::getTmax(int year,int doy)
{
    int Year_Index = FindYearIndex(year);
    double out;
    char errormessage[200];
    if(Year_Index >= 0) out = Annual_Weather[Year_Index].getTmax(doy);
    else{
        sprintf(errormessage,"WeatherReadFilesClass::getTmax.Year %d not found",year);
        nrerror(errormessage);
    }
    return(out);
};

double WeatherReadFilesClass::getTmin(int year,int doy)
{
    int Year_Index = FindYearIndex(year);
    double out;
    char errormessage[200];
    if(Year_Index >= 0) out = Annual_Weather[Year_Index].getTmin(doy);
    else{
        sprintf(errormessage,"WeatherReadFilesClass::getTmin.Year %d not found",year);
        nrerror(errormessage);
    }
    return(out);
};

double WeatherReadFilesClass::getSolRad(int year,int doy)
{
    int Year_Index = FindYearIndex(year);
    double out;
    char errormessage[200];
    if(Year_Index >= 0) out = Annual_Weather[Year_Index].getSolRad(doy);
    else{
        sprintf(errormessage,"WeatherReadFilesClass::getSolRad.Year %d not found",year);
        nrerror(errormessage);
    }
    return(out);
};

double WeatherReadFilesClass::getHumRelMax(int year,int doy)
{
    int Year_Index = FindYearIndex(year);
    double out;
    char errormessage[200];
    if(Year_Index >= 0) out = Annual_Weather[Year_Index].getRelHumMax(doy);
    else{
        sprintf(errormessage,"WeatherReadFilesClass::getRelHumMax.Year %d not found",year);
        nrerror(errormessage);
    }
    return(out);
};

double WeatherReadFilesClass::getHumRelMin(int year,int doy)
{
    int Year_Index = FindYearIndex(year);
    double out;
    char errormessage[200];
    if(Year_Index >= 0) out = Annual_Weather[Year_Index].getRelHumMin(doy);
    else{
        sprintf(errormessage,"WeatherReadFilesClass::getRelHumMin.Year %d not found",year);
        nrerror(errormessage);
    }
    return(out);
};

double WeatherReadFilesClass::getWind(int year,int doy)
{
    int Year_Index = FindYearIndex(year);
    double out;
    char errormessage[200];
    if(Year_Index >= 0) out = Annual_Weather[Year_Index].getWind(doy);
    else{
        sprintf(errormessage,"WeatherReadFilesClass::getWind.Year %d not found",year);
        nrerror(errormessage);
    }
    return(out);
};

#endif
