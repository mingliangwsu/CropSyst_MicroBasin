//______________________________________________________________________________
const char *Solid_liquid_form_label_table[] =
{"solid"
,"solid/semisolid"
,"semisolid"
,"semisolid/slurry"
,"slurry"
,"liquid/slurry"
,"liquid"
,0};
//_2002-03-22___________________________________________________________________
float manure_moisture_percent[] =
{80 // SOLID               // 20% DM
,84 // SOLID_SEMI_SOLID    // 16% DM  Roger Nelson's term
,87 // SEMI_SOLID          // 13% DM
,89 // SEMI_SOLID_SLURRY   // 11% DM  Roger Nelson's term
,91 // SLURRY              //  9% DM  but could range 8-10% DM
,94 // LIQUID_SLURRY       //  6% DM  but could range 5-7% DM
,97 // LIQUID              //  3% DM  0-4% dry matter   Roger Nelson's term
};
//_2004-11-01___________________________________________________________________

