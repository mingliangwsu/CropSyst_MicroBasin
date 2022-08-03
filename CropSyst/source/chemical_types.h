#ifndef chemical_typesH
#define chemical_typesH

#define   NH4_to_N_conv           (14.0 / 18.0)
#define   N_to_NH4_conv           (18.0 / 14.0)

#define   NO3_to_N_conv           (14.0 / 62.0)
#define   N_to_NO3_conv           (62.0 / 14.0)

// Warning I need to check the NH3 conversions
#define   NH3_to_N_conv           (0.8226)
#define   N_to_NH3_conv           (1.133016)

enum chemical_types { CT_SALT,CT_NO3,CT_NH4,CT_PMN,CT_PESTICIDE };

#endif
