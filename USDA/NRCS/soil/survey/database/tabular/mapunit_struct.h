//---------------------------------------------------------------------------
#ifndef mapunit_structH
#define mapunit_structH
#include "USDA/NRCS/soil/survey/database/STATSGO_SSURGO_types.h"
#include <string>
#include "corn/string/strconv.hpp"
//---------------------------------------------------------------------------
namespace USDA_NRCS
{
//______________________________________________________________________________
typedef std::string Mapunit_kind;  // Eventually this will be an enum
typedef std::string Mapunit_status;  // Eventually this will be an enum
typedef std::string Farmland_classification;  // Eventually this will be an enum
typedef std::string Mapunit_HEL_class;  // Eventually this will be an enum
typedef std::string Investigation_intensity;  // Eventually this will be an enum
typedef std::string NH_Important_forest_soil_group; // Eventually this will be an enum
typedef std::string VT_Septic_system_class;         // Eventually this will be an enum
typedef std::string Mapunit_certification_status;   // Eventually this will be an enum
//______________________________________________________________________________
struct Mapunit_struct
{
   std::string musym;                        // Mapunit Symbol   6
   std::string muname;                       // Mapunit Name   175
   Mapunit_kind   mukind;                    // Kind   254
   Mapunit_status mustatus;                  // Status  254
   nat32          muacres;                   // Total Acres  0 acres
   nat32_lrh mapunitlfw;                     // Linear Feature Width     meters
   float32_lrh mapunitpfa;                   // Point Feature Area 1 0.1 10 acres
   Farmland_classification farmlndcl;        // Farm Class   254
   Mapunit_HEL_class muhelcl;                // HEL   254
   Mapunit_HEL_class muwathelcl;             // HEL Water   254
   Mapunit_HEL_class muwndhelcl;             // HEL Wind   254
   std::string interpfocus;                  // Interpretive Focus   30
   Investigation_intensity invesintens;      // Order of Mapping   254
   nat8 iacornsr;                            // IA CSR   5 100
   NH_Important_forest_soil_group nhiforsoigrp; // NH Forest Soil Grp   254
   float32 nhspiagr;                         // NH SPI Agr   (prcsn 1) 0 100
   VT_Septic_system_class vtsepticsyscl;     // VT Septic System   254
   Mapunit_certification_status mucertstat;  // Map Unit Certification Status 254
   std::string lkey;                         // Legend Key   30
   std::string mukey;                        // Mapunit  30
 public:
   Mapunit_struct();                                                             //111218
   nat32 get_mukey() const { return CORN::cstr_to_nat32(mukey.c_str(),10); };
   void clear();                                                                 //111218
};
//______________________________________________________________________________
}; // namespace USDA_NRCS

#endif
