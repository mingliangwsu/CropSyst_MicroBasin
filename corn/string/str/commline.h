//file commline.h

#ifndef COMMLINE_LIB
#define COMMLINE_LIB


#include "str.h"
#include "str_fns.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif

// class for decoding command line parameters
// if first string begins with - or / assume it is options
// assume all options form a single string

class CommandLine
{
   int the_argc;
   char** the_argv;
   bool options;                // true if first arg begins with - or /
   int n_args;                  // number of arguments
public:
   CommandLine(int an_argc, char** an_argv);
   int argc() { return the_argc; }
   char** argv() { return the_argv; }
   String GetArg(int i);        // get i-th arg (1 = first arg after options)
   String GetOptions();
   int NumberOfArgs() { return n_args; }  // no. of args excl .exe and options
   bool Options() { return options; }
                                // true if there are options
   bool HasOption(const String& s);
                                // true if options has any char in s
   bool HasOptionCI(const String& s);
                                // true if options has any char in s
                                // using a case independent comparison
};

#ifdef use_namespace
}
#endif

#endif


// body file: commline.cpp


