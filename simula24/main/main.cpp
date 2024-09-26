#include <cstdio>
#include <curses.h>

#include <core/log/log.h>
#include <core/log/sink/ConsoleSink.h>
#include <core/error/seh.h>

using namespace simula24;

int main(int argc, char** argv)
{
    DebugLoggers::init();
    
    setSEHHandler();

    ENGINE_INFO("SEH Handler set");
}