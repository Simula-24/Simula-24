#include "ConsoleSink.h"
#include <cstdio>

using simula24::ConsoleSink;

void ConsoleSink::log(const stl::string& str)
{
    fprintf(stderr, str.c_str());
}

void ConsoleSink::flush()
{
    fflush(stderr);
}