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
#include <game/map/ObjectMap.h>
#include <game/object/ObjectTable.h>
#include <game/entity/Civilian.h>

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

    Civilian civ;
    civ.setLocation({ 9,9 });

    ObjectMap om(80, 60);
    ObjectTable ot;
    
    int f = ot.insert("ferrite_wall", 219, false);
    om.set(1, 1, f);
    om.set(2, 1, f);
    om.set(3, 1, f);
    om.set(4, 1, f);
    om.set(4, 2, f);
    om.set(4, 3, f);
    om.set(4, 4, f);
    om.set(3, 4, f);
    om.set(2, 4, f);
    om.set(1, 4, f);
    om.set(1, 3, f);
    om.set(1, 2, f);


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

        for (int i = 0; i < 80; i++)
        {
            for (int j = 0; j < 60; j++)
            {
                SDL_Rect g;
                g.w = 10;
                g.h = 10;
                g.y = i + (10 * i);
                g.x = j + (10 * j);
                if (om.get(i, j) != -1)
                {
                    mainWindow->copyTexture(image, &sheet->getTile(ot.getTileId(om.get(i,j))), &g);
                }
            }

        }
        Point p = civ.getLocation();
        SDL_Rect rec = { .x = p.x + (10 * p.x), .y = p.y + (10 * p.y), .w = 10, .h = 10};
        mainWindow->copyTexture(image, &sheet->getTile(1), &rec);

        mainWindow->present();
    }

    Graphics::get().terminate();

    return 0;

}