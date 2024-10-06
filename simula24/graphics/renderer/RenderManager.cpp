#include "RenderManager.h"

#include <SDL.h>
#include <SDL_image.h>

#include <graphics/tile/TileSheetParser.h>
#include <graphics/tile/TileConfig.h>
#include <core/error/error.h>
#include <cassert>
#include <smcore/map/ObjectMap.h>
#include <objectmanager/ObjectManager.h>
#include <core/log/log.h>

using simula24::RenderManager;
using simula24::TileSheetParser;
using simula24::TileConfig;
using simula24::Status;

RenderManager RenderManager::s_instance;

RenderManager::RenderManager()
    : m_mainWindow(nullptr), m_mainTexture(nullptr), m_mainTileSheet{ }
{
}

Status RenderManager::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        ENGINE_CRITICAL("Failed to initialize SDL: %s", SDL_GetError());
        return ERR_LIB_INIT;
    }

    ENGINE_INFO("SDL Initialized");

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        ENGINE_ERROR("Failed to initializes SDL_Image: %s", IMG_GetError());
        return ERR_LIB_INIT;
    }

    ENGINE_INFO("SDL_image Initialized");

    return OK;
}

Status RenderManager::terminate()
{
    IMG_Quit();
    SDL_Quit();
    return OK;
}

void RenderManager::setWindow(AppWindow* win)
{
    assert(win);
    m_mainWindow = win;
}

void RenderManager::addTileSheet(const stl::string& configLoc)
{
    TileSheetParser tsp;
    if (tsp.loadConfig(configLoc) != OK)
        return;

    m_mainTileSheet = tsp.getNextSheet();
    m_mainTexture = m_mainWindow->getTextureManager().loadFromFile("../data/tileset/cp437/cp437.png");
    m_globTileHeight = m_mainTileSheet->getTileHeight();
    m_globTileWidth = m_mainTileSheet->getTileWidth();
}

void RenderManager::renderFromObjectMap(const ObjectMap& om)
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
            if (om.get(i, j) != -1)
            {
                m_mainWindow->copyTexture(m_mainTexture,
                    &m_mainTileSheet->getTile(
                        OM::getObjectTable().getTileId(
                            om.get(i, j)
                        )
                    ),
                    &g);
            }
        }

    }
}
