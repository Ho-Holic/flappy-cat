#include "FlatTransformation.hpp"

FlatTransformation::FlatTransformation(const vec2& position)
    : Transformation()
    , m_position(position)
    , m_origin(0.f, 0.f)
    , m_scale(1.f, 1.f)
    , m_angle(0.f)
    , m_onUpdate()
{
    //
}

FlatTransformation::FlatTransformation()
    : FlatTransformation(vec2(0.f, 0.f))
{
    //
}

FlatTransformation::OnUpdateSignal& FlatTransformation::onUpdate()
{
    return m_onUpdate;
}

const vec2& FlatTransformation::position() const
{
    return m_position;
}

const vec2& FlatTransformation::origin() const
{
    return m_origin;
}

const vec2& FlatTransformation::scale() const
{
    return m_scale;
}

float FlatTransformation::rotation() const
{
    return m_angle;
}

void FlatTransformation::setPosition(const vec2& position)
{
    m_position = position;
    m_onUpdate.emit();
}

void FlatTransformation::setOrigin(const vec2& origin)
{
    m_origin = origin;
    m_onUpdate.emit();
}

void FlatTransformation::setScale(const vec2& factor)
{
    m_scale = factor;
    m_onUpdate.emit();
}

void FlatTransformation::setRotation(float angle)
{
    m_angle = angle;
    m_onUpdate.emit();
}
