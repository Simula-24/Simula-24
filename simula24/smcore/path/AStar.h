#ifndef GAME_PATH_A_STAR_H_
#define GAME_PATH_A_STAR_H_

#include <math/Point.h>
#include <core/stl/array.h>
#include <smcore/map/ObjectMap.h>
namespace simula24
{

using PointList = stl::array<Point>;

bool AStarPathFind(const Point& start, const Point& end, stl::array<Point>& out, const ObjectMap& map);

} // simula24


#endif // GAME_PATH_A_STAR_H_