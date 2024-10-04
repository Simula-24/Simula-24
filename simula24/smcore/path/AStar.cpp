#include "AStar.h"

#include <core/stl/priority_queue.h>
#include <core/stl/unordered_map.h>
#include <algorithm>
using simula24::Point;

static int heuristic(const Point& goal, const Point& n)
{
    int dx = abs(goal.x - n.x);
    int dy = abs(goal.y - n.y);
    return 1 * (dx + dy) + 1 * ((dx > dy) * dy + (dy > dx) * dx);
}


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
        for (auto i : map.getNeighbors(cur))
        {
            if(!came_from.contains(i))
            {
                frontier.push(i, 0);
                came_from.insert({ i, cur });
            }
        }

    }

    Point it = end;
    while (it != start)
    {
        out.push_back(it);
        it = came_from[it];
    }
    std::reverse(out.begin(), out.end());
;    return true;
}
