#pragma once

class Window;
class Shape;
class Transformation;

class Render {
public:
    Render();
    virtual ~Render() = default;

public:
    virtual void update(const Shape& shape) = 0;
    virtual void drawOn(const Window& window, const Transformation& transformation) const = 0;
};
