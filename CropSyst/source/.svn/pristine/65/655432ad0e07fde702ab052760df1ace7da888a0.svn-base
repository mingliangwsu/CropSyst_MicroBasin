
#include <fstream>
#include "ued/library/varcodes.h"
#ifndef primitiveH
#  include "corn/primitive.h"
#endif
//130928 #include "corn/string/ustring.h"
#include "mgmt_types.h"
#include "cs_varderiv.h"

/*
   This program generates the CropSyst UED variable code definitions header file

   Composing the variable codes:

   - CropSyst variable codes are non-stanard UED 32bit variable codes, but
     follow the standard format.
     That is, the upper byte specifies the UED qualifier
     with the upper most bit always set to 1(nonstandard)
   - CropSyst physical properties codes do not follow the UED standard.
     The 24 bit code is compose as follows

     23 20 1916 15               0
     +----+----+-----------------+
     | CG | C  |                 |
     +----+----+-----------------+
      \__CSC__/ \______CSV______/
      \_________CSPROP___________/

     CG is a class group: for example the various subclasses of soil:
     soil_file, soil_base, soil_finite_difference, soil_chemical_profile form one class group.
     Thus there can be 16 groups (0-F)

     C is the distinct class I.e.   soil_base  where the following variable is defined.
     Thus there can be 16 classes in a group (0-F)

     CSV is the cropsyst variable the coding of this field is up to the class where the variable is defined.
     Normally it is a simple enumeration. (65536 variables in any CropSyst class)


     In the case of the soil layer profiles, a UED layered variable will be used
     it is defined as follows:

    In V5 the layer is moved to bits 16-23,

     23     16 1512 11 8 7       0
     +--------+----+----+--------+
     |        | CG | C  |        |
     +--------+----+----+--------+
     \_Layer_/ \__CSC__/ \__CSV_/
               \______PROP______/            <- returned by get_property()
      \_____CS_LAYER_PROP________/

     In V4 the layer was in bits 0-7

     23 20 1916 15     8 7       0
     +----+----+--------+--------+
     | CG | C  |        |        |
     +----+----+--------+--------+
      \__CSC__/ \__CSV_/ \_Layer_/
      \______PROP______/            <- returned by get_property()
      \_____CS_LAYER_PROP________/


    Thus in classes where layering is used there can be a total of 256 variables
    in a class with 256 layers.
    (Layer 0 is used to designate a value for the whole profile)

    Currently only CSV's 0-31 are available for output

*/
/*130730  these defines move to CS_vardev.h
//The following composes a CropSyst non-standard UED scalar property code
#define CS_PROP(CSCV,CSV)              (((nat32)CSCV << 16) | (nat32)CSV)

//The following composes a CropSyst non-standard UED layered property code
#define CS_LAYER_PROP(CSCV,CSV,layer)  (((nat32)CSCV << 16) | ((((nat32)CSV) << 8) | (nat32)layer))

#define CS_UED_compose_var_code(qualifier,CSprop)   (((nat32)1 << 31) | ((nat32)qualifier << 24) | (nat32)CSprop)

#define CS_UED_compose_layer_var_code(qualifier,CSprop)   (((nat32)1 << 31) | ((nat32)1 << 30) |((nat32)qualifier << 24) | (nat32)CSprop)
*/
#include "cs_vars.h"
   char hex_buf[20];

using namespace CORN;

std::string CSVC_label;
//______________________________________________________________________________
void get_CSVC_label(nat32 CSVC)
{
   CSVC_label.assign("X");
   switch (CSVC)
   {
      case CSC_weather              : CSVC_label.assign("weather")            ; break;
      case CSC_weather_VPD          : CSVC_label.assign("weather_VPD")        ; break;
      case CSC_weather_ET           : CSVC_label.assign("weather_ET")         ; break;
      case CSC_weather_date         : CSVC_label.assign("weather_date")       ; break;
      case CSC_soil_base            : CSVC_label.assign("soil_base")          ; break;
      case CSC_soil_carbon_mass     : CSVC_label.assign("soil_C")             ; break;
      case CSC_soil_nitrogen        : CSVC_label.assign("soil_N")             ; break;
      case CSC_soil_phosphorus      : CSVC_label.assign("soil_P")             ; break;
      case CSC_soil_freezing        : CSVC_label.assign("soil_freezing")      ; break;
      case CSC_soil_erosion         : CSVC_label.assign("soil_erosion")       ; break;
      case CSC_soil_runoff          : CSVC_label.assign("soil_runoff")        ; break;
      case CSC_soil_pond            : CSVC_label.assign("soil_pond")          ; break;
      case CSC_soil_complete        : CSVC_label.assign("soil_complete")      ; break;
      case CSC_crop_base            : CSVC_label.assign("crop_base")          ; break;
      case CSC_crop_nitrogen_misc   : CSVC_label.assign("crop_N")             ; break;
      case CSC_crop_biomass         : CSVC_label.assign("crop_biomass")       ; break;
      case CSC_crop_carbon_mass     : CSVC_label.assign("crop_C_mass")        ; break;
      case CSC_crop_nitrogen_mass   : CSVC_label.assign("crop_N_mass")        ; break;
      case CSC_crop_nitrogen_conc   : CSVC_label.assign("crop_N_conc")        ; break;
      case CSC_crop_phosphorus_misc : CSVC_label.assign("crop_P_mass")        ; break;
      case CSC_crop_complete        : CSVC_label.assign("crop_complete")      ; break;
      case CSC_residue              : CSVC_label.assign("residue")            ; break;
      case CSC_residue_plant        : CSVC_label.assign("residue_plant")      ; break;
      case CSC_residue_manure       : CSVC_label.assign("residue_manure")     ; break;
      case CSC_water_table          : CSVC_label.assign("water_table")        ; break;
      case CSC_management           : CSVC_label.assign("mgmt")               ; break;
      case CSC_management_irrigation: CSVC_label.assign("mgmt_irrig")         ; break;
//      case CSC_management_biomass_grazed : CSVC_label.assign("mgmt_biomass_grazed"); break;
      case CSC_management_N         : CSVC_label.assign("mgmt_N")             ; break;
      case CSC_management_P         : CSVC_label.assign("mgmt_P")             ; break;
      case CSC_management_NH4       : CSVC_label.assign("mgmt_NH4")           ; break;
      case CSC_management_NO3       : CSVC_label.assign("mgmt_NO3")           ; break;
      case CSC_other_output         : CSVC_label.assign("other_output")       ; break;
      case CSC_organic_matter       : CSVC_label.assign("organic_matter")     ; break;

      case CSC_miscellaneous_N      : CSVC_label.assign("misc_N"); break;
//      case CSC_xxxx    : CSVC_label.assign("xxxx"); break;
//      case CSC_xxxx    : CSVC_label.assign("xxxx"); break;
//      case CSC_xxxx    : CSVC_label.assign("xxxx"); break;
//      case CSC_xxxx    : CSVC_label.assign("xxxx"); break;
//Soil chemicals not yet implemented
//      case CSC_soil_chemical : CSVC_label.assign("soil_chemical")      ; break;
   };
};
//______________________________________________________________________________
void output_layer_variables
(std::ostream &h_strm,std::ostream &m_strm,std::ostream &cs_strm
,std::ostream &bas_strm
,std::ostream &vc_stream     // This is to print a table of variable codes for listbox or combobox selectors
,char *base_label,nat32 qualifier,nat32 CSC,nat32 CSV)
{
   h_strm << std::endl;
   m_strm << std::endl;
   cs_strm << std::endl;
   bas_strm << std::endl;

   get_CSVC_label(CSC);

   std::string /*130919 CORN::Ustring*/ class_and_var_label(CSVC_label);
   class_and_var_label.append("_");
   class_and_var_label.append(base_label);

   for (int sl = 0; sl <= 31; sl++)
   {
      std::string /*130919 CORN::Ustring*/ CSVC_code_str ("CSVC_");
      CSVC_code_str.append(class_and_var_label);
      if (qualifier)
      {  CSVC_code_str.append("_");
         CSVC_code_str.append(UED::Variable_code_qualifier_descriptions[qualifier]);
      };
      if (sl > 0)
      {  CSVC_code_str.append("_");
         char sl_cstr[10];
         itoa(sl,sl_cstr,10);
         CSVC_code_str.append(sl_cstr);

      std::string /*130919 CORN::Ustring*/ class_and_var_and_layer_label(class_and_var_label);
      class_and_var_and_layer_label.append("_");
      class_and_var_and_layer_label.append(sl_cstr);
      vc_stream << "{0x" << itoa(CS_UED_compose_layer_var_code(qualifier,CS_LAYER_PROP(CSC, CSV,sl)),hex_buf,16)
             << ",\"" << class_and_var_and_layer_label << "\"}," << std::endl;
      };
      h_strm <<  "#define " << CSVC_code_str;
      for (int i = 0; i <=60 - CSVC_code_str.length(); i++) h_strm << ' ';
      h_strm << "0x" << itoa(CS_UED_compose_layer_var_code(qualifier,CS_LAYER_PROP(CSC,CSV,sl)),hex_buf,16);

//      h_strm <<  "#define CSVC_" << class_and_var_label;
//      if (qualifier)
//         h_strm << '_' << UED_variable_code_qualifier_descriptions[qualifier];
//      if (sl > 0)
//         h_strm << '_' << sl;
//      h_strm << "        0x" << itoa(CS_UED_compose_layer_var_code(qualifier,CS_LAYER_PROP(CSC,CSV,sl)),hex_buf,16);
      h_strm << std::endl;

      m_strm << CSVC_code_str;
//      m_strm <<  "CSVC_" << class_and_var_label;
//      if (qualifier)
//         m_strm << '_' << UED_variable_code_qualifier_descriptions[qualifier];
//      if (sl > 0)
//         m_strm << '_' << sl;
      m_strm << " = nat32(" << CS_UED_compose_layer_var_code(qualifier,CS_LAYER_PROP(CSC,CSV,sl));
      m_strm << ")" <<std::endl;

//      cs_strm <<  "   , "
      cs_strm <<  " const uint "
      << CSVC_code_str;
      for (int i = 0; i <=60 - CSVC_code_str.length(); i++) cs_strm << ' ';
      cs_strm << "=0x" << itoa(CS_UED_compose_layer_var_code(qualifier,CS_LAYER_PROP(CSC,CSV,sl)),hex_buf,16);
      cs_strm   << ";";
      cs_strm << std::endl;

      bas_strm <<  " public const "
      << CSVC_code_str;
      bas_strm << " as long = " << CS_UED_compose_layer_var_code(qualifier,CS_LAYER_PROP(CSC,CSV,sl));
      bas_strm << std::endl;


   };
   // We only need one output selection for layered variabes
//   strm << "#define OUTPUT_" << class_and_var_label << "()   (sel_vars_" << CSVC_label << " & (1 << CSV_" << class_and_var_label << "))" << std::endl;
};
//______________________________________________________________________________

void output_variable
(ostream &h_strm
,ostream &m_strm
,ostream &cs_strm       // C#
,ostream &bas_strm       // C#
,ostream &vc_stream     // This is to print a table of variable codes for listbox or combobox selectors
,const char *var_label
,nat32 qualifier
,nat32 CSVC
,nat32 CSV)
{
   get_CSVC_label(CSVC);
   std::string class_and_var_label(CSVC_label);
   class_and_var_label.append("_");
   class_and_var_label.append(var_label);

   std::string CSVC_code_str ("CSVC_");
   CSVC_code_str.append(class_and_var_label);
   if (qualifier)
   {  CSVC_code_str.append("_");
      CSVC_code_str.append(UED::Variable_code_qualifier_descriptions[qualifier]);
   }
   vc_stream << "{0x" << itoa(CS_UED_compose_var_code(qualifier,CS_PROP(CSVC, CSV)),hex_buf,16)
             << ",\"" << class_and_var_label << "\"}," << std::endl;

   // C/C++ declarations
   h_strm
   << "#define "
   << CSVC_code_str;
   for (int i = 0; i <=60 - CSVC_code_str.length(); i++) h_strm << ' ';
   h_strm
   << "0x"
   << itoa(CS_UED_compose_var_code(qualifier,CS_PROP(CSVC, CSV)),hex_buf,16)
   << std::endl;

   // Matlab declarations
   m_strm
   << CSVC_code_str;
   m_strm
   << " = nat32("
   << CS_UED_compose_var_code(qualifier,CS_PROP(CSVC, CSV))
   << ")" << std::endl;

   // C# declarations
   cs_strm <<  " const uint "
      << CSVC_code_str;
   for (int i = 0; i <=60 - CSVC_code_str.length(); i++) cs_strm << ' ';
   cs_strm << '='
   << "0x"
   << itoa(CS_UED_compose_var_code(qualifier,CS_PROP(CSVC, CSV)),hex_buf,16)
   << ";"
   << std::endl;

   bas_strm <<  " public const " << CSVC_code_str;
   bas_strm << " as long = "
   << CS_UED_compose_var_code(qualifier,CS_PROP(CSVC, CSV))
   << std::endl;

}
//______________________________________________________________________________
void output_property
(ostream &h_strm
,ostream &m_strm
,ostream &cs_strm       // C#
,ostream &bas_strm       // C#
,ostream &vc_stream     // This is to print a table of variable codes for listbox or combobox selectors
,const char *var_label
,nat32 CSVC
,nat32 CSV)
{
   get_CSVC_label(CSVC);
   std::string /*130919 CORN::Ustring*/ class_and_var_label(CSVC_label);
   class_and_var_label.append("_");
   class_and_var_label.append(var_label);

   std::string CSVC_code_str ("CSVP_");
   CSVC_code_str.append(class_and_var_label);
   vc_stream << "{0x" << itoa(CS_PROP(CSVC, CSV),hex_buf,16)
             << ",\"" << class_and_var_label << "\"}," << std::endl;

   // C/C++ declarations
   h_strm
   << "#define "
   << CSVC_code_str;
   for (int i = 0; i <=60 - CSVC_code_str.length(); i++) h_strm << ' ';
   h_strm
   << "0x"
   << itoa(CS_PROP(CSVC, CSV),hex_buf,16)
   << std::endl;

   // Matlab declarations
   m_strm
   << CSVC_code_str;
   m_strm
   << " = nat32("
   << CS_PROP(CSVC, CSV)
   << ")" << std::endl;

   // C# declarations
   cs_strm <<  " const uint "
      << CSVC_code_str;
   for (int i = 0; i <=60 - CSVC_code_str.length(); i++) cs_strm << ' ';
   cs_strm << '='
   << "0x"
   << itoa(CS_PROP(CSVC, CSV),hex_buf,16)
   << ";"
   << std::endl;

   bas_strm <<  " public const " << CSVC_code_str;
   bas_strm << " as long = "
   << CS_PROP(CSVC, CSV)
   << std::endl;
}
//__2013-09-09__________________________________________________________________
void output_layer_property
(std::ostream &h_strm,std::ostream &m_strm,std::ostream &cs_strm
,std::ostream &bas_strm
,std::ostream &vc_stream     // This is to print a table of variable codes for listbox or combobox selectors
,char *base_label,nat32 CSC,nat32 CSV)
{
   h_strm << std::endl;
   m_strm << std::endl;
   cs_strm << std::endl;
   bas_strm << std::endl;

   get_CSVC_label(CSC);

   std::string class_and_var_label(CSVC_label);
   class_and_var_label.append("_");
   class_and_var_label.append(base_label);

   for (int sl = 0; sl <= 31; sl++)
   {
      std::string CSVC_code_str ("CSVP_");
      CSVC_code_str.append(class_and_var_label);

      if (sl > 0)
      {  CSVC_code_str.append("_");
         char sl_cstr[10];
         itoa(sl,sl_cstr,10);
         CSVC_code_str.append(sl_cstr);

      std::string class_and_var_and_layer_label(class_and_var_label);
      class_and_var_and_layer_label.append("_");
      class_and_var_and_layer_label.append(sl_cstr);
      vc_stream << "{0x" << itoa(CS_LAYER_PROP(CSC, CSV,sl),hex_buf,16)
             << ",\"" << class_and_var_and_layer_label << "\"}," << std::endl;
      };
      h_strm <<  "#define " << CSVC_code_str;
      for (int i = 0; i <=60 - CSVC_code_str.length(); i++) h_strm << ' ';
      h_strm << "0x" << itoa(CS_LAYER_PROP(CSC,CSV,sl),hex_buf,16);

//      h_strm <<  "#define CSVC_" << class_and_var_label;
//      if (qualifier)
//         h_strm << '_' << UED_variable_code_qualifier_descriptions[qualifier];
//      if (sl > 0)
//         h_strm << '_' << sl;
//      h_strm << "        0x" << itoa(CS_UED_compose_layer_var_code(qualifier,CS_LAYER_PROP(CSC,CSV,sl)),hex_buf,16);
      h_strm << std::endl;

      m_strm << CSVC_code_str;
//      m_strm <<  "CSVC_" << class_and_var_label;
//      if (qualifier)
//         m_strm << '_' << UED_variable_code_qualifier_descriptions[qualifier];
//      if (sl > 0)
//         m_strm << '_' << sl;
      m_strm << " = nat32(" << CS_LAYER_PROP(CSC,CSV,sl);
      m_strm << ")" <<std::endl;

//      cs_strm <<  "   , "
      cs_strm <<  " const uint "
      << CSVC_code_str;
      for (int i = 0; i <=60 - CSVC_code_str.length(); i++) cs_strm << ' ';
      cs_strm << "=0x" << itoa(CS_LAYER_PROP(CSC,CSV,sl),hex_buf,16);
      cs_strm   << ";";
      cs_strm << std::endl;

      bas_strm <<  " public const "
      << CSVC_code_str;
      bas_strm << " as long = " << CS_LAYER_PROP(CSC,CSV,sl);
      bas_strm << std::endl;


   };
   // We only need one output selection for layered variabes
//   strm << "#define OUTPUT_" << class_and_var_label << "()   (sel_vars_" << CSVC_label << " & (1 << CSV_" << class_and_var_label << "))" << std::endl;
}
//_2013-09-09___________________________________________________________________

#define QUALIFIER_at_time_step       ((nat32)1 << (nat32)UED_at_time_step)
//obsolete ? #define QUALIFIER_average_for_time_step 1  ((nat32)1 << (nat32)UED_average_for_time_step)
#define QUALIFIER_time_step_avg         (1 << (nat32)UED_time_step_avg)
// Average value for the time step.
#define QUALIFIER_maximum_for_time_step (1 << (nat32)UED_maximum_for_time_step)
#define QUALIFIER_time_step_max         (1 << (nat32)UED_time_step_max)
// Max average value for the time step.

#define QUALIFIER_minimum_for_time_step (1 << (nat32)UED_minimum_for_time_step)
#define QUALIFIER_time_step_min         (1 << (nat32)UED_time_step_min)
// Min average value for the time step.

#define QUALIFIER_standard_deviation_for_time_step (1 << (nat32)UED_standard_deviation_for_time_step)
#define QUALIFIER_std_dev_time_step     (1 << (nat32)UED_std_dev_time_step)
// Standard deviation for the time step.

#define QUALIFIER_total_for_time_step   (1 << (nat32)UED_total_for_time_step)
#define QUALIFIER_time_step_sum         (1 << (nat32)UED_time_step_sum)

// The following accumulation are accumulation for a period of time matching a record period
// For example the sum of a record's set of values
#define QUALIFIER_accumulation_to_date_time (1 << (nat32)UED_accumulation_to_date_time)
#define QUALIFIER_accum_to_date             (1 << (nat32)UED_accum_to_date)
#define QUALIFIER_accum_to_time             (1 << (nat32)UED_accum_to_time)

// Accumulation to date/time.

#define QUALIFIER_accumulation_for_period_deprecated    (1 << (nat32)UED_accumulation_for_period_deprecated)
#define QUALIFIER_period_accum_deprecated              (1 << (nat32)UED_period_accum_deprecated)

#define QUALIFIER_daily_contribution      (1 << (nat32)UED_daily_contribution)
// This is for situations where there is an amount supplied for the time step
// but that may disappear from a total later on:
// I.e. biomass added to a plant during a day, or snow depth added to the snow pack
// There will usually be another variable showing the value "at the time step"
// I.e. the biomass of the plant observed at a given day, or the current snow pack depth

#define QUALIFIER_average_for_period  (1 << (nat32)UED_average_for_period)
#define QUALIFIER_period_avg  ((nat32)1 << (nat32)UED_period_avg)
//This is for running average at a time step  (I.e. CropSyst average nitrogen stress)
#define QUALIFIER_period_max              (1 << (nat32)UED_period_max)
#define QUALIFIER_period_min              (1 << (nat32)UED_period_min)
#define QUALIFIER_period_std_dev          (1 << (nat32)UED_period_std_dev)
#define QUALIFIER_period_sum              ((nat32)1 << (nat32)UED_period_sum)
#define QUALIFIER_period_init             ((nat32)1 << (nat32)UED_period_init)


//______________________________________________________________________________
void output_variables
(ostream &h_strm
,ostream &m_strm
,ostream &cs_strm       // C#
,ostream &bas_strm
,ostream &vc_stream     // This is to print a table of variable codes for listbox or combobox selectors
,const char *var_label
,nat32 for_qualifiers
,nat32 CSVC
,nat32 CSV)
{
   // C/C++ declarations
   get_CSVC_label(CSVC);
   std::string /*130919 CORN::Ustring*/ class_and_var_label(CSVC_label);
   class_and_var_label.append("_");
   class_and_var_label.append(var_label);

   std::string /*130919 CORN::Ustring*/ CSPROP_code_str ("CSPROP_");
   CSPROP_code_str.append(class_and_var_label);

   h_strm
   << "#define "
   << CSPROP_code_str;
   for (int i = 0; i <=62 - CSPROP_code_str.length(); i++) h_strm << ' ';
   h_strm
   << "0x"
   << itoa(CS_PROP(CSVC, CSV),hex_buf,16)
   << std::endl;

   for (nat32 ued_qualifier = 0; ued_qualifier < 32; ued_qualifier++)
   { nat32 mask = (1 << ued_qualifier);
      if (for_qualifiers & mask)
         output_variable
         (h_strm
         ,m_strm
         ,cs_strm       // C#
         ,bas_strm
         ,vc_stream     // This is to print a table of variable codes for listbox or combobox selectors
         ,var_label
         ,ued_qualifier
         , CSVC
         , CSV);
   }
}
//______________________________________________________________________________
void output_comment(ostream &h_strm, ostream &m_strm,ostream &cs_strm,const char *comment)
{
   h_strm << std::endl << "// " << comment << std::endl;
   m_strm << std::endl << "% " << comment << std::endl;
   cs_strm << std::endl << "// " << comment << std::endl;
   // Don't think needed comment for vb_stream
}
//______________________________________________________________________________
void main()
{
   ofstream csvc_h("csvc.h");
   ofstream csvc_m("csvc.m");
   ofstream csvc_cs("csvc.cs");
   ofstream csvc_bas("csvc.bas");
   ofstream csvc_vc("csvc.vc");

//   ofstream variable_codes_cpp("CS_var_codes.cpp");
   ofstream variable_codes_h("CS_var_codes.h");

   csvc_h << "#ifndef CSVC_H" << std::endl;
   csvc_h << "#define CSVC_H" << std::endl;

//   csvc_cs << "namespace CropSyst"<< std::endl<<"{" << std::endl;
//   csvc_cs << "   enum Variable_codes" << std::endl;
//   csvc_cs << "    { CSVC_unknown=0" << std::endl;

   variable_codes_h   << "#ifndef CS_VARCODES_H" << std::endl
                      << "#define CS_VARCODES_H" << std::endl
                      << "struct CropSyst_UED_variable_code" << std::endl
                      << "{   unsigned long code;" << std::endl
                      << "    char *        name;" << std::endl
                      << "};" << std::endl
                      << "extern CropSyst_UED_variable_code cropsyst_UED_variable_codes[];" << std::endl
                      << "#endif" <<std::endl;
//obs   variable_codes_cpp << "#include "CS_var_codes.h>" << std::endl;
//obs   variable_codes_cpp << "CropSyst_UED_variable_code cropsyst_UED_variable_codes[] =\n{";


   csvc_bas << "Option Explicit" << std::endl;
   csvc_bas << "Attribute VB_name = \"CSVC\"" << std::endl;
   output_comment(csvc_h,csvc_m,csvc_cs,"CropSyst variable codes");

   output_comment(csvc_h,csvc_m,csvc_cs,"Crop base");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"name"                   ,UED_at_time_step                 ,CSC_crop_base,CSV_crop_base_name);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"growing_degree_days"    ,UED_period_accum_deprecated      ,CSC_crop_base, CSV_crop_base_growing_degree_days);  // may need to be accum to day
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"seasonal_thermal_time"  ,UED_period_sum                   ,CSC_crop_base, CSV_crop_seasonal_thermal_time);  // may need to be accum to day
   //NYN output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"season_duration"        ,UED_period_sum                   ,CSC_crop_base, CSV_crop_season_duration);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"dry_biomass_deprecate"   ,UED_at_time_step,CSC_crop_base, CSV_crop_base_sum_daily_canopy_biomass_deprecate);  //replaced with Crop_biomass_produced_above_ground period_sum
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"root_biomass_current"    ,UED_at_time_step,CSC_crop_base, CSV_crop_base_root_biomass_deprecate);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"green_biomass"           ,UED_at_time_step,CSC_crop_base, CSV_crop_base_green_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fruit_biomass"          ,UED_at_time_step,CSC_crop_base, CSV_crop_fruit_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fruit_canopy_biomass"   ,UED_at_time_step,CSC_crop_base, CSV_crop_fruit_canopy_biomass);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"orchard_solid_canopy_interception",UED_at_time_step,CSC_crop_base, CSV_orchard_solid_canopy_interception);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"orchard_shaded_area_GAI "             ,UED_at_time_step,CSC_crop_base, CSV_orchard_shaded_area_GAI);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"orchard_canopy_porosity"          ,UED_at_time_step,CSC_crop_base, CSV_canopy_porosity);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leaf_area_index"        ,UED_at_time_step,CSC_crop_base, CSV_crop_base_leaf_area_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"green_area_index"       ,UED_at_time_step,CSC_crop_base, CSV_crop_base_green_area_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"root_depth"             ,UED_at_time_step,CSC_crop_base, CSV_crop_base_root_depth);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_stress_factor"           ,UED_at_time_step,CSC_crop_base, CSV_crop_base_water_stress_factor );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_stress_factor"           ,UED_period_avg,CSC_crop_base, CSV_crop_base_water_stress_factor );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature_stress_factor"     ,UED_at_time_step,CSC_crop_base, CSV_crop_base_temperature_stress_factor );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature_stress_factor"     ,UED_period_avg,CSC_crop_base,CSV_crop_base_temperature_stress_factor );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_init_temp_stress_index"     ,UED_at_time_step,CSC_crop_base,CSV_crop_base_tuber_init_temperature_stress_index );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_fill_temp_stress_index"     ,UED_at_time_step,CSC_crop_base,CSV_crop_base_tuber_filling_temperature_stress_index );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_stress_index"     ,UED_at_time_step,CSC_crop_base, CSV_crop_base_water_stress_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_stress_index"     ,UED_period_avg,CSC_crop_base, CSV_crop_base_water_stress_index);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature_stress_index",UED_at_time_step,CSC_crop_base, CSV_crop_base_temperature_stress_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature_stress_index",UED_period_avg,CSC_crop_base, CSV_crop_base_temperature_stress_index);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_temperature_stress_index",UED_period_avg,CSC_crop_base, CSV_crop_base_flower_temperature_stress_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_water_stress_index",UED_period_avg,CSC_crop_base, CSV_crop_base_flower_water_stress_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_N_stress_index"   ,UED_period_avg,CSC_crop_base, CSV_crop_base_flower_N_stress_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"filling_duration_index"  ,UED_period_avg,CSC_crop_base, CSV_crop_base_filling_duration_index);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fract_canopy_cover"      ,UED_at_time_step,CSC_crop_base, CSV_crop_base_fract_canopy_cover);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leaf_water_pot"          ,UED_at_time_step,CSC_crop_base, CSV_crop_base_leaf_water_pot);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_pot"              ,UED_time_step_sum,CSC_crop_base, CSV_crop_base_transp_pot);// 24
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_pot"              ,UED_period_sum,CSC_crop_base, CSV_crop_base_transp_pot);// 39
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_pot"              ,UED_accum_to_date,CSC_crop_base, CSV_crop_base_transp_pot);// 39

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_act"              ,UED_time_step_sum,CSC_crop_base, CSV_crop_base_transp_act);// 25
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_act"              ,UED_period_sum,CSC_crop_base, CSV_crop_base_transp_act);// 40
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_act"              ,UED_accum_to_date,CSC_crop_base, CSV_crop_base_transp_act);// 40

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"           ,UED_time_step_sum,CSC_crop_base, CSV_crop_base_water_inter);// 32
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"           ,UED_period_sum,CSC_crop_base, CSV_crop_base_water_inter);// 47
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"           ,UED_accum_to_date,CSC_crop_base, CSV_crop_base_water_inter);// 47

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"growth_stage"            ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_growth_stage);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"planting_date_YMD"       ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_planting_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"emergence_date_YMD"      ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_emergence_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flowering_date_YMD"      ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_flowering_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_init_date_YMD"     ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_tuber_init_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"grain_filling_date_YMD"  ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_grain_filling_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"peak_LAI_date_YMD"       ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_peak_LAI_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"maturity_date_YMD"       ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_maturity_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"harvest_date_YMD"        ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_harvest_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"restart_date_YMD"        ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_restart_date_YMD);


   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"bud_break_date_YMD"                        ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_bud_break_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"initial_fruit_growth_date_YMD"             ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_initial_fruit_growth_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"rapid_fruit_growth_date_YMD"               ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_rapid_fruit_growth_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_begin_date_YMD"                   ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_inactive_begin_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_end_date_YMD"                     ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_inactive_end_date_YMD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"base_chill_requirement_satisfied_date_YMD" ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_chill_requirement_satisfied_date_YMD);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"planting_date_YD"       ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_planting_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"emergence_date_YD"      ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_emergence_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flowering_date_YD"      ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_flowering_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_init_date_YD"     ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_tuber_init_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"grain_filling_date_YD"  ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_grain_filling_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"peak_LAI_date_YD"       ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_peak_LAI_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"maturity_date_YD"       ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_maturity_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"harvest_date_YD"        ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_harvest_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"restart_date_YD"        ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_restart_date_YD);


   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"bud_break_date_YD"                   ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_bud_break_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"initial_fruit_growth_date_YD"        ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_initial_fruit_growth_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"rapid_fruit_growth_date_YD"          ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_rapid_fruit_growth_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_begin_date_YD"              ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_inactive_begin_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_end_date_YD"                ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_inactive_end_date_YD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"chill_requirement_satisfied_date_YD" ,UED_at_time_step,CSC_crop_phenology, CSV_crop_phenology_chill_requirement_satisfied_date_YD);


   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"peak_LAI"               ,UED_maximum_for_time_step,CSC_crop_base,CSV_crop_base_peak_LAI);
   // yield is at_time_step, because their could be daily yields
   // There is also an accumulated yield for crops with multiple harvest such as tea, alphalfa
//moved below   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"yield"                  ,UED_at_time_step, CSC_crop_base, CSV_crop_base_yield);

   for (nat32 CSC = CSC_crop_biomass; CSC <=CSC_crop_nitrogen_conc; CSC++)  // Eventually we could include carbon etc., but currenly there are only a couple of carbon outputs
   {
      for (uint8 fate_index = 0; fate_index < FATE_INDEX_COUNT; fate_index++)
      {
         nat32 fate_bitmask = (1 << fate_index);
         output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,mass_fate_label_table[fate_index],UED_at_time_step, CSC, fate_bitmask);
         output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,mass_fate_label_table[fate_index],UED_period_sum, CSC, fate_bitmask);
         output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,mass_fate_label_table[fate_index],UED_total_for_time_step, CSC, fate_bitmask);
      };
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"canopy"               ,UED_at_time_step, CSC, CSV_canopy);  // This is the current canopy
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_canopy"       ,UED_at_time_step, CSC, CSV_removed_canopy);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_non_yield"    ,UED_at_time_step, CSC, CSV_removed_non_yield);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_residue"      ,UED_at_time_step, CSC, CSV_removed_residue);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_grazing"      ,UED_at_time_step, CSC, CSV_removed_grazing);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"roots_live"            ,UED_at_time_step, CSC, CSV_crop_roots_live);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"roots_dead"            ,UED_at_time_step, CSC, CSV_crop_roots_dead);
      // Note: not currently outputing roots by layer

      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"produced_above_ground"      ,UED_period_sum, CSC, CSV_canopy);  // the total biomass produced replaces CSV_crop_base_sum_daily_canopy_biomass_deprecate
      //                                             canopy produce         accum to day  might one day be useful
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_above_ground" ,UED_period_sum, CSC, CSV_removed_canopy);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_non_yield"    ,UED_period_sum, CSC, CSV_removed_non_yield);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_residue"      ,UED_period_sum, CSC, CSV_removed_residue);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_grazing"      ,UED_period_sum, CSC, CSV_removed_grazing);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"roots_live"            ,UED_period_sum, CSC, CSV_crop_roots_live);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"roots_dead"            ,UED_period_sum, CSC, CSV_crop_roots_dead);
      // Note: not currently outputing roots by layer

      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_grazing"      ,UED_total_for_time_step, CSC, CSV_removed_grazing);
      output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_residue"      ,UED_total_for_time_step, CSC, CSV_removed_residue);

   };
#ifdef OBSOLETE
Replaced with for loop
   // The following are used for harvest season (at time step)
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"yield"                   ,UED_at_time_step, CSC_crop_base, CSV_crop_base_yield);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"used_biomass" 		      ,UED_at_time_step, CSC_crop_base, CSV_crop_base_used_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"grazed_biomass" 		   ,UED_at_time_step, CSC_crop_base, CSV_crop_base_grazed_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residue_biomass" 		   ,UED_at_time_step, CSC_crop_base, CSV_crop_base_residue_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"disposed_biomass" 		   ,UED_at_time_step, CSC_crop_base, CSV_crop_base_disposed_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stubble_biomass" 		   ,UED_at_time_step, CSC_crop_base, CSV_crop_base_residue_stubble_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"live_biomass" 		      ,UED_at_time_step, CSC_crop_base, CSV_crop_base_live_biomass);


   // The following are used for growing season (period accum)
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"yield"                  ,UED_period_sum, CSC_crop_base, CSV_crop_base_yield);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"used_biomass" 		     ,UED_period_sum, CSC_crop_base, CSV_crop_base_used_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"grazed_biomass" 		  ,UED_period_sum, CSC_crop_base, CSV_crop_base_grazed_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residue_biomass" 		  ,UED_period_sum, CSC_crop_base, CSV_crop_base_residue_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"disposed_biomass" 		  ,UED_period_sum, CSC_crop_base, CSV_crop_base_disposed_biomass);

   // The following are used for annual report (UED_total_for_time_step where timestep is one year)
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"yield"                  ,UED_total_for_time_step, CSC_crop_base, CSV_crop_base_yield);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"used_biomass"           ,UED_total_for_time_step, CSC_crop_base, CSV_crop_base_used_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"grazed_biomass"         ,UED_total_for_time_step, CSC_crop_base, CSV_crop_base_grazed_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residue_biomass"        ,UED_total_for_time_step, CSC_crop_base, CSV_crop_base_residue_biomass);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"disposed_biomass"       ,UED_total_for_time_step, CSC_crop_base, CSV_crop_base_disposed_biomass);
#endif

   output_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"intercepted_PAR"        ,(nat32)(QUALIFIER_at_time_step|QUALIFIER_period_sum|QUALIFIER_accum_to_date), CSC_crop_base, CSV_crop_base_intercepted_PAR);
/* 070219 now use  output_variables
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"intercepted_PAR"        ,UED_at_time_step, CSC_crop_base, CSV_crop_base_intercepted_PAR);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"intercepted_PAR"        ,UED_period_sum, CSC_crop_base, CSV_crop_base_intercepted_PAR);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"intercepted_PAR"        ,UED_accum_to_date, CSC_crop_base, CSV_crop_base_intercepted_PAR);
*/
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"VPD_daytime"            ,UED_at_time_step, CSC_crop_base, CSV_crop_base_VPD);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"VPD_daytime"            ,UED_period_avg, CSC_crop_base, CSV_crop_base_VPD);

   output_comment(csvc_h,csvc_m,csvc_cs,"crop phosphorus" );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                  ,UED_total_for_time_step,CSC_crop_phosphorus_misc , CSV_crop_P_uptake);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                  ,UED_period_sum,         CSC_crop_phosphorus_misc , CSV_crop_P_uptake);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                  ,UED_accum_to_date,      CSC_crop_phosphorus_misc , CSV_crop_P_uptake);

   output_comment(csvc_h,csvc_m,csvc_cs,"crop nitrogen" );
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stress_factor"          ,UED_at_time_step,       CSC_crop_nitrogen_misc , CSV_crop_N_stress_factor);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stress_factor"          ,UED_period_avg,         CSC_crop_nitrogen_misc , CSV_crop_N_stress_factor);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stress_index"           ,UED_at_time_step,       CSC_crop_nitrogen_misc , CSV_crop_N_stress_index);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stress_index"           ,UED_period_avg,         CSC_crop_nitrogen_misc , CSV_crop_N_stress_index);


   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                  ,UED_total_for_time_step,CSC_crop_nitrogen_misc , CSV_crop_N_uptake);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                  ,UED_period_sum,         CSC_crop_nitrogen_misc , CSV_crop_N_uptake);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                  ,UED_accum_to_date,      CSC_crop_nitrogen_misc , CSV_crop_N_uptake);

//131007   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"above_ground_renamed"    ,UED_at_time_step,       CSC_crop_nitrogen_misc , CSV_crop_N_mass_canopy);
//131007   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"above_ground_renamed"    ,UED_period_sum,         CSC_crop_nitrogen_misc , CSV_crop_N_mass_canopy);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mass_canopy_production"  ,UED_accum_to_date,      CSC_crop_nitrogen_misc , CSV_crop_N_mass_canopy_production);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mass_canopy_current"     ,UED_at_time_step,      CSC_crop_nitrogen_misc , CSV_crop_N_mass_canopy_current);
   //110917 output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"canopy_assimilation"     ,UED_accum_to_date,      CSC_crop_nitrogen_misc , CSV_crop_N_mass_canopy);

//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"yield"                   ,UED_at_time_step,       CSC_crop_nitrogen_misc , CSV_crop_N_yield); //120117

   output_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"canopy_gaseous_loss"      ,(nat32)(QUALIFIER_at_time_step|QUALIFIER_period_sum|QUALIFIER_accum_to_date),      CSC_crop_nitrogen_misc , CSV_crop_N_canopy_gaseous_loss);

/*070206 obsolete now using
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"concentration"          ,UED_at_time_step,       CSC_crop_nitrogen , CSV_crop_N_plant_concentration_obsolete);
*/
/*070206 OBSOLETE Now using  CSC_crop_nitrogen_conc CSV_canopy and  CSV_crop_root_live
  generated in the loop CSC above
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"canopy_concentration"   ,UED_at_time_step,       CSC_crop_nitrogen , CSV_crop_N_canopy_concentration);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"root_concentration"     ,UED_at_time_step,       CSC_crop_nitrogen , CSV_crop_N_root_concentration);
*/
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"automatic_uptake"       ,UED_total_for_time_step ,CSC_crop_nitrogen_misc , CSV_crop_N_automatic_uptake);// 71
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"automatic_uptake"       ,UED_period_sum          ,CSC_crop_nitrogen_misc , CSV_crop_N_automatic_uptake);// 72
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"automatic_uptake"       ,UED_accum_to_date       ,CSC_crop_nitrogen_misc , CSV_crop_N_automatic_uptake);// 72
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fixation"               ,UED_at_time_step        ,CSC_crop_nitrogen_misc , CSV_crop_N_fixation);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fixation"               ,UED_total_for_time_step ,CSC_crop_nitrogen_misc , CSV_crop_N_fixation);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fixation"               ,UED_period_sum          ,CSC_crop_nitrogen_misc , CSV_crop_N_fixation);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fixation"               ,UED_accum_to_date       ,CSC_crop_nitrogen_misc , CSV_crop_N_fixation);
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fixation_GP"            ,UED_period_accum,       CSC_crop_nitrogen_misc , CSV_crop_N_fixation);
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fixation_AN"            ,UED_accum_to_date,      CSC_crop_nitrogen_misc , CSV_crop_N_fixation);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_mature_conc_ratio",UED_at_time_step    ,CSC_crop_nitrogen_misc,CSV_crop_N_flower_mature_conc_ratio);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake_excess_or_deficit",UED_at_time_step    ,CSC_crop_nitrogen_misc,CSV_crop_N_uptake_excess_or_deficit);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"min"      ,UED_at_time_step,       CSC_crop_nitrogen_conc , CSV_minimum);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"max"      ,UED_at_time_step,       CSC_crop_nitrogen_conc , CSV_maximum);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"critical" ,UED_at_time_step,       CSC_crop_nitrogen_conc , CSV_critical);
/* 070206 replaced with above
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"min_concentration"      ,UED_at_time_step,       CSC_crop_nitrogen , CSV_crop_N_min_concentration);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"max_concentration"      ,UED_at_time_step,       CSC_crop_nitrogen , CSV_crop_N_max_concentration);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"critical_concentration" ,UED_at_time_step,       CSC_crop_nitrogen , CSV_crop_N_critical_concentration);
*/
   output_comment(csvc_h,csvc_m,csvc_cs,"crop carbon" );
//NYN   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"assimilation_plant"                   ,UED_total_for_time_step,CSC_crop_carbon,CSV_crop_C_assimilation_total_plant);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"canopy"                  ,UED_total_for_time_step,CSC_crop_carbon_mass,CSV_canopy);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"roots_live"              ,UED_total_for_time_step,CSC_crop_carbon_mass,CSV_crop_roots_live);
/*070206 replaced with above
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"assimilation_plant"                   ,UED_total_for_time_step,CSC_crop_carbon,CSV_crop_C_assimilation_total_plant);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"assimilation_above_ground"            ,UED_total_for_time_step,CSC_crop_carbon,CSV_crop_C_assimilation_above_ground);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"assimilation_roots"                   ,UED_total_for_time_step,CSC_crop_carbon,CSV_crop_C_assimilation_root);
*/
   output_comment(csvc_h,csvc_m,csvc_cs,"Residue");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"ground_cover"            ,UED_at_time_step       ,CSC_residue,CSV_residue_ground_cover);// 16
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_storage"           ,UED_at_time_step       ,CSC_residue,CSV_residue_water_storage);// 17
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_biomass"         ,UED_at_time_step       ,CSC_residue,CSV_residue_surface_biomass);// 18
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot_evap"                ,UED_total_for_time_step,CSC_residue,CSV_residue_pot_evap);// 28
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot_evap"                ,UED_accum_to_date      ,CSC_residue,CSV_residue_pot_evap);// 43
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot_evap"                ,UED_period_sum         ,CSC_residue,CSV_residue_pot_evap);// 43
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act_evap"                ,UED_total_for_time_step,CSC_residue,CSV_residue_act_evap);// 29
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act_evap"                ,UED_accum_to_date      ,CSC_residue,CSV_residue_act_evap);// 44
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act_evap"                ,UED_period_sum         ,CSC_residue,CSV_residue_act_evap);// 44
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"           ,UED_total_for_time_step,CSC_residue,CSV_residue_water_inter);// 33
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"           ,UED_accum_to_date      ,CSC_residue,CSV_residue_water_inter);// 48
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"           ,UED_period_sum         ,CSC_residue,CSV_residue_water_inter);// 48
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"             ,UED_total_for_time_step,CSC_residue,CSV_residue_mineralizated);// 65
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"             ,UED_accum_to_date      ,CSC_residue,CSV_residue_mineralizated);// 66
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"             ,UED_period_sum         ,CSC_residue,CSV_residue_mineralizated);// 66
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated"             ,UED_at_time_step       ,CSC_residue,CSV_residue_incorporated);

   output_comment(csvc_h,csvc_m,csvc_cs,"Plant residue");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface"    		         ,UED_at_time_step       ,CSC_residue_plant,CSV_residue_plant_surface_BM);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flat"    		            ,UED_at_time_step       ,CSC_residue_plant,CSV_residue_plant_surface_flat_BM);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stubble"    		         ,UED_at_time_step       ,CSC_residue_plant,CSV_residue_plant_surface_stubble_BM);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated"             ,UED_at_time_step       ,CSC_residue_plant,CSV_residue_plant_incorporated);

   output_comment(csvc_h,csvc_m,csvc_cs,"Manure");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"             ,UED_total_for_time_step,CSC_residue_manure,CSV_residue_manure_mineralizated);// 67
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"             ,UED_accum_to_date      ,CSC_residue_manure,CSV_residue_manure_mineralizated);// 68
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"             ,UED_period_sum         ,CSC_residue_manure,CSV_residue_manure_mineralizated);// 68
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface"    				   ,UED_at_time_step       ,CSC_residue_manure,CSV_residue_manure_surface_BM);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated"             ,UED_at_time_step       ,CSC_residue_manure,CSV_residue_manure_incorporated);// 19

   output_comment(csvc_h,csvc_m,csvc_cs,"Weather");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"precipitation"           ,UED_total_for_time_step ,CSC_weather,CSV_weather_precipitation);// 31
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"precipitation"           ,UED_accum_to_date       ,CSC_weather,CSV_weather_precipitation);// 46
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"precipitation"           ,UED_period_sum       ,CSC_weather,CSV_weather_precipitation);// 46
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"snow_storage"            ,UED_at_time_step        ,CSC_weather,CSV_weather_snow_storage);// 52
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature"             ,UED_time_step_min       ,CSC_weather,CSV_weather_air_temperature);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature"             ,UED_time_step_max       ,CSC_weather,CSV_weather_air_temperature);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature"             ,UED_time_step_avg       ,CSC_weather,CSV_weather_air_temperature); //160324
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"solar_radiation"         ,UED_at_time_step/*<-check*/,CSC_weather,CSV_weather_solar_radiation);

   output_comment(csvc_h,csvc_m,csvc_cs,"Weather date");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"year_day"               ,UED_at_time_step        ,CSC_weather_date,CSV_weather_date_year_day);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"year"                   ,UED_at_time_step        ,CSC_weather_date,CSV_weather_date_year);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"DOY"                    ,UED_at_time_step        ,CSC_weather_date,CSV_weather_date_DOY);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"month"                  ,UED_at_time_step        ,CSC_weather_date,CSV_weather_date_month);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"DOM"                    ,UED_at_time_step        ,CSC_weather_date,CSV_weather_date_DOM);

   output_comment(csvc_h,csvc_m,csvc_cs,"ET");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot"                    ,UED_total_for_time_step ,CSC_weather_ET,CSV_weather_ET_pot);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act"                    ,UED_total_for_time_step ,CSC_weather_ET,CSV_weather_ET_act);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot"                    ,UED_accum_to_date       ,CSC_weather_ET,CSV_weather_ET_pot);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act"                    ,UED_accum_to_date       ,CSC_weather_ET,CSV_weather_ET_act);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot"                    ,UED_period_sum          ,CSC_weather_ET,CSV_weather_ET_pot);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act"                    ,UED_period_sum          ,CSC_weather_ET,CSV_weather_ET_act);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"ref"                    ,UED_total_for_time_step ,CSC_weather_ET,CSV_weather_ET_ref_short);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"ref"                    ,UED_accum_to_date       ,CSC_weather_ET,CSV_weather_ET_ref_short);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"ref"                    ,UED_period_sum          ,CSC_weather_ET,CSV_weather_ET_ref_short);



   output_comment(csvc_h,csvc_m,csvc_cs,"Soil base ");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_pot"               ,UED_total_for_time_step ,CSC_soil_base,CSV_soil_base_evap_pot);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_pot"               ,UED_accum_to_date       ,CSC_soil_base,CSV_soil_base_evap_pot);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_pot"               ,UED_period_sum          ,CSC_soil_base,CSV_soil_base_evap_pot);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_act"               ,UED_total_for_time_step ,CSC_soil_base,CSV_soil_base_evap_act);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_act"               ,UED_accum_to_date       ,CSC_soil_base,CSV_soil_base_evap_act);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_act"               ,UED_period_sum          ,CSC_soil_base,CSV_soil_base_evap_act);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_entering"         ,UED_total_for_time_step ,CSC_soil_base,CSV_soil_base_water_entering);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_entering"         ,UED_accum_to_date       ,CSC_soil_base,CSV_soil_base_water_entering);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_entering"         ,UED_period_sum          ,CSC_soil_base,CSV_soil_base_water_entering);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_drainage"         ,UED_total_for_time_step ,CSC_soil_base,CSV_soil_base_water_drainage);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_drainage"         ,UED_accum_to_date       ,CSC_soil_base,CSV_soil_base_water_drainage);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_drainage"         ,UED_period_sum          ,CSC_soil_base,CSV_soil_base_water_drainage);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_depletion_balance",UED_accum_to_date       ,CSC_soil_base,CSV_soil_base_water_depletion_balance);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_depletion_seasonal",UED_period_sum       ,CSC_soil_base,CSV_soil_base_water_depletion_seasonal);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_balance"          ,UED_accum_to_date       ,CSC_soil_base,CSV_soil_base_water_balance);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_balance"          ,UED_total_for_time_step ,CSC_soil_base,CSV_soil_base_water_balance);
//   csvc_h << std::endl <<"#define CSCV_soil_thickness                       0x" << itoa(CS_UED_compose_var_code(UED_at_time_step       ,CS_PROP(CSC_soil_base,CSV_soil_thickness)),hex_buf,16);

//   csvc_h << std::endl << "//Chemical soil" << std::endl;

//   csvc_h << std::endl << "//FD soil" << std::endl;

   output_comment(csvc_h,csvc_m,csvc_cs,"soil erosion");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"clod_rate"              ,UED_at_time_step       ,CSC_soil_erosion,CSV_soil_erosion_clod_rate);// 20
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"loss"                   ,UED_total_for_time_step,CSC_soil_erosion,CSV_soil_erosion_loss);// 21
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"loss"                   ,UED_period_sum,CSC_soil_erosion,CSV_soil_erosion_loss);// 21
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"index"                  ,UED_period_sum,CSC_soil_erosion ,CSV_soil_erosion_index); // not sure if average or sum
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"RUSLE_C_factor"         ,UED_total_for_time_step,CSC_soil_erosion,CSV_soil_RUSLE_C_factor);

   output_comment(csvc_h,csvc_m,csvc_cs,"soil runoff");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_water_runoff"   ,UED_total_for_time_step,CSC_soil_runoff,CSV_soil_runoff_surface_water_runoff);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_water_runoff"   ,UED_accum_to_date      ,CSC_soil_runoff,CSV_soil_runoff_surface_water_runoff);// 49
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_water_runoff"   ,UED_period_sum      ,CSC_soil_runoff,CSV_soil_runoff_surface_water_runoff);// 49
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_water_runon"    ,UED_total_for_time_step,CSC_soil_runoff,CSV_soil_runoff_surface_water_runon);

   output_comment(csvc_h,csvc_m,csvc_cs,"soil carbon mass");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_surface"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_surface);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_profile"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_5cm"                ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_10cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_15cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_30cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_60cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_90cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_soil_carbon_90cm);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_profile"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_SOM_C_mass_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_5cm"                ,UED_at_time_step,CSC_soil_carbon_mass,CSV_SOM_C_mass_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_10cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_SOM_C_mass_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_15cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_SOM_C_mass_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_30cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_SOM_C_mass_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_60cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_SOM_C_mass_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_90cm"               ,UED_at_time_step,CSC_soil_carbon_mass,CSV_SOM_C_mass_90cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_profile"      ,UED_at_time_step,CSC_soil_carbon_mass,CSV_microbial_C_mass_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_5cm"          ,UED_at_time_step,CSC_soil_carbon_mass,CSV_microbial_C_mass_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_10cm"         ,UED_at_time_step,CSC_soil_carbon_mass,CSV_microbial_C_mass_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_15cm"         ,UED_at_time_step,CSC_soil_carbon_mass,CSV_microbial_C_mass_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_30cm"         ,UED_at_time_step,CSC_soil_carbon_mass,CSV_microbial_C_mass_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_60cm"         ,UED_at_time_step,CSC_soil_carbon_mass,CSV_microbial_C_mass_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_90cm"         ,UED_at_time_step,CSC_soil_carbon_mass,CSV_microbial_C_mass_90cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_profile"         ,UED_at_time_step,CSC_soil_carbon_mass,CSV_labile_C_mass_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_5cm"             ,UED_at_time_step,CSC_soil_carbon_mass,CSV_labile_C_mass_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_10cm"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_labile_C_mass_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_15cm"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_labile_C_mass_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_30cm"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_labile_C_mass_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_60cm"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_labile_C_mass_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_90cm"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_labile_C_mass_90cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_profile"     ,UED_at_time_step,CSC_soil_carbon_mass,CSV_metastable_C_mass_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_5cm"         ,UED_at_time_step,CSC_soil_carbon_mass,CSV_metastable_C_mass_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_10cm"        ,UED_at_time_step,CSC_soil_carbon_mass,CSV_metastable_C_mass_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_15cm"        ,UED_at_time_step,CSC_soil_carbon_mass,CSV_metastable_C_mass_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_30cm"        ,UED_at_time_step,CSC_soil_carbon_mass,CSV_metastable_C_mass_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_60cm"        ,UED_at_time_step,CSC_soil_carbon_mass,CSV_metastable_C_mass_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_90cm"        ,UED_at_time_step,CSC_soil_carbon_mass,CSV_metastable_C_mass_90cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_profile"        ,UED_at_time_step,CSC_soil_carbon_mass,CSV_passive_C_mass_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_5cm"            ,UED_at_time_step,CSC_soil_carbon_mass,CSV_passive_C_mass_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_10cm"           ,UED_at_time_step,CSC_soil_carbon_mass,CSV_passive_C_mass_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_15cm"           ,UED_at_time_step,CSC_soil_carbon_mass,CSV_passive_C_mass_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_30cm"           ,UED_at_time_step,CSC_soil_carbon_mass,CSV_passive_C_mass_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_60cm"           ,UED_at_time_step,CSC_soil_carbon_mass,CSV_passive_C_mass_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_90cm"           ,UED_at_time_step,CSC_soil_carbon_mass,CSV_passive_C_mass_90cm);

// NYN
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_surface"  ,UED_at_time_step,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_surface);
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_profile"  ,UED_at_time_step,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_profile);
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_5cm"      ,UED_at_time_step,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_5cm);
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_30cm"     ,UED_at_time_step,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_30cm);
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_60cm"     ,UED_at_time_step,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_60cm);
//   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_90cm"     ,UED_at_time_step,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_90cm);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_surface"  ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_surface);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_profile"  ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_5cm"      ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_10cm"     ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_15cm"     ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_30cm"     ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_60cm"     ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_90cm"     ,UED_at_time_step     ,CSC_soil_carbon_mass,CSV_residue_C_mass_90cm);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_surface"  ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_surface);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_profile"  ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_5cm"      ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_10cm"     ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_15cm"     ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_30cm"     ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_60cm"     ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_90cm"     ,UED_minimum_for_time_step,CSC_soil_carbon_mass,CSV_residue_C_mass_90cm);


// renamed to xxx_profile   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_subsurface" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_subsurface);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_profile" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_subsurface);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_5cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_10cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_15cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_30cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_60cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_90cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_90cm);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_flat"       ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_flat);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_stubble"    ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_stubble);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_attached"   ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_residue_attached);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated_by_tillage"       ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_incorporated_by_tillage);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_by_harvest"            ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_removed_by_harvest);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_profile" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_5cm"  ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_10cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_15cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_30cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_60cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_90cm" ,UED_total_for_time_step,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_90cm);

   output_comment(csvc_h,csvc_m,csvc_cs,"soil nitrogen");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leached"                ,UED_total_for_time_step,CSC_soil_nitrogen,CSV_soil_N_leached);// 59
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leached"                ,UED_accum_to_date      ,CSC_soil_nitrogen,CSV_soil_N_leached);// 63
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leached"                ,UED_average_for_period ,CSC_soil_nitrogen,CSV_soil_N_leached);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leached"                ,UED_period_sum         ,CSC_soil_nitrogen,CSV_soil_N_leached);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"available"              ,UED_period_sum         ,CSC_soil_nitrogen,CSV_soil_N_available);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NH3_volatilization"     ,UED_total_for_time_step,CSC_soil_nitrogen,CSV_soil_NH3_volatilization);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NH3_volatilization"     ,UED_accum_to_date      ,CSC_soil_nitrogen,CSV_soil_NH3_volatilization);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NH3_volatilization"     ,UED_period_sum         ,CSC_soil_nitrogen,CSV_soil_NH3_volatilization);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"volatilization_total"     ,UED_total_for_time_step,CSC_soil_nitrogen,CSV_soil_volatilization_total); //131001


   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_denitrification"     ,UED_total_for_time_step,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_denitrification);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_denitrification"     ,UED_accum_to_date      ,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_denitrification);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_denitrification"     ,UED_period_sum         ,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_denitrification);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_nitrification"     ,UED_total_for_time_step,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_nitrification);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_nitrification"     ,UED_accum_to_date      ,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_nitrification);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_nitrification"     ,UED_period_sum         ,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_nitrification);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"input"                  ,UED_total_for_time_step,CSC_soil_nitrogen,CSV_soil_N_input);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"input"                  ,UED_accum_to_date      ,CSC_soil_nitrogen,CSV_soil_N_input);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"input"                  ,UED_period_sum         ,CSC_soil_nitrogen,CSV_soil_N_input);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"output"                 ,UED_total_for_time_step,CSC_soil_nitrogen,CSV_soil_N_output);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"output"                 ,UED_accum_to_date      ,CSC_soil_nitrogen,CSV_soil_N_output);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"output"                 ,UED_period_sum         ,CSC_soil_nitrogen,CSV_soil_N_output);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization"        ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization"        ,UED_accum_to_date,CSC_soil_nitrogen ,CSV_soil_N_immobilization);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization"        ,UED_period_sum,CSC_soil_nitrogen ,CSV_soil_N_immobilization);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_profile"  ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_5cm"      ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_10cm"     ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_15cm"     ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_30cm"     ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_60cm"     ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_90cm"     ,UED_total_for_time_step,CSC_soil_nitrogen ,CSV_soil_N_immobilization_90cm);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_profile"  ,UED_total_for_time_step,CSC_organic_matter ,CSV_N_mineralization_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_5cm"      ,UED_total_for_time_step,CSC_organic_matter ,CSV_N_mineralization_5cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_10cm"     ,UED_total_for_time_step,CSC_organic_matter ,CSV_N_mineralization_10cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_15cm"     ,UED_total_for_time_step,CSC_organic_matter ,CSV_N_mineralization_15cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_30cm"     ,UED_total_for_time_step,CSC_organic_matter ,CSV_N_mineralization_30cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_60cm"     ,UED_total_for_time_step,CSC_organic_matter ,CSV_N_mineralization_60cm);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_90cm"     ,UED_total_for_time_step,CSC_organic_matter ,CSV_N_mineralization_90cm);

//NYI   output_comment(csvc_h,csvc_m,csvc_cs,"Freezing soil");

//NYI   output_comment(csvc_h,csvc_m,csvc_cs,"Complete soil");

   output_comment(csvc_h,csvc_m,csvc_cs,"Soil pond");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_depth"            ,UED_at_time_step,      CSC_soil_pond    ,CSV_soil_pond_water_depth);

   output_comment(csvc_h,csvc_m,csvc_cs,"Water table");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"depth"      ,UED_at_time_step        ,CSC_water_table,CSV_water_table_depth);//


   output_comment(csvc_h,csvc_m,csvc_cs,"Management");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_total_for_time_step,CSC_management_irrigation,CSV_mgmt_irrigation);// 30
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_accum_to_date      ,CSC_management_irrigation,CSV_mgmt_irrigation);// 45
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_period_sum      ,CSC_management_irrigation,CSV_mgmt_irrigation);// 45

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"biomass_grazed"         ,UED_total_for_time_step,CSC_management,CSV_mgmt_biomass_grazed);// 30
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"biomass_grazed"         ,UED_accum_to_date      ,CSC_management,CSV_mgmt_biomass_grazed);// 45
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"biomass_unsatisfied"    ,UED_total_for_time_step,CSC_management,CSV_mgmt_biomass_unsatisfied);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"biomass_unsatisfied"    ,UED_accum_to_date      ,CSC_management,CSV_mgmt_biomass_unsatisfied);


   output_comment(csvc_h,csvc_m,csvc_cs,"Nitrogen management");
//incorrect   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_total_for_time_step,CSC_management_irrigation,CSV_mgmt_irrigation);// 30
//incorrect   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_accum_to_date      ,CSC_management_irrigation,CSV_mgmt_irrigation);// 45

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_total_for_time_step,CSC_management_N,CSV_mgmt_N_applied);// 57
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_accum_to_date      ,CSC_management_N,CSV_mgmt_N_applied);// 60
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_period_sum       ,CSC_management_N,CSV_mgmt_N_applied);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_total_for_time_step,CSC_management_P,CSV_mgmt_P_applied);// 57
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_accum_to_date      ,CSC_management_P,CSV_mgmt_P_applied);// 60
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                ,UED_period_sum       ,CSC_management_P,CSV_mgmt_P_applied);


   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_applied"        ,UED_total_for_time_step,CSC_management_N,CSV_mgmt_organic_N_applied);// 73
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_applied"        ,UED_accum_to_date      ,CSC_management_N,CSV_mgmt_organic_N_applied);// 74
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_applied"        ,UED_period_sum      ,CSC_management_N,CSV_mgmt_organic_N_applied);// 74


   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_gaseous_loss"   ,UED_total_for_time_step,CSC_management_N,CSV_mgmt_N_organic_gaseous_loss);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_gaseous_loss"   ,UED_accum_to_date      ,CSC_management_N,CSV_mgmt_N_organic_gaseous_loss);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_gaseous_loss"   ,UED_period_sum,CSC_management_N,CSV_mgmt_N_organic_gaseous_loss);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inorganic_gaseous_loss" ,UED_total_for_time_step,CSC_management_N,CSV_mgmt_N_inorganic_gaseous_loss);// 60
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inorganic_gaseous_loss" ,UED_accum_to_date      ,CSC_management_N,CSV_mgmt_N_inorganic_gaseous_loss);// 60
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inorganic_gaseous_loss" ,UED_period_sum      ,CSC_management_N,CSV_mgmt_N_inorganic_gaseous_loss);// 60

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"total_mineralization"   ,UED_total_for_time_step      ,CSC_miscellaneous_N,CSV_total_mineralization);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"total_mineralization"   ,UED_period_sum      ,CSC_miscellaneous_N,CSV_total_mineralization);


   //Layer variables________________________________________________________________________________________________________
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_content"         ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_base_water_content);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_avail_water"     ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_base_plant_avail_water);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_potential"       ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_water_potential);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"lateral_in_flow_depth" ,UED_total_for_time_step,CSC_soil_base      ,CSV_soil_lateral_in_flow_depth);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"lateral_out_flow_depth",UED_total_for_time_step,CSC_soil_base      ,CSV_soil_lateral_out_flow_depth);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature"           ,UED_time_step_avg,CSC_soil_base      ,CSV_soil_base_temperature);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NO3_amount"            ,UED_at_time_step,CSC_soil_nitrogen,CSV_soil_N_NO3_amount);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NH4_amount"            ,UED_at_time_step,CSC_soil_nitrogen,CSV_soil_N_NH4_amount);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_amount"              ,UED_at_time_step, CSC_soil_nitrogen,CSV_soil_N_amount);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralization"        ,UED_total_for_time_step,CSC_soil_nitrogen  ,CSV_soil_N_mineralization);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralization"        ,UED_period_sum,CSC_soil_nitrogen  ,CSV_soil_N_mineralization);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"nitrification"         ,UED_total_for_time_step,CSC_soil_nitrogen  ,CSV_soil_N_nitrification);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"denitrification"       ,UED_total_for_time_step,CSC_soil_nitrogen  ,CSV_soil_N_denitrification);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"nitrification"         ,UED_period_sum,CSC_soil_nitrogen  ,CSV_soil_N_nitrification); //110917
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"denitrification"       ,UED_period_sum,CSC_soil_nitrogen  ,CSV_soil_N_denitrification); //110917


   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"P_amount"              ,UED_at_time_step, CSC_soil_phosphorus,CSV_soil_P_amount);

   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"root_fraction"         ,UED_at_time_step ,CSC_crop_base      ,CSV_root_fraction);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"salinity"              ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_salinity);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"salt"                  ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_salt);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"CO2_C_loss_residue"     ,UED_total_for_time_step,CSC_organic_matter,CSV_gaseous_CO2_C_loss_residue);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"CO2_C_loss_SOM"         ,UED_total_for_time_step,CSC_organic_matter,CSV_gaseous_CO2_C_loss_SOM);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"CO2_C_loss_OM"          ,UED_total_for_time_step,CSC_organic_matter,CSV_gaseous_CO2_C_loss_total);

   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"          ,UED_total_for_time_step,CSC_organic_matter,CSV_N_mineralization_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"          ,UED_accum_to_date      ,CSC_organic_matter,CSV_N_mineralization_profile);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"          ,UED_period_sum         ,CSC_organic_matter,CSV_N_mineralization_profile);
   output_layer_variables(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"percent"               ,UED_total_for_time_step,CSC_organic_matter,CSV_organic_matter_percent);

   output_comment(csvc_h,csvc_m,csvc_cs,"Soil profile vectors");
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"field_capacity"           ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_field_capacity);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"permanent_wilt_point"     ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_permanent_wilt_point);
   output_variable(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"saturation_water_content" ,UED_at_time_step ,CSC_soil_base      ,CSV_soil_saturation_water_content);

   // Variable Property codes
   output_comment(csvc_h,csvc_m,csvc_cs,"Variable Property codes_________________________________________");

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"growing_degree_days"                 ,CSC_crop_base, CSV_crop_base_growing_degree_days);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"seasonal_thermal_time"               ,CSC_crop_base, CSV_crop_seasonal_thermal_time);  // may need to be accum to day

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"season_duration"                     ,CSC_crop_base, CSV_crop_season_duration);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"dry_biomass_deprecate"               ,CSC_crop_base, CSV_crop_base_sum_daily_canopy_biomass_deprecate);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"root_biomass_current"                ,CSC_crop_base, CSV_crop_base_root_biomass_deprecate);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"green_biomass"                       ,CSC_crop_base, CSV_crop_base_green_biomass);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fruit_biomass"                       ,CSC_crop_base, CSV_crop_fruit_biomass);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fruit_canopy_biomass"                ,CSC_crop_base, CSV_crop_fruit_canopy_biomass);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"orchard_solid_canopy_interception"   ,CSC_crop_base, CSV_orchard_solid_canopy_interception);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"orchard_shaded_area_GAI "            ,CSC_crop_base, CSV_orchard_shaded_area_GAI);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"orchard_canopy_porosity"             ,CSC_crop_base, CSV_canopy_porosity);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leaf_area_index"                     ,CSC_crop_base, CSV_crop_base_leaf_area_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"green_area_index"                    ,CSC_crop_base, CSV_crop_base_green_area_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"root_depth"                          ,CSC_crop_base, CSV_crop_base_root_depth);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_stress_factor"                 ,CSC_crop_base, CSV_crop_base_water_stress_factor );
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature_stress_factor"           ,CSC_crop_base,CSV_crop_base_temperature_stress_factor );
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_init_temp_stress_index"        ,CSC_crop_base,CSV_crop_base_tuber_init_temperature_stress_index );
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_fill_temp_stress_index"        ,CSC_crop_base,CSV_crop_base_tuber_filling_temperature_stress_index );
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_stress_index"                  ,CSC_crop_base, CSV_crop_base_water_stress_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature_stress_index"            ,CSC_crop_base, CSV_crop_base_temperature_stress_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_temperature_stress_index"     ,CSC_crop_base, CSV_crop_base_flower_temperature_stress_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_water_stress_index"           ,CSC_crop_base, CSV_crop_base_flower_water_stress_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_N_stress_index"               ,CSC_crop_base, CSV_crop_base_flower_N_stress_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"filling_duration_index"              ,CSC_crop_base, CSV_crop_base_filling_duration_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fract_canopy_cover"                  ,CSC_crop_base, CSV_crop_base_fract_canopy_cover);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leaf_water_pot"                      ,CSC_crop_base, CSV_crop_base_leaf_water_pot);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_pot"                          ,CSC_crop_base, CSV_crop_base_transp_pot);// 24
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"transp_act"                          ,CSC_crop_base, CSV_crop_base_transp_act);// 25
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"                       ,CSC_crop_base, CSV_crop_base_water_inter);// 32

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"growth_stage"                        ,CSC_crop_phenology, CSV_crop_phenology_growth_stage);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"planting_date_YMD"                   ,CSC_crop_phenology, CSV_crop_phenology_planting_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"emergence_date_YMD"                  ,CSC_crop_phenology, CSV_crop_phenology_emergence_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flowering_date_YMD"                  ,CSC_crop_phenology, CSV_crop_phenology_flowering_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_init_date_YMD"                 ,CSC_crop_phenology, CSV_crop_phenology_tuber_init_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"grain_filling_date_YMD"              ,CSC_crop_phenology, CSV_crop_phenology_grain_filling_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"peak_LAI_date_YMD"                   ,CSC_crop_phenology, CSV_crop_phenology_peak_LAI_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"maturity_date_YMD"                   ,CSC_crop_phenology, CSV_crop_phenology_maturity_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"harvest_date_YMD"                    ,CSC_crop_phenology, CSV_crop_phenology_harvest_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"restart_date_YMD"                    ,CSC_crop_phenology, CSV_crop_phenology_restart_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"bud_break_date_YMD"                  ,CSC_crop_phenology, CSV_crop_phenology_bud_break_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"initial_fruit_growth_date_YMD"       ,CSC_crop_phenology, CSV_crop_phenology_initial_fruit_growth_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"rapid_fruit_growth_date_YMD"         ,CSC_crop_phenology, CSV_crop_phenology_rapid_fruit_growth_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_begin_date_YMD"             ,CSC_crop_phenology, CSV_crop_phenology_inactive_begin_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_end_date_YMD"               ,CSC_crop_phenology, CSV_crop_phenology_inactive_end_date_YMD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"base_chill_requirement_satisfied_date_YMD"  ,CSC_crop_phenology, CSV_crop_phenology_chill_requirement_satisfied_date_YMD);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"planting_date_YD"                    ,CSC_crop_phenology, CSV_crop_phenology_planting_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"emergence_date_YD"                   ,CSC_crop_phenology, CSV_crop_phenology_emergence_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flowering_date_YD"                   ,CSC_crop_phenology, CSV_crop_phenology_flowering_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"tuber_init_date_YD"                  ,CSC_crop_phenology, CSV_crop_phenology_tuber_init_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"grain_filling_date_YD"               ,CSC_crop_phenology, CSV_crop_phenology_grain_filling_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"peak_LAI_date_YD"                    ,CSC_crop_phenology, CSV_crop_phenology_peak_LAI_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"maturity_date_YD"                    ,CSC_crop_phenology, CSV_crop_phenology_maturity_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"harvest_date_YD"                     ,CSC_crop_phenology, CSV_crop_phenology_harvest_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"restart_date_YD"                     ,CSC_crop_phenology, CSV_crop_phenology_restart_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"bud_break_date_YD"                   ,CSC_crop_phenology, CSV_crop_phenology_bud_break_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"initial_fruit_growth_date_YD"        ,CSC_crop_phenology, CSV_crop_phenology_initial_fruit_growth_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"rapid_fruit_growth_date_YD"          ,CSC_crop_phenology, CSV_crop_phenology_rapid_fruit_growth_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_begin_date_YD"              ,CSC_crop_phenology, CSV_crop_phenology_inactive_begin_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inactive_end_date_YD"                ,CSC_crop_phenology, CSV_crop_phenology_inactive_end_date_YD);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"chill_requirement_satisfied_date_YD" ,CSC_crop_phenology, CSV_crop_phenology_chill_requirement_satisfied_date_YD);


   for (nat32 CSC = CSC_crop_biomass; CSC <=CSC_crop_nitrogen_conc; CSC++)  // Eventually we could include carbon etc., but currently there are only a couple of carbon outputs
   {
      for (uint8 fate_index = 0; fate_index < FATE_INDEX_COUNT; fate_index++)
      {
         nat32 fate_bitmask = (1 << fate_index);
         output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,mass_fate_label_table[fate_index], CSC, fate_bitmask);
      }
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"remain_canopy"        , CSC, CSV_canopy);  // This is the current canopy
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"removed_canopy"       , CSC, CSV_removed_canopy);
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"removed_non_yield"    , CSC, CSV_removed_non_yield);
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"removed_residue"      , CSC, CSV_removed_residue);
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"removed_grazing"      , CSC, CSV_removed_grazing);
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"roots_live"           , CSC, CSV_crop_roots_live);
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"roots_dead"           , CSC, CSV_crop_roots_dead);
      // Note: not currently outputing roots by layer
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"produced_above_ground", CSC, CSV_canopy);
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"removed_above_ground" , CSC, CSV_removed_canopy);
      // Note: not currently outputing roots by layer
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"removed_grazing"      , CSC, CSV_removed_grazing);
      output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc            ,"removed_residue"      , CSC, CSV_removed_residue);
   }
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"intercepted_PAR"                     , CSC_crop_base, CSV_crop_base_intercepted_PAR);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"VPD_daytime"                         , CSC_crop_base, CSV_crop_base_VPD);
   output_comment(csvc_h,csvc_m,csvc_cs,"crop phosphorus" );
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                              ,CSC_crop_phosphorus_misc , CSV_crop_P_uptake);
   output_comment(csvc_h,csvc_m,csvc_cs,"crop nitrogen" );
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stress_factor"                       ,CSC_crop_nitrogen_misc , CSV_crop_N_stress_factor);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stress_index"                        ,CSC_crop_nitrogen_misc , CSV_crop_N_stress_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake"                              ,CSC_crop_nitrogen_misc , CSV_crop_N_uptake);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mass_canopy_production"              ,CSC_crop_nitrogen_misc , CSV_crop_N_mass_canopy_production);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mass_canopy_current"                         ,CSC_crop_nitrogen_misc , CSV_crop_N_mass_canopy_current); //131007
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"canopy_gaseous_loss"                 ,CSC_crop_nitrogen_misc , CSV_crop_N_canopy_gaseous_loss);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"automatic_uptake"                    ,CSC_crop_nitrogen_misc , CSV_crop_N_automatic_uptake);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"fixation"                            ,CSC_crop_nitrogen_misc , CSV_crop_N_fixation);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flower_mature_conc_ratio"            ,CSC_crop_nitrogen_misc,CSV_crop_N_flower_mature_conc_ratio);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"uptake_excess_or_deficit"            ,CSC_crop_nitrogen_misc,CSV_crop_N_uptake_excess_or_deficit);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"min"                                 ,CSC_crop_nitrogen_conc , CSV_minimum);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"max"                                 ,CSC_crop_nitrogen_conc , CSV_maximum);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"critical"                            ,CSC_crop_nitrogen_conc , CSV_critical);
   output_comment(csvc_h,csvc_m,csvc_cs,"crop carbon" );
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"canopy"                              ,CSC_crop_carbon_mass,CSV_canopy);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"roots_live"                          ,CSC_crop_carbon_mass,CSV_crop_roots_live);
   output_comment(csvc_h,csvc_m,csvc_cs,"Residue");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"ground_cover"                        ,CSC_residue,CSV_residue_ground_cover);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_storage"                       ,CSC_residue,CSV_residue_water_storage);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_biomass"                     ,CSC_residue,CSV_residue_surface_biomass);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot_evap"                            ,CSC_residue,CSV_residue_pot_evap);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act_evap"                            ,CSC_residue,CSV_residue_act_evap);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_intrcpt"                       ,CSC_residue,CSV_residue_water_inter);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"                         ,CSC_residue,CSV_residue_mineralizated);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated"                  ,CSC_residue,CSV_residue_incorporated);
   output_comment(csvc_h,csvc_m,csvc_cs,"Plant residue");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface"    		                     ,CSC_residue_plant,CSV_residue_plant_surface_BM);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"flat"    		                        ,CSC_residue_plant,CSV_residue_plant_surface_flat_BM);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"stubble"    		                     ,CSC_residue_plant,CSV_residue_plant_surface_stubble_BM);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated"                  ,CSC_residue_plant,CSV_residue_plant_incorporated);

   output_comment(csvc_h,csvc_m,csvc_cs,"Manure");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"                         ,CSC_residue_manure,CSV_residue_manure_mineralizated);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface"    				               ,CSC_residue_manure,CSV_residue_manure_surface_BM);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated"                  ,CSC_residue_manure,CSV_residue_manure_incorporated);

   output_comment(csvc_h,csvc_m,csvc_cs,"Weather");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"precipitation"                       ,CSC_weather,CSV_weather_precipitation);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"snow_storage"                        ,CSC_weather,CSV_weather_snow_storage);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature"                         ,CSC_weather,CSV_weather_air_temperature);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"solar_radiation"                     ,CSC_weather,CSV_weather_solar_radiation);

   output_comment(csvc_h,csvc_m,csvc_cs,"Weather date");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"year_day"                            ,CSC_weather_date,CSV_weather_date_year_day);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"year"                                ,CSC_weather_date,CSV_weather_date_year);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"DOY"                                 ,CSC_weather_date,CSV_weather_date_DOY);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"month"                               ,CSC_weather_date,CSV_weather_date_month);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"DOM"                                 ,CSC_weather_date,CSV_weather_date_DOM);

   output_comment(csvc_h,csvc_m,csvc_cs,"ET");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"pot"                                 ,CSC_weather_ET,CSV_weather_ET_pot);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"act"                                 ,CSC_weather_ET,CSV_weather_ET_act);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"ref"                                 ,CSC_weather_ET,CSV_weather_ET_ref_short);

   output_comment(csvc_h,csvc_m,csvc_cs,"Soil base ");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_pot"                            ,CSC_soil_base,CSV_soil_base_evap_pot);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"evap_act"                            ,CSC_soil_base,CSV_soil_base_evap_act);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_entering"                      ,CSC_soil_base,CSV_soil_base_water_entering);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_drainage"                      ,CSC_soil_base,CSV_soil_base_water_drainage);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_depletion_balance"             ,CSC_soil_base,CSV_soil_base_water_depletion_balance);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_depletion_seasonal"            ,CSC_soil_base,CSV_soil_base_water_depletion_seasonal);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_balance"                       ,CSC_soil_base,CSV_soil_base_water_balance);



   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"clod_rate"                           ,CSC_soil_erosion,CSV_soil_erosion_clod_rate);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"loss"                                ,CSC_soil_erosion,CSV_soil_erosion_loss);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"loss"                                ,CSC_soil_erosion,CSV_soil_erosion_loss);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"index"                               ,CSC_soil_erosion ,CSV_soil_erosion_index);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"RUSLE_C_factor"                      ,CSC_soil_erosion,CSV_soil_RUSLE_C_factor);


   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_water_runoff"                ,CSC_soil_runoff,CSV_soil_runoff_surface_water_runoff);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"surface_water_runon"                 ,CSC_soil_runoff,CSV_soil_runoff_surface_water_runon);


   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_surface"                         ,CSC_soil_carbon_mass,CSV_soil_carbon_surface);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_profile"                         ,CSC_soil_carbon_mass,CSV_soil_carbon_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_5cm"                             ,CSC_soil_carbon_mass,CSV_soil_carbon_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_10cm"                            ,CSC_soil_carbon_mass,CSV_soil_carbon_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_15cm"                            ,CSC_soil_carbon_mass,CSV_soil_carbon_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_30cm"                            ,CSC_soil_carbon_mass,CSV_soil_carbon_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_60cm"                            ,CSC_soil_carbon_mass,CSV_soil_carbon_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"all_90cm"                            ,CSC_soil_carbon_mass,CSV_soil_carbon_90cm);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_profile"                         ,CSC_soil_carbon_mass,CSV_SOM_C_mass_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_5cm"                             ,CSC_soil_carbon_mass,CSV_SOM_C_mass_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_10cm"                            ,CSC_soil_carbon_mass,CSV_SOM_C_mass_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_15cm"                            ,CSC_soil_carbon_mass,CSV_SOM_C_mass_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_30cm"                            ,CSC_soil_carbon_mass,CSV_SOM_C_mass_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_60cm"                            ,CSC_soil_carbon_mass,CSV_SOM_C_mass_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"SOM_90cm"                            ,CSC_soil_carbon_mass,CSV_SOM_C_mass_90cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_profile"                   ,CSC_soil_carbon_mass,CSV_microbial_C_mass_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_5cm"                       ,CSC_soil_carbon_mass,CSV_microbial_C_mass_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_10cm"                      ,CSC_soil_carbon_mass,CSV_microbial_C_mass_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_15cm"                      ,CSC_soil_carbon_mass,CSV_microbial_C_mass_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_30cm"                      ,CSC_soil_carbon_mass,CSV_microbial_C_mass_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_60cm"                      ,CSC_soil_carbon_mass,CSV_microbial_C_mass_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"microbial_90cm"                      ,CSC_soil_carbon_mass,CSV_microbial_C_mass_90cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_profile"                      ,CSC_soil_carbon_mass,CSV_labile_C_mass_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_5cm"                          ,CSC_soil_carbon_mass,CSV_labile_C_mass_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_10cm"                         ,CSC_soil_carbon_mass,CSV_labile_C_mass_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_15cm"                         ,CSC_soil_carbon_mass,CSV_labile_C_mass_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_30cm"                         ,CSC_soil_carbon_mass,CSV_labile_C_mass_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_60cm"                         ,CSC_soil_carbon_mass,CSV_labile_C_mass_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"labile_90cm"                         ,CSC_soil_carbon_mass,CSV_labile_C_mass_90cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_profile"                  ,CSC_soil_carbon_mass,CSV_metastable_C_mass_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_5cm"                      ,CSC_soil_carbon_mass,CSV_metastable_C_mass_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_10cm"                     ,CSC_soil_carbon_mass,CSV_metastable_C_mass_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_15cm"                     ,CSC_soil_carbon_mass,CSV_metastable_C_mass_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_30cm"                     ,CSC_soil_carbon_mass,CSV_metastable_C_mass_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_60cm"                     ,CSC_soil_carbon_mass,CSV_metastable_C_mass_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"metastable_90cm"                     ,CSC_soil_carbon_mass,CSV_metastable_C_mass_90cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_profile"                     ,CSC_soil_carbon_mass,CSV_passive_C_mass_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_5cm"                         ,CSC_soil_carbon_mass,CSV_passive_C_mass_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_10cm"                        ,CSC_soil_carbon_mass,CSV_passive_C_mass_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_15cm"                        ,CSC_soil_carbon_mass,CSV_passive_C_mass_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_30cm"                        ,CSC_soil_carbon_mass,CSV_passive_C_mass_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_60cm"                        ,CSC_soil_carbon_mass,CSV_passive_C_mass_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"passive_90cm"                        ,CSC_soil_carbon_mass,CSV_passive_C_mass_90cm);

// NYN
//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_surface"                ,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_surface);
//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_profile"                  ,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_profile);
//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_5cm"                    ,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_5cm);
//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_30cm"                   ,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_30cm);
//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_60cm"                   ,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_60cm);
//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_residue_90cm"                   ,CSC_soil_carbon_mass,CSV_plant_residue_C_mass_90cm);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_surface"                    ,CSC_soil_carbon_mass,CSV_residue_C_mass_surface);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_profile"                    ,CSC_soil_carbon_mass,CSV_residue_C_mass_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_5cm"                        ,CSC_soil_carbon_mass,CSV_residue_C_mass_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_10cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_15cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_30cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_60cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_90cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_90cm);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_surface"                    ,CSC_soil_carbon_mass,CSV_residue_C_mass_surface);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_profile"                    ,CSC_soil_carbon_mass,CSV_residue_C_mass_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_5cm"                        ,CSC_soil_carbon_mass,CSV_residue_C_mass_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_10cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_15cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_30cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_60cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"residues_90cm"                       ,CSC_soil_carbon_mass,CSV_residue_C_mass_90cm);


   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_profile"          ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_subsurface);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_5cm"              ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_10cm"             ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_15cm"             ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_30cm"             ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_60cm"             ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_90cm"             ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_90cm);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_flat"             ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_flat);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_stubble"          ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_stubble);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_residue_attached"         ,CSC_soil_carbon_mass,CSV_C_decomposed_residue_attached);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"incorporated_by_tillage"             ,CSC_soil_carbon_mass,CSV_C_incorporated_by_tillage);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"removed_by_harvest"                  ,CSC_soil_carbon_mass,CSV_C_removed_by_harvest);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_profile"              ,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_5cm"                  ,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_10cm"                 ,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_15cm"                 ,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_30cm"                 ,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_60cm"                 ,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"decomposed_SOM_90cm"                 ,CSC_soil_carbon_mass,CSV_C_decomposed_SOM_90cm);

   output_comment(csvc_h,csvc_m,csvc_cs,"soil nitrogen");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"leached"                             ,CSC_soil_nitrogen,CSV_soil_N_leached);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"available"                           ,CSC_soil_nitrogen,CSV_soil_N_available);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NH3_volatilization"                  ,CSC_soil_nitrogen,CSV_soil_NH3_volatilization);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"volatilization_total"                ,CSC_soil_nitrogen,CSV_soil_volatilization_total);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_denitrification"            ,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_denitrification);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N2O_loss_nitrification"              ,CSC_soil_nitrogen,CSV_soil_N_N2O_loss_nitrification);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"input"                               ,CSC_soil_nitrogen,CSV_soil_N_input);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"output"                              ,CSC_soil_nitrogen,CSV_soil_N_output);

//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization"                      ,CSC_soil_nitrogen ,CSV_soil_N_immobilization);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_profile"              ,CSC_soil_nitrogen ,CSV_soil_N_immobilization_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_5cm"                  ,CSC_soil_nitrogen ,CSV_soil_N_immobilization_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_10cm"                 ,CSC_soil_nitrogen ,CSV_soil_N_immobilization_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_15cm"                 ,CSC_soil_nitrogen ,CSV_soil_N_immobilization_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_30cm"                 ,CSC_soil_nitrogen ,CSV_soil_N_immobilization_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_60cm"                 ,CSC_soil_nitrogen ,CSV_soil_N_immobilization_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"immobilization_90cm"                 ,CSC_soil_nitrogen ,CSV_soil_N_immobilization_90cm);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_profile"            ,CSC_organic_matter ,CSV_N_mineralization_profile);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_5cm"                ,CSC_organic_matter ,CSV_N_mineralization_5cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_10cm"               ,CSC_organic_matter ,CSV_N_mineralization_10cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_15cm"               ,CSC_organic_matter ,CSV_N_mineralization_15cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_30cm"               ,CSC_organic_matter ,CSV_N_mineralization_30cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_60cm"               ,CSC_organic_matter ,CSV_N_mineralization_60cm);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_mineralization_90cm"               ,CSC_organic_matter ,CSV_N_mineralization_90cm);

//NYI   output_comment(csvc_h,csvc_m,csvc_cs,"Freezing soil");

//NYI   output_comment(csvc_h,csvc_m,csvc_cs,"Complete soil");

   output_comment(csvc_h,csvc_m,csvc_cs,"Soil pond");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_depth"                         ,CSC_soil_pond    ,CSV_soil_pond_water_depth);

   output_comment(csvc_h,csvc_m,csvc_cs,"Water table");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"depth"                               ,CSC_water_table,CSV_water_table_depth);

   output_comment(csvc_h,csvc_m,csvc_cs,"Management");
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                             ,CSC_management_irrigation,CSV_mgmt_irrigation);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"biomass_grazed"                      ,CSC_management,CSV_mgmt_biomass_grazed);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"biomass_unsatisfied"                 ,CSC_management,CSV_mgmt_biomass_unsatisfied);

   output_comment(csvc_h,csvc_m,csvc_cs,"Nitrogen management");

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                             ,CSC_management_N,CSV_mgmt_N_applied);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"applied"                             ,CSC_management_P,CSV_mgmt_P_applied);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_applied"                     ,CSC_management_N,CSV_mgmt_organic_N_applied);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"organic_gaseous_loss"                ,CSC_management_N,CSV_mgmt_N_organic_gaseous_loss);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"inorganic_gaseous_loss"              ,CSC_management_N,CSV_mgmt_N_inorganic_gaseous_loss);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"total_mineralization"                ,CSC_miscellaneous_N,CSV_total_mineralization);

   //Layer variables________________________________________________________________________________________________________
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_content"                 ,CSC_soil_base    ,CSV_soil_base_water_content);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"plant_avail_water"             ,CSC_soil_base    ,CSV_soil_base_plant_avail_water);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_depth"                   ,CSC_soil_base    ,CSV_soil_water_depth);

   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"water_potential"               ,CSC_soil_base    ,CSV_soil_water_potential);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"lateral_in_flow_depth"         ,CSC_soil_base    ,CSV_soil_lateral_in_flow_depth);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"lateral_out_flow_depth"        ,CSC_soil_base    ,CSV_soil_lateral_out_flow_depth);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"temperature"                   ,CSC_soil_base   ,CSV_soil_base_temperature);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NO3_amount"                    ,CSC_soil_nitrogen,CSV_soil_N_NO3_amount);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"NH4_amount"                    ,CSC_soil_nitrogen,CSV_soil_N_NH4_amount);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"N_amount"                      ,CSC_soil_nitrogen,CSV_soil_N_amount);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralization"                ,CSC_soil_nitrogen  ,CSV_soil_N_mineralization);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"nitrification"                 ,CSC_soil_nitrogen  ,CSV_soil_N_nitrification);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"denitrification"               ,CSC_soil_nitrogen  ,CSV_soil_N_denitrification);

   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"P_amount"                      ,CSC_soil_phosphorus,CSV_soil_P_amount);

   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"root_fraction"                 ,CSC_crop_base   ,CSV_root_fraction);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"salinity"                      ,CSC_soil_base    ,CSV_soil_salinity);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"salt"                          ,CSC_soil_base    ,CSV_soil_salt);

   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"CO2_C_loss_residue"                  ,CSC_organic_matter,CSV_gaseous_CO2_C_loss_residue);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"CO2_C_loss_SOM"                      ,CSC_organic_matter,CSV_gaseous_CO2_C_loss_SOM);
   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"CO2_C_loss_OM"                       ,CSC_organic_matter,CSV_gaseous_CO2_C_loss_total);

//   output_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"mineralized"                         ,CSC_organic_matter,CSV_N_mineralization_profile);
   output_layer_property(csvc_h,csvc_m,csvc_cs,csvc_bas,csvc_vc,"percent"                       ,CSC_organic_matter,CSV_organic_matter_percent);

   csvc_h << std::endl << "#endif" << std::endl;
   csvc_m << std::endl;
   csvc_bas << std::endl;
   csvc_vc << "{{0"<< ",\"\"}" << std::endl << "};";

//   csvc_cs << "    }" << std::endl;
//   csvc_cs << "}" << std::endl;
};
//______________________________________________________________________________
