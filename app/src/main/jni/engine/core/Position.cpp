// engine
#include "Position.hpp"

Position::Position(value_type x, value_type y)
    : mX(x)
    , mY(y)
{
    //
}

Position::Position()
    : Position(0.f, 0.f)
{
    //
}

float Position::x() const
{

    return mX;
}

float Position::y() const
{

    return mY;
}
