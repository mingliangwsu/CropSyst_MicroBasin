// file commline.cpp

#define WANT_MATH
#define WANT_STREAM

#include "include.h"
#include "myexcept.h"
#include "str.h"
#include "commline.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif


//************************** Command Line functions **********************

CommandLine::CommandLine(int an_argc, char** an_argv)
   : the_argc(an_argc), the_argv(an_argv)
{
   options = false;
   if (the_argc > 1)
   {
      char c = an_argv[1][0];    // 1st char of 2nd string
      if (c == '-' || c == '/') options = true;
   }
   n_args = options ? the_argc - 2 : the_argc - 1;
}

String CommandLine::GetArg(int i)
{
   if (i <= 0) Throw(Invalid_argument("Invalid argument for GetArg "));
   if (i > n_args)
      Throw(Invalid_argument("Insufficient command line arguments "));
   if (options) i++;
   return String(the_argv[i]);
}

String CommandLine::GetOptions()
{
   if (options) return String(the_argv[1]);
   else return String("");
}

bool CommandLine::HasOption(const String& s)
{
   if (!options || s.size() == 0) return false;
   return (String(the_argv[1]).find_first_of(s) != String::npos);
}

bool CommandLine::HasOptionCI(const String& s)
{
   if (!options || s.size() == 0) return false;
   String us = the_argv[1]; UpperCase(us);
   String op = s; UpperCase(op);
   return (us.find_first_of(op) != String::npos);
}

#ifdef use_namespace
}
#endif

