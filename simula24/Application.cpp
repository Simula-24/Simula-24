#include "Application.h"

#include <graphics/Graphics.h>
#include <core/log/log.h>
#include <cassert>
#include <graphics/tile/TileSheetParser.h>
#include <SDL.h>
#include <objectmanager/ObjectManager.h>
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

    m_rendermgr.setWindow(m_mainWindow);
    m_rendermgr.addTileSheet("../data/tileset/cp437/tileset.inf");
    
  
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
        m_rendermgr.renderFromObjectMap(m_activeSim.getObjectMap());

        m_rendermgr.present();
    }
}

