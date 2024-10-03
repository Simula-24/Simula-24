#include "Application.h"

#include <graphics/Graphics.h>
#include <core/log/log.h>
#include <cassert>
#include <game/tile/TileSheetParser.h>
#include <SDL.h>

using simula24::Application;
using simula24::Status;

Application::Application()
    : m_wm{}, m_mainWindow(nullptr), m_objectMap(80, 60)
{

}

Application::~Application()
{

}

Status Application::init()
{
    Status stat = OK;
    
    if ((stat = Graphics::get().init()) != OK)
    {
        ENGINE_CRITICAL("Failed to initialize graphic subsystem");
        return stat;
    }
    
    if (!m_wm.createWindow('main', "Simula 24", 800, 600))
    {
        ENGINE_CRITICAL("Failed to create new window");
        return ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE;
    }

    m_mainWindow = m_wm.getAppWindow('main');

    assert(m_mainWindow);

    TileSheetParser tsp;
    if (tsp.loadConfig("../data/tileset/cp437/tileset.inf") != OK)
        return FAILED;
    m_mainTileSheet = tsp.getNextSheet();

    m_mainTexture = m_mainWindow->getTextureManager().loadFromFile("../data/tileset/cp437/cp437.png");


    int f = m_objectTable.insert("ferrite_wall", 219, false);
    m_objectMap.set(1, 1, f);
    m_objectMap.set(2, 1, f);
    m_objectMap.set(3, 1, f);
    m_objectMap.set(4, 1, f);
    m_objectMap.set(4, 2, f);
    m_objectMap.set(4, 3, f);
    m_objectMap.set(4, 4, f);
    m_objectMap.set(3, 4, f);
    m_objectMap.set(2, 4, f);
    m_objectMap.set(1, 4, f);
    m_objectMap.set(1, 3, f);
    m_objectMap.set(1, 2, f);
    m_shouldRun = true;

    return OK;
}

void Application::run()
{
    SDL_Event event;
    while (m_shouldRun)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_shouldRun = false;
                break;
            }
        }

        update();
    }
}

void Application::update()
{
    for (int i = 0; i < 80; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            SDL_Rect g;
            g.w = 10;
            g.h = 10;
            g.y = i + (10 * i);
            g.x = j + (10 * j);
            if (m_objectMap.get(i, j) != -1)
            {
                m_mainWindow->copyTexture(m_mainTexture, &m_mainTileSheet->getTile(m_objectTable.getTileId(m_objectMap.get(i, j))), &g);
            }
        }

    }
    m_mainWindow->present();
}

