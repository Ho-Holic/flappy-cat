#pragma once

class Position {
public:
    using value_type = float;

public:
    Position();
    Position(value_type x, value_type y);

public:
    value_type x() const;
    value_type y() const;

private:
    value_type mX;
    value_type mY;
};

inline Position operator+(const Position& left, const Position& right)
{

    return Position(left.x() + right.x(),
        left.y() + right.y());
}

inline Position operator-(const Position& left, const Position& right)
{

    return Position(left.x() - right.x(),
        left.y() - right.y());
}

inline Position operator*(const Position& left, float scalar)
{

    return Position(left.x() * scalar, left.y() * scalar);
}

inline Position operator*(float scalar, const Position& right)
{

    return Position(scalar * right.x(), scalar * right.y());
}

inline Position operator/(const Position& left, float scalar)
{

    return Position(left.x() / scalar, left.y() / scalar);
}

inline Position operator/(float scalar, const Position& right)
{

    return Position(scalar / right.x(), scalar / right.y());
}

inline Position operator+(const Position& left, float scalar)
{

    return Position(left.x() + scalar, left.y() + scalar);
}

inline Position operator+(float scalar, const Position& right)
{

    return Position(scalar + right.x(), scalar + right.y());
}

inline Position operator-(const Position& p)
{
    return Position(-p.x(), -p.y());
}

// remove functions below, or make good design for this functions

// Normally no multiplication operator for vectors, but this is good for scaling
// other operators must be named e.g. dot_product and so on
inline Position operator*(const Position& left, const Position& right)
{

    return Position(left.x() * right.x(),
        left.y() * right.y());
}

inline Position operator/(const Position& left, const Position& right)
{
    return Position(left.x() / right.x(),
        left.y() / right.y());
}