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

#include <smcore/entity/CrewMember.h>

using simula24::RenderManager;
using simula24::TileSheetParser;
using simula24::TileConfig;
using simula24::Status;
using simula24::CrewMember;

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


    auto ret = tsp.getNextSheet();
    if (!ret.has_value())
        assert(false);
    m_mainTileSheet = std::move(ret.value());
    m_mainTexture = m_mainWindow->getTextureManager().loadFromFile("../data/tileset/cp437/test.png");
    m_globTileHeight = m_mainTileSheet.getTileHeight();
    m_globTileWidth = m_mainTileSheet.getTileWidth();
}

void RenderManager::renderFromObjectMap(const ObjectMap& om)
{
    for (int i = 0; i < om.getSizeX(); i++)
    {
        for (int j = 0; j < om.getSizeY(); j++)
        {
            SDL_Rect g;
            g.w = 16;
            g.h = 8;
            g.y = (i + j) * (8 / 2) - 0* 3;
            g.x = (i - j) * (16 / 2);
            g.x+=50;
            if (om.get(i, j) != -1)
            {
                m_mainWindow->copyTexture(m_mainTexture,
                    &m_mainTileSheet.getTile(
                        OM::getObjectTable().getTileId(
                            om.get(i, j)
                        )
                    ),
                    &g);
            }
        }

    }
}

void RenderManager::renderCivilianList(const stl::array<CrewMember>& cl)
{
    for (int i = 0; i < cl.size(); i++)
    {
        auto& loc = cl[i].getLocation();
        SDL_Rect location = {
            .x = (loc.x - loc.y) * (16 / 2) ,
            .y = (loc.x + loc.y) * (8 / 2),
            .w = 16, 
            .h = 8
        };
        location.x += 50;
        m_mainWindow->copyTexture(m_mainTexture, &m_mainTileSheet.getTile(1), &location);

    }
}
