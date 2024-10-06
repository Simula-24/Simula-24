#include "ObjectMap.h"
#include <smcore/path/AStar.h>
#include <objectmanager/ObjectManager.h>
#include <smcore/map/NeighborMap.h>
using simula24::ObjectMap;
using simula24::Point;

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

int simula24::ObjectMap::getPassableNeighbors(Point& n, PointList& out) const
{
    int x = 0;
    for (int i = 0; i < 4; i++)
    {

        int nx = (n.x + NeighborMap[i][0]);
        int ny = (n.y + NeighborMap[i][1]);

        if (nx >= 0 && nx < m_szx &&
            ny >= 0 && ny < m_szy)
        {
            int oid = m_oidMap[(nx * m_szx) + ny];
            if (oid == -1) {
                out[x++] = Point{ nx, ny };
            }
        }
    }
    return x;
}
