

/* language.cpp

   Written by Roger Nelson

		 Biological Systems Engr. Dept.
       Washington State University
       Pullman, WA 99164-6120

       rnelson@mail.wsu.edu

   See header file for additional documentation

*/

#define LANGUAGE_THE_TRANSLATIONS
#include <corn/language.h>
#undef LANGUAGE_THE_TRANSLATIONS

#include <fstream.h>

#include <ctype.h>
//#include <corn/corn.h>

#ifdef USE_UCSCU
struct UCSCU_options_layout *ucscu_options;
#endif

/*
ISO standard language codes ISO639

The list was extracted from an Internet draft,
"Characters and character sets for various languages"
by Harald.Alvestrand@delab.sintef.no.

*/
/*
	 ?? Gaelic
    ?? Rhaetian
    ?? Sami/
    ?? Sorbian

    lowercase letters must be used because thats the standard
*/
#ifdef HARDCODE_PHRASES

/*______*/ int CORN_translator_class::set(char *language_name)
/*______*/ {
/*______*/   int i;
/*______*/   for (i = 0; i < language_num_languages;i++)
/*______*/     if (strcmp(language_codes[i], language_name) == 0)
/*______*/     {
/*______*/        curr_language_number = i;
/*______*/        return(1);
/*______*/     };
/*______*/   return(0);
/*______*/ };

/*______*/ char *CORN_translator_class::translate_to
/*______*/ (phrase_ID phraseID,int language_number)
/*______*/ {
/*______*/    // With this, we now support recursive dialect definitions!

/*______*/    // Case where there is no translation for the language,
/*______*/ 	//	return the first translation (usually english).
/*______*/ 	if (language_translations[phraseID][language_number] == 0)
/*______*/ 		return(language_translations[phraseID][0]);

/*______*/ 	// Case where the translation is the same as a base language
/*______*/ 	//	this case will only occur in languages which are dialects
/*______*/ 	//	The entry in the table is actually the number of the base language.
/*______*/ 	if ((long)(language_translations[phraseID][language_number]) <= language_num_languages)
/*______*/ 		return(translate_to(phraseID,(int)(long)(language_translations[phraseID][language_number])));

/*______*/    // Case where the translation is the character string
/*______*/    return(language_translations[phraseID][language_number]);
/*______*/ }
/*______*/ #else
/*______*/ // This function reads a phrase entry from the phrases file.
/*______*/ // It is used internally and is probably of no use to the programmer.
/*______*/ //
/*______*/ // Returns true is the next phrase was read successfully.

/*______*/ int CORN_translator_class::read_phrase
/*______*/  (ifstream &phrase_file,
/*______*/   CORN_string &phrase,         // Where to put the read phrase.
/*______*/   CORN_string &language_tag,   // The language to read.
/*______*/   CORN_string &base_language_tag,
/*______*/   CORN_string &used_by         // This list of programs using this phrase.
/*______*/  )
/*______*/ {
/*______*/ 	CORN_string phrase_ID_str;
/*______*/ 	CORN_string language_tag_to_read;
/*______*/ 	int read_complete;
/*______*/ 	CORN_string phrase_in;

/*______*/    if (phrase_file.eof())  // If at eof then phrase not read
/*______*/       return(0);

/*______*/    phrase_ID_str.read_line(phrase_file);

/*______*/ 	if ((phrase_ID_str.length() == 0) || (phrase_file.eof()))
/*______*/       return(0);

/*______*/    phrase_file >> used_by; // erase the comment token
/*______*/    used_by.read_line(phrase_file);

/*______*/    read_complete = 0;
/*______*/    phrase.assign("");      // Clear the phrase
/*______*/    do
/*______*/ 	{
/*______*/       language_tag_to_read.assign(language_tag);
/*______*/       CORN_string language_tag_in;
/*______*/       phrase_file >> language_tag_in;

/*______*/      if (language_tag_in == "*/")
/*______*/         read_complete = 1;
/*______*/      else
/*______*/      {   phrase_in.read_line(phrase_file);

/*______*/          if (phrase_in.get_at(0) == '=')
/*______*/             language_tag_to_read.assign(phrase_in.substr(1));
/*980818*/          if ((language_tag_in == language_tag_to_read)  || (language_tag_in == "*"))
/*______*/ 			   phrase.assign(phrase_in);
/*______*/          else
/*980818*/             if (((language_tag_in == base_language_tag)) &&
/*______*/                (phrase.length()))
/*______*/               phrase.assign(phrase_in);
/*______*/ 	  };
/*______*/    } while (!read_complete);
/*______*/ 	return(1);
/*______*/ };

/*______*/ void CORN_translator_class::get_available_languages(ifstream &phrases_file)
/*______*/ {
/*______*/ 	 CORN_string name;
/*______*/ 	 CORN_string desc;

/*______*/ 	 do
/*______*/ 		 phrases_file >> name;
/*______*/ 	 while (name.substr(0,7) != "LINGVO,");
/*______*/ 	 phrases_file >> name; // ignore the program line
/*______*/ 	 phrases_file >> name; // ignore the program line

/*______*/ 	 while (name != "*/")   // comment token
/*______*/ 	 {
/*______*/       desc.read_line(phrases_file);
/*______*/       // not implemented yet languages_available = new language_available(name,desc,languages_available);
/*______*/       phrases_file >> name;
/*______*/ 	 };
/*______*/ };

/*______*/ void CORN_translator_class::load_dialects
/*______*/ (ifstream &phrases_file
/*______*/ ,CORN_string &language_tag
/*______*/ ,CORN_string &base_language_tag)
/*______*/ {
/*______*/    CORN_string lang_name;
/*______*/    CORN_string dialects;
#ifdef __BCPLUSPLUS__
              // Only Borland has case_sensitive compare. It is not critical
/*______*/    dialects.set_case_sensitive(false);
#endif
/*______*/    dialects.read_line(phrases_file); // the Dialects line
/*______*/    if (! dialects.find("DIALEKTOJ"))
/*______*/       return; // The program is not using dialects.
/*______*/    phrases_file >> lang_name;
/*______*/ 	while (lang_name != "*/")
/*______*/    {
/*______*/      dialects.read_line(phrases_file);
/*______*/ 	  if (dialects.find(language_tag) != NPOS)
/*______*/ 		  base_language_tag.assign(lang_name);  // Get the first word in the dialects line
/*______*/      phrases_file >> lang_name;
/*______*/    };
/*______*/ };

/*______*/ #ifdef USE_UCSCU
/*______*/ void CORN_translator_class::load_charactersets
/*______*/ (FILE *phrases_file,char *language_tag)
/*______*/ {
/*______*/    char lang_code[40];
/*______*/    char cs_code [40];
/*______*/    char cs_line[256];
/*______*/    cs_line[0] = 0;
/*______*/    while (strstr(cs_line,"CS") == NULL)
/*______*/       fgets(cs_line,255,phrases_file);

/*______*/    fgets(cs_line,255,phrases_file);
/*______*/ 	while (cs_line[0] != '*')
/*______*/    {
/*______*/      sscanf(cs_line,"%s %s\n",lang_code,cs_code);
/*______*/ 	  if (strcmp(lang_code,language_tag) == NULL)
/*______*/         ucscu_options[UCSCU_INPUT].CS = UCSCU_lookup_CS(cs_code);
/*______*/    };
/*______*/ };

/*______*/ #endif
/*______*/ // This function is usually used internally by language_init(),
/*______*/ // but may be used by the programmer to allow the user to change the
/*______*/ // language on the fly.
/*______*/ //
/*______*/ // load returns true if the translations loaded successfully
/*______*/ // false if the file is not found or corrupt.


/*______*/ bool CORN_translator_class::load
/*______*/ (const char *language_tag
/*______*/ ,const char *program_name
/*______*/ ,const char *phrases_full_filename
/*______*/ ,int num_phrases)
/*______*/ {
/*______*/     Phrase_ID phraseID;
/*______*/     CORN_string phrase;
/*______*/     CORN_string used_by;
/*______*/     CORN_string base_language_tag;
/*______*/     int phrase_count = 0;

/*______*/     if (phrase_table)
/*______*/     {
/*______*/      for (int i = 0; i < num_phrases; i++)
/*______*/        if (phrase_table[i])
/*010308*/           delete [] phrase_table[i];
/*______*/     };
/*______*/     phrase_table = new char *[num_phrases];

/*______*/     for (int i = 0; i < num_phrases; i++)
/*______*/       phrase_table[i] = 0;

/*______*/     current_code.assign(language_tag[0] ? language_tag : "en");

/*______*/     phraseID = 1; //LINGVO;

/*______*/     ifstream phrase_file(phrases_full_filename);
/*______*/     if (!phrase_file.good()) return(0);

/*______*/     get_available_languages(phrase_file);
/*______*/     phrase_file.seekg(0);

/*______*/     load_dialects(phrase_file,language_tag,base_language_tag);

/*______*/ #ifdef USE_UCSCU
/*______*/    language_load_charactersets(phrase_file,language_tag);
/*______*/ #endif

#ifdef __BCPLUSPLUS__
/*______*/    to_upper(program_name);  // Case changing should not be necessary!
#endif
/*______*/ 	for (phraseID = 1 /*LINGVO*/ ; phraseID < num_phrases; phraseID++)
/*______*/ 	{
/*______*/ 	  if (!read_phrase(phrase_file,phrase,
/*______*/ 			 language_tag,base_language_tag,used_by))
/*______*/ 	  {  phrase_file.close();
/*______*/ 		  return(0);   // language read failed.
/*______*/ 	  };
                // Only BORLAND has to_upper, it is not critical.
/*______*/      used_by.to_upper();
/*______*/ 	  if ((used_by.find(program_name) != NPOS) ||
/*______*/          (used_by.find("*") != NPOS))
/*______*/ 	  {
/*______*/         phrase_count += 1;
/*______*/ #       ifdef USE_UCSCU
/*______*/         UCSCU_string(phrase,list->phrase);
/*______*/ #       endif

/*______*/         phrase_table[phraseID] = new char[phrase.length()+1];
/*______*/         strcpy(phrase_table[phraseID],phrase.c_str());
/*______*/ 	  }
/*______*/         else phrase_table[phraseID] = 0;
/*______*/ 	};
/*______*/ 	phrase_file.close();
/*______*/ 	return(1);
/*______*/ };

#ifdef HARDCODE_PHRASES
/*______*/ CORN_translator_class::CORN_translator_class(char *language_name)
/*______*/ current_language_code(0)
/*______*/ { set(language_name); };

#else

/*______*/ CORN_translator_class::CORN_translator_class
/*______*/ (const char *language_tag
/*______*/ ,const char *program_name
/*______*/ ,const char *phrases_full_filename
/*______*/ ,int i_num_phrases
/*______*/ #ifdef USE_UCSCU
/*______*/ ,struct UCSCU_options_layout *i_ucscu_options
/*______*/ #endif
/*______*/ )
/*______*/ :phrase_table(0)
/*______*/ ,num_phrases(i_num_phrases)
/*______*/ {
/*______*/     char actual_language_tag[40];
/*______*/ #  ifdef USE_UCSCU
/*______*/     ucscu_options = i_ucscu_options;
/*______*/ #  endif
/*______*/     strcpy(actual_language_tag,language_tag);
/*______*/ 	   is_good = load( actual_language_tag, program_name,phrases_full_filename, num_phrases);
/*______*/ };

/*______*/ CORN_translator_class::CORN_translator_class
/*______*/ (char **static_phrases_table)
/*______*/ : phrase_table(static_phrases_table)
/*______*/ {
/*______*/     is_good = true;
/*______*/ };

#endif

/*______*/ // Make sure to deallocate the memory used by the phrase table.

/*______*/ CORN_translator_class::~CORN_translator_class()
/*______*/ {
/*______*/   for (int i = 0; i < num_phrases; i++)
/*010308*/       if (phrase_table[i]) delete [] phrase_table[i];
/*010308*/   delete [] phrase_table;
/*______*/ };
/*______*/ #endif

/*______*/ static char L_unable_to_translate_str[] = "???";
/*______*/ static char L_blank_str[] = " ";

/*______*/ // translate() is used in place of literal strings.
/*______*/ //   The programmer should not modify the returned string; if the string
/*______*/ //	must be modified, strcpy the string into a separate buffer.

/*______*/ const char *CORN_translator_class::translate
/*______*/ (Phrase_ID phraseID) const
/*______*/ {
/*______*/ #ifdef HARDCODE_PHRASES
/*______*/    return(translate_to(phraseID,curr_language_number));
/*______*/ #else
/*______*/    return (phrase_table[phraseID])
/*______*/    ? (phrase_table[phraseID][0] == '_')
/*______*/      ? L_blank_str
/*______*/      : phrase_table[phraseID]
/*______*/    : L_unable_to_translate_str;
/*______*/ #endif
/*______*/ };

#ifdef OBSOLETE
//000808 not used anywhere
/*______*/ ostream &CORN_translator_class::translate_to_stream
/*______*/ (ostream &strm, Phrase_ID phraseID) const
/*______*/ {
/*______*/ #ifdef HARDCODE_PHRASES
/*______*/    return(translate_to(phraseID,curr_language_number));
/*______*/ #else

/*______*/    if (phrase_table[phraseID] && (phrase_table[phraseID][0] != '_'))
/*______*/        strm << phrase_table[phraseID];

/*______*/    return strm;
/*______*/ #endif
/*______*/ };
#endif

/*______*/ void list_available_languages
/*______*/ (ostream &dest
/*______*/ ,const char *phrases_filename
/*______*/ )
/*______*/ {
/*______*/ #ifdef HARDCODE_PHRASES
/*______*/    int i;
/*______*/    for (i = 0; i < language_num_languages; i++)
/*______*/      dest << language_codes[i] << language_translations[0][i] << endl;

/*______*/ #else
/*______*/    CORN_string in_line;
/*______*/    ifstream phrase_file(phrases_filename);

/*______*/    if (phrase_file.good())
/*______*/    { do
/*______*/      { in_line.read_line(phrase_file );
/*______*/      } while (!phrase_file.eof() || (in_line.substr(0,6) != "LINGVO"));
/*______*/      do
/*______*/      { in_line.read_line(phrase_file );
/*______*/        if (in_line != "*/")
/*______*/           dest << in_line;
/*______*/      } while (!phrase_file.eof() || (in_line != "*/"));
/*______*/    };
/*______*/ #endif
/*______*/ };

#ifdef __DLL__

/*______*/ // This function is to allow Delphi to use this C++ class

/*______*/ extern "C" CORN_translator_class
/*______*/ stdcall
/*______*/ export
/*______*/ *create_CORN_translator_class
/*______*/ (const char *language_tag
/*______*/ ,const char *use_tag
/*______*/ ,const char *phrases_full_filename
/*______*/ ,int num_phrases
/*______*/ #    ifdef USE_UCSCU
/*______*/ ,struct UCSCU_options_layout *i_ucscu_options = 0
/*______*/ #   endif
/*______*/ )
/*______*/ {
/*______*/     return (CORN_translator_class *)new CORN_translator_class
/*______*/     (language_tag,use_tag,phrases_full_filename,num_phrases
/*______*/ #    ifdef USE_UCSCU
/*______*/     ,i_ucscu_options = 0
/*______*/ #   endif
/*______*/     );
/*______*/ };
#endif


