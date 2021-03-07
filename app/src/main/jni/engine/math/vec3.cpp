#include "vec3.hpp"

vec3::vec3(vec3::value_type x, vec3::value_type y, vec3::value_type z)
    : x(x)
    , y(y)
    , z(z)
{
    //
}

vec3::vec3(vec2 xy, vec3::value_type z)
    : vec3(xy.x, xy.y, z)
{
    //
}

vec3::vec3()
    : vec3(0.f, 0.f, 0.f)
{
    //
}

vec3::vec3(vec3::value_type xyz)
    : vec3(xyz, xyz, xyz)
{
    //
}
