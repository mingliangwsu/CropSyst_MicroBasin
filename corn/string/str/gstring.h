// String list

#ifndef GSTRING_LIB
#define GSTRING_LIB

//#define DO_REPORT                     // to activate REPORT


#include "str.h"
#include "str_fns.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif



class StringListItem;
   class StringList;
class TaggedStringList;
   class StringList_String;
   class StringList_GString;
   class StringList_Range;
   // class MaskedStringList;
class SubstitutionList;
class GString;
   class ExplicitString;
      class CIString;
   class PairGString;
      class AndGString;
      class OrGString;
      class XorGString;
      class PlusGString;
         class GTGString;
            class GTGString2;
         class LTGString;
   class NotGString;
   class AnyString;
      class LongestString;
      class ShortestString;
      class FixedLengthString;
   class Dots;
      class LongestDots;
      class ShortestDots;
      class FixedLengthDots;
   class WhiteSpace;
      class OptionalWhiteSpace;
class InitialGString;


class StringListItem
{
protected:
   String S;                          // the string in this item
   StringListItem* previous;          // previous item in list
   StringListItem* next;              // next item in list
   StringList* SL;                    // parent StringList object
   StringListItem(const String& s, StringList* sl) : S(s), SL(sl) {}
   StringListItem() {}
public:
   String& Value() { return S; }
   const String& ConstValue() const { return S; }
   StringListItem* Next() const { return next; }
   StringListItem* Previous() const { return previous; }
   void Replace(const String& s) { S = s; }
   void InsertBefore(const String& s);
   void InsertAfter(const String& s);
   void Delete() { delete this; }
   StringListItem* Find(const String& s) const;   // next example of this
   ~StringListItem();
   friend class StringList;
};

class StringList : public StringListItem
{
// previous points to last item in list
// next points to next item in list
// S is left blank

   unsigned int N;                 // length of list
public:
   void push_back(const String& s) { InsertBefore(s); }
   void push_front(const String& s) { InsertAfter(s); }
   String pop_back();              // return last in and remove it from list
   String pop_front();             // return first in and remove it from list
   void CleanUp();
   StringList() : N(0)
      { previous = this; next = this; SL = this; }
   StringList(StringList& SL);
   void operator=(StringList& SL);
   ~StringList() { CleanUp(); }
   StringList_String operator()(const String& s);
   StringList_GString operator()(const GString& g);
   StringList_Range operator()
      (const String& s1, const String& s2, int ends = 3);
   //StringList_GString operator()(GString& g1, GString& g2);
   TaggedStringList All();
   void Format(unsigned int width, StringList& sl);
   int size() { return N; }
   friend class StringListItem;
   friend class TaggedStringList;
   friend STD_NS ostream& operator<<(STD_NS ostream& os, StringList& sl);
   friend void operator>>(STD_NS istream& is, StringList& sl);

   class iterator
   {
      StringListItem* SLI;
      iterator(StringListItem* sli) : SLI(sli) {}
   public:
      iterator() : SLI(0) {}
      iterator operator++() { SLI = SLI->Next(); return *this; }
      iterator operator--() { SLI = SLI->Previous(); return *this; }
      iterator operator++(int)
         { iterator i = *this; SLI = SLI->Next(); return i; }
      iterator operator--(int)
         { iterator i = *this; SLI = SLI->Previous(); return i; }
      String& operator*() { return SLI->Value(); }
      bool operator==(const iterator& i) const { return SLI == i.SLI; }
      bool operator!=(const iterator& i) const { return SLI != i.SLI; }
      String* operator->() { return &(SLI->Value()); }
      friend class StringList;
   };
   iterator begin() { return iterator(Next()); }
   iterator end() { return iterator(this); }

   class const_iterator
   {
      const StringListItem* SLI;
      const_iterator(const StringListItem* sli) : SLI(sli) {}
   public:
      const_iterator() : SLI(0) {}
      const_iterator operator++() { SLI = SLI->Next(); return *this; }
      const_iterator operator--() { SLI = SLI->Previous(); return *this; }
      const_iterator operator++(int)
         { const_iterator i = *this; SLI = SLI->Next(); return i; }
      const_iterator operator--(int)
         { const_iterator i = *this; SLI = SLI->Previous(); return i; }
      const String operator*() { return SLI->ConstValue(); }
      bool operator==(const const_iterator& i) const { return SLI == i.SLI; }
      bool operator!=(const const_iterator& i) const { return SLI != i.SLI; }
      const String* operator->() { return &(SLI->ConstValue()); }
      friend class StringList;
   };
   const_iterator begin() const { return const_iterator(Next()); }
   const_iterator end() const { return const_iterator(this); }

   class reverse_iterator
   {
      StringListItem* SLI;
      reverse_iterator(StringListItem* sli) : SLI(sli) {}
   public:
      reverse_iterator() : SLI(0) {}
      reverse_iterator operator++() { SLI = SLI->Previous(); return *this; }
      reverse_iterator operator--() { SLI = SLI->Next(); return *this; }
      reverse_iterator operator++(int)
         { reverse_iterator i = *this; SLI = SLI->Previous(); return i; }
      reverse_iterator operator--(int)
         { reverse_iterator i = *this; SLI = SLI->Next(); return i; }
      String& operator*() { return SLI->Value(); }
      bool operator==(const reverse_iterator& i) const { return SLI == i.SLI; }
      bool operator!=(const reverse_iterator& i) const { return SLI != i.SLI; }
      String* operator->() { return &(SLI->Value()); }
      friend class StringList;
   };
   reverse_iterator rbegin() { return reverse_iterator(Previous()); }
   reverse_iterator rend() { return reverse_iterator(this); }

   class const_reverse_iterator
   {
      const StringListItem* SLI;
      const_reverse_iterator(const StringListItem* sli) : SLI(sli) {}
   public:
      const_reverse_iterator() : SLI(0) {}
      const_reverse_iterator operator++()
         { SLI = SLI->Previous(); return *this; }
      const_reverse_iterator operator--()
         { SLI = SLI->Next(); return *this; }
      const_reverse_iterator operator++(int)
         { const_reverse_iterator i = *this; SLI = SLI->Previous(); return i; }
      const_reverse_iterator operator--(int)
         { const_reverse_iterator i = *this; SLI = SLI->Next(); return i; }
      const String& operator*() { return SLI->ConstValue(); }
      bool operator==(const const_reverse_iterator& i) const
         { return SLI == i.SLI; }
      bool operator!=(const const_reverse_iterator& i) const
         { return SLI != i.SLI; }
      const String* operator->() { return &(SLI->ConstValue()); }
      friend class StringList;
   };
   const_reverse_iterator rbegin() const
      { return const_reverse_iterator(Previous()); }
   const_reverse_iterator rend() const
      { return const_reverse_iterator(this); }

   iterator find(const String& s);
   reverse_iterator rfind(const String& s);
   iterator find(const String& s, iterator i);
   reverse_iterator rfind(const String& s, reverse_iterator i);

   const_iterator find(const String& s) const;
   const_reverse_iterator rfind(const String& s) const;
   const_iterator find(const String& s, const_iterator i) const;
   const_reverse_iterator rfind(const String& s, const_reverse_iterator i)
      const;

   void erase(iterator i) { delete i.SLI; }
   void erase(reverse_iterator i) { delete i.SLI; }
   void insert_before(const String& s, iterator i) { i.SLI->InsertBefore(s); }
   void insert_after(const String& s, iterator i) { i.SLI->InsertAfter(s); }
};

class TaggedStringList
{
protected:
   StringList& SL;
public:
   TaggedStringList(StringList& sl) : SL(sl) {}
   virtual ~TaggedStringList() {}
   virtual bool Select(const StringListItem& SLI) const { return true; }
   const StringList& get_sl() const { return (const StringList&)SL; }
   StringList& get_sl() { return SL; }
   friend STD_NS ostream& operator<<(STD_NS ostream& os, const TaggedStringList& tsl);
   friend class StringList;
   
   class iterator
   {
      StringListItem* SLI;
      TaggedStringList* TSL;
      iterator(StringListItem* sli, TaggedStringList* tsl)
         : SLI(sli), TSL(tsl) {}
   public:
      iterator() : SLI(0) {}
      iterator operator++();
      iterator operator--();
      iterator operator++(int)
         { iterator i = *this; operator++(); return i; }
      iterator operator--(int)
         { iterator i = *this; operator--(); return i; }
      String& operator*() { return SLI->Value(); }
      bool operator==(const iterator& i) const { return SLI == i.SLI; }
      bool operator!=(const iterator& i) const { return SLI != i.SLI; }
      String* operator->() { return &(SLI->Value()); }
      friend class TaggedStringList;
   };
   iterator begin() { return ++iterator(&SL, this); }
   iterator end() { return iterator(&SL, this); }

   class const_iterator
   {
      const StringListItem* SLI;
      const TaggedStringList* TSL;
      const_iterator(const StringListItem* sli, const TaggedStringList* tsl)
         : SLI(sli), TSL(tsl) {}
   public:
      const_iterator() : SLI(0) {}
      const_iterator operator++();
      const_iterator operator--();
      const_iterator operator++(int)
         { const_iterator i = *this; operator++(); return i; }
      const_iterator operator--(int)
         { const_iterator i = *this; operator--(); return i; }
      const String& operator*() { return SLI->ConstValue(); }
      bool operator==(const const_iterator& i) const { return SLI == i.SLI; }
      bool operator!=(const const_iterator& i) const { return SLI != i.SLI; }
      const String* operator->() { return &(SLI->ConstValue()); }
      friend class TaggedStringList;
   };
   const_iterator begin() const { return ++const_iterator(&SL, this); }
   const_iterator end() const { return const_iterator(&SL, this); }


   class reverse_iterator
   {
      StringListItem* SLI;
      TaggedStringList* TSL;
      reverse_iterator(StringListItem* sli, TaggedStringList* tsl)
         : SLI(sli), TSL(tsl) {}
   public:
      reverse_iterator() : SLI(0) {}
      reverse_iterator operator++();
      reverse_iterator operator--();
      reverse_iterator operator++(int)
         { reverse_iterator i = *this; operator++(); return i; }
      reverse_iterator operator--(int)
         { reverse_iterator i = *this; operator--(); return i; }
      String& operator*() { return SLI->Value(); }
      bool operator==(const reverse_iterator& i) const { return SLI == i.SLI; }
      bool operator!=(const reverse_iterator& i) const { return SLI != i.SLI; }
      String* operator->() { return &(SLI->Value()); }
      friend class TaggedStringList;
   };
   reverse_iterator rbegin() { return ++reverse_iterator(&SL, this); }
   reverse_iterator rend() { return reverse_iterator(&SL, this); }

   class const_reverse_iterator
   {
      const StringListItem* SLI;
      const TaggedStringList* TSL;
      const_reverse_iterator(const StringListItem* sli,
         const TaggedStringList* tsl) : SLI(sli), TSL(tsl) {}
   public:
      const_reverse_iterator() : SLI(0) {}
      const_reverse_iterator operator++();
      const_reverse_iterator operator--();
      const_reverse_iterator operator++(int)
         { const_reverse_iterator i = *this; operator++(); return i; }
      const_reverse_iterator operator--(int)
         { const_reverse_iterator i = *this; operator--(); return i; }
      const String& operator*() { return SLI->ConstValue(); }
      bool operator==(const const_reverse_iterator& i) const
         { return SLI == i.SLI; }
      bool operator!=(const const_reverse_iterator& i) const
         { return SLI != i.SLI; }
      const String* operator->() { return &(SLI->ConstValue()); }
      friend class TaggedStringList;
   };
   const_reverse_iterator rbegin() const
      { return ++const_reverse_iterator(&SL, this); }
   const_reverse_iterator rend() const
      { return const_reverse_iterator(&SL, this); }

   void erase(iterator i) { delete i.SLI; }
   void erase(reverse_iterator i) { delete i.SLI; }
   void insert_before(const String& s, iterator i) { i.SLI->InsertBefore(s); }
   void insert_after(const String& s, iterator i) { i.SLI->InsertAfter(s); }
   int sf(const String& s1, const String& s2, iterator i); // substitute first
   int sl(const String& s1, const String& s2, iterator i); // substitute last
   int sa(const String& s1, const String& s2, iterator i); // substitute all
   int sf(const SubstitutionList&, iterator i); // substitute first
   int sl(const SubstitutionList&, iterator i); // substitute last
   int sa(const SubstitutionList&, iterator i); // substitute all
   int s(const GString& g1, const GString& g2, iterator i);
   void UpperCase(iterator i);
   void LowerCase(iterator i);

   int size();

   int erase();
   int insert_before(const String& s);
   int insert_after(const String& s);
   int sf(const String& s1, const String& s2);     // substitute first
   int sl(const String& s1, const String& s2);     // substitute last
   int sa(const String& s1, const String& s2);     // substitute all
   int sf(const SubstitutionList&);                // substitute first
   int sl(const SubstitutionList&);                // substitute last
   int sa(const SubstitutionList&);                // substitute all
   int s(const GString& g1, const GString& g2);    // gstring substitute
   void UpperCase();
   void LowerCase();

   friend class TaggedStringList::iterator;
   friend class TaggedStringList::reverse_iterator;
   friend class TaggedStringList::const_iterator;
   friend class TaggedStringList::const_reverse_iterator;

};

class StringList_String : public TaggedStringList
{
   String Target;
public:
   StringList_String(StringList& sl, const String& t)
      : TaggedStringList(sl), Target(t) {}
   bool Select(const StringListItem& SLI) const
      { return SLI.ConstValue().find(Target) != String::npos; }
};

class StringList_Range : public TaggedStringList
{
   String Target1, Target2;
   int Ends; // 0 neither boundary, 1 last, 2 first, 3 both
   bool Selected, ChangeNext;
public:
   StringList_Range(StringList& sl, const String& t1, const String& t2,
      int ends) : TaggedStringList(sl), Target1(t1), Target2(t2),
      Ends(ends), Selected(false), ChangeNext(false) {}
   bool Select(const StringListItem& SLI) const;
};



/*
class MaskedStringList : public TaggedStringList
{
   String Mask;
public:
   MaskedStringList(StringList& sl)
      : TaggedStringList(sl), Mask((sl.size()+7)/8, (char)0) {}
   MaskedStringList(const MaskedStringList& tsl)
      : TaggedStringList(tsl.SL), Mask(tsl.Mask) {}
   friend ostream& operator<<(STD_NS ostream& os, MaskedStringList& tsl);
   friend class StringList;
};
*/

// Carry out a one of a series of translations
// case independent not done yet

class SubstitutionList
{
   StringList input;        // what we are searching for
   StringList output;       // what we convert to
   bool first;              // next input will be an input one
   bool ci;                 // true for case independent
public:
   SubstitutionList() : first(true), ci(false) {}
   SubstitutionList& operator<<(const String& S);
   void SetCaseIndependent(bool cix = true) { ci = cix; }
   void CleanUp()
      { input.CleanUp(); output.CleanUp(); first = true; ci = false;}
   StringList& in() { return input; }
   const StringList& in() const { return input; }
   StringList& out() { return output; }
   const StringList& out() const { return output; }
   friend class TaggedStringList;
};

// GString is something we can match a string to

class GString
{
protected:
   GString() {}
   static String ws_chars;       // white space characters
public:
   virtual ~GString() {}
   NotGString operator~();
   PlusGString operator+(const GString& g);
   GTGString operator>(const GString& g);
   LTGString operator<(const GString& g);
   AndGString operator&(const GString& g);
   OrGString operator|(const GString& g);
   XorGString operator^(const GString& g);

   PlusGString operator+(const ExplicitString& es);
   GTGString operator>(const ExplicitString& es);
   LTGString operator<(const ExplicitString& es);
   AndGString operator&(const ExplicitString& es);
   OrGString operator|(const ExplicitString& es);
   XorGString operator^(const ExplicitString& es);
   virtual bool Matches(const String& s, uint offset, uint length) = 0;
   bool Matches(const String& s) { return Matches(s, 0, s.size()); }
   virtual bool Matches_i(const String& s, uint&, uint offset = 0,
      uint length = (uint)(-1)) { return Matches(s, offset, length); }
   virtual int ShortLong() const { return 0; }      // -1 = short, +1 = long
   virtual unsigned int FixedLength() const { return String::npos; }
   virtual void Collect(const String& s, StringList& SL);
   virtual void Translate(String& s, StringList& SL);
   virtual short int ProbeLeft(const String& s, uint offset, uint length,
      uint& fl) { return 0; }
   virtual short int ProbeRight(const String& s, uint offset, uint length,
      uint& fl) { return 0; }
};

// ProbeLeft and ProbeRight -
//    return -1 if a fit is impossible;
//    return 1 if there is a unique fit (return length of string used to fl);
//    return 0 if can't tell or fit is not unique

class ExplicitString : public GString
{
protected:
   String S;
public:
   ExplicitString() {}
   ExplicitString(const String& s) : S(s) {}
   ExplicitString(const char* s) : S(s) {}
   ExplicitString(const ExplicitString& es) : S(es.S) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   unsigned int FixedLength() const { return S.size(); }
   void Translate(String& s, StringList& SL);
   ~ExplicitString() {}
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

class CIString : public ExplicitString
// for case independent match
{
public:
   CIString(const String& s) : ExplicitString(s) { UpperCase(S); }
   CIString(const CIString& cis) : ExplicitString(cis.S) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   ~CIString() {}
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

class PairGString : public GString
{
protected:
   const GString* G1;
   const GString* G2;
   PairGString(const GString* g1, const GString* g2) : G1(g1), G2(g2) {}
   int ShortLong() const;
};

class AndGString : public PairGString
{
public:
   AndGString(const GString* g1, const GString* g2) : PairGString(g1, g2) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   unsigned int FixedLength() const;
   void Collect(const String& s, StringList& SL);
   void Translate(String& s, StringList& SL);
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

class OrGString : public PairGString
{
   int which;      // 1 for first branch, 2 for second
public:
   OrGString(const GString* g1, const GString* g2) : PairGString(g1, g2) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   unsigned int FixedLength() const;
   void Collect(const String& s, StringList& SL);
   void Translate(String& s, StringList& SL);
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

class XorGString : public PairGString
{
   int which;      // 1 for first branch, 2 for second
public:
   XorGString(const GString* g1, const GString* g2) : PairGString(g1, g2) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   unsigned int FixedLength() const;
   void Collect(const String& s, StringList& SL);
   void Translate(String& s, StringList& SL);
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

class PlusGString : public PairGString
{
protected:
   int split;     // where the string was split
public:
   PlusGString(const GString* g1, const GString* g2) : PairGString(g1, g2) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   unsigned int FixedLength() const;
   void Collect(const String& s, StringList& SL);
   void Translate(String& s, StringList& SL);
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

class GTGString : public PlusGString
{
public:
   GTGString(const GString* g1, const GString* g2) : PlusGString(g1, g2) {}
   GTGString2 operator>(const GString& g);
   GTGString2 operator>(const ExplicitString& es);
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   bool Matches_i(const String& s, unsigned int& ix, uint offset = 0,
      uint length = String::npos);
};

// this is for iterated '>' symbols
class GTGString2 : public GTGString
{
public:
   GTGString2(const GTGString* g1, const GString* g2) : GTGString(g1, g2) {}
   GTGString2(const GTGString2* g1, const GString* g2) : GTGString(g1, g2) {}
   GTGString2 operator>(const GString& g);
   GTGString2 operator>(const ExplicitString& es);
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   bool Matches_i(const String& s, unsigned int& ix, uint offset = 0,
      uint length = String::npos);
};

class LTGString : public PlusGString
{
public:
   LTGString(const GString* g1, const GString* g2) : PlusGString(g1, g2) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
};

class NotGString : public GString
{
   const GString* G;
public:
   NotGString(const GString* g) : G(g) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   void Translate(String& s, StringList& SL);
};

class AnyString : public GString
{
protected:
   String S;
public:
   uint size() const { return S.size(); }
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   AnyString() : S("") {}
   AnyString(const AnyString& us) : S(us.S) {}
   String Value() const { return S; }
   void Translate(String& s, StringList& SL);
};


class LongestString : public AnyString
{
public:
   int ShortLong() const { return 1; }
   LongestString() : AnyString() {}
   LongestString(const LongestString& ls) : AnyString(ls) {}
   void operator=(const String& s) { S = s; }
};

class ShortestString : public AnyString
{
public:
   int ShortLong() const { return -1; }
   ShortestString() : AnyString() {}
   ShortestString(const ShortestString& ss) : AnyString(ss) {}
   void operator=(const String& s) { S = s; }
};

class FixedLengthString : public AnyString
{
   unsigned int N;
public:
   FixedLengthString(unsigned int n) : AnyString(), N(n) {}
   FixedLengthString(const FixedLengthString& fs)
      : AnyString(fs), N(fs.N) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   unsigned int FixedLength() const { return N; }
   void operator=(const String& s) { S = s; }
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

// match any string - don't keep copy of string
class Dots : public GString
{
public:
   bool Matches(const String&, uint offset = 0, uint length = String::npos);
};

class LongestDots : public Dots
{
public:
   int ShortLong() const { return 1; }
};

class ShortestDots : public Dots
{
public:
   int ShortLong() const { return -1; }
};

class FixedLengthDots : public Dots
{
   unsigned int N;
public:
   FixedLengthDots(int n) : N(n) {}
   FixedLengthDots(const FixedLengthDots& fld) : N(fld.N) {}
   bool Matches(const String& s, uint offset = 0, uint length = String::npos);
   unsigned int FixedLength() const { return N; }
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};


// match sequence of spaces, tabs, lf, cr - must be at least one
class WhiteSpace : public GString
{
public:
   bool Matches(const String&, uint offset = 0, uint length = String::npos);
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

// match sequence of spaces, tabs, lf, cr
class OptionalWhiteSpace : public WhiteSpace
{
public:
   bool Matches(const String&, uint offset = 0, uint length = String::npos);
   short int ProbeLeft(const String& s, uint offset, uint length, uint& fl);
   short int ProbeRight(const String& s, uint offset, uint length, uint& fl);
};

// put before String or character string to convert to GString
class InitialGString
{
public:
   ExplicitString operator+(const String& s) { return ExplicitString(s); }
   ExplicitString operator>(const String& s) { return ExplicitString(s); }
   ExplicitString operator<(const String& s) { return ExplicitString(s); }
   ExplicitString operator&(const String& s) { return ExplicitString(s); }
   ExplicitString operator|(const String& s) { return ExplicitString(s); }
   ExplicitString operator^(const String& s) { return ExplicitString(s); }
   ExplicitString operator+(const char* s) { return ExplicitString(s); }
   ExplicitString operator>(const char* s) { return ExplicitString(s); }
   ExplicitString operator<(const char* s) { return ExplicitString(s); }
   ExplicitString operator&(const char* s) { return ExplicitString(s); }
   ExplicitString operator|(const char* s) { return ExplicitString(s); }
   ExplicitString operator^(const char* s) { return ExplicitString(s); }
};

// inlines

inline PlusGString GString::operator+(const ExplicitString& es)
   { return operator+((const GString&)es); }
inline GTGString GString::operator>(const ExplicitString& es)
   { return operator>((const GString&)es); }
inline LTGString GString::operator<(const ExplicitString& es)
   { return operator<((const GString&)es); }
inline AndGString GString::operator&(const ExplicitString& es)
   { return operator&((const GString&)es); }
inline OrGString GString::operator|(const ExplicitString& es)
   { return operator|((const GString&)es); }
inline XorGString GString::operator^(const ExplicitString& es)
   { return operator^((const GString&)es); }


inline GTGString2 GTGString::operator>(const ExplicitString& es)
   { return operator>((const GString&)es); }
inline GTGString2 GTGString2::operator>(const ExplicitString& es)
   { return operator>((const GString&)es); }

// functions

CIString CI(const String& s);

CIString CI(const char* s);


// Globals

extern InitialGString GS;
extern Dots DOTS;
extern LongestDots LDOTS;
extern ShortestDots SDOTS;
extern FixedLengthDots DOT;
extern WhiteSpace WS;
extern OptionalWhiteSpace OWS;

// ************************* miscellaneous functions ***********************

int s(String& S, const GString& g1, const GString& g2);

int sf(String& S, const SubstitutionList& sx);
int sl(String& S, const SubstitutionList& sx);
int sa(String& S, const SubstitutionList& sx);


// ********************** more search string list stuff ********************

class StringList_GString : public TaggedStringList
{
   GString* Target;
   // constructor is not accessible because GString tree will vanish at end
   // of expression where it is built
   // so we don't want a stand-alone StringList_GString object
   StringList_GString(StringList& sl, GString& t)
      : TaggedStringList(sl), Target(&t) {}
public:
   bool Select(const StringListItem& SLI) const
      { return Target->Matches(SLI.ConstValue()); }
   friend class StringList;
};

//********************** support for "REPORT" ******************************

// the following class is for counting the number of times a piece of code
// is executed. It is used for locating any code not executed by test
// routines. Use turbo GREP locate all places this code is called and
// check which ones are not accessed.
// Somewhat implementation dependent as it relies on "cout" still being
// present when ExeCounter objects are destructed.

#ifdef DO_REPORT

class ExeCounter
{
   int line;                                    // code line number
   int fileid;                                  // file identifier
   long nexe;                                   // number of executions
   static int nreports;                         // number of reports
public:
   ExeCounter(int,int);
   void operator++() { nexe++; }
   ~ExeCounter();                               // prints out reports
};

#endif


#ifdef use_namespace
}
#endif


#endif


// body file: liststr.cpp
// body file: gstring.cpp





