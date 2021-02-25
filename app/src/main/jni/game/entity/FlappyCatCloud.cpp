#include "FlappyCatCloud.hpp"
#include <core/Log.hpp>
#include <style/Guidelines.hpp>

FlappyCatCloud::FlappyCatCloud(const FlappyCatGameConstants& gameConstants)
    : FlappyCatStateNode<FlappyCatCloud>(gameConstants)
    , mParts(0.f)
    , mCloudParts()
{
    //
}

void FlappyCatCloud::initialize()
{
    mCloudParts.reserve(static_cast<size_t>(mParts));

    for (size_t i = 0; i < mParts; ++i) {
        mCloudParts.emplace_back(Position(0.f, 0.f), 0.f, 32);
    }
}

void FlappyCatCloud::drawOn(const Window& window) const
{
    for (const CircleShape& part : mCloudParts) {
        // TODO: make game circle abstraction from entity
        // part.drawOn(window);
        window.draw(part);
    }
}

void FlappyCatCloud::setColor(const Color& color)
{
    for (CircleShape& part : mCloudParts) {

        part.setColor(color);
    }
}

void FlappyCatCloud::setParts(float parts)
{
    mParts = parts;
}

void FlappyCatCloud::foreachCloud(const std::function<void(CircleShape&)>& modifier)
{
    for (CircleShape& part : mCloudParts) {

        REQUIRE(TAG, modifier != nullptr, "foreach modifier must be not null");
        modifier(part);
    }
}
