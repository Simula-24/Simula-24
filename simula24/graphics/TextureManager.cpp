#include "TextureManager.h"
#include <cassert>

#include <SDL.h>
#include <SDL_image.h>

#include <core/log/log.h>

using simula24::TextureManager;

SDL_Texture* TextureManager::loadFromFile(const stl::string& location)
{
    assert(m_renderer != nullptr);

    SDL_Texture* texture;
    SDL_Surface* tempSurface;

    ENGINE_INFO("Loading texture at %s",location.c_str());
    tempSurface = IMG_Load(location.c_str());
    if (!tempSurface)
    {
        ENGINE_ERROR("Failed to load texture at %s: %s", location.c_str(), IMG_GetError());

        return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(m_renderer, tempSurface);

    if (!texture)
    {
        ENGINE_ERROR("Failed to load texture at %s: %s", location.c_str(), SDL_GetError());
        // no early return
        // if we failed here, clients will detect
        // when they get a nullptr from 'texture' var
        // extra cleanup would be extraneous
    }

    SDL_FreeSurface(tempSurface);
    
    return texture;
}

void TextureManager::setRenderer(SDL_Renderer* r) 
{
#ifdef _DEBUG
    if (m_renderer)
        ENGINE_WARNING("TextureManager::setRenderer: replacing renderer %p with %p. This could cause a resource leak.", m_renderer, r);
#endif
    m_renderer = r;
}
