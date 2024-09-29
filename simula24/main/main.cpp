#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <core/log/log.h>
#include <core/log/sink/ConsoleSink.h>
#include <core/error/seh.h>
#include <locale.h>

#include <game/tile/TileSheetParser.h>

using namespace simula24;

int main(int argc, char** argv)
{
    DebugLoggers::init();
    setSEHHandler();
    ENGINE_INFO("SEH Handler set");

    //if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    //{
    //    ENGINE_ERROR("Failed to initialize SDL: %s", SDL_GetError());
    //    return -1;
    //}

    //if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    //{
    //    ENGINE_ERROR("Failed to initializes SDL_Image: %s", IMG_GetError());
    //    return -1;
    //}
    //SDL_Window* mainWindow = SDL_CreateWindow("Simula 24", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_HIDDEN);

    //if (!mainWindow)
    //{
    //    ENGINE_ERROR("Failed to create window: %s", SDL_GetError());
    //    SDL_Quit();
    //    return -1;
    //}

    //SDL_Renderer* r = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    TileSheetParser tsp(nullptr);
    if (tsp.load("../data/tileset/cp437/tileset.inf") != OK)
        printf("faile : (\n");
    
    SDL_Quit();

    return 0;

}