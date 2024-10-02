#ifndef GAME_MAP_OBJECT_MAP_H_
#define GAME_MAP_OBJECT_MAP_H_

#include <core/stl/array.h>

namespace simula24
{

class ObjectMap
{
public:
    ObjectMap(size_t sizex, size_t sizey)
        : m_szx(sizex), m_szy(sizey)
    {
        m_oidMap.resize(sizex * sizey);
        m_oidMap.fill_remaining(-1);
    }
    
    inline void set(int x, int y, int id) { m_oidMap[y * m_szx + x] = id; }
    inline int get(int x, int y) { return m_oidMap[y * m_szx + x]; }

private:
    stl::array<int> m_oidMap;
    size_t m_szx;
    size_t m_szy;
};

}

#endif // GAME_MAP_OBJECT_MAP_H_