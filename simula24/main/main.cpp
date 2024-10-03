#include <cstdio>
#include <core/log/log.h>
#include <core/error/seh.h>

#include <graphics/Graphics.h>
#include <game/Application.h>
using namespace simula24;

int main(int argc, char** argv)
{
    DebugLoggers::init();
    setSEHHandler();
    ENGINE_INFO("SEH Handler set");
    
    Graphics::get().terminate();
    Application app;
    if (app.init() != OK)
        return -1;
    app.run();
    return 0;

}