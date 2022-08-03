// test character string manipulation library
// Copyright (c) R B Davies 1996


#define WANT_STREAM
#define WANT_FSTREAM

#include "include.h"
#include "str.h"
#include "str_fns.h"

#ifdef use_namespace
using namespace RBD_STRING;              // access RBD_STRING namespace
#endif


String GlobalString1;                      // make sure globals are OK
String GlobalString2 = "Not null";
String GlobalString3 = "";


class Counter
{
   unsigned int i;
   const char* s;
public:
   Counter(const char* S) : i(0), s(S) {}
   ~Counter();
   void operator++() { i++; }
   unsigned int Value() const { return i; }
};

Counter::~Counter() { cout << s << " " << i << "\n"; }

Counter Totals("Number of tests ..............:");
Counter Errors("Number of errors (should be 1):");


void prstr(const String& s, const String& t);

void compare(long i, long j);

void compare_bool(bool i, bool j);

void compare(const void* i, const void* j, bool agree=true);


String thrice(const String& X)
{
   String A;
   A += X; A += '/'; A += X; A += '/'; A += X; A += '.';
   return A;
}

String twice(const String& X)
   { String A = X + "/"; String B = X + "."; return A + B; }

String alphabet1(String*& B)
{
   String A(26, (char)0);
   for (int i = 0; i < 26; i++) A[i] = (char)('A' + i);
   B = new String(A); return A;
}

String alphabet2(String*& B)
{
   String A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   B = new String(A); return A;
}

void none(const String&) {}


// test change of string in function - see if memory is returned
void MemRet(String& TheString)
{
   String NewString = "The new string";
   TheString = NewString;
}

int main()
{

   const char* s1; const char* s2; const char* s3; const char* s4;
   cout << "\nBegin test\n";   // Forces cout to allocate memory at beginning
   cout << 3.14159265 << endl; // also required by Borland Builder
   { String str; str.reserve(30000); s1 = str.data(); }
   { String str = "a"; s3 = str.data(); }

   {
      cout << "testing test program - should report error\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      prstr("just testing - 1", "just testing - 2 [0]");

      cout << "preliminary tests\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      {
         String f = "123456";        prstr(f, "123456 [0]");
         f = "abcdefg";              prstr(f, "abcdefg [0]");
         String g = "hijklmn";       prstr(f + g, "abcdefghijklmn [0]");
         f.reserve(30000);           prstr(f, "abcdefg [0]");
         const char* s = f.c_str();  prstr(s, "abcdefg [0]");
         String h = f;               prstr(h, "abcdefg [0]");
         String j; j = h;            prstr(h, "abcdefg [1]");
         prstr(j, "abcdefg [1]");
         compare_bool(h==j, true);
         f = "abcdef";               prstr("12345" + f, "12345abcdef [0]");
         prstr(f + "12345", "abcdef12345 [0]");
         f = "123"; g = "456"; h = "789";
         String fgh = f + g + h;     prstr(fgh, "123456789 [0]");
         fgh = "abc";                prstr(fgh, "abc [0]");
         prstr(f + g + h, "123456789 [0]");
         prstr(fgh, "abc [0]");
      }

      cout << "test string creation and copying\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";

      String f = "0123456789";    // creates string "0123456789"
      prstr(f, "0123456789 [0]");
      String g = f;
      prstr(g, "0123456789 [1]");
      prstr(f, "0123456789 [1]");
      g = "abc";
      String null1;
      prstr(g, "abc [0]");
      prstr(f, "0123456789 [0]");
      g = f;
      prstr(g, "0123456789 [1]");
      prstr(f, "0123456789 [1]");
      compare(f.size(), 10);
      compare(f.length(), 10);
      compare(f.capacity(), 10);
      compare(f.max_size(), String::npos - 1);
      f.reserve(30);
      prstr(g, "0123456789 [0]");
      prstr(f, "0123456789 [0]");
      compare(f.size(), 10);
      compare(f.length(), 10);
      compare(f.capacity(), 30);
      f.reserve(20);
      compare(f.capacity(), 20);
      f.reserve(5);
      compare(f.capacity(), 10);
      f.reserve(20);
      String h = "pqr";
      const void* fd = f.data(); const void* gd = g.data();
      f += h; g += h;
      compare(f.capacity(), 20);
      compare(fd, f.data(), true);
      compare(gd, g.data(), false);
      prstr(g, "0123456789pqr [0]");
      prstr(f, "0123456789pqr [0]");
      g = "abc";
      h = f;
      prstr(f, "0123456789pqr [0]");
      prstr(h, "0123456789pqr [0]");
      g.swap(f);
      h = f;
      prstr(f, "abc [1]");
      prstr(h, "abc [1]");
      h = g;
      prstr(g, "0123456789pqr [1]");
      swap(f, h);
      prstr(f, "0123456789pqr [1]");
      prstr(h, "abc [0]");
      h += "def";
      swap(h, h);                  prstr(h, "abcdef [0]");
      String a(g, 10);             prstr(a, "pqr [0]");
      String b(g, 0, 10);          prstr(b, "0123456789 [0]");
      String c("abcdefghi");       prstr(c, "abcdefghi [0]");
      String d("abcdefghi", 4);    prstr(d, "abcd [0]");
      String e(5, 'e');            prstr(e, "eeeee [0]");
      e = 'e';                     prstr(e, "e [0]");
      e.reserve(4);                prstr(e, "e [0]");
      f = e;                       prstr(e, "e [0]");
      const char *ed1, *fd1, *ed2, *fd2;
      ed1 = e.data(); fd1 = f.data();
      compare(e.capacity(), 4);
      compare(f.capacity(), 1);
      b = "";                                  // create some space
      e += 'f';  f += 'f';
      ed2 = ed1; fd2 = fd1; ed1 = e.data(); fd1 = f.data();
      compare(ed1, ed2, true); compare(fd1, fd2, false);
      compare(e.capacity(), 4);
      compare(f.capacity(), 2);
      e += "gh";  f += "gh";
      ed2 = ed1; fd2 = fd1; ed1 = e.data(); fd1 = f.data();
      compare(ed1, ed2, true); compare(fd1, fd2, false);
      prstr(e, "efgh [0]"); prstr(f, "efgh [0]");

      a = "abcdefg";  const char *ad1, *ad2, *ad3;
      ad1 = a.data();
      ad2 = a.c_str();  compare(ad1,ad2,false);
      ad3 = a.c_str();  compare(ad2,ad3,true);
      a.reserve(8);
      ad1 = a.data();   compare(ad3,ad1,false);
      ad2 = a.c_str();  compare(ad1,ad2,true);
      ad3 = a.c_str();  compare(ad2,ad3,true);

      a = "abcdefghij";
      a.reserve(1);
      a.erase(3,2);                prstr(a, "abcfghij [0]");
      compare(a.capacity(), 10);
      a.reserve();
      a.erase(3,2);                prstr(a, "abchij [0]");
      compare(a.capacity(), 6);

      cout << "test reserve\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      {
          // giving capacity to a regular string without and with change in
          // length of data array
          String x = "Mary had a little lamb";
          String y = x;
          const char* X = x.data(); const char* Y = y.data();
          x.reserve(22); y.reserve(23);
          compare(X, x.data(), true); compare(Y, y.data(), false);
          prstr(x, "Mary had a little lamb [0]");
          prstr(y, "Mary had a little lamb [0]");
          x = String(x,0,10) + String(x,10);
          y = String(y,0,8) + String(y,8);
          x.reserve(22); y.reserve(23);
          prstr(x, "Mary had a little lamb [0]");
          prstr(y, "Mary had a little lamb [0]");
          compare(x.capacity(), 22); compare(y.capacity(),23);
          x.reserve(); y = x;
          prstr(y, "Mary had a little lamb [1]");
          x.reserve();
          prstr(x, "Mary had a little lamb [0]");
          prstr(y, "Mary had a little lamb [0]");
          y = x;
          x.reserve(100);
          prstr(x, "Mary had a little lamb [0]");
          prstr(y, "Mary had a little lamb [0]");
          X = x.data(); Y = y.data();
          compare(X, x.c_str(), true);   // shouldn't change
          compare(Y, y.c_str(), false);  // should change
          prstr(x, "Mary had a little lamb [0]");
          prstr(y, "Mary had a little lamb [0]");
          x.reserve(100); y.reserve(100);
          prstr(x, "Mary had a little lamb [0]");
          prstr(y, "Mary had a little lamb [0]");
          compare(X, x.c_str(), false);   // does change in current version
          compare(x.capacity(), 100);  compare(y.capacity(), 100);
      }

      cout << "test append\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      e = "ex";                    prstr(e, "ex [0]");
      f = e;                       prstr(e, "ex [1]");
      e.reserve(4000);             prstr(e, "ex [0]");
      e = 'e';                     prstr(e, "e [0]");
      f = e;                       prstr(e, "e [0]");
      e.reserve(4000);             prstr(e, "e [0]");
      ed1 = e.data(); fd1 = f.data();
      a = "0123456789";
      e.append(10,'f');
      f.append(10,'f');
      ed2 = ed1; fd2 = fd1; ed1 = e.data(); fd1 = f.data();
      compare(ed1, ed2, true); compare(fd1, fd2, false);
      e.append("ghi",2);
      f.append("gh");
      ed2 = ed1; fd2 = fd1; ed1 = e.data(); fd1 = f.data();
      compare(ed1, ed2, true); compare(fd1, fd2, false);
      e.append(a,4,2);
      f.append(a,4,2);
      ed2 = ed1; fd2 = fd1; ed1 = e.data(); fd1 = f.data();
      compare(ed1, ed2, true); compare(fd1, fd2, false);
      e.append(a,8,String::npos);
      f.append(a,8,String::npos);
      ed2 = ed1; fd2 = fd1; ed1 = e.data(); fd1 = f.data();
      compare(ed1, ed2, true); compare(fd1, fd2, false);
      prstr(e, "effffffffffgh4589 [0]");
      prstr(f, "effffffffffgh4589 [0]");
      a.resize(12,'f');            prstr(a, "0123456789ff [0]");
      a.resize(6,'f');             prstr(a, "012345 [0]");
      String x;
      compare_bool(x.empty(), true);
      x.append("abc");             prstr(x, "abc [0]");
      x.push_back('d');
      x.push_back('e');
      x.push_back('f');            prstr(x, "abcdef [0]");
      compare_bool(x.empty(), false);

      cout << "test element access\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "0123456789"; b = a;     prstr(a, "0123456789 [1]");
      a[0] = a[8]; a[1] = a[9];    prstr(a, "8923456789 [0]");
                                   prstr(b, "0123456789 [0]");
      const String w = "0123456789"; x = w;
                                   prstr(w, "0123456789 [1]");
      a[0] = w[9]; a[9] = w[0];    prstr(w, "0123456789 [1]");
      prstr(a, "9923456780 [0]");  prstr(x, "0123456789 [1]");
      compare((unsigned int)w[10], 0);
      a = "0123456789"; b = a;     prstr(a, "0123456789 [1]");
      a.at(0) = a.at(8); a.at(1) = a.at(9);
      prstr(a, "8923456789 [0]");  prstr(b, "0123456789 [0]");
      x = w;                       prstr(w, "0123456789 [1]");
      a.at(0) = w.at(9); a.at(9) = w.at(0);
      prstr(w, "0123456789 [1]");
      prstr(a, "9923456780 [0]");  prstr(x, "0123456789 [1]");

      cout << "test assign\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a.assign(w);                 prstr(a, "0123456789 [2]");
      a.assign(w, 5,3);            prstr(a, "567 [0]");
                                   prstr(w, "0123456789 [1]");
      a.assign(w, 4,30);           prstr(a, "456789 [0]");
      a.assign("abcdef", 3);       prstr(a, "abc [0]");
      a.assign("abcdef");          prstr(a, "abcdef [0]");
      a.assign("abcdef", 100);     prstr(a, "abcdef [0]");
      a.assign(5, 'a');            prstr(a, "aaaaa [0]");

      String null2 = "";
      compare(null1.data(), null2.data(), true);
      null2 = "";
      compare(null1.data(), null2.data(), true);
      a = null1;
      compare(null1.data(), a.data(), true);
      a = "abc"; a.erase(); compare(null2.data(), a.data(), true);

      cout << "test substring\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      prstr(w.substr(2,5), "23456 [0]");
      prstr(w.substr(4), "456789 [0]");
      prstr(w.substr(), "0123456789 [0]");

      char buff[20];
      int rlen = w.copy(buff,5,2); prstr(String(buff,rlen), "23456 [0]");
      rlen = w.copy(buff,6); prstr(String(buff,rlen), "012345 [0]");

      cout << "test insert\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      x = "0123456789"; a = "abcdefg";
      x.insert(3, a, 2, 4);        prstr(x, "012cdef3456789 [0]");
      x = "0123456789";
      x.insert(4, a, 2, String::npos); prstr(x, "0123cdefg456789 [0]");
      x = "0123456789";
      x.insert(4, a);              prstr(x, "0123abcdefg456789 [0]");
      x = "0123456789";
      x.insert(4, "abcdefg", 2);   prstr(x, "0123ab456789 [0]");
      x = "0123456789";
      x.insert(4, "abcdefg");      prstr(x, "0123abcdefg456789 [0]");
      x = "0123456789";
      x.insert(4, 5, 'a');         prstr(x, "0123aaaaa456789 [0]");

      cout << "test erase\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      x = "0123456789";
      x.erase(3, 4);              prstr(x, "012789 [0]");
      x = "0123456789";
      x.erase(3, 40);             prstr(x, "012 [0]");
      x = "0123456789";
      x.erase(3);                 prstr(x, "012 [0]");
      x = "0123456789";
      x.erase(0, 4);              prstr(x, "456789 [0]");
      x = "0123456789";
      x.erase();                  prstr(x, " [0]");
      x = "abcdef";
      x.clear();                  prstr(x, " [0]");


      cout << "test replace\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      x = "0123456789";
      x.replace(3, 2, a, 1, 4);    prstr(x, "012bcde56789 [0]");
      x = "0123456789";
      x.replace(3, 2, a, 1, String::npos);  prstr(x, "012bcdefg56789 [0]");
      x = "0123456789";
      x.replace(3, 2, a);          prstr(x, "012abcdefg56789 [0]");
      x = "0123456789";
      x.replace(3, 20, a, 1, 4);   prstr(x, "012bcde [0]");
      x = "0123456789";
      x.replace(3, 20, a, 1, String::npos); prstr(x, "012bcdefg [0]");
      x = "0123456789";
      x.replace(3, 2, a, 0, 2);    prstr(x, "012ab56789 [0]");
      x = "0123456789";
      x.replace(3, 20, a);         prstr(x, "012abcdefg [0]");
      x = "0123456789";
      x.replace(3, 20, "abcdefg"); prstr(x, "012abcdefg [0]");
      x = "0123456789";
      x.replace(3, 2, "ab");       prstr(x, "012ab56789 [0]");
      x = "0123456789";
      x.replace(3, 2, "abcdefg");  prstr(x, "012abcdefg56789 [0]");
      x = "0123456789";
      x.replace(3, 2, 2, 'a');     prstr(x, "012aa56789 [0]");
      x = "0123456789";
      x.replace(5, 10, 10, 'a');   prstr(x, "01234aaaaaaaaaa [0]");
      x = "0123456789";
      x.replace(5, 10, 12, 'a');   prstr(x, "01234aaaaaaaaaaaa [0]");
      x = "0123456789";
      x.replace(5, 10, 8, 'a');    prstr(x, "01234aaaaaaaa [0]");
      {
         x = "0123456789";
         String y = x;             prstr(y, "0123456789 [1]");
         x.replace(5,3,"pqr");     prstr(y, "0123456789 [0]");
                                   prstr(x, "01234pqr89 [0]");
      }

      cout << "test insert with capacity\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      x.reserve(100);
      const char* xd1 = x.data();
      x.assign("0123456789"); a = "abcdefg";
      x.insert(3, a, 2, 4);        prstr(x, "012cdef3456789 [0]");
      x.assign("0123456789");
      x.insert(4, a, 2, String::npos); prstr(x, "0123cdefg456789 [0]");
      x.assign("0123456789");
      x.insert(4, a);              prstr(x, "0123abcdefg456789 [0]");
      x.assign("0123456789");
      x.insert(4, "abcdefg", 2);   prstr(x, "0123ab456789 [0]");
      x.assign("0123456789");
      x.insert(4, "abcdefg");      prstr(x, "0123abcdefg456789 [0]");
      x.assign("0123456789");
      x.insert(4, 5, 'a');         prstr(x, "0123aaaaa456789 [0]");

      cout << "test erase with capacity\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      x.assign("0123456789");
      x.erase(3, 4);              prstr(x, "012789 [0]");
      x.assign("0123456789");
      x.erase(3, 40);             prstr(x, "012 [0]");
      x.assign("0123456789");
      x.erase(3);                 prstr(x, "012 [0]");
      x.assign("0123456789");
      x.erase(0, 4);              prstr(x, "456789 [0]");
      x.assign("0123456789");
      x.erase();                  prstr(x, " [0]");


      cout << "test replace with capacity\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      x.assign("0123456789");
      x.replace(3, 2, a, 1, 4);    prstr(x, "012bcde56789 [0]");
      x.assign("0123456789");
      x.replace(3, 2, a, 1, String::npos);  prstr(x, "012bcdefg56789 [0]");
      x.assign("0123456789");
      x.replace(3, 2, a);          prstr(x, "012abcdefg56789 [0]");
      x.assign("0123456789");
      x.replace(3, 20, a, 1, 4);   prstr(x, "012bcde [0]");
      x.assign("0123456789");
      x.replace(3, 20, a, 1, String::npos); prstr(x, "012bcdefg [0]");
      x.assign("0123456789");
      x.replace(3, 2, a, 0, 2);    prstr(x, "012ab56789 [0]");
      x.assign("0123456789");
      x.replace(3, 20, a);         prstr(x, "012abcdefg [0]");
      x.assign("0123456789");
      x.replace(3, 20, "abcdefg"); prstr(x, "012abcdefg [0]");
      x.assign("0123456789");
      x.replace(3, 2, "ab");       prstr(x, "012ab56789 [0]");
      x.assign("0123456789");
      x.replace(3, 2, "abcdefg");  prstr(x, "012abcdefg56789 [0]");
      x.assign("0123456789");
      x.replace(3, 2, 2, 'a');     prstr(x, "012aa56789 [0]");
      x.assign("0123456789");
      x.replace(5, 10, 10, 'a');   prstr(x, "01234aaaaaaaaaa [0]");
      x.assign("0123456789");
      x.replace(5, 10, 12, 'a');   prstr(x, "01234aaaaaaaaaaaa [0]");
      x.assign("0123456789");
      x.replace(5, 10, 8, 'a');   prstr(x, "01234aaaaaaaa [0]");
      compare(xd1, x.data());
      compare(x.capacity(), 100);

      cout << "test some weirdos\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";

      a.erase(); a.reserve(10); ad1 = a.data();
      a.assign("abcdefg"); compare(ad1, a.data());
      b = a;
      prstr(a, "abcdefg [0]"); compare(a.capacity(), 10);
      a = a; b = a;
      prstr(a, "abcdefg [1]"); compare(a.capacity(), 7);

      a.erase(); a.reserve(10); ad1 = a.data();
      a.assign("abcdefghij"); compare(ad1, a.data());
      b = a;
      prstr(a, "abcdefghij [0]"); compare(a.capacity(), 10);
      a = a; b = a;
      prstr(a, "abcdefghij [1]"); compare(a.capacity(), 10);

      a.erase(); a.reserve(10);
      a.assign("abcdefghijk");
      b = a; a = a;      // check a is not reallocated
      prstr(a, "abcdefghijk [1]");

      a.erase(); a.reserve(20); ad1 = a.data();
      a.assign("abcdefghij");
      a.replace(2,5,a); b = a; prstr(a, "ababcdefghijhij [0]");
      compare(ad1, a.data());

      a.erase(); a.reserve(20); ad1 = a.data();
      a.assign("abcdefghij");
      a.replace(2,5,a,7,3); b = a; prstr(a, "abhijhij [0]");
      compare(ad1, a.data());

      a.erase(); a.reserve(20); ad1 = a.data();
      a.assign("abcdefghij");
      a.insert(2,a); b = a; prstr(a, "ababcdefghijcdefghij [0]");
      compare(ad1, a.data());

      a.erase(); a.reserve(20); ad1 = a.data();
      a.assign("abcdefghij");
      a.insert(2,a,7,3); b = a; prstr(a, "abhijcdefghij [0]");
      compare(ad1, a.data());

      a.erase(); a.reserve(20);
      a = "abcdefghij"; compare(a.capacity(), 10);
      a.replace(2,5,a); b = a; prstr(a, "ababcdefghijhij [1]");

      a.erase(); a.reserve(20);
      a = "abcdefghij"; compare(a.capacity(), 10);
      a.replace(2,5,a,7,3); b = a; prstr(a, "abhijhij [1]");

      a.erase(); a.reserve(20);
      a = "abcdefghij";
      a.insert(2,a); b = a; prstr(a, "ababcdefghijcdefghij [1]");

      a.erase(); a.reserve(20);
      a = "abcdefghij";
      a.insert(2,a,7,3); b = a; prstr(a, "abhijcdefghij [1]");

      {
         String A = "0123456789";
         A.reserve(1);             // will set capacity to A.size() = 10
         const char* d = A.data();
         A.erase(1,9);
         String B = A; prstr(A, "0 [0]"); prstr(B, "0 [0]");
	       compare(d,A.data(),true);
      }
      {
         String A = "0123456789";
         const char* d = A.data();
         compare(d,A.data(),true);
         A.erase(1,9);
         String B = A; prstr(A, "0 [1]"); prstr(B, "0 [1]");
      }
      {
         String A = "0123456789";
         const char* d = A.data();
         A.reserve(1);             // will set capacity to A.size() = 10
         compare(d,A.data(),true);
         A.erase(1,9);
         String B = A; prstr(A, "0 [0]"); prstr(B, "0 [0]");
         compare(d,A.data(),true);
      }
      {
         String A = "01234"; A += "56789";
         A.reserve(1);             // will set capacity to A.size() = 10
         prstr(A, "0123456789 [0]");
         A.erase(1,9); prstr(A, "0 [0]");
      }
      {
         String A = "0123456789"; String B = A;
         prstr(A, "0123456789 [1]");
         prstr(B, "0123456789 [1]");
         A.reserve(1);             // will set capacity to A.size() = 10
         prstr(A, "0123456789 [0]");
         prstr(B, "0123456789 [0]");
         A.erase(1,9);
         B = A; prstr(A, "0 [0]"); prstr(B, "0 [0]");
      }
      {
         String A = "0123456789"; const char* c = A.c_str();
         compare(c,A.data(),true);
         A.reserve(1);             // will set capacity to A.size() = 10
         compare(c,A.data(),false);
         prstr(A, "0123456789 [0]");
         A.erase(1,9);
         prstr(A, "0 [0]");
      }
      {
         // check transfer from function and avoidance of copy
         String A; String* B;
         A = alphabet1(B);             // string initiated as CharRepeated
         prstr(A,  "ABCDEFGHIJKLMNOPQRSTUVWXYZ [1]");
         prstr(*B, "ABCDEFGHIJKLMNOPQRSTUVWXYZ [1]");
         delete B; B = 0;
         prstr(A,  "ABCDEFGHIJKLMNOPQRSTUVWXYZ [0]");
         A = alphabet2(B);             // string initiated as character string
         prstr(A,  "ABCDEFGHIJKLMNOPQRSTUVWXYZ [1]");
         prstr(*B, "ABCDEFGHIJKLMNOPQRSTUVWXYZ [1]");
         delete B; B = 0;
         prstr(A,  "ABCDEFGHIJKLMNOPQRSTUVWXYZ [0]");
      }

      cout << "test comparisons\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "012345a";  b = "012345b";
      compare_bool((a == b), false);
      compare_bool((a != b), true);
      compare_bool((a > b), false);
      compare_bool((a < b), true);
      compare_bool((a >= b), false);
      compare_bool((a <= b), true);
      compare_bool((b == a), false);
      compare_bool((b != a), true);
      compare_bool((b < a), false);
      compare_bool((b > a), true);
      compare_bool((b <= a), false);
      compare_bool((b >= a), true);

      a = "012345";  b = "012345b";
      compare_bool((a == b), false);
      compare_bool((a != b), true);
      compare_bool((a > b), false);
      compare_bool((a < b), true);
      compare_bool((a >= b), false);
      compare_bool((a <= b), true);
      compare_bool((b == a), false);
      compare_bool((b != a), true);
      compare_bool((b < a), false);
      compare_bool((b > a), true);
      compare_bool((b <= a), false);
      compare_bool((b >= a), true);

      a = "012345";  b = "012345";
      compare_bool((a == b), true);
      compare_bool((a != b), false);
      compare_bool((a > b), false);
      compare_bool((a < b), false);
      compare_bool((a >= b), true);
      compare_bool((a <= b), true);
      compare_bool((b == a), true);
      compare_bool((b != a), false);
      compare_bool((b < a), false);
      compare_bool((b > a), false);
      compare_bool((b <= a), true);
      compare_bool((b >= a), true);


      a = "012345a";  b = "012345b";
      compare_bool(("012345a" == b), false);
      compare_bool(("012345a" != b), true);
      compare_bool(("012345a" > b), false);
      compare_bool(("012345a" < b), true);
      compare_bool(("012345a" >= b), false);
      compare_bool(("012345a" <= b), true);
      compare_bool((b == "012345a"), false);
      compare_bool((b != "012345a"), true);
      compare_bool((b < "012345a"), false);
      compare_bool((b > "012345a"), true);
      compare_bool((b <= "012345a"), false);
      compare_bool((b >= "012345a"), true);

      a = "012345";  b = "012345b";
      compare_bool(("012345" == b), false);
      compare_bool(("012345" != b), true);
      compare_bool(("012345" > b), false);
      compare_bool(("012345" < b), true);
      compare_bool(("012345" >= b), false);
      compare_bool(("012345" <= b), true);
      compare_bool((b == "012345"), false);
      compare_bool((b != "012345"), true);
      compare_bool((b < "012345"), false);
      compare_bool((b > "012345"), true);
      compare_bool((b <= "012345"), false);
      compare_bool((b >= "012345"), true);

      a = "012345";  b = "012345";
      compare_bool(("012345" == b), true);
      compare_bool(("012345" != b), false);
      compare_bool(("012345" > b), false);
      compare_bool(("012345" < b), false);
      compare_bool(("012345" >= b), true);
      compare_bool(("012345" <= b), true);
      compare_bool((b == "012345"), true);
      compare_bool((b != "012345"), false);
      compare_bool((b < "012345"), false);
      compare_bool((b > "012345"), false);
      compare_bool((b <= "012345"), true);
      compare_bool((b >= "012345"), true);


      a = "012345a";  b = "012345b";
      compare_bool((a == "012345b"), false);
      compare_bool((a != "012345b"), true);
      compare_bool((a > "012345b"), false);
      compare_bool((a < "012345b"), true);
      compare_bool((a >= "012345b"), false);
      compare_bool((a <= "012345b"), true);
      compare_bool(("012345b" == a), false);
      compare_bool(("012345b" != a), true);
      compare_bool(("012345b" < a), false);
      compare_bool(("012345b" > a), true);
      compare_bool(("012345b" <= a), false);
      compare_bool(("012345b" >= a), true);

      a = "012345";  b = "012345b";
      compare_bool((a == "012345b"), false);
      compare_bool((a != "012345b"), true);
      compare_bool((a > "012345b"), false);
      compare_bool((a < "012345b"), true);
      compare_bool((a >= "012345b"), false);
      compare_bool((a <= "012345b"), true);
      compare_bool(("012345b" == a), false);
      compare_bool(("012345b" != a), true);
      compare_bool(("012345b" < a), false);
      compare_bool(("012345b" > a), true);
      compare_bool(("012345b" <= a), false);
      compare_bool(("012345b" >= a), true);

      a = "012345";  b = "012345";
      compare_bool((a == "012345"), true);
      compare_bool((a != "012345"), false);
      compare_bool((a > "012345"), false);
      compare_bool((a < "012345"), false);
      compare_bool((a >= "012345"), true);
      compare_bool((a <= "012345"), true);
      compare_bool(("012345" == a), true);
      compare_bool(("012345" != a), false);
      compare_bool(("012345" < a), false);
      compare_bool(("012345" > a), false);
      compare_bool(("012345" <= a), true);
      compare_bool(("012345" >= a), true);

      cout << "test compare\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "012345aa";  b = "012345bb"; x = "x012345aa";
      compare(a.compare(b), -1);
      compare(b.compare(a), 1);
      compare(x.compare(1, String::npos, a), 0);
      compare(x.compare(1, String::npos, b), -1);
      compare(x.compare(1,7,a), -1);
      compare(x.compare(1,7,b), -1);
      compare(x.compare(1,6,a), -1);
      compare(x.compare(1,6,b), -1);
      compare(x.compare(2,5,a,1,4), 1);
      compare(x.compare(2,5,a,1,5), 0);
      compare(x.compare(2,5,a,1,6), -1);
      a = "012345aa";  b = "012345"; x = "x012345aa";
      compare(a.compare(b), 1);
      compare(a.compare(0,6,b), 0);
      compare(a.compare(0,7,b), 1);
      compare(b.compare(a), -1);
      compare(x.compare(1,String::npos,b), 1);
      compare(x.compare(1,7,b), 1);
      compare(x.compare(1,6,b), 0);


      a = "012345aa";  b = "012345bb"; x = "x012345aa";
      compare(a.compare("012345bb"), -1);
      compare(b.compare("012345aa"), 1);
      compare(x.compare(1, String::npos, "012345aa"), 0);
      compare(x.compare(1, String::npos, "012345bb"), -1);
      compare(x.compare(1,7,"012345aa"), -1);
      compare(x.compare(1,7,"012345bb"), -1);
      compare(x.compare(1,6,"012345aa"), -1);
      compare(x.compare(1,6,"012345bb"), -1);
      compare(x.compare(1,6,"012345678",5), 1);
      compare(x.compare(1,6,"012345678",6), 0);
      compare(x.compare(1,6,"012345678",7), -1);
      a = "012345aa";  b = "012345"; x = "x012345aa";
      compare(a.compare("012345"), 1);
      compare(a.compare(0,6,"012345"), 0);
      compare(a.compare(0,7,"012345"), 1);
      compare(b.compare("012345aa"), -1);
      compare(x.compare(1, String::npos, "012345"), 1);
      compare(x.compare(1,7,"012345"), 1);
      compare(x.compare(1,6,"012345"), 0);

      cout << "test add\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "a0123a"; b = "b456b"; c = "c78c";
      prstr(a + b + c, "a0123ab456bc78c [0]");
      x = a + b + c; prstr(x, "a0123ab456bc78c [0]");
      prstr("a0123a" + b + c, "a0123ab456bc78c [0]");
      x = "a0123a" + b + c; prstr(x, "a0123ab456bc78c [0]");
      prstr(a + "b456b" + c, "a0123ab456bc78c [0]");
      x = a + "b456b" + c; prstr(x, "a0123ab456bc78c [0]");
      prstr(a + b + "c78c", "a0123ab456bc78c [0]");
      x = a + b + "c78c"; prstr(x, "a0123ab456bc78c [0]");
      prstr(a + 'b' + c, "a0123abc78c [0]");
      x = a + 'b' + c; prstr(x, "a0123abc78c [0]");
      prstr('a' + b + c, "ab456bc78c [0]");
      x = 'a' + b + c; prstr(x, "ab456bc78c [0]");
      prstr(a + b + 'c', "a0123ab456bc [0]");
      x = a + b + 'c'; prstr(x, "a0123ab456bc [0]");

      a = "a0123a"; b = "b456b"; c = "c78c";
      prstr(a + (b + c), "a0123ab456bc78c [0]");
      x = a + (b + c); prstr(x, "a0123ab456bc78c [0]");
      prstr("a0123a" + (b + c), "a0123ab456bc78c [0]");
      x = "a0123a" + (b + c); prstr(x, "a0123ab456bc78c [0]");
      prstr(a + ("b456b" + c), "a0123ab456bc78c [0]");
      x = a + ("b456b" + c); prstr(x, "a0123ab456bc78c [0]");
      prstr(a + (b + "c78c"), "a0123ab456bc78c [0]");
      x = a + (b + "c78c"); prstr(x, "a0123ab456bc78c [0]");
      prstr(a + ('b' + c), "a0123abc78c [0]");
      x = a + ('b' + c); prstr(x, "a0123abc78c [0]");
      prstr('a' + (b + c), "ab456bc78c [0]");
      x = 'a' + (b + c); prstr(x, "ab456bc78c [0]");
      prstr(a + (b + 'c'), "a0123ab456bc [0]");
      x = a + (b + 'c'); prstr(x, "a0123ab456bc [0]");

      a = "The"; b = "quick"; c = "brown"; d = "fox";
      prstr(a+' '+b+' '+c+' '+d, "The quick brown fox [0]");

      cout << "test find\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "The quick brown fox jumps over the lazy dog.";
      compare(a.find(String("quick")),    4);
      compare(a.find(String("quick"),3),  4);
      compare(a.find(String("quick"),4),  4);
      compare(a.find(String("quick"),5),  String::npos);
      compare(a.find(String("quick"),6),  String::npos);
      compare(a.find(String("quack")),    String::npos);
      compare(a.find(String("q")),        4);
      compare(a.find(String("q"),4),      4);
      compare(a.find(String("q"),5),      String::npos);
      compare(a.find(String("q"),6),      String::npos);
      compare(a.find(String("1")),        String::npos);
      compare(a.find(String("")),         0);
      compare(a.find(String(""),10),      10);
      compare(a.find(String("quick")),    4);
      compare(a.find("quick"),            4);
      compare(a.find("quick",3),          4);
      compare(a.find("quick",4),          4);
      compare(a.find("quick",5),          String::npos);
      compare(a.find("quick",6),          String::npos);
      compare(a.find("quack"),            String::npos);
      compare(a.find("q"),                4);
      compare(a.find("q",4),              4);
      compare(a.find("q",5),              String::npos);
      compare(a.find("q",6),              String::npos);
      compare(a.find("1"),                String::npos);
      compare(a.find(""),                 0);
      compare(a.find("",10),              10);
      compare(a.find("",44),              44);
      compare(a.find("",45),              String::npos);
      compare(a.find("quick"),            4);
      compare(a.find('q'),                4);
      compare(a.find('q',4),              4);
      compare(a.find('q',5),              String::npos);
      compare(a.find('q',6),              String::npos);
      compare(a.find('1'),                String::npos);
      a = "She sells sea shells by the sea shore";
      compare(a.find(String("shells")),   14);
      compare(a.find(String("shore")),    32);
      compare(a.find(String("es")),       String::npos);
      compare(a.find("shells"),           14);
      compare(a.find("shore"),            32);
      compare(a.find("es"),               String::npos);


      cout << "test single character find functions\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "The quick brown fox jumps over the lazy dog.";
      compare(a.find('.'),                43);
      compare(a.rfind('.'),               43);
      compare(a.find_first_of('.'),       43);
      compare(a.find_last_of('.'),        43);
      compare(a.find('T'),                0);
      compare(a.rfind('T'),               0);
      compare(a.find_first_of('T'),       0);
      compare(a.find_last_of('T'),        0);
      compare(a.rfind('j'),               20);
      compare(a.rfind('j',19),            String::npos);
      compare(a.rfind('j',20),            20);
      compare(a.rfind('j',21),            20);
      compare(a.find_last_of('j'),        20);
      compare(a.find_last_of('j',19),     String::npos);
      compare(a.find_last_of('j',20),     20);
      compare(a.find_last_of('j',21),     20);
      compare(a.find_first_of('j'),       20);
      compare(a.find_first_of('j',19),    20);
      compare(a.find_first_of('j',20),    20);
      compare(a.find_first_of('j',21),    String::npos);
      a = "xaaaaaaaaaaaa";
      compare(a.find_first_not_of('a'),   0);
      compare(a.find_last_not_of('a'),    0);
      a = "aaaaaaaaaaaax";
      compare(a.find_first_not_of('a'),   12);
      compare(a.find_last_not_of('a'),    12);
      a = "aaaaxaaaaaaaa";
      compare(a.find_first_not_of('a'),   4);
      compare(a.find_last_not_of('a'),    4);
      compare(a.find_first_not_of('a',3), 4);
      compare(a.find_last_not_of('a',3),  String::npos);
      compare(a.find_first_not_of('a',4), 4);
      compare(a.find_last_not_of('a',4),  4);
      compare(a.find_first_not_of('a',5), String::npos);
      compare(a.find_last_not_of('a',5),  4);
      a = "aaaaaaaaaaaaa";
      compare(a.find_first_not_of('a'),   String::npos);
      compare(a.find_last_not_of('a'),    String::npos);

      cout << "test rfind\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "The quick brown fox jumps over the lazy dog.";
      compare(a.rfind(String("quick")),    4);
      compare(a.rfind(String("quick"),3),  String::npos);
      compare(a.rfind(String("quick"),4),  4);
      compare(a.rfind(String("quick"),5),  4);
      compare(a.rfind(String("quick"),6),  4);
      compare(a.rfind(String("quack")),    String::npos);
      compare(a.rfind(String("q")),        4);
      compare(a.rfind(String("q"),4),      4);
      compare(a.rfind(String("q"),3),      String::npos);
      compare(a.rfind(String("1")),        String::npos);
      compare(a.rfind(String("")),         44);
      compare(a.rfind(String(""),10),      10);
      compare(a.rfind(String(""),100),     44);
      compare(a.rfind(String("quick")),    4);
      compare(a.rfind("quick"),            4);
      compare(a.rfind("quick",3),          String::npos);
      compare(a.rfind("quick",4),          4);
      compare(a.rfind("quick",5),          4);
      compare(a.rfind("quack"),            String::npos);
      compare(a.rfind("q"),                4);
      compare(a.rfind("q",4),              4);
      compare(a.rfind("q",3),              String::npos);
      compare(a.rfind("1"),                String::npos);
      compare(a.rfind(""),                 44);
      compare(a.rfind("",10),              10);
      compare(a.rfind("quick"),            4);
      compare(a.rfind("."),                43);
      compare(a.rfind("T"),                0);
      a = "She sells sea shells by the sea shore";
      compare(a.rfind(String("shells")),   14);
      compare(a.rfind(String("shore")),    32);
      compare(a.rfind(String("es")),       String::npos);
      compare(a.rfind("shells"),           14);
      compare(a.rfind("shells",14),        14);
      compare(a.rfind("shells",13),        String::npos);
      compare(a.rfind("shore"),            32);
      compare(a.rfind("es"),               String::npos);
      compare(a.rfind("She",0),            0);
      compare(a.rfind("She",1),            0);

      cout << "test find_first_of\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "The quick brown fox jumps over the lazy dog.";
      compare(a.find_first_of(String("over")),          2);
      compare(a.find_first_of(String("over"),2),        2);
      compare(a.find_first_of(String("over"),3),        11);
      compare(a.find_first_of(String("over"),12),       12);
      compare(a.find_first_of(String("The")),           0);
      compare(a.find_first_of(String("The"),1),         1);
      compare(a.find_first_of(String("1.2")),           43);
      compare(a.find_first_of(String("1.2"),43),        43);
      compare(a.find_first_of(String("1.2"),44),        String::npos);
      compare(a.find_first_of(String("")),              String::npos);
      compare(a.find_first_of(String("q")),             4);
      compare(a.find_first_of("over"),          2);
      compare(a.find_first_of("over",2),        2);
      compare(a.find_first_of("over",3),        11);
      compare(a.find_first_of("over",12),       12);
      compare(a.find_first_of("The"),           0);
      compare(a.find_first_of("The",1),         1);
      compare(a.find_first_of("1.2"),           43);
      compare(a.find_first_of("1.2",43),        43);
      compare(a.find_first_of("1.2",44),        String::npos);
      compare(a.find_first_of(""),              String::npos);
      compare(a.find_first_of("q"),             4);

      cout << "test find_last_of\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "The quick brown fox jumps over the lazy dog.";
      compare(a.find_last_of(String("over")),          41);
      compare(a.find_last_of(String("over"),41),       41);
      compare(a.find_last_of(String("over"),40),       33);
      compare(a.find_last_of(String("over"),32),       29);
      compare(a.find_last_of(String("The")),           33);
      compare(a.find_last_of(String("The"),1),         1);
      compare(a.find_last_of(String("The"),0),         0);
      compare(a.find_last_of(String("1.2")),           43);
      compare(a.find_last_of(String("1.2"),43),        43);
      compare(a.find_last_of(String("1.2"),42),        String::npos);
      compare(a.find_last_of(String("")),              String::npos);
      compare(a.find_last_of(String("q")),             4);
      compare(a.find_last_of("over"),          41);
      compare(a.find_last_of("over",41),       41);
      compare(a.find_last_of("over",40),       33);
      compare(a.find_last_of("over",32),       29);
      compare(a.find_last_of("The"),           33);
      compare(a.find_last_of("The",1),         1);
      compare(a.find_last_of("The",0),         0);
      compare(a.find_last_of("1.2"),           43);
      compare(a.find_last_of("1.2",43),        43);
      compare(a.find_last_of("1.2",42),        String::npos);
      compare(a.find_last_of(""),              String::npos);
      compare(a.find_last_of("q"),             4);

      cout << "test find_first_not_of\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "She sells sea shells by the sea shore";
      compare(a.find_first_not_of(String("Shells ")),        12);
      compare(a.find_first_not_of(String("Shells "),12),     12);
      compare(a.find_first_not_of(String("Shells "),13),     21);
      compare(a.find_first_not_of(String("shell ")),          0);
      compare(a.find_first_not_of(String("shell "),1),       12);
      compare(a.find_first_not_of(String("short "),31),      36);
      compare(a.find_first_not_of(String("short "),30),      30);
      compare(a.find_first_not_of(String("shore hat"),23),   String::npos);
      compare(a.find_first_not_of(String(""),23),            23);
      compare(a.find_first_not_of(String("")),               0);
      compare(a.find_first_not_of(String(""),50),            String::npos);
      compare(a.find_first_not_of("Shells "),        12);
      compare(a.find_first_not_of("Shells ",12),     12);
      compare(a.find_first_not_of("Shells ",13),     21);
      compare(a.find_first_not_of("shell "),          0);
      compare(a.find_first_not_of("shell ",1),       12);
      compare(a.find_first_not_of("short ",31),      36);
      compare(a.find_first_not_of("short ",30),      30);
      compare(a.find_first_not_of("shore hat",23),   String::npos);
      compare(a.find_first_not_of("",23),            23);
      compare(a.find_first_not_of(""),               0);
      compare(a.find_first_not_of("",50),            String::npos);

      cout << "test find_last_not_of\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "She sells sea shells by the sea shore";
      compare(a.find_last_not_of(String("Shells ")),        35);
      compare(a.find_last_not_of(String("Shells "),11),     String::npos);
      compare(a.find_last_not_of(String("Shells "),12),     12);
      compare(a.find_last_not_of(String("shell "),12),      12);
      compare(a.find_last_not_of(String("shell "),11),      0);
      compare(a.find_last_not_of(String("short ")),         36);
      compare(a.find_last_not_of(String("short "),30),      30);
      compare(a.find_last_not_of(String("shore hat")),      22);
      compare(a.find_last_not_of(String(""),23),            23);
      compare(a.find_last_not_of(String("")),               36);
      compare(a.find_last_not_of(String(""),50),            36);
      compare(a.find_last_not_of("Shells "),        35);
      compare(a.find_last_not_of("Shells ",11),     String::npos);
      compare(a.find_last_not_of("Shells ",12),     12);
      compare(a.find_last_not_of("shell ",12),      12);
      compare(a.find_last_not_of("shell ",11),      0);
      compare(a.find_last_not_of("short "),         36);
      compare(a.find_last_not_of("short ",30),      30);
      compare(a.find_last_not_of("shore hat"),      22);
      compare(a.find_last_not_of("",23),            23);
      compare(a.find_last_not_of(""),               36);
      compare(a.find_last_not_of("",50),            36);

      cout << "test finds with zero length string\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      a = "";
      compare(a.find(""),                      0);
      compare(a.rfind(""),                     0);
      compare(a.find_first_of(""),             String::npos);
      compare(a.find_last_of(""),              String::npos);
      compare(a.find_first_not_of(""),         String::npos);
      compare(a.find_last_not_of(""),          String::npos);
      compare(a.find('1'),                     String::npos);
      compare(a.rfind('1'),                    String::npos);
      compare(a.find_first_of('1'),            String::npos);
      compare(a.find_last_of('1'),             String::npos);
      compare(a.find_first_not_of('1'),        String::npos);
      compare(a.find_last_not_of('1'),         String::npos);
      compare(a.find("1"),                     String::npos);
      compare(a.rfind("1"),                    String::npos);
      compare(a.find_first_of("1"),            String::npos);
      compare(a.find_last_of("1"),             String::npos);
      compare(a.find_first_not_of("1"),        String::npos);
      compare(a.find_last_not_of("1"),         String::npos);
      compare(a.find("",1),                      String::npos);
      compare(a.rfind("",1),                     0);
      compare(a.find_first_of("",1),             String::npos);
      compare(a.find_last_of("",1),              String::npos);
      compare(a.find_first_not_of("",1),         String::npos);
      compare(a.find_last_not_of("",1),          String::npos);
      compare(a.find('1',1),                     String::npos);
      compare(a.rfind('1',1),                    String::npos);
      compare(a.find_first_of('1',1),            String::npos);
      compare(a.find_last_of('1',1),             String::npos);
      compare(a.find_first_not_of('1',1),        String::npos);
      compare(a.find_last_not_of('1',1),         String::npos);
      compare(a.find("1",1),                     String::npos);
      compare(a.rfind("1",1),                    String::npos);
      compare(a.find_first_of("1",1),            String::npos);
      compare(a.find_last_of("1",1),             String::npos);
      compare(a.find_first_not_of("1",1),        String::npos);
      compare(a.find_last_not_of("1",1),         String::npos);

      cout << "test multiple reference to sum\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      prstr(thrice("123"), "123/123/123. [0]");
      a = "1"; b = "2"; c = "3";
      prstr(thrice(a + b + c), "123/123/123. [0]");
      prstr(twice(a + b + c), "123/123. [0]");
      a = "abc"; b = "def"; c = "ghi";
      prstr(twice(a + b), "abcdef/abcdef. [0]");
      none(a + b + c);

      cout << "test substitution in function\n";
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      String TheString = "This is an old string which will be replaced";
      MemRet(TheString);
      prstr(TheString, "The new string [0]");

      cout << "test input" << endl;
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      {
         ifstream fin("strtst.dat");
         fin >> a >> b >> c >> d;
         prstr(a, "Twinkle, [0]");
         prstr(b, "twinkle, [0]");
         prstr(c, "little [0]");
         prstr(d, "star, [0]");
         fin >> a >> b >> c >> d >> e >> f;
         prstr(a, "How [0]");
         prstr(b, "I [0]");
         prstr(c, "wonder [0]");
         prstr(d, "what [0]");
         prstr(e, "you [0]");
         prstr(f, "are. [0]");
         getline(fin, a);  // to start newline
         getline(fin, a);  prstr(a, "The quick brown fox [0]");
         getline(fin, a);  prstr(a, "jumps over the lazy dog. [0]");
         getline(fin, a);  prstr(a, "---------- [0]");
      }

      cout << "test string functions" << endl;
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      {
         a = "1234567890AaBbCcZz  ,./<>?;'{}[]\\~`!@#$%^&*()_-+=";
         b = "1234567890AABBCCZZ  ,./<>?;'{}[]\\~`!@#$%^&*()_-+=";
         c = "1234567890aabbcczz  ,./<>?;'{}[]\\~`!@#$%^&*()_-+=";
         d = a; UpperCase(d); prstr(d, b + " [0]");
         d = a; LowerCase(d); prstr(d, c + " [0]");
         a = ToString(1234); prstr(a, "1234 [0]");
         a = ToString(-1234); prstr(a, "-1234 [0]");
         a = ToString(0); prstr(a, "0 [0]");
         a = ToString(999999); prstr(a, "999999 [0]");
         a = ToString(-999999); prstr(a, "-999999 [0]");
         a = ToString(1234.98); prstr(a, "1234.9800 [0]");
         a = ToString(-1234.05); prstr(a, "-1234.0500 [0]");
         a = ToString(0.0); prstr(a, "0.0000 [0]");
         a = ToString(999999.9999); prstr(a, "999999.9999 [0]");
         a = ToString(-999999.9999); prstr(a, "-999999.9999 [0]");
         a = ToString(999999.999951); prstr(a, "1000000.0000 [0]");
         a = ToString(-999999.999951); prstr(a, "-1000000.0000 [0]");
      }
      
      cout << "test substitute functions" << endl;
      cout << "   ... doing test " << (Totals.Value() + 1 ) << "\n";
      {
         int n;
         a = "The quick brown fox jumps over the lazy dog";
         n = sf(a, "e", "E");
         prstr(a, "ThE quick brown fox jumps over the lazy dog [0]");
         compare(n, 1); 
         n = sf(a, "1", "2");
         prstr(a, "ThE quick brown fox jumps over the lazy dog [0]");
         compare(n, 0); 
         n = sl(a, "e", "E");
         prstr(a, "ThE quick brown fox jumps over thE lazy dog [0]");
         compare(n, 1); 
         n = sl(a, "2", "3");
         prstr(a, "ThE quick brown fox jumps over thE lazy dog [0]");
         compare(n, 0); 
         n = sa(a, "o", "O");
         prstr(a, "ThE quick brOwn fOx jumps Over thE lazy dOg [0]");
         compare(n, 4); 
         n = sa(a, "o", "O");
         prstr(a, "ThE quick brOwn fOx jumps Over thE lazy dOg [0]");
         compare(n, 0); 
         a = "The quick brown fox jumps over the lazy dog";
         n = sl(a, "T", "t");
         prstr(a, "the quick brown fox jumps over the lazy dog [0]");
         compare(n, 1); 
         n = sf(a, "g", "G");
         prstr(a, "the quick brown fox jumps over the lazy doG [0]");
         compare(n, 1); 
         n = sf(a, "t", "T");
         prstr(a, "The quick brown fox jumps over the lazy doG [0]");
         compare(n, 1); 
         n = sl(a, "G", "g");
         prstr(a, "The quick brown fox jumps over the lazy dog [0]");
         compare(n, 1);
         n = sl(a, "lazy", "quick");
         prstr(a, "The quick brown fox jumps over the quick dog [0]");
         compare(n, 1);
         n = sf(a, "quick", "lazy");
         prstr(a, "The lazy brown fox jumps over the quick dog [0]");
         compare(n, 1);
         n = sa(a, "brown", "red");
         prstr(a, "The lazy red fox jumps over the quick dog [0]");
         compare(n, 1);
          
      }
    

      cout << "test printing - the following 2 lines should be identical\n";
      a = "The "; b = "quick "; c = "brown "; d = "fox\n";
      cout << a << b << c << d;  cout << "The quick brown fox\n";

      cout << "printing npos" << endl;
      cout << String::npos << endl;
   }

   { String str; str.reserve(30000); s2 = str.data(); }
   cout << "(The following memory checks are probably not valid with all\n";
   cout << "compilers - see newmat documentation)\n";
   cout << "Checking for lost memory (large block): "
      << (unsigned long)s1 << " " << (unsigned long)s2 << " ";
   if (s1 != s2) cout << " - see Newmat doc: 2.8\n"; else cout << " - ok\n";
   { String str = "a"; s4 = str.data(); }
   cout << "Checking for lost memory (small block): "
      << (unsigned long)s3 << " " << (unsigned long)s4 << " ";
   if (s3 != s4) cout << " - see Newmat doc: 2.8\n"; else cout << " - ok\n";
#ifdef DO_FREE_CHECK
   FreeCheck::Status();
#endif
   return 0;
}


// the compare functions

void prstr(const String& s, const String& t)
{
   String u;
   ++Totals;
   int sr = s.refcount();
   switch (sr)
   {
   case 0: u = "[0]"; break;
   case 1: u = "[1]"; break;
   case 2: u = "[2]"; break;
   case 3: u = "[3]"; break;


   default: u = "[x]"; break;
   }
   if (t != s + ' ' + u)
   {
      ++Errors;
      String s1 = s;          // printing will disengage s1 from s
      cout << "Error at test " << Totals.Value() << ":\n";
      cout << "prstr: " << s1 << " [" << sr << "]: should be "
         << t << "\n";
   }
}

void compare(long i, long j)
{
   ++Totals;
   if (i!=j)
   {
      ++Errors;
      cout << "Error at test " << Totals.Value() << ":\n";
      cout << "found " << i << " should be " << j << "\n";
   }
}

void compare_bool(bool i, bool j)
{
   ++Totals;
   if (i!=j)
   {
      ++Errors;
      cout << "Error at test " << Totals.Value() << ":\n";
      cout << "found " << i << " should be " << j << "\n";
   }
}

void compare(const void* i, const void* j, bool agree)
{
   ++Totals;
   if ((i==j) != agree)
   {
      cout << "Error at test " << Totals.Value() << ":\n";
      ++Errors;
      if (agree)
	 cout << "found " << (unsigned long)i
            << " should be " << (unsigned long)j << "\n";
      else
         cout << "found " << (unsigned long)i
            << " shouldn't be " << (unsigned long)j << "\n";
   }
}


