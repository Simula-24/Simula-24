#include "Application.h"

#include <cassert>
#include <chrono>
#include <thread>
#include <stdio.h>

#include <SDL.h>

#include <core/log/log.h>
#include <math/Point.h>
#include <core/system/Clock.h>

#include <graphics/renderer/Camera.h>
#include <graphics/tile/TileSheetParser.h>

#include <smcore/localsystem/LocalCluster.h>

#include <objectmanager/ObjectManager.h>


#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

using simula24::Application;
using simula24::Status;
void drawCircle(SDL_Renderer* r, simula24::Point p, int radius);
void drawTriangle(SDL_Renderer* r, simula24::Point p, int radius);
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
    
    if ((stat = RM::get().init()) != OK)
    {
        ENGINE_CRITICAL("Failed to initialize graphic subsystem");
        return stat;
    }
    
    if (!m_wm.createWindow('main', "Simula 24", 1280, 720))
    {
        ENGINE_CRITICAL("Failed to create new window");
        return ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE;
    }

    m_mainWindow = m_wm.getAppWindow('main');

    RM::get().setWindow(m_mainWindow);
    RM::get().addTileSheet("../data/tileset/cp437/tileset.inf");
    
  
    m_shouldRun = true;

    return OK;
}

void Application::run()
{
    Camera cam{};
    RM::get().setCamera(&cam);
    cam.incX(50);
    
    SDL_Event event;
    SDL_RenderSetVSync(m_mainWindow->getRenderer(), 1);
    
    Clock gameClock;
    gameClock.reset();

    gameClock.start();
    while (m_shouldRun)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                m_shouldRun = false;
                break;
            }

            else if(event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        cam.incY(gameClock.getDelta());
                        break;
                    case SDLK_DOWN:
                        cam.incY(-gameClock.getDelta());
                        break;
                    case SDLK_LEFT:
                        cam.incX(gameClock.getDelta());
                        break;
                    case SDLK_RIGHT:
                        cam.incX(-gameClock.getDelta());
                        break;
                }
            }
   
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        bool t = true;
        ImGui::ShowDemoWindow(&t);
        gameClock.tick();
        m_mainWindow->clear();
        
        m_activeSim.update();
        RM::get().renderFromObjectMap(m_activeSim.getObjectMap());
        RM::get().renderCivilianList(m_activeSim.getCrewMemberList());
        
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_mainWindow->getRenderer());
        RM::get().present();
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void drawCircle(SDL_Renderer* r, simula24::Point p, int radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);
    SDL_SetRenderDrawColor(r, 0, 0x0, 0xff, 0xff);
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(r, p.x + x, p.y - y);
        SDL_RenderDrawPoint(r, p.x + x, p.y + y);
        SDL_RenderDrawPoint(r, p.x - x, p.y - y);
        SDL_RenderDrawPoint(r, p.x - x, p.y + y);
        SDL_RenderDrawPoint(r, p.x + y, p.y - x);
        SDL_RenderDrawPoint(r, p.x + y, p.y + x);
        SDL_RenderDrawPoint(r, p.x - y, p.y - x);
        SDL_RenderDrawPoint(r, p.x - y, p.y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    SDL_SetRenderDrawColor(r, 0,0,0,0);

}

void drawTriangle(SDL_Renderer* r, simula24::Point p, int radius)
{
    simula24::Point p1 = { p.x, p.y - radius };
    simula24::Point p2 = { p.x + radius, p.y + radius };
    simula24::Point p3 = { p.x - radius, p.y + radius };
    SDL_SetRenderDrawColor(r, 0xff, 0, 0, 0xff);

    SDL_RenderDrawLine(r, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(r, p1.x, p1.y, p3.x, p3.y);
    SDL_RenderDrawLine(r, p2.x, p2.y, p3.x, p3.y);

}