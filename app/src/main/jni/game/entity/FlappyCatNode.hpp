#pragma once

// engine
#include <core/Window.hpp>

// stl
#include <memory>
#include <vector>

// game
#include <game/FlappyCatClock.hpp>
#include <game/entity/FlappyCatEntity.hpp>

using FlappyCatNode = FlappyCatEntity; // tmp

class FlappyCatNode2 {
public:
    FlappyCatNode2();

public:
    void addChild(const std::shared_ptr<FlappyCatNode2>& child);

public:
    virtual void initialize();
    virtual void reset();
    virtual void drawOn(const Window& window) const;
    virtual void update(const FrameDuration& frameDuration);

private:
    std::vector<std::shared_ptr<FlappyCatNode2>> mChildren;
};
