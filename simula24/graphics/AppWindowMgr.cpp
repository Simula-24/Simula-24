#include "AppWindowMgr.h"

#include <SDL.h>
using simula24::AppWindow;
using simula24::AppWindowMgr;

AppWindowMgr::~AppWindowMgr()
{
    for (auto& i : m_windows)
    {
        i.second.~AppWindow();
    }
}

bool AppWindowMgr::createWindow(U32 name, const stl::string& title, int w, int h, int x, int y)
{
    AppWindow nwin;
    if (nwin.create(title, w, h, x, y))
    {
        m_windows[name] = AppWindow{ stl::move(nwin) };
        return true;
    }

    return false;
}

AppWindow* AppWindowMgr::getAppWindow(U32 name)
{
    auto iter = m_windows.find(name);
    if (iter != m_windows.end())
        return &iter->second;
    return nullptr;
}