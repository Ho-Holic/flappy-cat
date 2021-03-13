#include "FlappyCatEntity.hpp"
#include <core/Log.hpp>

FlappyCatEntity::FlappyCatEntity(const FlappyCatGameConstants& gameConstants)
    : m_gameConstants(gameConstants)
    , m_position()
    , m_angle(0.f)
    , m_size()
{
    //
}

FlappyCatEntity::~FlappyCatEntity() = default;

void FlappyCatEntity::syncChildren()
{
    // intentionally left blank
}

void FlappyCatEntity::moveBy(const vec2& offset)
{
    moveTo(position() + offset);
}

void FlappyCatEntity::moveTo(const vec2& position)
{
    m_position = position;
    syncChildren();
}

void FlappyCatEntity::resize(const vec2& size)
{
    m_size = size;
    syncChildren();
}

void FlappyCatEntity::rotateTo(float angle)
{
    m_angle = angle;
    syncChildren();
}

const FlappyCatGameConstants& FlappyCatEntity::gameConstants() const
{
    return m_gameConstants;
}

const vec2& FlappyCatEntity::position() const
{
    return m_position;
}

const vec2& FlappyCatEntity::size() const
{
    return m_size;
}

float FlappyCatEntity::rotation() const
{
    return m_angle;
}
