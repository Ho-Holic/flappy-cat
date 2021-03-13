#include "Transformation.hpp"
#include <cmath>

mat3 to_mat3(const Transformation& transformation)
{
    vec2 t = transformation.position();
    vec2 s = transformation.scale();
    float angle = transformation.rotation();
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
