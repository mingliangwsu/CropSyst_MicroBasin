// test character string manipulation library
// Copyright (c) R B Davies 1996


#define WANT_STREAM

#include "include.h"
#include "str.h"

#ifdef use_namespace
using namespace RBD_STRING;              // access RBD_STRING namespace
#endif


int main()
{



   const char* s1; const char* s2; const char* s3; const char* s4;
   cout << "\nBegin test\n";   // Forces cout to allocate memory at beginning
   cout << 3.14159265 << endl; // also required by Borland Builder
   Try { Throw(Exception("Just a dummy\n")); } CatchAll {}
                               // setup exception buffer
   { String str; str.reserve(30000); s1 = str.data(); }
   { String str = "a"; s3 = str.data(); }

   {
      Tracer et("Test");
      String test = "1234567890";

      cout << "-----------------------------------------\n\n";
      et.ReName("Block A");
      cout << "Bad index" << endl;
      Try { char c = test[10]; cout << c << endl; }
      Catch(Exception) { cout << Exception::what() << endl; }
      CatchAndThrow;
      cout << "-----------------------------------------\n\n";
      et.ReName("Block B");
      cout << "Bad pos value" << endl;
      Try { String s = String(test,11,12); cout << s << endl; }
      Catch(Exception) { cout << Exception::what() << endl; }
      CatchAndThrow;
      cout << "-----------------------------------------\n\n";
      et.ReName("Block C");
      cout << "0 in place of char*" << endl;
      Try { char* c = 0; String s = String(c); cout << s << endl; }
      Catch(Exception) { cout << Exception::what() << endl; }
      CatchAndThrow;
      cout << "-----------------------------------------\n\n";
      et.ReName("Block D");
      cout << "string too long" << endl;
      Try { String s(String::npos,'x'); cout << s << endl; }
      Catch(Exception) { cout << Exception::what() << endl; }
      CatchAndThrow;
      cout << "-----------------------------------------\n\n";
      et.ReName("Block E");
      cout << "string too long" << endl;
      Try
      {
         String s(String::npos-2,'x');
         s.append("ab");
         cout << s << endl;
      }
      Catch(Exception) { cout << Exception::what() << endl; }
      CatchAndThrow;
      cout << "-----------------------------------------\n\n";


   }

   { String str; str.reserve(30000); s2 = str.data(); }
   cout << "(The following memory checks are probably not valid with all\n";
   cout << "compilers - see newmat documentation)\n";
   cout << "Checking for lost memory (large block): "
      << (unsigned long)s1 << " " << (unsigned long)s2 << " ";
   if (s1 != s2) cout << " - Newmat doc: 2.8\n"; else cout << " - ok\n";
   { String str = "a"; s4 = str.data(); }
   cout << "Checking for lost memory (small block): "
      << (unsigned long)s3 << " " << (unsigned long)s4 << " ";
   if (s3 != s4) cout << " - Newmat doc: 2.8\n"; else cout << " - ok\n";
#ifdef DO_FREE_CHECK
   FreeCheck::Status();
#endif


   return 0;

}


