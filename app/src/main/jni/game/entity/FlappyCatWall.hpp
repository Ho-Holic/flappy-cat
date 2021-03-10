#pragma once

#include "entity/FlappyCatStateNode.hpp"
#include <core/Clock.hpp>
#include <core/Window.hpp>
#include <math/vec2.hpp>
#include <prototype/RectangleShape.hpp>

//
//  A4    .----.
//        |....|
//        |....|
//  A3    .----.    <----------.
//                             |
//         hero  <-            | Gap Interval
//                |            |
//  A2    .----.  | <----------.
//        |....|  |
//        |....|  | Gap Displacement
//  A1    .----. <-
//

class FlappyCatWall : public FlappyCatStateNode<FlappyCatWall> {
public:
    FlappyCatWall(const FlappyCatGameConstants& gameConstants);

public:
    void setGapInterval(float interval);
    void setGapDisplacement(float displacement);
    bool collideWithCircle(const vec2& center, float radius);

public:
    void drawOn(const Window& window, const RenderContext& renderContext) const override;

public:
    void setColor(const Color& color);
    const Color& color() const;
    void activateWall();
    bool isActivated() const;

private:
    enum class WallState {
        Normal,
        Activated
    };

private:
    void syncChildren() override;

private:
    float m_gapInterval;
    float m_gapDisplacement;
    RectangleShape m_topBlock;
    RectangleShape m_bottomBlock;
    WallState m_wallState;
};
