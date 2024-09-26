#include <cstdio>
#include <curses.h>
#include <simula24/core/log/log.h>
#include <simula24/core/log/sink/ConsoleSink.h>
#include <simula24/core/error/seh.h>
#include <utility>
int main(int argc, char** argv)
{
    simula24::setSEHHandler();
    simula24::Logger l("hello");
    l.setSink<simula24::ConsoleSink>();
    l.info("hlelo ni");
    l.setLogFilter(simula24::LogLevel::WARNING);
    l.info("hlelo ni");
    l.warning("hlelo ni");
}