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
    
    AppWindow(const AppWindow&) = default;
    AppWindow& operator=(const AppWindow&) = default;

    AppWindow(AppWindow&&);
    AppWindow& operator=(AppWindow&&);

    ~AppWindow() { destroy(); }
    
    bool create(const stl::string& name, int w, int h,
        int x = SDL_WINDOWPOS_UNDEFINED, 
        int y = SDL_WINDOWPOS_UNDEFINED);

    void destroy();

    __forceinline void clear() { SDL_RenderClear(m_renderer); }
    
    __forceinline void copyTexture(SDL_Texture* tex, const SDL_Rect* source, const SDL_Rect* dest = nullptr) { SDL_RenderCopy(m_renderer, tex, source, dest); }
    
    __forceinline void present() { SDL_RenderPresent(m_renderer); }

    // TODO: delete after texmanager
    inline SDL_Renderer* getRenderer() { return m_renderer; }
private:
    SDL_Window* m_window;
    
    SDL_Renderer* m_renderer;
    
    SDL_Rect m_dimensions;
    
    stl::string m_name;
};


} // simula24


#endif // GRAPHICS_APP_WINDOW_H_