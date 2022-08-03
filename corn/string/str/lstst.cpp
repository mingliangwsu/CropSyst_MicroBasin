// test character string manipulation library and string list

#define WANT_STREAM
#define WANT_FSTREAM

#include "include.h"
#include "str.h"
#include "gstring.h"

#ifdef use_namespace
using namespace RBD_STRING;              // access RBD_STRING namespace
#endif


int main()
{

   Try
   {
      Tracer TR("string-list-test");
      
      int c;

      StringList::iterator word;

      // construct a string list and load it with data
      // i.e. one word is one each line
      StringList Fox;
      Fox.push_back("The");
      Fox.push_back("quick");
      Fox.push_back("brown");
      Fox.push_back("fox");
      Fox.push_back("jumps");
      Fox.push_back("over");
      Fox.push_back("the");
      Fox.push_back("lazy");
      Fox.push_back("dog");

      // print it out
      cout << "*** print words and numbers of letters ***" << endl;
      for (word = Fox.begin(); word != Fox.end(); ++word)
         cout << *word << "     " << word->size() << endl;;
      cout << endl;

      // Save a spare copy
      StringList SpareFox = Fox;

      // check out size for tagged lists
      cout << "*** check out size for tagged lists (4 lines) ***" << endl;
      cout << "Number of lines with e   (3) " << Fox("e").size() << endl;
      cout << "Number of lines with z   (1) " << Fox("z").size() << endl;
      cout << "Number of lines with *   (0) " << Fox("*").size() << endl;
      cout << "Number of lines with mps (1) " << Fox("mps").size() << endl;
      cout << endl;

      // edit it
      cout << "*** swap dog and fox ***" << endl;
      StringList::iterator i;
      i = Fox.find("fox");
      if (i == Fox.end()) cout << "Can't find fox" << endl; else *i = "dog";
      i = Fox.find("dog", ++i);
      if (i == Fox.end()) cout << "Can't find dog" << endl; else *i = "fox";
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // edit it
      cout << "*** put quick before fox ***" << endl;
      i = Fox.find("quick");
      if (i == Fox.end()) cout << "Can't find quick" << endl; else Fox.erase(i);
      i = Fox.find("fox");
      if (i == Fox.end()) cout << "Can't find fox" << endl;
      else Fox.insert_before("quick", i);
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // edit it
      cout << "*** put lazy after The ***" << endl;
      i = Fox.find("The");
      if (i == Fox.end()) cout << "Can't find The" << endl;
      else Fox.insert_after("lazy", i);
      i = Fox.find("lazy");
      if (i == Fox.end()) cout << "Can't find lazy" << endl;
      i = Fox.find("lazy",++i);
      if (i == Fox.end()) cout << "Can't find lazy" << endl;
      else Fox.erase(i);
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // search for a word that is not there
      cout << "*** search for a word that is not there ***" << endl;
      i = Fox.find("cat");
      if (i == Fox.end()) cout << "Can't find cat" << endl;
      cout << "*** print out again ***" << endl;
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // recover saved copy
      cout << "*** Recover saved copy ***" << endl;
      Fox = SpareFox;
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // print it out in reverse order
      cout << "*** print in reverse order ***" << endl;
      for (StringList::reverse_iterator rword = Fox.rbegin();
         rword != Fox.rend(); ++rword)
         cout << *rword << " ";
      cout << endl;

      // convert lines containing 'o' to upper case/
      cout << "*** convert words containing 'o' to upper case ***" << endl;
      Fox(DOTS+"o"+DOTS).UpperCase();
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // convert lines containing 'O' to lower case/
      cout << "*** convert words containing 'O' to lower case ***" << endl;
      Fox(DOTS+"O"+DOTS).LowerCase();
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // Upper case "quick brown fox"
      cout << "*** upper case \"quick brown fox\" ***" << endl;
      Fox("qui", "fo", 3).UpperCase();
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // Lower case "quick brown fox"
      cout << "*** lower case \"quick brown fox\" ***" << endl;
      Fox("he", "mp", 0).LowerCase();
      for (word = Fox.begin(); word != Fox.end(); ++word) cout << *word << " ";
      cout << endl;

      // Try rfind
      cout << "*** rfind over ***" << endl;
      StringList::reverse_iterator ri = Fox.rfind("over");
      if (ri == Fox.rend()) cout << "can't rfind over" << endl;
      cout << "*** try again ***" << endl;
      StringList::reverse_iterator ri1 = Fox.rfind("over", ++ri);
      if (ri1 != Fox.rend()) cout << "over rfound incorrectly" << endl;
      cout << "*** try jumps ***" << endl;
      ri1 = Fox.rfind("jumps", ri);
      if (ri1 == Fox.rend()) cout << "can't find jumps" << endl;

      // Try const find and rfind
      cout << "*** const find and rfind ***" << endl;
      const StringList cFox = Fox;
      StringList::const_iterator ci = cFox.find("quick");
      if (ci == cFox.end()) cout << "can't find quick" << endl;
      StringList::const_iterator ci1 = cFox.find("quick", ++ci);
      if (ci1 != cFox.end()) cout << "quick found incorrectly" << endl;
      ci1 = cFox.find("brown", ci);
      if (ci1 == cFox.end()) cout << "can't find brown" << endl;
      StringList::const_reverse_iterator cri = cFox.rfind("fox");
      if (cri == cFox.rend()) cout << "can't find fox" << endl;
      StringList::const_reverse_iterator cri1 = cFox.rfind("fox", ++cri);
      if (cri1 != cFox.rend()) cout << "fox found incorrectly" << endl;
      cri1 = cFox.rfind("brown", cri);
      if (cri1 == cFox.rend()) cout << "can't find brown" << endl;

      // test the GString functions
      cout << "*** GString tests ***" << endl;

      FixedLengthString FLS(5);
      ShortestString SS;
      LongestString LS;
      LongestString LS1;

      cout << (GS + "ABC" + SS).Matches("ABCPQRST") << "  ";
         cout << SS.Value() << endl;
      cout << (LS + "FGH").Matches("12345FGH") << "  ";
         cout << LS.Value() << endl;
      cout << (SS + "ABC" + LS).Matches("XXXABCYYYABCZZZ") << "  ";
         cout  << SS.Value() << "  " << LS.Value() << endl;
      cout << (LS + "ABC" + SS).Matches("XXXABCYYYABCZZZ") << "  ";
         cout  << LS.Value() << "  " << SS.Value() << endl;
      cout << (LS + "ABC" + LS1).Matches("XXXABCYYYABCZZZ") << "  ";
         cout  << LS.Value() << "  " << LS1.Value() << endl;
      SS = ""; LS = "";
      cout << ((SS | LS) + "ABC" + LS1).Matches("XXXABCYYYABCZZZ") << "  ";
         cout  << SS.Value() << " | " << LS.Value() << "  " << LS1.Value()
            << endl;

      cout << (GS ^ "ABC" ^ "FGH").Matches("ABC");
      cout << (GS ^ "ABC" ^ "ABC").Matches("ABC");
      cout << (GS ^ "FGH" ^ "FGH").Matches("ABC");
      cout << (DOTS + "ABC" + DOTS).Matches("XXXABCYYYABCZZZ");
      cout << (DOTS + "FGH" + DOTS).Matches("XXXABCYYYABCZZZ");
      cout <<
         (SDOTS+"ABC" > DOTS+"ABC" > "ZZZ").Matches("XXXABCYYYABCZZZ");
      cout <<
         (LDOTS+"ABC" > DOTS+"ABC" > "ZZZ").Matches("XXXABCYYYABCZZZ");
      cout <<
         (LDOTS+"BCY" > DOTS+"ABC" > "ZZZ").Matches("XXXABCYYYABCZZZ");
      cout <<
         (LDOTS+"BCY" > DOTS+"ABC" > DOTS).Matches("XXXABCYYYABCZZZ");
      cout <<
         (LDOTS+"BCY" > DOTS+"ABC" > "ZZ").Matches("XXXABCYYYABCZZZ");
      cout <<
         (LDOTS+"BCY" > DOTS+"ABC" > "ZZZZ").Matches("XXXABCYYYABCZZZ");
      cout <<
         (DOTS+"bad"+DOTS).Matches("The big BAD wolf");
      cout <<
         (DOTS+CI("bad")+DOTS).Matches("The big BAD wolf");
      cout <<
         (DOTS+CI("good")+DOTS).Matches("The big BAD wolf");
      cout <<
         (WS+"alpha"+DOTS+"gamma"+WS).Matches("alpha beta gamma");
      cout <<
         (OWS+"alpha"+DOTS+"gamma"+OWS).Matches("alpha beta gamma");
      cout <<
         (WS+"alpha"+DOTS+"gamma"+WS).Matches(" alpha beta gamma");
      cout <<
         (WS+"alpha"+DOTS+"gamma"+WS).Matches("alpha beta gamma ");
      cout <<
         (WS+"alpha"+DOTS+"gamma"+WS).Matches(" alpha beta gamma ");
      cout <<
         (WS+"alpha"+DOTS+"gamma"+WS).Matches("  alpha beta gamma  ");
      cout << CI("Mixed").Matches("mixed");
      cout << CI("Mixed").Matches("MIXED");
      cout << CI("Mixed").Matches("MOXED");
      cout << CI(String("Mixed")).Matches("mixed");
      cout << (GS | "this" | "that").Matches("this");
      cout << (GS | "this" | "that").Matches("that");
      cout << (GS | "this" | "that").Matches("thus");
      cout << (GS ^ "this" ^ "that").Matches("this");
      cout << (GS ^ "this" ^ "that").Matches("that");
      cout << (GS ^ "this" ^ "that").Matches("thus");
      cout << (GS ^ "this" ^ "this").Matches("this");
      cout << (GS & "this" & "that").Matches("this");
      cout << (GS & "this" & "this").Matches("this");
      cout << (GS + "this" + "that").Matches("thisthat");
      cout << (GS + "this" + "that").Matches("this that");
      cout << (GS + "this" + "that").Matches("thisthus");
      cout << (GS + "that" + "this").Matches("thathis");
      cout << (GS > "this" > "that").Matches("thisthat");
      cout << (GS > "this" > "that").Matches("this that");
      cout << (GS > "this" > "that").Matches("thisthus");
      cout << (GS > "that" > "this").Matches("thathis");
      cout << (GS < "this" < "that").Matches("thisthat");
      cout << (GS < "this" < "that").Matches("this that");
      cout << (GS < "this" < "that").Matches("thisthus");
      cout << (GS < "that" < "this").Matches("thathis");
      cout << WS.Matches("  ");
      cout << WS.Matches(" \t \n \r ");
      cout << WS.Matches(" \t \\ \n \r ");
      cout << WS.Matches("");
      cout << OWS.Matches(" \t  \n \r ");
      cout << OWS.Matches("");
      cout << (WS + DOTS).Matches(" abc");
      cout << (DOTS + WS).Matches("abc ");
      cout << (WS + DOTS).Matches("abc");
      cout << (DOTS + WS).Matches("abc");
      cout << (OWS + DOTS).Matches("abc");
      cout << (DOTS + OWS).Matches("abc");
      cout << (GS + "First" + (DOTS + "Second")).Matches("First and Second");
      cout << (GS + "First" + (DOTS + "Second")).Matches("First and Sekond");
      cout << (GS + "First" + (DOTS + "Second")).Matches("Furst and Second");
      cout <<
         ((DOTS + "First") + (DOTS + "Second")).Matches(" First and Second");
      cout <<
         ((DOTS + "First") + (DOTS + "Second")).Matches(" First and Sekond");
      cout <<
         ((DOTS + "First") + (DOTS + "Second")).Matches(" Furst and Second");
      cout << (GS > "First" > (DOTS + "Second")).Matches("First and Second");
      cout << (GS > "First" > (DOTS + "Second")).Matches("First and Sekond");
      cout << (GS > "First" > (DOTS + "Second")).Matches("Furst and Second");
     cout <<
         ((DOTS + "First") > (DOTS + "Second")).Matches(" First and Second");
      cout <<
         ((DOTS + "First") > (DOTS + "Second")).Matches(" First and Sekond");
      cout <<
         ((DOTS + "First") > (DOTS + "Second")).Matches(" Furst and Second");
      cout <<
         ((GS+"First"+DOTS) < (GS+"Second"+DOTS)).Matches("First and Second.");
      cout <<
         ((GS+"First"+DOTS) < (GS+"Second"+DOTS)).Matches("First and Sekond.");
      cout <<
         ((GS+"First"+DOTS) < (GS+"Second"+DOTS)).Matches("Furst and Second.");

      cout << endl;

      ifstream is("lstst.dat");
      StringList TheData; is >> TheData;
      is.close();
      cout << "*** all the data ***" << endl;
      cout << TheData;
      cout << "*** just those with 've' ***" << endl;
      cout << TheData("ve");
      cout << "*** just those without 've' ***" << endl;
      cout << TheData(~(DOTS + "ve" + DOTS));
      cout << "*** just those beginning with 'fo' or 's' ***" << endl;
      cout << TheData((GS | "fo" | "s") + ShortestString());
      cout << "*** just those with 'e' ***" << endl;
      cout << TheData(DOTS + "e" + DOTS);
      cout << "*** just those with exactly two 'e's ***" << endl;
      cout << TheData((DOTS + "e" + DOTS + "e" + DOTS)
         & ~(DOTS + "e" + DOTS + "e" + DOTS + "e" + DOTS));
      cout << "*** erase eleven ***" << endl;
      c = TheData("eleven").erase();
      cout << "number of erases = " << c << endl;
      cout << TheData;
      cout << "*** restore it ***" << endl;
      c = TheData("ten").insert_after("eleven");
      cout << "number of inserts = " << c << endl;
      cout << TheData;
      cout << "*** replace all 'e's by 'k' ***" << endl;
      c = TheData.All().sa("e","k");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;
      cout << "*** fix all numbers with three (or more) 'e's ***" << endl;
      c = TheData(DOTS+"k"+DOTS+"k"+DOTS+"k"+DOTS).sa("k","e");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;
      cout << "*** fix the first 'e' ***" << endl;
      c = TheData.All().sf("k","e");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;
      cout << "*** fix the last 'e' ***" << endl;
      c = TheData.All().sl("k","e");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** replace first 'e' by 'k' and second by 'j' ***" << endl;
      c = TheData.All().s(DOTS+"e"+DOTS+"e"+DOTS,
                          DOTS+"k"+DOTS+"j"+DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** restore them ***" << endl;
      c = TheData.All().s(DOTS+(GS ^ "j" ^ "k")+DOTS,
                          DOTS+(GS ^ "e" ^ "e")+DOTS);
      cout << "number of substitutes = " << c << endl;
      c = TheData.All().s(DOTS+(GS ^ "j" ^ "k")+DOTS,
                          DOTS+(GS ^ "e" ^ "e")+DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** repl. 2nd 'e' by 'k' unless there is a double 'e' ***" << endl;
      c = TheData.All().s((DOTS+"e" +DOTS+"e"+DOTS) & ~(   DOTS+"ee"+DOTS),
                          (DOTS+DOTS+DOTS+"k"+DOTS) & ~(GS+ "" + "" + "" ));
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** restore them ***" << endl;
      c = TheData.All().s(DOTS+"k"+DOTS,
                          DOTS+"e"+DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** select 3'e's & not double 'e'; replace by 11 ***" << endl;
      c = TheData.All().s(
         (   DOTS+"e"+DOTS+"e"+DOTS+"e"+DOTS) & ~(   DOTS+"ee"+DOTS),
         (GS+""  +"" +""  +"" +""  +"" +"")   & "11"                );
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** restore it ***" << endl;
      c = TheData("11").sf("11","eleven");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** change single letter between 't' and 'n' to q ***" << endl;
      c = TheData.All().s(DOTS + "t" + DOT + "n" + DOTS,
                          DOTS + DOT + "q" + DOT + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** restore it ***" << endl;
      c = TheData.All().sa("q","e");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** numbers ***" << endl;
      SubstitutionList Numbers;
      Numbers << "one" << "1"
          << "two" << "2"
          << "three" << "3"
          << "four" << "4"
          << "five" << "5";
      c = TheData.All().sa(Numbers);
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** restore ***" << endl;
      Numbers.CleanUp();
      Numbers << "1" << "one"
          << "2" << "two"
          << "3" << "three"
          << "4"<< "four"
          << "5" << "five";
      c = TheData.All().sf(Numbers);
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** cap 1st t or v in lines with one but not both ***" << endl;
      c = TheData.All().s( (SDOTS+"v"+DOTS) ^ (SDOTS+"t"+DOTS),
                            (DOTS+"V"+DOTS) ^ (DOTS+"T"+DOTS) );
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** restore ***" << endl;
      c = TheData.All().s( (SDOTS+"V"+DOTS) | (SDOTS+"T"+DOTS),
                            (DOTS+"v"+DOTS) | (DOTS+"t"+DOTS) );
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** UC ee if first letter f xor second letter i ***" << endl;
      c = TheData.All().s( ((DOT + "i") ^ (GS + "f" + DOT)) + DOTS + "ee" + DOTS,
                           ((DOT + DOT) ^ (     DOT + DOT)) + DOTS + "EE" + DOTS );
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** restore last E ***" << endl;
      c = TheData("EE").sl("E","e");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;

      cout << "*** do it again ***" << endl;
      c = TheData("E").sl("E","e");
      cout << "number of substitutes = " << c << endl;
      cout << TheData;



      cout << "*** The fox ***" << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is.seekg(0); is >> Fox; is.close();
      cout << Fox << endl;
      c = Fox.All().sa("quick", "fast");
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(DOTS + "quick" + DOTS,
                      DOTS + "fast"  + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox("fox").s(DOTS + "quick" > DOTS + ".",
                       DOTS + "fast"  > DOTS + "?");
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(GS + "The" + DOTS          + "fox" + DOTS,
                           DOTS  + " slow grey " + DOTS  + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(DOTS + (GS | "jump" | "jumps") + DOTS,
                      DOTS + (GS | "leap" | "leaps") + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      ShortestString SS1, SS2;
      c = Fox.All().s(
         GS + "The quick brown " + SS1 + " jumps over the lazy " + SS2 + ".",
              DOTS               + SS2 + DOTS                    + SS1 + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         (GS | "The" | "Le") > DOTS +  "fox" > DOTS + "the" > DOTS + "." ,
         (GS | "A"   | "Un") > DOTS +  "cat" > DOTS + "a"   > DOTS + "?" );
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         (GS | "The" | "Le") > DOTS +  "fox" > DOTS + "the" > DOTS ,
         (GS | "A"   | "Un") > DOTS +  "cat" > DOTS + "a"   > DOTS );
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         GS + "The" + DOTS <  GS + "fox" + DOTS < GS + "the" + DOTS < "." ,
         GS + "A"   + DOTS <  GS + "cat" + DOTS < GS + "a"   + DOTS < "?" );
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(DOTS + CI("the") + DOTS, DOTS + "XXX" + DOTS);
      cout << "number of substitutes = " << c << endl;
      c = Fox.All().s(DOTS + CI("the") + DOTS, DOTS + "XXX" + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(DOTS + CI("the") + DOTS, DOTS + DOTS + " ... ");
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         DOTS + "fox"  + WS   + "jumps" + DOTS,
         DOTS + "hawk" + DOTS + "flies" + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         DOTS + "ju"  + WS   + "mps" + DOTS,
         DOTS + "cli" + DOTS + "mbs" + DOTS);       // won't match
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         DOTS + "ju"  + OWS  + "mps" + DOTS,
         DOTS + "cli" + DOTS + "mbs" + DOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
               OWS + DOTS + OWS,
         GS + "\"" + DOTS + "\"");
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
             DOTS + WS   >      DOTS   + WS   >      DOTS  + WS   > LDOTS,
         GS + "A" + DOTS > GS + "slow" + DOTS > GS + "red" + DOTS > LDOTS);
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         LDOTS + "he"  > DOTS + "quick" >  SDOTS,
         LDOTS +  DOTS > DOTS + "slow"  >  SDOTS);   // won't match
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         LDOTS + "he"  + DOTS + "quick" +  SDOTS,
         LDOTS +  DOTS + DOTS + "slow"  +  SDOTS);   // will match
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();
      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         SDOTS < GS + "quick" +  DOTS < GS + "he" + LDOTS,
         SDOTS < GS + "slow"  +  DOTS <      DOTS + LDOTS);   // won't match
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();

      is.open("fox.dat"); is >> Fox; is.close();
      c = Fox.All().s(
         SDOTS + "quick" +  DOTS + "he" + LDOTS,
         SDOTS + "slow"  +  DOTS + DOTS + LDOTS);   // will match
      cout << "number of substitutes = " << c << endl;
      cout << Fox << endl;

      Fox.CleanUp(); is.clear();

      cout << "test s function on a string" << endl;
      String test; int ifound;
      test = "one two three four";
      ifound = s(test, DOTS+"two"+DOTS, DOTS+"TWO"+DOTS);
      cout << ifound << " " << test << endl;
      ifound = s(test, DOTS+"two"+DOTS, DOTS+"THREE"+DOTS);
      cout << ifound << " " << test << endl;
      cout << endl;
      
      cout << "test substitute functions on string with StringList" << endl;
      Numbers.CleanUp();
      Numbers << "1" << "I"
              << "4"<< "IV"
              << "5" << "V"
              << "2" << "II"
              << "3" << "III";
      test = "1 2 3 4 5 6 7 1 2 3 4 5 6 7 1 2 3 4 5 6 7";
      c = sf(test, Numbers);
      cout << "number of substitutes = " << c << endl;
      cout << test << endl;
      test = "1 2 3 4 5 6 7 1 2 3 4 5 6 7 1 2 3 4 5 6 7";
      c = sl(test, Numbers);
      cout << "number of substitutes = " << c << endl;
      cout << test << endl;
      test = "1 2 3 4 5 6 7 1 2 3 4 5 6 7 1 2 3 4 5 6 7";
      c = sa(test, Numbers);
      cout << "number of substitutes = " << c << endl;
      cout << test << endl;
      cout << endl;

   }
      // catch exceptions thrown by my programs
   Catch(Exception) { cout << Exception::what() << endl; }
      // catch exceptions thrown by other people's programs
   CatchAll { cout << "exception caught in main program" << endl; }

   return 0;
}








