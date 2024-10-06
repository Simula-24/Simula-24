#include "AStar.h"
#include <cassert>
#include <core/stl/priority_queue.h>
#include <core/stl/unordered_map.h>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <core/log/log.h>
#include <queue>
using simula24::Point;



static int heuristic(const Point& goal, const Point& n)
{
    int dx = abs(goal.x - n.x);
    int dy = abs(goal.y - n.y);
    return dx - dy;
    //return 1 * (dx + dy) + 1 * ((dx > dy) * dy + (dy > dx) * dx);
}


bool simula24::AStarPathFind(const Point& start, const Point& end, PointList& out, const ObjectMap& map)
{
    CLIENT_INFO("AStar begin: (%d, %d) -> (%d, %d)",
        start.x, start.y,
        end.x, end.y
    );
    std::queue<Point> frontier;
    std::unordered_map<Point, Point> came_from;
    std::unordered_map<Point, int> cost_so_far;
    
    frontier.push(start);
    came_from[start] = start;
    PointList n;
    
    n.resize(5);
    int iter = 0;
    
    while (!frontier.empty())
    {
        Point cur = frontier.front();
            frontier.pop();
        //frontier.pop();
        if (cur == end)
            break;
        
        int x = map.getPassableNeighbors(cur, n);
        
        for (int i = 0; i < x; i++)
        {
            Point& next = n[i];
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = cur;
            }
        }

    }
    if (!came_from.contains(end))
    {
        CLIENT_ERROR("No path found between (%d, %d) and (%d, %d)",
            start.x, start.y,
            end.x, end.y
        );
        return false;
    }
    Point it = end;

    while (it != start)
    {
        out.push_back(it);
        it = came_from[it];

        if (it == start)
            break;


    }
    out.push_back(start);

    std::reverse(out.begin(), out.end());

;    return true;
}
