#include "AStar.h"

#include <core/stl/priority_queue.h>
#include <core/stl/unordered_map.h>


bool simula24::AStarPathFind(const Point& start, const Point& end, stl::array<Point>& out, const ObjectMap& map)
{
    stl::priority_queue<Point> frontier;
    stl::unordered_map<Point, Point> came_from;
    stl::unordered_map<Point, int> cost_so_far;

    frontier.push(start, 0);
    came_from.insert({ start, start });
    cost_so_far.insert({ start, 0 });

    while (!frontier.empty())
    {
        Point cur = frontier.pop().object;
        if (cur == end)
            break;
        
    }


    return true;
}
