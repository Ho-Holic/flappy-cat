#include "Transformation.hpp"
#include <cmath>

mat3 Transformation::toMat3() const
{
    vec2 t = position();
    vec2 s = scale();
    float angle = rotation();
    float sinv = std::sin(angle);
    float cosv = std::cos(angle);

    // clang-format off
    return {
        s.x * cosv, s.x * -sinv, t.x,
        s.y * sinv, s.y * cosv,  t.y,
        0.f,        0.f,         1.f,
    };
    // clang-format on
}
