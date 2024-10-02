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
#include <graphics/TextureManager.h>
#include <core/stl/priority_queue.h>
using namespace simula24;

int main(int argc, char** argv)
{
    DebugLoggers::init();
    setSEHHandler();
    ENGINE_INFO("SEH Handler set");
    
    Graphics::get().init();
    AppWindowMgr wmgr;
    AppWindow* mainWindow = nullptr;
    if (!wmgr.createWindow('id', "Simula 24", 800, 600))
        return -1;

    mainWindow = wmgr.getAppWindow('id');

    TileSheetParser tsp;
    if (tsp.loadConfig("../data/tileset/cp437/tileset.inf") != OK)
        printf("faile : (\n");

    auto sheet = tsp.getNextSheet();

    SDL_Texture* image = mainWindow->getTextureManager().loadFromFile("../data/tileset/cp437/cp437.png");

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

        mainWindow->clear();
        for(int i = 0; i < sheet->getNumTiles(); i++)
            mainWindow->copyTexture(image, &sheet->getTile(219), &sheet->getTile(i));

        mainWindow->present();
    }

    Graphics::get().terminate();

    return 0;

}