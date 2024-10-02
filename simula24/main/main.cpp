#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <core/log/log.h>
#include <core/log/sink/ConsoleSink.h>
#include <core/error/seh.h>
#include <locale.h>

#include <game/tile/TileConfig.h>
#include <game/tile/TileSheetParser.h>

#include <graphics/Graphics.h>
#include <graphics/AppWindowMgr.h>
#include <core/stl/priority_queue.h>
using namespace simula24;

int main(int argc, char** argv)
{
    DebugLoggers::init();
    setSEHHandler();
    ENGINE_INFO("SEH Handler set");
    priority_queue<double> q(10);
    q.push(1.1f, 1);
    q.dump();
    q.push(2.1f, 2);
    q.dump();
    q.push(3.1f, 3);
    q.dump();
    q.push(4.1f, 7);
    q.dump();
    q.push(5.1f, 5);
    q.dump();
    q.push(6.1f, 1);
    q.dump();
    q.push(9.1f, 7);
    q.dump();
    decltype(q)::pq_pair t = q.pop();
    while (t.priority != (U32)-1)
    {
        printf("%lf => %d\n", t.object, t.priority);
        q.dump();
        t = q.pop();
    }
    //Graphics::get().init();
    //AppWindowMgr wmgr;
    //AppWindow* mainWindow = nullptr;
    //if (!wmgr.createWindow('id', "Simula 24", 800, 600))
    //    return -1;

    //mainWindow = wmgr.getAppWindow('id');
    //SDL_Renderer* r = mainWindow->getRenderer();

    //TileSheetParser tsp;
    //if (tsp.loadConfig("../data/tileset/cp437/tileset.inf") != OK)
    //    printf("faile : (\n");

    //auto sheet = tsp.getNextSheet();


    //SDL_Texture* image;
    //SDL_Surface* loadedTexture;
    //loadedTexture = IMG_Load("../data/tileset/cp437/cp437.png");

    //if (!loadedTexture)
    //{
    //    ENGINE_ERROR("Failed to load image: %s", IMG_GetError());
    //    return -1; 
    //}

    //image = SDL_CreateTextureFromSurface(r, loadedTexture);
    //SDL_FreeSurface(loadedTexture);
    //SDL_Event event;
    //bool shouldQuit = false;
    //while (!shouldQuit)
    //{
    //    while (SDL_PollEvent(&event))
    //    {
    //        if (event.type == SDL_QUIT) 
    //        {
    //            shouldQuit = true;
    //            break;
    //        }
    //    }

    //    SDL_RenderClear(r);
    //    for(int i = 0; i < sheet->getNumTiles(); i++)
    //        SDL_RenderCopy(r, image, &sheet->getTile(46), &sheet->getTile(i));

    //    SDL_RenderPresent(r);
    //}

    //Graphics::get().terminate();

    return 0;

}