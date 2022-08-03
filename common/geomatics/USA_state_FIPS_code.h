#ifndef USA_state_FIPS_codeH
#define USA_state_FIPS_codeH
//______________________________________________________________________________
// Federal Information Processing Standard
struct USA_State_FIPS
{  const char *code  // 2 letter Code
;  const char *name  // State name
;};
//______________________________________________________________________________
extern USA_State_FIPS USA_state_FIPS[];
// terminated with code = 0 and name = 0;
int lookup_USA_state_FIPS_number(const char *state_name_or_FIPS_CODE);
// These were erroneous extern  char USA_state_FIPS_code[][3]; // depricated, use USA_state_FIPS
//______________________________________________________________________________
#endif
