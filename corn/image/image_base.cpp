#include "corn/image/image_base.h"

#define odd(x) ((-x) & 0x01)
#define even(x) (!((-x) & 0x01))

namespace CORN
{
//______________________________________________________________________________
void Image_base::checker_board_transparent()
{
   for (int r=0; r < get_height(); r++)
      for (int c = 0; c < get_width(); c++)
         if ((even(r) && even(c)) ||
             (odd(r) && odd(c)))
            point(c,r,get_transparent_color());
};
//______________________________________________________________________________

// line can be moved to image
void Image_base::line(nat16 c1,nat16 r1,nat16 c2,nat16 r2,Image_color_index color)
{
#ifdef DDA
  int error = 0;
  int deltax = c2 - c1;
  int deltay = r2 - r1;

  if (deltay < 0)
  {
    int h_c1 = c1;
    c1 = c2;
    c2 = h_c1;
    int h_r1 = r1;
    r1 = r2;
    r2 = h_r1;
    deltay=-deltay;
    deltax=-deltax;
  };

  int c = c1;
  int r = r1;
  int i;
  if (deltax >= 0)
  {
     if (deltax >= deltay)
     {  for (i = 1; i < deltax; i++)
            if (error < 0)
            { c+= 1;
               point(c,r,color);
               error += deltay;
            }
            else
            { c+= 1;
               r+= 1;
               point(c,r,color);
               error  += deltay - deltax;
            };
     }
     else
     {
       for (i = 1 ; i < deltay;i++)
         if (error < 0)
         {
            c+= 1;
            r += 1;
            point(c,r,color);
            error += deltay - deltax;
         }
         else
         { r += 1;
           point(c,r,color);
           error -= deltax;
         }
     }
  }
  else
    if (deltax >= deltay)
    {
      for (i= 1; i< deltax; i++)
         if (error < 0)
         { c-= 1;
           point(c,r,color);
           error += deltay;
         }
         else
         { c -= 1;
           r -= 1;
           point(c,r,color);
           error += deltax+deltay;
         };
    }
    else
      for (i = 1; i < deltay ; i++)
            if (error < 0)
            { c -= 1;
              r -= 1;
              point (c,r,color);
              error += deltax + deltay;
            }
            else
            { r += 1;
              point(c,r,color);
              error += deltax;
            };
    point(c2,r2,color);

#else

   if (r2 < r1)
   {
     int h_c1 = c1;
     c1 = c2;
     c2 = h_c1;
     int h_r1 = r1;
     r1 = r2;
     r2 = h_r1;
   };

   int deltax = c2 - c1;
   int deltay = r2 - r1;

   if (deltay == 0)
      for (int c = c1; c <= c2; c++)
         point(c,r1,color);
   else
      if (deltax == 0)
         for (int r = r1; r <= r2; r++)
            point(c1,r,color);
   else
   if ((deltax > deltay))
   {
     float slope = (float)deltay / (float)deltax;
     for (int c = 0; c < deltax; c++)
     {
       int r = (float)c * slope;
       point(c1+c,r1+r,color);
     };
   }
   else
   {
     float slope = (float)deltax / (float)deltay;
     for (int r = 0; r < deltay; r++)
     {
       int c = (float)r * slope;
       point(c1+c,r1+r,color);
     };
   }

#endif
};
//______________________________________________________________________________
}
