#ifndef GAME_ENTITY_CIVILIAN_H_
#define GAME_ENTITY_CIVILIAN_H_

#include <math/Point.h>

namespace simula24 
{

class Civilian 
{
public:
    Civilian() {}
    void setLocation(const Point& p) { m_location = p; }
    const Point& getLocation() const { return m_location; }

private:
    Point m_location;
};

} // simula24



#endif // GAME_ENTITY_CIVILIAN_H_