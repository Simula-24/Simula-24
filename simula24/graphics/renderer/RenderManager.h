#ifndef GRAPHICS_RENDERER_RENDER_MANAGER_H_
#define GRAPHICS_RENDERER_RENDER_MANAGER_H_

#include <SDL.h>
#include <graphics/tile/TileSheet.h>
#include <graphics/AppWindow.h>
#include <graphics/AppWindowMgr.h>
#include <core/stl/smart_ptr.h>
#include <core/error/error.h>
#include <graphics/tile/TileSheetDatabase.h>
namespace simula24
{

class ObjectMap;
class CrewMember;
class Camera;

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

    ///
    /// @brief
    ///     Parse the games tile sheets
    /// 
    Status loadTileDatabase(const stl::string& directory);


    ///
    /// @brief
    ///     Render objects found in an object map
    ///     Will skip over empty (-1) entries
    /// 
    void renderFromObjectMap(const ObjectMap& om);
    
    ///
    /// @brief
    ///     Render a list of crew members
    ///     TODO: see if this should be general, as in renderCreatures() or something
    /// 
    void renderCivilianList(const stl::array<CrewMember>& cl);


    void newFrame();
    void endFrame();

    /// Present/swap buffers
    inline void present() 
    { 
        assert(m_mainWindow);
        m_mainWindow->present(); 
    }
    
    inline void setCamera(Camera* cam) { m_camera = cam; }

private:

    /// Window Manager
    AppWindowMgr m_wm;
    /// Primary window
    AppWindow* m_mainWindow;
    /// Database containing all of our tilesheets
    TileSheetDatabase m_tileDB;
    
    Camera* m_camera;

    int m_globTileWidth;
    int m_globTileHeight;

    int m_tilesPerRow;
    int m_tilesPerColumn;


    
    
    ///////////////////////////////////////////
    ////////// SINGLETON BOILERPLATE //////////
    ///////////////////////////////////////////

public:
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;
    constexpr static RenderManager& get() { return s_instance; }
private:
    RenderManager();
    static RenderManager s_instance;

};


} // simula24

using RM = simula24::RenderManager;

#endif // GRAPHICS_RENDERER_RENDER_MANAGER_H_