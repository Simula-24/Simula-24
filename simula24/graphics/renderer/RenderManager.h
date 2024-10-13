#ifndef GRAPHICS_RENDERER_RENDER_MANAGER_H_
#define GRAPHICS_RENDERER_RENDER_MANAGER_H_

#include <SDL.h>
#include <graphics/tile/TileSheet.h>
#include <graphics/AppWindow.h>
#include <core/stl/smart_ptr.h>
#include <core/error/error.h>
#include <graphics/tile/TileSheetDatabase.h>
namespace simula24
{

class ObjectMap;
class CrewMember;
///
/// @brief
///     Manages rendering to the main window
/// 
class RenderManager
{
public:

    /// 
    /// @brief
    ///     Initialize SDL/SDL Image
    /// @returns    
    ///     OK on success
    ///     ERR_LIB_INIT on fail
    /// 
    Status init();
    
    ///
    /// @brief
    ///     Tears down SDL/SDL_Image
    /// 
    Status terminate();

    void setWindow(AppWindow* win);

    void addTileSheet(const stl::string& configLoc);

    void renderFromObjectMap(const ObjectMap& om);
    void renderCivilianList(const stl::array<CrewMember>& cl);
    inline void present() 
    { 
        assert(m_mainWindow);
        m_mainWindow->present(); 
    }
    
public:
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;
    constexpr static RenderManager& get() { return s_instance; }
private:
    RenderManager();
    static RenderManager s_instance;

private:

    AppWindow* m_mainWindow;
    
    SDL_Texture* m_mainTexture;
    
    TileSheet m_mainTileSheet;

    int m_globTileWidth;
    int m_globTileHeight;

    int m_tilesPerRow;
    int m_tilesPerColumn;

    TileSheetDatabase m_tileDB;
};


} // simula24

using RM = simula24::RenderManager;

#endif // GRAPHICS_RENDERER_RENDER_MANAGER_H_