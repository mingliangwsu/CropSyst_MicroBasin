// character string manipulation library and string list

#define WANT_STREAM
#define WANT_MATH

#include "include.h"
#include "str.h"
#include "gstring.h"
#include "str_fns.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif


#ifdef DO_REPORT
#define REPORT { static ExeCounter ExeCount(__LINE__,2); ++ExeCount; }
#else
#define REPORT {}
#endif


void StringListItem::InsertBefore(const String& s)
{
   REPORT
   StringListItem* SLI = new StringListItem(s, SL);
   SLI->next = this; SLI->previous = previous;
   previous->next = SLI; previous = SLI;
   SL->N++;
}

void StringListItem::InsertAfter(const String& s)
{
   REPORT
   StringListItem* SLI = new StringListItem(s, SL);
   SLI->next = next; SLI->previous = this;
   next->previous = SLI; next = SLI;
   SL->N++;
}

StringListItem* StringListItem::Find(const String& s) const
{
   for (StringListItem* SLI = next; SLI != SL; SLI = SLI->next)
      if (SLI->S == s) { REPORT return SLI; }
   REPORT return 0;
}

StringList::StringList(StringList& sl) : N(0)
{
   REPORT previous = this; next = this; SL = this;
   for (StringList::iterator i = sl.begin(); i != sl.end(); i++) push_back(*i);
}

void StringList::operator=(StringList& sl)
{
   REPORT CleanUp();
   for (StringList::iterator i = sl.begin(); i != sl.end(); i++) push_back(*i);
}




StringList::iterator StringList::find(const String& s)
   { REPORT return find(s, begin()); }

StringList::reverse_iterator StringList::rfind(const String& s)
   { REPORT return rfind(s, rbegin()); }

StringList::iterator StringList::find(const String& s, StringList::iterator i)
{
   for (; i != end(); i++) if (*i == s) { REPORT return i; }
   REPORT return end();
}

StringList::reverse_iterator
   StringList::rfind(const String& s, StringList::reverse_iterator i)
{
   for (; i != rend(); i++) if (*i == s) { REPORT return i; }
   REPORT return rend();
}


StringList::const_iterator StringList::find(const String& s) const
   { REPORT return find(s, begin()); }

StringList::const_reverse_iterator StringList::rfind(const String& s) const
   { REPORT return rfind(s, rbegin()); }

StringList::const_iterator
   StringList::find(const String& s, StringList::const_iterator i) const
{
   for (; i != end(); i++) if (*i == s) { REPORT return i; }
   REPORT return end();
}

StringList::const_reverse_iterator
   StringList::rfind(const String& s, StringList::const_reverse_iterator i)
   const
{
   for (; i != rend(); i++) if (*i == s) { REPORT return i; }
   REPORT return rend();
}


StringListItem::~StringListItem()
   { REPORT previous->next = next; next->previous = previous; SL->N--; }

String StringList::pop_back()
   { REPORT String s = previous->S; previous->Delete(); return s; }

String StringList::pop_front()
   { REPORT String s = next->S; next->Delete(); return s; }

void StringList::CleanUp()
{
   REPORT
   StringListItem* SLI1;
   for (StringListItem* SLI = next; SLI != this; SLI = SLI1)
   {  SLI1 = SLI->next; delete SLI; }
}

// word wrap to fit into page of width "width"
void StringList::Format(unsigned int width, StringList& sl)
{
   REPORT
   String S2; S2.reserve(512);
   unsigned int q = 0;            // location on output string
   for (StringList::iterator i = begin(); i != end(); i++)
   {
      unsigned int p = 0;         // location on input string
      String& S1 = *i; unsigned int n = S1.size(); unsigned int s;

      if (n == 0)                 // blank line
      {
         REPORT
         if (q > 0) { sl.push_back(S2); S2.erase(); }   // clear pending
         sl.push_back(S2); q = 0;                       // blank line
         continue;
      }
      else if (S1[0] == ' ')      // line beginning with space
      {
         REPORT
         if (q > 0) { REPORT sl.push_back(S2); S2.erase(); }   // clear pending
         q = S1.find_first_not_of(' ');
         if (q != String::npos) { REPORT S2.append(q, ' '); p = q; }
         else { REPORT sl.push_back(S2); q = 0; continue; } // only sp. on line
      }
      else if (q > 0) { REPORT S2 += ' '; q++; }

      do
      {
         REPORT
         unsigned int w = S1.find(' ', p);         // char after next word
         if (w == String::npos) { REPORT w = n; s = n; }
         else
         {
            REPORT
            s = S1.find_first_not_of(' ',w);       // beg. of following word
            if (s == String::npos) s = n;
         }
         // p = letters processed so far
         // w = letters processed so far plus next word
         // s = letters processed so far plus next word plus next spaces
         if (q + w - p >= width && q != 0)     // won't fit in space
                                               // & word would fit in a line
         {
            REPORT
            if (S2[q-1] == ' ') { REPORT S2.erase(q-1,1); }
            sl.push_back(S2); S2.erase(); q=0;
         }
         S2 += S1.substr(p, s-p); q += s-p; p=s;
      }
      while (s != n);
   }
   if (q>0)
   {
      REPORT
      if (S2[q-1] == ' ') S2.erase(q-1,1);
      sl.push_back(S2);
   }
}

ostream& operator<<(ostream& os, StringList& sl)
{
   REPORT
   for (StringListItem* word = sl.Next(); word != &sl; word = word->Next())
      os << word->Value() << endl;
   return os;
}

void operator>>(istream& is, StringList& sl)
   { REPORT while (!is.eof()) { String s; getline(is, s); sl.push_back(s); } }

TaggedStringList StringList::All()
   { REPORT return TaggedStringList(*this); }


TaggedStringList::iterator
   TaggedStringList::iterator::operator++()
{
   REPORT
   do SLI = SLI->Next();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}

TaggedStringList::iterator
   TaggedStringList::iterator::operator--()
{
   REPORT
   do SLI = SLI->Previous();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}

TaggedStringList::reverse_iterator
   TaggedStringList::reverse_iterator::operator++()
{
   REPORT
   do SLI = SLI->Previous();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}

TaggedStringList::reverse_iterator
   TaggedStringList::reverse_iterator::operator--()
{
   REPORT
   do SLI = SLI->Next();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}


TaggedStringList::const_iterator
   TaggedStringList::const_iterator::operator++()
{
   REPORT
   do SLI = SLI->Next();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}

TaggedStringList::const_iterator
   TaggedStringList::const_iterator::operator--()
{
   REPORT
   do SLI = SLI->Previous();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}

TaggedStringList::const_reverse_iterator
   TaggedStringList::const_reverse_iterator::operator++()
{
   REPORT
   do SLI = SLI->Previous();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}

TaggedStringList::const_reverse_iterator
   TaggedStringList::const_reverse_iterator::operator--()
{
   REPORT
   do SLI = SLI->Next();
   while (! TSL->Select(*SLI)  && SLI != &(TSL->get_sl()) );
   return *this;
}


ostream& operator<<(ostream& os, const TaggedStringList& tsl)
{
   Tracer("<< TaggedStringList");
   REPORT
   for (TaggedStringList::const_iterator i = tsl.begin(); i != tsl.end(); i++)
      os << *i << endl;
   return os;
}

int TaggedStringList::sf(const String& s1, const String& s2, iterator i)
{
   Tracer TR("TaggedStringList::sf");
   unsigned int p = i->find(s1); if (p == String::npos) { REPORT return 0; }
   i->replace(p, s1.size(), s2);
   REPORT
   return 1;
}

int TaggedStringList::sl(const String& s1, const String& s2, iterator i)
{
   Tracer TR("TaggedStringList::sl");
   unsigned int p = i->rfind(s1); if (p == String::npos)
      { REPORT return 0; }
   i->replace(p, s1.size(), s2);
   REPORT
   return 1;
}

int TaggedStringList::sa(const String& s1, const String& s2, iterator i)
{
   Tracer TR("TaggedStringList::sa");
   int n = s1.size(); if (n == 0) { REPORT return 0; }
   int c = 0;
   for (unsigned int p = 0; ;)
   {
      p = i->find(s1, p); if (p == String::npos) { REPORT return c; }
      i->replace(p, n, s2); p += s2.size(); ++c;
   }
}

int TaggedStringList::sf(const SubstitutionList& sx, iterator i)
{
   REPORT
   int c = 0;
   StringList::const_iterator m = sx.out().begin();
   for (StringList::const_iterator k = sx.in().begin(); k != sx.in().end(); ++k)
      { c += sf(*k, *m, i); ++m; }
   return c;
}

int TaggedStringList::sl(const SubstitutionList& sx, iterator i)
{
   REPORT
   int c = 0;
   StringList::const_iterator m = sx.out().begin();
   for (StringList::const_iterator k = sx.in().begin(); k != sx.in().end(); ++k)
      { c += sl(*k, *m, i); ++m; }
   return c;
}

int TaggedStringList::sa(const SubstitutionList& sx, iterator i)
{
   REPORT
   int c = 0;
   StringList::const_iterator m = sx.out().begin();
   for (StringList::const_iterator k = sx.in().begin(); k != sx.in().end(); ++k)
      { c += sa(*k, *m, i); ++m; }
   return c;
}

int TaggedStringList::s(const GString& g1, const GString& g2, iterator i)
{
   Tracer TR("TaggedStringList::s");
   String& S = *i;
   if (!((GString&)g1).Matches(S)) { REPORT return 0; } // can we do this better
   StringList Input;
   ((GString&)g1).Collect(S, Input);          // can we do this better
   S.erase();
   ((GString&)g2).Translate(S, Input);        // can we do this better
   REPORT
   return 1;
}

#ifdef use_namespace

void TaggedStringList::UpperCase(iterator i)
   { REPORT RBD_STRING::UpperCase(*i); }

void TaggedStringList::LowerCase(iterator i)
   { REPORT RBD_STRING::LowerCase(*i); }

#else

void TaggedStringList::UpperCase(iterator i)
   { REPORT ::UpperCase(*i); }

void TaggedStringList::LowerCase(iterator i)
   { REPORT ::LowerCase(*i); }

#endif

int TaggedStringList::erase()
{
   REPORT
   int c = 0;
   iterator i1;
   for (iterator i = begin(); i != end(); i = i1)
      { i1 = i; i1++; erase(i); ++c; }
   return c;
}

int TaggedStringList::insert_before(const String& s)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) { insert_before(s, i); ++c; }
   return c;
}

int TaggedStringList::insert_after(const String& s)
{
   REPORT
   int c = 0;
   iterator i1;
   for (iterator i = begin(); i != end(); i = i1 )
      { i1 = i; i1++; insert_after(s, i); ++c; }
   return c;
}

int TaggedStringList::sf(const String& s1, const String& s2)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) c += sf(s1, s2, i);
   return c;
}

int TaggedStringList::sl(const String& s1, const String& s2)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) c += sl(s1, s2, i);
   return c;
}

int TaggedStringList::sa(const String& s1, const String& s2)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) c += sa(s1, s2, i);
   return c;
}

int TaggedStringList::sf(const SubstitutionList& sx)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) c += sf(sx, i);
   return c;
}

int TaggedStringList::sl(const SubstitutionList& sx)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) c += sl(sx, i);
   return c;
}

int TaggedStringList::sa(const SubstitutionList& sx)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) c += sa(sx, i);
   return c;
}

int TaggedStringList::s(const GString& g1, const GString& g2)
{
   REPORT
   int c = 0;
   for (iterator i = begin(); i != end(); i++) c += s(g1, g2, i);
   return c;
}

void TaggedStringList::UpperCase()
   { REPORT for (iterator i = begin(); i != end(); i++) UpperCase(i); }

void TaggedStringList::LowerCase()
   { REPORT for (iterator i = begin(); i != end(); i++) LowerCase(i); }

int TaggedStringList::size()
{
   REPORT int n = 0;
   for (iterator i = begin(); i != end(); i++) n++;
   return n;
}


StringList_String StringList::operator()(const String& s)
{
   Tracer TR("StringList::operator()(const String& s)");
   REPORT return StringList_String(*this, s);
}

StringList_GString StringList::operator()(const GString& gs)
{
   Tracer TR("StringList::operator()(const GString& gs)");
   REPORT return StringList_GString(*this, (GString&)gs);
}

StringList_Range StringList::operator()(const String& s1, const String& s2,
   int ends)
   { REPORT return StringList_Range(*this, s1, s2, ends); }

bool StringList_Range::Select(const StringListItem& SLI) const
{
   // assume we are moving in the forward direction
   // and select is called every iteration

   if (ChangeNext)
   {
      REPORT
      ((StringList_Range&)(*this)).ChangeNext = false;
      ((StringList_Range&)(*this)).Selected = !Selected;
   }

   if (Selected)
   {
      REPORT
      if (SLI.ConstValue().find(Target2) != String::npos)     // found Target2
      {
         if (Ends & 1)
            { REPORT ((StringList_Range&)(*this)).ChangeNext = true; }
         else { REPORT ((StringList_Range&)(*this)).Selected = false; }
      }
   }
   else
   {
      REPORT
      if (SLI.ConstValue().find(Target1) != String::npos)     // found Target1
      {
         if ( !(Ends & 2) )
            { REPORT ((StringList_Range&)(*this)).ChangeNext = true; }
         else { REPORT ((StringList_Range&)(*this)).Selected = true; }
      }
   }

   return Selected;
}


//StringList_GString StringList::operator()(GString& gs1, GString& gs2)
//{
//   return StringList_GString(*this, gs1, gs2);
//}


/*
MaskedStringList StringList::operator[](GString& g)
{
   MaskedStringList TSL(*this);
   int m = 0; unsigned char mask = 128;
   for (StringListItem* sli = Next(); sli != this; sli = sli->Next())
   {
      if ( g.Matches(sli->Value()) ) TSL.Mask[m] |= mask;
      mask >>= 1;
      if (!mask) { m++; mask = 128; }
   }
   return TSL;
}

ostream& operator<<(ostream& os, MaskedStringList& tsl)
{
   StringList& sl = tsl.SL;
   int m = 0; unsigned char mask = 128;
   for (StringListItem* word = sl.Next(); word != &sl; word = word->Next())
   {
      if (tsl.Mask[m] & mask) os << word->Value() << endl;
      mask >>= 1;
      if (!mask) { m++; mask = 128; }

   }
   return os;
}

*/

SubstitutionList& SubstitutionList::operator<<(const String& S)
{
   if (first) { REPORT input.push_back(S); }
   else { REPORT output.push_back(S); }
   first = !first;
   return *this;
}

/************************* ExeCounter functions *****************************/

#ifdef DO_REPORT

int ExeCounter::nreports;                      // will be set to zero

ExeCounter::ExeCounter(int xl, int xf) : line(xl), fileid(xf), nexe(0) {}

ExeCounter::~ExeCounter()
{
   nreports++;
   cout << "REPORT  " << setw(6) << nreports << "  "
      << setw(6) << fileid << "  " << setw(6) << line
      << "  " << setw(6) << nexe << "\n";
}

#endif


#ifdef use_namespace
}
#endif


