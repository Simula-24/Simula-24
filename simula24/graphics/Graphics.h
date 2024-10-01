#ifndef GRAPHICS_GRAPHICS_H_
#define GRAPHICS_GRAPHICS_H_

#include <SDL.h>
#include <core/error/error.h>


namespace simula24 
{

class Graphics 
{
public:
    constexpr static Graphics& get() { return s_instance; }

    Status init();
    void terminate();

public:
    /// Singleton boilerplate
    void operator=(const Graphics&) = delete;
    Graphics(const Graphics&) = delete;
private:
    Graphics() {}

    static Graphics s_instance;

};

} // simula24



#endif // GRAPHICS_GRAPHICS_H_