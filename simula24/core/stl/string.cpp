#include <string.h>

#include <simula24/core/stl/string.h>

bool stl::operator==(const char* str1, const stl::string& str2)
{
    return strcmp(str1, str2.c_str()) == 0;
}

bool stl::operator==(const stl::string& str1, const stl::string& str2)
{
    return strcmp(str1.c_str(), str2.c_str()) == 0;
}

bool stl::operator!=(const char* str1, const stl::string& str2)
{
    return strcmp(str1, str2.c_str()) != 0;
}

bool stl::operator>(const char* str1, const stl::string& str2)
{
    return strcmp(str1, str2.c_str()) > 0;
}

bool stl::operator<(const char* str1, const stl::string& str2)
{
    return strcmp(str1, str2.c_str()) < 0;
}

stl::string stl::operator+(const char* str1, const stl::string& str2)
{
    stl::string temp = str2;
    temp += str1;
    return temp;
}

stl::string stl::operator+(const stl::string& str1, const stl::string& str2)
{
    stl::string temp = str1;
    temp += str2;
    return temp;

}

bool stl::is_integer(const stl::string& str)
{
    return stl::is_integer(str.c_str());
}

bool stl::is_integer(const char* str)
{
    const char* rawStr = str;

    while (*rawStr)
    {
        if (!((*rawStr >= 0x30 && *rawStr <= 0x39) || *rawStr == '-'))
            return false;
        rawStr++;
    }

    return true;
}

bool stl::is_float(const stl::string& str)
{
    return is_float(str.c_str());
}

bool stl::is_float(const char* str)
{
    const char* rawStr = str;

    while (*rawStr)
    {
        if (!((*rawStr >= 0x30 && *rawStr <= 0x39) || *rawStr == '-' || *rawStr == '.'))
            return false;
        rawStr++;
    }

    return true;
}
