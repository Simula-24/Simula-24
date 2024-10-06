#ifndef GAME_PATH_A_STAR_H_
#define GAME_PATH_A_STAR_H_

#include <math/Point.h>
#include <core/stl/array.h>
#include <vector>
#include <smcore/map/ObjectMap.h>
namespace simula24
{

bool AStarPathFind(const Point& start, const Point& end, PointList& out, const ObjectMap& map);

} // simula24


#endif // GAME_PATH_A_STAR_H_