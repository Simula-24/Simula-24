#ifndef GRAPHICS_APP_WINDOW_H_
#define GRAPHICS_APP_WINDOW_H_

#include <SDL.h>
#include <core/stl/string.h>
#include <graphics/TextureManager.h>
#include <core/types.h>
namespace simula24
{

///
/// @brief
///     A medium for displaying stuff
/// 
///     Mostly just a wrapper around SDL_Window/SDL_Renderer
/// 
///     This also includes a texture manager, as each texture can
///     only be associated with one renderer
/// 
class AppWindow
{
public:

    AppWindow() 
        : m_window(nullptr), m_renderer(nullptr), m_texManager{} {}
    
    AppWindow(const AppWindow&) = default;
    AppWindow& operator=(const AppWindow&) = default;

    AppWindow(AppWindow&&);
    AppWindow& operator=(AppWindow&&);

    ~AppWindow() { destroy(); }
    
    ///
    /// @brief 
    ///     Create a new window with name as title
    /// 
    bool create(const stl::string& name, int w, int h,
        int x = SDL_WINDOWPOS_UNDEFINED, 
        int y = SDL_WINDOWPOS_UNDEFINED);

    /// Destroy the window
    void destroy();

    /// Clear the contents of the window
    inline void clear() { SDL_RenderClear(m_renderer); }
    
    ///
    /// @brief
    ///     Copy a texture (i.e from a tilesheet) from source to the screen
    /// 
    /// @param dest
    ///     if nullptr, dest is the same as source
    /// 
    inline void copyTexture(SDL_Texture* tex, const SDL_Rect* source, const SDL_Rect* dest = nullptr) { SDL_RenderCopy(m_renderer, tex, source, dest); }
    
    /// Update the screen 
    inline void present() { SDL_RenderPresent(m_renderer); }

    inline TextureManager& getTextureManager() { return m_texManager; }

    FORCEINLINE SDL_Renderer* getRenderer() const { return m_renderer; }
private:

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    
    SDL_Rect m_dimensions;
    stl::string m_name;

    TextureManager m_texManager;
};


} // simula24


#endif // GRAPHICS_APP_WINDOW_H_