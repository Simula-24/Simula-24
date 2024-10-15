#include "Application.h"

#include <cassert>
#include <chrono>
#include <thread>
#include <stdio.h>

#include <SDL.h>

#include <core/log/log.h>
#include <math/Point.h>
#include <core/system/Clock.h>
#include <core/system/Scheduler.h>

#include <graphics/renderer/Camera.h>
#include <graphics/tile/TileSheetParser.h>

#include <smcore/localsystem/LocalCluster.h>

#include <objectmanager/ObjectManager.h>


#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <ui/debug/console/DbgConsole.h>
using simula24::Application;
using simula24::Status;
void drawCircle(SDL_Renderer* r, simula24::Point p, int radius);
void drawTriangle(SDL_Renderer* r, simula24::Point p, int radius);
Application::Application()
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
#if defined(SIMULA24_DEBUG)
    RM::get().loadTileDatabase("../data/tileset/cp437/");
#else 
    RM::get().loadTileDatabase("./data/tileset/cp437/");
#endif
  
    m_shouldRun = true;

    return OK;
}

void Application::run()
{
    Camera cam{};
    RM::get().setCamera(&cam);
    cam.incX(50);
    DebugConsoleGfx dbgc;
    SDL_Event event;
    
    Clock gameClock;
    gameClock.reset();

    gameClock.start();
    U64 frames = 0;
    double fps = 0;
    Scheduler test(0.25, [&]() {m_activeSim.update(); });
    test.start();
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
                        cam.incY(1000*gameClock.getDelta());
                        break;
                    case SDLK_DOWN:
                        cam.incY(-1000 * gameClock.getDelta());
                        break;
                    case SDLK_LEFT:
                        cam.incX(1000 * gameClock.getDelta());
                        break;
                    case SDLK_RIGHT:
                        cam.incX(-1000 * gameClock.getDelta());
                        break;
                    case SDLK_BACKQUOTE:
                        dbgc.setActive(!dbgc.isActive());
                        break;

                }
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                cam.incScale(-event.wheel.y);
            }
        }

        RM::get().newFrame();
        test.update();
        gameClock.tick();
        dbgc.show();
        fps = 1 / gameClock.getDelta();
        ImGui::Text("DELTA: %lf", gameClock.getDelta());
        ImGui::Text("FPS: %lf", fps);
        ImGui::Text("Total uptime: %lf", gameClock.getTotal());
        ImGui::Text("Zoom: x%d", 7-cam.getScale());
        RM::get().renderFromObjectMap(m_activeSim.getObjectMap());
        RM::get().renderCivilianList(m_activeSim.getCrewMemberList());
        RM::get().endFrame();

        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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