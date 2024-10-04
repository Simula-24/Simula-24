#ifndef GRAPHICS_RENDERER_RENDER_MANAGER_H_
#define GRAPHICS_RENDERER_RENDER_MANAGER_H_

#include <SDL.h>
#include <graphics/tile/TileSheet.h>
#include <graphics/AppWindow.h>
#include <core/stl/smart_ptr.h>


namespace simula24
{

class ObjectMap;

///
/// @brief
///     Manages rendering to the main window
/// 
class RenderManager
{
public:

    RenderManager();
    ~RenderManager();

    void setWindow(AppWindow* win);

    void addTileSheet(const stl::string& configLoc);

    void renderFromObjectMap(const ObjectMap& om);
    
private:

    AppWindow* m_mainWindow;
    
    SDL_Texture* m_mainTexture;
    
    stl::shared_ptr<TileSheet> m_mainTileSheet;

    int m_globTileWidth;
    int m_globTileHeight;
};


} // simula24

#endif // GRAPHICS_RENDERER_RENDER_MANAGER_H_