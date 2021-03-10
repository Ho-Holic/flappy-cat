#pragma once

#include <core/Color.hpp>
#include <core/RenderContext.hpp>
#include <core/Vertices.hpp>

class Window {
public:
    virtual ~Window() = default;

public:
    virtual void clear(const Color& color) const = 0;
    virtual void drawVertices(const Vertices& vertices,
        const RenderContext& renderContext) const = 0;
    virtual void display() const = 0;
};
