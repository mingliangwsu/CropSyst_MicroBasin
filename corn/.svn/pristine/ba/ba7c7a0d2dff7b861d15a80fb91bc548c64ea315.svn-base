// *************** convert integer or double to string etc *****************

#define WANT_STREAM
#define WANT_MATH

#include "str.h"
#include "str_fns.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif



String ToString(int value)
// convert signed integer to string
{
   bool negative;
   if (value < 0) { value = -value; negative = true; }
   else if (value == 0) return String("0");
   else negative = false;
   char b[100]; b[99] = (char)0; int i = 99;
   while (value > 0)
   {
      int nv = value / 10; int rm = value - nv * 10;
      b[--i] = (char)(rm + '0'); value = nv;
      if (i<=0) return ("*****");
   }
   if (negative) b[--i] = '-';
   return String(b+i);
}

String ToString(long value)
// convert signed long to string
{
   bool negative;
   if (value < 0) { value = -value; negative = true; }
   else if (value == 0) return String("0");
   else negative = false;
   char b[100]; b[99] = (char)0; int i = 99;
   while (value > 0)
   {
      long nv = value / 10; long rm = value - nv * 10;
      b[--i] = (char)(rm + '0'); value = nv;
      if (i<=0) return ("*****");
   }
   if (negative) b[--i] = '-';
   return String(b+i);
}

String ToString(double value, int ndec)
// convert double to string, ndec = number of decimals
{
   bool negative;
   if (value < 0) { value = -value; negative = true; }
   else negative = false;
   if (value >= 1000000L) return ("*****");
   double p = pow(10.0,ndec); double i; double f = modf(value, &i);
   f = floor(f * p + 0.5);
   if (f >= p) i += 1.0; else f += p;
   long li = (long)i; long lf = (long)f; long lp = (long)p;
   if (!li && lf==lp) negative = false;
   String si = ToString(li); String sf = ToString(lf); sf[0] = '.';
   if (negative) return String("-")+si+sf; else return si+sf;
}

void UpperCase(String& S)
{
   unsigned int n = S.size();
   for (unsigned int j = 0; j < n; j++)
   {
      char sj = S[j];
      if (sj >= 'a' && sj <= 'z') S[j] = (char)(sj - ('a' - 'A'));
   }
}

void LowerCase(String& S)
{
   unsigned int n = S.size();
   for (unsigned int j = 0; j < n; j++)
   {
      char sj = S[j];
      if (sj >= 'A' && sj <= 'Z') S[j] = (char)(sj + ('a' - 'A'));
   }
}

bool IsInt(const String& S)
{
   unsigned int n = S.size();
   unsigned int i = S.find_first_not_of(" \t");
   if (i == String::npos) return false;         // do not accept blanks
   if (S[i] == '-' || S[i] == '+')              // sign
   {
      i++;
      if (i >= n || S[i] == ' ' || S[i] == '\t')
         return false;                          // nothing following sign
   }
   for (unsigned int i1 = i; i1 < n; ++i1)
   {
      if (S[i1] < '0' ||  S[i1] > '9')
      {
         unsigned int i2 = S.find_first_not_of(" \t", i1);
         return i2 == String::npos;            // trailing blanks?
      }
   }
   return true;
}

// also include E format
bool IsFloat(const String& S)
{
   unsigned int n = S.size();
   bool dp = false;                             // have decimal point
   unsigned int i = S.find_first_not_of(" \t");
   if (i == String::npos) return false;         // do not accept blanks
   if (S[i] == '-' || S[i] == '+')              // sign
   {
      i++;
      if (i >= n || S[i] == ' ' || S[i] == '\t')
         return false;                          // nothing following sign
   }
   bool nos = false;
   for (unsigned int i1 = i; i1 < n; i1++)
   {
      if (S[i1] < '0' || S[i1] > '9')
      {
         if (S[i1] == '.')
         {
            if (dp) return false;               // two decimals
            dp = true;
         }
         else if (S[i1] == 'E' || S[i1] == 'e')
         {
            ++i1;
            if (i1 >=n) return false;           // nothing following E
            if (S[i1] == ' ' || S[i1] == '\t') return false;
            return IsInt(S.substr(i1));
         }
         else
         {
            unsigned int i2 = S.find_first_not_of(" \t", i1);
            return i2 == String::npos;          // trailing blanks?
         }
      }
      else nos = true;                          // at least one digit
   }
   return nos;
}


int sf(String& S, const String& s1, const String& s2)
{
   unsigned int p = S.find(s1); if (p == String::npos) return 0;
   S.replace(p, s1.size(), s2);
   return 1;
}

int sl(String& S, const String& s1, const String& s2)
{
   unsigned int p = S.rfind(s1); if (p == String::npos) return 0;
   S.replace(p, s1.size(), s2);
   return 1;
}

int sa(String& S, const String& s1, const String& s2)
{
   int n = s1.size(); if (n == 0) return 0;
   int c = 0;
   for (unsigned int p = 0; ;)
   {
      p = S.find(s1, p); if (p == String::npos) return c;
      S.replace(p, n, s2); p += s2.size(); ++c;
   }
}




#ifdef use_namespace
}
#endif


