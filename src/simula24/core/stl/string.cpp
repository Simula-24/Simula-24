#include <string.h>

#include <simula24/core/stl/string.h>

bool simula24::operator==(const char* str1, const simula24::string& str2)
{
    return strcmp(str1, str2.c_str()) == 0;
}

bool simula24::operator==(const simula24::string& str1, const simula24::string& str2)
{
    return strcmp(str1.c_str(), str2.c_str()) == 0;
}

bool simula24::operator!=(const char* str1, const simula24::string& str2)
{
    return strcmp(str1, str2.c_str()) != 0;
}

bool simula24::operator>(const char* str1, const simula24::string& str2)
{
    return strcmp(str1, str2.c_str()) > 0;
}

bool simula24::operator<(const char* str1, const simula24::string& str2)
{
    return strcmp(str1, str2.c_str()) < 0;
}

simula24::string simula24::operator+(const char* str1, const simula24::string& str2)
{
    simula24::string temp = str2;
    temp += str1;
    return temp;
}

simula24::string simula24::operator+(const simula24::string& str1, const simula24::string& str2)
{
    simula24::string temp = str1;
    temp += str2;
    return temp;

}

bool simula24::is_integer(const simula24::string& str)
{
    return simula24::is_integer(str.c_str());
}

bool simula24::is_integer(const char* str)
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

bool simula24::is_float(const simula24::string& str)
{
    return is_float(str.c_str());
}

bool simula24::is_float(const char* str)
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
