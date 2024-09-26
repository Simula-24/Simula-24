#include <cstdio>
#include <SDL.h>
#include <curses.h>


#include <core/log/log.h>
#include <core/log/sink/ConsoleSink.h>
#include <core/error/seh.h>
#include <locale.h>

using namespace simula24;

int main(int argc, char** argv)
{
    DebugLoggers::init();
    
    setSEHHandler();
    setlocale(LC_ALL, "");
    ENGINE_INFO("SEH Handler set");
    initscr();
    resize_term(30,120);
    
    PDC_set_title("Simula24");
    noecho();
    cbreak();
    curs_set(0);
    WINDOW* mainw = newwin(10, 10, 0,0);

    SDL_Event event;
    bool shouldrun = true;
    while (shouldrun)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                shouldrun = false;
        }

        wborder(mainw,
            0x2502, 0x2502, 
            0x2500, 0x2500, 
            0x250C, 0x2510, 
            0x2514, 0x2518  
        );
        wrefresh(mainw);
        mvaddch(20, 20, L'♘');
        
        refresh();
        
    }

    return 0;

}