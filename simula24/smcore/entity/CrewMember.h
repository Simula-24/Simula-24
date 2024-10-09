#ifndef SMCORE_ENTITY_CREW_MEMBER_H_
#define SMCORE_ENTITY_CREW_MEMBER_H_

#include <math/Point.h>
#include <smcore/job/Job.h>
#include "EntityState.h"

namespace simula24 
{

///
/// @brief
///     A crew member
///     Has a path, job, and state
class CrewMember 
{
public:
    
    CrewMember();
    CrewMember& operator=(const CrewMember& o);


    void setLocation(const Point& p) { m_location = p; }
    const Point& getLocation() const { return m_location; }

    void setPath(PointList& p);

    PointList& getPath() { return m_path; }

    void update();
    
    void setJob(LocalJob& j);

    EntityState getCurrentState() const { return m_state; }

private:
    /// current location
    Point m_location;
    /// Current path
    PointList m_path;
    /// index of current path
    int m_pathIndex;
    LocalJob m_currentJob;
    EntityState m_state;

};

} // simula24



#endif // GAME_ENTITY_CREW_MEMBER_H_