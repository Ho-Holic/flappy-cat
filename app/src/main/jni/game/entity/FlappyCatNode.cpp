#include "FlappyCatNode.hpp"

FlappyCatNode::FlappyCatNode()
: mChildren() {
  //
}

void FlappyCatNode::initialize() {
  // intentionally left blank
}

void FlappyCatNode::reset() {
  // intentionally left blank
}

void FlappyCatNode::addChild(const FlappyCatNode::shared& child) {

  mChildren.push_back(child);
}


void FlappyCatNode::update(const FrameDuration& frameDuration) {

  for (const auto& child : mChildren)  {
    child->update(frameDuration);
  }
}

void FlappyCatNode::drawOn(const Window& window) const {

  for (const auto& child : mChildren) {
    child->drawOn(window);
  }
}

