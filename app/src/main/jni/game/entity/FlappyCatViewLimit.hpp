#pragma once


// engine
#include <prototype/RectangleShape.hpp>

// game
#include "FlappyCatEntity.hpp"

class FlappyCatViewLimit : public FlappyCatEntity {
public:
  FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;

private:
  virtual void syncChildren() override;

private:
  RectangleShape mTop;
  RectangleShape mTopRight;
  RectangleShape mRight;
  RectangleShape mBottomRight;
  RectangleShape mBottom;
  RectangleShape mBottomLeft;
  RectangleShape mLeft;
  RectangleShape mTopLeft;
};



