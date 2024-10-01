#include "AppWindow.h"
#include <utility>
#include <core/stl/string.h>
#include <core/log/log.h>
using simula24::AppWindow;

AppWindow::AppWindow(AppWindow&& other)
    : m_window(std::exchange(other.m_window, nullptr)),
    m_renderer(std::exchange(other.m_renderer, nullptr))
{
    
}

AppWindow& AppWindow::operator=(AppWindow&& other)
{
    m_window   = std::exchange(other.m_window, nullptr);
    m_renderer = std::exchange(other.m_renderer, nullptr);
    return *this;
}

bool AppWindow::create(const stl::string& name, int w, int h, int x, int y)
{
    m_window = SDL_CreateWindow(name.c_str(), x, y, w, h, 0);
    
    if (!m_window)
    {
        ENGINE_ERROR("Failed to create window (name:\"%s\";w:%d;h:%d;x:%d;y:%d): %s",
            name.c_str(), w, h, x, y, SDL_GetError()
        );

        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_renderer)
    {
        ENGINE_ERROR("Failed to create SDL for window \"%s\": %s", name.c_str(), SDL_GetError());
        return false;
    }

    m_dimensions = {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };
    m_name = name;

    return true;

}

void AppWindow::destroy()
{
    // SDL does null checks for us
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
}
