#ifndef GRAPHICS_RENDERER_CAMERA_H_
#define GRAPHICS_RENDERER_CAMERA_H_

#include <math/Point.h>
#include <SDL_rect.h>
#include <core/types.h>
namespace simula24
{

///
/// @brief
///     Camera class for SDL
/// 
///     In SDL, "views" don't work as they do with traditional graphics APIs,
///     That is, there is no model-view-projection matrix, instead we just have 
///     offsets.
///     
///     
class Camera
{
public:

    FORCEINLINE void incX(int amount) { m_loc.x += amount; }
    FORCEINLINE void incY(int amount) { m_loc.y += amount; }
    FORCEINLINE int getX() const { return m_loc.x; }
    FORCEINLINE int getY() const { return m_loc.y; }

private:
    Point m_loc;
    //SDL_Rect m_bounds;
};


} // simula24

#endif // GRAPHICS_RENDERER_CAMERA_H_