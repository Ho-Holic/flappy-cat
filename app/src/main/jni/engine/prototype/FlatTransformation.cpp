// engine
#include "FlatTransformation.hpp"

FlatTransformation::FlatTransformation(const Position& position)
    : Transformation()
    , mPosition(position)
    , m_origin(0.f, 0.f)
    , mScale(1.f, 1.f)
    , m_angle(0.f)
    , m_onUpdate()
{
    //
}

FlatTransformation::FlatTransformation()
    : FlatTransformation(Position(0.f, 0.f))
{
    //
}

FlatTransformation::OnUpdateSignal& FlatTransformation::onUpdate()
{

    return m_onUpdate;
}

const Position& FlatTransformation::position() const
{

    return mPosition;
}

const Position& FlatTransformation::origin() const
{

    return m_origin;
}

const Position& FlatTransformation::scale() const
{

    return mScale;
}

float FlatTransformation::rotation() const
{

    return m_angle;
}

void FlatTransformation::setPosition(const Position& position)
{

    mPosition = position;
    m_onUpdate.emit();
}

void FlatTransformation::setOrigin(const Position& origin)
{

    m_origin = origin;
    m_onUpdate.emit();
}

void FlatTransformation::setScale(const Position& factor)
{

    mScale = factor;
    m_onUpdate.emit();
}

void FlatTransformation::setRotation(float angle)
{

    m_angle = angle;
    m_onUpdate.emit();
}
