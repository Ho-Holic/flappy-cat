#pragma once

#include <prototype/ShapeConstructor.hpp>
#include <prototype/TriangleGeometry.hpp>

// TODO: only right triangle now, later add tilt angle
using TriangleShape = ShapeConstructor<TriangleGeometry>;
