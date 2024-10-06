#ifndef SMCORE_MAP_OBJECT_MAP_H_
#define SMCORE_MAP_OBJECT_MAP_H_

#include <core/stl/array.h>
#include <math/Point.h>
namespace simula24
{

///
/// @brief 
///     Holds a 2D array of OIDs
/// 
class ObjectMap
{
public:
    ObjectMap(size_t sizex, size_t sizey)
        : m_szx(sizex), m_szy(sizey)
    {
        m_oidMap.resize(sizex * sizey);
        m_oidMap.fill(-1);
    }
    
    constexpr void set(int x, int y, int id) { m_oidMap[y * m_szx + x] = id; }
    constexpr int get(int x, int y) const { return m_oidMap[y * m_szx + x]; }

    constexpr size_t getSizeX() const { return m_szx; }
    constexpr size_t getSizeY() const { return m_szy; }

    int getNeighbors(Point& n, stl::array<Point>&) const;

    int getPassableNeighbors(Point& n, stl::array<Point>&) const;

private:
    stl::array<int> m_oidMap;
    size_t m_szx;
    size_t m_szy;
};

}

#endif // GAME_MAP_OBJECT_MAP_H_