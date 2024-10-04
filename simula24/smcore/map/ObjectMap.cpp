#include "ObjectMap.h"
#include <smcore/map/NeighborMap.h>

using simula24::ObjectMap;
using simula24::Point;

stl::array<Point> ObjectMap::getNeighbors(Point& n) const
{
    stl::array<Point> out;
    out.resize(8);
    for (int i = 0; i < 8; i++)
    {

        int nx = (n.x + NeighborMap[i][0]);
        int ny = (n.y + NeighborMap[i][1]);

        if (nx >= 0 && nx < m_szx &&
            ny >= 0 && ny < m_szy)
        {
            if (m_oidMap[(nx * m_szx) + ny] == -1) {
                out.push_back(Point{ nx, ny });
            }
        }
    }
    return out;
}

int ObjectMap::getNeighbors(Point& n, stl::array<Point>& out) const
{
    int x = 0;
    for (int i = 0; i < 8; i++)
    {

        int nx = (n.x + NeighborMap[i][0]);
        int ny = (n.y + NeighborMap[i][1]);

        if (nx >= 0 && nx < m_szx &&
            ny >= 0 && ny < m_szy)
        {
            if (m_oidMap[(nx * m_szx) + ny] == -1) {
                out[x++] = Point{ nx, ny };
            }
        }
    }
    return x;
}
