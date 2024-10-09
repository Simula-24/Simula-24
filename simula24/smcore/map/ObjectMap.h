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
    
    /// Set (x,y) as ID
    constexpr void set(int x, int y, int id) { m_oidMap[y * m_szx + x] = id; }
    
    /// Get ID at (x,y)
    constexpr int get(int x, int y) const { return m_oidMap[y * m_szx + x]; }

    constexpr size_t getSizeX() const { return m_szx; }
    constexpr size_t getSizeY() const { return m_szy; }

    /// 
    /// @brief
    ///     Get neighbors around point N
    ///     Will get all points that are not set to empty
    ///                     NW  N  NE 
    ///                       \ | /
    ///                    W -- n -- S
    ///                       / | \
    ///                     SW  S  SE
    ///     
    int getNeighbors(Point& n, stl::array<Point>&) const;

    ///
    /// @brief
    ///     Get all points are 'n' that are not empty and 
    ///     are marked as passable in ObjectManager::ObjectTable
    /// 
    int getPassableNeighbors(Point& n, PointList&) const;

private:
    stl::array<int> m_oidMap;
    size_t m_szx;
    size_t m_szy;
};

}

#endif // GAME_MAP_OBJECT_MAP_H_