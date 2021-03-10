#pragma once

#include <core/Color.hpp>
#include <core/RenderContext.hpp>
#include <core/Vertices.hpp>
#include <core/View.hpp>

class Window {
public:
    Window();
    virtual ~Window() = default;

public:
    virtual void clear(const Color& color) const = 0;
    virtual void drawVertices(const Vertices& vertices,
        const RenderContext& renderContext) const = 0;
    virtual void display() const = 0;

public:
    const View& view() const;
    View& view();

private:
    View m_view;
};
