#ifndef GRAPHICS_APP_WINDOW_MGR_H_
#define GRAPHICS_APP_WINDOW_MGR_H_

#include <core/stl/unordered_map.h>
#include "AppWindow.h"
#include <core/types.h>

#include <optional>

namespace simula24
{

///
/// @brief
///     Manages @ref AppWindow s
/// 
class AppWindowMgr
{
public:

    AppWindowMgr() {}
    ~AppWindowMgr();
    bool createWindow(U32 id, const stl::string& title, int w, int h, 
            int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED);
    AppWindow* getAppWindow(U32 id);
private:

    stl::unordered_map<U32, AppWindow> m_windows;
};

} // simula24

#endif // GRAPHICS_APP_WINDOW_MGR_H_