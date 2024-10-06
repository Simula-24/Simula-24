#ifndef MATH_POINT_H_
#define MATH_POINT_H_

#include <core/stl/hash.h>

namespace simula24
{

///
/// @brief
///     2D Point
/// 
struct Point
{
    int x;
    int y;
    constexpr Point() {}
    constexpr Point(int _x, int _y) : x(_x), y(_y) {}
    
    constexpr Point(const Point& p) : x(p.x), y(p.y) {}

    Point& operator=(const Point& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

};

bool operator==(const Point& l, const Point& r);
bool operator!=(const Point& l, const Point& r);
bool operator<(const Point& l, const Point& r);
bool operator>(const Point& l, const Point& r);



} // simula24

template<>
class stl::hash<simula24::Point>
{
public:
    static uint32_t run(const simula24::Point& p)
    {
        return (stl::hash<uint32_t>().run((uint32_t)p.x)) ^ 
              ((stl::hash<uint32_t>().run((uint32_t)p.x) << 1));
    }
};


template <>
struct std::hash<simula24::Point>
{
    std::size_t operator()(const simula24::Point& k) const
    {
        return (hash<int>()(k.x) ^ (hash<int>()(k.y) << 1));
    }
};

#endif // MATH_POINT_H_