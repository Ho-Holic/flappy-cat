// engine
#include "vec2.hpp"

vec2::vec2(value_type x, value_type y)
    : mX(x)
    , mY(y)
{
    //
}

vec2::vec2()
    : vec2(0.f, 0.f)
{
    //
}

float vec2::x() const
{

    return mX;
}

float vec2::y() const
{

    return mY;
}
