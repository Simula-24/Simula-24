#ifndef GRAPHICS_TEXTURE_MANAGER_H_
#define GRAPHICS_TEXTURE_MANAGER_H_

#include <SDL.h>
#include <core/stl/string.h>
#include <utility>
namespace simula24
{

///
/// @brief
///     Manage textures used by a specific SDL_Renderer
///     This is mostly used in the context of AppWindows
/// 
class TextureManager
{
public:

    TextureManager() : m_renderer(nullptr) {}
    TextureManager(TextureManager&& o)
        : m_renderer(std::exchange(o.m_renderer, nullptr)) {}
    
    TextureManager& operator=(TextureManager&& o)
    {
        m_renderer = std::exchange(o.m_renderer, nullptr);
        return *this;
    }

    TextureManager(const TextureManager& o)
        : m_renderer(o.m_renderer)
    {}
    
    TextureManager& operator=(const TextureManager& o)
    {
        m_renderer = o.m_renderer;
        return *this;
    }


    
    ///
    /// @brief
    ///     Load a texture from the disk
    /// 
    /// @returns nullptr on fail
    /// 
    SDL_Texture* loadFromFile(const stl::string& location);

    ///
    /// @brief
    ///     Set the renderer
    ///     This will generate a warning in debug builds if 
    ///     there is already a renderer attached.
    /// 
    void setRenderer(SDL_Renderer* r);

private:

    SDL_Renderer* m_renderer;

};

} // simula24


#endif // GRAPHICS_TEXTURE_MANAGER_H_