// game
#include "FlappyCatCloud.hpp"

// engine
#include <core/Log.hpp>

// style
#include <style/Guidelines.hpp>

FlappyCatCloud::FlappyCatCloud(const FlappyCatGameConstants& gameConstants)
    : FlappyCatEntity(gameConstants)
    , mParts(0.f)
    , mCloudParts()
    , mResetModifier([](entity_type&) {})
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

void FlappyCatCloud::reset()
{

    for (entity_type& part : mCloudParts) {

        REQUIRE(TAG, mResetModifier != nullptr, "Reset modifier must be not null");

        mResetModifier(part);
    }
}

void FlappyCatCloud::drawOn(const Window& window) const
{

    for (const entity_type& part : mCloudParts) {
        // TODO: make game circle abstraction from entity
        // part.drawOn(window);
        window.draw(part);
    }
}

void FlappyCatCloud::setResetModifier(const modifier_type& modifier)
{

    mResetModifier = modifier;
}

void FlappyCatCloud::setColor(const Color& color)
{

    for (entity_type& part : mCloudParts) {

        part.setColor(color);
    }
}

void FlappyCatCloud::setParts(float parts)
{

    mParts = parts;
}
