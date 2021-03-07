#pragma once

#include "vec2.hpp"

class vec3 {
public:
    using value_type = float;

public:
    vec3();
    vec3(value_type xyz);
    vec3(value_type x, value_type y, value_type z);
    vec3(vec2 xy, value_type z);

public:
    value_type x;
    value_type y;
    value_type z;
};
