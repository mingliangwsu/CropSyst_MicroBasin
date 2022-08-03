#ifndef CORN_LANGUAGE_H
#define CORN_LANGUAGE_H

#ifdef USE_CORN_TRANSLATOR_CLASS
#	ifndef __cplusplus
#		error This library requires C++. For the C version try my lang.*
#	endif
#	include <corn/no_ns.h>
#	define Phrase_ID int

/* To hard code phrases in the executable:

    #define HARDCODE_PHRASES

   in your program before the #include this header file.

   You should use HARDCODE_PHRASES when your application consists of
   a single executable file in which the phrases will be used,
   or if you are using UNIX.
   If your application consists of several separate programs which
   share many of the same phrases, you should use the load phrases option.

   To perform automatice character set conversion:

   #define USE_UCSCU

   This requires my UCSCU library
   Note the minor change to langauge_init where you specify the character set
   conversion options.

*/

/* language.hpp

   This C++ module will help provide translation of text strings
	to different human languages.  UNIX, AMIGADOS, and Borland C++,

   Written by Roger Nelson

		 Biological Systems Engr. Dept.
       Washington State University
       Pullman, WA 99164-6120

       Comments, suggestions, questions and bug reports can be sent to:
       rnelson@mail.wsu.edu

       Phone: (509)335-1100  or 335-1578 (main office)
       Home:  (509)332-8387
       FAX  : (509)335-2722

   An similar module for the programming language Pascal is also available.

   -------
	2.00 Jan. 1994
   Thanks to:

     Andreas Scherer
     Dipl.-Math., Stud. O.R. an der RWTH Aachen
     Roland-Straﬂe 16
     52070 Aachen, Deutschland (Germany)
     <scherer@genesis.informatik.rwth-aachen.de>
     For several corrections for ANSI C++ and Amiga SAS/C++


	Future plans

   1. When loading the phrases file, I would like to allow the programmer
      to specify the name of the phrases file, so that an application
      could use several phrases files.  This may make the phrases files
      easier to maintain and remove the need for the program list for
      each phrase.

   3.00 Aug 6

      Phrases list can now be either a phrases file or a null terminated
      array of static text.


*/

#include <corn/std/std_fstream.h>
#	include <corn/cstrngem.h>
#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#	ifdef USE_UCSCU
#  	 include <ucscu/ucscu.h>
#	endif

#	ifndef char_8bit
#  	ifdef __BCPLUSPLUS__
#    		define char_8bit  char
#  	else
#    		define char_8bit unsigned char
#  	endif
#	endif

/*______*/  class CORN_translator_class
/*______*/  {
/*______*/  private:
/*______*/
/*______*/      char **phrase_table;
/*______*/      // We use a table of character string instead of
/*______*/      // string class because we don't need the string
/*______*/      // object overhead.
/*______*/      // eventually we will add multiple languages
/*______*/  public:
/*______*/     // not ready yet: language_available *languages_available;  /* List of available languages*/
/*______*/
/*______*/     CORN_string current_code;       // active language
/*______*/     int num_languages_loaded;  // Count of the number of languages loaded
/*______*/                                // for translations
/*______*/     int *languages_loaded;     // The languages currently loaded
/*______*/
/*______*/  #ifdef HARDCODE_PHRASES
/*______*/     int curr_language_number = 0;
/*______*/
/*______*/
/*______*/     int set(char *language_tag);
/*______*/     // When using the HARDCODE_PHRASES option the function sets the language
/*______*/     // to translate to and can be called anytime as often as needed to
/*______*/     //
/*______*/     // set() sets the current language to translate to.
/*______*/     // It is used in HARDCODE_PHRASES mode in lieu of the constructor
/*______*/     // and load().
/*______*/     // set() may be called as many times as desired any where in the
/*______*/     // program, You will want to use it at the beginning of the program.
/*______*/     // If no language is set, the first language in the LINGVO entry is
/*______*/     // used.  Therefore, if you want the default language to be English,
/*______*/     // English should be the first entry in the LINGVO entry.
/*______*/
/*______*/     translator_class(char *language_tag);
/*______*/
/*______*/     char *translate_to(Phrase_ID phraseID,int language_number) const;
/*______*/     // Hard coded phrases has the option of offering translation to
/*______*/     //   any language at any time.
/*______*/
/*______*/  #else
/*______*/      CORN_translator_class
/*______*/      (const char *language_tag
/*______*/      ,const char *use_tag
/*______*/      ,const char *phrases_full_filename
/*______*/      ,int num_phrases
/*______*/  #    ifdef USE_UCSCU
/*______*/      ,struct UCSCU_options_layout *i_ucscu_options = 0
/*______*/  #   endif
/*______*/      );
/*______*/      // This constructor is used with phrases file mode.
/*______*/
/*000806*/      CORN_translator_class
/*______*/      (
/*______*/        char **static_phrases_table
/*______*/      );
/*______*/     // This constructor is used with static phrases table mode.
/*______*/     // static_phrases_table is null terminated I.e.
/*______*/     // char *my_phrases[] = {"phrase1","phrase2",0};
/*______*/
/*______*/      ~CORN_translator_class();
/*______*/
/*______*/     bool load
/*______*/     (const char *language_tag
/*______*/     ,const char *use_tag
/*______*/     ,const char *phrases_full_filename
/*______*/     ,int num_phrases);
/*______*/     // load is usually used internally by the constructor,
/*______*/  	//    but may be used by the programmer to allow the user to change
/*______*/     //    the language on the fly.
/*______*/     //
/*______*/     //    load returns 1 if the translations loaded successfully
/*______*/     //    0 if the file is not found or corrupt.
/*______*/
/*______*/     inline bool good() const { return is_good; };
/*______*/
/*______*/  #endif
/*______*/
/*______*/     // translate() is used in place of literal strings.
/*______*/     //   The programmer should not modify the returned string; if the string
/*______*/     //   must be modified, strcpy the string into a seperate buffer.
/*______*/
/*______*/     const char *translate(Phrase_ID phraseID) const;
/*______*/
/*______*/  private:
/*______*/     bool is_good;
/*______*/     int num_phrases;
/*______*/  
/*______*/     int read_phrase
/*______*/     (ifstream &phrase_file
/*______*/     ,CORN_string &phrase              // Where to put the read phrase.
/*______*/     ,CORN_string &language_tag        // The language to read.
/*______*/     ,CORN_string &base_language_tag
/*______*/     ,CORN_string &used_by              // This list of programs using this phrase
/*______*/     );
/*______*/
/*______*/     void get_available_languages(ifstream &phrases_file);
/*______*/  
/*______*/     void load_dialects
/*______*/     (ifstream &phrases_file
/*______*/     ,CORN_string &language_tag
/*______*/     ,CORN_string &base_language_tag);
/*______*/  
/*______*/  };
/*______*/
#	endif
#endif
//language
