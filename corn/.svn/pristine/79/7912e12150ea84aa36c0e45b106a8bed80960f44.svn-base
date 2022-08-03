
// ******************convert integer or double to string*********************

#ifndef STR_FNS_LIB
#define STR_FNS_LIB


#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif


String ToString(int i);

String ToString(long i);

String ToString(double f, int ndec = 4);

void UpperCase(String& S);

void LowerCase(String& S);

bool IsInt(const String& S);

bool IsFloat(const String& S);



inline bool Contains(const String& S, const String& str)
   { return S.find(str) != String::npos; }

inline bool Contains(const String& S, const char* s)
   { return S.find(s) != String::npos; }

inline bool Contains(const String& S, char c)
   { return S.find(c) != String::npos; }

inline bool ContainsAnyOf(const String& S, const String& str)
   { return S.find_first_of(str) != String::npos; }

inline bool ContainsAnyOf(const String& S, const char* s)
   { return S.find_first_of(s) != String::npos; }

inline bool ContainsAnyOf(const String& S, char c)
   { return S.find_first_of(c) != String::npos; }

inline bool ContainsOnly(const String& S, const String& str)
   { return S.find_first_not_of(str) == String::npos; }

inline bool ContainsOnly(const String& S, const char* s)
   { return S.find_first_not_of(s) == String::npos; }

inline bool ContainsOnly(const String& S, char c)
   { return S.find_first_not_of(c) == String::npos; }

int sf(String& S, const String& s1, const String& s2);

int sl(String& S, const String& s1, const String& s2);

int sa(String& S, const String& s1, const String& s2);


#ifdef use_namespace
}
#endif


#endif

// body file: str_fns.cpp



