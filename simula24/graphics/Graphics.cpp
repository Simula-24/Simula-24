#include <simula24/graphics/Graphics.h>
#include <core/log/log.h>
#include <SDL.h>
#include <SDL_image.h>

using simula24::Graphics;
using simula24::Status;

Graphics Graphics::s_instance;


Status Graphics::init()
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
    
    return OK;
}

void Graphics::terminate()
{
    IMG_Quit();
    SDL_Quit();
}