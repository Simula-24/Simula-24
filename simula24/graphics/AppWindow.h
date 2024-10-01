#ifndef GRAPHICS_APP_WINDOW_H_
#define GRAPHICS_APP_WINDOW_H_

#include <SDL.h>
#include <core/stl/string.h>

namespace simula24
{

///
/// @brief
///     A medium for displaying stuff
/// 
///     Mostly just a wrapper around SDL_Window/SDL_Renderer
/// 
class AppWindow
{
public:

    AppWindow() 
        : m_window(nullptr), m_renderer(nullptr) {}
    
    AppWindow(AppWindow&&);
    AppWindow& operator=(AppWindow&&);

    
    bool create(const stl::string& name, int w, int h, int x, int y);
    void destroy();



private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

};


} // simula24


#endif // GRAPHICS_APP_WINDOW_H_