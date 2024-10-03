#include "Point.h"

namespace simula24
{

bool operator==(const Point& l, const Point& r)
{
    return (l.x == r.x && l.y == r.y);
}
bool operator!=(const Point& l, const Point& r)
{
    return (l.x != r.x || l.y != r.x);
}
bool operator<(const Point& l, const Point& r)
{
    return (l.x < r.x) || (l.y < r.y && l.x == r.x);
}
bool operator>(const Point& l, const Point& r)
{
    return (l.x > r.x) || (l.y > r.y && l.x == r.x);
}

}