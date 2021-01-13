#pragma once

// engine
#include <core/Clock.hpp>
#include <core/Position.hpp>
#include <core/Window.hpp>
#include <prototype/RectangleShape.hpp>

// game
#include "FlappyCatEntity.hpp"

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

class FlappyCatWall : public FlappyCatEntity {
public:
    /*
   * TODO: Problem with emplace_back() with no args
   * It has some bug with call to empty constructor
   * Then game show black screen. Also header files
   * shows that emplace build on top of push_back()
   * Seems this is not final version of header
   * Need to check this bug in Ndk r15
   */
    FlappyCatWall(const FlappyCatGameConstants& gameConstants);

public:
    void setGapInterval(float interval);
    void setGapDisplacement(float displacement);
    bool collideWithCircle(const Position& center, float radius);

public:
    virtual void drawOn(const Window& window) const override;

public:
    void setColor(const Color& color);
    const Color& color() const;
    void activateWall();

private:
    enum class WallState {
        Normal,
        Activated
    };

private:
    virtual void syncChildren() override;

private:
    float mGapInterval;
    float mGapDisplacement;
    RectangleShape mTopBlock;
    RectangleShape mBottomBlock;
    WallState mWallState;
};
