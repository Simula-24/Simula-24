#include <cstdio>
#include <SDL.h>
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
    initscr();
    resize_term(30,120);
    noecho();
    cbreak();
    curs_set(0);
    WINDOW* mainw = newwin(10, 10, 0,0);

    while (true)
    {
        wborder(mainw, '|', '|', '-', '-', 0, 0, 0, 0);
        wrefresh(mainw);
        refresh();
        
    }

    return 0;

}