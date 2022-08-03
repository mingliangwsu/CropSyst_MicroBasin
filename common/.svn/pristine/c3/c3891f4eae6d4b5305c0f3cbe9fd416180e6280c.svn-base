
#ifndef DECOMPOSITION_CONST_H
#define DECOMPOSITION_CONST_H

#define convert_decomposition_time_63_to_constant(decomp_time_63) (decomp_time_63 > 0.0 ? (- CORN_ln(1.0 - 1.0/ (float64)decomp_time_63)) : 0.0)
// was  divided by  CORN_ln(Euler_number)  but this = 1
#define convert_decomposition_time_50_to_constant(decomp_time_50) (decomp_time_50 > 0.0 ? (- CORN_ln(0.5)/ (float64)decomp_time_50) : 0.0)
#define convert_decomposition_time_63_to_50(decomp_time_63)       (- CORN_ln(0.5)/ convert_decomposition_time_63_to_constant((float64)decomp_time_63))

#define convert_constant_to_decomposition_time_63(DC)             (1.0 / (-exp(-DC) + 1.0))

#endif
