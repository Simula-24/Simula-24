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


template <typename T, typename priority_t>
class PriorityQueue
{
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement,
        std::vector<PQElement>,
        std::greater<PQElement> > m_pqueue;

public:
    void push(T n, priority_t p)
    {
        m_pqueue.emplace(PQElement{ p, n });
    }

    T pop()
    {
        T elem = m_pqueue.top().second;
        m_pqueue.pop();
        return elem;
    }

    bool empty()
    {
        return m_pqueue.empty();
    }
};


static int heuristic(const Point& goal, const Point& n)
{
    int dx = abs(goal.x - n.x);
    int dy = abs(goal.y - n.y);
    return dx + dy;
    //return 1 * (dx + dy) + 1 * ((dx > dy) * dy + (dy > dx) * dx);
}


bool simula24::AStarPathFind(const Point& start, const Point& end, PointList& out, const ObjectMap& map)
{
    CLIENT_INFO("AStar begin: (%d, %d) -> (%d, %d)",
        start.x, start.y,
        end.x, end.y
    );
    PriorityQueue<Point, int> frontier;
    std::unordered_map<Point, Point> came_from;
    std::unordered_map<Point, int> cost_so_far;
    
    frontier.push(start, 1);
    came_from[start] = start;
    cost_so_far[start] = 0;
    PointList n;
    
    n.resize(5);
#ifdef _DEBUG
    int iter = 0;
#endif
    while (!frontier.empty())
    {
        Point cur = frontier.pop();
        //frontier.pop();
        if (cur == end)
            break;
        
        int x = map.getPassableNeighbors(cur, n);
        for (int i = 0; i < x; i++)
        {
#ifdef _DEBUG
            iter++;
#endif
            Point& next = n[i];
            int new_cost = cost_so_far[cur] + heuristic(cur, next);
            if (!came_from.contains(next) ||
                new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                frontier.push(next, new_cost + heuristic(next, end ));
                came_from[next] = cur;
            }
        }

    }

#ifdef _DEBUG
    CLIENT_DEBUG("(%d, %d) -> (%d, %d). Total path size: %d. Neighbors touched: %ld",
        start.x, start.y, end.x, end.y, iter, came_from.size()
    );
#endif // _DEBUG
    if (!came_from.contains(end))
    {
        CLIENT_ERROR("No path found between (%d, %d) and (%d, %d)",
            start.x, start.y,
            end.x, end.y
        );
        return false;
    }
    Point it = end;
    out.resize(came_from.size());
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
