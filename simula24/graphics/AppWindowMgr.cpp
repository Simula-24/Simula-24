#include "AppWindowMgr.h"

#include <SDL.h>

using simula24::AppWindow;
using simula24::AppWindowMgr;

bool AppWindowMgr::createWindow(U32 name, const stl::string& title, int w, int h, int x, int y)
{
    AppWindow nwin;
    if (nwin.create(title, w, h, x, y))
    {
        //m_windows.insert({ name, nwin });
        return true;
    }

    return false;
}