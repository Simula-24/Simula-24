﻿#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <core/log/log.h>
#include <core/log/sink/ConsoleSink.h>
#include <core/error/seh.h>
#include <locale.h>

#include <game/tile/TileConfig.h>
#include <game/tile/TileSheetParser.h>

#include <graphics/Graphics.h>

using namespace simula24;

int main(int argc, char** argv)
{
    DebugLoggers::init();
    setSEHHandler();
    ENGINE_INFO("SEH Handler set");

    Graphics::get().init();

    SDL_Window* mainWindow = SDL_CreateWindow("Simula 24", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    if (!mainWindow)
    {
        ENGINE_ERROR("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* r = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    TileSheetParser tsp;
    if (tsp.loadConfig("../data/tileset/cp437/tileset.inf") != OK)
        printf("faile : (\n");

    auto sheet = tsp.getNextSheet();


    SDL_Texture* image;
    SDL_Surface* loadedTexture;
    loadedTexture = IMG_Load("../data/tileset/cp437/cp437.png");

    if (!loadedTexture)
    {
        ENGINE_ERROR("Failed to load image: %s", IMG_GetError());
        return -1; 
    }

    image = SDL_CreateTextureFromSurface(r, loadedTexture);
    SDL_FreeSurface(loadedTexture);
    SDL_Event event;
    bool shouldQuit = false;
    while (!shouldQuit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                shouldQuit = true;
                break;
            }
        }

        SDL_RenderClear(r);
        for(int i = 0; i < sheet->getNumTiles(); i++)
            SDL_RenderCopy(r, image, &sheet->getTile(46), &sheet->getTile(i));

        SDL_RenderPresent(r);
    }

    Graphics::get().terminate();

    return 0;

}