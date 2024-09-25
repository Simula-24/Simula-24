#ifndef SIMULA24_CORE_STL_STRING_H_
#define SIMULA24_CORE_STL_STRING_H_

#include <simula24/core/stl/basic_string.h>

namespace simula24
{

using string = basic_string<char>;

bool operator==(const char* str1, const string& str2);
bool operator==(const string& str1, const string& str2);

bool operator!=(const char* str1, const string& str2);
bool operator>(const char* str1, const string& str2);
bool operator<(const char* str1, const string& str2);

/// append str1 to str2
string operator+(const char* str1, const string& str2);
string operator+(const string& str1, const string& str2);



bool is_integer(const simula24::string& str);
bool is_integer(const char* str);
bool is_float(const simula24::string& str);
bool is_float(const char* str);

}

#endif // SIMULA24_CORE_STL_STRING_H_