#ifndef manure_formH
#define manure_formH

#define FRESH_MANURE_FORM  SEMI_SOLID

#ifndef labeled_enumH
#include "corn/labeled_enum.h"
#endif
//______________________________________________________________________________
enum Solid_liquid_form                                                           //020322
   {solid_form             // 20% DM
   ,solid_semi_solid_form  // 16% DM  Roger Nelson's term
   ,semi_solid_form        // 13% DM
   ,semi_solid_slurry_form // 11% DM  Roger Nelson's term
   ,slurry_form            //  9% DM  but could range 8-10% DM
   ,liquid_slurry_form     //  6% DM  but could range 5-7% DM
   ,liquid_form            //  3% DM  0-4% dry matter   Roger Nelson's term
   ,solid_liquid_form_COUNT                                                      //150623BRC
   };
extern const char *Solid_liquid_form_label_table[];
DECLARE_LABELED_ENUM(Solid_liquid_form_labeled,Solid_liquid_form,Solid_liquid_form_label_table)
//______________________________________________________________________________
extern float manure_moisture_percent[];                                          //041101

#endif

