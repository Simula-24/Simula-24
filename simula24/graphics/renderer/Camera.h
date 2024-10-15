#ifndef GRAPHICS_RENDERER_CAMERA_H_
#define GRAPHICS_RENDERER_CAMERA_H_

#include <math/Point.h>
#include <cmath>
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
    Camera()
        : m_loc{ 0,0 }, m_scale(1) 
    {
    }
    
    FORCEINLINE void incX(int amount) { m_loc.x += amount; }
    FORCEINLINE void incY(int amount) { m_loc.y += amount; }
    FORCEINLINE int getX() const { return m_loc.x; }
    FORCEINLINE int getY() const { return m_loc.y; }
    FORCEINLINE int getScale() const { return SDL_clamp(m_scale, 1, 6); }
    void incScale(int amount) 
    {
        if ((m_scale <= 1 && amount <= -1) || (m_scale >= 6 && amount >= 1))
            return;
        m_scale += amount; 
    }
private:
    Point m_loc;
    int m_scale;
    //SDL_Rect m_bounds;
};


} // simula24

#endif // GRAPHICS_RENDERER_CAMERA_H_