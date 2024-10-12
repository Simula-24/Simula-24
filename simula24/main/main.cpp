#include <cstdio>
#include <core/log/log.h>
#include <core/error/seh.h>

#include <Application.h>
using namespace simula24;

int main(int argc, char** argv)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    DebugLoggers::init();
    setSEHHandler();
    ENGINE_INFO("SEH Handler set");
    
    Application app;
    if (app.init() != OK)
        return -1;
    app.run();
    return 0;

}