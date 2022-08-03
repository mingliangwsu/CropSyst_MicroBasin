#ifndef float16H
#define float16H
#include "corn/primitive.h"

namespace CORN
{
typedef int16 float16_bits;
class float16;
extern float32 float16_to_float32(const float16 &number);
//______________________________________________________________________________
class float16
{
   float16_bits bits;
 public:
   float16();
   float16(const float16 &copy);
   float16(float64);
   float16(float32);
   float16(sint32);
   float16(sint16);
   float16(sint8);

   // Caste operstors
   inline operator float64 () const { return (float64)float16_to_float32(*this); }
   inline operator float32 () const { return float16_to_float32(*this); }
   inline operator sint32  () const { return float16_to_float32(*this); }
   inline operator sint16  () const { return (sint16) float16_to_float32(*this); }
   inline operator sint8   () const { return (sint8)  float16_to_float32(*this); }

   inline float16_bits get_bits() const { return bits; }
   inline float16_bits set_bits(float16_bits _bits) { bits=_bits; return bits;}
};
//______________________________________________________________________________
extern float32 float16_error(float32 number);
      // Returns the precision error of number stored as float16
extern bool has_acceptable_precision(float64 number,nat8 decimal_places);

extern float32 maximum_as_float32();
extern float32 minimum_as_float32();
extern float32 maximum_infinity_as_float32();
extern float32 minimum_infinity_as_float32();

// extremes
#define infinity_positive_bits   0x7C00
// b0 11111 0000000000
#define infinity_negative_bits   0xFC00
// b1 11111 0000000000
#define zero_positive_bits       0x0000
// b0 00000 0000000000
#define zero_negative_bits       0x8000
// b1 00000 0000000000

bool float16_test();

//______________________________________________________________________________
}
#endif
