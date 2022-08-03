#include "float16.h"
#include <limits.h>
#include <math.h>
#include "corn/math/compare.hpp"
// http://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion

namespace CORN
{
//______________________________________________________________________________
union float32_store
{
   float32  number;
   int32    signed_bits;
   nat32    unsigned_bits;
};
//______________________________________________________________________________
        static int const shift = 13;
        static int const shiftSign = 16;

        static int32 const infN = 0x7F800000; // flt32 infinity
        static int32 const maxN = 0x477FE000; // max flt16 normal as a flt32
        static int32 const minN = 0x38800000; // min flt16 normal as a flt32
        static int32 const signN = 0x80000000; // flt32 sign bit

        static int32 const infC = infN >> shift;
        static int32 const nanN = (infC + 1) << shift; // minimum flt16 nan as a flt32
        static int32 const maxC = maxN >> shift;
        static int32 const minC = minN >> shift;
        static int32 const signC = signN >> shiftSign; // flt16 sign bit

        static int32 const mulN = 0x52000000; // (1 << 23) / minN
        static int32 const mulC = 0x33800000; // minN / (1 << (23 - shift))

        static int32 const subC = 0x003FF; // max flt32 subnormal down shifted
        static int32 const norC = 0x00400; // min flt32 normal down shifted

        static int32 const maxD = infC - maxC - 1;
        static int32 const minD = minC - subC - 1;

//______________________________________________________________________________
float16_bits float32_to_float16_bits(float32 number)
{
   float32_store store32;
   store32.number = number;
   float32_store subnormal;
   nat32 sign = store32.signed_bits & signN;
   store32.signed_bits ^= sign;
   sign >>= shiftSign; // move sign bit to f16 position
   subnormal.signed_bits = mulN;
   subnormal.signed_bits = subnormal.number * store32.number; // correct subnormals
   store32.signed_bits ^= (subnormal.signed_bits ^ store32.signed_bits) & -(minN > store32.signed_bits);
   store32.signed_bits ^= (infN ^ store32.signed_bits) & -((infN > store32.signed_bits) & (store32.signed_bits > maxN));
   store32.signed_bits ^= (nanN ^ store32.signed_bits) & -((nanN > store32.signed_bits) & (store32.signed_bits > infN));
   store32.unsigned_bits >>= shift; // logical shift
   store32.signed_bits ^= ((store32.signed_bits - maxD) ^ store32.signed_bits) & -(store32.signed_bits > maxC);
   store32.signed_bits ^= ((store32.signed_bits - minD) ^ store32.signed_bits) & -(store32.signed_bits > subC);
   float16_bits bits_f16 = store32.unsigned_bits | sign;
   return  bits_f16;
}
//______________________________________________________________________________
float16_bits float64_to_float16_bits(float64 number)
{  return float32_to_float16_bits((float32)number);
}
//______________________________________________________________________________
float16::float16()
: bits(0)
{}
//______________________________________________________________________________
float16::float16(const float16 &copy)
: bits(copy.bits)
{}
//______________________________________________________________________________
float16::float16(float64 number)
: bits(float64_to_float16_bits(number))
{}
//______________________________________________________________________________
float16::float16(float32 number)
: bits(float32_to_float16_bits((float32)number))
{}
//______________________________________________________________________________
float16::float16(sint32 number)
: bits(float32_to_float16_bits((float32)number))
{}
//______________________________________________________________________________
float16::float16(sint16 number)
: bits(float32_to_float16_bits((float32)number))
{}
//______________________________________________________________________________
float16::float16(sint8 number)
: bits(float32_to_float16_bits((float32)number))
{}
//______________________________________________________________________________

// Caste operstors
float32 float16_to_float32(const float16 &number)
{
   float32_store store32;
      store32.unsigned_bits = number.get_bits();
      int32 sign = store32.signed_bits & signC;
      store32.signed_bits ^= sign;
      sign <<= shiftSign;
      store32.signed_bits ^= ((store32.signed_bits + minD) ^ store32.signed_bits) & -(store32.signed_bits > subC);
      store32.signed_bits ^= ((store32.signed_bits + maxD) ^ store32.signed_bits) & -(store32.signed_bits > maxC);
   float32_store subnormal;
      subnormal.signed_bits = mulC;
      subnormal.number *= store32.signed_bits;
   int32 mask = -(norC > store32.signed_bits);
   store32.signed_bits <<= shift;
   store32.signed_bits ^= (subnormal.signed_bits ^ store32.signed_bits) & mask;
   store32.signed_bits |= sign;
   return store32.number;
}
//______________________________________________________________________________
float32 float16_error(float32 number)
{  float16 as_f16(number);
   float32 as_f32(as_f16);
   float32 error = number - as_f32;
   return error;
}
//______________________________________________________________________________
bool has_acceptable_precision(float64 number,nat8 decimal_places)
{
   float16 as_f16(number);
   //170217 float64 as_f64 = as_f16;
   float64 number_scaled = number * pow(10.0,decimal_places);
   float16 as_f64_scaled = number_scaled  * pow(10.0,decimal_places);
   bool acceptable = CORN::is_approximately<float64>(number_scaled,as_f64_scaled,1.0);
   return acceptable;
}
/*
float32 maximum_as_float32() const;
float32 minimum_as_float32() const;
float32 maximum_infinity_as_float32() const;
float32 minimum_infinity_as_float32() const;
*/
//______________________________________________________________________________
bool float16_test() 
{  bool passed = false;
   /* NYI
   float16 infinity_positive(xxx); passed &= infinity_positive.get_bits() == infinity_positive_bits;
   float16 infinity_negative(xxx); passed &= infinity_negative.get_bits() == infinity_negative_bits;
   */
   float16 zero_positive(0.0);     passed &= zero_positive.get_bits() == zero_positive_bits;
   float16 zero_negative(-0.0);    passed &= zero_negative.get_bits() == zero_negative_bits;

   float16 one (1.0);              passed &= one.get_bits() == 0x3C00;
   float16 minus_2(-2.0);          passed &= minus_2.get_bits() == 0xC000;
   float16 next_smallest_number_after_1(1.0009765625);
      passed &= next_smallest_number_after_1.get_bits() == 0x3C01;
   float16 third(1.0/3.0);         passed &= third.get_bits() == 0x3555;
   //170217unused float64 third_as_f64 = third;
   // 0.333251953125
/*
Integers between 0 and 2048 can be exactly represented
Integers between 2049 and 4096 round to a multiple of 2 (even number)
Integers between 4097 and 8192 round to a multiple of 4
Integers between 8193 and 16384 round to a multiple of 8
Integers between 16385 and 32768 round to a multiple of 16
Integers between 32769 and 65536 round to a multiple of 32
Integers equal to or above 65520 are rounded to "infinity".
*/
   return passed;
}
//______________________________________________________________________________
} // namespace CORN
