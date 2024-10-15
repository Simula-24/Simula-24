#include "RenderManager.h"

#include <SDL.h>
#include <SDL_image.h>

#include <core/log/log.h>
#include <core/error/error.h>

#include <graphics/tile/TileConfig.h>
#include <graphics/renderer/Camera.h>
#include <graphics/tile/SheetLoader.h>
#include <graphics/tile/TileSheetParser.h>

#include <smcore/map/ObjectMap.h>
#include <smcore/entity/CrewMember.h>

#include <objectmanager/ObjectManager.h>
#include <cassert>

#include <imgui.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <backends/imgui_impl_sdl2.h>

using simula24::RenderManager;
using simula24::TileSheetParser;
using simula24::TileConfig;
using simula24::Status;
using simula24::CrewMember;

RenderManager RenderManager::s_instance;

RenderManager::RenderManager()
    : m_mainWindow(nullptr), m_tileDB{}, m_camera(nullptr)
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls



    if (!m_wm.createWindow('main', "Simula 24", 1280, 720))
    {
        ENGINE_CRITICAL("Failed to create new window");
        return ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE;
    }

    m_mainWindow = m_wm.getAppWindow('main');
    ImGui_ImplSDL2_InitForSDLRenderer(m_mainWindow->getWindow(), m_mainWindow->getRenderer());
    ImGui_ImplSDLRenderer2_Init(m_mainWindow->getRenderer());
    return OK;
}

Status RenderManager::terminate()
{
    IMG_Quit();
    SDL_Quit();
    return OK;
}

Status RenderManager::loadTileDatabase(const stl::string& directory)
{

    CLIENT_INFO("Loading tile database at %s", directory.c_str());

    SheetLoader loader(m_tileDB, m_mainWindow->getTextureManager());
    if (!loader.loadWorldTiles(directory))
        return FAILED;
    return OK;

}

void RenderManager::renderFromObjectMap(const ObjectMap& om)
{
    for (int i = 0; i < om.getSizeX(); i++)
    {
        for (int j = 0; j < om.getSizeY(); j++)
        {

            int id = om.get(i, j);
            if (id == -1)
                continue;

            int height = OM::getObjectTable().getTileSize(id);

         
            SDL_Texture* tex = m_tileDB.worldTiles[0].getTexture();
            const SDL_Rect* d = &m_tileDB.worldTiles[0].getTile(
                OM::getObjectTable().getTileId(
                    id
                )
            );
            
            SDL_Rect g;
            int h, w;
                h = d->h; w = d->w;
            g.w = w/4;
            g.h = h/4;
            g.y = j + (j*w/4);
            g.x = i + (i*h/4);
            g.x += m_camera->getX();
            g.y += m_camera->getY();
            m_mainWindow->copyTexture(tex, d, &g);
        }

    }
}

void RenderManager::renderCivilianList(const stl::array<CrewMember>& cl)
{
    for (int i = 0; i < cl.size(); i++)
    {
        auto* tile = &m_tileDB.worldTiles[0].getTile(1);
        auto& loc = cl[i].getLocation();
        SDL_Rect location = {
            .x = loc.x + ((tile->w/4)*loc.x),
            .y = loc.y + ((tile->w/4)*loc.y),
            .w = tile->w/4, 
            .h = tile->h/4
        };
        location.x += m_camera->getX();
        location.y += m_camera->getY();
        m_mainWindow->copyTexture(m_tileDB.worldTiles[0].getTexture(),tile, &location);

    }
}

void RenderManager::newFrame()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    m_mainWindow->clear();
}

void RenderManager::endFrame()
{

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_mainWindow->getRenderer());
    m_mainWindow->present();
}
