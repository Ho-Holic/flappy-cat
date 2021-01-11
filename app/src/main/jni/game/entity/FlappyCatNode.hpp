#pragma once


// engine
#include <core/Window.hpp>

// stl
#include <vector>
#include <memory>

// game
#include <game/FlappyCatClock.hpp>

class FlappyCatNode {
public:
  using shared = std::shared_ptr<FlappyCatNode>;
  using children = std::vector<FlappyCatNode::shared>;

public:
  FlappyCatNode();

public:
  void addChild(const FlappyCatNode::shared& child);

public:
  virtual void initialize();
  virtual void reset();
  virtual void drawOn(const Window& window) const;
  virtual void update(const FrameDuration& frameDuration);

private:
  FlappyCatNode::children mChildren;
};



