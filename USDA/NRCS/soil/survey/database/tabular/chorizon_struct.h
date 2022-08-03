//---------------------------------------------------------------------------
#ifndef chorizon_structH
#define chorizon_structH
//---------------------------------------------------------------------------
#include "USDA/NRCS/soil/survey/database/STATSGO_SSURGO_types.h"
#include <string>

// This table format is documented in
//http://soildatamart.nrcs.usda.gov/documents/SSURGOMetadataTableColumns.pdf

namespace USDA_NRCS
{
//_2011-02-15___________________________________________________________________
typedef std::string Horz_desgn_master;      // Eventually this will be an enum
typedef std::string Horz_desgn_master_prime;      // Eventually this will be an enum
typedef std::string Soil_erodibility_factor;      // Eventually this will be an enum
typedef std::string Excavation_difficulty_class;  // Eventually this will be an enum
typedef std::string Observed_soil_moisture_status;  // Eventually this will be an enum
//_2011-02-15___________________________________________________________________
struct CHorizon_struct
{
   std::string   hzname; // Designation String No 12
   nat8 desgndisc; // Disc Integer No 2 99
   Horz_desgn_master desgnmaster; // Master Choice No 254
   Horz_desgn_master_prime desgnmasterprime; // Prime Choice No 254
   nat8        desgnvert;  // Sub   1
   nat16_lrh   hzdept;// Top Depth 0 9999 centimeters
   nat16_lrh   hzdepb;// Bottom Depth - Low Value Integer No 0 9999 centimeters
   nat16_lrh   hzthk;// Thickness - Low Value Integer No 0 9999 centimeters
   nat8_lrh    fraggt10; // Rock >10 - Low Value Integer No 0 100 percent
   nat8_lrh    frag3to10; // Rock 3-10 - Low Value Integer No 0 100 percent
   float32_lrh    sieveno4; // #4 - Low Value Float No 1 0 100 percent
   float32_lrh    sieveno10;//  #10 - Low Value Float No 1 0 100 percent
   float32_lrh    sieveno40;//  #40 - Low Value Float No 1 0 100 percent
   float32_lrh    sieveno200;//  #200 - Low Value Float No 1 0 100 percent
   float32_lrh     sandtotal;//  Total Sand - Low Value Float No 1 0 100 percent
   float32_lrh    sandvc;//  vcos - Low Value Float No 1 0 100 percent
   float32_lrh    sandco;//  cos - Low Value Float No 1 0 100 percent
   float32_lrh    sandmed;//  ms - Low Value Float No 1 0 100 percent
   float32_lrh    sandfine;//  fs - Low Value Float No 1 0 100 percent
   float32_lrh    sandvf;//  vfs - Low Value Float No 1 0 100 percent
   float32_lrh    silttotal;//  Total Silt - Low Value Float No 1 0 100 percent
   float32_lrh    siltco;//  Coarse Silt - Low Value Float No 1 0 100 percent
   float32_lrh    siltfine;//  Fine Silt - Low Value Float No 1 0 100 percent
   float32_lrh    claytotal;//  Total Clay - Low Value Float No 1 0 100 percent
   float32_lrh    claysizedcarb;//  CaCO3 Clay - Low Value Float No 1 0 100 percent
   float32_lrh    om;//  OM - Low Value Float No 2 0 100 percent
   float32_lrh    dbtenthbar;//  Db 0.1 bar H2O - Low Value Float No 2 0.02 2.6 grams per cubic centimeter
   float32_lrh    dbthirdbar;//  Db 0.33 bar H2O - Low Value Float No 2 0.02 2.6 grams per cubic centimeter
   float32_lrh    dbfifteenbar;//  Db 15 bar H2O - Low Value Float No 2 0.02 2.6 grams per cubic centimeter
   float32_lrh    dbovendry;//  Db oven dry - Low Value Float No 2 0.02 2.6 grams per cubic centimeter
   float32        partdensity; // Dp Float No 2 0.01 5 grams per cubic centimeter
   float32_lrh    ksat;//  Ksat - Low Value  4 0 705 micrometers per second
   float32_lrh    awc;//  AWC - Low Value  2 0 0.7 centimeters per centimeter
   float32_lrh    wtenthbar;// 0.1 bar H2O - Low Value  1 0 2000 percent
   float32_lrh    wthirdbar;// 0.33 bar H2O - Low Value  1 0 2000 percent
   float32_lrh    wfifteenbar;// 15 bar H2O - Low Value  1 0 400 percent
   nat8_lrh       wsatiated;// Satiated H2O - Low Value   10 70 percent
   float32_lrh    lep;// LEP - Low Value Float No 1 0 30 percent
   float32_lrh    ll; //LL - Low Value Float No 1 0 400 percent
   float32_lrh    pi; //PI - Low Value Float No 1 0 130 percent
   nat8_lrh    aashind;// AASHTO Group Index - Low Value Integer No 0 120
   Soil_erodibility_factor kwfact; //Kw 254
   Soil_erodibility_factor kffact; //Kf  254
   nat8_lrh    caco3;// CaCO3 - Low Value Integer No 0 110 percent
   nat8_lrh    gypsum;// Gypsum - Low Value Integer No 0 120 percent
   float32_lrh    sar;// SAR - Low Value Float No 1 0 9999
   float32_lrh    ec;// EC - Low Value Float No 1 0 15000 millimhos per centimeter
   float32_lrh    cec7;// CEC-7 - Low Value Float No 1 0 400 milliequivalents per 100grams
   float32_lrh    ecec;// ECEC - Low Value Float No 1 0 400 milliequivalents per 100grams
   float32_lrh    sumbases; // Sum of Bases - Low Value Float No 1 0 300 milliequivalents per 100grams
   float32_lrh    ph1to1h2o;// pH H2O - Low Value Float No 1 1.8 11
   float32_lrh    ph01mcacl2;// pH CaCl2 - Low Value Float No 1 1.8 11
   float32_lrh    freeiron;// Free Iron - Low Value Float No 2 0 100 percent
   float32_lrh    feoxalate;// Oxalate Fe - Low Value Float No 2 0 150000 milligrams per kilogram
   float32_lrh    extracid;// Ext Acidity - Low Value Float No 1 0 250 milliequivalents per 100grams
   float32_lrh    extral;// Extract Al - Low Value Float No 2 0 150 milliequivalents per 100 grams
   float32_lrh    aloxalate;// Oxalate Al - Low Value Float No 1 0 170000 milligrams per kilogram
   float32_lrh    pbray1;// Bray 1 Phos - Low Value Float No 1 0 500 milligrams per kilogram
   float32_lrh    poxalate;// Oxalate Phos - Low Value Float No 1 0 milligrams per kilogram
   float32_lrh    ph2osoluble;// Water Soluble Phos - Low Value Float No 1 0 5000 milligrams per kilogram
   float32_lrh    ptotal;// Total Phos - Low Value Float No 2 0 percent
   Excavation_difficulty_class excavdifcl; // Excav Diff Choice No 254
   Observed_soil_moisture_status excavdifms; // Excav Diff Moisture Choice No 254
   std::string cokey; //  Component Key String Yes 30
   std::string chkey; // Chorizon Key String Yes 30
 public:
   CHorizon_struct();
   void clear();
};
//______________________________________________________________________________
} // namespace USDA_NRCS
#endif
