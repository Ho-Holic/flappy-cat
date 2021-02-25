#include "FlappyCatNode.hpp"

FlappyCatNode2::FlappyCatNode2()
    : mChildren()
{
    //
}

void FlappyCatNode2::initialize()
{
    // intentionally left blank
}

void FlappyCatNode2::reset()
{
    // intentionally left blank
}

void FlappyCatNode2::addChild(const std::shared_ptr<FlappyCatNode2>& child)
{

    mChildren.push_back(child);
}

void FlappyCatNode2::update(const FrameDuration& frameDuration)
{

    for (const auto& child : mChildren) {
        child->update(frameDuration);
    }
}

void FlappyCatNode2::drawOn(const Window& window) const
{

    for (const auto& child : mChildren) {
        child->drawOn(window);
    }
}
