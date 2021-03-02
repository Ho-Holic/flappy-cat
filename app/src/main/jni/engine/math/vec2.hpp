#pragma once

class vec2 {
public:
    using value_type = float;

public:
    vec2();
    vec2(value_type x, value_type y);

public:
    value_type x;
    value_type y;
};

inline vec2 operator+(const vec2& left, const vec2& right)
{

    return vec2(left.x + right.x,
        left.y + right.y);
}

inline vec2 operator-(const vec2& left, const vec2& right)
{

    return vec2(left.x - right.x,
        left.y - right.y);
}

inline vec2 operator*(const vec2& left, float scalar)
{

    return vec2(left.x * scalar, left.y * scalar);
}

inline vec2 operator*(float scalar, const vec2& right)
{

    return vec2(scalar * right.x, scalar * right.y);
}

inline vec2 operator/(const vec2& left, float scalar)
{

    return vec2(left.x / scalar, left.y / scalar);
}

inline vec2 operator/(float scalar, const vec2& right)
{

    return vec2(scalar / right.x, scalar / right.y);
}

inline vec2 operator+(const vec2& left, float scalar)
{

    return vec2(left.x + scalar, left.y + scalar);
}

inline vec2 operator+(float scalar, const vec2& right)
{

    return vec2(scalar + right.x, scalar + right.y);
}

inline vec2 operator-(const vec2& p)
{
    return vec2(-p.x, -p.y);
}

// remove functions below, or make good design for this functions

// Normally no multiplication operator for vectors, but this is good for scaling
// other operators must be named e.g. dot_product and so on
inline vec2 operator*(const vec2& left, const vec2& right)
{

    return vec2(left.x * right.x,
        left.y * right.y);
}

inline vec2 operator/(const vec2& left, const vec2& right)
{
    return vec2(left.x / right.x,
        left.y / right.y);
}
