// test character string manipulation library and string list

#define WANT_STREAM
#define WANT_MATH

#include "include.h"
#include "str.h"
#include "gstring.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif



#ifdef DO_REPORT
#define REPORT { static ExeCounter ExeCount(__LINE__,1); ++ExeCount; }
#else
#define REPORT {}
#endif



// ************************ Generalised String functions **********************

PlusGString GString::operator+(const GString& g)
   { REPORT return PlusGString(this, &g); }

GTGString GString::operator>(const GString& g)
   { REPORT return GTGString(this, &g); }

GTGString2 GTGString::operator>(const GString& g)
   { REPORT return GTGString2(this, &g); }

GTGString2 GTGString2::operator>(const GString& g)
   { REPORT return GTGString2(this, &g); }

LTGString GString::operator<(const GString& g)
   { REPORT return LTGString(this, &g); }

AndGString GString::operator&(const GString& g)
   { REPORT return AndGString(this, &g); }

OrGString GString::operator|(const GString& g)
   { REPORT return OrGString(this, &g); }

XorGString GString::operator^(const GString& g)
   { REPORT return XorGString(this, &g); }

NotGString GString::operator~()
   { REPORT return NotGString(this); }


bool ExplicitString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("ExplicitString::Matches");
   REPORT return S == s.substr(offset, length);
}

bool CIString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("CIString::Matches");
   REPORT
   String us = s.substr(offset, length); UpperCase(us);
   return S == us;
}

bool AndGString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("AndGString::Matches");
   REPORT
   return
      ((GString*&)G1)->Matches(s, offset, length)
         && ((GString*&)G2)->Matches(s, offset, length);
}

bool OrGString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("OrGString::Matches");
   if (((GString*&)G1)->Matches(s, offset, length))
      { REPORT which = 1; return true; }
   if (((GString*&)G2)->Matches(s, offset, length))
      { REPORT which = 2; return true; }
   REPORT return false;
}

bool XorGString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("XorGString::Matches");
   bool b1 = ((GString*&)G1)->Matches(s, offset, length);
   bool b2 = ((GString*&)G2)->Matches(s, offset, length);
   if (b1 && !b2) { REPORT which = 1; return true; }
   if (!b1 && b2) { REPORT which = 2; return true; }
   REPORT return false;
}

bool PlusGString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("PlusGString::Matches");
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;

   unsigned int n1, n2;

   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset, n, n1);
   if (p1 == -1) { REPORT return false; }

   short int p2 = ((GString*&)G2)->ProbeRight(s, offset, n, n2);
   if (p2 == -1) { REPORT return false; }

   if (p1 == 1 && p2 == 1)
   {
      if (n1 + n2 == n) { split = n1; REPORT return true; }
      else { REPORT return false; }
   }

   if (p1 == 1)
   {
      if (((GString*&)G2)->Matches(s, offset + n1, n-n1))
         { split = n1; REPORT return true; }
      else { REPORT return false; }
   }

   if (p2 == 1)
   {
      if (((GString*&)G1)->Matches(s, offset, n-n2))
         { split = n - n2; REPORT return true; }
      else { REPORT return false; }
   }

/*
   unsigned int n1 = G1->FixedLength(); unsigned int n2 = G2->FixedLength();

   // if either of strings is of fixed length no iteration is necessary

   if (n1 != String::npos)
   {
      if (n1 > n) return false;
      split = n1;
      return ((GString*&)G1)->Matches(s, offset, n1)
         && ((GString*&)G2)->Matches(s, offset + n1, n-n1);
   }

   if (n2 != String::npos)
   {
      if (n2 > n) return false;
      split = n - n2;
      return ((GString*&)G1)->Matches(s, offset, n-n2)
         && ((GString*&)G2)->Matches(s, offset + n-n2, n2);
   }
*/
   // divide s into a first part to match G1 and a second part to match G2
   // iterate over division points

   if (G1->ShortLong() <= 0 && G2->ShortLong() >= 0)
   {
      for (unsigned int i = 0; i <= n; i++)
         if ( ((GString*&)G1)->Matches(s, offset, i)
            && ((GString*&)G2)->Matches(s, offset + i, n-i) )
            { split = i; REPORT return true; }
      REPORT return false;
   }
   else
   {
      for (int i = n; i >= 0; i--)
         if ( ((GString*&)G1)->Matches(s, offset, i)
            && ((GString*&)G2)->Matches(s, offset + i, n-i) )
            { split = i; REPORT return true; }
      REPORT return false;
   }
}

bool GTGString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("GTGString::Matches");
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;

   unsigned int n1, n2;

   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset, n, n1);
   if (p1 == -1) { REPORT return false; }

   short int p2 = ((GString*&)G2)->ProbeRight(s, offset, n, n2);
   if (p2 == -1) { REPORT return false; }

   if (p1 == 1 && p2 == 1)
   {
      if (n1 + n2 == n) { split = n1; REPORT return true; }
      else { REPORT return false; }
   }

   if (p1 == 1)
   {
      if (((GString*&)G2)->Matches(s, offset + n1, n-n1))
         { split = n1; REPORT return true; }
      else { REPORT return false; }
   }

   if (p2 == 1)
   {
      // cannot be sure of fit even if we get match in following
      if ( !(((GString*&)G1)->Matches(s, offset, n-n2)) )
         { REPORT return false; }
   }
   else { REPORT n2 = String::npos; }

/*
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;
   unsigned int n1 = G1->FixedLength(); unsigned int n2 = G2->FixedLength();

   // if first of strings is of fixed length no iteration is necessary

   if (n1 != String::npos)
   {
      if (n1 > n) return false;
      split = n1;
      return ((GString*&)G1)->Matches(s, offset, n1)
         && ((GString*&)G2)->Matches(s, offset + n1, n-n1);
   }

   if (n2 != String::npos)
   {
      if ( !(((GString*&)G1)->Matches(s, offset, n-n2)
         && ((GString*&)G2)->Matches(s, offset + n-n2, n2)) )
         return false;
   }
*/
   // divide s into a first part to match G1 and a second part to match G2
   // iterate over division points

   if (G1->ShortLong() <= 0)
   {
      int m = (n2 != String::npos) ? n-n2 : n;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G1)->Matches(s, offset, i) )
         {
            if ( ((GString*&)G2)->Matches(s, offset + i, n-i) )
               { split = i; return true; }
            REPORT return false;
         }
      REPORT return false;
   }
   else
   {
      int m = (n2 != String::npos) ? n-n2 : 0;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G1)->Matches(s, offset, i) )
         {
            if ( ((GString*&)G2)->Matches(s, offset + i ,n-i) )
               { split = i; return true; }
            REPORT return false;
         }
      REPORT return false;
   }
}

// we are starting the match at location ix and we allow some of the
// string to be left over

bool GTGString::Matches_i(const String& s, unsigned int& ix, uint offset,
   uint length)
{
   Tracer TR("GTGString::Matches_i");
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;

/*

   unsigned int n1 = G1->FixedLength(); unsigned int n2 = G2->FixedLength();

   // first string

   if (n1 != String::npos)    // G1 of fixed length
   {
      if (n1 > n-ix) return false;
      if ( !((GString*&)G1)->Matches(s, offset + ix, n1) ) return false;
      split = n1; ix += n1;
   }
   else if (G1->ShortLong() <= 0)
   {
      int m = (n2 != String::npos) ? n-ix-n2 : n-ix;
      bool found = false;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G1)->Matches(s, offset + ix, i) )
            { found = true; split = i; ix += i; break; }
      if (!found) return false;
   }
   else
   {
      int m = (n2 != String::npos) ? n-ix-n2 : ix;
      bool found = false;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G1)->Matches(s, offset + ix, i) )
            { found = true; split = i; ix += i; break; }
      if (!found) return false;
   }

   // now do second string

   if (n2 != String::npos)    // G2 of fixed length
   {
      if (n2 > n-ix) return false;
      if ( !((GString*&)G2)->Matches(s, offset + ix, n2) ) return false;
      ix += n2;
   }
   else if (G2->ShortLong() <= 0)
   {
      int m = n-ix;
      bool found = false;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) return false;
   }
   else
   {
      int m = ix;
      bool found = false;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) return false;
   }

   return true;
*/

   unsigned int n1, n2;

   // first string

   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset+ix, n-ix, n1);
   if (p1 == -1) { REPORT return false; }

   if (p1 == 1) { split = n1; ix += n1; }

   else if (G1->ShortLong() <= 0)
   {
      n2 = G2->FixedLength();
      int m = (n2 != String::npos) ? n-ix-n2 : n-ix;
      bool found = false;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G1)->Matches(s, offset + ix, i) )
            { found = true; split = i; ix += i; break; }
      if (!found) { REPORT return false; }
   }
   else
   {
      n2 = G2->FixedLength();
      int m = (n2 != String::npos) ? n-ix-n2 : ix;
      bool found = false;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G1)->Matches(s, offset + ix, i) )
            { found = true; split = i; ix += i; break; }
      if (!found) { REPORT return false; }
   }

   // now do second string

   short int p2 = ((GString*&)G2)->ProbeLeft(s, offset+ix, n-ix, n2);
   if (p2 == -1) { REPORT return false; }

   if (p2 == 1) { ix += n2; }

   else if (G2->ShortLong() <= 0)
   {
      int m = n-ix;
      bool found = false;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) { REPORT return false; }
      REPORT
   }
   else
   {
      int m = ix;
      bool found = false;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) { REPORT return false; }
      REPORT
   }

   REPORT return true;

}

bool GTGString2::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("GTGString2::Matches");

   unsigned int ix = 0;
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;

   // first string

   if ( !((GString*&)G1)->Matches_i(s, ix, offset, n) )
      { REPORT return false; }
   split = ix;

   // now do second string

   REPORT return ((GString*&)G2)->Matches(s, offset+ix, n-ix);

}

bool GTGString2::Matches_i(const String& s, unsigned int& ix, uint offset,
   uint length)
{
   Tracer TR("GTGString2::Matches_i");
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;

/*
   unsigned int n2 = G2->FixedLength();

   // first string

   int i = ix;
   if ( !((GString*&)G1)->Matches_i(s, ix, offset + i, n-i) ) return false;
   split = ix - i;

   // now do second string

   if (n2 != String::npos)    // G2 of fixed length
   {
      if (n2 > n-ix) return false;
      if ( !((GString*&)G2)->Matches(s, offset + ix, n2) ) return false;
      ix += n2;
   }
   else if (G2->ShortLong() <= 0)
   {
      int m = n-ix;
      bool found = false;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) return false;
   }
   else
   {
      int m = ix;
      bool found = false;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) return false;
   }

   return true;
*/


   // first string

   int i = ix;
   if ( !((GString*&)G1)->Matches_i(s, ix, offset+i, n-i) ) return false;
   split = ix - i;

   // now do second string

   unsigned int n2;
   short int p2 = ((GString*&)G2)->ProbeLeft(s, offset+ix, n-ix, n2);
   if (p2 == -1) { REPORT return false; }

   if (p2 == 1) { ix += n2; }

   else if (G2->ShortLong() <= 0)
   {
      int m = n-ix; bool found = false;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) { REPORT return false; }
      REPORT
   }
   else
   {
      int m = ix; bool found = false;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G2)->Matches(s, offset + ix, i) )
            { found = true; ix += i; break; }
      if (!found) { REPORT return false; }
      REPORT
   }

   REPORT return true;


}

bool LTGString::Matches(const String& s, uint offset, uint length)
{
   Tracer TR("LTGString::Matches");
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;

   unsigned int n1, n2;

   short int p2 = ((GString*&)G2)->ProbeRight(s, offset, n, n2);
   if (p2 == -1) { REPORT return false; }

   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset, n, n1);
   if (p1 == -1) { REPORT return false; }

   if (p1 == 1 && p2 == 1)
   {
      if (n1 + n2 == n) { split = n1; REPORT return true; }
      else { REPORT return false; }
   }

   if (p2 == 1)
   {
      if (((GString*&)G1)->Matches(s, offset, n-n2))
         { split = n-n2; REPORT return true; }
      else { REPORT return false; }
   }

   if (p1 == 1)
   {
      // cannot be sure of fit even if we get match in following
      if ( !(((GString*&)G2)->Matches(s, offset+n1, n-n1)) )
         { REPORT return false; }
      REPORT
   }
   else { REPORT n1 = String::npos; }

/*
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;
   unsigned int n1 = G1->FixedLength(); unsigned int n2 = G2->FixedLength();

   // if second of strings is of fixed length no iteration is necessary

   if (n2 != String::npos)
   {
      if (n2 > n) return false;
      split = n - n2;
      return ((GString*&)G1)->Matches(s, offset, n-n2)
         && ((GString*&)G2)->Matches(s, offset + n-n2, n2);
   }

   if (n1 != String::npos)
   {
      if ( !(((GString*&)G1)->Matches(s, offset, n1)
         && ((GString*&)G2)->Matches(s, offset + n1, n-n1)) )
         return false;
   }
*/
   // divide s into a first part to match G1 and a second part to match G2
   // iterate over division points

   if (G2->ShortLong() >= 0)
   {
      int m = (n1 != String::npos) ? n1 : n;
      for (int i = 0; i <= m; i++)
         if ( ((GString*&)G2)->Matches(s, offset + i, n-i) )
         {
            if ( ((GString*&)G1)->Matches(s, offset, i) )
               { split = i; REPORT return true; }
            REPORT return false;
         }
      REPORT return false;
   }
   else
   {
      int m = (n1 != String::npos) ? n1 : 0;
      for (int i = n; i >= m; i--)
         if ( ((GString*&)G2)->Matches(s, offset + i, n-i) )
         {
            if ( ((GString*&)G1)->Matches(s, offset, i) )
               { split = i; REPORT return true; }
            REPORT return false;
         }
      REPORT return false;
   }
}

bool NotGString::Matches(const String& s, uint offset, uint length)
   { REPORT return ! ((GString*&)G)->Matches(s, offset, length); }

bool AnyString::Matches(const String& s, uint offset, uint length)
   { S = s.substr(offset, length); REPORT return true; }

bool FixedLengthString::Matches(const String& s, uint offset, uint length)
{
   String ss = s.substr(offset, length);
   if (ss.size() == N) { S = ss; REPORT return true; }
   else { S = ""; REPORT return false; }
}

bool Dots::Matches(const String&, uint, uint)
   { REPORT return true; }

bool FixedLengthDots::Matches(const String& s, uint offset, uint length)
{
   String ss = s.substr(offset, length);
   REPORT return (ss.size() == N);
}

bool WhiteSpace::Matches(const String& s, uint offset, uint length)
{
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;
   if (offset > 0 && Contains(ws_chars, s[offset-1]) ) { REPORT return false; }
   if (s.size() > n + offset
      && Contains(ws_chars, s[n + offset]) ) { REPORT return false; }
   if (n == 0) { REPORT return false; }
   REPORT return ContainsOnly(s.substr(offset, n), ws_chars);
}

bool OptionalWhiteSpace::Matches(const String& s, uint offset, uint length)
{
   unsigned int n = (length == String::npos) ? (s.size() - offset) : length;
   if (offset > 0 && Contains(ws_chars, s[offset-1]) ) { REPORT return false; }
   if (s.size() > n + offset
      && Contains(ws_chars, s[n + offset]) ) { REPORT return false; }
   if (n == 0) { REPORT return true; }
   REPORT return ContainsOnly(s.substr(offset, n), ws_chars);
}

void GString::Collect(const String& s, StringList& SL)
   { REPORT SL.push_back(s); }

void AndGString::Collect(const String& s, StringList& SL)
{
   Tracer TR("AndGString::Collect");
   REPORT
   ((GString*&)G1)->Collect(s, SL); ((GString*&)G2)->Collect(s, SL);
}

void OrGString::Collect(const String& s, StringList& SL)
{
   Tracer TR("OrGString::Collect");
   if (which == 1)
      { REPORT SL.push_back("1"); ((GString*&)G1)->Collect(s, SL); }
   else if (which == 2)
      { REPORT SL.push_back("2"); ((GString*&)G2)->Collect(s, SL); }
}

void XorGString::Collect(const String& s, StringList& SL)
{
   Tracer TR("XorGString::Collect");
   if (which == 1)
      { REPORT SL.push_back("1"); ((GString*&)G1)->Collect(s, SL); }
   else if (which == 2)
      { REPORT SL.push_back("2"); ((GString*&)G2)->Collect(s, SL); }
}

void PlusGString::Collect(const String& s, StringList& SL)
{
   Tracer TR("PlusGString::Collect");
   REPORT
   ((GString*&)G1)->Collect(s.substr(0,split), SL);
   ((GString*&)G2)->Collect(s.substr(split,s.size()-split), SL);
}

void GString::Translate(String& s, StringList& SL)
   { REPORT s += SL.pop_front(); }

void ExplicitString::Translate(String& s, StringList& SL)
  { REPORT s += S; SL.pop_front(); }

void AndGString::Translate(String& s, StringList& SL)
{
   REPORT
   ((GString*&)G1)->Translate(s, SL);
   ((GString*&)G2)->Translate(s, SL);
}

void OrGString::Translate(String& s, StringList& SL)
{
   String w = SL.pop_front();
   if (w == "1") { REPORT ((GString*&)G1)->Translate(s, SL); }
   else if (w == "2") { REPORT ((GString*&)G2)->Translate(s, SL); }
}

void XorGString::Translate(String& s, StringList& SL)
{
   String w = SL.pop_front();
   if (w == "1") { REPORT ((GString*&)G1)->Translate(s, SL); }
   else if (w == "2") { REPORT ((GString*&)G2)->Translate(s, SL); }
}

void PlusGString::Translate(String& s, StringList& SL)
{
   REPORT
   ((GString*&)G1)->Translate(s, SL);
   ((GString*&)G2)->Translate(s, SL);
}

void NotGString::Translate(String&, StringList& SL) { REPORT SL.pop_front(); }

void AnyString::Translate(String& s, StringList& SL)
   { REPORT s += S; SL.pop_front(); }

int PairGString::ShortLong() const
{
   if (G1->ShortLong() == G2->ShortLong()) { REPORT return G1->ShortLong(); }
   if (G1->ShortLong() <= 0 && G2->ShortLong() <= 0) { REPORT return -1; }
   if (G1->ShortLong() >= 0 && G2->ShortLong() >= 0) { REPORT return 1; }
   REPORT return 0;
}

unsigned int AndGString::FixedLength() const
{
   if (G1->FixedLength() == G2->FixedLength())
      { REPORT return G1->FixedLength(); }
   if (G1->FixedLength() == String::npos) { REPORT return G2->FixedLength(); }
   if (G2->FixedLength() == String::npos) { REPORT return G1->FixedLength(); }
   REPORT return String::npos;
}

unsigned int OrGString::FixedLength() const
{
   if (G1->FixedLength() == G2->FixedLength())
      { REPORT return G1->FixedLength(); }
   else { REPORT return String::npos; }
}

unsigned int XorGString::FixedLength() const
{
   if (G1->FixedLength() == G2->FixedLength())
      { REPORT return G1->FixedLength(); }
   else { REPORT return String::npos; }
}

unsigned int PlusGString::FixedLength() const
{
   if (G1->FixedLength() != String::npos && G2->FixedLength() != String::npos)
      { REPORT return G1->FixedLength() + G2->FixedLength(); }
   else { REPORT return String::npos; }
}

// ProbeLeft and ProbeRight -
//    return -1 if a fit is impossible;
//    return 1 if there is a unique fit (return length of string used to fl);
//    return 0 if can't tell or fit is not unique

short int ExplicitString::ProbeLeft(const String& s, uint offset, uint length,
   uint& fl)
{
   Tracer TR("ExplicitString::ProbeLeft");
   if (length == String::npos) length = s.size() - offset;
   unsigned int n = S.size();
   if (n > length) { REPORT return -1; }
   if (S == s.substr(offset, n)) { fl = n; REPORT return 1; }
   REPORT return -1;
}

short int ExplicitString::ProbeRight(const String& s, uint offset, uint length,
   uint& fl)
{
   Tracer TR("ExplicitString::ProbeRight");
   if (length == String::npos) length = s.size() - offset;
   unsigned int n = S.size();
   if (n > length) { REPORT return -1; }
   if (S == s.substr(offset + length - n, n)) { fl = n; REPORT return 1; }
   REPORT return -1;
}


short int CIString::ProbeLeft(const String& s, uint offset, uint length,
   uint& fl)
{
   Tracer TR("CIString::ProbeLeft");
   if (length == String::npos) length = s.size() - offset;
   unsigned int n = S.size();
   if (n > length) { REPORT return -1; }
   String us = s.substr(offset, n); UpperCase(us);
   if (S == us) { fl = n; REPORT return 1; }
   REPORT return -1;
}

short int CIString::ProbeRight(const String& s, uint offset, uint length,
   uint& fl)
{
   Tracer TR("CIString::ProbeRight");
   if (length == String::npos) length = s.size() - offset;
   unsigned int n = S.size();
   if (n > length) { REPORT return -1; }
   String us = s.substr(offset + length - n, n); UpperCase(us);
   if (S == us) { fl = n; REPORT return 1; }
   REPORT return -1;
}


short int AndGString::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("AndGString::ProbeLeft");
   uint fl1, fl2;
   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset, length, fl1);
   short int p2 = ((GString*&)G2)->ProbeLeft(s, offset, length, fl2);
   if (p1 == -1 || p2 == -1) { REPORT return -1; }
   if (p1 == 0 || p2 == 0) { REPORT return 0; }
   if (fl1 == fl2) { fl = fl1; REPORT return 1; }
   else { REPORT return 0; }
}

short int AndGString::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("AndGString::ProbeRight");
   uint fl1, fl2;
   short int p1 = ((GString*&)G1)->ProbeRight(s, offset, length, fl1);
   short int p2 = ((GString*&)G2)->ProbeRight(s, offset, length, fl2);
   if (p1 == -1 || p2 == -1) { REPORT return -1; }
   if (p1 == 0 || p2 == 0) { REPORT return 0; }
   if (fl1 == fl2) { fl = fl1; REPORT return 1; }
   else { REPORT return 0; }
}


short int OrGString::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("OrGString::ProbeLeft");
   uint fl1, fl2;
   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset, length, fl1);
   if (p1 == 0) { REPORT return 0; }
   short int p2 = ((GString*&)G2)->ProbeLeft(s, offset, length, fl2);
   if (p1 == -1 && p2 == -1) { REPORT return -1; }
   if (p1 == 1 && p2 == 1 && fl1 == fl2)
      { fl = fl1; which = 1; REPORT return 1; }
   REPORT return 0;
}

short int OrGString::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("OrGString::ProbeRight");
   uint fl1, fl2;
   short int p1 = ((GString*&)G1)->ProbeRight(s, offset, length, fl1);
   if (p1 == 0) { REPORT return 0; }
   short int p2 = ((GString*&)G2)->ProbeRight(s, offset, length, fl2);
   if (p1 == -1 && p2 == -1) { REPORT return -1; }
   if (p1 == 1 && p2 == 1 && fl1 == fl2)
      { fl = fl1; which = 1; REPORT return 1; }
   if (p1 == 1 && p2 == -1) { fl = fl1; which = 1; REPORT return 1; }
   if (p1 == -1 && p2 == 1) { fl = fl2; which = 2; REPORT return 1; }
   REPORT return 0;
}


short int XorGString::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("XorGString::ProbeLeft");
   uint fl1, fl2;
   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset, length, fl1);
   if (p1 == 0) { REPORT return 0; }
   short int p2 = ((GString*&)G2)->ProbeLeft(s, offset, length, fl2);
   if (p1 == -1 && p2 == -1) { REPORT return -1; }
   if (p1 == 1 && p2 == 1 && fl1 == fl2) { REPORT return -1; }
   if (p1 == -1 && p2 == 1) { fl = fl2; which = 2; REPORT return 1; }
   if (p1 == 1 && p2 == -1) { fl = fl1; which = 1; REPORT return 1; }
   REPORT return 0;
}

short int XorGString::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("XorGString::ProbeRight");
   uint fl1, fl2;
   short int p1 = ((GString*&)G1)->ProbeRight(s, offset, length, fl1);
   if (p1 == 0) { REPORT return 0; }
   short int p2 = ((GString*&)G2)->ProbeRight(s, offset, length, fl2);
   if (p1 == -1 && p2 == -1) { REPORT return -1; }
   if (p1 == 1 && p2 == 1 && fl1 == fl2) { REPORT return -1; }
   if (p1 == -1 && p2 == 1) { fl = fl2; which = 2; REPORT return 1; }
   if (p1 == 1 && p2 == -1) { fl = fl1; which = 1; REPORT return 1; }
   REPORT return 0;
}


short int PlusGString::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("PlusGString::ProbeLeft");
   if (length == String::npos) length = s.size() - offset;
   unsigned int n1;
   short int p1 = ((GString*&)G1)->ProbeLeft(s, offset, length, n1);
   if (p1 == 1)
   {
      unsigned int n2;
      short int p2 = ((GString*&)G2)->ProbeLeft(s, offset+n1, length-n1, n2);
      if (p2 == 1) { REPORT fl = split = n1 + n2; }
      REPORT return p2;
   }
   REPORT return p1;
}

short int PlusGString::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("PlusGString::ProbeRight");
   if (length == String::npos) length = s.size() - offset;
   unsigned int n2;
   short int p2 = ((GString*&)G2)->ProbeRight(s, offset, length, n2);
   if (p2 == 1)
   {
      unsigned int n1;
      short int p1 = ((GString*&)G1)->ProbeRight(s, offset, length-n2, n1);
      if (p1 == 1) { REPORT fl = split = length - n1 + n2; }
      REPORT return p1;
   }
   REPORT return p2;
}


short int FixedLengthString::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("FixedLengthString::ProbeLeft");
   if (length == String::npos) length = s.size() - offset;
   if (N <= length) { fl = N; S = s.substr(offset, N); REPORT return 1; }
   REPORT return -1;
}

short int FixedLengthString::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("FixedLengthString::ProbeRight");
   if (length == String::npos) length = s.size() - offset;
   if (N <= length)
      { fl = N; S = s.substr(offset + length - N, N); REPORT return 1; }
   REPORT return -1;
}

short int FixedLengthDots::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("FixedLengthDots::ProbeLeft");
   if (length == String::npos) length = s.size() - offset;
   if (N <= length) { fl = N; REPORT return 1; }
   REPORT return -1;
}

short int FixedLengthDots::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("FixedLengthDots::ProbeRight");
   if (length == String::npos) length = s.size() - offset;
   if (N <= length) { fl = N; REPORT return 1; }
   REPORT return -1;
}


short int WhiteSpace::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("WhiteSpace::ProbeLeft");
   if (length == String::npos) length = s.size() - offset;
   if (offset > 0 && Contains(ws_chars, s[offset-1])) { REPORT return -1; }
   uint i = s.find_first_not_of(ws_chars,offset);
   if (i == offset) { REPORT return -1; }
   if (i == String::npos || i >= length+offset)
   {
      if (s.size() == length+offset) { fl = length; REPORT return 1; }
      else { REPORT return -1; }
   }
   fl = i-offset; REPORT return 1;
}

short int WhiteSpace::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("WhiteSpace::ProbeRight");
   if (length == String::npos) length = s.size() - offset;
   if (offset+length < s.size() && Contains(ws_chars, s[offset+length]))
      { REPORT return -1; }
   uint i = s.substr(offset,length).find_last_not_of(ws_chars);
   if (i == length - 1) { REPORT return -1; }
   if (i == String::npos)
   {
      if (offset == 0) { fl = length; REPORT return 1; }
      else { REPORT return -1; }
   }
   fl = length - i - 1; REPORT return 1;
}


short int OptionalWhiteSpace::ProbeLeft(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("OptionalWhiteSpace::ProbeLeft");
   if (length == String::npos) length = s.size() - offset;
   if (offset > 0 && Contains(ws_chars, s[offset-1])) { REPORT return -1; }
   uint i = s.find_first_not_of(ws_chars,offset);
   if (i == String::npos || i >= length+offset)
   {
      if (s.size() == length+offset) { fl = length; REPORT return 1; }
      else { REPORT return -1; }
   }
   fl = i-offset; REPORT return 1;
}

short int OptionalWhiteSpace::ProbeRight(const String& s, uint offset,
   uint length, uint& fl)
{
   Tracer TR("OptionalWhiteSpace::ProbeRight");
   if (length == String::npos) length = s.size() - offset;
   if (offset+length < s.size() && Contains(ws_chars, s[offset+length]))
      { REPORT return -1; }
   uint i = s.substr(offset,length).find_last_not_of(ws_chars);
   if (i == String::npos)
   {
      if (offset == 0) { fl = length; REPORT return 1; }
      else { REPORT return -1; }
   }
   fl = length - i - 1; REPORT return 1;
}


// functions

CIString CI(const String& s) { REPORT return CIString(s); }

CIString CI(const char* s) { REPORT return CIString(String(s)); }

int s(String& S, const GString& g1, const GString& g2)
{
   REPORT
   if (!((GString&)g1).Matches(S)) return 0;
   StringList Input;
   ((GString&)g1).Collect(S, Input);
   S.erase();
   ((GString&)g2).Translate(S, Input);
   return 1;
}

int sf(String& S, const SubstitutionList& sx)
{
   REPORT
   int c = 0;
   StringList::const_iterator m = sx.out().begin();
   for (StringList::const_iterator k = sx.in().begin(); k != sx.in().end(); ++k)
      { c += sf(S, *k, *m); ++m; }
   return c;
}

int sl(String& S, const SubstitutionList& sx)
{
   REPORT
   int c = 0;
   StringList::const_iterator m = sx.out().begin();
   for (StringList::const_iterator k = sx.in().begin(); k != sx.in().end(); ++k)
      { c += sl(S, *k, *m); ++m; }
   return c;
}

int sa(String& S, const SubstitutionList& sx)
{
   REPORT
   int c = 0;
   StringList::const_iterator m = sx.out().begin();
   for (StringList::const_iterator k = sx.in().begin(); k != sx.in().end(); ++k)
      { c += sa(S, *k, *m); ++m; }
   return c;
}



// statics

String GString::ws_chars = " \t\r\n";    // white space characters

// globals - declarations

InitialGString GS;
Dots DOTS;
LongestDots LDOTS;
ShortestDots SDOTS;
FixedLengthDots DOT(1);           // single character
WhiteSpace WS;
OptionalWhiteSpace OWS;

#ifdef use_namespace
}
#endif



