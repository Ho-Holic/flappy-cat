#pragma once

class Window;
class Shape;
struct RenderContext;

class Render {
public:
    Render();
    virtual ~Render() = default;

public:
    virtual void update(const Shape& shape) = 0;
    virtual void drawOn(const Window& window, const RenderContext& renderContext) const = 0;
};
