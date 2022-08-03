#ifdef OBSOLETE
081017 The dewpoint temperature calculations were not working well,
VP_act is usually/always > VPsat_at_Tmin

/*081016_*/ float64 Relative_humidity_maximum_parameter::est_from_VPD_max(CORN::Quality_code &RHmax_quality)
/*_______*/ {
/*_______*/    RHmax_quality = quality_estimated_from(
/*_______*/         UED_worst_quality(get_min_temperature_quality()
/*_______*/        ,UED_worst_quality(get_max_temperature_quality()
/*_______*/                          ,get_vapor_pressure_deficit_max_quality())))
/*_______*/    if (!UED_is_valid(RHmax_quality))
/*_______*/       return 0.0; // Abort, we don't have sufficient quality data.
/*_______*/    float64 VPD_max       = vapor_pressure_deficit_max->get();
/*_______*/    Vapor_pressure_base vapor_pressure;
/*_______*/    float64 max_temp      = air_temperature_max->get(); //   get_curr_min_temperature();
/*_______*/    float64 min_temp      = air_temperature_min->get(); //   get_curr_min_temperature();
/*_______*/    float64 VPsat_at_Tmax = vapor_pressure.calc_saturation_kPa(max_temp,max_temp,OVER_WATER_ONLY);
/*_______*/    float64 VPsat_at_Tmin = vapor_pressure.calc_saturation_kPa(min_temp,min_temp,OVER_WATER_ONLY);
/*040114_*/       // RLN: According to the World Meteorological Organization WMO
/*040114_*/       // RH is calculated by computing the denominoator (or maximum possible water vapor content)
/*040114_*/       // over water rather than ice regardless of the temperature.
/*040114_*/       // This results in a higher value of maximum possible water
/*040114_*/       // vapor contant at any given temperature.
/*040114_*/       // Apparently this is  to prevent the occassional possibility of RH values
/*040114_*/       // in exccess of 100% when the atmosphere is in a super-cooled state.

/*_______*/    float64 VP_act        = VPsat_at_Tmax - VPD_max;
/*_______*/    float64 RHmax = VP_act / VPsat_at_Tmin * 100.0;
/*_______*/    RHmax = CORN_must_be_between(RHmax,0.0,100.0);
/*_______*/    return RHmax;
/*_______*/ };
#endif
//______________________________________________________________________________
#ifdef OBSOLETE
091212 This is the same as calc_from_VPsat_at_max_dew_point
/*081028_*/ float64 Relative_humidity_minimum_parameter::calc_from_max_dew_point_temperature(CORN::Quality &RHmin_quality) const
/*_______*/ {  float64 RHmin = 0.0;
TRACE          trace << std::string(" ",trace_indent) << "RHmin calculating from DewPtmax" << endl; trace_indent += 1;

/*_______*/    if (!dew_point_temperature_max || ! air_temperature_max)
/*_______*/       RHmin_quality.set(missing_quality);
/*_______*/    else
/*_______*/    {  Quality DP_max_qual;
/*_______*/       float64 max_dewpt_temp = dew_point_temperature_max->get(DP_max_qual);
/*_______*/       if (DP_max_qual.is_valid())
/*_______*/       {
/*_______*/          Quality Tmax_quality;
/*_______*/          float64 Tmax = air_temperature_max->get(Tmax_quality);
//091209/*_______*/          const CORN::Quality &contrib_quality = DP_max_qual.worst(Tmax_quality);
//091209/*_______*/          RHmin_quality.set(quality_calculated_from(contrib_quality.get()));
/*_______*/          RHmin_quality.set(DP_max_qual.worst(Tmax_quality));

/*091209_*/          // Dew point and relative humidity are always the same quality (the calculation is one to one)
/*091209_*/          // (in the real world measured relative humidity is actually typically calculated directly from dewpoint temperature)

/*_______*/          Vapor_pressure_base vapor_pressure;
/*_______*/          float64 VPsat_max_dewpt_temp =  vapor_pressure.calc_saturation_kPa (max_dewpt_temp, Tmax,OVER_ICE_IF_FREEZING /*OVER_WATER_ONLY*/);
/*_______*/          float64 VPsat_at_Tmax =  vapor_pressure.calc_saturation_kPa(Tmax,Tmax,OVER_WATER_ONLY);
/*_______*/          RHmin =  VPsat_max_dewpt_temp / VPsat_at_Tmax * 100.0;
/*_______*/          RHmin = CORN_must_be_between(RHmin,0.0,100.0);
/*_______*/          set(RHmin,RHmin_quality);
/*_______*/       } else
/*_______*/          RHmin_quality.set(unknown_quality);
/*_______*/    };
/*_______*/    return RHmin;
/*_______*/ };
#endif
//______________________________________________________________________________

091212  don't delete. Claudio decided trying to estimate from DewPtavg is not tenable

//______________________________________________________________________________

091212  don't delete

//______________________________________________________________________________
