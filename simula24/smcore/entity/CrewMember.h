#ifndef SMCORE_ENTITY_CREW_MEMBER_H_
#define SMCORE_ENTITY_CREW_MEMBER_H_

#include <math/Point.h>
#include <smcore/path/AStar.h>
namespace simula24 
{

class CrewMember 
{
public:
    
    CrewMember() : m_path() {}
    CrewMember& operator=(const CrewMember& o)
    {
        m_path = o.m_path;
        return *this;
    }
    void setLocation(const Point& p) { m_location = p; }
    const Point& getLocation() const { return m_location; }

    void setPath(PointList& p) 
    { 
        m_path = std::move(p);
        m_pathIndex = 0;
    }

    PointList& getPath() { return m_path; }

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



#endif // GAME_ENTITY_CREW_MEMBER_H_