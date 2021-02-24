#pragma once

// engine
#include <core/Window.hpp>

// stl
#include <memory>
#include <vector>

// game
#include <game/FlappyCatClock.hpp>

class FlappyCatNode {
public:
    FlappyCatNode();

public:
    void addChild(const std::shared_ptr<FlappyCatNode>& child);

public:
    virtual void initialize();
    virtual void reset();
    virtual void drawOn(const Window& window) const;
    virtual void update(const FrameDuration& frameDuration);

private:
    std::vector<std::shared_ptr<FlappyCatNode>> mChildren;
};
