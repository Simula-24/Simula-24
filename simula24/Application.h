#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

#include <graphics/AppWindowMgr.h>
#include <core/error/error.h>
#include <graphics/tile/TileSheet.h>
#include <core/stl/smart_ptr.h>

#include <smcore/map/ObjectMap.h>
#include <objectmanager/object/ObjectTable.h>

namespace simula24
{

class Application
{
public:

    Application();
    ~Application();

    Status init();
    void run();

private:

    void update();
    
private:
    AppWindowMgr m_wm;
    AppWindow* m_mainWindow;
    /// it might look dumb, but this is just a pre-pre-alpha 
    SDL_Texture* m_mainTexture;
    stl::shared_ptr<TileSheet> m_mainTileSheet;

    ObjectMap m_objectMap;
    ObjectTable m_objectTable;

    bool m_shouldRun{ false };

};


} // simula24

#endif // GAME_APPLICATION_H_