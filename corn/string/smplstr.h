#ifndef CORN_SMPLSTR_H
#define CORN_SMPLSTR_H

/*
   This class is intended to provide a string with the most basic functionality
   not based on any other string classes.

   It is intended for storing character arrays with automatic resizing.
   It is not intended for string manipulation.

   This class is provided because I wanted to provided CORN classes that
   do not depend on string classes that are not library sharable between
   C++ builder and BC++.

   It does not use exceptions, templates or anything that would not
   work on any C++ compiler.
*/
namespace CORN {
class Simple_string
{
private:
   char *str;
public:
   Simple_string(const char *i_str);
   Simple_string(const Simple_string &i_to_be_copied);
};

}; // namespace CORN

#endif
