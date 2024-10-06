#include "AStar.h"

#include <core/stl/priority_queue.h>
#include <core/stl/unordered_map.h>
#include <unordered_map>
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
    stl::priority_queue<Point> frontier(100);
    std::unordered_map<Point, Point> came_from;
    std::unordered_map<Point, int> cost_so_far;
    
    frontier.push(start, 0);
    came_from.insert({ start, start });
    cost_so_far.insert({ start, 0 });

    stl::array<Point> n;
    
    n.resize(10);
    
    while (!frontier.empty())
    {
        Point cur = frontier.pop().object;
        if (cur == end)
            break;
        
        int x = map.getPassableNeighbors(cur, n);
        
        for (int i = 0; i < x; i++)
        {
            if(!came_from.contains(n[i]))
            {
                frontier.push(n[i], 0);
                came_from.insert({ n[i], cur });
            }
        }

    }

    Point it = end;
    while (it != start)
    {
        out.push_back(it);
        it = came_from[it];
    }
    out.push_back(start);
    for (auto& i : out) printf("%d %d\n", i.x, i.y);

    auto outstart = out.begin();
    auto outend = out.end();

    while (outstart != outend && outstart != --outend) {

        std::iter_swap(outstart, outend);
        ++outstart;
    }

    for (auto& i : out) printf("%d %d\n",i.x,i.y);

;    return true;
}
