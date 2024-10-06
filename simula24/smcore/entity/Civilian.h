#ifndef SMCORE_ENTITY_CIVILIAN_H_
#define SMCORE_ENTITY_CIVILIAN_H_

#include <math/Point.h>
#include <smcore/path/AStar.h>
namespace simula24 
{

class Civilian 
{
public:
    
    Civilian() {}
    
    void setLocation(const Point& p) { m_location = p; }
    const Point& getLocation() const { return m_location; }

    void setPath(PointList& p) 
    { 
        m_path = p;
        m_pathIndex = 0;
    }


    void update();

private:
    /// current location
    Point m_location;
    /// Current path
    PointList m_path;
    /// index of current path
    int m_pathIndex;


};

} // simula24



#endif // GAME_ENTITY_CIVILIAN_H_